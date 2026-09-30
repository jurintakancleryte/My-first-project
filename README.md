Student Grade Management System

A C++ program for managing student records, calculating final grades, separating students based on their final grades, and measuring the performance of different operations on large datasets.

Compile run command: g++ main.cpp Calculation.cpp Student.cpp functions.cpp -o Student_program 
Program run command: ./Student_program

Features

    Student data is implemented using a Student class.
    Student data members are private.
    Public methods are provided for accessing and working with student data.
    Supports reading student data from files.
    Supports calculating final grades using:
        Homework average
        Homework median
    Separates students into two groups:
        Final grade below 5.0
        Final grade 5.0 or above
    Writes the two groups into separate output files.
    Generates large datasets for performance testing.
    Measures the execution time of:
        File reading
        Student grouping
        File writing
    Uses multiple dataset sizes to analyze performance.

Project Structure
├── main.cpp
├── Student.h
├── Student.cpp
├── functions.h
├── functions.cpp
├── Calculation.h
├── Calculation.cpp
└── README.md
