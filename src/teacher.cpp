#include "teacher.h"
#include "input.h"

using namespace std;

void Teacher::setTitle(const string& t) {
    title = t;
}

string Teacher::getTitle() const {
    return title;
}

void Teacher::setNrOfClasses(int n) {
    nrOfClasses = n;
}

int Teacher::getNrOfClasses() const {
    return nrOfClasses;
}

bool Teacher::isApproved(double grade) {
    return grade >= 1.0 && grade <= PASSING_GRADE;
}

bool Teacher::addStudent(const string& name, double grade) {
    if (!isApproved(grade)) return false;
    students.push_back(name);
    return true;
}

const vector<string>& Teacher::getStudents() const {
    return students;
}

void Teacher::insertStudents(istream& in, ostream& out) {
    int n = readInt(in, out, "How many students are there? ", 0, 1000);
    for (int i = 0; i < n; i++) {
        string name = readNonEmptyLine(in, out, "Student " + to_string(i + 1) + " name: ");
        // German grading system: 1-6, where 1 is best and 6 is worst
        double grade = readDouble(in, out, "German grade for this student (1-6): ", 1.0, 6.0);

        if (addStudent(name, grade)) {
            out << "  -> " << name << " approved (grade " << grade << ")." << endl;
        } else {
            out << "  -> " << name << " not approved (grade " << grade << " - failing)." << endl;
        }
    }
}

void Teacher::outputStudents(ostream& out) const {
    if (students.empty()) {
        out << "No approved students to list." << endl;
        return;
    }
    out << "Approved students:" << endl;
    for (size_t i = 0; i < students.size(); ++i) {
        out << "  " << (i + 1) << ". " << students[i] << endl;
    }
}
