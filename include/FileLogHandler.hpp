#ifndef FILELOGHANDLER_HPP
#define FILELOGHANDLER_HPP

#include "Logger.hpp"
#include <fstream>

class FileLogHandler : public LogHandler
{
private:
	std::ofstream _file;

public:
	FileLogHandler(const std::string &filename);
	virtual ~FileLogHandler();

	virtual void handleDebug(t_event event);
	virtual void handleInfo(t_event event);
	virtual void handleWarning(t_event event);
	virtual void handleError(t_event event);
};

#endif
