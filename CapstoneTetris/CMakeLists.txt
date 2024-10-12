# CMakeList.txt : CMake project for CapstoneTetris, include source and define
# project specific logic here.
#

# !!! If you're still having issues building after pointing to the built SDL2-devel-2.30.8-VC directory
# The exe requires that SDL2.DLL (x64 version!) is in the out/build/x64-debug/CapstoneTetris directory.

if(WIN32)
	set(CMAKE_PREFIX_PATH "C:/lib/")
endif()

find_package(SDL2 REQUIRED)

# Add source to this project's executable.
add_executable (CapstoneTetris "main.cpp" "main.h" "game.cpp" "game.h" "tetris/tetris.h" "tetris/tetris.cpp" "utils/vector2.h" "tetromino/tetrominos.h")

target_link_libraries(CapstoneTetris SDL2::SDL2 SDL2::SDL2main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CapstoneTetris PROPERTY CXX_STANDARD 20)
endif()

