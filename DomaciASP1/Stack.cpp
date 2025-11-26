#include "Stack.h"

using namespace std;

Stack::Stack(int size): size(size), top(0) {
	stack = new int[size];
}

Stack::~Stack() {
	delete[] stack;
}

void Stack::push(int data) {
	if (top > size) {
		cout << "Error - stack overflow." << endl;
		return;
	}
	stack[top] = data;
	top++;
}

int Stack::pop() {
	if (isEmpty()) {
		cout << "Error - stack underflow." << endl;
		return -1;
	}
	top--;
	int temp = stack[top];
	
	return temp;
}

int Stack::peek() {
	if (isEmpty()) {
		cout << "Error - stack underflow." << endl;
		return -1;
	}
	return stack[top-1];
}

bool Stack::isEmpty() {
	if (top == 0) return true;
	else return false;
}






