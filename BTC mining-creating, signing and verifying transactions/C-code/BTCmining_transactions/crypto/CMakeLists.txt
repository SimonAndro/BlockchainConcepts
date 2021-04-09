add_library(crypto SHARED
        hash.c
        blake3_dispatch.c
        blake3_portable.c
        memzero.c
        ripemd160.c
    )
