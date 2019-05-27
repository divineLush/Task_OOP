#pragma once

#include<random>

#include "Shapes.h"

Shape * generate_shape(size_t i) {
	Container<Point> foo = Container<Point>();

	switch (i) {
		case 0:
			return new Point(rand() % 1000, rand() % 1000);
			break;
		case 1:
			return new Circle(Point(rand() % 1000, rand() % 1000), rand() % 1000);
			break;
		case 2:
			return new Rectangle(Point(rand() % 1000, rand() % 1000), Point(rand() % 1000, rand() % 1000));
			break;
		case 3:
			return new Square(Point(rand() % 1000, rand() % 1000), Point(rand() % 1000, rand() % 1000));
			break;
		case 4:
			// Container<Point> foo = Container<Point>();
			for (int i = 0; i < rand() % 10; i++) {
				foo.push_back(Point(rand() % 1000, rand() % 1000));
			}
			return new Polyline(foo);
		case 5:
			// Container<Point> foo = Container<Point>();
			for (int i = 0; i < rand() % 10; i++) {
				foo.push_back(Point(rand() % 1000, rand() % 1000));
			}
			return new Polygon(foo);
		default :
			return nullptr;
	}
}