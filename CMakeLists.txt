cmake_minimum_required(VERSION 3.15)

project(SpiralColors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NAME ${PROJECT_NAME})

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/third_party")
include(FetchContent)

# --------------------------- SFML ---------------------------
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 3.0.2
)


FetchContent_MakeAvailable(sfml)

add_subdirectory(cmake-wrapper)

add_executable(${NAME} color_utils.cc convertColor.cc main.cc)

# Thêm include path và link libraries
target_include_directories(
    ${NAME}
    PRIVATE
    ${LCMS_INCLUDE_DIRS}
)

target_compile_definitions(
    ${NAME}
    PRIVATE
    LCMS_PROFILE_DIR=\"profiles\"
)

target_link_libraries(
    ${NAME}
    PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    lcms
)

add_custom_command(
    TARGET ${NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/profiles
    $<TARGET_FILE_DIR:${NAME}>/profiles
)
