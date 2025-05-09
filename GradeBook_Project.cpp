#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 
#include <iomanip>

using namespace std;

// Student class //

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
        if (grades.empty()) return 0;  // avoid divisoin by zero
        float sum = 0;
        for(float g : grades) sum += g;
        return sum / grades.size();  // returns average
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
        ss << name << ", Student ID: " << studentID << ", Grades:";
        for (float g : grades)
            ss << "," << g;
        ss <<", Final Grade: " << fixed << setprecision(2) << getAverage();
        return ss.str(); // return format to
    }

    //function to read student's data from line of text
    static Student fromFileFormat(const string& line) {
        stringstream ss(line);
        string name;
        getline(ss, name, ',');         // get name

        string temp;
        getline(ss, temp, ':');     // skip Student ID
        getline(ss, temp, ',');     // get student ID value

        int studentID = stoi(temp);  // convert to int

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

// GradeBook Class //

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

        //Function to print all of students info for all students
        void listStudents() {
            for (Student* s: students) s->printInfo();
        }

        // save all students to a flie
        void saveToFlie( string filename) {
            ofstream fout(filename);            // open file to read
            for (Student* s : students)
                fout << s->toFileFormat() << endl;  // wrtie each student
            fout.close(); // close file
        }

        // Load students from file
        void loadFromFile(string filename) {
            ifstream fin(filename);     // open file for reading
            string line;
            while (getline(fin, line)) {
                Student s = Student::fromFileFormat(line);  // create from line
                students.push_back(new Student(s));         //add copy to vector
            }
            fin.close();
        }

        // Find student using ID
        Student* findStudentById(int studentID) {
            for (Student* s : students) {
                if (s->getStudentID() == studentID)
                return s;
            }
            return nullptr;     //null if not found
        }

        //Add grade to student from list
        void addGradeToStudent(int studentID, float grade) {
            Student* s = findStudentById(studentID);
            if (s != nullptr) {
                s->addGrade(grade);
                cout << "Grade has been added.\n";
            } else {
                cout <<"Student not found.\n";
            }
        }

        // Delete student by using ID
        void deleteStudentById(int studentID) {
            for (int i = 0; i < students.size(); ++i) {
                if (students[i] -> getStudentID() == studentID) {
                    delete students[i];
                    students.erase(students.begin() + i);
                    cout << "Student has been deleted.\n";
                    return;
                }
            }
            cout << "Student not found\n";
        }
        
};

// Main function //
int main() {
    Gradebook gb;
    int choice;
    string firstName, lastName, fullName;
    int studentID;
    float grade;

    do {
        //Display Menu with choices
        cout << "\n *****-- Gradebook Menu --*****\n";
        cout << "1. Add Student\n";
        cout << "2. List Students\n";
        cout << "3. Save to File\n";
        cout << "4. Load from File\n";
        cout << "5. Add Grade to Student\n";
        cout << "6. Delete Student\n";
        cout << "7. Exit\n";
        cin >> choice;

        // Breaks loop if invlaid input
        if(cin.fail()) {                    
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input. Please Enter a Number.\n";
            continue;
        }

        switch(choice) {
            case 1:
                // add student
                cout << "Enter First Name: ";
                cin >> firstName;
                cout << "Enter Last Name: ";
                cin >> lastName;
                fullName = firstName + " " + lastName;

                cout << "Enter Student's ID: "; // add id to student
                cin >> studentID;
                gb.addStudent(fullName, studentID);

                cout << "Enter First Grade: ";  // add first grade
                cin >> grade;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid Grade. Please Enter a Number: ";
                    cin >> grade;
                }
                gb.addGradeToStudent(studentID, grade);
                break;
            
            case 2: // show list of students
                gb.listStudents();
                break;

            case 3: // save data
                gb.saveToFlie("gradebook.txt");
                cout << "Saved to gradebook.txt\n";
                break;

            case 4: // load data
                gb.loadFromFile("gradebook.txt");
                cout << "Loaded from gradebook.txt\n";
                break;

            case 5: // Add grade to student
                cout << "Enter Student's ID: ";
                cin >> studentID;
                cout << "Enter Grade to Add: ";
                cin >> grade;
                gb.addGradeToStudent(studentID, grade);
                break;

            case 6: // Delete Student
                cout << "Enter Student's ID to Delete: ";
                cin >> studentID;
                gb.deleteStudentById(studentID);
                break; 
        
        }

    } while (choice !=7); // repeat until user exits

    return 0;
}