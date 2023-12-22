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
    int programMode = chooseAction();

    if (programMode == 1) {
        vector<Student> students;

        cout << endl << "If you wish to stop adding students, simply press ENTER without typing anything in when asked for a student's name." << endl << "The same rule applies to grade entering - if you entered all grades, simply press ENTER without typing anything in." << endl << endl;

        bool inputByHand = chooseInputFile();

        if (inputByHand) {
            int gradeCount = chooseGradeInputGen();

            while (true) {
                Student student = Student();

                student = inputNameSurname(student, students.size());

                if (student.getName().empty()) {
                    break;
                }

                if (gradeCount > -1) {
                    student.generateRandomGrades(gradeCount);
                } else {
                    student = inputGrades(student);
                }

                student.calculateAvg();
                student.calculateMdn();

                students.push_back(student);
                cout << endl;
            }
        } else {
            string line;
            ifstream file(inputFolderName + "/" + inputFileName);

            getline(file, line);

            while (getline(file, line)) {
                Student student = Student(line, false);

                student.calculateAvg();
                student.calculateMdn();

                students.push_back(student);
            }

            file.close();
        }

        outputResults(students, inputByHand, (outputFolderName + "/" + inputFileName), true, true);
    } else if (programMode == 2) {
        if (studentCounts.empty()) {
            int studentCount = chooseStudentCount();
            cout << endl << "Generating a file of " << studentCount << " students." << endl;

            if (measureTime) {
                for (int i = 0; i < measureTimeIterationCount; i++) {
                    cout << "Iteration number - " << i+1 << endl;
                    generateStudentFile(studentCount);

                    if (measureList) {
                        generateStudentFileList(studentCount);
                    }
                    
                    cout << endl;
                }
            } else {
                generateStudentFile(studentCount);
            }
        } else {
            for (int studentCount : studentCounts) {
                cout << endl << "Generating a file of " << studentCount << " students." << endl;

                if (measureTime) {
                    for (int i = 0; i < measureTimeIterationCount; i++) {
                        cout << "Iteration number - " << i+1 << endl;
                        generateStudentFile(studentCount);
                        
                        if (measureList) {
                            generateStudentFileList(studentCount);
                        }
                        
                        cout << endl;
                    }
                } else {
                    generateStudentFile(studentCount);
                }
            }
        }
    } else if (programMode == 3) {
        if (studentCounts.empty()) {
            int studentCount = chooseStudentCount();
            cout << endl << "Processing a file of " << studentCount << " students." << endl;

            if (measureTime) {
                for (int i = 0; i < measureTimeIterationCount; i++) {
                    cout << "Iteration number - " << i+1 << endl;
                    auto startTime = high_resolution_clock::now();

                    vector<Student> students = readGeneratedStudents(studentCount);
                    splitOutputStudents(students, studentCount);

                    milliseconds duration = calculateDuration(startTime);
                    cout << "(VECTOR) Full test time: " << duration.count() << " milliseconds." << endl << endl;

                    if (measureList && studentSplitStrategy == 1) {
                        startTime = high_resolution_clock::now();

                        list<Student> studentsList = readGeneratedStudentsList(studentCount);
                        splitOutputStudents(studentsList, studentCount);

                        duration = calculateDuration(startTime);
                        cout << "(LIST) Full test time: " << duration.count() << " milliseconds." << endl << endl << endl;
                    }
                }
            } else {
                vector<Student> students = readGeneratedStudents(studentCount);
                splitOutputStudents(students, studentCount);
            }
        } else {
            for (int studentCount : studentCounts) {
                cout << endl << "Processing a file of " << studentCount << " students." << endl;

                if (measureTime) {
                    for (int i = 0; i < measureTimeIterationCount; i++) {
                        cout << "Iteration number - " << i+1 << endl;
                        auto startTime = high_resolution_clock::now();

                        vector<Student> students = readGeneratedStudents(studentCount);
                        splitOutputStudents(students, studentCount);

                        milliseconds duration = calculateDuration(startTime);
                        cout << "(VECTOR) Full test time: " << duration.count() << " milliseconds." << endl << endl;

                        if (measureList && studentSplitStrategy == 1) {
                            startTime = high_resolution_clock::now();

                            list<Student> studentsList = readGeneratedStudentsList(studentCount);
                            splitOutputStudents(studentsList, studentCount);

                            duration = calculateDuration(startTime);
                            cout << "(LIST) Full test time: " << duration.count() << " milliseconds." << endl << endl << endl;
                        }
                    }
                } else {
                    vector<Student> students = readGeneratedStudents(studentCount);
                    splitOutputStudents(students, studentCount);
                }
            }
        }
    } else if (programMode == 4) { // demo student copy constructor and copy assignment operator
        Student student = Student(string("Vardas"), string("Pavarde"));

        student.addGrade(5);
        student.addGrade(8);
        student.addGrade(6);
        student.setExamGrade(9);
        student.calculateAvg();
        student.calculateMdn();

        cout << "Original student's name " << student.getName() << " , surname: " << student.getSurname() << " , avg - " << setprecision(2) << fixed << student.getAvg() << " , mdn - " << setprecision(2) << fixed << student.getMdn() << endl; 

        Student studentCopied = Student(student);

        cout << "Copied via constructor student's name " << studentCopied.getName() << " , surname: " << studentCopied.getSurname() << " , avg - " << setprecision(2) << fixed << studentCopied.getAvg() << " , mdn - " << setprecision(2) << fixed << studentCopied.getMdn() << endl; 

        studentCopied.setName("Vardas1");
        studentCopied.addGrade(10);
        studentCopied.addGrade(10);
        studentCopied.calculateAvg();
        studentCopied.calculateMdn();

        Student studentAssigned = studentCopied;

        cout << "Copied via assignment student's name " << studentAssigned.getName() << " , surname: " << studentAssigned.getSurname() << " , avg - " << setprecision(2) << fixed << studentAssigned.getAvg() << " , mdn - " << setprecision(2) << fixed << studentAssigned.getMdn() << endl; 
    }
}