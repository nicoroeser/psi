#ifndef OPT_RECORDING_H
#define OPT_RECORDING_H

#include "optionstab.h"

class QButtonGroup;
class QWidget;
class QStringList;

class OptionsTabRecording : public OptionsTab {
    Q_OBJECT
public:
    OptionsTabRecording(QObject *parent);
    ~OptionsTabRecording() = default;

    QWidget *widget();
    void     applyOptions();
    void     restoreOptions();

private:
    QWidget *   w;
    QStringList soundDevices_;
};

#endif // OPT_RECORDING_H
