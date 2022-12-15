#include "realtime.h"

#include <QCoreApplication>
#include <QMouseEvent>
#include <QKeyEvent>
#include <iostream>
#include "glm/gtc/constants.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#include "settings.h"
#include "utils/shaderloader.h"
// ================== Project 5: Lights, Camera

Realtime::Realtime(QWidget *parent)
    : QOpenGLWidget(parent),m_angleX(6), m_angleY(0), m_zoom(2)
{
    m_prev_mouse_pos = glm::vec2(size().width()/2, size().height()/2);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    rebuildMatrices();
    m_keyMap[Qt::Key_W]       = false;
    m_keyMap[Qt::Key_A]       = false;
    m_keyMap[Qt::Key_S]       = false;
    m_keyMap[Qt::Key_D]       = false;
    m_keyMap[Qt::Key_Control] = false;
    m_keyMap[Qt::Key_Space]   = false;

    // If you must use this function, do not edit anything above this
}

void Realtime::finish() {
    killTimer(m_timer);
    this->makeCurrent();

    // Students: anything requiring OpenGL calls when the program exits should be done here
    glDeleteProgram(m_shader);
    this->doneCurrent();
}

void Realtime::initializeGL() {
    m_devicePixelRatio = this->devicePixelRatio();

    m_timer = startTimer(1000/60);
    m_elapsedTimer.start();

    // Initializing GL.
    // GLEW (GL Extension Wrangler) provides access to OpenGL functions.
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error while initializing GL: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Initialized GL: Version " << glewGetString(GLEW_VERSION) << std::endl;

    // Allows OpenGL to draw objects appropriately on top of one another
    glEnable(GL_DEPTH_TEST);
    // Tells OpenGL to only draw the front face
    glEnable(GL_CULL_FACE);
    // Tells OpenGL how big the screen is
    glViewport(0, 0, size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);

     glClearColor(0,0,0,1);
      m_shader = ShaderLoader::createShaderProgram(":/resources/shaders/default.vert",
                                                   ":/resources/shaders/default.frag"); // Shader setup (DO NOT EDIT)


      glready = true;

    settings.Angle = 20 ;
    settings.step = 0.1 ;
    settings.level = 5 ;
    GenerateLsystem();
    this->s = SimpleController(glready);
}

void Realtime::paintGL() {

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glUseProgram(m_shader);

   for(auto& sh : this->line){
       sh.draw(this->m_shader,this->m_view, this->m_proj);
   }

   glUseProgram(0);
  if(this->glready){
   this->s.draw(this->m_timer,
                this->m_proj ,
                this->m_view);
  }
}

void Realtime::resizeGL(int w, int h) {
    // Tells OpenGL how big the screen is
    glViewport(0, 0, size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);
    m_proj = glm::perspective(glm::radians(45.0),1.0 * w / h,0.01,1000.0);
    // Students: anything requiring OpenGL calls when the program starts should be done here
}

void Realtime::sceneChanged() {

    update(); // asks for a PaintGL() call to occur
}

void Realtime::settingsChanged() {
    if(glready){
     if(this->step != settings.step || this->angle != settings.Angle ||
             this->level != settings.level || this->stringRule != settings.stringRule ||
             this->enables != settings.enableStochastic){
         for(auto& l : this->line){
            l.DeleteLine();
         }
         GenerateLsystem();

     }
    }

    for(auto& l : this->line){
            glm::vec3 color =glm::vec3(settings.Rchannel,
                                       settings.Gchannel,
                                       settings.Bchannel);
            l.setColor(color);
    }
    update(); // asks for a PaintGL() call to occur
}

// ================== Project 6: Action!

void Realtime::keyPressEvent(QKeyEvent *event) {
    m_keyMap[Qt::Key(event->key())] = true;
}

void Realtime::keyReleaseEvent(QKeyEvent *event) {
    m_keyMap[Qt::Key(event->key())] = false;
}

void Realtime::mousePressEvent(QMouseEvent *event) {
    // Set initial mouse position
      m_prevMousePos = event->pos();
}

void Realtime::mouseReleaseEvent(QMouseEvent *event) {
    if (!event->buttons().testFlag(Qt::LeftButton)) {
        m_mouseDown = false;
    }
}

void Realtime::mouseMoveEvent(QMouseEvent *event) {
    // Update angle member variables based on event parameters
       // m_angleX += 10 * (event->position().x() - m_prevMousePos.x()) / (float) width();
       // m_angleY += 10 * (event->position().y() - m_prevMousePos.y()) / (float) height();
        //m_prevMousePos = event->pos();
       // rebuildMatrices();
}

