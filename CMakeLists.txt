cmake_minimum_required(VERSION 3.1)

project(radeon C)

set(CMAKE_C_STANDARD 11)

find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)

file(GLOB SOURCES "source/*.c")

include_directories(${ZLIB_INCLUDE_DIRS})

add_executable(radeon ${SOURCES})

target_link_libraries(radeon PRIVATE Threads::Threads ${ZLIB_LIBRARIES})
