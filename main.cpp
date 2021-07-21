/*
Big Number Calculator
Application string functions go in CalculatorApp.h
Math functions go in main
*/
#include <iostream>
#include <string>
#include <vector>

#include "CalculatorApp.h"

// Function Prototypes
int isPrecedence(const LStack<char> &operatorStack, char currentOperator);
int checkFunctionType(std::string userInput);
bool verifyMathInput(std::string userInput);
int verifyStringInput(std::string userInput);
bool convertInfixToPostfix(std::string userInput, LQueue<std::string> &postfixQueue);
bool postfixEval(LQueue<std::string> &postfixQueue, std::string &result);
std::string doMath(std::string operand1, std::string operand2, int operationType);
void displayAnswer(std::string result, bool validInput);
void displayError(std::string errorMessage);


int main() {
    std::string userInput, operand1, operand2, result;
    int functionType, functionTypeStr, functionTypeInt;
    char oprt; // operator
    bool validInput;
    LQueue<std::string> postfixQueue;
    std::cout << "Command Line Calculator Application" << std::endl;
    std::cout << "Made by Neal A. 4/19/2021" << std::endl;
    std::cout << "Enter math operation. CTRL+C to exit or Type \"quit\"" << std::endl;
    while(1) {
        getline(std::cin, userInput);
        functionType = checkFunctionType(userInput);
        if(functionType == 0) {
            if(verifyMathInput(userInput)) {
                convertInfixToPostfix(userInput, postfixQueue);
                validInput = postfixEval(postfixQueue, result);
                displayAnswer(result, validInput);
            }
        }
        else if(functionType == 1) {
            functionTypeStr = verifyStringInput(userInput);
            switch(functionTypeStr) {
                case(0): // get back to string functions later
                case(1):
                    return 0;
                    break;
                case(2):
                    commasOn = true;
                    break;
                case(3):
                    commasOn = false;
                    break;
                case(4):
                    clearScreen();
                    break;
                default:
                    std::cout << "Invalid Function" << std::endl;
                    break;
            }
        } 
        else {
            std::cout << "Invalid Input" << std::endl;
        }
        while(!postfixQueue.isEmpty()) {
            postfixQueue.popFront();
        }
    }
}

/**********************************************
Determine if string is a userinput
Return types: 
-1 Invalid Input
0 Math Function
1 String function
**********************************************/
int checkFunctionType(std::string userInput) {
    if(isDigit(userInput[0]) || userInput[0] == '(' || userInput[0] == '-') return 0;
    else if(isLetter(userInput[0])) return 1;
    else return -1;
}

bool verifyMathInput(std::string userInput) {
    for(std::string::size_type i = 0; i < userInput.length(); i++) {
        if(!isDigit(userInput[i]) && !isOperator(userInput[i]) && userInput[i] != ' ') {
            std::cout << "Invalid Character \"" << userInput[i] << "\"" << std::endl;
            return false;
        }
    }
    return true;
}

int verifyStringInput(std::string userInput) {
    std::string appFunctionsStr[5] = {"quit", "exit", "commas: on", "commas: off", "clear"};
    for(std::string::size_type i = 0; i < userInput.length(); i++) { // lower all chars
        userInput[i] = convLower(userInput[i]);
    }
    for(int i = 0; i < 5; i++) {
        if(userInput == appFunctionsStr[i]) return i;
    }
    return -1;
}


