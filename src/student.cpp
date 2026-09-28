#include "student.h"
#include "input.h"

#include <iomanip>

using namespace std;

void Student::setFaculty(const string& f) {
    faculty = f;
}

string Student::getFaculty() const {
    return faculty;
}

void Student::setCls(const string& c) {
    cls = c;
}

string Student::getCls() const {
    return cls;
}

string Student::gradeDescriptor(double g) {
    if (g <= 1.5) return "Sehr gut";
    if (g <= 2.5) return "Gut";
    if (g <= 3.5) return "Befriedigend";
    if (g <= 4.0) return "Ausreichend";
    if (g <= 5.0) return "Mangelhaft";
    return "Ungenügend";
}

bool Student::addGrade(double grade) {
    if (grade < BEST_GRADE || grade > WORST_GRADE) return false;
    grades.push_back(grade);
    return true;
}

const vector<double>& Student::getGrades() const {
    return grades;
}

double Student::averageGrade() const {
    if (grades.empty()) return 0.0;
    double sum = 0;
    for (double g : grades) {
        sum += g;
    }
    return sum / grades.size();
}

void Student::pushData(istream& in, ostream& out) {
    out << "\n--- GERMAN GRADE ENTRY SYSTEM ---" << endl;
    out << "(enter grades on a scale from 1.0 [best] to 6.0 [worst])" << endl;

    int n = readInt(in, out, "\nHow many grades do you want to enter? ", 1, 100);

    out << "\nEnter your grades below:" << endl;
    out << "─────────────────────────────────────────" << endl;
    for (int i = 0; i < n; i++) {
        string prompt = "  Grade " + to_string(i + 1) + " (1.0-6.0): ";
        addGrade(readDouble(in, out, prompt, BEST_GRADE, WORST_GRADE));
    }

    printReport(out);
}

void Student::printReport(ostream& out) const {
    out << "\n--- GRADE SUMMARY REPORT ---" << endl;
    if (grades.empty()) {
        out << "No grades entered." << endl;
        return;
    }

    out << fixed << setprecision(1);
    out << "\nAll Grades Entered:" << endl;
    for (size_t i = 0; i < grades.size(); i++) {
        out << "  [" << (i + 1) << "] " << grades[i] << " (" << gradeDescriptor(grades[i]) << ")" << endl;
    }

    double average = averageGrade();
    out << "\n─────────────────────────────────────────" << endl;
    out << "  Average Grade: " << setprecision(2) << average
        << " (" << gradeDescriptor(average) << ")" << endl;
    out << "─────────────────────────────────────────" << endl << endl;
    out << defaultfloat << setprecision(6);
}
