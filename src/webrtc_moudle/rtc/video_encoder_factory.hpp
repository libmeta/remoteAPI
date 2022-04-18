#pragma once

#include <memory>
#include <vector>

// WebRTC
#include <api/video_codecs/sdp_video_format.h>
#include <api/video_codecs/video_encoder.h>
#include <api/video_codecs/video_encoder_factory.h>

#include "video_codec_info.hpp"

#if USE_MSDK_ENCODER
#include "hwenc_msdk/msdk_session.h"
#endif

struct VideoEncoderFactoryConfig {
    VideoCodecInfo::Type vp8_encoder;
    VideoCodecInfo::Type vp9_encoder;
    VideoCodecInfo::Type av1_encoder;
    VideoCodecInfo::Type h264_encoder;
    bool simulcast;
    bool hardware_encoder_only;

#if USE_MSDK_ENCODER
    std::shared_ptr<MsdkSession> msdk_session;
#endif
};

class VideoEncoderFactory : public webrtc::VideoEncoderFactory {
    VideoEncoderFactoryConfig config_;
    std::unique_ptr<webrtc::VideoEncoderFactory> video_encoder_factory_;
    std::unique_ptr<VideoEncoderFactory> internal_encoder_factory_;

public:
    VideoEncoderFactory(const VideoEncoderFactoryConfig& config);
    virtual ~VideoEncoderFactory() { }

    std::vector<webrtc::SdpVideoFormat> GetSupportedFormats() const override;

    std::unique_ptr<webrtc::VideoEncoder> CreateVideoEncoder(
        const webrtc::SdpVideoFormat& format) override;

private:
    std::unique_ptr<webrtc::VideoEncoder> WithSimulcast(
        const webrtc::SdpVideoFormat& format,
        std::function<std::unique_ptr<webrtc::VideoEncoder>(
            const webrtc::SdpVideoFormat&)>
            create);
};
