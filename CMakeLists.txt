cmake_minimum_required(VERSION 3.10)

project("Foo Project" VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -O3")
# set(SFML_STATIC_LIBRARIES TRUE)

add_library(GS STATIC src/graphics_settings.cpp)
add_library(GA STATIC src/game_app.cpp)
add_executable(GameDev2 src/main.cpp)
target_include_directories(GameDev2 PUBLIC include)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
#find_package(GL REQUIRED)   ## https://www.startpage.com/do/dsearch?query=libGL+cmake+find_package
#find_package(GLEW REQUIRED) ## https://www.startpage.com/do/dsearch?query=libGLEW+cmake+find_package

target_link_libraries(GameDev2 GS GA GL GLEW sfml-graphics sfml-window sfml-system)

