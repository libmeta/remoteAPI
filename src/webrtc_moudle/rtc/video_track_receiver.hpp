#pragma once
// WebRTC
#include <api/media_stream_interface.h>

class VideoTrackReceiver {
public:
    virtual void AddTrack(webrtc::VideoTrackInterface* track) = 0;
    virtual void RemoveTrack(webrtc::VideoTrackInterface* track) = 0;
};
