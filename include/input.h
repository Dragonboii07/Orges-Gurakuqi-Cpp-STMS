#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <iostream>
#include <stdexcept>
#include <string>

// Thrown when the input stream ends (Ctrl+Z / Ctrl+D or end of a piped file),
// so the program can stop cleanly instead of looping forever.
struct InputEnded : std::runtime_error {
    InputEnded() : std::runtime_error("input ended") {}
};

// Every helper reads a whole line, so a bad answer never stays stuck in the
// stream, and keeps asking until the answer is valid.
std::string readLine(std::istream& in, std::ostream& out, const std::string& prompt);
std::string readNonEmptyLine(std::istream& in, std::ostream& out, const std::string& prompt);
int readInt(std::istream& in, std::ostream& out, const std::string& prompt, int min, int max);
double readDouble(std::istream& in, std::ostream& out, const std::string& prompt, double min, double max);
char readChoice(std::istream& in, std::ostream& out, const std::string& prompt, const std::string& choices);

#endif // INPUT_H_INCLUDED
