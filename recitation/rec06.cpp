// by Sam Cao
/*
  rec06_start.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section {
    class TimeSlot {
        private:
            int hours;
            string day;
        public:
            TimeSlot(const string& day,int hours) : day(day),hours(hours) {};
            friend ostream &operator<<(ostream &os, const TimeSlot &timeSlot ) {
            if(timeSlot.hours > 12){
                os << ", Time slot:" << " [Day: "<< timeSlot.day << ", Start time: " << timeSlot.hours-12<< "pm],";
            }
            else{
                os << ", Time slot:" << " [Day: "<< timeSlot.day << ", Start time: " << timeSlot.hours<< "am],";
            }
            return os;
            }
    };


    class StudentRecord {
        public:
            StudentRecord(const string&student_name):student_name(student_name){};
        friend ostream &operator<<(ostream &os, StudentRecord& studentRecord ) {
            os<<endl;
            os<<"Name: "<<studentRecord.student_name<<", Grades:";
            for (size_t i=0; i<studentRecord.student_grades.size()-1; i++){

                os<<studentRecord.student_grades[i]<<' ';

            }

            return os;
            }
        const string &getName(){
                return student_name;
        }
        void setGrade(int &grades, int& week){
             student_grades[week-1] = grades;
        }
        private:
            string student_name;
            vector<int> student_grades = vector<int>(14,-1);

        };// add 14 grades in the record



public:
    Section(const string &section_name,const string& day,int hours): section_name(section_name), timeSlot(day,hours){};
    Section(const Section&section):section_name(section.section_name), timeSlot(section.timeSlot){
        for (const StudentRecord *record: section.class_list){
            class_list.push_back(new StudentRecord(*record));
        }
    }
    friend ostream &operator<<(ostream &os, Section&section ) {
        os << "Section: " << section.section_name << section.timeSlot << " Students: ";
        if (section.class_list.size() == 0) {
            os << "None" << endl;
        } else {
            for (size_t i = 0; i < section.class_list.size(); i++) {
                os << *section.class_list[i];
            }
        }

        return os;
    }
    ~Section(){

        cout << "Section " << section_name << " is being deleted" << endl;
        for (size_t index = 0; index < class_list.size(); ++index)
        {
            cout << "Deleting " << class_list[index]->getName() << endl;
            delete class_list[index];
        }
        class_list.clear();
    }


        void addgrade(const string &stud,int grades,int week) {
            for (size_t stud_pos = 0; stud_pos < class_list.size(); ++stud_pos) {
                if (class_list[stud_pos]->getName() == stud) {
                    class_list[stud_pos]->setGrade(grades, week);
                }
            }
        }

        void addStudent(const string& stud) {
            class_list.push_back(new StudentRecord(stud));

    }
private:
    string section_name;
    TimeSlot timeSlot;
    vector<StudentRecord*> class_list;
    };

class LabWorker { // know which section is teaching
    friend ostream &operator<<(ostream &os, const LabWorker &professor) {
        if (professor.tosection == nullptr){
            os << professor.worker_name << " does not have a section"<<endl;
        }
        else{
            os << professor.worker_name<< " has "<< *professor.tosection <<endl;
        }
        return os;
    }
private:
    string worker_name;
    Section* tosection;
public:
    LabWorker(const string& worker_name):worker_name(worker_name),tosection(nullptr){};

    void addSection(Section& section_name){
        tosection = &section_name;
    }
    void addGrade(const string& stud_name,int grades,int week){
        tosection -> addgrade(stud_name,grades,week);
    }

};


void doNothing(Section sec) { cout << sec << endl; }
int main() {

        cout << "Test 1: Defining a section\n";
        Section secA2("A2", "Tuesday", 16);
        cout << secA2 << endl;

        cout << "\nTest 2: Adding students to a section\n";
         secA2.addStudent("John");
         secA2.addStudent("George");
         secA2.addStudent("Paul");
         secA2.addStudent("Ringo");
         cout << secA2 << endl;

        cout << "\nTest 3: Defining a lab worker.\n";
        LabWorker moe( "Moe" );
        cout << moe << endl;

        cout << "\nTest 4: Adding a section to a lab worker.\n";
         moe.addSection( secA2 );
         cout << moe << endl;

        cout << "\nTest 5: Adding a second section and lab worker.\n";
         LabWorker jane( "Jane" );
         Section secB3( "B3", "Thursday", 11 );
         secB3.addStudent("Thorin");
         secB3.addStudent("Dwalin");
         secB3.addStudent("Balin");
         secB3.addStudent("Kili");
         secB3.addStudent("Fili");
         secB3.addStudent("Dori");
         secB3.addStudent("Nori");
         secB3.addStudent("Ori");
         secB3.addStudent("Oin");
         secB3.addStudent("Gloin");
         secB3.addStudent("Bifur");
         secB3.addStudent("Bofur");
         secB3.addStudent("Bombur");
         jane.addSection( secB3 );
         cout << jane << endl;

        cout << "\nTest 6: Adding some grades for week one\n";
         moe.addGrade("John", 17, 1);
         moe.addGrade("Paul", 19, 1);
         moe.addGrade("George", 16, 1);
         moe.addGrade("Ringo", 7, 1);
         cout << moe << endl;

        cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
         moe.addGrade("John", 15, 3);
         moe.addGrade("Paul", 20, 3);
         moe.addGrade("Ringo", 0, 3);
         moe.addGrade("George", 16, 3);
         cout << moe << endl;

        cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
             << "those students (or rather their records?)\n";

        cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
             << "then make sure the following call works:\n";
        doNothing(secA2);
        cout << "Back from doNothing\n\n";

    } // main

