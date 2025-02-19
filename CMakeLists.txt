cmake_minimum_required(VERSION 3.10)

project(Sname)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(MyApp 
main.cpp
models/Client.cpp
models/Room.cpp
models/Hotel.cpp
)