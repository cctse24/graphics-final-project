#pragma once

#include <QMainWindow>
#include <QCheckBox>
#include <QSlider>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QDial>
#include <QComboBox>
#include "realtime.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    void initialize();
    void finish();

private:
    void connectUIElements();
    void connectLevel();
    void connectAngle();
    void connectStep();
    void connectRule();
    void connectlsystem_Stochastic();
    void connectRchannel();
    void connectGChannel();
    void connectBChannel();


    Realtime *realtime;
    QCheckBox *filter1;
    QCheckBox *filter2;
    QPushButton *uploadFile;

    QComboBox* txtRule ;

    QDial *AngleSlider;
    QSlider *StepSlider;
    QDoubleSpinBox *AngleBox;
    QDoubleSpinBox *StepBox;
    QSpinBox   * LevelBox;

    QDial *RchSlider;
    QDial *GchSlider;
    QDial *BchSlider;
    QSpinBox *RchBox;
    QSpinBox *GchrBox;
    QSpinBox *BchrBox;

    QCheckBox *lsystem_Stochastic;


private slots:
    void onValChangeAngle(double newValue);
    void onValChangeStep(double newValue);
    void onValChangeLevel(int newValue);
    void onIndexChangeRule(int newIndex);

    void onValChangeRChannelSlider(int newValue);
    void onValChangeGChannelSlider(int newValue);
    void onValChangeBChannelSlider(int newValue);

    void onValChangeRChannelBox(double newValue);
    void onValChangeGChannelBox(double newValue);
    void onValChangeBChannelBox(double newValue);
    void onlsystem_Stochastic();
};
