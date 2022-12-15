#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "lsystem/LSystem.hpp"
#include <unordered_map>
#include "utils/shaderloader.h"

class SimpleEmitter
{
public:
	SimpleEmitter();

	void update( const float dt );

	void draw();

private:
	struct Particle
	{
        vec3 position;
		float lifetime;
	};
    std::vector< Particle > particles;

    float positions[800];

	GLuint vertexBuffer;
    GLuint positionBuffer;
    GLuint VAO;
};

class SimpleParticleShader
{
public:
	SimpleParticleShader();
    void setUniformViewMatrix( const mat4& M_v );
    void setUniformProjectionMatrix( const mat4& M_p );
	void setUniformParticleSize( const float particleSize );
    GLuint& get_m_shader();

private:
    GLuint m_shader ;
	GLuint u_M_v;
	GLuint u_M_p;
	GLuint u_particleSize;
};

class SimpleController
{
public:
	SimpleController();
    SimpleController(bool init );
    void draw( const float dt , const mat4 M_p , const mat4& M_v );

private:
	SimpleParticleShader* shader;

	SimpleEmitter* emitter;
};
