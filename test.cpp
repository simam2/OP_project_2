#define CATCH_CONFIG_MAIN

#include <iomanip>
#include <random>

#include "catch2/catch_amalgamated.hpp"
#include "student.cpp"

using namespace std;

TEST_CASE("Setting names for Student", "[Student][setNames]") {
    Student student = Student("Vardas", "Pavarde");
    REQUIRE(student.getName() == "Vardas");
    REQUIRE(student.getSurname() == "Pavarde");
}

TEST_CASE("Adding grades for Student", "[Student][addGrade][getGrades]") {
    Student student;
    student.addGrade(90);
    student.addGrade(85);
    student.addGrade(92);
    REQUIRE(student.getGrades() == std::vector<int>{90, 85, 92});
}