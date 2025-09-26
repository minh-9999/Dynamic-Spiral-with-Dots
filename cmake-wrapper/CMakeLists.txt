cmake_minimum_required(VERSION 3.15)
project(lcms LANGUAGES C)

include(FetchContent)

# --------------------------- Little CMS ---------------------------
FetchContent_Declare(
    lcms_source
    GIT_REPOSITORY https://github.com/mm2/Little-CMS/
    GIT_TAG lcms2.17
)
FetchContent_MakeAvailable(lcms_source)

set(LCMS_SRC_DIR ${lcms_source_SOURCE_DIR})

file(
    GLOB
    LCMS_SRC
    ${LCMS_SRC_DIR}/src/*.c
)

add_library(
    lcms
    STATIC ${LCMS_SRC}
)

target_include_directories(
    lcms
    PUBLIC ${LCMS_SRC_DIR}/include
)
