#pragma once

#include <string>
#include <vector>

using namespace std;

class Person
{
protected:
    string name;
    string surname;

public:
    virtual ~Person(){};

    virtual void setNames(string, string) = 0;
    virtual void setName(string) = 0;
    virtual void setSurname(string) = 0;

    inline string getName() const { return name; }
    inline string getSurname() const { return surname; }
};

class Student : public Person
{
private:
    vector<int> grades;
    int examGrade;
    float finalAvg;
    float finalMdn;

public:
    Student(){};
    ~Student()
    {
        cout << "Deconstructed " << getName() << endl;
    };

    Student(string, bool);
    Student(string, string);

    Student(const Student &other);
    Student &operator=(const Student &other);

    void setNames(string, string);
    void setName(string);
    void setSurname(string);
    void setExamGrade(int);
    void addGrade(int);

    void generateRandomGrades(int);
    void calculateAvg();
    void calculateMdn();

    void printToTerminal(bool);
    void printToFile(ofstream &, bool);

    inline vector<int> getGrades() const { return grades; }
    inline int getExamGrade() const { return examGrade; }
    inline float getAvg() const { return finalAvg; }
    inline float getMdn() const { return finalMdn; }
};

bool compareByName(const Student &, const Student &);
bool compareByAvg(const Student &, const Student &);