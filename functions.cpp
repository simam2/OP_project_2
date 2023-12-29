#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>

#include "student.cpp"
#include "constants.h"

using namespace std;
using namespace std::chrono;


Student inputNameSurname(Student &student, int i) {
    int studentNumber = i + 1;
    string name = "";
    string surname = "";

    cin.ignore();

    while (name.length() <= 0 || name.length() > maxNameLength) {
        cout << "Please enter the name of student number " << studentNumber << ": ";
        getline(cin, name);

        if (name.empty()) {
            break;
        }
    }

    if (name.empty()) {
        return student;
    }

    while (surname.length() <= 0 || surname.length() > maxSurnameLength) {
        cout << "Please enter the surname of student number " << studentNumber << " (name - " << name << "): ";
        cin >> surname;
    }

    student.setNames(name, surname);

    return student;
}

Student inputGrades(Student &student) {
    int count = 1;
    string input;

    cin.ignore();

    while (true) {
        cout << "Please enter grade " << count << " for student " << student.getName() << " " << student.getSurname() << ": ";
        getline(cin, input);

        if (input.empty()) {
            break;
        }

        try {
            if (stoi(input) >= 1 && stoi(input) <= 10) {
                count++;
                student.addGrade(stoi(input));
            } else {
                cout << "You must enter a number between 1 and 10." << endl;
            }
        } catch (invalid_argument&) {
            cout << "You must enter a number between 1 and 10." << endl;
        }
    }

    int examGrade = 0;

    while (examGrade < 1 || examGrade > 10) {
        cout << "Please enter the exam grade for student " << student.getName() << " " << student.getSurname() << ": ";
        
        string input;
        cin >> input;

        try {
            if (stoi(input) >= 1 && stoi(input) <= 10) {
                student.setExamGrade(stoi(input));
            } else {
                examGrade = -1;
                cout << "You must enter a number between 1 and 10." << endl;
            }
        } catch (invalid_argument&) {
            cout << "You must enter a number between 1 and 10." << endl;
        }
    }

    return student;
}

Student generateGrades(Student &student, int gradeCount) {
    student.generateRandomGrades(gradeCount);

    return student;
}

char chooseAction() {
    int userChoice = 0;

    while (userChoice != 1 && userChoice != 2 && userChoice != 3 && userChoice != 4) {
        cout << "Please choose what you'd like the program to do - input '1' if you would like to input/process data, input '2' if you want random input files to be generated, input '3' if you would like a generated file to be processed, input '4' if you want to see a demo of student copy actions: ";
        cin >> userChoice;
        cout << endl;
    }

    return userChoice;
}

int chooseStudentCount() {
    int studentCount = 0;

    while (studentCount < 1) {
        cout << "Please choose how many students should be (or was) generated: ";
        cin >> studentCount;
        cout << endl;
    }

    return studentCount;
}

bool chooseInputFile() {
    char userChoice = 'A';

    while (toupper(userChoice) != 'Y' && toupper(userChoice) != 'N') {
        cout << "Please choose whether you would like to input students by hand - input 'Y' for manual input or 'N' for file read: ";
        cin >> userChoice;
        cout << endl;
    }

    return toupper(userChoice) == 'Y';
}

