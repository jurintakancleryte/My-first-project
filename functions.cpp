#include "functions.h"
#include "Student.h"
#include "Calculation.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <limits>
#include <algorithm>
#include <chrono>
#include <bits/stdc++.h>

using namespace std;

// Pseudo-random number generator for uniform distribution
int getRandomInt(int min, int max)
{
    static mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// Manually add a student from console input
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

    // Validate exam grade (1-10)
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

    // Read and validate each homework score
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

    // Construct and push Student object
    students.emplace_back(name, surname, homework, exam);
    cout << "Student " << name << " " << surname << " added successfully!\n";
}

// Generate random students in memory
void generateRandomStudents(vector<Student> &students)
{
    int numberOfStudents;
    cout << "\nHow many random students do you want to generate? (1-1000): ";

    while (!(cin >> numberOfStudents) || numberOfStudents < 1 || numberOfStudents > 1000)
    {
        cout << "Invalid input! Please enter a number between 1 and 1000: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    const vector<string> firstNames = {
        "John", "Peter", "Anna", "Mark", "Laura",
        "Tom", "Emma", "David", "Sarah", "Harsh"};

    const vector<string> lastNames = {
        "Smith", "Brown", "Johnson", "Wilson", "Taylor",
        "Anderson", "Thomas", "Jackson", "White", "Harris"};

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

// Display student results in formatted table
void displayStudentResults(vector<Student> &students)
{
    if (students.empty())
    {
        cout << "\nThere are no students currently loaded.\n";
        return;
    }

    // Sort students alphabetically using external compareByName helper
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
    size_t displayCount = min((size_t)1000, students.size());

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

// Enable the option to either select a preset file or enter a filename manually
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

    return "kursiokai.txt";
}

// Read student records from a file
bool readStudentsFromFile(const string &filename, vector<Student> &students)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }

    // Read header line
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
        if (word.rfind("ND", 0) == 0)
        {
            homeworkCount++;
        }
    }

    if (homeworkCount == 0)
    {
        cerr << "Error: No homework columns (ND) found in file header.\n";
        return false;
    }

    // Read students from file using Student class stream reader
    Student tempStudent;
    while (tempStudent.readFromStream(file, homeworkCount))
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

// Generate a large dataset file of students
void generateDatasetFile(const string &filename, int studentCount, int homeworkCount)
{
    cout << "\nGenerating file '" << filename << "' with " << studentCount << " students...\n";

    auto start = chrono::high_resolution_clock::now();

    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not create file " << filename << "\n";
        return;
    }

    // Write header line matching v0.1 format
    outFile << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
    for (int i = 1; i <= homeworkCount; ++i)
    {
        outFile << setw(10) << ("ND" + to_string(i));
    }
    outFile << setw(10) << "Egz." << "\n";

    // Fast output buffering for large dataset file writing
    string buffer;
    buffer.reserve(1024 * 1024); // 1 MB buffer chunk

    for (int i = 1; i <= studentCount; ++i)
    {
        stringstream ss;
        ss << left << setw(20) << ("Vardas" + to_string(i))
           << setw(20) << ("Pavarde" + to_string(i));

        for (int j = 0; j < homeworkCount; ++j)
        {
            ss << setw(10) << getRandomInt(1, 10);
        }
        ss << setw(10) << getRandomInt(1, 10) << "\n";

        buffer += ss.str();

        // Flush buffer when size exceeds 1 MB
        if (buffer.size() >= 1024 * 1024)
        {
            outFile << buffer;
            buffer.clear();
        }
    }

    // Flush remaining buffer
    if (!buffer.empty())
    {
        outFile << buffer;
    }

    outFile.close();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Successfully generated '" << filename << "' in "
         << fixed << setprecision(4) << elapsed.count() << " seconds.\n";
}

