#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <random>
#include <fstream>
#include <sstream>

#include "student.h"
#include "constants.h"

using namespace std;


Student inputNameSurname(Student &student, int i) {
    int studentNumber = i + 1;

    cin.ignore();

    while (student.name.length() <= 0 || student.name.length() > maxNameLength) {
        cout << "Please enter the name of student number " << studentNumber << ": ";
        getline(cin, student.name);

        if (student.name.empty()) {
            break;
        }
    }

    if (student.name.empty()) {
        return student;
    }

    while (student.surname.length() <= 0 || student.surname.length() > maxSurnameLength) {
        cout << "Please enter the surname of student number " << studentNumber << " (name - " << student.name << "): ";
        cin >> student.surname;
    }

    return student;
}


Student inputGrades(Student &student) {
    int count = 1;
    string input;

    cin.ignore();

    while (true) {
        cout << "Please enter grade " << count << " for student " << student.name << " " << student.surname << ": ";
        getline(cin, input);

        if (input.empty()) {
            break;
        }

        try {
            if (stoi(input) >= 1 && stoi(input) <= 10) {
                count++;
                student.grades.push_back(stoi(input));
            } else {
                cout << "You must enter a number between 1 and 10." << endl;
            }
        } catch (invalid_argument&) {
            cout << "You must enter a number between 1 and 10." << endl;
        }
    }

    while (student.examGrade < 1 || student.examGrade > 10) {
        cout << "Please enter the exam grade for student " << student.name << " " << student.surname << ": ";
        
        string input;
        cin >> input;

        try {
            if (stoi(input) >= 1 && stoi(input) <= 10) {
                student.examGrade = stoi(input);
            } else {
                student.examGrade = -1;
                cout << "You must enter a number between 1 and 10." << endl;
            }
        } catch (invalid_argument&) {
            cout << "You must enter a number between 1 and 10." << endl;
        }
    }

    return student;
}

Student generateGrades(Student &student, int gradeCount) {
    random_device randomDevice;
    mt19937 gen(randomDevice());
    uniform_int_distribution<int> distribution(1, 10);

    for (int i = 0; i < gradeCount; i++) {
        student.grades.push_back(distribution(gen));
    }

    student.examGrade = distribution(gen);

    return student;
}

char chooseAction() {
    int userChoice = 0;

    while (userChoice != 1 && userChoice != 2) {
        cout << "Please choose what you'd like the program to do - input '1' if you would like to input/process data, input '2' if you want random input files to be generated: ";
        cin >> userChoice;
        cout << endl;
    }

    return userChoice;
}

int chooseStudentCount() {
    int studentCount = 0;

    while (studentCount < 1) {
        cout << "Please choose how many students should be generated: ";
        cin >> studentCount;
        cout << endl;
    }

    return studentCount;
}

bool chooseInputFile() {
    char userChoice;

    while (toupper(userChoice) != 'Y' && toupper(userChoice) != 'N') {
        cout << "Please choose whether you would like to input students by hand - input 'Y' for manual input or 'N' for file read: ";
        cin >> userChoice;
        cout << endl;
    }

    return toupper(userChoice) == 'Y';
}

int chooseGradeInputGen() {
    char userChoice;
    int gradeCount = 0;
    
    while (toupper(userChoice) != 'Y' && toupper(userChoice) != 'N') {
        cout << "Will you input the grades of the students yourself? Type 'Y' if yes or 'N' if you want them to be randomly generated: ";
        cin >> userChoice;
        cout << endl;
    }

    if (toupper(userChoice) == 'Y') {
        return -1;
    }

    while (gradeCount < 1) {
        cout << "You have chosen random grade generation." << endl << "Please specify how many grades should be generated for each student: ";
        cin >> gradeCount;
        cout << endl;
    }

    return gradeCount;
}

bool compareStudentNames(Student &left, Student &right) {
    return left.name < right.name;
}

bool compareStudentFinalAvg(Student &left, Student &right) {
    return left.finalAvg < right.finalAvg;
}

Student calculateAvg(Student &student) {
    student.finalAvg = ((accumulate(student.grades.begin(), student.grades.end(), student.finalAvg) / student.grades.size()) * gradesWeight) + (student.examGrade * examWeight);
    return student;
}

Student calculateMdn(Student &student) {
    vector<int> sortedGrades = student.grades;
    sort(sortedGrades.begin(), sortedGrades.end());
    
    int gradesCount = sortedGrades.size();
    float medianGrade;

    if (gradesCount % 2 == 0) {
        medianGrade = (sortedGrades[(gradesCount / 2) - 1] + sortedGrades[gradesCount / 2]) / 2.0;
    } else {
        medianGrade = sortedGrades[gradesCount / 2];
    }

    student.finalMdn = (medianGrade * gradesWeight) + (student.examGrade * examWeight);

    return student;
}

void outputResults(vector<Student> &students, bool outputToTerminal, string fullFileName, bool printMdn, bool sortByName) {
    cout << endl << "There are " << students.size() << " students." << endl << endl;

    if (students.size() > 0) {
        if (sortByName) {
            sort(students.begin(), students.end(), &compareStudentNames);
        }

        if (outputToTerminal) {
            cout << left;
            cout << setw(maxSurnameLength) << "Surname" << setw(maxNameLength) << "Name" << setw(20) << "Final Grade (avg)";

            if (printMdn) {
                cout << setw(20) << "Final Grade (mdn)" << endl;
            } else {
                cout << endl;
            }

            cout << string(maxSurnameLength + maxNameLength + (printMdn ? 40 : 20), '-') << endl;
            
            for (Student student : students) {
                cout << setw(maxSurnameLength) << student.surname << setw(maxNameLength) << student.name << setw(20) << setprecision(2) << fixed << student.finalAvg;

                if (printMdn) {
                    cout << setw(20) << setprecision(2) << fixed << student.finalMdn << endl;
                } else {
                    cout << endl;
                }
            }
        } else {
            ofstream file(fullFileName);

            file << left;
            file << setw(maxSurnameLength) << "Surname" << setw(maxNameLength) << "Name" << setw(20) << "Final Grade (avg)";

            if (printMdn) {
                file << setw(20) << "Final Grade (mdn)" << endl;
            } else {
                file << endl;
            }

            file << string(maxSurnameLength + maxNameLength + (printMdn ? 40 : 20), '-') << endl;
            
            for (Student student : students) {
                file << setw(maxSurnameLength) << student.surname << setw(maxNameLength) << student.name << setw(20) << setprecision(2) << fixed << student.finalAvg;

                if (printMdn) {
                    file << setw(20) << setprecision(2) << fixed << student.finalMdn << endl;
                } else {
                    file << endl;
                }
            }

            file.close();
        }
    }
}

void generateStudentFile(int &studentCount) {
    vector<Student> students;

    for (int i = 1; i <= studentCount; i++) {
        Student student = Student();

        student.name = generatedNamePrefix + to_string(i);
        student.surname = generatedSurnamePrefix + to_string(i);

        student = generateGrades(student, generatedGradeCount);
        student = calculateAvg(student);

        students.push_back(student);
    }

    sort(students.begin(), students.end(), &compareStudentFinalAvg);
    outputResults(students, false, (inputFolderName + "/" + generatedFilePrefix + to_string(studentCount) + ".txt"), false, false);
}