#include "mainwindow.h"
#include "settings.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QSettings>
#include <QLabel>
#include <QGroupBox>
#include <iostream>

void MainWindow::initialize() {
    realtime = new Realtime;

    QHBoxLayout *hLayout = new QHBoxLayout; // horizontal alignment
    QVBoxLayout *vLayout = new QVBoxLayout(); // vertical alignment

    QFont font;
    font.setPointSize(12);
    font.setBold(true);

    QLabel *l_system_label = new QLabel(); // Parameters label
    l_system_label->setText("L-system parameters:");
    l_system_label->setFont(font);

    QLabel *camera_label = new QLabel(); // Camera label
    camera_label->setText("Color Picker");
    camera_label->setFont(font);

    QLabel *angle_label = new QLabel(); // angle label
    angle_label->setText("Angle :");
    QLabel *Step_label = new QLabel(); // Step label
    Step_label->setText("Step :");

    QLabel *Level_label = new QLabel(); // Step label
    Level_label->setText("Level :");

    QLabel *R_ch = new QLabel(); // Near plane label
    R_ch->setText("R channel:");
    QLabel *G_ch = new QLabel(); // Far plane label
    G_ch->setText("G channel:");

    QLabel *B_ch = new QLabel(); // Far plane label
    B_ch->setText("B channel:");

    // Creates the boxes containing the parameter sliders and number boxes
    QGroupBox *AngleLayout = new QGroupBox(); // horizonal slider 1 alignment
    QHBoxLayout *angle = new QHBoxLayout();
    QGroupBox *StepLayout = new QGroupBox(); // horizonal slider 2 alignment
    QHBoxLayout *step = new QHBoxLayout();

    QGroupBox *LevelLayout = new QGroupBox(); // horizonal slider 2 alignment
    QHBoxLayout *Level = new QHBoxLayout();

    // Create slider controls to control parameters
    AngleSlider = new QDial();
    AngleSlider->setMinimum(1);
    AngleSlider->setMaximum(360);
    AngleSlider->setValue(20);

    AngleBox = new QDoubleSpinBox();
    AngleBox->setMinimum(1);
    AngleBox->setMaximum(360);
    AngleBox->setSingleStep(1);
    AngleBox->setValue(20);

    StepBox = new QDoubleSpinBox();
    StepBox->setMinimum(0.1f);
    StepBox->setMaximum(1.f);
    StepBox->setSingleStep(0.1f);
    StepBox->setValue(0.1f);

    LevelBox = new QSpinBox();
    LevelBox->setMinimum(1);
    LevelBox->setMaximum(5);
    LevelBox->setSingleStep(1);
    LevelBox->setValue(3);

    angle->addWidget(AngleSlider);
    angle->addWidget(AngleBox);
    AngleLayout->setLayout(angle);
    step->addWidget(StepBox);
    StepLayout->setLayout(step);
    Level->addWidget(LevelBox);
    LevelLayout->setLayout(Level);


    QGroupBox *R_layout = new QGroupBox();
    QHBoxLayout *R = new QHBoxLayout();
    QGroupBox *G_layout = new QGroupBox();
    QHBoxLayout *G = new QHBoxLayout();

    QGroupBox *B_layout = new QGroupBox();
    QHBoxLayout *B = new QHBoxLayout();


    RchSlider = new QDial();
    RchSlider->setMinimum(0);
    RchSlider->setMaximum(255);
    RchSlider->setValue(10);

    RchBox = new QSpinBox();
    RchBox->setMinimum(0);
    RchBox->setMaximum(255);
    RchBox->setSingleStep(1);
    RchBox->setValue(10);

    GchSlider = new QDial();
    GchSlider->setMinimum(0);
    GchSlider->setMaximum(255);
    GchSlider->setValue(10);

    GchrBox = new QSpinBox();
    GchrBox->setMinimum(0);
    GchrBox->setMaximum(255);
    GchrBox->setValue(10);

    BchSlider = new QDial();
    BchSlider->setMinimum(0);
    BchSlider->setMaximum(255);
    BchSlider->setValue(10);

    BchrBox = new QSpinBox();
    BchrBox->setMinimum(0);
    BchrBox->setMaximum(255);
    BchrBox->setSingleStep(1);
    BchrBox->setValue(10);

    R->addWidget(RchSlider);
    R->addWidget(RchBox);
    R_layout->setLayout(R);

    G->addWidget(GchSlider);
    G->addWidget(GchrBox);
    G_layout->setLayout(G);

    B->addWidget(BchSlider);
    B->addWidget(BchrBox);
    B_layout->setLayout(B);

    vLayout->addWidget(l_system_label);

    vLayout->addWidget(angle_label);
    vLayout->addWidget(AngleLayout);

    vLayout->addWidget(Step_label);
    vLayout->addWidget(StepLayout);

    vLayout->addWidget(Level_label);
    vLayout->addWidget(LevelLayout);

    vLayout->addWidget(camera_label);
    vLayout->addWidget(R_ch);
    vLayout->addWidget(R_layout);
    vLayout->addWidget(G_ch);
    vLayout->addWidget(G_layout);

    vLayout->addWidget(B_ch);
    vLayout->addWidget(B_layout);

    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addLayout(vLayout);

    hLayout->addWidget(realtime, 1);
    QVBoxLayout *vLayout1 = new QVBoxLayout();
    vLayout1->setAlignment(Qt::AlignTop);
    QLabel *l_system_rule = new QLabel();
    l_system_rule->setText("L-system Rules:");
    l_system_rule->setFont(font);


    txtRule = new QComboBox();


    vLayout1->addWidget(l_system_rule);
    QGroupBox *TextLayout = new QGroupBox();
    QHBoxLayout *text = new QHBoxLayout();
    txtRule->addItem("Fractal plant");
    txtRule->addItem("Fractal (binary) tree");
    txtRule->addItem("Snowflake");
    txtRule->addItem("Leaf");
    txtRule->addItem("Bushes (0)");
    txtRule->addItem("Bushes (1)");
    txtRule->addItem("Bushes (2)");
    txtRule->addItem("plant (2)");
    txtRule->addItem("plant (3)");

    txtRule->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum );
    text->addWidget(txtRule);
    TextLayout->setLayout(text);
    vLayout1->addWidget(TextLayout);

    QLabel *l_system_axiom = new QLabel(); //  label
    l_system_axiom->setText("l_system_Variations:");
    l_system_axiom->setFont(font);

    QLabel *Stochastic_G = new QLabel(); //  label
    Stochastic_G->setText("Enable Stochastic Grammar:");
    Stochastic_G->setFont(font);


    lsystem_Stochastic = new QCheckBox();
    QGroupBox *lsystem_layout = new QGroupBox();
    QHBoxLayout *Stochastic = new QHBoxLayout();
    Stochastic->addWidget(Stochastic_G);
    Stochastic->addWidget(lsystem_Stochastic);

    lsystem_layout->setLayout(Stochastic);
    vLayout1->addWidget(l_system_axiom);

    vLayout1->addWidget(lsystem_layout);

    hLayout->addLayout(vLayout1);

     this->setLayout(hLayout);

    connectUIElements();

    onValChangeAngle(45);
    onValChangeStep(0.1);
    onValChangeLevel(3);
    onIndexChangeRule(0);

    onValChangeRChannelBox(0);
    onValChangeGChannelBox(255);
    onValChangeBChannelBox(0);
}