// Generate all dataset files (1K, 10K, 100K, 1M, 10M)
void generateAllDatasets()
{
    cout << "\n====================================\n";
    cout << "      DATASET GENERATION MENU       \n";
    cout << "====================================\n";
    cout << "1. Generate 1,000 students (students_1000.txt)\n";
    cout << "2. Generate 10,000 students (students_10000.txt)\n";
    cout << "3. Generate 100,000 students (students_100000.txt)\n";
    cout << "4. Generate 1,000,000 students (students_1000000.txt)\n";
    cout << "5. Generate 10,000,000 students (students_10000000.txt)\n";
    cout << "6. Generate ALL datasets (1K - 10M)\n";
    cout << "7. Return to main menu\n";
    cout << "Enter your choice (1-7): ";

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 7)
    {
        cout << "Invalid choice! Please enter a number between 1 and 7: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (choice)
    {
    case 1:
        generateDatasetFile("students_1000.txt", 1000);
        break;
    case 2:
        generateDatasetFile("students_10000.txt", 10000);
        break;
    case 3:
        generateDatasetFile("students_100000.txt", 100000);
        break;
    case 4:
        generateDatasetFile("students_1000000.txt", 1000000);
        break;
    case 5:
        generateDatasetFile("students_10000000.txt", 10000000);
        break;
    case 6:
        generateDatasetFile("students_1000.txt", 1000);
        generateDatasetFile("students_10000.txt", 10000);
        generateDatasetFile("students_100000.txt", 100000);
        generateDatasetFile("students_1000000.txt", 1000000);
        generateDatasetFile("students_10000000.txt", 10000000);
        break;
    case 7:
        break;
    }
}

void separateStudentsStrategy1(const vector<Student> &allStudents,
                               vector<Student> &belowFive,
                               vector<Student> &fiveOrAbove,
                               bool useMedian = false)
{

    belowFive.clear();
    fiveOrAbove.clear();

    belowFive.reserve(allStudents.size() / 2);
    fiveOrAbove.reserve(allStudents.size() / 2);

    for (const auto &student : allStudents)
    {
        double finalGrade = student.calculateFinalGrade(useMedian);
        if (finalGrade < 5.0)
        {
            belowFive.push_back(student);
        }
        else
        {
            fiveOrAbove.push_back(student);
        }
    }

    sort(belowFive.begin(), belowFive.end(),
         [useMedian](const Student &a, const Student &b)
         {
             return a.calculateFinalGrade(useMedian) < b.calculateFinalGrade(useMedian);
         });

    sort(fiveOrAbove.begin(), fiveOrAbove.end(),
         [useMedian](const Student &a, const Student &b)
         {
             return a.calculateFinalGrade(useMedian) < b.calculateFinalGrade(useMedian);
         });
}

// Separate students into two groups based on final grade threshold (5.0):
// belowFive: Final < 5.0
// fiveOrAbove: Final >= 5.0
void separateStudents(const vector<Student> &allStudents,
                      vector<Student> &belowFive,
                      vector<Student> &fiveOrAbove,
                      bool useMedian)
{
    separateStudentsStrategy1(allStudents, belowFive, fiveOrAbove, useMedian);
}

// Write student list and final grades to file
bool writeStudentsToFile(const string &filename,
                         const vector<Student> &students,
                         bool useMedian)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not create output file " << filename << "\n";
        return false;
    }

    // Header
    file << left << setw(20) << "Vardas"
         << setw(20) << "Pavarde"
         << (useMedian ? "Galutinis (Med.)\n" : "Galutinis (Vid.)\n");
    file << "-------------------------------------------------------\n";

    string buffer;
    buffer.reserve(1024 * 1024);

    for (const auto &s : students)
    {
        stringstream ss;
        ss << left << setw(20) << s.getName()
           << setw(20) << s.getSurname()
           << fixed << setprecision(2) << s.calculateFinalGrade(useMedian) << "\n";

        buffer += ss.str();

        if (buffer.size() >= 1024 * 1024)
        {
            file << buffer;
            buffer.clear();
        }
    }

    if (!buffer.empty())
    {
        file << buffer;
    }

    file.close();
    return true;
}

