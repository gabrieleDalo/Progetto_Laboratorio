cmake_minimum_required(VERSION 3.16)
project(Progetto_Laboratorio)

set(CMAKE_CXX_STANDARD 11)

find_package(wxWidgets REQUIRED net gl core base xrc adv)
include(${wxWidgets_USE_FILE})

add_executable(Progetto_Laboratorio main.cpp Subject.h Observer.h Controller.cpp Controller.h Model.cpp Model.h View.cpp View.h Cell.cpp Cell.h)

# for each of your dependent executable/library targets:
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
