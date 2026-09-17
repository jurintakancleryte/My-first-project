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

//void function is empty function; does not return any value

void addStudentManually(vector<Student> &students)
{
    Student s;

    cout << "\n--- Add Student ---\n";
    cout << "Enter first name: ";
    cin >> s.firstName;

    cout << "Enter last name: ";
    cin >> s.lastName;

    //Validate exam grade (1 - 10)
    cout << "Enter exam result (1-10): ";
    while (!(cin >> s.exam) || s.exam < 1 || s.exam > 10)
    {
        cout << "Invalid exam grade! Enter an integer between 1 and 10: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // search it
    }

    //Validate number of homework assignments (0 - 10)
    int n;
    cout << "Enter the number of homework assignments (0-10): ";
    while (!(cin >> n) || n < 0 || n > 10)
    {
        cout << "Invalid number! Enter a count between 0 and 10: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    //Validate each homework score (1 - 10)
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

//kuriame funckija kuri generuoja "automatiskai" studentus

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

    //kadangi programa negali pati sukurti, nes dudoame sarasa random vardu/pavardziu

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
        for (int j = 0; j < homeworkCount; j++) //for loop in other for loop
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This discards everything remaining on the line up to the Enter key, leaving the input buffer empty and ready for a fresh input attempt on the next loop iteration.
    }

    cout << fixed << setprecision(2);

    if (choice == 1)
    {
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

void showMenu()
{
    cout << "\n====================================\n";
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
    int choice = 0;

    do
    {
        showMenu();
        cout << "Enter your choice (1-4): ";

        //Validates main menu choice directly
        while (!(cin >> choice) || choice < 1 || choice > 4)
        {
            cout << "Invalid choice! Please enter a number from 1 to 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

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
            cout << "Exiting program...\n";
            break;
        }

    } while (choice != 4);

    return 0;
}