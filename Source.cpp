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
		Node<T> * foo = new Node<T>;
		foo->next = nullptr;
		foo->data = item;

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
			Node<T> * foo = new Node<T>;
			foo = head;
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

int main() {
	Container<int> A;
	A.push_back(1);
	A.push_front(2);
	A.push_back(3);
	A.push_front(4);
	A.push_back(5);
	A.push_front(6);
	std::cout << A.length() << std::endl;
	std::cout << A.is_empty() << std::endl;
	std::cout << A.get(0) << std::endl;
	std::cout << A.get(A.length()-1) << std::endl;
	A.show();
	std::cout << std::endl;
	A.exterminate_first();
	A.show();
	std::cout << std::endl;
	A.exterminate_last();
	A.show();
	std::cout << std::endl;
	A.exterminate_first();
	A.show();
	std::cout << std::endl;
	A.exterminate_last();
	A.show();
	A.~Container();
	std::cout << std::endl;
	std::cout << A.length();
	getchar();
	return 0;
}
