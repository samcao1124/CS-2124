/*Sam Cao
  rec08_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to fix the cyclic association.
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}


// Course class
// output operator:
ostream& operator <<(ostream& os, const Course& cs_course) {
    os << cs_course.name << ": ";
    if (cs_course.students.size() == 0) {
        os << "No Students";
    }else {
        for (size_t each_student = 0; each_student < cs_course.students.size(); ++each_student) {
                os << cs_course.students[each_student]->getName();
        }
    }
        return os;

}
//constructor
Course :: Course(const string& name) : name(name){}

const string& Course ::getName() const {return name;}


bool Course ::addStudent(Student* student_2){
    for (size_t each_student = 0; each_student < students.size();++ each_student){
        if(students[each_student] == student_2){
            return false;
        }
    }
    students.push_back(student_2);
    return true;


}
// remove students
void Course ::removeStudentsFromCourse(){
    for (size_t i = 0; i < students.size(); ++i) {
        students[i]->removedFromCourse(this);
    }

}
//students class
// output operator:
ostream& operator <<(ostream& os, const Student& cs_student) {
    os << cs_student.name << ": ";
    if (cs_student.courses.size() == 0) {
        os << "No Courses";
    }else {
        for (size_t each_courses = 0; each_courses < cs_student.courses.size(); ++each_courses) {

                os << cs_student.courses[each_courses]->getName();

        }
    }
    return os;

}
//constructor:
Student ::Student(const string& name_stu) : name(name_stu){}
// get name:
const string& Student ::getName() const {return name;}

bool Student ::addCourse(Course * course2) {
    for (size_t each_course = 0; each_course < courses.size(); ++ each_course){
        if(courses[each_course] == course2){
            return false;
        }
    }
    courses.push_back(course2);
    return true;
}

void Student ::removedFromCourse(Course * course1) {

    for (size_t i = 0; i < courses.size(); ++i){
        if(courses[i] == course1){
            for (size_t m = 0; m < courses.size(); ++m){
                courses[m] = courses[m+1];
            }
        }
    }
    courses.pop_back();
}


// registrar class
// operator:
ostream& operator <<(ostream& os, const Registrar& cs_registrar){
    os << "Registrar's Report" << endl;
    os << "Courses: " << endl;
    for(size_t each_course = 0; each_course < cs_registrar.courses.size(); ++ each_course) {

            os << *cs_registrar.courses[each_course] << endl;
        }

    os << "Students: " << endl;
    for(size_t each_student = 0; each_student < cs_registrar.students.size(); ++ each_student) {
            os << *cs_registrar.students[each_student] << endl;
    }
    return os;
}
// constructor:
Registrar ::Registrar() {}


size_t Registrar::findStudent(const string& name) const{
    size_t student_position = students.size();
    for (size_t each_student = 0; each_student < students.size(); ++ each_student){
        if(students[each_student]->getName() == name){
            return each_student;
        }
    }
    return student_position;

}
size_t Registrar :: findCourse(const string& name) const{
    size_t course_position = courses.size();
    for (size_t each_course = 0; each_course < courses.size(); ++ each_course){
        if(courses[each_course]->getName() == name){
            return each_course;
        }
    }
    return course_position;
}

bool Registrar ::addCourse(const string &name) {
    for (size_t each_course = 0; each_course < courses.size(); ++ each_course){
        if(courses[each_course]->getName() == name){
            return false;
        }
    }
    courses.push_back(new Course(name));
    return true;
}

bool Registrar ::addStudent(const string & name) {
    for (size_t each_student = 0; each_student < students.size(); ++ each_student){
        if(students[each_student]->getName() == name){
            return false;
        }
    }
    students.push_back(new Student(name));
    return true;
}

void Registrar ::purge() {
    for (Course * each_course :courses){
        delete each_course;
    }
    courses.clear();

    for (Student * each_student :students){
        delete each_student;
    }
    students.clear();
}

bool Registrar :: enrollStudentInCourse(const string& studentName,
                           const string& courseName){
    size_t student_position = findStudent(studentName);
    size_t course_position = findCourse(courseName);
    if (course_position != courses.size() && student_position != students.size()) {
        courses[course_position]->addStudent(students[student_position]);   //include student to course
        students[student_position]->addCourse(courses[course_position]);    //include course to student
        return true;
    }
    return false;


}
bool Registrar::cancelCourse(const string& courseName){
    size_t course_position = findCourse(courseName);
    if (course_position != courses.size()){
        courses[course_position] -> removeStudentsFromCourse();
        delete courses[course_position];
        for (size_t index_course = course_position ; index_course< courses.size()-1 ;  ++ index_course){
            courses[index_course] = courses[index_course+1];
        }
        courses.pop_back();
        return true;
    }
    return false;

}