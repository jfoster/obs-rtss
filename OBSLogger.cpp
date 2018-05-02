#include "OBSLogger.h"

#include <obs.h>

const char *_name;

OBSLogger::OBSLogger(const char *name) {
	_name = name;
}

void OBSLogger::Error(const char *format, ...) {
	blog(LOG_ERROR, "%s %s", _name, format);
}

void OBSLogger::Warning(const char *format, ...) {
	blog(LOG_WARNING, "%s %s", _name, format);
}

void OBSLogger::Info(const char *format, ...) {
	blog(LOG_INFO, "%s %s", _name, format);
}

void OBSLogger::Debug(const char *format, ...) {
	blog(LOG_DEBUG, "%s %s" , _name, format);
}

OBSLogger::~OBSLogger() {

}