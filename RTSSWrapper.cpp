#include "RTSSWrapper.h"
#include "RTSSInterface.h"

RTSSInterface* rtssi;

RTSSWrapper::RTSSWrapper() {

}

void RTSSWrapper::showStreaming() {
	rtssi->UpdateOSD("Streaming");
}

void RTSSWrapper::showRecording() {
	rtssi->UpdateOSD("Recording");
}

void RTSSWrapper::hide() {
	rtssi->ReleaseOSD();
}

RTSSWrapper::~RTSSWrapper() {

}