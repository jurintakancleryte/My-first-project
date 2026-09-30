#include <bits/stdc++.h>
#include "Student.h"
#include "Calculation.h"

using namespace std;

// Degautl constructor
Student::Student() : name_(""), surname_(""), homework_(), exam_(0.0) {}
// created a studetn with empty name and all other default values

// Parameterized constructor
Student::Student(const string &name, const string &surname, const vector<int> &homework, double exam)
{
    name_ = name;
    surname_ = surname;
    homework_ = homework;
    exam_ = exam;
}

// getters
string Student::getName() const
{
    return name_;
}

string Student::getSurname() const
{
    return surname_;
}

const vector<int> Student::getHomework() const
{
    return homework_;
}

double Student::getExam() const
{
    return exam_;
}

// setters
void Student::setName(const string &name)
{
    name_ = name;
}

void Student::setSurname(const string &surname)
{
    surname_ = surname;
}

void Student::setHomework(const vector<int> &homework)
{
    homework_ = homework;
}

void Student::addHomework(int grade)
{
    homework_.push_back(grade);
}

void Student::setExam(double exam)
{
    exam_ = exam;
}

// calculations
double Student::calculateHomeworkAverage() const
{
    return calAverage(homework_);
}

double Student::calculateHomeworkMedian() const
{
    return calMedian(homework_);
}

double Student::calculateFinalGrade(bool useMedian) const
{
    // ? - short form of "if else"
    double homeworkScore = useMedian ? calculateHomeworkMedian() : calculateHomeworkAverage();
    return 0.4 * homeworkScore + 0.6 * exam_;
}

bool Student::readFromStream(istream &is, int homeworkCount)
{
    string tempName, tempSurname;
    if (!(is >> tempName >> tempSurname))
    //exit problem of there is the problem with surname
    {
        return false; //end of file or reading failure
    }

    vector<int> tempHomework;  //empty vector
    tempHomework.reserve(homeworkCount);
    //making ampty spaces(indexes) in vector

    for (int i = 0; i < homeworkCount; i++)
    {
        int grade; //store values
        if (!(is >> grade)) 
        //if we get any error while accesing the grade will return false
        {
            return false;
        }

        //validate homework grade range (1-10)
        if (grade < 1 || grade > 10)
        {
            cerr << "Error: Invalid homework grade (" << grade << ") for "
                 << tempName << " " << tempSurname << ".\n";
            return false;
        }

        tempHomework.push_back(grade); //push grade into vector
    }

    double tempExam;
    if (!(is >> tempExam))
    {
        return false;
    }

    //validate exam grade range (1-10)
    if (tempExam < 1.0 || tempExam > 10.0)
    {
        //cerr - printing error message
        cerr << "Error: Invalid exam grade (" << tempExam << ") for "
             << tempName << " " << tempSurname << ".\n";
        return false;
    }

    //assign validated values to member variables
    name_ = tempName;
    surname_ = tempSurname;
    homework_ = move(tempHomework); 
    //move - wont remove previous values (memory management)
    // homework_ = tempHomework
    exam_ = tempExam;

    return true;
}