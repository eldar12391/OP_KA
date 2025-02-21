cmake_minimum_required(VERSION 3.10)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

# Найти библиотеку Curses
find_package(Curses REQUIRED COMPONENTS ncursesw)

add_executable(MyApp 
    main.cpp
    models/Client.cpp
    models/Room.cpp
    models/Hotel.cpp
    engine/Screen.cpp
)

# Подключить библиотеку к целевому исполняемому файлу
target_include_directories(MyApp PRIVATE ${CURSES_INCLUDE_DIR})
target_link_libraries(MyApp PRIVATE ${CURSES_LIBRARIES})