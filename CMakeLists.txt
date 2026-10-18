cmake_minimum_required(VERSION 4.2.3)
project(arinc429_decoder)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip
)

FetchContent_MakeAvailable(googletest)

# CMake's testing infrastructure
enable_testing()

add_library(arinc429 src/placeholder.cpp)
target_include_directories(arinc429 PUBLIC include)
target_compile_features(arinc429 PUBLIC cxx_std_17)
target_compile_options(arinc429 PRIVATE -Wall -Wextra -Wpedantic)

add_executable(arinc429_cli cli/main.cpp cli/table_printer.cpp)
target_link_libraries(arinc429_cli PRIVATE arinc429)
target_compile_options(arinc429_cli PRIVATE -Wall -Wextra -Wpedantic)

add_executable(arinc429_tests tests/sanity_test.cpp)
target_link_libraries(arinc429_tests PRIVATE arinc429 GTest::gtest_main)
target_compile_options(arinc429_tests PRIVATE -Wall -Wextra -Wpedantic)

include(GoogleTest)
gtest_discover_tests(arinc429_tests)

