#include "remoteapi.hpp"
#include "webrtc_moudle/rtc/scalable_track_source.hpp"
#include "webrtc_moudle/rtc/native_buffer.hpp"

#include <nlohmann/json.hpp>
#include <jmi.h>

#include "srtwrap/srtwrap.hpp"
#include "ffwrap/ffmuxer.hpp"

RemoteApi::RemoteApi()
{
    NativeBuffer::Create(webrtc::VideoType::kI420,1920,1080);
    fprintf(stdout,"hello\n");
}
