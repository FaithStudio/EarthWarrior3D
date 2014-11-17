#ifndef _FMOD_AUDIO_ENGINE_H_
#define _FMOD_AUDIO_ENGINE_H_

#include "fmod_studio.hpp"

namespace FMODAudioEngine
{
    void endStudioSystem();
    void update();
    void playBackgroundMusic(const char *musicPath);
    void setBackgroundMusicParam(const char *param, float value);
    void playEvent(const char *eventPath);
    void playEventWithParam(const char *eventPath, const char *param, float value);

    FMOD::Studio::EventInstance *getEvent(const char *eventPath);
}

#endif // _FMOD_AUDIO_ENGINE_H_
