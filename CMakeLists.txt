cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lsfml-graphics -lsfml-window -lsfml-system")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

project(chess VERSION 1.0)

find_package(SFML 2.5.1 REQUIRED network audio graphics window system)

file(GLOB SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
