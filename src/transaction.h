#pragma once

#include <stdint.h>

enum { IMPLIED, ORIGINATED } contract_type;

struct contract __attribute__((packed)) {
    uint8_t contract_type;
    uint8_t curve;
    uint8_t source_pkh[20];
};

struct transaction_prefix __attribute__((packed)) {
    uint8_t operation_type;
    struct contract source;
    uint64_t fee_micros;
    int32_t counter;
    uint8_t gas[0];
};

struct transaction_suffix __attribute__((packed)) {
    uint64_t storage_limit;
    uint64_t amount_micros;
    struct contract destination;
    uint8_t has_field_params;
    uint8_t field_params[0];
};
