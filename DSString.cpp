#include "DSString.h"

// Default constructor
DSString::DSString() : data(nullptr), len(0) {}

// Constructor from C-string
DSString::DSString(const char* str) {
    copyData(str);
}

// Copy constructor
DSString::DSString(const DSString& other) {
    copyData(other.data);
}

// Destructor
DSString::~DSString() {
    delete[] data;
}

// Helper function to copy data from a C-string
void DSString::copyData(const char* str) {
    if (str) {
        // Calculate the length manually
        len = 0;
        while (str[len] != '\0') {
            len++;
        }
        data = new char[len + 1];
        for (int i = 0; i < len; i++) {
            data[i] = str[i];
        }
        data[len] = '\0';
    } else {
        data = nullptr;
        len = 0;
    }
}

// Copy assignment operator
DSString& DSString::operator=(const DSString& other) {
    if (this != &other) {
        delete[] data;
        copyData(other.data);
    }
    return *this;
}

// Equality operator
bool DSString::operator==(const DSString& other) const {
    if (len != other.len) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

// Less than operator (for use in map comparisons)
bool DSString::operator<(const DSString& other) const {
    int minLen = len < other.len ? len : other.len;
    for (int i = 0; i < minLen; i++) {
        if (data[i] < other.data[i]) {
            return true;
        } else if (data[i] > other.data[i]) {
            return false;
        }
    }
    return len < other.len;
}

// Access operator
char& DSString::operator[](int index) {
    return data[index];
}

// Length of the string
int DSString::length() const {
    return len;
}

// c_str() method for C-string compatibility
const char* DSString::c_str() const {
    return data;
}

// Stream insertion operator (optional, for easy printing)
std::ostream& operator<<(std::ostream& os, const DSString& str) {
    os << str.data;
    return os;
}
