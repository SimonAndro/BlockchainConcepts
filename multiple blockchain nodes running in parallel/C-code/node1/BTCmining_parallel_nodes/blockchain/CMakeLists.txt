
SET(CMAKE_BUILD_TYPE "debug")

add_library(blockchain 
        src/common.c
        src/transaction.c
        src/block.c
)

target_include_directories (blockchain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
