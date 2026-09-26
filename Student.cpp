#include <bits/stdc++.h>
#include "Student.h"
#include "Calculation.h"

using namespace std;

//Degautl constructor
Student::Student(): name_(""), surname_(""), homework_(), exam_(0.0){}
//created a studetn with empty name and all other default values

//Parameterized constructor
Student:: Student(const string& name, const string& surname, const vector<int>& homework, double exam){
    name_ = name;
    surname_ = surname;
    homework_ = homework;
    exam_ = exam;
}

//getters
string Student::getName() const{
    return name_;
}

string Student::getSurname() const{
    return surname_;
}

const vector<int> Student::getHomework() const{
    return homework_;
}

double Student::getExam() const{
    return exam_;
}

//setters
void Student::setName(const string& name){
    name_ = name;
}

void Student::setSurname(const string& surname){
    surname_ = surname;
}

void Student::setHomework(const vector<int>& homework){
    homework_ = homework;
}

void Student::addHomework(int grade){
    homework_.push_back(grade);
}

void Student::setExam(double exam){
    exam_ = exam;
}

//calculations
double Student::calculateHomeworkAverage() const{
    return calAverage(homework_);
}

double Student::calculateHomeworkMedian() const{
    return calMedian(homework_);
}

double Student::calculateFinalGrade(bool useMedian = false) const{
    // ? - short form of "if else"
    double homeworkScore = useMedian ? calculateHomeworkMedian() : calculateHomeworkAverage();
    return 0.4 * homeworkScore + 0.6 * exam_;
}