void MainWindow::finish() {
    realtime->finish();
    delete(realtime);
}

void MainWindow::connectUIElements() {
    connectAngle();
    connectStep();
    connectLevel();
    connectRule();
    connectlsystem_Stochastic();

    connectRchannel();
    connectGChannel();
    connectBChannel();
}

void MainWindow::connectlsystem_Stochastic() {
    connect(lsystem_Stochastic, &QCheckBox::clicked, this, &MainWindow::onlsystem_Stochastic);
}



void MainWindow::connectAngle() {
    connect(AngleSlider, &QDial::valueChanged, this, &MainWindow::onValChangeAngle);
    connect(AngleBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::onValChangeAngle);
}

void MainWindow::connectLevel() {
    connect(LevelBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::onValChangeLevel);
}

void MainWindow::connectStep() {

    connect(StepBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::onValChangeStep);
}


void MainWindow::connectRchannel() {
    connect(RchSlider, &QDial::valueChanged, this, &MainWindow::onValChangeRChannelSlider);
    connect(RchBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::onValChangeRChannelBox);
}

void MainWindow::connectGChannel() {
    connect(GchSlider, &QDial::valueChanged, this, &MainWindow::onValChangeGChannelSlider);
    connect(GchrBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::onValChangeGChannelBox);
}

void MainWindow::connectBChannel() {
    connect(BchSlider, &QDial::valueChanged, this, &MainWindow::onValChangeBChannelSlider);
    connect(BchrBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::onValChangeBChannelBox);
}
void MainWindow::connectRule() {
    connect(txtRule, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::onIndexChangeRule);
}

void MainWindow::onValChangeAngle(double newValue) {
    AngleSlider->setValue(newValue);
    AngleBox->setValue(newValue);
    settings.Angle = AngleBox->value();
    realtime->settingsChanged();
}

void MainWindow::onValChangeStep(double newValue) {
    StepBox->setValue(newValue);
    settings.step = StepBox->value();
    realtime->settingsChanged();
}

void MainWindow::onValChangeLevel(int newValue) {

    LevelBox->setValue(newValue);
    settings.level = LevelBox->value();
    realtime->settingsChanged();
}

void MainWindow::onValChangeRChannelSlider(int newValue) {
    RchSlider->setValue(newValue);
    RchBox->setValue(newValue);
    settings.Rchannel = RchSlider->value();
    realtime->settingsChanged();
}

void MainWindow::onValChangeGChannelSlider(int newValue) {
    GchSlider->setValue(newValue);
    GchrBox->setValue(newValue);
    settings.Gchannel = GchSlider->value();
    realtime->settingsChanged();
}

void MainWindow::onValChangeBChannelSlider(int newValue) {
    BchSlider->setValue(newValue);
    BchrBox->setValue(newValue);
    settings.Bchannel = BchSlider->value();
    realtime->settingsChanged();
}

void MainWindow::onValChangeRChannelBox(double newValue) {
    RchSlider->setValue(int(newValue));
    RchBox->setValue(newValue);
    settings.Rchannel = RchBox->value();
    realtime->settingsChanged();
}

void MainWindow::onValChangeBChannelBox(double newValue) {
   BchSlider->setValue(int(newValue));
   BchrBox->setValue(newValue);
    settings.Bchannel = BchrBox->value();
    realtime->settingsChanged();
}

void MainWindow::onValChangeGChannelBox(double newValue) {
    GchSlider->setValue(int(newValue));
    GchrBox->setValue(newValue);
    settings.Gchannel = GchrBox->value();
    realtime->settingsChanged();
}

void MainWindow::onIndexChangeRule(int newValue) {
    txtRule->setCurrentIndex(newValue);
    settings.stringRule = txtRule->currentIndex();
    realtime->settingsChanged();
}

void MainWindow::onlsystem_Stochastic(){
    settings.enableStochastic = !settings.enableStochastic;
    realtime->settingsChanged();
}



