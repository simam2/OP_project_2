#pragma once

#include <string>
#include <vector>

using namespace std;

class Student
{
private:
    string name;
    string surname;
    vector<int> grades;
    int examGrade;
    float finalAvg;
    float finalMdn;

public:
    Student(){};
    ~Student(){};

    Student(string, bool);
    Student(string, string);
    
    Student(const Student &other);
    Student &operator=(const Student &other);

    void setNames(string, string);
    void setExamGrade(int);
    void addGrade(int);

    void generateRandomGrades(int);
    void calculateAvg();
    void calculateMdn();

    inline string getName() const { return name; }
    inline string getSurname() const { return surname; }
    inline vector<int> getGrades() const { return grades; }
    inline int getExamGrade() const { return examGrade; }
    inline float getAvg() const { return finalAvg; }
    inline float getMdn() const { return finalMdn; }
};

bool compareByName(const Student&, const Student&);
bool compareByAvg(const Student&, const Student&);