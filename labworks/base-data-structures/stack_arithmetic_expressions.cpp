#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#define MAX_SIZE 1000

using namespace std;

typedef struct OperandStack {
    char* buffer;
    size_t top;
    size_t maxSize;
} operand_stack_t;

void newStack(operand_stack_t* stack, size_t maxSize) {
    stack -> buffer = (char*) malloc(maxSize*sizeof(char));
    stack -> maxSize = maxSize;
    stack -> top = 0;
}

bool isEmpty(operand_stack_t* stack) {
    return stack -> top == 0;
}

bool isFull(operand_stack_t* stack) {
    return stack -> top == stack -> maxSize;
}

void pushValue(operand_stack_t* stack, char value) {
    if (!(isFull(stack))) {
        stack -> buffer[stack -> top] = value;
        stack -> top++;
    }
}

char getValue(operand_stack_t* stack) {
    return stack -> buffer[stack -> top - 1];
}

void popValue(operand_stack_t* stack) {
    if (!(isEmpty(stack))) {
        stack -> top--;
    }
}

bool isOperator(char symbol) {
    char signs[] = {'+', '-', '/', '*'};
    for (int i = 0; i < 4; i++) {
        if (signs[i] == symbol)
            return true;
    }
    return false;
}

bool isBracket(char symbol) {
    return symbol == '(' || symbol == ')';
}

vector<string> getPolishExpressionArray(string PolishExpression) {
    vector<string> tokens;
    string token;
    for (char c : PolishExpression) {
        if (c == ' ') {
            tokens.push_back(token);
            token.clear();
        } else {
            token += c;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}
vector<string> getMathExpressionArray(string mathExpression) {
    vector<string> tokens;
    string token;
    for (char c : mathExpression) {
        if (isOperator(c) || isBracket(c)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, c));
        } else if (c != ' ') {
            token += c;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

int getPriority(char c) {
    switch (c) {
        case '+': case '-':
            return 1;
        case '*': case '/':
            return 2;
    }
    return 0;
}

string reverseJoinStackBrackets(operand_stack_t* stack, string reversePolishNotation) {
    while (!isEmpty(stack) && getValue(stack) != '(') {
        reversePolishNotation = reversePolishNotation + getValue(stack) + " ";
        popValue(stack);
    }
    popValue(stack);
    return reversePolishNotation;
}
string reverseJoinStack(operand_stack_t* stack, string reversePolishNotation, char sign) {
    while (!isEmpty(stack) && (getPriority(sign) <= getPriority(getValue(stack)))) {
        if (getValue(stack) != '(' && getValue(stack) != ')') {
            reversePolishNotation = reversePolishNotation + getValue(stack) + " ";
        }
        popValue(stack);
    }
    return reversePolishNotation;
}
int main() {
    // Input
    char line[MAX_SIZE];
    cin.getline(line, MAX_SIZE);

    // Math Expression
    string traditionalNotation = string(line);
    cout << "Expression: " << endl << traditionalNotation << endl;

    // Split out expression
    vector<string> tokens = getMathExpressionArray(traditionalNotation);

    // Initialize new stack
    operand_stack_t stack;
    newStack(&stack, MAX_SIZE);

    string reversePolishNotation = "";

    // '+' = '-' = 1
    // '*' = '/' = 2
    int priority = 0;

    // Iterate over tokens (partsOfExpression)
    for (int i = 0; i < tokens.size(); i++) {
        string token = tokens[i];

        // Check if this symbol is operator or bracket
        char sign = token.c_str()[0];

        if (token.length() == 1 && isOperator(sign)) { // Operators

            // if previous operator priority is bigger that priority of this operator
            if (getPriority(sign) <= priority) {
                // Join part with same and smaller priority
                reversePolishNotation = reverseJoinStack(&stack, reversePolishNotation, sign);
            }
            priority = getPriority(sign);
            pushValue(&stack, sign);
        } else if (token.length() == 1 && isBracket(sign)) { // Bracket

            // If we close brackets
            if (sign == ')') {

                // Join part with brackets
                reversePolishNotation = reverseJoinStackBrackets(&stack, reversePolishNotation);

                // Priority equals priority of last operand
                priority = getValue(&stack);
            }

            // If we open brackets
            else {
                // Put the bracket in stack
                pushValue(&stack, sign);

                // Set null priority
                priority = 0;
            }
        } else { // Number
            reversePolishNotation = reversePolishNotation + token + " ";
        }
    }

    // Join by all priorities from biggest to smallest
    reversePolishNotation = reverseJoinStack(&stack, reversePolishNotation, '*');
    reversePolishNotation = reverseJoinStack(&stack, reversePolishNotation, '+');

    // Output
    cout << "Reverse Polish Notation: " << endl << reversePolishNotation << endl;

    vector<string> polishExpression = getPolishExpressionArray(reversePolishNotation);

    for (int i = 0; i < polishExpression.size(); i++) {
        // Find sign
        char sign = polishExpression[i].c_str()[0];
        if (isOperator(sign) && polishExpression[i].length() == 1) {
            long long int firstOperand = stoll(polishExpression[i-2]);
            long long int secondOperand = stoll(polishExpression[i-1]);
            long long int result;
            switch (sign) {
                case '+':
                    result = firstOperand + secondOperand;
                    break;
                case '-':
                    result = firstOperand - secondOperand;
                    break;
                case '*':
                    result = firstOperand * secondOperand;
                    break;
                case '/':
                    result = firstOperand / secondOperand;
                    break;
            }

            // Delete first and second previous operands and operator in front
            polishExpression.erase(polishExpression.cbegin() + i - 2, polishExpression.cbegin() + i + 1);
            // Insert new value
            polishExpression.insert(polishExpression.cbegin() + i - 2, to_string(result));
            // Move on 3 steps back
            i -= 3;
        }
    }
    cout << "Result:" << endl << stoll(polishExpression[0]);
    return 0;
}