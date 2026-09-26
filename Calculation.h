#ifndef CALCULATION_H
#define CALCULATION_H

#include <vector>

using namespace std;

//Forward declaration of Student to avoid circular header dependencies
class Student;

//Returns 0.0 if the vector is empty
double calAverage(const vector<int>& homework);

double calMedian(vector<int> homework);

//Comparison function to sort students alphabetically
//First compares by first name, then by last name (surname)
bool compareByName(const Student& a, const Student& b);

#endif