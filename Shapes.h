#pragma once

#include <string>
#include <iostream>  
#include <sstream>
#include <cmath>

#include "Base.h"
#include "Container.h"

class Shape : public Printable {
public:
	virtual std::string get_info() const = 0;

	static size_t get_count() { return k; }

	virtual ~Shape() { k--; }

protected:
	Shape() { k++; }

private:
	static size_t k;
};

class Point : public Shape, public Named {
public:
	Point(double x_, double y_) : Named("Point"), x(x_), y(y_) {}

	Point(Point const& foo) : Named("Point"), x(foo.x), y(foo.y) {}

	virtual std::string get_info() const {
		std::stringstream stream;
		stream << get_name() << "\nCoord: (" << x << ", " << y << ")\n";
		return stream.str();
	}

	double get_x() const { return x; }

	double get_y() const { return y; }

	double calculate_dist(double x_, double y_) const {
		return sqrt(pow(x_ - x , 2) + pow(y_ - y , 2));
	}

	double calculate_dist(Point const & foo) const {
		return sqrt(pow(foo.get_x() - x, 2) + pow(foo.get_y() - y, 2));
	}

	friend std::ostream& operator << (std::ostream & s, Point const & a) {
		return s << a.get_info();
	}

private:
	double x;
	double y;
};

class Circle : public Shape, public Named {
public:
	Circle(Point const & p, double r) : Named("Circle"), center(p), radius(r > 0 ? r : 0){}

	virtual std::string get_info() const {
		std::stringstream stream;
		stream << get_name() << "\nCenter coord: (" << center.get_x() << ", "
			<< center.get_y() << ")\nR = " << radius << "\n"
			<< "Area = " << calculate_area() << "\n"
			<< "Length = " << calculate_length() << "\n";
		return stream.str();
	}

	double calculate_area() const { return 3.14*pow( radius, 2 ); }

	double calculate_length() const { return 2*3.14*radius; }

	friend std::ostream& operator << (std::ostream & s, Circle const & a) {
		return s << a.get_info();
	}

private:
	Point center;
	double radius;
};

class Rectangle : public Shape, public Named {
public:
	Rectangle(Point const & a_, Point const & c_): 
		Named("Rectangle"), 
		a(a_.get_x() < c_.get_x() ? a_ : Point(0, 0)), 
		c(a_.get_y() > c_.get_y() ? c_ : Point(0, 0)) {}

	virtual std::string get_info() const {
		std::stringstream stream;
		stream << get_name() << "\nCoord: a = (" << a.get_x() << ", " << a.get_y() << "), c = (" << c.get_x() << ", " << c.get_y() << ")\n";
		stream << "Perimeter = " << calculate_perimeter() << "\n";
		stream << "Area = " << calculate_area() << "\n";
		return stream.str();
	}

	double calculate_perimeter() const {
		return 2 * ( fabs( a.get_x() - c.get_x() ) + fabs( a.get_y() - c.get_y() ) );
	}

	double calculate_area() const {
		return fabs( (a.get_x() - c.get_x()) * (a.get_y() - c.get_y()) );
	}

	friend std::ostream& operator << (std::ostream & s, Rectangle const & a) {
		return s << a.get_info();
	}

private:
	Point a;
	Point c;
};

class Square : public Shape, public Named {
public:
	Square( Point const & a_, Point const & c_ ) : 
		Named("Square"), 
		a(a_.get_x() < c_.get_x() ? a_ : Point(0, 0)),
		c(a_.get_y() > c_.get_y() ? c_ : Point(0, 0)) {}

	virtual std::string get_info() const {
		std::stringstream stream;
		stream << get_name() << "\nCoord: a = (" << a.get_x() << ", " << a.get_y() <<
			"), b = (" << (a.get_x() + c.get_x()) / 2 + (a.get_y() - c.get_y()) / 2 << ", " << (a.get_y() + c.get_y()) / 2 - (a.get_x() - c.get_x()) / 2 <<
			"), c = (" << c.get_x() << ", " << c.get_y() <<
			"), d = (" << (a.get_x() + c.get_x()) / 2 - (a.get_y() - c.get_y()) / 2 << ", " << (a.get_y() + c.get_y()) / 2 + (a.get_x() - c.get_x()) / 2 << ")\n";
		stream << "Perimeter = " << calculate_perimeter() << "\n";
		stream << "Area = " << calculate_area() << "\n";
		return stream.str();
 	}

	double calculate_perimeter() const {
		return 2 * (fabs(a.get_x() - c.get_x()) + fabs(a.get_y() - c.get_y()));
	}

	double calculate_area() const {
		return fabs((a.get_x() - c.get_x()) * (a.get_y() - c.get_y()));
	}

	friend std::ostream& operator << (std::ostream & s, Square const & a) {
		return s << a.get_info();
	}

private:
	Point a;
	Point c;
};

class Polyline : public Shape, public Named {
public:
	Polyline() : Named("Polyline"), points() {}

	Polyline(Container<Point> const & p): Named("Polyline"), points(p) {}

	void add_point(Point const & p) {
		points.push_back(p);
	}

	virtual std::string get_info() const {
		std::stringstream stream;
		stream << get_name() << "\n";
		if (points.is_empty()) {
			stream << "No points";
		}
		else {
			stream << "Points: ";
			for (size_t i = 0; i < points.length(); i++) {
				stream << "(" << points.get(i).get_x() << ", " 
					<< points.get(i).get_y() << "), ";
			}
			stream << "\n" << "Length = " << calculate_length() << "\n";
		}
		return stream.str();
	}

	double calculate_length() const {
		double length = 0;
		for (size_t i = 1; i < points.length(); i++) {
			Point const & foo1 = points.get(i-1);
			Point const & foo2 = points.get(i);
			length += foo1.calculate_dist(foo2);
		}
		return length;
	}

	friend std::ostream& operator << (std::ostream & s, Polyline const & a) {
		return s << a.get_info();
	}

private:
	Container<Point> points;
};

class Polygon : public Shape, public Named {
public:
	Polygon() : Named("Polygon"), points() {}

	Polygon(Container<Point> const & p) : Named("Polygon"), points(p) {}

	virtual std::string get_info() const {
		std::stringstream stream;
		stream << get_name() << "\n";
		if (points.is_empty()) {
			stream << "No points" << "\n";
		}
		else {
			stream << "Points: ";
			for (size_t i = 0; i < points.length(); i++) {
				stream << "(" << points.get(i).get_x() << ", " 
					<< points.get(i).get_y() << "), ";
			}
			stream << "\n" << "Length = " << calculate_length() << "\n";
		}
		return stream.str();
	}

	double calculate_length() const {
		double length = 0;
		for (size_t i = 1; i < points.length(); i++) {
			Point const & foo1 = points.get(i - 1);
			Point const & foo2 = points.get(i);
			length += foo1.calculate_dist(foo2);
		}
		length += points.get(0).calculate_dist(points.get(points.length() - 1));
		return length;
	}

	friend std::ostream& operator << (std::ostream & s, Polygon & a) {
		return s << a.get_info();
	}

private:
	Container<Point> points;
};