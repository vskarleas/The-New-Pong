cmake_minimum_required(VERSION 3.12)
project(Pong VERSION 7.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OS-specific configurations
if(APPLE)
    # macOS Homebrew paths
    set(SDL2_DIR "/opt/homebrew/Cellar/sdl2/2.30.12/lib/cmake/SDL2")
    set(SDL2_TTF_DIR "/opt/homebrew/Cellar/sdl2_ttf/2.24.0/lib/cmake/SDL2_ttf")
    set(SDL2_MIXER_DIR "/opt/homebrew/Cellar/sdl2_mixer/2.8.1/lib/cmake/SDL2_mixer")
    set(SDL2_IMAGE_DIR "/opt/homebrew/Cellar/sdl2_image/2.8.4/lib/cmake/SDL2_image")
    set(SDL2_NET_DIR "/opt/homebrew/Cellar/sdl2_net/2.0.1/lib/cmake/SDL2_net")

    set(SDL2_INCLUDE_DIRS "/opt/homebrew/Cellar/sdl2/2.30.12/include/SDL2")
    set(SDL2_TTF_INCLUDE_DIRS "/opt/homebrew/Cellar/sdl2_ttf/2.24.0/include/SDL2")
    set(SDL2_MIXER_INCLUDE_DIRS "/opt/homebrew/Cellar/sdl2_mixer/2.8.1/include/SDL2")
    set(SDL2_IMAGE_INCLUDE_DIRS "/opt/homebrew/Cellar/sdl2_image/2.8.4/include/SDL2")
    set(SDL2_NET_INCLUDE_DIRS "/opt/homebrew/Cellar/sdl2_net/2.0.1/include/SDL2")
elseif(UNIX AND NOT APPLE)
    # Linux paths
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
    pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_NET REQUIRED SDL2_net)
endif()

# Find required packages
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_net REQUIRED)

# Include directories for SDL2 and its extensions
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_NET_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Create a library target for the game components
add_library(${PROJECT_NAME}_lib
    paddle.cpp
    ball_base.cpp
    classic_ball.cpp
    square_ball.cpp
    triangle_ball.cpp
    page_3b_0t.cpp
    page_3b.cpp
    game_save.cpp
    page_2b_1t.cpp
    page_3b_1t.cpp
    renderers.cpp
    page_4b_1t.cpp
    ai.cpp
    game.cpp
    game_over.cpp
    user.cpp
    network.cpp
    gui.cpp
    letter.cpp
    sound_effects.cpp
    power.cpp
    invisible_power.cpp
    inverse_power.cpp
)

# Create the main executable
add_executable(${PROJECT_NAME} main.cpp)

# Link the library to the main executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    ${PROJECT_NAME}_lib
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
    SDL2_image::SDL2_image
    SDL2_net::SDL2_net
)

# Link SDL2 libraries to the lib target
target_link_libraries(${PROJECT_NAME}_lib 
    PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
    SDL2_image::SDL2_image
    SDL2_net::SDL2_net
)

# Include directories
target_include_directories(${PROJECT_NAME}_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)

# Copy assets to build directory
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
)
add_dependencies(${PROJECT_NAME} copy_assets)

# Enabling testing
enable_testing()

# Create test directory
add_subdirectory(tests)