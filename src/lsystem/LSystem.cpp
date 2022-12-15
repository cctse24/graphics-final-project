#include "LSystem.hpp"

LSystem::LSystem(vector<Line>& line_arr):
    turtle(Turtle(line_arr)){

}

int LSystem::checkGrammar(vector<string>& rules){
  string r = rules[0];
  short pos = r.find(" (");
  if (-1 != pos)
    return 1;
  else
    return 0;
}


void LSystem::addConstant(char constant){
    constants.push_back(constant);
}

void LSystem::setStep(float _step){
  step = _step;
}

void LSystem::setAngle(float _angle){
  angle = _angle;
}

void LSystem::build(string axiom,
                    vector<string>& rules,
                    int iterations){
    string result;
        if(checkGrammar(rules) == 0){
          StandartGrammar ls(axiom, rules);
          ls.iterate(iterations);
          result = ls.getResult();
        }
        else{

          StochasticGrammar ls(axiom, rules);
          ls.iterate(iterations);
          result = ls.getResult();
        }

        turtle.init(step, angle);
        turtle.interpret(result, constants);

}

Turtle& LSystem::getTurtle(){
    return this->turtle;
}


