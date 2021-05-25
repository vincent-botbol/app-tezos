#include "cx.h"
#include "os.h"
#include "ux.h"
#include <stdlib.h>

cx_err_t cx_hash_no_throw(cx_hash_t *hash,
                          uint32_t mode,
                          const uint8_t *in,
                          size_t len,
                          uint8_t *out,
                          size_t out_len) {
    return CX_OK;
}

cx_err_t cx_ecdsa_sign_no_throw(const cx_ecfp_private_key_t *pvkey,
                                uint32_t mode,
                                cx_md_t hashID,
                                const uint8_t *hash,
                                size_t hash_len,
                                uint8_t *sig,
                                size_t *sig_len,
                                uint32_t *info) {
    return CX_OK;
}

size_t cx_hash_sha256(const uint8_t *in, size_t in_len, uint8_t *out, size_t out_len) {
    return CX_SHA256_SIZE;
}

size_t cx_hash_get_size(const cx_hash_t *ctx) {
    return 32;  // FIXME: return real length
}

cx_err_t cx_blake2b_init_no_throw(cx_blake2b_t *hash, size_t size) {
    return CX_OK;
}

cx_err_t cx_ecfp_generate_pair_no_throw(cx_curve_t curve,
                                        cx_ecfp_public_key_t *pubkey,
                                        cx_ecfp_private_key_t *privkey,
                                        bool keepprivate) {
    return CX_OK;
}

cx_err_t cx_ecfp_init_private_key_no_throw(cx_curve_t curve,
                                           const uint8_t *rawkey,
                                           size_t key_len,
                                           cx_ecfp_private_key_t *pvkey) {
    return CX_OK;
}

cx_err_t cx_ecdomain_parameters_length(cx_curve_t cv, size_t *length) {
    *length = 32;  // FIXME: return real length
    return CX_OK;
}

cx_err_t cx_edwards_compress_point_no_throw(cx_curve_t curve, uint8_t *P, size_t P_len) {
    return CX_OK;
}

cx_err_t cx_eddsa_sign_no_throw(const cx_ecfp_private_key_t *pv_key,
                                cx_md_t hashID,
                                const uint8_t *hash,
                                size_t hash_len,
                                uint8_t *sig,
                                size_t sig_len) {
    return CX_OK;
}

void os_perso_derive_node_bip32(cx_curve_t curve,
                                const unsigned int *path,
                                unsigned int pathLength,
                                unsigned char *privateKey,
                                unsigned char *chain) {
}

void os_perso_derive_node_with_seed_key(unsigned int mode,
                                        cx_curve_t curve,
                                        const unsigned int *path,
                                        unsigned int pathLength,
                                        unsigned char *privateKey,
                                        unsigned char *chain,
                                        unsigned char *seed_key,
                                        unsigned int seed_key_length) {
}

void io_seproxyhal_display_default(const bagl_element_t *element) {
}

unsigned short io_exchange(unsigned char channel_and_flags, unsigned short tx_len) {
    return 0;
}

unsigned int os_ux_blocking(bolos_ux_params_t *params) {
    return BOLOS_UX_OK;
}

void os_sched_exit(bolos_task_status_t exit_code) {
    exit(exit_code);
}

void os_longjmp(unsigned int exception) {
    longjmp(try_context_get()->jmp_buf, exception);
}

try_context_t *current_context = NULL;

try_context_t *try_context_get(void) {
    return current_context;
}

try_context_t *try_context_set(try_context_t *ctx) {
    try_context_t *previous_ctx = current_context;
    current_context = ctx;
    return previous_ctx;
}

void *pic(void *linked_address) {
    return linked_address;
}
