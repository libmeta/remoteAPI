#include "remoteapi.hpp"

#include <cstdio>
#include <nlohmann/json.hpp>
#include <jmi.h>

#include "srtwrap.hpp"
#include "ffwrap/ffmuxer.hpp"

RemoteApi::RemoteApi()
{
    fprintf(stdout,"hello\n");
}
