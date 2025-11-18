#ifndef STDLOGHANDLER_HPP
# define STDLOGHANDLER_HPP

# include "Logger.hpp"

/**
 * @file StdLogHandler.cpp
 * @brief Implements the standard output logging strategy.
 *
 * Each log level is printed to std::cout with a readable prefix. This class
 * provides a simple and direct logging backend suited for debugging.
 *
 * Responsibilities:
 *  - Format messages consistently
 *  - Write log events to stdout
 */

class StdLogHandler : public LogHandler
{
  public:
	StdLogHandler();
	virtual ~StdLogHandler();

	virtual void handleDebug(t_event event);
	virtual void handleInfo(t_event event);
	virtual void handleWarning(t_event event);
	virtual void handleError(t_event event);
};

#endif
