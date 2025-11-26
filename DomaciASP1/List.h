#ifndef List_h
#define List_h

#include <string>
#include <iostream>
#include "NodeList.h"


template <typename T>
class List {
public:
	List();

	void addElem(T info);
	void setElem(T info, int index);

	int getIndex(T info);
	int getNumOfElem() const;
	T getElem(int index) const;


	void removeElem(T info);
	void deleteList();
	void print();

private:
	int numOfElem;
	NodeList<T>* head;

};


template<typename T>
List<T>::List() : numOfElem(0), head(nullptr) {}

template <typename T>
void List<T>::addElem(T info) {
	NodeList<T>* newNode = new NodeList<T>(info);
	if (head == nullptr) head = newNode;
	else {
		NodeList<T>* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	numOfElem++;
}

template <typename T>
int List<T>::getIndex(T info) {
	NodeList<T>* temp = head;
	int counter = 0;
	while (temp) {
		if (temp->info == info) {
			return counter;
		}
		counter++;
		temp = temp->next;
	}
	std::cout << "Error - Element " << info << " not found." << std::endl;
	return -1;
}


template <typename T>
void List<T>::setElem(T info, int index) {
	NodeList<T>* temp = head;
	int counter = 0;
	while (temp) {
		if (counter == index) {
			temp->info = info;
			return;
		}
		counter++;
		temp = temp->next;
	}
	std::cout << "Error - index " << index << " out of range." << std::endl;
	return; // ako ne nadje taj elem
}


template <typename T>
T List<T>::getElem(int index) const {
	if (index < 0 or index >= numOfElem) {
		std::cout << "Error - index out of range." << std::endl;
		return T();
	}
	NodeList<T>* temp = head;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return temp->info;
}

template <typename T>
int List<T>::getNumOfElem() const {
	return numOfElem;
}

template <typename T>
void List<T>::print() {
	NodeList<T>* temp = head;
	while (temp) {
		std::cout << temp->info << ' ';
		temp = temp->next;
	}
	std::cout << std::endl;
}

template <typename T>
void List<T>::removeElem(T info) {
	NodeList<T>* curr = head;
	NodeList<T>* prev = nullptr;
	while (curr) {
		if (curr->info == info) {
			if (curr == head) {
				head = curr->next;	
			}
			else {
				prev->next = curr->next;
			}
			delete curr;
			numOfElem--;
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	std::cout << "Error - Element " << info << " not found." << std::endl;
	return;
}

template <typename T>
void List<T>::deleteList() {
	if (numOfElem == 0) return;
	NodeList<T>* curr = head;
	NodeList<T>* temp = head;
	while (curr != nullptr) {
		curr = curr->next;
		delete temp;
		temp = curr;
	}
	numOfElem = 0;
	head = nullptr;

}

#endif
