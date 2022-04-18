#pragma once


#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#if USE_NVCODEC_ENCODER
#include "hwenc_nvcodec/nvcodec_h264_encoder.h"
#include "hwenc_nvcodec/nvcodec_video_decoder.h"
#endif

#if USE_MSDK_ENCODER
#include "hwenc_msdk/msdk_video_decoder.h"
#include "hwenc_msdk/msdk_video_encoder.h"
#endif

#if USE_JETSON_ENCODER
#include "hwenc_jetson/jetson_video_encoder.h"
#endif

    struct VideoCodecInfo {
    enum class Type {
        Default,
        NVIDIA,
        Intel,
        VideoToolbox,
        Software,
        NotSupported,
        };

    std::vector<Type> vp8_encoders;
    std::vector<Type> vp8_decoders;

    std::vector<Type> vp9_encoders;
    std::vector<Type> vp9_decoders;

    std::vector<Type> av1_encoders;
    std::vector<Type> av1_decoders;

    std::vector<Type> h264_encoders;
    std::vector<Type> h264_decoders;

         // Default を解決して、ちゃんとしたエンコーダ名か NotSupported になるようにする
    static Type Resolve(Type specified, const std::vector<Type>& codecs) {
        if (codecs.empty()) {
            return Type::NotSupported;
        }
        if (specified == Type::Default) {
            // 先頭のを利用する
            return codecs[0];
        }
        auto it = std::find(codecs.begin(), codecs.end(), specified);
        if (it != codecs.end()) {
            return *it;
        }
        return Type::NotSupported;
    }

    static std::vector<std::pair<std::string, VideoCodecInfo::Type>>
    GetValidMappingInfo(std::vector<Type> types) {
        std::vector<std::pair<std::string, VideoCodecInfo::Type>> infos;
        infos.push_back({"default", VideoCodecInfo::Type::Default});
        for (auto type : types) {
            auto p = TypeToString(type);
            infos.push_back({p.second, type});
        }
        return infos;
    }

    static std::pair<std::string, std::string> TypeToString(Type type) {
        switch (type) {
        case Type::NVIDIA:
            return {"NVIDIA VIDEO CODEC SDK", "nvidia"};
        case Type::Intel:
            return {"Intel Media SDK", "intel"};
        case Type::VideoToolbox:
            return {"VideoToolbox", "videotoolbox"};
        case Type::Software:
            return {"Software", "software"};
        default:
            return {"Unknown", "unknown"};
        }
    }

    static VideoCodecInfo Get() {
#if defined(_WIN32)
        return GetWindows();
#elif defined(__APPLE__)
        return GetMacos();
#elif defined(__linux__)
        return GetLinux();
#endif
    }

private:
#if defined(_WIN32)

    static VideoCodecInfo GetWindows() {
        VideoCodecInfo info;

#if USE_NVCODEC_ENCODER
        if (NvCodecH264Encoder::IsSupported()) {
            info.h264_encoders.push_back(Type::NVIDIA);
        }
        if (NvCodecVideoDecoder::IsSupported(CudaVideoCodec::VP8)) {
            info.vp8_decoders.push_back(Type::NVIDIA);
        }
        if (NvCodecVideoDecoder::IsSupported(CudaVideoCodec::VP9)) {
            info.vp9_decoders.push_back(Type::NVIDIA);
        }
        if (NvCodecVideoDecoder::IsSupported(CudaVideoCodec::H264)) {
            info.h264_decoders.push_back(Type::NVIDIA);
        }
#endif

#if USE_MSDK_ENCODER
        auto session = MsdkSession::Create();
        if (session != nullptr) {
            if (MsdkVideoEncoder::IsSupported(session, MFX_CODEC_VP8)) {
                info.vp8_encoders.push_back(Type::Intel);
            }
            if (MsdkVideoEncoder::IsSupported(session, MFX_CODEC_VP9)) {
                info.vp9_encoders.push_back(Type::Intel);
            }
            if (MsdkVideoEncoder::IsSupported(session, MFX_CODEC_AVC)) {
                info.h264_encoders.push_back(Type::Intel);
            }
            if (MsdkVideoEncoder::IsSupported(session, MFX_CODEC_AV1)) {
                info.av1_encoders.push_back(Type::Intel);
            }
            if (MsdkVideoDecoder::IsSupported(session, MFX_CODEC_VP8)) {
                info.vp8_decoders.push_back(Type::Intel);
            }
            if (MsdkVideoDecoder::IsSupported(session, MFX_CODEC_VP9)) {
                info.vp9_decoders.push_back(Type::Intel);
            }
            if (MsdkVideoDecoder::IsSupported(session, MFX_CODEC_AVC)) {
                info.h264_decoders.push_back(Type::Intel);
            }
            if (MsdkVideoDecoder::IsSupported(session, MFX_CODEC_AV1)) {
                info.av1_decoders.push_back(Type::Intel);
            }
        }
#endif

        info.vp8_encoders.push_back(Type::Software);
        info.vp8_decoders.push_back(Type::Software);
        info.vp9_encoders.push_back(Type::Software);
        info.vp9_decoders.push_back(Type::Software);
        info.av1_encoders.push_back(Type::Software);
        info.av1_decoders.push_back(Type::Software);

        return info;
    }

#elif defined(__APPLE__)

    static VideoCodecInfo GetMacos() {
        VideoCodecInfo info;

        info.h264_encoders.push_back(Type::VideoToolbox);
        info.h264_decoders.push_back(Type::VideoToolbox);
        info.vp8_encoders.push_back(Type::Software);
        info.vp9_encoders.push_back(Type::Software);
        info.vp8_decoders.push_back(Type::Software);
        info.vp9_decoders.push_back(Type::Software);
        info.av1_encoders.push_back(Type::Software);
        info.av1_decoders.push_back(Type::Software);

        return info;
    }

#elif defined(__linux__)

    static VideoCodecInfo GetLinux() {
        VideoCodecInfo info;

#if USE_NVCODEC_ENCODER
        if (NvCodecH264Encoder::IsSupported()) {
            info.h264_encoders.push_back(Type::NVIDIA);
        }
        if (NvCodecVideoDecoder::IsSupported(CudaVideoCodec::VP8)) {
            info.vp8_decoders.push_back(Type::NVIDIA);
        }
        if (NvCodecVideoDecoder::IsSupported(CudaVideoCodec::VP9)) {
            info.vp9_decoders.push_back(Type::NVIDIA);
        }
        if (NvCodecVideoDecoder::IsSupported(CudaVideoCodec::H264)) {
            info.h264_decoders.push_back(Type::NVIDIA);
        }
#endif

#if USE_MSDK_ENCODER
        auto session = MsdkSession::Create();
        if (session != nullptr) {
            if (MsdkVideoEncoder::IsSupported(session, MFX_CODEC_VP8)) {
                info.vp8_encoders.push_back(Type::Intel);
            }
            if (MsdkVideoEncoder::IsSupported(session, MFX_CODEC_VP9)) {
                info.vp9_encoders.push_back(Type::Intel);
            }
            if (MsdkVideoEncoder::IsSupported(session, MFX_CODEC_AVC)) {
                info.h264_encoders.push_back(Type::Intel);
            }
            if (MsdkVideoEncoder::IsSupported(session, MFX_CODEC_AV1)) {
                info.av1_encoders.push_back(Type::Intel);
            }
            if (MsdkVideoDecoder::IsSupported(session, MFX_CODEC_VP8)) {
                info.vp8_decoders.push_back(Type::Intel);
            }
            if (MsdkVideoDecoder::IsSupported(session, MFX_CODEC_VP9)) {
                info.vp9_decoders.push_back(Type::Intel);
            }
            if (MsdkVideoDecoder::IsSupported(session, MFX_CODEC_AVC)) {
                info.h264_decoders.push_back(Type::Intel);
            }
            if (MsdkVideoDecoder::IsSupported(session, MFX_CODEC_AV1)) {
                info.av1_decoders.push_back(Type::Intel);
            }
        }
#endif

#if USE_MMAL_ENCODER
        info.h264_encoders.push_back(Type::MMAL);
        info.h264_decoders.push_back(Type::MMAL);
#endif

#if USE_JETSON_ENCODER
        info.h264_encoders.push_back(Type::Jetson);
        info.h264_decoders.push_back(Type::Jetson);
        if (JetsonVideoEncoder::IsSupportedVP8()) {
            info.vp8_encoders.push_back(Type::Jetson);
        }
        info.vp8_decoders.push_back(Type::Jetson);
        info.vp9_decoders.push_back(Type::Jetson);
        if (JetsonVideoEncoder::IsSupportedVP9()) {
            info.vp9_encoders.push_back(Type::Jetson);
        }
#endif

        info.vp8_encoders.push_back(Type::Software);
        info.vp8_decoders.push_back(Type::Software);
        info.vp9_encoders.push_back(Type::Software);
        info.vp9_decoders.push_back(Type::Software);

#if !defined(__arm__) || defined(__aarch64__) || defined(__ARM_NEON__)
        info.av1_encoders.push_back(Type::Software);
        info.av1_decoders.push_back(Type::Software);
#endif

        return info;
    }

#endif
};
