cmake_minimum_required(VERSION 3.10)
project(student_teacher_management VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra)
endif()

# classes shared by the program and the tests
add_library(stms_core STATIC src/input.cpp src/person.cpp src/student.cpp src/teacher.cpp)
target_include_directories(stms_core PUBLIC include)

add_executable(stms src/main.cpp)
target_link_libraries(stms PRIVATE stms_core)

enable_testing()
add_executable(stms_tests tests/stms_tests.cpp)
target_link_libraries(stms_tests PRIVATE stms_core)
add_test(NAME stms_tests COMMAND stms_tests)
