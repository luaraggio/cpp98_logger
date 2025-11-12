/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Person.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:49:21 by lraggio           #+#    #+#             */
/*   Updated: 2025/11/12 19:53:13 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Person.hpp"

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
