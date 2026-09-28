#include <iostream>
#include <string>
#include "input.h"
#include "person.h"
#include "student.h"
#include "teacher.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ---------------------------------------------------------------------------
// helper functions to break main into logical pieces
// ---------------------------------------------------------------------------

static void setUtf8Console() {
#ifdef _WIN32
    // switch Windows console to UTF-8 so output renders properly
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

// asks for the fields every person has
static void readPerson(Person& p) {
    p.setName(readNonEmptyLine(cin, cout, "Name: "));
    p.setSurname(readNonEmptyLine(cin, cout, "Surname: "));
    p.setAge(readInt(cin, cout, "Age: ", 1, 150));
}

static void handleStudent() {
    Student s;

    cout << "\n--- STUDENT INFORMATION FORM ---" << endl;
    readPerson(s);
    s.setFaculty(readNonEmptyLine(cin, cout, "Faculty: "));
    s.setCls(readNonEmptyLine(cin, cout, "Class/Grade: "));

    cout << "\n--- INFORMATION SUMMARY ---" << endl;
    cout << "Name: " << s.getFullName() << "\n"
         << "Age: " << s.getAge() << "\n"
         << "Faculty: " << s.getFaculty() << "\n"
         << "Class: " << s.getCls() << endl;

    s.pushData();
}

static void handleTeacher() {
    Teacher t;

    cout << "\n--- TEACHER INFORMATION FORM ---" << endl;
    readPerson(t);
    t.setTitle(readNonEmptyLine(cin, cout, "Title (Professor/Dr./Instructor): "));
    t.setNrOfClasses(readInt(cin, cout, "Number of Classes: ", 0, 100));

    cout << "\n--- TEACHER INFORMATION SUMMARY ---" << endl;
    cout << "Name: " << t.getTitle() << " " << t.getFullName() << "\n"
         << "Age: " << t.getAge() << "\n"
         << "Classes: " << t.getNrOfClasses() << endl;

    cout << "\n--- APPROVED STUDENTS REGISTRY ---" << endl;
    cout << "(Only students with German grade 1-4 will be approved)\n";
    t.insertStudents();

    cout << "\n--- APPROVED STUDENTS LIST ---" << endl;
    t.outputStudents();
}

// ---------------------------------------------------------------------------
// entry point
// ---------------------------------------------------------------------------

int main() {
    setUtf8Console();

    cout << "========================================" << endl;
    cout << "   Student & Teacher Management System  " << endl;
    cout << "========================================" << endl;

    try {
        do {
            char answer = readChoice(cin, cout, "\nAre you a student (S) or a teacher (T)? ", "ST");
            if (answer == 'S') {
                handleStudent();
            } else {
                handleTeacher();
            }
        } while (readChoice(cin, cout, "\nWould you like to perform another operation? (Y/N): ", "YN") == 'Y');
    } catch (const InputEnded&) {
        cout << "\n(end of input)" << endl;
    }

    cout << "\nThank you for using the program. Goodbye!" << endl;
    return 0;
}
