// #include "../include/Logger.hpp"
// #include "../include/StdLogHandler.hpp"
// #include "../include/Person.hpp"

// int main()
// {
// 	StdLogHandler handler;
// 	Logger::initializeLogger(DEBUG, &handler);

// 	Person p("Alice", 30);
// 	p.describe();

// 	Logger::debug("This is a debug message.");
// 	// Logger::warning("Low memory warning.");
// 	// Logger::error("Something went wrong!");

// 	return 0;
// }

// int main() {
// 	Logger::initializeLogger(DEBUG, new StdLogHandler());

// 	Logger::debug("Esse é de debug");
// 	Logger::info("Esse é de info");
// 	Logger::warning("Esse é de warning");
// 	Logger::error("Esse é de error");
// }

#include "../include/CompositeLogHandler.hpp"
#include "../include/FileLogHandler.hpp"
#include "../include/StdLogHandler.hpp"

int main()
{
    CompositeLogHandler multi;
    StdLogHandler console;
    FileLogHandler file("app.log");

    multi.addHandler(&console);
    multi.addHandler(&file);

    Logger::initializeLogger(DEBUG, &multi);

    Logger::info("Logger initialized with stdout + file.");
    Logger::debug("Debugging...");
    Logger::warning("Careful...");
    Logger::error("Something failed!");

    return 0;
}
