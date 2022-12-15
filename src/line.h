#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"
#include <vector>
#include <GL/glew.h>
#include "Polyline2D/include/Polyline2D.h"
using glm::mat4;
using glm::vec3;
using glm::radians;
using glm::lookAt;
using std::vector;


class Line {
private:
    GLuint VBO, VAO;
    vec3 startPoint;
    vec3 endPoint;
    vec3 lineColor;
    vec3 wireframeColor;
    const std::vector<crushedpixel::Vec2> points;
    vector<crushedpixel::Vec2> polyline_vertices;

    GLuint posInAttribLocation;
    GLuint colorUniformLocation;
    GLsizei numPoints, numVertices;
public:

    Line();

    Line(vec3 start,
                vec3 end,
                float thickness);

    void setColor(vec3& lineColor);

    void draw(GLuint& m_shader,
                    glm::mat4& m_view,
                    glm::mat4& m_proj );

    void DeleteLine();
};
