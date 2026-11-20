#ifndef STUDENT_CLASS
#define STUDENT_CLASS

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <utility>

using namespace std;

// declare but not define!!!!
class Student
{
private:
    string name_;
    string surname_;
    vector<int> homework_;
    double exam_;

public:
    // constructors
    Student();
    Student(const string &name, const string &surname, const vector<int> &homework, double exam);

    // destructor
    ~Student();

    // copy constructor
    Student(const Student &other);

    // Copy assignment operator
    Student &operator=(const Student &other);

    // getters
    string getName() const;
    string getSurname() const;
    const vector<int> getHomework() const;
    double getExam() const;

    // setters
    void setName(const string &name);
    void setSurname(const string &surname);
    void addHomework(int grade);
    void setHomework(const vector<int> &homework);
    void setExam(double exam); // shouldnt be a const bcwe calculate it (set it by formules)

    // calculations
    double calculateHomeworkAverage() const;
    double calculateHomeworkMedian() const;
    double calculateFinalGrade(bool useMedian = false) const; // default value

    // read from a file
    bool readFromStream(istream &is, int homeworkCount);

    // --- Stream Operator Overloads ---
    friend ostream &operator<<(ostream &os, const Student &s);
    friend istream &operator>>(istream &is, Student &s); 
};

// Overloaded stream operators (non-member declarations)
ostream &operator<<(ostream &os, const Student &s);
istream &operator>>(istream &is, Student &s);

#endif