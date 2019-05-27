#pragma once

#include<random>

#include "Shapes.h"

Shape * generate_shape(size_t i) {
	if (i == 0) {
		return &Point(rand() % 1000, rand() % 1000);
	}
	if (i == 1) {
		return &Circle(Point(rand() % 1000, rand() % 1000), rand() % 1000);
	}
	if (i == 2) {
		return &Rectangle(Point(rand() % 1000, rand() % 1000), Point(rand() % 1000, rand() % 1000));
	}
	if (i == 3) {
		return &Square(Point(rand() % 1000, rand() % 1000), Point(rand() % 1000, rand() % 1000));
	}
	if (i == 4) {
		Container<Point> foo = Container<Point>();
		for (int i = 0; i < rand() % 10; i++) {
			foo.push_back(Point(rand() % 1000, rand() % 1000));
		}
		return &Polyline(foo);
	}
	if (i == 5) {
		Container<Point> foo = Container<Point>();
		for (int i = 0; i < rand() % 10; i++) {
			foo.push_back(Point(rand() % 1000, rand() % 1000));
		}
		return &Polygon(foo);
	}
	return nullptr;
}