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

    //function to read student's data from line of text
    static Student fromFileFormat(const string& line) {
        stringstream ss(line);
        string name;
        getline(ss, name, ',');         // get name

        int studentID;                  //read id
        ss >> studentID;
        ss.ignore();

        Student s(name,studentID); // create student object
        string token;

        // Read and add grades until "Final Grade" is found
        while (getline(ss, token, ',')) {
            if(token.find("Final") != string::npos) break;
            try {
                float g = stof(token);  // converts string to float
                s.addGrade(g);          // adds grade to student
            } catch (...) {}            // ignore invalid data
        }
        return s;
    }

    // Return student ID
    int getStudentID() const {
        return studentID;
    }

};

// GradeBook Class

class Gradebook {
    private:
        vector<Student*> students; // vector of pointers to Student objects

    public:
        // Destructor to clean up allocated students
        ~Gradebook() {
            for (Student* s : students) delete s;
        }

        //Function to add new students
        void addStudent( string name, int studentID) {
            students.push_back(new Student(name , studentID));
        }

        
        
};