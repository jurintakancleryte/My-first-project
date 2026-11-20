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

Student::~Student(){
    // Standard library members (string, vector) automatically release their own resources.
    // Explicit destructor body satisfies the Rule of Three requirement.
}

// Copy constructor
Student::Student(const Student& other)
    : name_(other.name_), surname_(other.surname_),
      homework_(other.homework_), exam_(other.exam_)
{
}

// Copy assignment operator
Student& Student::operator=(const Student& other)
{
    // Guard against self-assignment (e.g. s = s)  
    if (this != &other) 
    {
        name_ = other.name_;
        surname_ = other.surname_;
        homework_ = other.homework_;
        exam_ = other.exam_;
    }
    return *this; // Return *this for assignment chaining (e.g. s1 = s2 = s3)
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
    // exit problem of there is the problem with surname
    {
        return false; // end of file or reading failure
    }

    vector<int> tempHomework; // empty vector
    tempHomework.reserve(homeworkCount);
    // making ampty spaces(indexes) in vector

    for (int i = 0; i < homeworkCount; i++)
    {
        int grade; // store values
        if (!(is >> grade))
        // if we get any error while accesing the grade will return false
        {
            return false;
        }

        // validate homework grade range (1-10)
        if (grade < 1 || grade > 10)
        {
            cerr << "Error: Invalid homework grade (" << grade << ") for "
                 << tempName << " " << tempSurname << ".\n";
            return false;
        }

        tempHomework.push_back(grade); // push grade into vector
    }

    double tempExam;
    if (!(is >> tempExam))
    {
        return false;
    }

    // validate exam grade range (1-10)
    if (tempExam < 1.0 || tempExam > 10.0)
    {
        // cerr - printing error message
        cerr << "Error: Invalid exam grade (" << tempExam << ") for "
             << tempName << " " << tempSurname << ".\n";
        return false;
    }

    // assign validated values to member variables
    name_ = tempName;
    surname_ = tempSurname;
    homework_ = move(tempHomework);
    // move - wont remove previous values (memory management)
    //  homework_ = tempHomework
    exam_ = tempExam;

    return true;
}

// Overloaded output operator (<<) to output a Student's information to a generic ostream
ostream& operator<<(ostream& os, const Student& s)
{
    os << s.name_ << " " << s.surname_;
    for (int hw : s.homework_)
    {
        os << " " << hw;
    }
    os << " " << s.exam_;
    return os;
}

istream& operator>>(istream& is, Student& s)
{
    string line;
    // Skip any leading empty lines or whitespace
    while (getline(is, line))
    {
        if (line.find_first_not_of(" \t\r\n") != string::npos)
        {
            break;
        }
    }

    if (line.empty() || line.find_first_not_of(" \t\r\n") == string::npos) //error checking (for space and ect)
    {
        is.setstate(ios::failbit); //the process - failed
        return is;
    }

    stringstream ss(line);
    string tempName, tempSurname;
    if (!(ss >> tempName >> tempSurname))
    {
        is.setstate(ios::failbit);
        return is;
    }

    vector<string> tokens; //counting for all left data
    string tok;
    while (ss >> tok)
    {
        tokens.push_back(tok);
    }

    if (tokens.empty())
    {
        is.setstate(ios::failbit);
        return is;
    }

    vector<int> tempHomework;
    double tempExam = 0.0;

    //error handling
    try
    {
        if (tokens.size() == 1)
        {
            tempExam = stod(tokens[0]); //stod - string to double
        }
        else
        {
            tempHomework.reserve(tokens.size() - 1);
            for (size_t i = 0; i < tokens.size() - 1; ++i)
            {
                int g = stoi(tokens[i]); //stoi - string to integer
                if (g < 1 || g > 10)
                {
                    is.setstate(ios::failbit);
                    return is;
                }
                tempHomework.push_back(g);
            }
            tempExam = stod(tokens.back());
        }

        if (tempExam < 1.0 || tempExam > 10.0)
        {
            is.setstate(ios::failbit);
            return is;
        }
    }

    //all catch handler - every tyoe of error
    catch (...)
    {
        is.setstate(ios::failbit);
        return is;
    }

    s.name_ = tempName;
    s.surname_ = tempSurname;
    s.homework_ = std::move(tempHomework);
    s.exam_ = tempExam;

    return is;
}