# Student & Teacher Management System (C++)

A command-line C++ program that models `Person`, `Student` and `Teacher`
classes. Students enter their grades and get a report on the German grading
scale; teachers enter their students' grades and get a list of who passed.

## Features

* **Student mode**: name, surname, age, faculty and class, then any number of
  grades with a summary report and average
* **Teacher mode**: name, surname, age, title and number of classes, then a
  registry of students where only grades 1-4 are approved
* **German grading scale**: 1.0 (best) to 6.0 (worst), with the matching
  descriptions (Sehr gut, Gut, Befriedigend, Ausreichend, Mangelhaft, Ungenügend);
  decimal commas such as `2,3` are accepted
* **Robust input**: every answer is checked and asked again if it is invalid
  (for example letters where a number is expected), and the program exits
  cleanly when the input ends
* Unit tests for the input handling and the grade logic

## Project structure

```
├── include/
│   ├── input.h        # input helpers: read and validate one answer
│   ├── person.h       # Person base class
│   ├── student.h      # Student class
│   └── teacher.h      # Teacher class
├── src/
│   ├── main.cpp       # menu and forms
│   ├── input.cpp
│   ├── person.cpp
│   ├── student.cpp
│   └── teacher.cpp
├── tests/
│   └── stms_tests.cpp # unit tests
├── CMakeLists.txt     # CMake build
├── run.bat            # build and run on Windows with one double-click
├── Orges_Gurakuqi_C++_Project.cbp  # Code::Blocks project
└── .vscode/           # VS Code build and debug settings
```

## Class hierarchy

```
Person (name, surname, age)
├── Student (faculty, class, grades)
└── Teacher (title, number of classes, approved students)
```

## Building

Any C++17 compiler works: g++ (MinGW-w64 / MSYS2 on Windows), clang++ or MSVC.

### Windows, quickest way

Double-click `run.bat`, or run it from a terminal in the project folder. It
builds `bin\Debug\project.exe` with g++ and starts it.

### VS Code

Open the folder, press `Ctrl+Shift+B` to build and `F5` to run with the
debugger. The settings expect MSYS2 in `C:\msys64\ucrt64`; change the paths in
`.vscode/` if your compiler is somewhere else.

### Code::Blocks

Open `Orges_Gurakuqi_C++_Project.cbp` and press Build and run (`F9`).

### Command line (g++)

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o stms
./stms
```

### CMake (also builds the tests)

```bash
cmake -S . -B build
cmake --build build
./build/stms            # on Windows with Visual Studio: build\Debug\stms.exe
```

## Running the tests

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Usage example

```
Are you a student (S) or a teacher (T)? T

--- TEACHER INFORMATION FORM ---
Name: John
Surname: Smith
Age: 35
Title (Professor/Dr./Instructor): Dr.
Number of Classes: 2

--- APPROVED STUDENTS REGISTRY ---
(Only students with German grade 1-4 will be approved)
How many students are there? 2
Student 1 name: Anna Mueller
German grade for this student (1-6): 2
  -> Anna Mueller approved (grade 2).
Student 2 name: Bob Weber
German grade for this student (1-6): 5
  -> Bob Weber not approved (grade 5 - failing).

--- APPROVED STUDENTS LIST ---
Approved students:
  1. Anna Mueller
```

## Credits

Designed and built by Orges Gurakuqi: the class hierarchy, the student and
teacher forms and the German grading logic.

I used an AI coding assistant (Claude) to review and polish the project. It
helped me fix the program getting stuck in an endless loop on invalid input,
move the input checks into one place, repair the Code::Blocks and VS Code
build settings, add a CMake build and write the tests.

## License

This project is licensed under the MIT License - see [LICENSE](LICENSE) for
details.
