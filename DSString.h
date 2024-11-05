#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>

class DSString {
private:
    char* data;
    int len;

    void copyData(const char* str);  // Helper function to copy C-string data

public:
    DSString();                          // Default constructor
    DSString(const char* str);            // Constructor from C-string
    DSString(const DSString& other);      // Copy constructor
    ~DSString();                         // Destructor

    DSString& operator=(const DSString& other); // Copy assignment operator
    bool operator==(const DSString& other) const;
    bool operator<(const DSString& other) const;
    char& operator[](int index);

    int length() const;                   // Returns the length of the string
    const char* c_str() const;            // Method to get C-string

    friend std::ostream& operator<<(std::ostream& os, const DSString& str);
};

#endif // DSSTRING_H
