#include "apdu.h"
#include "apdu_sign.h"
#include "globals.h"
#include "os.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

uint8_t G_io_apdu_buffer[IO_APDU_BUFFER_SIZE];

#define CLA 0x80

#define P1_FIRST       0x00
#define P1_NEXT        0x01
#define P1_LAST_MARKER 0x80

void handle_apdu_sign_no_throw() {
    BEGIN_TRY {
        TRY {
            handle_apdu_sign(INS_SIGN);
        }
        CATCH_ALL {
            clear_apdu_globals();
        }
        FINALLY {
        }
    }
    END_TRY;
}

bool called_from_swap = false;
swap_values_t swap_values;

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    const uint8_t first_apdu[] = {0x80, 0x04, 0x00, 0x00, 0x11, 0x04, 0x80, 0x00, 0x00, 0x2C, 0x80,
                                  0x00, 0x06, 0xC1, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00};
    const uint8_t second_apdu[] = {0x80, 0x04, 0x01, 0x00, 0x01, 0x03};

    memset(&global, 0, sizeof(global));

    memcpy(G_io_apdu_buffer, first_apdu, sizeof(first_apdu));
    handle_apdu_sign_no_throw();

    memcpy(G_io_apdu_buffer, second_apdu, sizeof(second_apdu));
    handle_apdu_sign_no_throw();

    bool last = false;
    while (!last) {
        last = Size <= MAX_APDU_SIZE;

        G_io_apdu_buffer[0] = CLA;
        G_io_apdu_buffer[1] = INS_SIGN;
        G_io_apdu_buffer[2] = P1_NEXT;
        G_io_apdu_buffer[3] = 0x00;
        if (last) {
            G_io_apdu_buffer[2] |= P1_LAST_MARKER;
            G_io_apdu_buffer[4] = Size;
            memcpy(G_io_apdu_buffer + OFFSET_CDATA, Data, Size);
            Data += Size;
            Size = 0;
        } else {
            G_io_apdu_buffer[4] = MAX_APDU_SIZE;
            memcpy(G_io_apdu_buffer + OFFSET_CDATA, Data, MAX_APDU_SIZE);
            Data += MAX_APDU_SIZE;
            Size -= MAX_APDU_SIZE;
        }
        handle_apdu_sign_no_throw();
    }

    return 0;
}
