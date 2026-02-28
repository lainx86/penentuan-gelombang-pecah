cmake_minimum_required(VERSION 3.14)
project(GelombangPecah VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ──────────────────────────────────────────────
# Dependencies via FetchContent
# ──────────────────────────────────────────────
include(FetchContent)

FetchContent_Declare(
    OpenXLSX
    GIT_REPOSITORY https://github.com/troldal/OpenXLSX.git
    GIT_TAG        master
    GIT_SHALLOW    TRUE
)

# Disable unnecessary targets for dependencies to speed up build and silence warnings
set(OPENXLSX_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(OPENXLSX_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(OpenXLSX)

# ──────────────────────────────────────────────
# Executable
# ──────────────────────────────────────────────
add_executable(gelombang_pecah
    src/main.cpp
    src/wave_calc.cpp
    third_party/InterpKit/src/logic.cpp
)

target_include_directories(gelombang_pecah PRIVATE 
    include
    third_party/InterpKit/src
)

target_link_libraries(gelombang_pecah PRIVATE
    OpenXLSX::OpenXLSX
)

if(MINGW)
    target_link_options(gelombang_pecah PRIVATE -static)
endif()

# ──────────────────────────────────────────────
# Embed data_tabel.xlsx into the binary
# ──────────────────────────────────────────────
set(EMBED_INPUT  "${CMAKE_SOURCE_DIR}/third_party/InterpKit/data_tabel.xlsx")
set(EMBED_OUTPUT "${CMAKE_BINARY_DIR}/generated/embedded_data.h")

add_custom_command(
    OUTPUT  ${EMBED_OUTPUT}
    COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${EMBED_INPUT}
            -DOUTPUT_FILE=${EMBED_OUTPUT}
            -P ${CMAKE_SOURCE_DIR}/third_party/InterpKit/cmake/embed_resource.cmake
    DEPENDS ${EMBED_INPUT}
            ${CMAKE_SOURCE_DIR}/third_party/InterpKit/cmake/embed_resource.cmake
    COMMENT "Embedding data_tabel.xlsx into binary..."
)

add_custom_target(embed_data DEPENDS ${EMBED_OUTPUT})
add_dependencies(gelombang_pecah embed_data)

target_include_directories(gelombang_pecah PRIVATE ${CMAKE_BINARY_DIR}/generated)
