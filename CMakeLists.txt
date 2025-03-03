cmake_minimum_required(VERSION 3.10)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

# Найти библиотеку Curses
find_package(Curses REQUIRED COMPONENTS ncursesw)

add_executable(MyApp 
    main.cpp
    models/Hotel.cpp  # Исправлено: порядок файлов важен
    models/Client.cpp
    models/Room.cpp
    engine/Screen.cpp
    algorithms/Processing.cpp
    algorithms/Sort.cpp
)

# Указать компилятору искать заголовочные файлы в этих папках
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}  # Текущая директория (корневая папка проекта)
    ${CMAKE_CURRENT_SOURCE_DIR}/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/models
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms
    ${CURSES_INCLUDE_DIRS}  # Исправлено: правильная переменная
)

# Подключить библиотеку к целевому исполняемому файлу
target_link_libraries(MyApp PRIVATE ${CURSES_LIBRARIES})