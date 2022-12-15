#include "Turtle.hpp"
#include "glm/gtx/string_cast.hpp"

Turtle::Turtle(vector<Line>& line_arr):
    Line_arr(line_arr){

  direction = degToRad(90);
}

bool Turtle::getPen() {
  return pen;
}

void Turtle::setPen(bool npen) {
  pen = npen;
}

void Turtle::init(float _step, float _angle){
    step = _step;
    angle = _angle;
}

void Turtle::moveto(float x1, float z1){

  x = x1;
  z = z1;
}

const vector<Line>& Turtle::get_arr_lin() const{
   return this->Line_arr;
}


void Turtle::move(float distance){

  float dx = x + distance * cos(direction);
  float dz = z + distance * sin(direction);

  //Append this position to the vertex vector
  if (getPen()){
    glm::vec2 tmp_x, tmp_z;
    tmp_x = glm::vec2(x, z);
    tmp_z = glm::vec2(dx, dz);

    Line line1 = Line(glm::vec3(tmp_x.x,0,tmp_x.y),
                      glm::vec3(tmp_z.x,0,tmp_z.y) ,
               thickness);
       this->Line_arr.push_back(line1);
  }

  x = dx;
  z = dz;
}

void Turtle::turnRight(float angle){
  /* Turn the turtle to the right side */
    direction -= degToRad(angle);
    thickness = 0.6*thickness;
    //point_size = 0.6 *point_size;
    thickness = std::fmaxf(0.003, thickness);
   // point_size =  std::fmaxf(0.003, point_size);
}

void Turtle::turnLeft(float angle){
  /* Turn the turtle to the left side */
    direction += degToRad(angle);
    thickness = 0.6*thickness;
    //point_size = 0.6 *point_size;
    thickness = std::fmaxf(0.003, thickness);
    //point_size =  std::fmaxf(0.003, point_size);

}

void Turtle::save(){
  save_stack.push(x);
  save_stack.push(z);
  save_stack.push(direction);
  save_stack.push(thickness);
}

void Turtle::restore(){
  thickness = save_stack.top();
  save_stack.pop();
  direction = save_stack.top();
  save_stack.pop();
  float nz = save_stack.top();
  save_stack.pop();
  float nx = save_stack.top();
  save_stack.pop();
  x = nx;
  z = nz;
}

float Turtle::degToRad(float deg){
	return deg*0.0174532925;
}

// --------------- Drawing methods ---------------

void Turtle::penDown(){
  /* Lowers the pen-the turtle, after which
   * she leaves a trail when moving
   */
   setPen(true);
}

void Turtle::penUp(){
  /* Lifts the pen the turtle, after which
   * it ceases to leave a trail when moving
   */
   setPen(false);
}

// --------------- Interpret methods ---------------

void Turtle::interpret(string result, vector<char>& constants){
    /* interpretation of the alphabet in a certain action turtles */
    for (unsigned int i = 0, size = result.size(); i < size ; ++i) {
      switch (result[i]) {
        case '+':
          turnLeft(angle);
        break;
        case '-':
          turnRight(angle);
        break;
        case '[':
          save();
        break;
        case ']':
          restore();
        break;
        default:
          if (find(constants.begin(), constants.end(), result[i]) == constants.end()){

               move(step);
          }

        break;
      }
    }
  }


