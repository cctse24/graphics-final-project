#include <iostream>
#include <stdexcept>
#include "camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtx/string_cast.hpp"
Camera::Camera()  {

}
Camera::Camera(glm::vec4 pos , glm::vec4 look , glm::vec4 up, float heightAngle){
    glm::vec4 v_1 = {1, 0 ,0,0};
    glm::vec4 v_2 = {0, 1 ,0,0};
    glm::vec4 v_3 = {0, 0 ,1,0};
    glm::vec4 v_4 = {-1*pos[0], -1*pos[1] ,-1*pos[2],1};
    glm::mat4 mt ;
    mt[0]= v_1;
    mt[1]= v_2;
    mt[2]= v_3;
    mt[3]= v_4;
    auto w = -glm::vec3(look);
    w =glm::normalize(w);
    auto v = glm::vec3(up) - dot(glm::vec3(up), w)*w;
    v= glm::normalize(v);
    auto u = cross(v, w);
    glm::vec4 v_11= {u[0],  v[0] ,w[0],0};
    glm::vec4 v_22 = {u[1], v[1] ,w[1],0};
    glm::vec4 v_33 = {u[2], v[2] ,w[2],0};
    glm::vec4 v_44 = {0, 0 ,0,1};
    glm::mat4 mr;
    mr[0]= v_11;
    mr[1]= v_22;
    mr[2]= v_33;
    mr[3]= v_44;
    this->ViewMatrix =  mr*mt;
    this->heightAngle = heightAngle;
    this->look = look;
    this->up = up ;
    this->pos = pos;
    this->ViewMatrix_inverse = glm::inverse(this->ViewMatrix);
    this->k = 1;
}
 Camera::Camera(glm::vec4 pos , glm::vec4 look , glm::vec4 up, float heightAngle,
                float ratio)  {
     glm::vec4 v_1 = {1, 0 ,0,0};
     glm::vec4 v_2 = {0, 1 ,0,0};
     glm::vec4 v_3 = {0, 0 ,1,0};
     glm::vec4 v_4 = {-1*pos[0], -1*pos[1] ,-1*pos[2],1};
     glm::mat4 mt ;
     mt[0]= v_1;
     mt[1]= v_2;
     mt[2]= v_3;
     mt[3]= v_4;
     auto w = -glm::vec3(look);
     w =glm::normalize(w);
     auto v = glm::vec3(up) - dot(glm::vec3(up), w)*w;
     v= glm::normalize(v);
     auto u = cross(v, w);

    glm::vec4 v_11= {u[0],  v[0] ,w[0],0};
    glm::vec4 v_22 = {u[1], v[1] ,w[1],0};
    glm::vec4 v_33 = {u[2], v[2] ,w[2],0};
    glm::vec4 v_44 = {0, 0 ,0,1};
    glm::mat4 mr;
    mr[0]= v_11;
    mr[1]= v_22;
    mr[2]= v_33;
    mr[3]= v_44;

    this->ViewMatrix =  mr*mt;
    this->heightAngle = heightAngle;
    this->look = look;
    this->up = up ;
    this->pos = pos;
    this->ViewMatrix_inverse = glm::inverse(this->ViewMatrix);
    this->k = 1;

}
 glm::vec4 Camera::getPos() const  {
     // Optional TODO: implement the getter or make your own design
     return this->pos;
 }

 glm::vec4 Camera::getUp() const  {
     // Optional TODO: implement the getter or make your own design
     return this->up;
 }
 glm::vec4 Camera::getlook() const  {
     // Optional TODO: implement the getter or make your own design
     return this->look;
 }

glm::mat4 Camera::getViewMatrix() const {
    // Optional TODO: implement the getter or make your own design
    return this->ViewMatrix;
}

glm::mat4 Camera::getViewMatrixInverse () const {
    // Optional TODO: implement the getter or make your own design
    return this->ViewMatrix_inverse;
}
glm::mat4 Camera::getProjectionMatrix() const {
    return this->projection_matrix;
 }

float Camera::getAspectRatio() const {
    // Optional TODO: implement the getter or make your own design
    return this->AspectRatio;
}

float Camera::getHeightAngle() const {
    // Optional TODO: implement the getter or make your own design
    return this->heightAngle;
}

glm::vec4 Camera::worldtocamera(glm::vec4 worldpoint) const  {

    return this->ViewMatrix * worldpoint;

}

glm::vec4 Camera::cameratoworld(glm::vec4 Camerapoint) const  {

    return this->ViewMatrix_inverse * Camerapoint;

}

float Camera::getdepth() const {
    // Optional TODO: implement the getter or make your own design
    return this->k;
}

float Camera::getFocalLength() const {
    // Optional TODO: implement the getter or make your own design
    throw std::runtime_error("not implemented");
}

float Camera::getAperture() const {
    // Optional TODO: implement the getter or make your own design
    throw std::runtime_error("not implemented");
}


void Camera::createPerspective( float aspect, float near, float far)   {
    this->AspectRatio = aspect;
    float width_angle = aspect * this->heightAngle;

    float c = (-near)/far;
    float half_width = width_angle/2.0;
    float half_hight = this->getHeightAngle()/2.0;
    float scale_x = 1.0/(far*glm::tan(half_width));
    float scale_y = 1.0/(far*glm::tan(half_hight));
    float scale_z = 1.0/far;
    glm::vec4 v0 = glm::vec4(scale_x ,0,0,0);
    glm::vec4 v1 = glm::vec4(0,scale_y,0,0);
    glm::vec4 v2 = glm::vec4(0,0,scale_z,0);
    glm::vec4 v3 = glm::vec4(0,0,0,1);
    glm::mat4 s = glm::mat4{v0,v1,v2,v3};

    float m_z = 1.0/(1.0+c);
    float m_z_1 = -c/(1.0+c);
    glm::vec4 v00 = glm::vec4(1,0,0,0);
    glm::vec4 v11 = glm::vec4(0,1,0,0);
    glm::vec4 v22 = glm::vec4(0,0,m_z,-1);
    glm::vec4 v33 = glm::vec4(0,0,m_z_1,0);
    glm::mat4 m = glm::mat4{v00,v11,v22,v33};

    glm::vec4 v000 = glm::vec4(1,0,0,0);
    glm::vec4 v111 = glm::vec4(0,1,0,0);
    glm::vec4 v222 = glm::vec4(0,0,-2,0);
    glm::vec4 v333 = glm::vec4(0,0,-1,1);
    glm::mat4 rem = glm::mat4{v000,v111,v222,v333};

    this->projection_matrix = rem*m*s;

}



