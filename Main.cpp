#include "factory.h"

size_t Shape::k = 0;

int main() {
	Container<Shape *> shapes = Container<Shape *>();
	for (size_t i = 0; i < 20; i++) {
		shapes.push_back(generate_shape(rand() % 4));
	}
	
	for (size_t i = 0; i < 20; i++) {
		std::cout << shapes.get(i)->get_info() << "\n";
	}

	std::cout << "Number of figures = " << Shape::get_count() << "\n";
	shapes.~Container();
	std::cout << "Number of figures = " << shapes.length();
	getchar();
	return 0;
}