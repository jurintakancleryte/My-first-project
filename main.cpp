// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <string>
// #include <random>
// #include <limits>
// #include <iomanip>

#include <bits/stdc++.h>

using namespace std;

struct Student // sukuriame objekta Studentas varda, pav, nd, exam
{
    string firstName;
    string lastName;
    vector<int> homework;
    int exam;
};

// Calculation Functions:

float calAverage(const vector<int> &homework) // apskaiciuojame namu darbu vidurki
{
    if (homework.empty())
        return 0.0f; // Prevent division by zero

    float sum = 0.0f;
    for (int mark : homework)
    {
        sum += mark;
    }
    return sum / homework.size();
}

float calMedian(vector<int> homework) // apskaicuojame medianos vidurki
{
    if (homework.empty())
        return 0.0f;

    sort(homework.begin(), homework.end());
    int n = homework.size();

    if (n % 2 == 0)
    {
        return (homework[(n / 2) - 1] + homework[n / 2]) / 2.0f; // 2.0f preserves decimal
    }
    else
    {
        return homework[n / 2];
    }
}

int getRandomInt(int min, int max)
{
    static mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// void function is empty function; does not return any value

void addStudentManually(vector<Student> &students)
{
    Student s;

    cout << "\n--- Add Student ---\n";
    cout << "Enter first name: ";
    cin >> s.firstName;

    cout << "Enter last name: ";
    cin >> s.lastName;

    // Validate exam grade (1 - 10)
    cout << "Enter exam result (1-10): ";
    while (!(cin >> s.exam) || s.exam < 1 || s.exam > 10)
    {
        cout << "Invalid exam grade! Enter an integer between 1 and 10: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // search it
    }

    // Validate number of homework assignments (0 - 10)
    int n;
    cout << "Enter the number of homework assignments (0-10): ";
    while (!(cin >> n) || n < 0 || n > 10)
    {
        cout << "Invalid number! Enter a count between 0 and 10: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Validate each homework score (1 - 10)
    for (int i = 0; i < n; i++)
    {
        int score;
        cout << "Enter score for homework #" << (i + 1) << " (1-10): ";
        while (!(cin >> score) || score < 1 || score > 10)
        {
            cout << "Invalid score! Enter an integer between 1 and 10: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        s.homework.push_back(score);
    }

    students.push_back(s);
    cout << "Student added successfully!\n";
}

// kuriame funckija kuri generuoja "automatiskai" studentus

void generateRandomStudents(vector<Student> &students)
{
    int numberOfStudents;
    cout << "\nHow many random students do you want to generate? (1-1000): ";

    // Validate student count
    while (!(cin >> numberOfStudents) || numberOfStudents < 1 || numberOfStudents > 1000)
    {
        cout << "Invalid input! Please enter a number between 1 and 1000: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // kadangi programa negali pati sukurti, nes dudoame sarasa random vardu/pavardziu

    const vector<string> firstNames = {
        "John", "Peter", "Anna", "Mark", "Laura",
        "Tom", "Emma", "David", "Sarah", "Harsh"};

    const vector<string> lastNames = {
        "Smith", "Brown", "Johnson", "Wilson", "Taylor",
        "Anderson", "Thomas", "Jackson", "White", "Harris"};

    for (int i = 0; i < numberOfStudents; i++)
    {
        Student s;
        s.firstName = firstNames[getRandomInt(0, firstNames.size() - 1)];
        s.lastName = lastNames[getRandomInt(0, lastNames.size() - 1)];

        int homeworkCount = getRandomInt(1, 10);
        for (int j = 0; j < homeworkCount; j++) // for loop in other for loop
        {
            s.homework.push_back(getRandomInt(1, 10));
        }

        s.exam = getRandomInt(1, 10);
        students.push_back(s);
    }

    cout << numberOfStudents << " random students generated successfully!\n";
}

bool cmp(const Student &s1, const Student &s2)
{
    if (s1.firstName == s2.firstName)
    {
        return s1.lastName < s2.lastName;
    }
    return s1.firstName < s2.firstName;
}

void displayStudentResults(vector<Student> &students)
{
    if (students.empty())
    {
        cout << "\nThere are no students currently.\n";
        return;
    }

    sort(students.begin(), students.end(), cmp);

    cout << "\n========== Display Results ==========\n";
    cout << "Choose calculation method:\n";
    cout << "1. Average\n";
    cout << "2. Median\n";
    cout << "3. Both\n";
    cout << "Enter your choice: ";

    int choice;
    // Repeatedly loop until user inputs 1, 2, or 3
    while (!(cin >> choice) || choice < 1 || choice > 3)
    {
        cout << "Invalid choice! Enter 1, 2, or 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        // This discards everything remaining on the line up to the Enter key
        // leaving the input buffer empty and ready for a fresh input attempt on the next loop iteration.
    }

    cout << fixed << setprecision(2);   //setprecision - after the point only two decimal places

    if (choice == 1)
    {
        // left, setw(n) - allying to left 
        //used to make tables structured
        cout << left << setw(15) << "First Name" << setw(15) << "Last Name" << "Average\n";
        cout << "-------------------------------------------\n";
        for (const auto &s : students)
        {
            cout << left << setw(15) << s.firstName << setw(15) << s.lastName << calAverage(s.homework) << "\n";
        }
    }
    else if (choice == 2)
    {
        cout << left << setw(15) << "First Name" << setw(15) << "Last Name" << "Median\n";
        cout << "-------------------------------------------\n";
        for (const auto &s : students)
        {
            cout << left << setw(15) << s.firstName << setw(15) << s.lastName << calMedian(s.homework) << "\n";
        }
    }
    else if (choice == 3)
    {
        cout << left << setw(15) << "First Name" << setw(15) << "Last Name" << setw(12) << "Average" << "Median\n";
        cout << "--------------------------------------------------------\n";
        for (const auto &s : students)
        {
            cout << left << setw(15) << s.firstName << setw(15) << s.lastName
                 << setw(12) << calAverage(s.homework) << calMedian(s.homework) << "\n";
        }
    }
}

bool readStudentsFromFile(vector<Student> &students)
{
    ifstream file("kursiokai.txt"); //ifstream - read the file 

    // Check if file is opened
    if (!file.is_open())
    {
        cout << "Error: Could not open the file\n";
        return false;
    }

    // Read header
    string headerLine;
    getline(file, headerLine);  //gives us the first line

    // Count how many homework columns are in the header
    stringstream headerStream(headerLine);

    string word;
    int homeworkCount = 0;

    while (headerStream >> word)
    {
        // ND1, ND2, ND3, ... are homework columns
        if (word.rfind("ND", 0) == 0) //finds the number of homework in each file
        {
            homeworkCount++;
            // homeworkCount = homeworkCount + 1;
        }
    }

    // Make sure we found homework columns
    if (homeworkCount == 0)
    {
        cout << "Error: No homework columns found in the file.\n";
        return false;
    }

    string firstName;
    string lastName;

    while (file >> firstName >> lastName) //condition to check if line exists or not
    {
        Student student;

        student.firstName = firstName;
        student.lastName = lastName;

        //student.homework.clear(); // <-- verify if vector is empty

        // Read all homework grades

        for (int i = 0; i < homeworkCount; i++) 
        {
            int grade;
            if (!(file >> grade))  
            {
                cout << "Error: Invalid homework grade for "
                     << firstName << " " << lastName << ".\n";

                return false;
            }

            // Grade must be 1-10
            if (grade < 1 || grade > 10)
            {
                cout << "Error: Invalid homework grade: "
                     << grade << "\n";

                cout << "Student: "
                     << firstName << " "
                     << lastName << "\n";

                cout << "Homework grades must be between 1 and 10.\n";

                return false;
            }

            student.homework.push_back(grade);  //psuh the grade into homework vector
        }

        // Read exam grade
        if (!(file >> student.exam)) //copying the next value from the file into student.exam
        {
            cout << "Error: Invalid exam grade for "
                 << firstName << " "
                 << lastName << ".\n";

            return false;
        }

        // Validate exam grade --> condition
        if (student.exam < 1 || student.exam > 10)
        {
            cout << "Error: Invalid exam grade: "
                 << student.exam << "\n";

            cout << "Student: "
                 << firstName << " "
                 << lastName << "\n";

            cout << "Exam grade must be between 1 and 10.\n";

            return false;
        }

        // Make sure there is at least one homework
        if (student.homework.empty())
        {
            cout << "Error: Student has no homework grades.\n";
            return false;
        }

        students.push_back(student);
    }

    file.close();  //uzdarome faila, nes uzsima vietos

    if (students.empty())
    {
        cout << "Error: No students found in the file.\n";
        return false;
    }

    cout << students.size()
         << " students loaded successfully.\n";

    return true;
}

void showMenu()
{
    cout << "\n====================================\n";
    cout << "        STUDENT GRADE SYSTEM\n";
    cout << "====================================\n";
    cout << "1. Add student manually\n";
    cout << "2. Generate random students\n";
    cout << "3. Display student results\n";
    cout << "4. Read student data from file\n";
    cout << "5. Exit\n";
}

int main()
{
    vector<Student> students;
    int choice = 0;

    do
    {
        showMenu();
        cout << "Enter your choice (1-4): ";

        // Validates main menu choice directly
        while (!(cin >> choice) || choice < 1 || choice > 5)
        {
            cout << "Invalid choice! Please enter a number from 1 to 5: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }

        switch (choice)  //switch statement
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
            students.clear();  //before reading from file we clear a vector

            if (readStudentsFromFile(students))
            {
                cout << "Students loaded successfully.\n";
            }
            break;
        case 5:
            cout << "Exiting program...\n";
            break;
        }

    } while (choice != 5);

    return 0;
}