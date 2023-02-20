cmake_minimum_required(VERSION 3.0.0)
project(aoc22 VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ABSL_PROPAGATE_CXX_STD on)

add_subdirectory(thirdparty/abseil-cpp)

add_executable(aoc22_01 day01.cpp)
target_link_libraries(aoc22_01 absl::strings)
target_compile_options(aoc22_01 PRIVATE -Wall -Wextra -Wpedantic)

add_executable(aoc22_02 day02.cpp)
target_link_libraries(aoc22_02 absl::strings)
target_compile_options(aoc22_02 PRIVATE -Wall -Wextra -Wpedantic)

add_executable(aoc22_03 day03.cpp)
target_link_libraries(aoc22_03 absl::btree absl::strings)
target_compile_options(aoc22_03 PRIVATE -Wall -Wextra -Wpedantic)

add_executable(aoc22_04 day04.cpp)
target_link_libraries(aoc22_04 absl::strings)
target_compile_options(aoc22_04 PRIVATE -Wall -Wextra -Wpedantic)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
