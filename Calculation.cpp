#include <bits/stdc++.h>
#include "Calculation.h"
#include "Student.h"

using namespace std;

double calAverage(const vector<int> &homework)
{
    if (homework.empty())
        return 0.0f; // Prevent division by zero

    double sum = 0.0f;
    for (int mark : homework)
    {
        sum += mark;
    }
    return sum / homework.size();
}

double calMedian(vector<int> homework)
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

bool compareByName(const Student &a, const Student &b)
{
    if (a.getName() == b.getName())
    {
        return a.getSurname() < b.getSurname();
    }
    return a.getName() < b.getName();
}
