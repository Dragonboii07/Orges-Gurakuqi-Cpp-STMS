// Simple self-checking tests: run the program, it prints each failure and
// returns a non-zero exit code if anything is wrong.
#include <iostream>
#include <sstream>
#include <string>
#include "input.h"
#include "student.h"
#include "teacher.h"

static int failures = 0;

#define CHECK(cond)                                                           \
    do {                                                                      \
        if (!(cond)) {                                                        \
            std::cerr << __FILE__ << ":" << __LINE__ << ": FAILED " #cond "\n"; \
            ++failures;                                                       \
        }                                                                     \
    } while (0)

static void testReadIntRetriesOnBadInput() {
    std::istringstream in("abc\n12abc\n-5\n\n7\n");
    std::ostringstream out;
    CHECK(readInt(in, out, "? ", 1, 10) == 7);
}

static void testReadDoubleAcceptsDecimalComma() {
    std::istringstream in("2,5\n");
    std::ostringstream out;
    CHECK(readDouble(in, out, "? ", 1.0, 6.0) == 2.5);
}

static void testEndOfInputThrows() {
    std::istringstream in("abc\n");  // one bad answer, then nothing
    std::ostringstream out;
    bool threw = false;
    try {
        readInt(in, out, "? ", 1, 10);
    } catch (const InputEnded&) {
        threw = true;
    }
    CHECK(threw);
}

static void testReadChoiceIsCaseInsensitive() {
    std::istringstream in("x\nyes\nt\n");
    std::ostringstream out;
    CHECK(readChoice(in, out, "? ", "ST") == 'T');
}

static void testGradeDescriptor() {
    CHECK(Student::gradeDescriptor(1.0) == "Sehr gut");
    CHECK(Student::gradeDescriptor(2.3) == "Gut");
    CHECK(Student::gradeDescriptor(4.0) == "Ausreichend");
    CHECK(Student::gradeDescriptor(4.3) == "Mangelhaft");
    CHECK(Student::gradeDescriptor(6.0) == "Ungenügend");
}

static void testStudentGrades() {
    Student s;
    CHECK(s.averageGrade() == 0.0);
    CHECK(s.addGrade(1.0));
    CHECK(s.addGrade(3.0));
    CHECK(!s.addGrade(0.5));
    CHECK(!s.addGrade(7.0));
    CHECK(s.getGrades().size() == 2);
    CHECK(s.averageGrade() == 2.0);
}

static void testPushDataSkipsInvalidGrades() {
    Student s;
    std::istringstream in("zero\n2\n7\n1.3\nabc\n2,7\n");
    std::ostringstream out;
    s.pushData(in, out);
    CHECK(s.getGrades().size() == 2);
    CHECK(s.averageGrade() == 2.0);
    CHECK(out.str().find("Average Grade: 2.00 (Gut)") != std::string::npos);
}

static void testTeacherApprovesGradesOneToFour() {
    Teacher t;
    std::istringstream in("3\nAnna Mueller\n2\nBob Weber\n5\nCara\n4\n");
    std::ostringstream out;
    t.insertStudents(in, out);
    CHECK(t.getStudents().size() == 2);
    CHECK(t.getStudents()[0] == "Anna Mueller");
    CHECK(t.getStudents()[1] == "Cara");
    CHECK(Teacher::isApproved(4.0));
    CHECK(!Teacher::isApproved(4.1));
}

static void testFullName() {
    Student s;
    s.setName("Anna");
    CHECK(s.getFullName() == "Anna");
    s.setSurname("Mueller");
    CHECK(s.getFullName() == "Anna Mueller");
}

int main() {
    testReadIntRetriesOnBadInput();
    testReadDoubleAcceptsDecimalComma();
    testEndOfInputThrows();
    testReadChoiceIsCaseInsensitive();
    testGradeDescriptor();
    testStudentGrades();
    testPushDataSkipsInvalidGrades();
    testTeacherApprovesGradesOneToFour();
    testFullName();

    if (failures == 0) {
        std::cout << "All tests passed." << std::endl;
        return 0;
    }
    std::cout << failures << " check(s) failed." << std::endl;
    return 1;
}
