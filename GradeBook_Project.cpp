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

    // function calculate grades average
    float getAverage() const {
        if (grades.empty()) return 0;
        float sum = 0;
        for(float g : grades) sum += g;
        return sum / grades.size();
    }

    // function to print student's info
    void printInfo() const {
        cout << "Studnet: " << name << "(ID: " << studentID << ")\n";
        cout << "Grades: ";
        for (float g : grades) cout << g << " ";
        cout << "\nAverage: " << getAverage() << endl;
    }

    // saving student's info into file format
    string toFileFormat() const {
        stringstream ss;
        ss << name << "," << studentID;
        for (float g : grades)
            ss << "," << g;
        ss <<", Final Grade: " << fixed << setprecision(2) << getAverage();
        return ss.str();
    }

};