void Realtime::timerEvent(QTimerEvent *event) {
    int elapsedms   = m_elapsedTimer.elapsed();
    float deltaTime = elapsedms * 0.001f;
    m_elapsedTimer.restart();

    // Use deltaTime and m_keyMap here to move around

    update(); // asks for a PaintGL() call to occur
}
void Realtime::wheelEvent(QWheelEvent *event) {
     //Update zoom based on event parameter
        m_zoom -= event->angleDelta().y() / 100.f;
         rebuildMatrices();
}

void Realtime::pickRule(std::vector<string>& arr, std::string& axiom){

    switch(settings.stringRule){
    case 0:{
        arr.push_back("X => F+[[X]-X]-F[-FX]+X");
        arr.push_back( "F => FF");
        axiom = "X";
        if(settings.stringRule != this->stringRule){
            this->angle =  22.5;
            this->stringRule = settings.stringRule;
        }
        break;
    }
    case 1: {
        arr.push_back("1 => 11 ");
        arr.push_back( "0 => 1[+0]-0");
        axiom = "0";
         if(settings.stringRule != this->stringRule){
             this->angle = 45;
             this->stringRule = settings.stringRule;
         }
         break;
    }
    case 2: {
        arr.push_back("F => F-F++F-F");
        axiom = "F++F++F";

        if(settings.stringRule != this->stringRule){
            this->angle = 60;
            this->stringRule = settings.stringRule;
        }
         break;

    }
    case 3 :{
        arr.push_back("a => F[+x]Fb");
        arr.push_back("b => F[-y]Fa");
        arr.push_back("x => a");
        arr.push_back("y => b");
        axiom = "a";
        if(settings.stringRule != this->stringRule){
            this->angle = 45;
            this->step = 0.70;
            this->stringRule = settings.stringRule;
        }
        break;
    }
    case 4 :{
        arr.push_back("X => X[-FFF][+FFF]FX");
        arr.push_back("Y => YFX[+Y][-Y]");
        axiom = "Y";
        if(settings.stringRule != this->stringRule){
            this->angle = 25.7;
            this->stringRule = settings.stringRule;
        }
        break;
    }
    case 5 :{
        arr.push_back("F => FF+[+F-F-F]-[-F+F+F]");
        axiom = "F";
        if(settings.stringRule != this->stringRule){
            this->angle = 22.5;
            this->stringRule = settings.stringRule;
            this->level = 4;
        }
        break;
    }
    case 6 :{
        arr.push_back("F => FF-[XY]+[XY]");
        arr.push_back("X => +FY");
        arr.push_back("Y => -FX");
        axiom = "F";

        if(settings.stringRule != this->stringRule){
            this->angle = 22.5;
            this->stringRule = settings.stringRule;
            this->level = 4;
        }
        break;
    }
    case 7 :{
        arr.push_back("F => FX[FX[+XF]]");
        arr.push_back("X => FF[+XZ++X-F[+ZX]][-X++F-X]");
        arr.push_back("Z => [+F-X-F][++ZX]");
        axiom = "X";

        if(settings.stringRule != this->stringRule){
            this->angle = 22.5;
            this->stringRule = settings.stringRule;
            this->level = 4;
        }
        break;
    }
    case 8 :{
        arr.push_back("F => FXF[-F[-FX]+FX]");
        arr.push_back("X => F++F");
        axiom = "X";
        if(settings.stringRule != this->stringRule){
            this->angle = 22.5;
            this->stringRule = settings.stringRule;
            this->level = 4;
        }
        break;
    }
     default:
    {
        arr.push_back("X => F+[[X]-X]-F[-FX]+X");
        arr.push_back( "F => FF");
        axiom = "X";
        this->level = 5;
        break;
    }
    }
}

