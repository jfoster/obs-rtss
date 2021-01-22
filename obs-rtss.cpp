#include <obs-module.h>
#include <obs-frontend-api.h>

#include "pch.h"
#include "RTSSSharedMemoryInterface.h"

/* Defines common functions (required) */
OBS_DECLARE_MODULE()

/* Implements common ini-based locale (optional) */
OBS_MODULE_USE_DEFAULT_LOCALE("obs-rtss", "en-US")

CRTSSSharedMemoryInterface *rtss;

void ReleaseOSD()
{
	rtss->ReleaseOSD("obs-rtss");
}

void obs_osd_frontend_event_callback(enum obs_frontend_event event, void *private_data)
{
	ReleaseOSD();
	switch (event) {
		case OBS_FRONTEND_EVENT_FINISHED_LOADING:
			break;

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

		case OBS_FRONTEND_EVENT_SCENE_CHANGED:
			break;
		case OBS_FRONTEND_EVENT_SCENE_LIST_CHANGED:
			break;
		case OBS_FRONTEND_EVENT_SCENE_COLLECTION_CHANGED:
			break;
		case OBS_FRONTEND_EVENT_SCENE_COLLECTION_LIST_CHANGED:
			break;
		case OBS_FRONTEND_EVENT_SCENE_COLLECTION_CLEANUP:
			break;

		case OBS_FRONTEND_EVENT_TRANSITION_CHANGED:
			break;
		case OBS_FRONTEND_EVENT_TRANSITION_STOPPED:
			break;
		case OBS_FRONTEND_EVENT_TRANSITION_LIST_CHANGED:
			break;
		case OBS_FRONTEND_EVENT_TRANSITION_DURATION_CHANGED:
			break;

		case OBS_FRONTEND_EVENT_PROFILE_CHANGED:
			break;
		case OBS_FRONTEND_EVENT_PROFILE_LIST_CHANGED:
			break;

		case OBS_FRONTEND_EVENT_REPLAY_BUFFER_STARTING:
			break;
		case OBS_FRONTEND_EVENT_REPLAY_BUFFER_STARTED:
			break;
		case OBS_FRONTEND_EVENT_REPLAY_BUFFER_STOPPING:
			break;
		case OBS_FRONTEND_EVENT_REPLAY_BUFFER_STOPPED:
			break;

		case OBS_FRONTEND_EVENT_STUDIO_MODE_ENABLED:
			break;
		case OBS_FRONTEND_EVENT_STUDIO_MODE_DISABLED:
			break;
		case OBS_FRONTEND_EVENT_PREVIEW_SCENE_CHANGED:
			break;

		case OBS_FRONTEND_EVENT_EXIT:
			break;
	}
}

bool obs_module_load(void)
{
	obs_frontend_add_event_callback(obs_osd_frontend_event_callback, 0);
	rtss->UpdateOSD("obs-rtss", "obs-rtss");
	return true;
}

void obs_module_unload() {
	ReleaseOSD();
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
