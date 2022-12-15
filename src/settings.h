#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

struct Settings {
    std::string sceneFilePath;
    float Angle = 1;
    float step = 1;
    int level = 1 ;
    int Rchannel = 1;
    int Gchannel = 1;
    int Bchannel = 1;
    int stringRule = 0  ;
    bool perPixelFilter = false;
    bool kernelBasedFilter = false;
    bool enableStochastic = false;
    bool extraCredit2 = false;
    bool extraCredit3 = false;
    bool extraCredit4 = false;
};


// The global Settings object, will be initialized by MainWindow
extern Settings settings;

#endif // SETTINGS_H