/****************************
-1 if neither
0 if current precedes (*, +)
1 if the same
2 Special parenthesis case
do not pop stack
*****************************/
int isPrecedence(const LStack<char> &operatorStack, char currentOperator) {
    if(operatorStack.isEmpty()) return -1;
    char previousOperator = operatorStack.getTop();
    if(currentOperator == previousOperator) return 1; 
    switch(previousOperator) {
        case('('):
            return -1; // do nothing special case
        case('^'):
            if(currentOperator == '(') return -1;
            return 0; // 2nd most likely to precede so will return 0 
        case('*'):
        case('/'):
        case('%'):
            if(currentOperator == '*' || currentOperator == '/' || currentOperator == '%') return 1;
            if(currentOperator == '+' || currentOperator == '-') return 0;
            return -1;
        case('+'):
        case('-'):
            if(currentOperator == '+' || currentOperator == '-') return 1;
            return -1;
    }
    return -1;
}
// (25+25)
bool convertInfixToPostfix(std::string userInput, LQueue<std::string> &postfixQueue) {
    LStack<char> operatorStack;
    std::string operatorStr, operandStr; // initialize as empty string
    char previousOperator, operatorCh;
    for(std::string::size_type i = 0; i < userInput.length(); i++) {
        if(userInput[i] == ' ' || userInput[i] == ',') continue; // ignore any spaces
        if(isDigit(userInput[i])) {
            operandStr += userInput[i];
            continue; // break one loop iteration to continue appending digit to string
        }
        if(isOperator(userInput[i])) {
            if(operandStr.length() > 0) { // push back the operand if not empty 
                postfixQueue.addRear(operandStr);
                operandStr = ""; // reset the operand
            }
            if(userInput[i] == ')') { // parenthesis special case
                operatorCh = operatorStack.pop();
                while(operatorCh != '(') { // if we encounter the closing bracket remove all operators from the stack
                    postfixQueue.addRear(convCharToString(operatorCh));
                    operatorCh = operatorStack.pop();
                }
                continue;
            }
            switch(isPrecedence(operatorStack, userInput[i])) {
                case(0): // * + do not pop the stack
                case(1): // + -
                    postfixQueue.addRear(convCharToString(operatorStack.pop()));
                    operatorStack.push(userInput[i]); // replace with the next element
                    break;
                case(-1):
                    operatorStack.push(userInput[i]);
                    break;
            }
            if(!isOperator(userInput[i]) && !isDigit(userInput[i]) && !isOperator(userInput[i])) {
                std::cout << "Invalid character: \"" << userInput[i] << "\" found" << std::endl;
                return false;
            }
        }
    } // end of for loop
    if(operandStr.length() > 0) postfixQueue.addRear(operandStr);
    while(!operatorStack.isEmpty()) {
        postfixQueue.addRear(convCharToString(operatorStack.pop()));
    }
    // postfixQueue.displayAll();
    return true;
}

/****************
0 - add
1 - subtract
2 - multiply
3 - divide
4 - modulo
5 - caret
****************/
int chooseOperation(char ch) {
    switch(ch) {
        case('+'): return 0;
        case('-'): return 1;
        case('*'): return 2;
        case('/'): return 3;
        case('%'): return 4;
        case('^'): return 5;
    }
    return -1; // error
}

/*************************************
Push and pop operands and opeartors into stack
Then call doMath function
**************************************/
bool postfixEval(LQueue<std::string> &postfixQueue, std::string &result) {
    LStack<std::string> postfixStack;
    std::string item, operand1, operand2;
    // std::cout << "pfix display: ";
    // postfixQueue.displayAll();
    while(!postfixQueue.isEmpty()) {
        item = postfixQueue.popFront();
        if(isMathOperator(item[0])) { // check but exclude parenthesis
            try {
                operand2 = postfixStack.pop();
                operand1 = postfixStack.pop();
                item = doMath(operand1, operand2, chooseOperation(item[0]));
            } catch (LStack<std::string>::stackUnderflow) {
                return false;
            }
        }
        postfixStack.push(item);
    }
    result = postfixStack.pop();
    if(!postfixStack.isEmpty()) {
        if(isOperator(result[0])) result = "Error: Too Many Operators";
        else result = "Error: Too many Operands";
        return false;
    }
    return true;
}

std::string doMath(std::string operand1_Str, std::string operand2_Str, int operationType) {
    long int res, operand1_Int, operand2_Int;
    operand1_Int = convStringToInt(operand1_Str);
    operand2_Int = convStringToInt(operand2_Str);
    std::string result;
    switch(operationType) {
        case(0): // add
            res = operand1_Int + operand2_Int;
            break;
        case(1):
            res = operand1_Int - operand2_Int;
            break;
        case(2):
            res = operand1_Int * operand2_Int;
            break;
        case(3):
            res = operand1_Int / operand2_Int;
            break;
        case(4):
            res = operand1_Int % operand2_Int;
            break;
        case(5):
            res = 1;
            for(long int i = 0; i < operand2_Int; i++) {
                res *= operand1_Int;
            }
            break;
    } 
    result = convIntToString(res);

    return result;
}

void displayAnswer(std::string result, bool validInput) {
    if(commasOn && validInput == true) {
        int ctr = 0;
        for(std::string::size_type i = 0; i < result.length(); i++) {
            if(ctr == 3) {
                result.insert(i, ",");
                ctr = 0;
                continue;
            }
        }
    }
    std::cout << result << std::endl;
}

void displayError(std::string errorMessage) {
    std::cout << errorMessage << std::endl;
}
