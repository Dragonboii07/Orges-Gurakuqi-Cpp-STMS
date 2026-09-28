#ifndef TEACHER_H_INCLUDED
#define TEACHER_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "person.h"

class Teacher : public Person {
private:
    std::string title;
    int nrOfClasses;
    std::vector<std::string> students;  // approved students only

public:
    Teacher() : nrOfClasses(0) {}

    void setTitle(const std::string& t);
    std::string getTitle() const;

    void setNrOfClasses(int n);
    int getNrOfClasses() const;

    // German grades 1-4 pass, 5-6 fail
    static constexpr double PASSING_GRADE = 4.0;
    static bool isApproved(double grade);

    // records the student if approved; returns whether they were
    bool addStudent(const std::string& name, double grade);
    const std::vector<std::string>& getStudents() const;

    // asks for the students and their grades
    void insertStudents(std::istream& in = std::cin, std::ostream& out = std::cout);
    void outputStudents(std::ostream& out = std::cout) const;
};

#endif // TEACHER_H_INCLUDED
