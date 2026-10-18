cmake_minimum_required(VERSION 4.2.3)
project(arinc429_decoder)
add_library(arinc429 src/placeholder.cpp)
target_include_directories(arinc429 PUBLIC include)
