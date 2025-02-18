# CMakeList.txt : CMake project for CapstoneTetris, include source and define
# project specific logic here.
#

# !!! If you're still having issues building after pointing to the built SDL2-devel-2.30.8-VC directory
# The exe requires that SDL2.DLL (x64 version) is in the same directory.
set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(CMAKE_PREFIX_PATH "C:/lib/SDL2/cmake" "C:/lib/SDL2_ttf/cmake")

if(WIN32)
    include_directories(${SDL2_INCLUDE_DIRS} "C:/lib/SDL2_ttf/include")  # For Windows
    set(SDL2_LIB_DIR "C:/lib/SDL2/lib/x64")
    set(SDL2_TTF_LIB_DIR "C:/lib/SDL2_ttf/lib/x64")
    link_directories(${SDL2_LIB_DIR} ${SDL2_TTF_LIB_DIR})
else()
    include_directories(${SDL2_INCLUDE_DIRS} SDL2)  # For Linux/macOS
endif()


# Add source to this project's executable.
add_executable (CapstoneBlockGame
                "main.cpp" "main.hpp"
                "application.cpp" "application.hpp"
                "blockgame/blockgame.cpp" "blockgame/blockgame.hpp"
                "utils/vector2.hpp"
                "tetromino/tetromino.cpp" "tetromino/tetrominos.hpp"
                "gameeventhandler.cpp" "gameeventhandler.hpp"
                "UI/UIManager.cpp" "UI/UIManager.hpp"
                "mainmenu/mainmenu.cpp" "mainmenu/mainmenu.hpp"
                "UI/UIElement.cpp" "UI/UIElement.hpp"
                "UI/UIRect.cpp" "UI/UIRect.hpp"
                "UI/UIButton.cpp" "UI/UIButton.hpp"
                "UI/UILabel.cpp" "UI/UILabel.hpp"
                "UI/UILabeledButton.cpp" "UI/UILabeledButton.hpp")


target_link_libraries(CapstoneBlockGame SDL2::SDL2 SDL2::SDL2main SDL2_ttf)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CapstoneBlockGame PROPERTY CXX_STANDARD 20)
endif()

