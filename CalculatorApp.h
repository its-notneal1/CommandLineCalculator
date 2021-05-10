#ifndef CALCULATORAPP_H
#define CALCULATORAPP_H
// Header file for application processes related to display
// Math functions are located in main
#include <iostream> // std::cout 
#include <string> // std::string
#include <fstream> // library used to view user settings
#include <stdlib.h> // clear screen
#include <cstdlib> // exit

#include "library/LQueue.h"
#include "library/LStack.h"

bool commasOn = false; // if commas will be printed for outputs

// String functions
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    std::cout << "Large Number Calculator Application" << std::endl;
    std::cout << "Author: Neal Archival" << std::endl;
    std::cout << "Enter math operation. CTRL+C to end or Type \"quit\"" << std::endl;
}

void exitApplication() {
    exit(0); // do not exit with errors
}

int commaFunction(std::string command) {
    if(command == "commas") {
        std::cout << "Type: \"commas: on\" or \"commas: off\"" << std::endl; 
    }
    if(command == "on") {
        return 0; // return true commas on
    } else if (command == "off") {
        return 1; // false commas are off
    } else {
        std::cout << "Invalid Comma Setting. " << std::endl;
        return -1;
    }
}

// Int, Char, and Str functions

// Convert a single digit into character. Pass single digit integer to convert
char convIntToChar(int n) {
    if(n > 9 || n < -9) return (n%10) + '0'; // only return the right most digit
    else if(n < 0) n *= -1; // convert to positive
    return n + '0';
}

// Convert a character digit into integer
int convCharToInt(char ch) {
    return ch - '0';
}

//Convert a character into lowercase
char convLower(char ch) {
    if(ch >= 65 && ch <= 90) return ch + 32;
    return ch;
}

char convUpper(char ch) {
    if(ch >= 97 && ch <= 122) return ch - 32;
    return ch;
}

bool isDigit(char ch) {
    if(ch >= 48 && ch <= 57) return true;
    return false;
}

std::string convCharToString(char ch) {
    std::string str = "";
    str += ch;
    return str;
}

long int convStringToInt(std::string numberStr) {
    long int result = convCharToInt(numberStr[numberStr.length() - 1]);
    long int increment, tens = 1;
    int endIndex = 0;
    if(numberStr[0] == '-') {
        endIndex = 1;
    }
    for(int i = numberStr.length() - 2; i >= 0; i--) {
        tens *= 10;
        increment = tens * convCharToInt(numberStr[i]);
        result += increment;
    }
    if(endIndex == -1) return result * -1;
    return result;
}

std::string convIntToString(long int n) {
    std::string result;
    if(n == 0) return "0";
    LStack<char> numberList;
    if(n < 0) result += '-';
    while(n != 0) {
        numberList.push(convIntToChar(n % 10));
        n /= 10;
    }
    while(!numberList.isEmpty()) result += numberList.pop();
    return result;
}

bool isOperator(char ch) {
    switch(ch) {
        case('+'):
        case('-'):
        case('/'):
        case('*'):
        case('%'):
        case('^'): 
        case('('):
        case(')'):
            return true;
            break;
        default:
            return false;
            break;
    }
}

// Excluding parenthesis
bool isMathOperator(char ch) {
    switch(ch) {
        case('+'):
        case('-'):
        case('*'):
        case('/'):
        case('^'):
        case('%'):
            return true;
        default:
            return false;
    }
}

bool isParenthesis(char ch) {
    switch(ch) {
        case('('):
        case(')'):
            return true;
        default:
            return false;
    }
}

bool isLetter(char ch) {
    if(ch >= 65 && ch <= 90) { // check if lower case
        return true;
    } else if(ch >= 97 && ch <= 122) { // check if upper case
        return true;
    } else {
        return false;
    }
}


// appFunctionsStr

#endif