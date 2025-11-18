#include "../include/StdLogHandler.hpp"

/**
 * @file StdLogHandler.hpp
 * @brief Declares a concrete LogHandler that outputs to standard output.
 *
 * StdLogHandler implements all methods of the LogHandler interface, printing
 * log messages directly to stdout using std::cout.
 *
 * Format:
 *  [LEVEL] message
 *
 * Example:
 *  [INFO] Server started
 *
 * This class is commonly used for development, debugging and CLI-based logs.
 */

StdLogHandler::StdLogHandler() : LogHandler() {}

StdLogHandler::~StdLogHandler() {}

void StdLogHandler::handleDebug(t_event event) {
	std::cout << "[DEBUG] " << event.message << std::endl;
}

void StdLogHandler::handleInfo(t_event event) {
	std::cout << "[INFO] " << event.message << std::endl;
}

void StdLogHandler::handleWarning(t_event event) {
	std::cout << "[WARNING] " << event.message << std::endl;
}

void StdLogHandler::handleError(t_event event) {
	std::cout << "[ERROR] " << event.message << std::endl;
}
