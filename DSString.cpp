//
// Created by mark on 6/2/2021.
//

#include "DSString.h"

DSString::DSString() { //default constructor
    str = nullptr;
}

DSString::DSString(const char* s) {
    str = new char[strlen(s) + 1];
    strcpy(str, s);
}

DSString::DSString(const DSString& arg) {
    str = new char[strlen(arg.str) + 1];
    strcpy(str, arg.str);
}

DSString::~DSString() { //destructor
    delete[] str;
}

DSString& DSString::operator=(const char* s) {
    if (str != nullptr) {
        delete[] str;
    }
    str = new char[strlen(s) + 1];
    strcpy(str, s);
    return *this;
}

DSString& DSString::operator=(const DSString& arg) {
    if (str != nullptr) {
        delete[] str;
    }
    str = new char[strlen(arg.str) + 1];
    strcpy(str, arg.str);
    return *this;
}

DSString DSString::operator+(const DSString& arg) const{
    if (str == nullptr) {
        char* temp = new char[strlen(arg.str) + 1];
        strcpy(temp, arg.str);
        DSString temp2(temp);
        delete[] temp;
        return temp2;
    } else {
        int length = strlen(str);
        char* temp = new char[length + 1 + strlen(arg.str)];
        strcpy(temp, str);
        strcat(temp, arg.str);
        DSString temp2(temp);
        delete[] temp;
        return temp2;
    }
}

DSString DSString::operator+(const char* s) const{
    if (str == nullptr) {
        char* temp = new char[strlen(s) + 1];
        strcpy(temp, s);
        DSString temp2(temp);
        delete[] temp;
        return temp2;
    } else {
        int length = strlen(str);
        char* temp = new char[length + 1 + strlen(s)];
        strcpy(temp, str);
        strcat(temp, s);
        DSString temp2(temp);
        delete[] temp;
        return temp2;
    }

}


bool DSString::operator==(const DSString& arg) const{
    return strcmp(str, arg.str) == 0;
}

bool DSString::operator==(const char* s) const{
    return strcmp(str, s) == 0;
}

bool DSString::operator!=(const DSString& arg) const {
    return strcmp(str, arg.str) != 0;
}

bool DSString::operator!=(const char* s) const {
    return strcmp(str, s) != 0;
}

bool DSString::operator>(const DSString& arg) const{
    return strcmp(str, arg.str) > 0;
}

bool DSString::operator>(const char* s) const{
    return strcmp(str, s) > 0;
}

bool DSString::operator<(const DSString& arg) const{
    return strcmp(str, arg.str) < 0;
}

bool DSString::operator<(const char* s) const{
    return strcmp(str, s) < 0;
}

char& DSString::operator[](const int i) const{
    return str[i];
}

int DSString::getLength() const{ //returns the length of the DSString
    return strlen(str);
}

DSString DSString::substring(int start, int numChars) const{
    if (numChars > 0) { //prevents negative word lengths from occurring
        char *temp = new char[numChars + 1];
        strncpy(temp, str + start, numChars);
        temp[numChars] = '\0';

        DSString ss(temp);
        delete[] temp;
        return ss;
    }
    DSString temp("");
    return temp; //returns an empty string if a negative numChars is somehow passed to the function
}

char* DSString::c_str() const{
    return str; //returns the c string inside DSString
}

std::ostream& operator<<(std::ostream& output, const DSString& arg) {
    output << arg.str;
    return output;
}

std::istream &operator>>(std::istream& input, const DSString& arg) {
    input >> arg.str;
    return input;
}

int DSString::find(char c) const{ //this function finds the first location of a character within the DSString
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == c) {
            return i; //returns the first location of c
        }
    }
    return -1; //returns -1 if c is not within the DSString
}

int DSString::find(char c, int instance) const{ //this function finds the nth location of a character
    int j = 0;                                  //within the DSString (where n = instance)
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == c) {
            ++j;
            if (j == instance) {
                return i; //returns the nth location of c (where n = instance)
            }
        }
    }
    return -1; //returns -1 if c is not within the DSString 'instance' number of times
}

int DSString::count(char c) const{ //this functions counts how many times a character appears in the DSString
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == c) {
            count++;
        }
    }
    return count; //returns the number of instances of c
}

char DSString::end() const {
    return str[strlen(str) - 1]; //returns the last character in str
}

char DSString::beginning() const {
    return str[0]; //returns the first character in str
}

void DSString::lowercase() const { //lowercases all letters in the DSString
    for (int i = 0; i < strlen(str); i++) {
        if ((str[i] >= 65) && (str[i] <= 90)) { //activates if the character is an uppercase letter
            str[i] += 32; //converts the uppercase letter to a lowercase letter
        }
    }
}
