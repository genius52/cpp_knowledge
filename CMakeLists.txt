cmake_minimum_required(VERSION 3.30)
project(cpp_feature)

set(CMAKE_CXX_STANDARD 20)
include_directories(".")
aux_source_directory(. DIR_SRCS)
aux_source_directory(basic DIR_SRCS)

add_executable(cpp_feature ${DIR_SRCS})
