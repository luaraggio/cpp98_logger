#ifndef PERSON_HPP
# define PERSON_HPP

# include <string>
# include <sstream>
# include "Logger.hpp"

/**
 * @file Person.hpp
 * @brief Simple test class used to demonstrate logger integration.
 *
 * Person is a lightweight model containing a name and age. Its constructor and
 * describe() method emit log messages to validate the behavior of the logger
 * strategy in use.
 */

class Person
{
private:
	std::string _name;
	int _age;

public:
	Person(const std::string &name, int age);
	void describe() const;
};

#endif
