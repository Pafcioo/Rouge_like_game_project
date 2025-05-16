cmake_minimum_required(VERSION 3.28)

# 1) Nazwa projektu i standard C++
project(Rouge_like_game_project LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2) Katalog wyjściowy dla binarek
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 3) Pobranie SFML przez FetchContent
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.1
    GIT_SHALLOW    ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

# 4) Zbieramy wszystkie pliki .cpp/.hpp z src/
file(GLOB GAME_SOURCES
    "${CMAKE_SOURCE_DIR}/Game/*.cpp"
    "${CMAKE_SOURCE_DIR}/Game/*.h"
)

add_subdirectory(Game/AIController)
add_subdirectory(Game/Spawner)
add_subdirectory(Game/Factory)

# 5) Tworzymy target o nazwie projektu
add_executable(${PROJECT_NAME} ${GAME_SOURCES})

# 6) Wymagamy C++17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# 7) Linkujemy potrzebne moduły SFML
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Spawner
        AIController
        Factory
        SFML::Graphics
        SFML::Window
        SFML::System
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Assets
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets
)





