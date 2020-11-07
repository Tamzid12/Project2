/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>  
#include <iomanip>
#include <fstream>
#include "mystack.h"
 
using namespace std; 

// this function is to check the validity of the passed in epxressions, and 
// pushing them in to the stack is they are valid.

void evaluateExpression(ifstream& inpF, ofstream& outF, 
                        stackType<double>& stack,
                        char& ch, bool& isExpOk);
                       
// this function is to set what each operators (+,-,*,/) do, and set the 2nd 
// and 1st value of the expression equal to the top of the stack. 

void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk);
void discardExp(ifstream& in, ofstream& out, char& ch);

// this function is to print out the final result into the output file.We take 
// isExpOk as a parameter to check the validity of the expressions before
//printing.

void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk);

int main()
{
    bool expressionOk;
    char ch;
    stackType<double> stack(100);
    ifstream infile; // for input file
    ofstream outfile; // for output file
 
    infile.open("RpnData.txt"); // the input file

    if (!infile) // if the file is not found, terminate the program and print an 
    // error message.
    {
        cout << "Cannot open the input file. "
             << "Program terminates!" << endl;
        return 1;
    }
     
    outfile.open("RpnOutput.txt"); // the output file to print out all the final
    //result

    outfile << fixed << showpoint;
    outfile << setprecision(2); // to round the answers to 2 decimal places.

    infile >> ch;
    while (infile)
    {
        stack.initializeStack();
        expressionOk = true; // set expressionOk to true
        outfile << ch;

        evaluateExpression(infile, outfile, stack, ch, 
                           expressionOk); // pass the expressions to the evaluateExpression
                           // function to check their validity
        printResult(outfile, stack, expressionOk); // if they are valid, pass
        // the expressions to the printResult function to print them out to 
        // the output file
        infile >> ch; //begin processing the next expression
    } //end while 

    infile.close(); // close the input file to prevent memory leak
    outfile.close(); // close the output file to prevent memory leak

    return 0;

} //end main


void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)
{
    double num;

    while (ch != '=')
    {
        switch (ch)
        {
        case '#': 
            inpF >> num;
            outF << num << " ";
            if (!stack.isFullStack()) // as long as the stack is not full, keep
            // pushing in the numbers into the stack.
                stack.push(num);
            else
            {
                cout << "Stack overflow. " // if the stack is full, print out
                // an error message and terminate the program.
                     << "Program terminates!" << endl;
                exit(0);  //terminate the program
            }

            break;
        default: 
            evaluateOpr(outF, stack, ch, isExpOk);
        }//end switch

        if (isExpOk) //if there is no error
        {
            inpF >> ch;
            outF << ch;

            if (ch != '#')
                outF << " ";
        }
        else
            discardExp(inpF, outF, ch);
    } //end while (!= '=')
} //end evaluateExpression


void evaluateOpr(ofstream& out, stackType<double>& stack,
              char& ch, bool& isExpOk)
{
    double op1, op2;

    if (stack.isEmptyStack()) // if the stack is empty, print out an error message
    {
        out << " (Not enough operands)";
        isExpOk = false; // since there is no element in the stack
        // isExpOk is set to false
    }
    else
    {
        op2 = stack.top(); // set the top equal to the 2nd value of the expression
        stack.pop(); // pop the stack

        if (stack.isEmptyStack()) // if the stack is empty, print out an error.
        {
            out << " (Not enough operands)";
            isExpOk = false; // set isExpOk equal to false
        }
        else
        {
            op1 = stack.top(); // set the top equal to the 1st value of the expression
            stack.pop(); // pop the stack

            switch (ch)
            {
            case '+': // set what the + operator does
                stack.push(op1 + op2);
                break;
            case '-': // set what the - operator does
                stack.push(op1 - op2);
                break;
            case '*': // set what the * operator does
                stack.push(op1 * op2);
                break;
            case '/': // set what the / operator does
                if (op2 != 0) // we have to check if the 2nd value is 0, if it 
                // is not, then divide
                    stack.push(op1 / op2);
                else
                {
                    out << " (Division by 0)"; // if the 2nd value is 0, set \
                    // isExpOk equal to false
                    isExpOk = false;
                }
                break;
            default:  
                out << " (Illegal operator)";
                isExpOk = false;
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr


void discardExp(ifstream& in, ofstream& out, char& ch)
{
    while (ch != '=')
    {
        in.get(ch);
        out << ch;
    }
} //end discardExp

void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk)
{
    double result;

    if (isExpOk) //if no error, print the result
    {
        if (!stack.isEmptyStack()) // if the stack is not empty, continue;
        {
            result = stack.top(); // set result equal to top
            stack.pop(); // pop the stack

            if (stack.isEmptyStack())
                outF << result << endl;
                
                // if any of the above tests fail, print out an according Error
                // message
            else
                outF << " (Error: Too many operands)" << endl;
        } //end if
        else
            outF << " (Error in the expression)" << endl;
    }
    else
        outF << " (Error in the expression)" << endl;

    outF << "_________________________________" 
         << endl << endl;
} //end printResult


