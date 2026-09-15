// #include <iostream>
// #include <vector>
// #include <cmath>

#include <bits/stdc++.h>
using namespace std;

float calAverage(vector<int> &homework, int n)
{
    float sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum = sum + homework[i];
    }

    float average = float(sum / n);
    return average;
}

float calMedian(vector<int> &homework)
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

int main()
{
    struct Student
    {
        string firstName;
        string lastName;
        vector<int> homework;
        int exam;
    };

    Student s1; // sukuriam objekta
    cout << "Enter time first name: ";
    cin >> s1.firstName;
    cout << "Enter time last name: ";
    cin >> s1.lastName;
    cout << "Enter exam result: ";
    cin >> s1.exam;
    cout << s1.firstName << " " << s1.lastName << " " << s1.exam;

    int n;
    cout << "Enter the number of homework: ";
    cin >> n;
    cout << "Enter the score of your homeworks: " << endl;

    for (int i = 0; i < n; i++)
    {
        int h;
        cin >> h;
        s1.homework.push_back(h);
    }
    
    float avg = calAverage(s1.homework, n);
    avg = round(avg * 100.0) / 100.0;
    cout << "Average is = " << avg;

    return 0;
}