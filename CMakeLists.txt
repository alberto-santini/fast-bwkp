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
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(Cplex)

include_directories("src")
include_directories(SYSTEM ${CPLEX_INCLUDE_DIRS})

set(SOURCE_FILES
  src/primal/mip.h
  src/primal/mip.c
  src/primal/solution.h
  src/primal/solution.c
  src/relaxations/cardinality_preserving.c
  src/relaxations/cardinality_preserving.h
  src/relaxations/capacity_preserving.c
  src/relaxations/capacity_preserving.h
  src/relaxations/continuous.c
  src/relaxations/continuous.h
  src/relaxations/n_items_bound.c
  src/relaxations/n_items_bound.h
  src/relaxations/solution.c
  src/relaxations/solution.h
  src/relaxations/lagrange.h
  src/relaxations/lagrange.c
  src/instance.c
  src/instance.h
  src/main.c
  src/sort.c
  src/sort.h
  src/timing.c
  src/timing.h
)

add_executable(fast-bwkp ${SOURCE_FILES})
target_link_libraries(fast-bwkp ${CPLEX_LIBRARIES})

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    target_link_libraries(fast-bwkp m pthread)
endif()