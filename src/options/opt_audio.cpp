#include "opt_audio.h"

#include "opt_sound.h"
#include "opt_recording.h"

OptionsTabAudio::OptionsTabAudio(QObject *parent) :
    MetaOptionsTab(parent, "sound", "", tr("Audio"), tr("Messages options"), "psi/publishTune")
{
    addTab(new OptionsTabSound(this));
    addTab(new OptionsTabRecording(this));
}
