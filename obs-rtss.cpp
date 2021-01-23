#include <obs-module.h>
#include <obs-frontend-api.h>
#include <windows.h>

#include "pch.h"
#include "RTSSSharedMemoryInterface.h"

CRTSSSharedMemoryInterface *rtss;

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs-rtss", "en-US")

void obs_osd_frontend_event_callback(enum obs_frontend_event event, void *private_data)
{
	switch (event) {
		case OBS_FRONTEND_EVENT_STREAMING_STARTING:
			rtss->UpdateOSD("obs-rtss-stream", "Streaming...");
			break;
		case OBS_FRONTEND_EVENT_STREAMING_STARTED:
			rtss->UpdateOSD("obs-rtss-stream", "Streaming");
			break;
		case OBS_FRONTEND_EVENT_STREAMING_STOPPING:
			rtss->UpdateOSD("obs-rtss-stream", "Stopping...");
			break;
		case OBS_FRONTEND_EVENT_STREAMING_STOPPED:
			rtss->ReleaseOSD("obs-rtss-stream");
			break;
		case OBS_FRONTEND_EVENT_RECORDING_STARTING:
			rtss->UpdateOSD("obs-rtss-record", "Recording...");
			break;
		case OBS_FRONTEND_EVENT_RECORDING_STARTED:
			rtss->UpdateOSD("obs-rtss-record", "Recording");
			break;
		case OBS_FRONTEND_EVENT_RECORDING_STOPPING:
			rtss->UpdateOSD("obs-rtss-record", "Stopping...");
			break;
		case OBS_FRONTEND_EVENT_RECORDING_STOPPED:
			rtss->ReleaseOSD("obs-rtss-record");
			break;
		case OBS_FRONTEND_EVENT_RECORDING_PAUSED:
			break;
		case OBS_FRONTEND_EVENT_RECORDING_UNPAUSED:
			break;
		case OBS_FRONTEND_EVENT_REPLAY_BUFFER_STARTING:
			break;
		case OBS_FRONTEND_EVENT_REPLAY_BUFFER_STARTED:
			break;
		case OBS_FRONTEND_EVENT_REPLAY_BUFFER_STOPPING:
			break;
		case OBS_FRONTEND_EVENT_REPLAY_BUFFER_STOPPED:
			break;
		case OBS_FRONTEND_EVENT_REPLAY_BUFFER_SAVED:
			rtss->UpdateOSD("obs-rtss-replay", "Replay Saved");
			Sleep(5000);
			rtss->ReleaseOSD("obs-rtss-replay");
			break;
	}
}

bool obs_module_load(void)
{
	obs_frontend_add_event_callback(obs_osd_frontend_event_callback, 0);
	return true;
}

void obs_module_unload() {
	rtss->ReleaseOSD("obs-rtss");
	rtss->ReleaseOSD("obs-rtss-stream");
	rtss->ReleaseOSD("obs-rtss-record");
	rtss->ReleaseOSD("obs-rtss-replay");
}

const char *obs_module_author(void) {
	return "Rave";
}

const char *obs_module_name(void) {
	return "obs-rtss";
}

const char *obs_module_description(void) {
	return "On screen display for OBS using RTSS";
}
