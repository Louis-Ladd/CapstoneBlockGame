# CMakeList.txt : CMake project for CapstoneTetris, include source and define
# project specific logic here.
#

if(WIN32)
	set(CMAKE_PREFIX_PATH "C:/lib/")
endif()

find_package(SDL2 REQUIRED)

# Add source to this project's executable.
add_executable (CapstoneTetris "main.cpp" "main.h" "game.cpp" "game.h")

target_link_libraries(CapstoneTetris SDL2::SDL2 SDL2::SDL2main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CapstoneTetris PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
