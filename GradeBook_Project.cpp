#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 
#include <iomanip>

using namespace std;

// Student class

class Student {

    private:
        string name; // student's name
        int studentID; // studnet's id
        vector<float> grades; // list of grades

    public:
    // constructor to initilaze name and ID
    Student(string name, int studentID) : name(name), studentID(studentID) {}

    // function to add grade
    void addGrade(float grade) {
        grades.push_back(grade);
    }

}