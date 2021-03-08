#include <iostream>
#include "StackCalculator.hpp"


using namespace std;
/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-")
      return false;

    else if(s.size() > 1 && s[0] == '-')
      s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++){
      if(!isdigit(s[i]) && s[i] != '.')
        return false;
      if(s[i]=='.' && !point) point = true;
      else if(s[i]=='.' && point) return false;
    }

    return true;
}

StackCalculator::StackCalculator()
{
  //TODO:
  stackHead=NULL;
}

StackCalculator::~StackCalculator()
{
  //TODO:
  while(!isEmpty()) {
    pop();
  }
}

bool StackCalculator::isEmpty()
{
	//TODO:
  return (stackHead == NULL);
}

void StackCalculator::push(float number)
{
  Operand* nn = new Operand;
  nn->number = number;
  nn->next = NULL;
  nn->next = stackHead;
  stackHead = nn;
  //TODO:
}

void StackCalculator::pop()
{
	//TODO:
    if(!isEmpty())
    {
      Operand* temp = stackHead;
      stackHead = stackHead->next;
      delete temp;
      temp = NULL;
    }
    else
    {
        cout<<"Stack empty, cannot pop an item."<<endl;
    }
}

Operand* StackCalculator::peek()
{
	//TODO:
    if(!isEmpty())
        return stackHead;
    else{
        cout<<"Stack empty, cannot peek."<<endl;
        return nullptr;
    }
}

bool StackCalculator:: evaluate(string* s, int size)
{
    /*TODO: 1.scan the array from the end
            2.Use isNumber function to check if the input is an operand
            3.push all operands to the stack
            4.If operator take two element of from the stack,
              compute and put the result back in stack
            5.Handle the boundery cases as required.
            6.Read the writeup for more details
    */
    for (int i = size-1; i >= 0; i--) {
        if (isNumber(s[i])) push(stof(s[i]));
        else if (s[i] != "+" && s[i] != "*") {
            cout << "err: invalid operation" << endl;
            return false;
        }
        else {
            if (isEmpty()) {
              cout << "err: not enough operands" << endl;
              return false;
            }
            float val1 = peek()->number;
            pop();
            if (isEmpty()) {
              cout << "err: not enough operands" << endl;
              return false;
            }
            float val2 = peek()->number;
            pop();
            if (s[i] == "*") {
              push(val1 * val2);
            }
            else {
              push(val1 + val2);
            }
        }
    }
		return true;
}
