#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "Student.h"
#include "functions.h"

using namespace std;

int main()
{
    vector<Student> students;
    int choice = 0;

    do
    {
        showMenu();
        cout << "Enter your choice (1-7): ";

        // Validate menu choice input
        while (!(cin >> choice) || choice < 1 || choice > 7)
        {
            cout << "Invalid choice! Please enter a number from 1 to 7: ";
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
        {
            students.clear();
            string filename = selectOrEnterFile();

            if (readStudentsFromFile(filename, students))
            {
                cout << students.size() << " students loaded successfully from " << filename << ".\n";
            }
            break;
        }
        case 5:
            generateAllDatasets();
            break;
        case 6:
            runAllPerformanceAnalyses();
            break;
        case 7:
            cout << "Exiting Student Grade System. Goodbye!\n";
            break;
        }

    } while (choice != 7);

    return 0;
}