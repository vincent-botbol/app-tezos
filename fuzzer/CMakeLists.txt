cmake_minimum_required(VERSION 3.10)

project(TezosFuzzer VERSION 2.2.13 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

set(BOLOS_SDK $ENV{BOLOS_SDK})

add_compile_options(-g -ggdb2 -O3)

include_directories(. ../src
        "${BOLOS_SDK}/include"
        "${BOLOS_SDK}/lib_cxng/include"
        "${BOLOS_SDK}/lib_ux/include"
        )

# definitions for cxng
add_compile_definitions(
    HAVE_ECC
    HAVE_ECC_WEIERSTRASS
    HAVE_SECP256K1_CURVE
    HAVE_SECP256R1_CURVE
    HAVE_ECC_TWISTED_EDWARDS
    HAVE_ED25519_CURVE

    HAVE_ECDSA
    HAVE_EDDSA

    HAVE_HASH
    HAVE_SHA256
    HAVE_BLAKE2)

# set in Makefile
add_compile_definitions(
        OS_IO_SEPROXYHAL
        IO_SEPROXYHAL_BUFFER_SIZE_B=300
        IO_HID_EP_LENGTH=64
        HAVE_UX_FLOW
        VERSION=${PROJECT_VERSION})

set(APP_SRC_DIR "../src")

set(APP_INCLUDE_DIR
    ${APP_SRC_DIR}
    ${APP_SRC_DIR}/swap
)

set(APP_SOURCES
    ${APP_SRC_DIR}/apdu_sign.c
    ${APP_SRC_DIR}/base58.c
    ${APP_SRC_DIR}/globals.c
    ${APP_SRC_DIR}/keys.c
    ${APP_SRC_DIR}/operations.c    
    ${APP_SRC_DIR}/to_string.c
    ${APP_SRC_DIR}/ui_common.c
    ${APP_SRC_DIR}/swap/is_safe_to_swap.c
)

add_executable(test_parser
    fuzz_tx_parser.c
    mocks.c
    ui_fuzzer.c
    ${APP_SOURCES}
)

target_include_directories(test_parser PUBLIC ${APP_INCLUDE_DIR})

target_link_libraries(test_parser PUBLIC bsd)
target_compile_options(test_parser PUBLIC -fsanitize=fuzzer,address,undefined)
target_link_options(test_parser PUBLIC -fsanitize=fuzzer,address,undefined)
