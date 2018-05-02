#pragma once
class OBSLogger
{
public:
	OBSLogger(const char * name);
	void Error(const char * format, ...);
	void Warning(const char * format, ...);
	void Info(const char * format, ...);
	void Debug(const char * format, ...);
	~OBSLogger();
};

