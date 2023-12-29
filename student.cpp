#include "student.h"
#include "constants.h"

Student::Student(string line, bool isGenerated) {
    istringstream splitString(line);

    splitString >> name >> surname;

    if (isGenerated) {
        for (int i = 0; i < generatedGradeCount; i++) {
            int grade;

            splitString >> grade;
            addGrade(grade);
        }
    } else {
        int grade;

        while (splitString >> grade) {
            addGrade(grade);
        }

        grades.pop_back();
        examGrade = grade;
    }

    splitString >> finalAvg;
}

Student::Student(string name, string surname) {
    setNames(name, surname);
}

Student::Student(const Student& other) : Student(other.name, other.surname) {
    grades = other.grades;
    examGrade = other.examGrade;
    finalAvg = other.finalAvg;
    finalMdn = other.finalMdn;
}

Student& Student::operator=(const Student& other)
{
    if (this != &other) {
        name = other.name;
        surname = other.surname;
        grades = other.grades;
        examGrade = other.examGrade;
        finalAvg = other.finalAvg;
        finalMdn = other.finalMdn;
    }

    return *this;
}

void Student::setNames(string name, string surname) {
    this->name = name;
    this->surname = surname;
}

void Student::setName(string name) {
    this->name = name;
}

void Student::setSurname(string surname) {
    this->surname = surname;
}

void Student::setExamGrade(int examGrade) {
    this->examGrade = examGrade;
}

void Student::addGrade(int grade) {
    grades.push_back(grade);
}

void Student::generateRandomGrades(int gradeCount) {
    random_device randomDevice;
    mt19937 gen(randomDevice());
    uniform_int_distribution<int> distribution(1, 10);

    for (int i = 0; i < gradeCount; i++) {
        addGrade(distribution(gen));
    }

    setExamGrade(distribution(gen));
}

void Student::calculateAvg() {
    finalAvg = ((accumulate(grades.begin(), grades.end(), finalAvg) / grades.size()) * gradesWeight) + (examGrade * examWeight);
}

void Student::calculateMdn() {
    vector<int> sortedGrades = grades;
    sort(sortedGrades.begin(), sortedGrades.end());
    
    int gradesCount = sortedGrades.size();
    float medianGrade;

    if (gradesCount % 2 == 0) {
        medianGrade = (sortedGrades[(gradesCount / 2) - 1] + sortedGrades[gradesCount / 2]) / 2.0;
    } else {
        medianGrade = sortedGrades[gradesCount / 2];
    }

    finalMdn = (medianGrade * gradesWeight) + (examGrade * examWeight);
}

void Student::printToTerminal(bool printMdn) {
    string allGrades = "";
    for (int grade : grades) {
        allGrades += to_string(grade);
        allGrades += " ";
    }

    cout << setw(maxSurnameLength) << surname << setw(maxNameLength) << name << setw(32) << allGrades << setw(20) << setprecision(2) << fixed << finalAvg;

    if (printMdn) {
        cout << setw(20) << setprecision(2) << fixed << finalMdn << endl;
    } else {
        cout << endl;
    }
}

void Student::printToFile(ofstream& file, bool printMdn) {
    string allGrades = "";
    for (int grade : grades) {
        allGrades += to_string(grade);
        allGrades += " ";
    }

    file << setw(maxSurnameLength) << surname << setw(maxNameLength) << name << setw(32) << allGrades << setw(20) << setprecision(2) << fixed << finalAvg;

    if (printMdn) {
        file << setw(20) << setprecision(2) << fixed << finalMdn << endl;
    } else {
        file << endl;
    }
}

bool compareByName(const Student& student1, const Student& student2) {
    return student1.getName() < student2.getName();
}

bool compareByAvg(const Student& student1, const Student& student2) {
    return student1.getAvg() < student2.getAvg();
}