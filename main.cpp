// #include <iostream>
// #include <vector>
// #include <cmath>

#include <bits/stdc++.h>
using namespace std;

struct Student
{
string firstName;
string lastName;
vector<int> homework;
int exam;
};

float calAverage(vector<int> homework)
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

float calMedian(vector<int> homework)
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

float calFinalScoreuMedian(const Student &s)  //const - constant: doesnt let the data/ values to be changed
{
float median = calMedian(s.homework);
float score = 0.4 * median + 0.6 * s.exam;
return score;
}

float calFinalScoreAverage(const Student &s)
{
float average = calAverage(s.homework);
float score = 0.4 * average + 0.6 * s.exam;
return score;
}

void addStudentManually(vector<Student>&students)  //& - push data inside list 
                                //pass by values and pass by referencwes
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

students.push_back(s1);  //pusch_back - insert values into the list
return;  //onlt return (no 0) because void function

}

void displayStudentResults(vector<Student>students){

if(students.size()==0){  //check for empty students vector
    cout<<"There are no students currently.\n";
    return;
}

cout << "\n========== DISPLAY RESULTS ==========\n";

cout << "Choose calculation method:\n";
cout << "1. Average\n";
cout << "2. Median\n";
cout << "3. Both\n";
cout << "Enter your choice: ";
int choice;
cin>>choice;
if(choice<1 || choice>3){
    cout<<"Invalid choice, Enter your choice again: \n";
    cin>>choice;
}
if(choice==1){
    cout<<"First Name   Last Name    Average \n";
    for(auto s: students){
        cout<<s.firstName<<"    "<<s.lastName<<"   "<<calAverage(s.homework)<<endl;
    }
}
else if(choice==2){
    cout<<"First Name   Last Name    Median \n";
    for(auto s: students){
        cout<<s.firstName<<"    "<<s.lastName<<"    "<<calMedian(s.homework)<<endl;
    }
}
else if(choice==3){
    cout<<"First Name   Last Name    Average    Median \n";
    for(auto s: students){  //auto takes the data type (int, string and etc.)
        cout<<s.firstName<<"    "<<s.lastName<<"    "<<calAverage(s.homework)<<"    "<<calMedian(s.homework)<<endl;
    }
}
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
vector<Student>students;

cout << "Enter your choice:\n";
int choice;
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
}while(choice!=4);

return 0;