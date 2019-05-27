#pragma once

#include <iostream>

template <class T>
struct Node {
	T data;
	Node * next;
	Node * prev;
};

template<class T>
class Container {
public:
	Container() : head(nullptr), tail(nullptr), size(0) {}

	void push_back(T item) {
		size++;
		Node<T> * foo = new Node<T>; // C2280
		foo->next = nullptr;
		foo->data = item; // C2280

		if (head) {
			foo->prev = tail;
			tail->next = foo;
			tail = foo;
		}
		else {
			foo->prev = nullptr;
			head = tail = foo;
		}
	}

	void push_back(Node<T> * item) {
		size++;
		if (head) {
			item->prev = tail;
			tail->next = item;
			tail = item;
		}
		else {
			item->prev = nullptr;
			head = tail = item;
		}
	}

	void push_front(T item) {
		size++;
		Node<T> * foo = new Node<T>;
		foo->next = head;
		foo->data = item;

		if (head) {
			foo->next = head;
			head->prev = foo;
			head = foo;
		}
		else {
			foo->next = nullptr;
			head = tail = foo;
		}
	}

	void exterminate_last() {
		size--;
		Node<T> * foo = head;
		while (foo->next != tail) {
			foo = foo->next;
		}
		delete tail;
		tail = foo;
		tail->next = nullptr;
	}

	void exterminate_first() {
		size--;
		Node<T> * foo = head->next;
		delete head;
		head = foo;
	}

	size_t length() const { return size; }

	void show() const {
		Node<T> * foo = head;
		while (foo) {
			std::cout << foo->data << ' ';
			foo = foo->next;
		}
		delete foo;
	}

	T const & get(size_t i) const {
		if (i < size) {
			int j = 0;
			Node<T> * foo = head;
			//Node<T> * foo = new Node<T>;
			//foo = head;
			while (i != j) {
				foo = foo->next;
				j++;
			}
			return foo->data;
		}
	}

	bool is_empty() const {
		if (head && tail) {
			return false;
		}
		else {
			return true;
		}
	}

	~Container() {
		size = 0;
		while (head) {
			tail = head->next;
			delete head;
			head = tail;
		}
	}
 
private:
	Node<T> * head;
	Node<T> * tail;
	size_t size;
};