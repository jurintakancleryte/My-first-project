#ifndef FUNCTION_H
#define FUNCTION_H

#include "Student.h"
using namespace std;

int getRandomInt(int min, int max);

void addStudentManually(vector<Student>& students);

void generateRandomStudents(vector<Student> &students);

void displayStudentResults(vector<Student>& students);

//return a sting, gives us an option
string selectOrEnterFile();

bool readStudentsFromFile(const string& filename, vector<Student>& students);

#endif