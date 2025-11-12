/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Person.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:30:00 by lraggio           #+#    #+#             */
/*   Updated: 2025/11/12 19:49:00 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERSON_HPP
# define PERSON_HPP

# include <string>
# include <sstream>
# include "Logger.hpp"

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
