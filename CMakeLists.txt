cmake_minimum_required(VERSION 3.12)
project(StudentGradeSystem VERSION 0.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
main.cpp
Student.cpp
functions.cpp
Calculation.cpp
)

set(HEADERS
Student.h
functions.h
Calculation.h
)

add_executable(student_grade_sys ${SOURCES} ${HEADERS})

if(MSVC)
target_compile_options(student_grade_sys PRIVATE /O2 /W4)
else()
target_compile_options(student_grade_sys PRIVATE -O2 -Wall -Wextra)
endif()