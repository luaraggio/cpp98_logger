#include "../include/Logger.hpp"

/**
 * @file Logger.cpp
 * @brief Implements the Singleton Logger and its message dispatching logic.
 *
 * The Logger filters log messages based on severity and forwards them to the
 * configured LogHandler. Each log level has its own dedicated dispatch method.
 *
 * The logger accepts one strategy at initialization and delegates every log
 * event to the provided handler.
 *
 * Responsibilities:
 *  - Enforce the Singleton instance
 *  - Filter events using the configured LogLevel threshold
 *  - Forward log events to the strategy object (LogHandler)
 */

Logger *Logger::_instance = NULL;

Logger::Logger(enum LogLevel level, LogHandler *handler) : _handler(handler), _level(level) {}

Logger::~Logger() {}

int Logger::initializeLogger(enum LogLevel level, LogHandler *handler)
{
	if (Logger::_instance) {
		return (-1);
	}
	Logger::_instance = new Logger(level, handler);
	return (0);
}

void Logger::debug(std::string message)
{
	if (!Logger::_instance || !Logger::_instance->_handler
		|| Logger::_instance->_level > DEBUG) {
		return ;
	}
	t_event event = {
		.level = DEBUG,
		.message = message
	};
	Logger::_instance->_handler->handleDebug(event);
}

void Logger::info(std::string message)
{
	if (!Logger::_instance || !Logger::_instance->_handler
		|| Logger::_instance->_level > INFO) {
		return ;
	}
	t_event event = {
		.level = INFO,
		.message = message
	};
	Logger::_instance->_handler->handleInfo(event);
}

void Logger::warning(std::string message)
{
	if (!Logger::_instance || !Logger::_instance->_handler
		|| Logger::_instance->_level > WARNING) {
		return ;
	}
	t_event event = {.level = WARNING, .message = message};
	Logger::_instance->_handler->handleWarning(event);
}

void Logger::error(std::string message)
{
	if (!Logger::_instance || !Logger::_instance->_handler
		|| Logger::_instance->_level > ERROR) {
		return ;
	}

	t_event event = {
		.level = ERROR,
		.message = message
	};
	Logger::_instance->_handler->handleError(event);
}

