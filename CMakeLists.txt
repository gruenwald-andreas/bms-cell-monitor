cmake_minimum_required(VERSION 3.16)
project(BmsCellMonitor VERSION 1.0 LANGUAGES CXX)

# Modernes C++17 erzwingen & strikte Compiler-Warnungen aktivieren
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Bibliothek mit der Kernlogik (hardwareunabhängig)
add_library(bms_core src/CellMonitor.cpp)
target_include_directories(bms_core PUBLIC include)

# Hauptprogramm (Simulation)
add_executable(bms_sim src/main.cpp)
target_link_libraries(bms_sim PRIVATE bms_core)

# GoogleTest automatisch einbinden
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Unit-Tests konfigurieren
enable_testing()
add_executable(bms_tests tests/test_cell_monitor.cpp)
target_link_libraries(bms_tests PRIVATE bms_core GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(bms_tests)
