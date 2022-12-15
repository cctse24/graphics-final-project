#pragma once

#include <glm/glm.hpp>

// A class representing a virtual camera.

class Camera {
 private:
    glm::vec4 pos;
    glm::vec4 look;
    glm::vec4 up;
    glm::mat4 ViewMatrix =  glm::mat4(1.0f);
    float heightAngle;   // The height angle of the camera in RADIANS
    float AspectRatio;
    glm::mat4 ViewMatrix_inverse;
    glm::mat4 projection_matrix =  glm::mat4(1.0f);
    float k;




public:
    void createPerspective(float aspect, float near, float far);
    Camera();
    Camera(glm::vec4 pos , glm::vec4 look , glm::vec4 up, float heightAngle);
    Camera(glm::vec4 pos , glm::vec4 look , glm::vec4 up, float heightAngle, float ratio);
    glm::vec4 getPos() const;
    glm::vec4 getUp() const ;
    glm::vec4 getlook() const ;
    glm::mat4 getViewMatrix() const;

    glm::mat4 getViewMatrixInverse() const;

    glm::mat4 getProjectionMatrix() const ;

    // Returns the aspect ratio of the camera.
    float getAspectRatio() const;

    // Returns the height angle of the camera in RADIANS.
    float getHeightAngle() const;

    // Returns the focal length of this camera.
    // This is for the depth of field extra-credit feature only;
    // You can ignore if you are not attempting to implement depth of field.
    float getFocalLength() const;

    // Returns the focal length of this camera.
    // This is for the depth of field extra-credit feature only;
    // You can ignore if you are not attempting to implement depth of field.
    float getAperture() const;

    float getdepth() const;
    glm::vec4 worldtocamera(glm::vec4 worldpoint) const ;

    glm::vec4 cameratoworld(glm::vec4 Camerapoint) const ;
};
