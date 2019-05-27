#include "factory.h"

int main() {
	k = 0;
	Container<Shape *> shapes = Container<Shape *>();
	for (size_t i = 0; i < 20; i++) {
		shapes.push_back(generate_shape(rand() % 4));
	}
	for (size_t i = 0; i < 20; i++) {
		shapes.get(i)->get_info();
		std::cout << '\n';
	}
	std::cout << Shape::get_count() << '\n';
	shapes.~Container();
	std::cout << shapes.length();
	return 0;
}