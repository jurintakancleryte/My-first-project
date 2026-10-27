#ifndef FUNCTION_H
#define FUNCTION_H

#include "Student.h"
using namespace std;

int getRandomInt(int min, int max);

void addStudentManually(vector<Student> &students);

void generateRandomStudents(vector<Student> &students);

void displayStudentResults(vector<Student> &students);

void displayStudentResultsList(list<Student> &students);

// return a sting gives us an option
string selectOrEnterFile();

bool readStudentsFromFile(const string &filename, vector<Student> &students);

bool readStudentsFromFileList(const string &filename, list<Student> &students);

// generates a dataset file containing student records with random grades
void generateDatasetFile(const string &filename, int studentCount, int homeworkCount = 5);

// generate all dataset files
void generateAllDatasets();

void separateStudents(const vector<Student> &allStudents,
                      vector<Student> &belowFive,
                      vector<Student> &fiveOrAbove,
                      bool useMedian = false);

void separateStudentsStrategy1(const vector<Student> &allStudents,
                      vector<Student> &belowFive,
                      vector<Student> &fiveOrAbove,
                      bool useMedian = false);

void separateStudentsStrategy2(vector<Student> &allStudents,
                      vector<Student> &belowFive,
                      bool useMedian = false);

void separateStudentsStrategy3(vector<Student> &allStudents,
                      vector<Student> &belowFive,
                      bool useMedian = false);

void separateStudentsList(const list<Student> &allStudents,
                      list<Student> &belowFive,
                      list<Student> &fiveOrAbove,
                      bool useMedian = false);

void separateStudentsListStrategy1(const list<Student> &allStudents,
                      list<Student> &belowFive,
                      list<Student> &fiveOrAbove,
                      bool useMedian = false);

void separateStudentsListStrategy2(list<Student> &allStudents,
                      list<Student> &belowFive,
                      bool useMedian = false);

void separateStudentsListStrategy3(list<Student> &allStudents,
                      list<Student> &belowFive,
                      bool useMedian = false);

bool writeStudentsToFile(const string &filename,
                         const vector<Student> &students,
                         bool useMedian = false);

bool writeStudentsToFileList(const string &filename,
                         const list<Student> &students,
                         bool useMedian = false);

void demonstrateMemoryAddresses();

void runBenchmarkForFile(const string& filename, bool useMedian = false, int repetitions = 5);

void runAllContainerBenchmarks();

void showMenu();

#endif