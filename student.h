#pragma once

#include <string>
#include <vector>

using namespace std;

struct Student {
    string name;
    string surname;
    vector<int> grades;
    int examGrade;
    float finalAvg;
    float finalMdn;
};