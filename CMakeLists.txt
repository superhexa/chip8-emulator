cmake_minimum_required(VERSION 3.10)
project(chip8-core C)
set(CMAKE_C_STANDARD 11)
include_directories(include)
add_executable(chip8
  src/entry.c
  src/context.c
  src/executor.c
  src/framebuffer.c
  src/keystate.c
  src/timerunit.c
)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(chip8 ${SDL2_LIBRARIES})
