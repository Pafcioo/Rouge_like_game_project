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

# 4) Dodaj moduły (każdy ma swój CMakeLists.txt)
add_subdirectory(algorithm)
add_subdirectory(core)
add_subdirectory(entity)
add_subdirectory(factory)
add_subdirectory(logic)
add_subdirectory(ui)

# 5) Tworzymy główny executable (bez własnych plików źródłowych)
# Wszystkie pliki są w modułach, więc tworzymy "pusty" executable
add_executable(${PROJECT_NAME} core/src/Game.cpp)

# 6) Katalogi include
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}
)

# 7) Wymagamy C++17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# 8) Linkujemy wszystkie moduły i SFML
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        algorithm
        core
        entity
        factory
        logic
        ui
        sfml-graphics
        sfml-window
        sfml-system
)

# 9) Kopiowanie zasobów po kompilacji
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resources
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
)