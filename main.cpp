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

            file.close();
        }

        outputResults(students, inputByHand, (outputFolderName + "/" + inputFileName), true, true);
    } else if (programMode == 2) {
        int studentCount = chooseStudentCount();

        generateStudentFile(studentCount);
    } else if (programMode == 3) {
        int studentCount = chooseStudentCount();
        vector<Student> students = readGeneratedStudents(studentCount);

        splitOutputStudents(students, studentCount);
    }
    
}