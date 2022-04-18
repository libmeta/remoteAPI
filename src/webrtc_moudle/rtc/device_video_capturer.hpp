#pragma once

#include <memory>
#include <vector>

// WebRTC
#include <api/scoped_refptr.h>
#include <modules/video_capture/video_capture.h>
#include <rtc_base/ref_counted_object.h>

#include "scalable_track_source.hpp"

class DeviceVideoCapturer : public ScalableVideoTrackSource,
                            public rtc::VideoSinkInterface<webrtc::VideoFrame> {
public:
    static rtc::scoped_refptr<DeviceVideoCapturer> Create(size_t width,
        size_t height,
        size_t target_fps);
    static rtc::scoped_refptr<DeviceVideoCapturer> Create(
        size_t width,
        size_t height,
        size_t target_fps,
        size_t capture_device_index);
    static rtc::scoped_refptr<DeviceVideoCapturer> Create(
        size_t width,
        size_t height,
        size_t target_fps,
        const std::string& capture_device);
    DeviceVideoCapturer();
    virtual ~DeviceVideoCapturer();

private:
    bool Init(size_t width,
        size_t height,
        size_t target_fps,
        size_t capture_device_index);
    void Destroy();

    // rtc::VideoSinkInterface interface.
    void OnFrame(const webrtc::VideoFrame& frame) override;

    int LogDeviceInfo();
    int GetDeviceIndex(const std::string& device);

    rtc::scoped_refptr<webrtc::VideoCaptureModule> vcm_;
    webrtc::VideoCaptureCapability capability_;
};
