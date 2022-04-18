#pragma once

#include <stddef.h>

#include <memory>
// WebRTC
#include <media/base/adapted_video_track_source.h>
#include <media/base/video_adapter.h>
#include <rtc_base/timestamp_aligner.h>

class ScalableVideoTrackSource : public rtc::AdaptedVideoTrackSource {
public:
    ScalableVideoTrackSource();
    virtual ~ScalableVideoTrackSource();

    bool is_screencast() const override;
    absl::optional<bool> needs_denoising() const override;
    webrtc::MediaSourceInterface::SourceState state() const override;
    bool remote() const override;
    void OnCapturedFrame(const webrtc::VideoFrame& frame);

protected:
    virtual bool UseNativeBuffer() { return false; }

private:
    rtc::TimestampAligner timestamp_aligner_;
};
