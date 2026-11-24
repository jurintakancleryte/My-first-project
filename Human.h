#ifndef HUMAN_H
#define HUMAN_h

#include <bits/stdc++.h>
using namespace std;

class Human
{
protected:
    string firstName_;
    string lastName_;

public:
    Human()  //constructor 
    {
        firstName_ = "";
        lastName_ = "";
    }

    Human(string firstName, string lastName)  //perametrised constructor 
    {
        firstName_ = firstName;
        lastName_ = lastName;
    }

    virtual ~Human() = default; //cleaning the storage after the class is completed

    virtual void print(ostream &out) const = 0; //pure virtual function (no objects)

    string getFirstName() const { return firstName_; }  //getters
    string getLastName() const { return lastName_; }

    void setFirstName(const string &firstName)  //setters
    {
        firstName_ = firstName;
    }

    void setLastName(const string &lastName)
    {
        lastName_ = lastName;
    }
};

#endif