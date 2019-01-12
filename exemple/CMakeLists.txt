cmake_minimum_required(VERSION 3.2)

set(TARGET "table")
project(${TARGET})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(
        ../include
        ./src
        ./
)


set(SOURCES
        src/main.cpp
        )

set(HEADERS
        )

add_executable(
        ${TARGET}
        ${SOURCES}
        ${HEADERS}
)

target_link_libraries(
        ${TARGET}
)