// Read student records from a file into a list of Student objects
bool readStudentsFromFileList(const string &filename, list<Student> &students)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }

    string headerLine;
    if (!getline(file, headerLine))
    {
        cerr << "Error: File " << filename << " is empty.\n";
        return false;
    }

    stringstream headerStream(headerLine);
    string word;
    int homeworkCount = 0;

    while (headerStream >> word)
    {
        if (word.rfind("ND", 0) == 0)
        {
            homeworkCount++;
        }
    }

    if (homeworkCount == 0)
    {
        cerr << "Error: No homework columns (ND) found in file header.\n";
        return false;
    }

    Student tempStudent;
    while (tempStudent.readFromStream(file, homeworkCount))
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

// Display student results for a list container formatted in a console table
void displayStudentResultsList(list<Student> &students)
{
    if (students.empty())
    {
        cout << "\nThere are no students currently loaded.\n";
        return;
    }

    // Sort list using list member function .sort()
    students.sort(compareByName);

    cout << "\n========== Display Results (std::list) ==========\n";
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
    size_t displayCount = min((size_t)1000, students.size());

    auto it = students.begin();
    if (choice == 1)
    {
        cout << left << setw(15) << "First Name"
             << setw(15) << "Last Name"
             << "Final (Avg.)\n";
        cout << "-------------------------------------------\n";
        for (size_t i = 0; i < displayCount && it != students.end(); ++i, ++it)
        {
            cout << left << setw(15) << it->getName()
                 << setw(15) << it->getSurname()
                 << it->calculateFinalGrade(false) << "\n";
        }
    }
    else if (choice == 2)
    {
        cout << left << setw(15) << "First Name"
             << setw(15) << "Last Name"
             << "Final (Med.)\n";
        cout << "-------------------------------------------\n";
        for (size_t i = 0; i < displayCount && it != students.end(); ++i, ++it)
        {
            cout << left << setw(15) << it->getName()
                 << setw(15) << it->getSurname()
                 << it->calculateFinalGrade(true) << "\n";
        }
    }
    else if (choice == 3)
    {
        cout << left << setw(15) << "First Name"
             << setw(15) << "Last Name"
             << setw(15) << "Final (Avg.)"
             << "Final (Med.)\n";
        cout << "--------------------------------------------------------\n";
        for (size_t i = 0; i < displayCount && it != students.end(); ++i, ++it)
        {
            cout << left << setw(15) << it->getName()
                 << setw(15) << it->getSurname()
                 << setw(15) << it->calculateFinalGrade(false)
                 << it->calculateFinalGrade(true) << "\n";
        }
    }
}

void separateStudentsList(const list<Student> &allStudents,
                          list<Student> &belowFive,
                          list<Student> &fiveOrAbove,
                          bool useMedian = false)
{
    belowFive.clear();
    fiveOrAbove.clear();

    for (const auto &student : allStudents)
    {
        double finalGrade = student.calculateFinalGrade(useMedian);
        if (finalGrade < 5.0)
        {
            belowFive.push_back(student);
        }
        else
        {
            fiveOrAbove.push_back(student);
        }
    }

    // all srudents.clear(); enter below5.scirnk_to_fit; ir tas pats su five_or_above

    belowFive.sort([useMedian](const Student &a, const Student &b)
                   { return a.calculateFinalGrade(useMedian) < b.calculateFinalGrade(useMedian); });

    // Sort the 5-and-above group by final grade in ascending order
    fiveOrAbove.sort([useMedian](const Student &a, const Student &b)
                     { return a.calculateFinalGrade(useMedian) < b.calculateFinalGrade(useMedian); });
}

