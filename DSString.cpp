#include "DSString.h"
#include <cstring>

// Default constructor
DSString::DSString() : data(nullptr), len(0) {}

// Constructor from C-string
DSString::DSString(const char* str) {
    if (str) {
        len = strlen(str);
        data = new char[len + 1];
        strcpy(data, str);
    } else {
        data = nullptr;
        len = 0;
    }
}

// Copy constructor
DSString::DSString(const DSString& other) : len(other.len) {
    data = new char[len + 1];
    strcpy(data, other.data);
}

// Destructor
DSString::~DSString() {
    delete[] data;
}

// Copy assignment operator
DSString& DSString::operator=(const DSString& other) {
    if (this != &other) {
        delete[] data;
        len = other.len;
        data = new char[len + 1];
        strcpy(data, other.data);
    }
    return *this;
}

// Equality operator
bool DSString::operator==(const DSString& other) const {
    return strcmp(data, other.data) == 0;
}

// Less than operator (for use in map comparisons)
bool DSString::operator<(const DSString& other) const {
    return strcmp(data, other.data) < 0;
}

// Access operator
char& DSString::operator[](int index) {
    return data[index];
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
