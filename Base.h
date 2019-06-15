#pragma once

#include <string>

class Printable {
public:
	virtual std::string get_info() const = 0;
};

class Named : public Printable {
public:
	Named(std::string const& n) : name( n ) {}

	virtual std::string get_info() const { return name; }

	std::string const& get_name() const { return name; }

private:
	std::string const name;
};
