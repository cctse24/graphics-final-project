
#pragma once

#include "Turtle.hpp"
#include "StandartGrammar.hpp"
#include "StochasticGrammar.hpp"


class LSystem{
  public:

    LSystem(vector<Line>& line_arr);

    int checkGrammar(vector<string>&);
    void addConstant(char);
    void setStep(float);
    void setAngle(float);
    void build(string, vector<string>&, int);
    void loop();
    Turtle& getTurtle();
  private:

    Turtle turtle;
    vector <char> constants;
    float step;
    float angle;
};
