
//
//  main.cpp
//  Question2
//
//  Created by Tamzid chowdhury on 11/05/20.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include "mystack.h"

 
using namespace std;

//function to print the result to the output file

void printResult(ofstream& outF,stackType<double>& stack);

// function to set what each operator will do, and to read the inputs from the input file

double evaluatePrefix(string exprsn);

int main()
{
    char ch;
    stackType<double> stack(100); // size of the stack
    ifstream infile; // for input file
    ofstream outfile; // for output file
 
    infile.open("input.txt");

    if (!infile) // if the file is not found
    {
        cout << "Cannot open the input file. "
             << "Program terminates!" << endl;
        return 1;
    }
     
    outfile.open("output.txt"); // file to store the outputs

    outfile << fixed << showpoint;
    outfile << setprecision(2); // round all the answers to 2 decimal places

    infile >> ch;
    while (infile)
    {
        stack.initializeStack();
        outfile << ch;

        printResult(outfile, stack );
        infile >> ch; //begin processing the next expression
    } //end while

    infile.close(); // close files to prevent memory leaks
    outfile.close();

    return 0;

} //end main

bool isOperand(char c)
{
    // If the character is a digit then it must
    // be an operand
    return isdigit(c);
}

double evaluatePrefix(string exprsn, ofstream& out)
{
    stack<double> Stack;
  
    for (int j = exprsn.size() - 1; j >= 0; j--) {
  
        // Push operand to Stack
        // To convert exprsn[j] to digit subtract
        // '0' from exprsn[j].
        if (isOperand(exprsn[j]))
            Stack.push(exprsn[j] - '0');
  
        else {
  
            // Operator encountered
            // Pop two elements from Stack
            double o1 = Stack.top();
            Stack.pop();
            double o2 = Stack.top();
            Stack.pop();
  
            // Use switch case to operate on o1
            // and o2 and perform o1 O o2.
            switch (exprsn[j]) {
            case '+': // sets what the + operator will do
                Stack.push(o1 + o2);
                break;
            case '-': // sets what the - operator will do
                Stack.push(o1 - o2);
                break;
            case '*': // sets what the * operator will do
                Stack.push(o1 * o2);
                break;
            case '/':
                if (o2 != 0) // we have to make sure we are not divind by 0
                Stack.push(o1 / o2);
            else
            {
                out << " (Error! Division by 0)"; // if we dividing by 0, print out error message
                                }
                break;
            }
        }
    }
  
    return Stack.top();
}
  

void printResult(ofstream& outF, stackType<double>& stack )
{
    double result;

    
        if (!stack.isEmptyStack()) // checks if the stack is empty
        {
            result = stack.top();
            stack.pop();

            if (stack.isEmptyStack())
                outF << result << endl;
            else
                outF << " (Error: Too many operands)" << endl;
        } //end if
        else
            outF << " (Error in the expression)" << endl;
    outF << "_________________________________"
         << endl << endl;
} //end printResult
