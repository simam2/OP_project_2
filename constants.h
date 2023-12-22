#pragma once

#include <string>

using namespace std;

const float examWeight = 0.6;
const float gradesWeight = 0.4;
const int maxStudentCount = 5;
const int maxNameLength = 15;
const int maxSurnameLength = 20;
const string inputFolderName = "input";
const string outputFolderName = "output";
const string inputFileName = "studentai10000.txt";

const bool measureTime = true;
const bool measureList = false;
const int studentSplitStrategy = 1; // 1 - split the original list into two new ones; 2 - remove the "notAsSmart" ones from the original list and put them into a new list; 3 - the same as 1st but using remove_copy_if.
const vector<int> studentCounts = {1000, 10000, 100000};
const int measureTimeIterationCount = 5;
const int generatedGradeCount = 10;
const string generatedFilePrefix = "studentai_";
const string generatedNamePrefix = "Vardas";
const string generatedSurnamePrefix = "Pavarde";
const string ouputFileSmartSuffix = "_smart";
const string ouputFileNotAsSmartSuffix = "_notAsSmart";