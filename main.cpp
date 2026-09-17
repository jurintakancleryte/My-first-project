// #include <iostream>
// #include <vector>
// #include <cmath>

#include <bits/stdc++.h>
using namespace std;

struct Student // sukuriame objekta Studentas varda, pav, nd, exam
{
    string firstName;
    string lastName;
    vector<int> homework;
    int exam;
};

float calAverage(vector<int> homework) // apskaiciuojame namu darbu vidurki
{
    int n = homework.size();
    float sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum = sum + homework[i];
    }

    float average = float(sum / n);
    return average;
}

float calMedian(vector<int> homework) // apskaicuojame medianos vidurki
{
    sort(homework.begin(), homework.end());
    int n = homework.size();
    if (n % 2 == 0)
    {
        return (homework[(n / 2) - 1] + homework[n / 2]) / 2;
    }
    else
    {
        return homework[n / 2];
    }
}

float calFinalScoreuMedian(const Student &s) // const - constant: doesnt let the data/ values to be changed
{
    float median = calMedian(s.homework);
    float score = 0.4 * median + 0.6 * s.exam; // apskaiciuota pagal duota formule
    return score;
}

float calFinalScoreAverage(const Student &s)
{
    float average = calAverage(s.homework);
    float score = 0.4 * average + 0.6 * s.exam;
    return score;
}

// void function is empty function; does not return any value

void addStudentManually(vector<Student> &students) //& - push data inside list
                                                   // pass by values and pass by referencwes
{
    Student s1; // creating objects
    cout << "Enter the first name: ";
    cin >> s1.firstName;
    cout << "Enter the last name: ";
    cin >> s1.lastName;
    cout << "Enter exam result: ";
    cin >> s1.exam;

    int n;
    cout << "Enter the number of homework: \n";
    cin >> n;
    cout << "Enter the score of your homeworks: " << endl;

    for (int i = 0; i < n; i++)
    {
        int h;
        cin >> h;
        s1.homework.push_back(h);
    }

    students.push_back(s1); // pusch_back - insert values into the list
    return;                 // using return (with no 0) because void function (empty function)
}

bool cmp(Student &s1, Student &s2) // True/ False
{
    if (s1.firstName == s2.firstName)
    {
        return s1.lastName < s2.lastName; // jeigu studentai turi vienodus vardus - tada tikrinamos ju pavardes
    }
    return s1.firstName < s2.firstName;
}

void displayStudentResults(vector<Student> students)
{
    if (students.size() == 0)
    {
        // check for empty students vector
        cout << "There are no students currently.\n";
        return;
    }

    sort(students.begin(), students.end(), cmp);

    cout << "\n========== DISPLAY RESULTS ==========\n";

    cout << "Choose calculation method:\n";
    cout << "1. Average\n";
    cout << "2. Median\n";
    cout << "3. Both\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > 3)
    {
        cout << "Invalid choice, Enter your choice again: \n";
        cin >> choice;
    }
    if (choice == 1)
    {
        cout << "First Name   Last Name    Average \n";
        for (auto s : students)
        {
            cout << s.firstName << "    " << s.lastName << "   " << calAverage(s.homework) << endl;
        }
    }
    else if (choice == 2)
    {
        cout << "First Name   Last Name    Median \n";
        for (auto s : students)
        {
            cout << s.firstName << "    " << s.lastName << "    " << calMedian(s.homework) << endl;
        }
    }
    else if (choice == 3)
    {
        cout << "First Name   Last Name    Average    Median \n";
        for (auto s : students)
        {
            // auto takes the data type (int, string and etc.) - automatiskai nustato tipa
            cout << s.firstName << "    " << s.lastName << "    " << calAverage(s.homework) << "    " << calMedian(s.homework) << endl;
        }
    }
    return;
}

#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

int getRandomInt(int min, int max)
{
    static mt19937 gen(random_device{}()); // static -allows certain members to belong to the class or file
                                           // rather than to individual objects or function calls
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

void generateRandomStudents(vector<Student> &students)
{
    int numberOfStudents;
    cout << "\nHow many random students do you want to generate? ";
    cin >> numberOfStudents;

    if (numberOfStudents <= 0)
    {
        cout << "Invalid number of students.\n";
        return;
    }

    vector<string> firstNames = {
        "John", "Peter", "Anna", "Mark", "Laura",
        "Tom", "Emma", "David", "Sarah", "Harsh"};

    vector<string> lastNames = {
        "Smith", "Brown", "Johnson", "Wilson", "Taylor",
        "Anderson", "Thomas", "Jackson", "White", "Harris"};

    for (int i = 0; i < numberOfStudents; i++)
    {
        Student student;

        student.firstName = firstNames[getRandomInt(0, firstNames.size() - 1)];
        student.lastName = lastNames[getRandomInt(0, lastNames.size() - 1)];

        int homeworkCount = getRandomInt(2, 5); // it can be changed as per requirement

        for (int i = 0; i < homeworkCount; i++)
        {
            int randomHomeWorkScore = getRandomInt(1, 10); // assuming grades are 1-10
            student.homework.push_back(randomHomeWorkScore);
        }

        student.exam = getRandomInt(1, 10);

        students.push_back(student);
    }

    cout << numberOfStudents << " random students generated successfully!\n";
    return;
}

void showMenu()
{
    cout << "====================================\n";
    cout << "        STUDENT GRADE SYSTEM\n";
    cout << "====================================\n";

    cout << "1. Add student manually\n";
    cout << "2. Generate random students\n";
    cout << "3. Display student results\n";
    cout << "4. Exit\n";
}

int main()
{
    vector<Student> students;

    cout << "Enter your choice:\n";
    int choice;

    //(Do loop) - Kodo blokas bus ivykdytas viena karta pries patikrinant, ar salyga tenkinama.
    // Tada ciklas bus kartojamas tol, kol salyga bus tenkinama.
    do
    {
        showMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            addStudentManually(students);
            break;
        case 2:
            generateRandomStudents(students);
            break;
        case 3:
            displayStudentResults(students);
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice, enter correct choice: \n";
            break;
        }
    } while (choice != 4);

    return 0;
}