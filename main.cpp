#include <iostream>
#include <numeric>
#include <iomanip>

using namespace std;


const float examWeight = 0.6;
const float gradesWeight = 0.4;
const int maxStudentCount = 5;
const int maxNameLength = 15;
const int maxSurnameLength = 20;

struct Student {
    string name;
    string surname;
    vector<int> grades;
    int examGrade;
    float finalAvg;
    float finalMdn;
};


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

        if (stoi(input) >= 1 && stoi(input) <= 10) {
            count++;
            student.grades.push_back(stoi(input));
        }
    }

    while (student.examGrade < 1 || student.examGrade > 10) {
        cout << "Please enter the exam grade for student " << student.name << " " << student.surname << ": ";
        cin >> student.examGrade;
    }

    return student;
}

bool chooseAvgMdn() {
    char userChoice;

    while (toupper(userChoice) != 'A' && toupper(userChoice) != 'M') {
        cout << "Please choose how the final grade should be calculated - input 'A' for average or 'M' for median: ";
        cin >> userChoice;
        cout << endl;
    }

    return toupper(userChoice) == 'A';
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


int main() {
    cout << endl << "If you wish to stop adding students, simply press ENTER without typing anything in when asked for a student's name." << endl << "The same rule applies to grade entering - if you entered all grades, simply press ENTER without typing anything in." << endl << endl;

    bool isAvg = chooseAvgMdn();

    vector<Student> students;

    while (true) {
        Student student = Student();

        student = inputNameSurname(student, students.size());

        if (student.name.empty()) {
            break;
        }

        student = inputGrades(student);

        if (isAvg) {
            student = calculateAvg(student);
        } else {
            student = calculateMdn(student);
        }

        students.push_back(student);
        cout << endl;
    }

    cout << endl << "There are " << students.size() << " students." << endl << endl;

    if (students.size() > 0) {
        string finalGradeHeader = string("Final grade (") + (isAvg ? "avg" : "mdn") + ")";

        cout << left;
        cout << setw(maxSurnameLength) << "Surname" << setw(maxNameLength) << "Name" << setw(20) << finalGradeHeader << endl;
        cout << string(maxSurnameLength + maxNameLength + 20, '-') << endl;
        
        for (Student student : students) {
            cout << setw(maxSurnameLength) << student.surname << setw(maxNameLength) << student.name << setw(20) << setprecision(2) << fixed << (isAvg ? student.finalAvg : student.finalMdn) << endl;
        }
    }
}