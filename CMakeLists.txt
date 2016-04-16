cmake_minimum_required(VERSION 2.8.4)
project(fast-bwkp)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64 -Wall -Werror")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -ggdb")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -O3 -flto")
set(CMAKE_INCLUDE_SYSTEM_FLAG_C "-isystem ")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -save-temps=obj")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-format -std=gnu11")
endif()

include_directories("src")

set(SOURCE_FILES
    src/instance.c
    src/instance.h
    src/lagrange.c
    src/lagrange.h
    src/main.c
    src/sort.c
    src/sort.h
    src/tester.c
    src/tester.h
    src/timing.c
    src/timing.h
)

add_executable(fast-bwkp ${SOURCE_FILES})