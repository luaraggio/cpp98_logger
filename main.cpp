/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:49:43 by lraggio           #+#    #+#             */
/*   Updated: 2025/11/12 21:50:33 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Logger.hpp"
#include "include/StdLogHandler.hpp"
#include "include/Person.hpp"

int main()
{
	StdLogHandler handler;
	Logger::initializeLogger(DEBUG, &handler);

	Person p("Alice", 30);
	p.describe();

	Logger::debug("This is a debug message.");
	Logger::warning("Low memory warning.");
	Logger::error("Something went wrong!");

	return 0;
}

// int main() {
// 	Logger::initializeLogger(DEBUG, new StdLogHandler());

// 	Logger::debug("Esse é de debug");
// 	Logger::info("Esse é de info");
// 	Logger::warning("Esse é de warning");
// 	Logger::error("Esse é de error");
// }
