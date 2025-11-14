cmake_minimum_required(VERSION 3.25)

# Set Project Name, version and used languages.
project(CHIP8.Emulator VERSION 0.1.0 LANGUAGES C CXX)

# Set default C++ version.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include external library
include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 12.1.0
)

FetchContent_MakeAvailable(fmt)

include(FetchContent)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.32.10
)

FetchContent_MakeAvailable(SDL2)

# Set Default Main executable. References to all single files.
add_executable(CHIP8.Emulator 
    src/CHIP8.UI.SDL/Main.cpp
    src/CHIP8.Core/CPU.cpp
    src/CHIP8.Core/Memory.cpp
    src/CHIP8.Core/RegistersEnum.h
    src/CHIP8.Core/KeyEnum.h
)

# Link external libs to this project.
target_link_libraries(CHIP8.Emulator PRIVATE fmt::fmt)
target_link_libraries(CHIP8.Emulator PRIVATE SDL2::SDL2)