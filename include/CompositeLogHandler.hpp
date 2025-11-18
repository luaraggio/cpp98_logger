#ifndef COMPOSITELOGHANDLER_HPP
#define COMPOSITELOGHANDLER_HPP

#include "Logger.hpp"
#include <vector>

class CompositeLogHandler : public LogHandler
{
private:
	std::vector<LogHandler*> _handlers;

public:
	CompositeLogHandler();
	virtual ~CompositeLogHandler();

	void addHandler(LogHandler *handler);

	virtual void handleDebug(t_event event);
	virtual void handleInfo(t_event event);
	virtual void handleWarning(t_event event);
	virtual void handleError(t_event event);
};

#endif
