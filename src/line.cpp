#include "line.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include <GL/glew.h>
#include <iostream>
#include <ostream>


void writeVec2( vector<float>  &out, const crushedpixel::Vec2 &vec) {
    // write vertices as two consecutive floats
    out.push_back(vec.x);
    out.push_back(vec.y);
}

glm::vec3 generateRandomColor(glm::vec3 mix) {
    srand(time(0));

    int red = arc4random() % 256;
    int green = arc4random() % 256;
    int blue = arc4random() % 256;


        int r = (red + mix.x) / 2;
        int g = (green + mix.y) / 2;
        int b = (blue + mix.z) / 2;

    glm::vec3 color = glm::vec3(r, g, b);
    return color;
}

Line::Line(){
}

 Line::Line(vec3 start,
            vec3 end,
            float thickness): 	points{
    {end.x, end.z},
  {start.x, start.z},
} {


     startPoint = start;
     endPoint = end;
     lineColor = vec3(1,1,1);

     glGenBuffers(1, &VBO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);

      polyline_vertices = crushedpixel::Polyline2D::create(
                 points, thickness,
                 crushedpixel::Polyline2D::JointStyle::ROUND,
                 crushedpixel::Polyline2D::EndCapStyle::SQUARE);


      numPoints = (GLsizei) points.size();
      numVertices = (GLsizei) polyline_vertices.size();

      // write original points, followed by vertices, to buffer
          vector<float> buffer;
          for (auto &vertex : points) {
              writeVec2(buffer, vertex);
          }
          for (auto &vertex : polyline_vertices) {
              writeVec2(buffer, vertex);
          }

     glBufferData(GL_ARRAY_BUFFER, sizeof(float)*buffer.size(),
                  buffer.data(), GL_STATIC_DRAW);

     glGenVertexArrays(1, &VAO);
     glBindVertexArray(VAO);

     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
     glEnableVertexAttribArray(0);

     glBindBuffer(GL_ARRAY_BUFFER, 0);
     glBindVertexArray(0);
     glm::vec3 color = glm::vec3(0,255,0);
     setColor(color);
}


 void Line::setColor(vec3& color) {

     this->lineColor.x = fmin(color.x / 255.0F, 1.0F);
     this->lineColor.y = fmin(color.y / 255.0F, 1.0F);
     this->lineColor.z = fmin(color.z / 255.0F, 1.0F);
     auto test = generateRandomColor(color);

     wireframeColor.x =  fmin(test.x / 255.0F, 1.0F) ;
     wireframeColor.y =  fmin(test.y / 255.0F, 1.0F) ;
     wireframeColor.z = fmin(test.z / 255.0F, 1.0F) ;
 }


 void Line::DeleteLine(){

     glDeleteVertexArrays(1, &VAO);
     glDeleteBuffers(1, &VBO);
 }


 void Line::draw(GLuint& m_shader,
                 glm::mat4& m_view,
                 glm::mat4& m_proj ){

      auto location = glGetUniformLocation(m_shader, "view_matrix");
     glUniformMatrix4fv(location,1,false, glm::value_ptr(m_view));
     location = glGetUniformLocation(m_shader, "projection_matrix");
     glUniformMatrix4fv(location,1,false, glm::value_ptr(m_proj));

     glUniformMatrix4fv(glGetUniformLocation(m_shader, "view_matrix"), 1, GL_FALSE, &m_view[0][0]);
     glUniformMatrix4fv(glGetUniformLocation(m_shader, "projection_matrix"), 1, GL_FALSE, &m_proj[0][0]);

     posInAttribLocation = glGetAttribLocation(m_shader, "posIn");
     colorUniformLocation = glGetUniformLocation(m_shader, "color");
     glBindVertexArray(VAO);

     {   // draw wireframe

             glUniform4f(colorUniformLocation,
                             wireframeColor.x,
                             wireframeColor.y,
                             wireframeColor.z,
                             1);

             glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
             glDrawArrays(GL_TRIANGLES, numPoints, numVertices);
         }

         {   // fill solid

             glUniform4f(colorUniformLocation,
                             lineColor.x,
                             lineColor.y,
                             lineColor.z,
                             1);

             glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
             glDrawArrays(GL_TRIANGLES, numPoints, numVertices);
         }

     glBindVertexArray(0);
 }





