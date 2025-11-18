#include "../include/Person.hpp"

/**
 * @file Person.cpp
 * @brief Implements the Person class used in logger tests.
 *
 * Constructor:
 *  - Emits a log event indicating the creation of a new Person instance.
 *
 * describe():
 *  - Builds a formatted string describing the person.
 *  - Sends the message through Logger::info() for demonstration purposes.
 */

Person::Person(const std::string &name, int age)
	: _name(name), _age(age)
{
	Logger::info("Person created: " + _name);
}

void Person::describe() const
{
	std::stringstream ss;
	ss << "Person: " << _name << ", " << _age << " years old";
	Logger::info(ss.str());
}
