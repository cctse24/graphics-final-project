
#pragma once

#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "line.h"
#include "glm/gtc/type_ptr.hpp"
#include <GL/glew.h>

using namespace std;

class Turtle{
  public:
    // --------------- Methods of movement ---------------
    Turtle(vector<Line>& line_arr);
    void moveto(float, float);
    void move(float);
    void turnRight(float);
    void turnLeft(float);
    void save();
    void restore();
    float degToRad(float);
    const vector<Line>& get_arr_lin() const;
    // --------------- Drawing methods ---------------

    void penDown();
    void penUp();

    void interpret(string, vector<char>&);
    void init(float, float);

  private:
    // --------------- Getters and Setters ---------------
    bool getPen();

    float thickness = 0.1f;
    void setPen(bool);
    float step;
    float angle;
    vector<Line>& Line_arr;
    float x = 0.0f; //Current position of the turtle
    float z = -5.f; //Current position of the turtle
    float direction = 0.f;  // he position of the turtle's head in space( in degrees )
    bool pen = true;
    stack <float> save_stack; // stack to store coordinates
};