void separateStudentsStrategy2(vector<Student> &allStudents,
                               vector<Student> &belowFive,
                               bool useMedian = false)
{
    belowFive.clear();

    belowFive.reserve(allStudents.size() / 2); // good for time complexity

    auto it = allStudents.begin();
    while (it != allStudents.end())
    {
        if (it->calculateFinalGrade(useMedian) < 5.0)
        {
            belowFive.push_back(std::move(*it));
            // function that is use of move
            it = allStudents.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void separateStudentsStrategy3(vector<Student> &allStudents,
                               vector<Student> &belowFive,
                               bool useMedian = false)
{
    belowFive.clear();

    auto pointerToPoorStudents = std::stable_partition(allStudents.begin(), allStudents.end(),
                                                       [useMedian](const Student &s)
                                                       {
                                                           return s.calculateFinalGrade(useMedian) >= 5.0;
                                                       });
    belowFive.assign(make_move_iterator(pointerToPoorStudents),
                     make_move_iterator(allStudents.end()));
    allStudents.erase(pointerToPoorStudents, allStudents.end());
}

// Separate list of students into belowFive and fiveOrAbove
void separateStudentsList(const list<Student> &allStudents,
                          list<Student> &belowFive,
                          list<Student> &fiveOrAbove,
                          bool useMedian)
{
    separateStudentsListStrategy1(allStudents, belowFive, fiveOrAbove, useMedian);
}

void separateStudentsListStrategy2(list<Student> &allStudents,
                                   list<Student> &belowFive,
                                   bool useMedian = false)
{
    belowFive.clear();

    auto it = allStudents.begin();
    while (it != allStudents.end())
    {
        if (it->calculateFinalGrade(useMedian) < 5.0)
        {
            belowFive.push_back(std::move(*it));
            // function that is use of move
            it = allStudents.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void separateStudentsListStrategy3(list<Student> &allStudents,
                                   list<Student> &belowFive,
                                   bool useMedian = false)
{
    belowFive.clear();

    auto pointerToPoorStudents = std::stable_partition(allStudents.begin(), allStudents.end(),
                                                       [useMedian](const Student &s)
                                                       {
                                                           return s.calculateFinalGrade(useMedian) >= 5.0;
                                                       });
    belowFive.splice(belowFive.begin(), allStudents, pointerToPoorStudents, allStudents.end());
    // directly moving data to the list, not copying it
}

// Write list of students to output file
bool writeStudentsToFileList(const string &filename,
                             const list<Student> &students,
                             bool useMedian)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not create output file " << filename << "\n";
        return false;
    }

    file << left << setw(20) << "Vardas"
         << setw(20) << "Pavarde"
         << (useMedian ? "Galutinis (Med.)\n" : "Galutinis (Vid.)\n");
    file << "-------------------------------------------------------\n";

    string buffer;
    buffer.reserve(1024 * 1024);

    for (const auto &s : students)
    {
        stringstream ss;
        ss << left << setw(20) << s.getName()
           << setw(20) << s.getSurname()
           << fixed << setprecision(2) << s.calculateFinalGrade(useMedian) << "\n";

        buffer += ss.str();

        if (buffer.size() >= 1024 * 1024)
        {
            file << buffer;
            buffer.clear();
        }
    }

    if (!buffer.empty())
    {
        file << buffer;
    }

    file.flush();
    file.close();
    return true;
}

// Demonstration of memory addresses (&student) during manual entry for vector vs list
void demonstrateMemoryAddresses()
{
    cout << "\n===========================================================\n";
    cout << "     MANUAL ENTRY MEMORY ADDRESS DEMONSTRATION (&student)   \n";
    cout << "===========================================================\n";
    cout << "This test demonstrates how student objects are stored in memory:\n";
    cout << "- std::vector stores elements in contiguous memory. When capacity is exceeded,\n";
    cout << "  it reallocates memory and moves existing objects to new addresses.\n";
    cout << "- std::list stores elements in separate nodes on the heap.\n";
    cout << "  Inserting new elements never relocates existing list nodes.\n\n";

    vector<Student> studentVector;
    list<Student> studentList;

    char choice = 'y';
    int studentIndex = 1;

    while (choice == 'y' || choice == 'Y')
    {
        string name = "Student" + to_string(studentIndex);
        string surname = "Test" + to_string(studentIndex);
        vector<int> homework = {8, 9, 7, 10, 8};
        double exam = 9.0;

        Student s(name, surname, homework, exam);

        studentVector.push_back(s);
        studentList.push_back(s);

        cout << "\n--- Current Memory Addresses after adding Student #" << studentIndex << " ---\n";
        cout << "std::vector capacity: " << studentVector.capacity()
             << " | size: " << studentVector.size() << "\n";

        // printing memory of address of vector
        cout << "\nstd::vector student object memory addresses:\n";
        for (size_t i = 0; i < studentVector.size(); ++i)
        {
            cout << "  Vector Element #" << (i + 1) << " Address: "
                 << static_cast<const void *>(&studentVector[i]) << "\n";
            // data type that convert the adress to pointer type so that cout that
        }

        // printing memory of address of vector
        cout << "\nstd::list student object memory addresses:\n";
        size_t listIdx = 1; // for cout
        for (const auto &studentNode : studentList)
        {
            cout << "  List Element #" << listIdx++ << " Address:   "
                 << static_cast<const void *>(&studentNode) << "\n";
        }

        cout << "\nDo you want to add another student to observe address changes? (y/n): ";
        cin >> choice;
        studentIndex++;
    }

    cout << "\nDemonstration complete!\n";
}

// Benchmark comparison for a single dataset file across std::vector and std::list (5 repetitions)
void runBenchmarkForFile(const string &filename, bool useMedian, int repetitions)
{
    cout << "\n===========================================================\n";
    cout << "Benchmarking File: " << filename << " (" << repetitions << " repetitions)\n";
    cout << "===========================================================\n";

    vector<Student> vectorStudents;
    list<Student> listStudents;

    if (!readStudentsFromFile(filename, vectorStudents))
    {
        cerr << "Failed to read file " << filename << " into std::vector.\n";
        return;
    }
    if (!readStudentsFromFileList(filename, listStudents))
    {
        cerr << "Failed to read file " << filename << " into std::list.\n";
        return;
    }

    size_t studentCount = vectorStudents.size();
    string sizeStr = to_string(studentCount);
                //if integer it changes the data stype of a string

    double totalV1_sep = 0.0, totalV2_sep = 0.0, totalV3_sep = 0.0;
    double totalL1_sep = 0.0, totalL2_sep = 0.0, totalL3_sep = 0.0;
    double totalVecWrite = 0.0, totalListWrite = 0.0;

    // Vector Strategy 2 is O(N^2) due to shifting elements on every erase.
    // For 1M or 10M records, it would take multiple hours, so it is skipped for N > 100,000.
    bool skipV2 = (studentCount > 100000);

    string vecOutBelow = "students_below_5_vector_" + sizeStr + ".txt";
    string vecOutAbove = "students_5_and_above_vector_" + sizeStr + ".txt";
    string listOutBelow = "students_below_5_list_" + sizeStr + ".txt";
    string listOutAbove = "students_5_and_above_list_" + sizeStr + ".txt";

    for (int r = 1; r <= repetitions; ++r)
    {
        cout << "  Run #" << r << " of " << repetitions << "..." << endl;

        // 1. Vector Strategy 1 (2 new containers)
        vector<Student> v1_poor, v1_good;
        auto startV1 = chrono::high_resolution_clock::now();
        separateStudentsStrategy1(vectorStudents, v1_poor, v1_good, useMedian);
        auto endV1 = chrono::high_resolution_clock::now();
        totalV1_sep += chrono::duration<double>(endV1 - startV1).count();

        // 2. Vector Strategy 2 (Move poor & erase from original)
        if (!skipV2)
        {
            vector<Student> v2_copy = vectorStudents;
            vector<Student> v2_poor;
            auto startV2 = chrono::high_resolution_clock::now();
            separateStudentsStrategy2(v2_copy, v2_poor, useMedian);
            auto endV2 = chrono::high_resolution_clock::now();
            totalV2_sep += chrono::duration<double>(endV2 - startV2).count();
        }

        // 3. Vector Strategy 3 (Optimized with std::stable_partition)
        {
            vector<Student> v3_copy = vectorStudents;
            vector<Student> v3_poor;
            auto startV3 = chrono::high_resolution_clock::now();
            separateStudentsStrategy3(v3_copy, v3_poor, useMedian);
            auto endV3 = chrono::high_resolution_clock::now();
            totalV3_sep += chrono::duration<double>(endV3 - startV3).count();
        }

        // Vector File Writing
        auto startVWrite = chrono::high_resolution_clock::now();
        writeStudentsToFile(vecOutBelow, v1_poor, useMedian);
        writeStudentsToFile(vecOutAbove, v1_good, useMedian);
        auto endVWrite = chrono::high_resolution_clock::now();
        totalVecWrite += chrono::duration<double>(endVWrite - startVWrite).count();

        // 4. List Strategy 1 (2 new containers)
        list<Student> l1_poor, l1_good;
        auto startL1 = chrono::high_resolution_clock::now();
        separateStudentsListStrategy1(listStudents, l1_poor, l1_good, useMedian);
        auto endL1 = chrono::high_resolution_clock::now();
        totalL1_sep += chrono::duration<double>(endL1 - startL1).count();

        // 5. List Strategy 2 (Move poor & erase from original)
        {
            list<Student> l2_copy = listStudents;
            list<Student> l2_poor;
            auto startL2 = chrono::high_resolution_clock::now();
            separateStudentsListStrategy2(l2_copy, l2_poor, useMedian);
            auto endL2 = chrono::high_resolution_clock::now();
            totalL2_sep += chrono::duration<double>(endL2 - startL2).count();
        }

        // 6. List Strategy 3 (Optimized with std::stable_partition + splice)
        {
            list<Student> l3_copy = listStudents;
            list<Student> l3_poor;
            auto startL3 = chrono::high_resolution_clock::now();
            separateStudentsListStrategy3(l3_copy, l3_poor, useMedian);
            auto endL3 = chrono::high_resolution_clock::now();
            totalL3_sep += chrono::duration<double>(endL3 - startL3).count();
        }

        // List File Writing
        auto startLWrite = chrono::high_resolution_clock::now();
        writeStudentsToFileList(listOutBelow, l1_poor, useMedian);
        writeStudentsToFileList(listOutAbove, l1_good, useMedian);
        auto endLWrite = chrono::high_resolution_clock::now();
        totalListWrite += chrono::duration<double>(endLWrite - startLWrite).count();
    }

    double avgV1_sep = totalV1_sep / repetitions;
    double avgV2_sep = totalV2_sep / repetitions;
    double avgV3_sep = totalV3_sep / repetitions;
    double avgVecWrite = totalVecWrite / repetitions;

    double avgL1_sep = totalL1_sep / repetitions;
    double avgL2_sep = totalL2_sep / repetitions;
    double avgL3_sep = totalL3_sep / repetitions;
    double avgListWrite = totalListWrite / repetitions;

    // Print Benchmark Summary Table
    cout << fixed << setprecision(5);
    cout << "\n-------------------------------------------------------------------------------------------------\n";
    cout << "STRATEGY BENCHMARK SUMMARY FOR: " << studentCount << " students (" << repetitions << "-run averages)\n";
    cout << "-------------------------------------------------------------------------------------------------\n";
    cout << left << setw(44) << "Strategy & Container"
         << setw(20) << "Avg Separation (s)"
         << setw(20) << "Avg Writing (s)"
         << "Total Time (s)\n";
    cout << "-------------------------------------------------------------------------------------------------\n";

    cout << left << setw(44) << "vector: Strategy 1 (2 new containers)"
         << setw(20) << avgV1_sep
         << setw(20) << avgVecWrite
         << (avgV1_sep + avgVecWrite) << "\n";

    if (skipV2)
    {
        cout << left << setw(44) << "vector: Strategy 2 (erase from original)"
             << setw(20) << "SKIPPED (O(N^2))"
             << setw(20) << "SKIPPED"
             << "SKIPPED\n";
    }
    else
    {
        cout << left << setw(44) << "vector: Strategy 2 (erase from original)"
             << setw(20) << avgV2_sep
             << setw(20) << avgVecWrite
             << (avgV2_sep + avgVecWrite) << "\n";
    }

    cout << left << setw(44) << "vector: Strategy 3 (std::stable_partition)"
         << setw(20) << avgV3_sep
         << setw(20) << avgVecWrite
         << (avgV3_sep + avgVecWrite) << "\n";

    cout << left << setw(44) << "list:   Strategy 1 (2 new containers)"
         << setw(20) << avgL1_sep
         << setw(20) << avgListWrite
         << (avgL1_sep + avgListWrite) << "\n";

    cout << left << setw(44) << "list:   Strategy 2 (erase from original)"
         << setw(20) << avgL2_sep
         << setw(20) << avgListWrite
         << (avgL2_sep + avgListWrite) << "\n";

    cout << left << setw(44) << "list:   Strategy 3 (std::stable_partition + splice)"
         << setw(20) << avgL3_sep
         << setw(20) << avgListWrite
         << (avgL3_sep + avgListWrite) << "\n";

    cout << "-------------------------------------------------------------------------------------------------\n";
}

// Run container benchmark comparisons across all 5 dataset files
void runAllContainerBenchmarks()
{
    const vector<string> files = {
        "students_1000.txt",
        "students_10000.txt",
        "students_100000.txt",
        "students_1000000.txt",
        "students_10000000.txt"};

    cout << "\nChoose grade calculation method for benchmark:\n";
    cout << "1. Average\n";
    cout << "2. Median\n";
    cout << "Enter choice (1-2): ";

    int methodChoice;
    while (!(cin >> methodChoice) || methodChoice < 1 || methodChoice > 2)
    {
        cout << "Invalid choice! Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool useMedian = (methodChoice == 2);

    for (const auto &file : files)
    {
        ifstream check(file);
        if (!check.is_open())
        {
            cout << "\nDataset file '" << file << "' not found. Generating it now...\n";
            int count = 1000;
            if (file == "students_1000.txt")
                count = 1000;
            else if (file == "students_10000.txt")
                count = 10000;
            else if (file == "students_100000.txt")
                count = 100000;
            else if (file == "students_1000000.txt")
                count = 1000000;
            else if (file == "students_10000000.txt")
                count = 10000000;

            generateDatasetFile(file, count);
        }
        else
        {
            check.close();
        }

        runBenchmarkForFile(file, useMedian, 5);
    }
}

// Main interactive menu interface
void showMenu()
{
    cout << "\n====================================\n";
    cout << "    STUDENT GRADE SYSTEM (v0.3)     \n";
    cout << "====================================\n";
    cout << "1. Add student manually\n";
    cout << "2. Generate random students (in memory)\n";
    cout << "3. Display student results\n";
    cout << "4. Read student data from file\n";
    cout << "5. Generate test dataset files (1K - 10M)\n";
    cout << "6. Run std::vector vs std::list performance benchmark (5 runs)\n";
    cout << "7. Memory address demonstration (&student)\n";
    cout << "8. Exit\n";
}
