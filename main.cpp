#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <random>
#include <fstream>
#include <sstream>

#include "constants.h"
#include "functions.cpp"

using namespace std;


int main() {
    cout << endl << "If you wish to stop adding students, simply press ENTER without typing anything in when asked for a student's name." << endl << "The same rule applies to grade entering - if you entered all grades, simply press ENTER without typing anything in." << endl << endl;

    bool inputByHand = chooseInputFile();

    vector<Student> students;

    if (inputByHand) {
        int gradeCount = chooseGradeInputGen();

        while (true) {
            Student student = Student();

            student = inputNameSurname(student, students.size());

            if (student.name.empty()) {
                break;
            }

            if (gradeCount > -1) {
                student = generateGrades(student, gradeCount);
            } else {
                student = inputGrades(student);
            }

            student = calculateAvg(student);
            student = calculateMdn(student);

            students.push_back(student);
            cout << endl;
        }
    } else {
        string line;
        ifstream file(inputFolderName + "/" + inputFileName);

        getline(file, line);

        while (getline(file, line)) {
            Student student = Student();

            istringstream splitString(line);

            splitString >> student.name >> student.surname;

            int grade;

            while (splitString >> grade) {
                student.grades.push_back(grade);
            }

            student.grades.pop_back();
            student.examGrade = grade;

            student = calculateAvg(student);
            student = calculateMdn(student);

            students.push_back(student);
        }
Y
        file.close();
    }

    cout << endl << "There are " << students.size() << " students." << endl << endl;

    if (students.size() > 0) {
        sort(students.begin(), students.end(), &compareStudents);

        if (inputByHand) {
            cout << left;
            cout << setw(maxSurnameLength) << "Surname" << setw(maxNameLength) << "Name" << setw(20) << "Final Grade (avg)" << setw(20) << "Final Grade (mdn)" <<endl;
            cout << string(maxSurnameLength + maxNameLength + 40, '-') << endl;
            
            for (Student student : students) {
                cout << setw(maxSurnameLength) << student.surname << setw(maxNameLength) << student.name << setw(20) << setprecision(2) << fixed << student.finalAvg << setw(20) << setprecision(2) << fixed << student.finalMdn << endl;
            }
        } else {
            ofstream file(outputFolderName + "/" + inputFileName);

            file << left;
            file << setw(maxSurnameLength) << "Surname" << setw(maxNameLength) << "Name" << setw(20) << "Final Grade (avg)" << setw(20) << "Final Grade (mdn)" << endl;
            file << string(maxSurnameLength + maxNameLength + 40, '-') << endl;
            
            for (Student student : students) {
                file << setw(maxSurnameLength) << student.surname << setw(maxNameLength) << student.name << setw(20) << setprecision(2) << fixed << student.finalAvg << setw(20) << setprecision(2) << fixed << student.finalMdn << endl;
            }

            file.close();
        }
    }
    
}