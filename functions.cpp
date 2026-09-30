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

    // validate number of homework assignments (0-10)
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

    return "kursiokai.txt"; // default value
}

bool readStudentsFromFile(const string &filename, vector<Student> &students)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }

    // read header line
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
        if (word.rfind("ND", 0) == 0) // rfind - finds maching word for ND
        {
            homeworkCount++;
        }
    }

    if (homeworkCount == 0)
    {
        cerr << "Error: No homework columns (ND) found in file header.\n";
        return false;
    }

    // read students from file using Student class stream reader
    Student tempStudent;
    while (tempStudent.readFromStream(file, homeworkCount))
    // calling function to read the data
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

void generateDatasetFile(const string &filename, int studentCount, int homeworkCount)
{
    cout << "\nGenerating file '" << filename << "' with " << studentCount << " students...\n";

    auto start = chrono::high_resolution_clock::now();
    // starts a counting (timing)

    ofstream outFile(filename); // ofstream - write into a file
    if (!outFile.is_open())
    {
        cerr << "Error: Could not create file " << filename << "\n";
        return;
    }

    // write header line matching v0.1 format
    outFile << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
    for (int i = 1; i <= homeworkCount; ++i)
    {
        outFile << setw(10) << ("ND" + to_string(i));
        // to_string convers into a string
    }
    outFile << setw(10) << "Egz." << "\n";

    // fast output buffering for large dataset file writing
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
        ss << setw(10) << getRandomInt(1, 10) << "\n"; // exam score
        // stringstream - when we write a long string

        buffer += ss.str();

        // flush buffer when size exceeds 1 MB
        if (buffer.size() >= 1024 * 1024)
        {
            outFile << buffer;
            buffer.clear();
        }
    }

    // empty remaining buffer
    if (!buffer.empty())
    {
        outFile << buffer;
    }

    outFile.close();

    // auto end - stops counting (timing)
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Successfully generated '" << filename << "' in "
         << fixed << setprecision(4) << elapsed.count() << " seconds.\n";
    // nusako butent 4sk po kablelio tikslu laika
}

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

void separateStudents(const vector<Student> &allStudents,
                      vector<Student> &belowFive,
                      vector<Student> &fiveOrAbove,
                      bool useMedian)
{
    // clearing the vectors
    belowFive.clear();
    fiveOrAbove.clear();

    // accessing by reference
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
}

// write student list and final grades to file
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

    // header
    file << left << setw(20) << "Vardas"
         << setw(20) << "Pavarde"
         << (useMedian ? "Galutinis (Med.)\n" : "Galutinis (Vid.)\n");
    file << "-------------------------------------------------------\n";

    string buffer;
    buffer.reserve(1024 * 1024); // 1mb

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

// Run performance measurement for reading, grouping, and writing
void runPerformanceAnalysisForFile(const string &filename, bool useMedian)
{
    cout << "\n---------------------------------------------------\n";
    cout << "Running performance benchmark on: " << filename << "\n";
    cout << "---------------------------------------------------\n";

    // --- A. Measure Reading Time ---
    vector<Student> students;
    auto startRead = chrono::high_resolution_clock::now();

    // reads student from a file. Inserts values for each student
    if (!readStudentsFromFile(filename, students))
    {
        cerr << "Aborting benchmark for " << filename << " due to read error.\n";
        return;
    }

    auto endRead = chrono::high_resolution_clock::now();
    chrono::duration<double> readTime = endRead - startRead;

    // --- B. Measure Grouping Time ---
    vector<Student> belowFive;
    vector<Student> fiveOrAbove;

    auto startGroup = chrono::high_resolution_clock::now();

    separateStudents(students, belowFive, fiveOrAbove, useMedian);

    auto endGroup = chrono::high_resolution_clock::now();
    chrono::duration<double> groupTime = endGroup - startGroup;

    // --- C. Measure Writing Time ---
    string outBelow = "students_below_5_" + to_string(students.size()) + ".txt";
    string outAbove = "students_5_and_above_" + to_string(students.size()) + ".txt";

    auto startWrite = chrono::high_resolution_clock::now();

    bool writeSuccess1 = writeStudentsToFile(outBelow, belowFive, useMedian);
    bool writeSuccess2 = writeStudentsToFile(outAbove, fiveOrAbove, useMedian);

    auto endWrite = chrono::high_resolution_clock::now();
    chrono::duration<double> writeTime = endWrite - startWrite;

    if (!writeSuccess1 || !writeSuccess2)
    {
        cerr << "Error writing output files during benchmark.\n";
        return;
    }

    double totalSec = readTime.count() + groupTime.count() + writeTime.count();

    cout << fixed << setprecision(4);
    cout << "Dataset: " << students.size() << " students (" << filename << ")\n";
    cout << "Below 5.0 count:    " << belowFive.size() << "\n";
    cout << "5.0 & above count:  " << fiveOrAbove.size() << "\n";
    cout << "---------------------------------------------------\n";
    cout << "Reading time:      " << readTime.count() << " seconds\n";
    cout << "Grouping time:     " << groupTime.count() << " seconds\n";
    cout << "Writing time:      " << writeTime.count() << " seconds\n";
    cout << "Total time:        " << totalSec << " seconds\n";
    cout << "---------------------------------------------------\n";
}

void runAllPerformanceAnalyses()
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
            int count = 1000; // default of starting value
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

        runPerformanceAnalysisForFile(file, useMedian);
    }
}

void showMenu()
{
    cout << "\n====================================\n";
    cout << "    STUDENT GRADE SYSTEM (v2)       \n";
    cout << "====================================\n";
    cout << "1. Add student manually\n";
    cout << "2. Generate random students (in memory)\n";
    cout << "3. Display student results\n";
    cout << "4. Read student data from file\n";
    cout << "5. Generate test dataset files (1K - 10M)\n";
    cout << "6. Run performance benchmark analysis\n";
    cout << "7. Exit\n";
}