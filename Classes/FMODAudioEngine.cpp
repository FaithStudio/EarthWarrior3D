#include "FMODAudioEngine.h"
#include "platform/CCPlatformConfig.h"
#include <assert.h>

#define CHECK_RESULT(result) assert(result == FMOD_OK)

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #define FILE_PREFIX "file:///android_asset/"
#else
    #define FILE_PREFIX
#endif

namespace FMODAudioEngine
{

static FMOD::Studio::System *gSystem = 0;
static FMOD::Studio::EventInstance *gMusicEvent = 0;

FMOD::Studio::System *getStudioSystem()
{
    if (gSystem == 0)
    {
        FMOD_RESULT result = FMOD::Studio::System::create(&gSystem);
        CHECK_RESULT(result);

        FMOD::System *lowLevelSystem ;
        result = gSystem->getLowLevelSystem(&lowLevelSystem);
        CHECK_RESULT(result);
        
        result = lowLevelSystem->setDSPBufferSize(512, 4);
        CHECK_RESULT(result);

        result = gSystem->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
        CHECK_RESULT(result);

        FMOD::Studio::Bank *masterBank;
        result = gSystem->loadBankFile(FILE_PREFIX"Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);
        CHECK_RESULT(result);

        FMOD::Studio::Bank *stringsBank;
        result = gSystem->loadBankFile(FILE_PREFIX"Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
        CHECK_RESULT(result);
    }

    return gSystem;
}


void endStudioSystem()
{
    if (gSystem)
    {
        FMOD_RESULT result = gSystem->release();
        CHECK_RESULT(result);

        gSystem = 0;
    }
}


void playBackgroundMusic(const char *musicPath)
{
    if (gMusicEvent)
    {
        FMOD_RESULT result = gMusicEvent->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
        CHECK_RESULT(result);

        result = gMusicEvent->release();
        CHECK_RESULT(result);
        
        gMusicEvent = 0;
    }

    gMusicEvent = getEvent(musicPath);
    
    FMOD_RESULT result = gMusicEvent->start();
    CHECK_RESULT(result);
}


void setBackgroundMusicParam(const char *param, float value)
{
    if (gMusicEvent)
    {
        FMOD::Studio::ParameterInstance *paramInst;
        FMOD_RESULT result = gMusicEvent->getParameter(param, &paramInst);
        CHECK_RESULT(result);

        result = paramInst->setValue(value);
        CHECK_RESULT(result);
    }
}


FMOD::Studio::EventInstance *getEvent(const char *eventPath)
{
    FMOD::Studio::System *system = getStudioSystem();

    FMOD::Studio::EventDescription *desc;
    FMOD_RESULT result = system->getEvent(eventPath, &desc);
    CHECK_RESULT(result);

    FMOD::Studio::EventInstance *inst;
    result = desc->createInstance(&inst);
    CHECK_RESULT(result);

    return inst;
}


void playEvent(const char *eventPath)
{
    FMOD::Studio::EventInstance *inst = getEvent(eventPath);

    FMOD_RESULT result = inst->start();
    CHECK_RESULT(result);

    result = inst->release(); // Fire and forget
    CHECK_RESULT(result);
}


void playEventWithParam(const char *eventPath, const char *param, float value)
{
    FMOD::Studio::EventInstance *eventInst = getEvent(eventPath);

    FMOD::Studio::ParameterInstance *paramInst;
    FMOD_RESULT result = eventInst->getParameter(param, &paramInst);
    CHECK_RESULT(result);

    result = paramInst->setValue(value);
    CHECK_RESULT(result);

    result = eventInst->start();
    CHECK_RESULT(result);

    result = eventInst->release(); // Fire and forget
    CHECK_RESULT(result);
}


void update()
{
    FMOD::Studio::System *system = getStudioSystem();

    FMOD_RESULT result = system->update();
    CHECK_RESULT(result);
}

}
