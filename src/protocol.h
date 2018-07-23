#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "baking_auth.h"

#include "cx.h"

#define MAGIC_BYTE_INVALID 0x00
#define MAGIC_BYTE_BLOCK 0x01
#define MAGIC_BYTE_BAKING_OP 0x02
#define MAGIC_BYTE_UNSAFE_OP 0x03
#define MAGIC_BYTE_UNSAFE_OP2 0x04
#define MAGIC_BYTE_UNSAFE_OP3 0x05

static inline uint8_t get_magic_byte(const uint8_t *data, size_t length) {
    if (data == NULL || length == 0) return MAGIC_BYTE_INVALID;
    else return *data;
}

bool is_block_valid(const void *data, size_t length);

level_t get_block_level(const void *data, size_t length); // Precondition: is_block_valid returns true

#define READ_UNALIGNED_BIG_ENDIAN(type, in) \
    ({ \
        const uint8_t *bytes = (uint8_t*)in; \
        uint8_t out_bytes[sizeof(type)]; \
        type res; \
\
        for (size_t i = 0; i < sizeof(type); i++) { \
            out_bytes[i] = bytes[sizeof(type) - i - 1]; \
        } \
        memcpy(&res, out_bytes, sizeof(type)); \
\
        res; \
    })

struct operation_group_header {
    uint8_t magic_byte;
    uint8_t hash[32];
} __attribute__((packed));

struct contract {
    uint8_t outright;
    uint8_t curve_code;
    uint8_t pkh[HASH_SIZE];
} __attribute__((packed));

enum operation_tag {
    OPERATION_TAG_REVEAL = 7,
    OPERATION_TAG_TRANSACTION = 8,
    OPERATION_TAG_DELEGATION = 10,
};

struct operation_header {
    uint8_t tag;
    struct contract contract;
} __attribute__((packed));

struct delegation_contents {
    uint8_t delegate_present;
    uint8_t curve_code;
    uint8_t hash[HASH_SIZE];
} __attribute__((packed));

void guard_valid_self_delegation(const void *data, size_t length, cx_curve_t curve,
                                 size_t path_length, uint32_t *bip32_path);

// Return false if the transaction isn't easily parseable, otherwise prompt with given callbacks
// and do not return, but rather throw ASYNC.
bool prompt_transaction(const void *data, size_t length, cx_curve_t curve,
                        size_t path_length, uint32_t *bip32_path,
                        callback_t ok, callback_t cxl);
