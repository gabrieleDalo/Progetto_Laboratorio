cmake_minimum_required(VERSION 3.16)
project(Progetto_Laboratorio)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(Google_Tests)
set(SOURCE_FILES main.cpp Subject.h Observer.h Controller.cpp Controller.h Model.cpp Model.h View.cpp View.h)

find_package(wxWidgets REQUIRED net gl core base xrc adv)
include(${wxWidgets_USE_FILE})

add_executable(Progetto_Laboratorio ${SOURCE_FILES})

# for each of your dependent executable/library targets:
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

