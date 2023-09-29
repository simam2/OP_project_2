#include <iostream>
#include <numeric>
#include <iomanip>

using namespace std;


const int gradeCount = 3;
const int maxStudentCount = 5;
const int maxNameLength = 15;
const int maxSurnameLength = 20;

struct Student {
    string name;
    string surname;
    array<int,gradeCount> grades;
    int examGrade;
    float finalAvg;
};


Student inputNameSurname(Student &student, int i) {
    int studentNumber = i + 1;

    while (student.name.length() <= 0 || student.name.length() > maxNameLength) {
        cout << "Please enter the name of student number " << studentNumber << ": ";
        cin >> student.name;
    }

    while (student.surname.length() <= 0 || student.surname.length() > maxSurnameLength) {
        cout << "Please enter the surname of student number " << studentNumber << " (name - " << student.name << "): ";
        cin >> student.surname;
    }

    return student;
}

Student inputGrades(Student &student) {
    for (int i = 0; i < gradeCount; i++) {
        while (student.grades[i] < 1 || student.grades[i] > 10) {
            cout << "Please enter grade " << i + 1 << " for student " << student.name << " " << student.surname << ": ";
            cin >> student.grades[i];
        }
    }

    while (student.examGrade < 1 || student.examGrade > 10) {
        cout << "Please enter the exam grade for student " << student.name << " " << student.surname << ": ";
        cin >> student.examGrade;
    }

    return student;
}

Student calculateAvg(Student &student) {
    student.finalAvg = (accumulate(student.grades.begin(), student.grades.end(), student.finalAvg) + student.examGrade) / (student.grades.size() + 1);
    return student;
}


int main() {
    int studentCount;

    while (studentCount < 0 || studentCount > maxStudentCount) {
        cout << "Please input the student count: ";
        cin >> studentCount;
        cout << endl;
    };

    Student students[studentCount];

    for (int i = 0; i < studentCount; i++){
        Student student = Student();

        student = inputNameSurname(student, i);
        student = inputGrades(student);
        student = calculateAvg(student);

        students[i] = student;
        cout << endl;
    }

    cout << endl << "There are " << studentCount << " students." << endl << endl;

    if (studentCount > 0) {
        cout << left;
        cout << setw(maxSurnameLength) << "Surname" << setw(maxNameLength) << "Name" << setw(20) << "Final grade (avg)" << endl;
        cout << string(maxSurnameLength + maxNameLength + 20, '-') << endl;
        
        for (Student student : students) {
            cout << setw(maxSurnameLength) << student.surname << setw(maxNameLength) << student.name << setw(20) << setprecision(2) << fixed << student.finalAvg << endl;
        }
    }
}