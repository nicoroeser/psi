#include "opt_recording.h"

#include "../avcall/avcall.h"
#include "opt_avcall.h"
#include "common.h"
#include "iconwidget.h"
#include "psioptions.h"
#include "ui_opt_recording.h"

#include <QAudioDeviceInfo>
#include <QComboBox>
#include <QLineEdit>
#include <QList>
#include <QStringList>

class OptRecordingUI : public QWidget, public Ui::OptRecording {
public:
    OptRecordingUI() : QWidget() { setupUi(this); }
};

//----------------------------------------------------------------------------
// OptionsRecording
//----------------------------------------------------------------------------

OptionsTabRecording::OptionsTabRecording(QObject *parent) :
    OptionsTab(parent, "sound", "", tr("Recording"), tr("Recording audio device configuration"), "psi/mic"),
    w(nullptr)
{
}

QWidget *OptionsTabRecording::widget()
{
    if (w)
        return nullptr;

    w = new OptRecordingUI();

    if (!soundDevices_.isEmpty())
        soundDevices_.clear();

    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    for (const QAudioDeviceInfo &device : devices) {
        QString devName = device.deviceName();
        if (!devName.isEmpty() && !devName.contains("CARD"))
            soundDevices_ << devName;
    }
    OptRecordingUI *d = static_cast<OptRecordingUI *>(w);
    d->cb_audioInDevice->addItems(soundDevices_);
    if (AvCallManager::isSupported())
        d->layout()->addWidget(OptionsTabAvCall(parent()).widget());

    return w;
}

void OptionsTabRecording::applyOptions()
{
    if (!w)
        return;

    OptRecordingUI *d = static_cast<OptRecordingUI *>(w);

    PsiOptions::instance()->setOption("options.media.devices.audio-input",
                                      d->cb_audioInDevice->itemData(d->cb_audioInDevice->currentIndex()).toString());
}

void OptionsTabRecording::restoreOptions()
{
    if (!w)
        return;

    OptRecordingUI *d             = static_cast<OptRecordingUI *>(w);
    QString         defaultDevice = QAudioDeviceInfo::defaultInputDevice().deviceName();
    QString         storedDevice  = PsiOptions::instance()->getOption("options.media.devices.audio-input").toString();
    if (!storedDevice.isEmpty()) {
        if (soundDevices_.contains(storedDevice))
            d->cb_audioInDevice->setCurrentIndex(soundDevices_.indexOf(storedDevice));
    } else {
        if (soundDevices_.contains(defaultDevice))
            d->cb_audioInDevice->setCurrentIndex(soundDevices_.indexOf(defaultDevice));
    }
}
