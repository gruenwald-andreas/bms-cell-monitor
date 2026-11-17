cmake_minimum_required(VERSION 3.16)
project(BmsCellMonitor VERSION 1.0 LANGUAGES CXX)

# Enforce Modern C++17 and strict compiler warnings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Core hardware-independent BMS library
add_library(bms_core src/CellMonitor.cpp)
target_include_directories(bms_core PUBLIC include)

# Simulation executable
add_executable(bms_sim src/main.cpp)
target_link_libraries(bms_sim PRIVATE bms_core)

# Fetch GoogleTest automatically
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Configure unit tests
enable_testing()
add_executable(bms_tests tests/test_cell_monitor.cpp)
target_link_libraries(bms_tests PRIVATE bms_core GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(bms_tests)