int chooseGradeInputGen() {
    char userChoice = 'A';
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

milliseconds calculateDuration(system_clock::time_point &startTime) {
    auto endTime = high_resolution_clock::now();
    duration<double> timeDiff = endTime - startTime;
    return duration_cast<milliseconds>(timeDiff);
}


// Vector functions

void outputResults(vector<Student> &students, bool outputToTerminal, string fullFileName, bool printMdn, bool sortByName) {
    if (students.size() > 0) {
        if (sortByName) {
            sort(students.begin(), students.end(), &compareByName);
        }

        if (outputToTerminal) {
            cout << endl << "(VECTOR) There are " << students.size() << " students." << endl << endl;

            cout << left;
            cout << setw(maxSurnameLength) << "Surname" << setw(maxNameLength) << "Name" << setw(32) << "All grades" << setw(20) << "Final Grade (avg)";

            if (printMdn) {
                cout << setw(20) << "Final Grade (mdn)" << endl;
            } else {
                cout << endl;
            }

            cout << string(maxSurnameLength + maxNameLength + 32 + (printMdn ? 40 : 20), '-') << endl;
            
            for (Student student : students) {
                student.printToTerminal(printMdn);
            }
        } else {
            ofstream file(fullFileName);

            file << left;
            file << setw(maxSurnameLength) << "Surname" << setw(maxNameLength) << "Name" << setw(32) << "All grades" << setw(20) << "Final Grade (avg)";

            if (printMdn) {
                file << setw(20) << "Final Grade (mdn)" << endl;
            } else {
                file << endl;
            }

            file << string(maxSurnameLength + maxNameLength + 32 + (printMdn ? 40 : 20), '-') << endl;
            
            for (Student student : students) {
                student.printToFile(file, printMdn);
            }

            file.close();
        }
    }
}

void generateStudentFile(int &studentCount) {
    vector<Student> students;

    auto startTime = high_resolution_clock::now();

    for (int i = 1; i <= studentCount; i++) {
        Student student = Student();

        student.setNames(generatedNamePrefix + to_string(i), generatedSurnamePrefix + to_string(i));
        student.generateRandomGrades(generatedGradeCount);
        student.calculateAvg();

        students.push_back(student);
    }

    sort(students.begin(), students.end(), &compareByAvg);
    outputResults(students, false, (inputFolderName + "/" + generatedFilePrefix + to_string(studentCount) + ".txt"), false, false);

    if (measureTime) {
        milliseconds duration = calculateDuration(startTime);
        cout << "(VECTOR) File generation took " << duration.count() << " milliseconds." << endl;
    }
}

vector<Student> readGeneratedStudents(int studentCount) {
    vector<Student> students;

    string line;
    auto startTime = high_resolution_clock::now();

    ifstream file(inputFolderName + "/" + generatedFilePrefix + to_string(studentCount) + ".txt");

    if (file.fail()) {
        cout << "A generated file of " << studentCount << " students could not be found." << endl;
        exit(EXIT_FAILURE);
    }

    getline(file, line);
    getline(file, line);

    while (getline(file, line)) {
        Student student = Student(line, true);
        students.push_back(student);
    }

    file.close();

    if (measureTime) {
        milliseconds duration = calculateDuration(startTime);
        cout << "(VECTOR) File read took " << duration.count() << " milliseconds." << endl;
    }

    return students;
}

void splitOutputStudents(vector<Student> &students, int studentCount) {
    auto startTime = high_resolution_clock::now();

    switch (studentSplitStrategy) {
        case 1: {
            vector<Student> students1;
            vector<Student> students2;

            for (Student student : students) {
                if (student.getAvg() < 5) {
                    students1.push_back(student);
                } else {
                    students2.push_back(student);
                }
            }

            if (measureTime) {
                milliseconds duration = calculateDuration(startTime);
                cout << "(VECTOR) Student split took " << duration.count() << " milliseconds." << endl;
            }

            startTime = high_resolution_clock::now();

            outputResults(students1, false, (outputFolderName + "/" + generatedFilePrefix + to_string(studentCount) + ouputFileNotAsSmartSuffix + ".txt"), false, false);

            if (measureTime) {
                milliseconds duration = calculateDuration(startTime);
                cout << "(VECTOR) Student (not as smart) output took " << duration.count() << " milliseconds." << endl;
            }
            
            startTime = high_resolution_clock::now();

            outputResults(students2, false, (outputFolderName + "/" + generatedFilePrefix + to_string(studentCount) + ouputFileSmartSuffix + ".txt"), false, false);

            if (measureTime) {
                milliseconds duration = calculateDuration(startTime);
                cout << "(VECTOR) Student (smart) output took " << duration.count() << " milliseconds." << endl;
            }

            break;
        }

        case 2: {
            vector<Student> students1;

            for (auto it = students.begin(); it != students.end(); ++it) {
                int index = distance(students.begin(), it);
                Student student = students.at(index);
                
                if (student.getAvg() < 5) {
                    students1.push_back(student);
                    students.erase(it);
                }
            }

            if (measureTime) {
                milliseconds duration = calculateDuration(startTime);
                cout << "(VECTOR) Student split took " << duration.count() << " milliseconds." << endl;
            }

            startTime = high_resolution_clock::now();

            outputResults(students1, false, (outputFolderName + "/" + generatedFilePrefix + to_string(studentCount) + ouputFileNotAsSmartSuffix + ".txt"), false, false);

            if (measureTime) {
                milliseconds duration = calculateDuration(startTime);
                cout << "(VECTOR) Student (not as smart) output took " << duration.count() << " milliseconds." << endl;
            }
            
            startTime = high_resolution_clock::now();

            outputResults(students, false, (outputFolderName + "/" + generatedFilePrefix + to_string(studentCount) + ouputFileSmartSuffix + ".txt"), false, false);

            if (measureTime) {
                milliseconds duration = calculateDuration(startTime);
                cout << "(VECTOR) Student (smart) output took " << duration.count() << " milliseconds." << endl;
            }

            break;
        }

        case 3: {
            vector<Student> students1;
            vector<Student> students2;

            remove_copy_if(students.begin(), students.end(), back_inserter(students1), [](Student &student) { return student.getAvg() >= 5; });
            remove_copy_if(students.begin(), students.end(), back_inserter(students2), [](Student &student) { return student.getAvg() < 5; });

            if (measureTime) {
                milliseconds duration = calculateDuration(startTime);
                cout << "(VECTOR) Student split took " << duration.count() << " milliseconds." << endl;
            }

            startTime = high_resolution_clock::now();

            outputResults(students1, false, (outputFolderName + "/" + generatedFilePrefix + to_string(studentCount) + ouputFileNotAsSmartSuffix + ".txt"), false, false);

            if (measureTime) {
                milliseconds duration = calculateDuration(startTime);
                cout << "(VECTOR) Student (not as smart) output took " << duration.count() << " milliseconds." << endl;
            }
            
            startTime = high_resolution_clock::now();

            outputResults(students2, false, (outputFolderName + "/" + generatedFilePrefix + to_string(studentCount) + ouputFileSmartSuffix + ".txt"), false, false);

            if (measureTime) {
                milliseconds duration = calculateDuration(startTime);
                cout << "(VECTOR) Student (smart) output took " << duration.count() << " milliseconds." << endl;
            }

            break;
        }
    }
}

// List functions

void outputResults(list<Student> &students, bool outputToTerminal, string fullFileName, bool printMdn, bool sortByName) {
    if (students.size() > 0) {
        if (sortByName) {
            students.sort(&compareByName);
        }

        if (outputToTerminal) {
            cout << endl << "(LIST) There are " << students.size() << " students." << endl << endl;

            cout << left;
            cout << setw(maxSurnameLength) << "Surname" << setw(maxNameLength) << "Name" << setw(32) << "All grades" << setw(20) << "Final Grade (avg)";

            if (printMdn) {
                cout << setw(20) << "Final Grade (mdn)" << endl;
            } else {
                cout << endl;
            }

            cout << string(maxSurnameLength + maxNameLength + 32 + (printMdn ? 40 : 20), '-') << endl;
            
            for (Student student : students) {
                student.printToTerminal(printMdn);
            }
        } else {
            ofstream file(fullFileName);

            file << left;
            file << setw(maxSurnameLength) << "Surname" << setw(maxNameLength) << "Name" << setw(32) << "All grades" << setw(20) << "Final Grade (avg)";

            if (printMdn) {
                file << setw(20) << "Final Grade (mdn)" << endl;
            } else {
                file << endl;
            }

            file << string(maxSurnameLength + maxNameLength + 32 + (printMdn ? 40 : 20), '-') << endl;
            
            for (Student student : students) {
                student.printToFile(file, printMdn);
            }

            file.close();
        }
    }
}

void generateStudentFileList(int &studentCount) {
    list<Student> students;

    auto startTime = high_resolution_clock::now();

    for (int i = 1; i <= studentCount; i++) {
        Student student = Student(generatedNamePrefix + to_string(i), generatedSurnamePrefix + to_string(i));

        student.generateRandomGrades(generatedGradeCount);
        student.calculateAvg();

        students.push_back(student);
    }

    students.sort(&compareByAvg);
    outputResults(students, false, (inputFolderName + "/" + generatedFilePrefix + to_string(studentCount) + ".txt"), false, false);

    if (measureTime) {
        milliseconds duration = calculateDuration(startTime);
        cout << "(LIST) File generation took " << duration.count() << " milliseconds." << endl;
    }
}

list<Student> readGeneratedStudentsList(int studentCount) {
    list<Student> students;

    string line;
    auto startTime = high_resolution_clock::now();

    ifstream file(inputFolderName + "/" + generatedFilePrefix + to_string(studentCount) + ".txt");

    if (file.fail()) {
        cout << "A generated file of " << studentCount << " students could not be found." << endl;
        exit(EXIT_FAILURE);
    }

    getline(file, line);
    getline(file, line);

    while (getline(file, line)) {
        Student student = Student(line, true);
        students.push_back(student);
    }

    file.close();

    if (measureTime) {
        milliseconds duration = calculateDuration(startTime);
        cout << "(LIST) File read took " << duration.count() << " milliseconds." << endl;
    }

    return students;
}

void splitOutputStudents(list<Student> &students, int studentCount) {
    list<Student> students1;
    list<Student> students2;

    auto startTime = high_resolution_clock::now();

    for (Student student : students) {
        if (student.getAvg() < 5) {
            students1.push_back(student);
        } else {
            students2.push_back(student);
        }
    }

    if (measureTime) {
        milliseconds duration = calculateDuration(startTime);
        cout << "(LIST) Student split took " << duration.count() << " milliseconds." << endl;
    }

    startTime = high_resolution_clock::now();

    outputResults(students1, false, (outputFolderName + "/" + generatedFilePrefix + to_string(studentCount) + ouputFileNotAsSmartSuffix + ".txt"), false, false);
    
    if (measureTime) {
        milliseconds duration = calculateDuration(startTime);
        cout << "(LIST) Student (not as smart) output took " << duration.count() << " milliseconds." << endl;
    }
    
    startTime = high_resolution_clock::now();

    outputResults(students2, false, (outputFolderName + "/" + generatedFilePrefix + to_string(studentCount) + ouputFileSmartSuffix + ".txt"), false, false);

    if (measureTime) {
        milliseconds duration = calculateDuration(startTime);
        cout << "(LIST) Student (smart) output took " << duration.count() << " milliseconds." << endl;
    }
}