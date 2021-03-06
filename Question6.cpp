//
//  main.cpp
//  Q6
//
//  Created by Tamzid chowdhury on 11/7/20.
//

#include <iostream>
#include <fstream>

using namespace std;

  
// A structure to represent a stack
class Stack
{
    public:
    int top;
    unsigned capacity;
    char* array;
};
  
// function to create a stack of given
// capacity. It initializes size of stack as 0
Stack* createStack(unsigned capacity)
{
    Stack* stack = new Stack();
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = new char[(stack->capacity * sizeof(char))];
    return stack;
}
  
// Stack is full when top is equal to the last index
int full (Stack* stack)
{ return stack->top == stack->capacity - 1; }
  
// Stack is empty when top is equal to -1
int empty(Stack* stack)
{ return stack->top == -1; }
  
// Function to add an item to stack.
// It increases top by 1
void push(Stack* stack, char item)
{
    if (full(stack))
        return;
    stack->array[++stack->top] = item;
}
  
// Function to remove an item from stack.
// It decreases top by 1
char pop(Stack* stack)
{
    if (Empty(stack))
        return -1;
    return stack->array[stack->top--];
}
  
// A stack based function to reverse a string
void reverseString(string str)
{
    stack <char> st;
    
    for ( int i=0; i<str.length(); i++){ // go until the stack has space
        if (str[i] != ' ')
        st.push(str[i]);
        
        else{
            while ( st.empty() == false ){ // as long as the stack is not empty
                cout << st.top();
                st.pop();
            }
            cout << " ";
        }
    }
    
    while ( st.empty() == false){
        cout<< st.top();
        st.pop();
    }
}
  
// Driver code
int main()
{
    ifstream infile;
    infile.open("input.txt"); // the input file
    if (infile.fail()){ // if the file isn't found.
        cout<< "No such file was found";
    }
    else{
        string str ;
        while(getline(infile,str)){ // reads each line from the input file.
            cout<< "The original string: " << str << endl;
            cout << "The Reversed String: ";
            reverseString(str);
            cout<< endl;
        }
        infile.close(); // close to prevent memory leaks.
    }
    
  
    return 0;
}
