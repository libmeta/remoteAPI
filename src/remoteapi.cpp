#include "remoteapi.hpp"

#include <cstdio>
#include <nlohmann/json.hpp>
#include <jmi.h>

#include "srtwrap/srtwrap.hpp"
#include "ffwrap/ffmuxer.hpp"

#include "rtc_base/platform_thread.h"
#include "webrtc_moudle/rtc/native_buffer.hpp"

RemoteApi::RemoteApi()
{
    NativeBuffer::Create(webrtc::VideoType::kI420,1920,1080);
    fprintf(stdout,"hello\n");
}
