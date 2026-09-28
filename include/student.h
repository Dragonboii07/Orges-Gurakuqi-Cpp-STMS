#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "person.h"

class Student : public Person {
private:
    std::string faculty;
    std::string cls;
    std::vector<double> grades;

public:
    Student() {}

    void setFaculty(const std::string& f);
    std::string getFaculty() const;

    void setCls(const std::string& c);
    std::string getCls() const;

    // German grades: 1.0 (best) to 6.0 (worst)
    static constexpr double BEST_GRADE = 1.0;
    static constexpr double WORST_GRADE = 6.0;
    static std::string gradeDescriptor(double grade);

    // returns false (and stores nothing) if the grade is outside 1.0-6.0
    bool addGrade(double grade);
    const std::vector<double>& getGrades() const;
    double averageGrade() const;  // 0 when there are no grades

    // asks how many grades to enter, reads them and prints the report
    void pushData(std::istream& in = std::cin, std::ostream& out = std::cout);
    void printReport(std::ostream& out = std::cout) const;
};

#endif // STUDENT_H_INCLUDED
