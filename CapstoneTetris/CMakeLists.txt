# CMakeList.txt : CMake project for CapstoneTetris, include source and define
# project specific logic here.
#

# !!! If you're still having issues building after pointing to the built SDL2-devel-2.30.8-VC directory
# The exe requires that SDL2.DLL (x64 version) is in the same directory.

find_package(SDL2 REQUIRED)

if(WIN32)
    include_directories(${SDL2_INCLUDE_DIRS})  # For Windows
else()
    include_directories(${SDL2_INCLUDE_DIRS} SDL2)  # For Linux/macOS
endif()


# Add source to this project's executable.
add_executable (CapstoneTetris "main.cpp" "main.hpp" "game.cpp" "game.hpp" "tetris/tetris.hpp" "tetris/tetris.cpp" "utils/vector2.hpp" "tetromino/tetrominos.hpp" "tetromino/tetromino.cpp" "input.cpp" "input.hpp")

target_link_libraries(CapstoneTetris SDL2::SDL2 SDL2::SDL2main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CapstoneTetris PROPERTY CXX_STANDARD 20)
endif()

