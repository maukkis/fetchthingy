cmake_minimum_required(VERSION 3.25.1)

project(fetchthing
DESCRIPTION "simple fetch script with multithreading written in C++")

set(CMAKE_CXX_STANDARD 17)
set(DCKMAKE_BUILD_TYPE Release)
file(GLOB_RECURSE fetchthing_src "src/*.cpp"
"src/*.h")

add_executable(fetchthing ${fetchthing_src})
