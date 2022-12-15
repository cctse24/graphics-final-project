#pragma once

#include "LSystemGrammar.h"
#include <ctime>
#include <map>

using namespace std;

class StochasticGrammar : public LSystemGrammar{
  public:
    StochasticGrammar(string axiom, vector<string>& rul):LSystemGrammar(axiom,rul){}
    StochasticGrammar(vector<string>& rul):LSystemGrammar(rul){}
    StochasticGrammar(string axiom):LSystemGrammar(axiom){}
    StochasticGrammar():LSystemGrammar(){}
    void iterate(int);
  private:
    vector<Rule> getRules(vector<string> &);
    map<float, Rule> buildRuleRange(const vector<Rule> &rules);
};
