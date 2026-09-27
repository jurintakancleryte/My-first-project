#include "functions.h"
#include "Calculation.h"
#include <bits/stdc++.h>

using namespace std;

// function to return random number
int getRandomInt(int min, int max)
{
    static mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

void addStudentManually(vector<Student> &students)
{
    string name, surname;
    double exam;
    vector<int> homework;

    cout << "\n--- Add Student Manually ---\n";
    cout << "Enter first name: ";
    cin >> name;

    cout << "Enter last name (surname): ";
    cin >> surname;

    // validate exam grade (1-10)
    cout << "Enter exam result (1-10): ";
    while (!(cin >> exam) || exam < 1.0 || exam > 10.0)
    {
        cout << "Invalid exam grade! Enter a number between 1 and 10: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Validate number of homework assignments (0-10)
    int count;
    cout << "Enter the number of homework assignments (0-10): ";
    while (!(cin >> count) || count < 0 || count > 10)
    {
        cout << "Invalid number! Enter a count between 0 and 10: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // read and validate each homework score
    for (int i = 0; i < count; i++)
    {
        int score;
        cout << "Enter score for homework #" << (i + 1) << " (1-10): ";

        while (!(cin >> score) || score < 1 || score > 10)
        {
            cout << "Invalid score! Enter an integer between 1 and 10: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        homework.push_back(score);
    }

    // construct and push Student object
    students.emplace_back(name, surname, homework, exam);
    // emplace_back - adds element to the end of Student constructor
    // avoid to create intermediate objects
    cout << "Student " << name << " " << surname << " added successfully!\n";
}

void generateRandomStudents(vector<Student> &students)
{
    {
        int numberOfStudents;
        cout << "\nHow many random students do you want to generate? (1-1000): ";

        while (!(cin >> numberOfStudents) || numberOfStudents < 1 || numberOfStudents > 1000)
        {
            cout << "Invalid input! Please enter a number between 1 and 1000: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // vectors for random first name and last name
        const vector<string> firstNames = {
            "John", "Peter", "Anna", "Mark", "Laura", "Tom", "Emma", "David",
            "Sarah", "Harsh", "Jurinta", "Ivanov"};

        const vector<string> lastNames = {
            "Smith", "Brown", "Johnson", "Wilson", "Taylor",
            "Anderson", "Thomas", "Jackson", "White", "Harris", "Kancleryte"};

        // reserve - creates empty spaces into vector
        students.reserve(students.size() + numberOfStudents);

        for (int i = 0; i < numberOfStudents; i++)
        {
            string fname = firstNames[getRandomInt(0, firstNames.size() - 1)];
            string lname = lastNames[getRandomInt(0, lastNames.size() - 1)];

            int hwCount = getRandomInt(1, 10);
            vector<int> hw;
            hw.reserve(hwCount);

            for (int j = 0; j < hwCount; j++)
            {
                hw.push_back(getRandomInt(1, 10));
            }

            double examGrade = getRandomInt(1, 10);
            students.emplace_back(fname, lname, hw, examGrade);
        }

        cout << numberOfStudents << " random students generated successfully!\n";
    }
}

void displayStudentResults(vector<Student> &students)
{
    if (students.empty())
    {
        cout << "\nThere are no students currently loaded.\n";
        return;
    }

    // sort students alphabetically using external compareByName helper
    sort(students.begin(), students.end(), compareByName);

    cout << "\n========== Display Results ==========\n";
    if (students.size() > 1000)
    {
        cout << "Note: Displaying the first 1,000 of " << students.size() << " students.\n";
    }

    cout << "Choose calculation method:\n";
    cout << "1. Average\n";
    cout << "2. Median\n";
    cout << "3. Both\n";
    cout << "Enter your choice: ";

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 3)
    {
        cout << "Invalid choice! Enter 1, 2, or 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << fixed << setprecision(2);
    // if decimal number sets it to last two digits after dot
    size_t displayCount = min((size_t)1000, students.size());
    // size_t - similar to int (data type)

    if (choice == 1)
    {
        cout << left << setw(15) << "First Name"
             << setw(15) << "Last Name"
             << "Final (Avg.)\n";
        cout << "-------------------------------------------\n";
        for (size_t i = 0; i < displayCount; ++i)
        {
            const auto &s = students[i];
            cout << left << setw(15) << s.getName()
                 << setw(15) << s.getSurname()
                 << s.calculateFinalGrade(false) << "\n";
        }
    }
    else if (choice == 2)
    {
        cout << left << setw(15) << "First Name"
             << setw(15) << "Last Name"
             << "Final (Med.)\n";
        cout << "-------------------------------------------\n";
        for (size_t i = 0; i < displayCount; ++i)
        {
            const auto &s = students[i];
            cout << left << setw(15) << s.getName()
                 << setw(15) << s.getSurname()
                 << s.calculateFinalGrade(true) << "\n";
        }
    }
    else if (choice == 3)
    {
        cout << left << setw(15) << "First Name"
             << setw(15) << "Last Name"
             << setw(15) << "Final (Avg.)"
             << "Final (Med.)\n";
        cout << "--------------------------------------------------------\n";
        for (size_t i = 0; i < displayCount; ++i)
        {
            const auto &s = students[i];
            cout << left << setw(15) << s.getName()
                 << setw(15) << s.getSurname()
                 << setw(15) << s.calculateFinalGrade(false)
                 << s.calculateFinalGrade(true) << "\n";
        }
    }
}

string selectOrEnterFile()
{
    cout << "\n------------------------------------\n";
    cout << "        FILE SELECTION MENU          \n";
    cout << "------------------------------------\n";
    cout << "1. Select from standard dataset files\n";
    cout << "2. Enter custom filename manually\n";
    cout << "Enter your choice (1-2): ";

    int mode;
    while (!(cin >> mode) || mode < 1 || mode > 2)
    {
        cout << "Invalid choice! Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (mode == 1)
    {
        cout << "\nAvailable files:\n";
        cout << "1. kursiokai.txt\n";
        cout << "2. students_1000.txt\n";
        cout << "3. students_10000.txt\n";
        cout << "4. students_100000.txt\n";
        cout << "5. students_1000000.txt\n";
        cout << "6. students_10000000.txt\n";
        cout << "Enter file choice (1-6): ";

        int fileChoice;
        while (!(cin >> fileChoice) || fileChoice < 1 || fileChoice > 6)
        {
            cout << "Invalid choice! Enter a number between 1 and 6: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // switch - select statement
        switch (fileChoice)
        {
        case 1:
            return "kursiokai.txt";
        case 2:
            return "students_1000.txt";
        case 3:
            return "students_10000.txt";
        case 4:
            return "students_100000.txt";
        case 5:
            return "students_1000000.txt";
        case 6:
            return "students_10000000.txt";
        }
    }
    else
    {
        cout << "\nEnter filename: ";
        string filename;
        cin >> filename;
        return filename;
    }

    return "kursiokai.txt"; //default value
}

bool readStudentsFromFile(const string &filename, vector<Student> &students)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }

    //read header line
    string headerLine;
    if (!getline(file, headerLine))
    {
        cerr << "Error: File " << filename << " is empty.\n";
        return false;
    }

    // Parse header to count homework columns ("ND1", "ND2", etc.)
    stringstream headerStream(headerLine);
    string word;
    int homeworkCount = 0;

    while (headerStream >> word)
    {
        if (word.rfind("ND", 0) == 0) //rfind - finds maching word for ND
        {
            homeworkCount++;
        }
    }

    if (homeworkCount == 0)
    {
        cerr << "Error: No homework columns (ND) found in file header.\n";
        return false;
    }

    //read students from file using Student class stream reader
    Student tempStudent;
    while (tempStudent.readFromStream(file, homeworkCount))
    //calling function to read the data
    {
        students.push_back(tempStudent);
    }

    file.close();

    if (students.empty())
    {
        cerr << "Error: No valid students read from file.\n";
        return false;
    }

    return true;
}