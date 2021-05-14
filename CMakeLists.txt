cmake_minimum_required(VERSION 2.8)
project(G52CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wall -Wextra")
add_definitions(-std=c++11)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${G52CPP_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

set(SOURCE_FILES src/mainfunction.cpp 
src/BaseEngine.cpp
src/BouncingBall.cpp
src/BouncingBallMain.cpp
src/DisplayableObject.cpp
src/DraggingDemo.cpp
src/DrawingSurface.cpp
src/FlashingDemo.cpp
src/FontManager.cpp
src/ImageMappingDemo.cpp
src/MazeDemoMain.cpp
src/MazeDemoObject.cpp
src/MazeDemoTileManager.cpp
src/SimpleDemo.cpp
src/SimpleImage.cpp
src/StarfieldDemo.cpp
src/TileManager.cpp
src/ZoomingDemo.cpp
src/MyDemoA.cpp
src/SpaceshipObject.cpp
src/Follower.cpp
src/MyDemoTileManager.cpp
src/Part2/AnimatedImage.cpp
src/Part2/MiningGame.cpp
src/Part2/WorldTileManager.cpp
src/Part2/WorldGen.cpp
src/Part2/Player.cpp
src/Part2/Entity.cpp
src/Part2/Inventory.cpp
)

add_executable(SDL2_App ${SOURCE_FILES})
target_link_libraries(SDL2_App ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY})

add_custom_command(TARGET SDL2_App PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${G52CPP_SOURCE_DIR}/src/resources ${CMAKE_CURRENT_BINARY_DIR})
