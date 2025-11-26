#ifndef Stack_h
#define Stack_h

#include <iostream>

class Stack	{
public:
	Stack(int size);
	~Stack();

	void push(int data);
	int pop();
	int peek();
	bool isEmpty();


private:
	int* stack;
	int size;
	int top;
	
};
#endif
