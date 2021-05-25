#include "globals.h"
#include "to_string.h"
#include "ui.h"

#include <stdlib.h>

#define G_display global.dynamic_display

void clear_data() {
    explicit_bzero(&G_display.screen_title, sizeof(G_display.screen_title));
    explicit_bzero(&G_display.screen_value, sizeof(G_display.screen_value));
}

void ux_prepare_display(ui_callback_t ok_c, ui_callback_t cxl_c) {
    global.dynamic_display.screen_stack_size = global.dynamic_display.formatter_index;
    global.dynamic_display.formatter_index = 0;
    global.dynamic_display.current_state = STATIC_SCREEN;

    if (ok_c) global.dynamic_display.ok_callback = ok_c;
    if (cxl_c) global.dynamic_display.cxl_callback = cxl_c;
}

void set_screen_data() {
    struct screen_data *fmt = &G_display.screen_stack[G_display.formatter_index];
    clear_data();
    copy_string((char *) G_display.screen_title, sizeof(G_display.screen_title), fmt->title);
    fmt->callback_fn(G_display.screen_value, sizeof(G_display.screen_value), fmt->data);
}

void ux_confirm_screen(ui_callback_t ok_c, ui_callback_t cxl_c) {
    for (int i = 0; i < G_display.formatter_index; i++) {
        struct screen_data *fmt = &global.dynamic_display.screen_stack[i];
        fmt->callback_fn(G_display.screen_value, sizeof(G_display.screen_value), fmt->data);
        printf("%s: %s\n", fmt->title, G_display.screen_value);
    }
    ux_prepare_display(ok_c, cxl_c);

    ok_c();
    THROW(ASYNC_EXCEPTION);
}