void Realtime::pickRuleS(std::vector<string>& arr, std::string& axiom){
    switch(settings.stringRule){
    case 0:{
        arr.push_back("X => F+[[X]-X]-F[-FX]+X (0.7)");
        arr.push_back( "F => FF (0.3)");
        axiom = "X";
        if(settings.stringRule != this->stringRule){
            this->angle =  22.5;
            this->stringRule = settings.stringRule ;
        }
        break;
    }
    case 1: {
        arr.push_back("1 => 11 (0.7)");
        arr.push_back( "0 => 1[+0]-0 (0.3)");
        axiom = "0";
         if(settings.stringRule != this->stringRule){
             this->angle = 45;
             this->stringRule = settings.stringRule ;
         }
         break;
    }
    case 2: {
        arr.push_back("F => F-F++F-F");
        axiom = "F++F++F";

        if(settings.stringRule != this->stringRule){
            this->angle = 60;
            this->stringRule = settings.stringRule ;
        }
         break;

    }
    case 3 :{
        arr.push_back("a => F[+x]Fb (0.25)");
        arr.push_back("b => F[-y]Fa (0.25)");
        arr.push_back("x => a (0.15)");
        arr.push_back("y => b (0.35)");
        axiom = "a";
        if(settings.stringRule != this->stringRule){
            this->angle = 45;
            this->step = 0.70;
            this->stringRule = settings.stringRule ;
        }
        break;
    }
    case 4 :{
        arr.push_back("X => X[-FFF][+FFF]FX (0.7)");
        arr.push_back("Y => YFX[+Y][-Y] (0.3)");
        axiom = "Y";
        if(settings.stringRule != this->stringRule){
            this->angle = 25.7;
            this->stringRule = settings.stringRule ;
        }
        break;
    }
    case 5 :{
        arr.push_back("F => FF+[+F-F-F]-[-F+F+F]");
        axiom = "F";
        if(settings.stringRule != this->stringRule){
            this->angle = 22.5;
            this->stringRule = settings.stringRule ;
        }
        break;
    }
    case 6 :{
        arr.push_back("F => FF-[XY]+[XY] (0.33)");
        arr.push_back("X => +FY (0.44)");
        arr.push_back("Y => -FX (0.22)");
        axiom = "F";

        if(settings.stringRule != this->stringRule){
            this->angle = 22.5;
            this->stringRule = settings.stringRule ;
        }
        break;
    }
    case 7 :{
        arr.push_back("F => FX[FX[+XF]] (0.33)");
        arr.push_back("X => FF[+XZ++X-F[+ZX]][-X++F-X] (0.22)");
        arr.push_back("Z => [+F-X-F][++ZX] (0.44)");
        axiom = "X";

        if(settings.stringRule != this->stringRule){
            this->angle = 22.5;
            this->stringRule = settings.stringRule ;
        }
        break;
    }
    case 8 :{
        arr.push_back("F => FXF[-F[-FX]+FX] (0.7)");
        arr.push_back("X => F++F (0.3)");
        axiom = "X";
        if(settings.stringRule != this->stringRule){
            this->angle = 22.5;
            this->stringRule = settings.stringRule ;
        }
        break;
    }
     default:
    {
        arr.push_back("X => F+[[X]-X]-F[-FX]+X (0.7)");
        arr.push_back( "F => FF (0.3)");
        axiom = "X";
        break;
    }
    }

}

void Realtime::GenerateLsystem(){
    this->angle = settings.Angle;
    this->step = settings.step;
    this->level = settings.level;

    std::vector<string> arr;
    std::string axiom;

    if(settings.enableStochastic){
         pickRuleS(arr, axiom);
         this->enables = settings.enableStochastic;
    }else {
        pickRule(arr, axiom);
        this->enables = settings.enableStochastic;
    }
    glm::vec4 color =glm::vec4(settings.Rchannel,
                               settings.Gchannel,
                               settings.Bchannel,1);

      this->line.resize(0);
      this->line.clear();
      LSystem s = LSystem(this->line);
       s.setAngle(this->angle);
       s.setStep(this->step);
       s.build(axiom, arr,this->level);

}

void Realtime::rebuildMatrices() {
    // Update view matrix by rotating eye vector based on x and y angles
    m_view = glm::mat4(1);
    glm::mat4 rot = glm::rotate(glm::radians(-10 * m_angleX),glm::vec3(0,0,1));
    glm::vec3 eye = glm::vec3(5,0,0);
    eye = glm::vec3(rot * glm::vec4(eye,1));

    rot = glm::rotate(glm::radians(-10 * m_angleY),glm::cross(glm::vec3(0,0,1),eye));
    eye = glm::vec3(rot * glm::vec4(eye,1));

    eye = eye * m_zoom;

    m_view = glm::lookAt(eye,glm::vec3(0,0,0),glm::vec3(0,0,1));
    m_proj = glm::perspective(glm::radians(45.0),1.0 * size().width() / size().width(),0.01,1000.0);

    update();
}

