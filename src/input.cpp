#include "input.h"

#include <cctype>
#include <sstream>

using namespace std;

static string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

string readLine(istream& in, ostream& out, const string& prompt) {
    out << prompt;
    string line;
    if (!getline(in, line)) throw InputEnded();
    return trim(line);
}

string readNonEmptyLine(istream& in, ostream& out, const string& prompt) {
    while (true) {
        string line = readLine(in, out, prompt);
        if (!line.empty()) return line;
        out << "  This field cannot be empty." << endl;
    }
}

// parses the whole line as a T; "12abc" or "" are rejected
template <typename T>
static bool parseNumber(const string& text, T& value) {
    istringstream ss(text);
    ss >> value;
    return ss && (ss >> ws).eof();
}

int readInt(istream& in, ostream& out, const string& prompt, int min, int max) {
    while (true) {
        int value;
        if (parseNumber(readLine(in, out, prompt), value) && value >= min && value <= max) {
            return value;
        }
        out << "  Please enter a whole number between " << min << " and " << max << "." << endl;
    }
}

double readDouble(istream& in, ostream& out, const string& prompt, double min, double max) {
    while (true) {
        string text = readLine(in, out, prompt);
        // accept a German-style decimal comma, e.g. 2,3
        for (char& c : text) {
            if (c == ',') c = '.';
        }
        double value;
        if (parseNumber(text, value) && value >= min && value <= max) {
            return value;
        }
        out << "  Please enter a number between " << min << " and " << max << "." << endl;
    }
}

char readChoice(istream& in, ostream& out, const string& prompt, const string& choices) {
    while (true) {
        string answer = readLine(in, out, prompt);
        if (answer.size() == 1) {
            char c = static_cast<char>(toupper(static_cast<unsigned char>(answer[0])));
            if (choices.find(c) != string::npos) return c;
        }
        out << "  Please type one of: ";
        for (size_t i = 0; i < choices.size(); ++i) {
            out << (i ? ", " : "") << choices[i];
        }
        out << "." << endl;
    }
}
