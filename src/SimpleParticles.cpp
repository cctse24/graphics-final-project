#include "SimpleParticles.hpp"
#include "glm/gtc/random.hpp"

SimpleEmitter::SimpleEmitter()
{
    // create 100 particles
    this->particles.resize( 200 );
    for ( uint i = 0 ; i < this->particles.size() ; ++i )
    {
        // give every particle a random position
        this->particles[i].position.x = glm::linearRand( ( -5.0f ) , ( 5.0f ) );
        this->particles[i].position.y = glm::linearRand( ( -5.0f ) , ( 5.0f ) );
        this->particles[i].position.z = glm::linearRand( ( -1.0f ) , ( 8.0f ) );
        this->particles[i].lifetime = glm::linearRand( ( 100.0f ) , ( 140.0f ) );
    }

    // create a vertex and position buffer
     glGenBuffers(1, &this->vertexBuffer);
     glGenBuffers(1,&this->positionBuffer);

     glGenVertexArrays(1, &VAO);

    // fill the vertex buffer
    std::vector< float > vertices;
    vertices.push_back( 0.0f );
    vertices.push_back( 0.0f );
    vertices.push_back( 0.0f );

    vertices.push_back( 1.0f );
    vertices.push_back( 0.0f );
    vertices.push_back( 0.0f );

    vertices.push_back( 0.0f );
    vertices.push_back( 1.0f );
    vertices.push_back( 0.0f );

    vertices.push_back( 1.0f );
    vertices.push_back( 1.0f );
    vertices.push_back( 0.0f );

    glBindBuffer( GL_ARRAY_BUFFER , this->vertexBuffer );
    glBufferData( GL_ARRAY_BUFFER , vertices.size()*sizeof(float) , vertices.data() , GL_STATIC_DRAW );

    // fill the position buffer
    glBindBuffer( GL_ARRAY_BUFFER , this->positionBuffer );
    glBufferData( GL_ARRAY_BUFFER , this->particles.size()*4*sizeof(float) , this->positions , GL_DYNAMIC_DRAW );

    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void SimpleEmitter::update( const float dt )
{
    for ( uint i = 0 ; i < this->particles.size() ; ++i )
    {
        // subtract from the particles lifetime
        this->particles[i].lifetime -= dt;

        // if the lifetime is below 0 respawn the particle
        if ( this->particles[i].lifetime <= 0.0f )
        {
            this->particles[i].position.x = glm::linearRand( ( -5.0f ) , ( 5.0f ) );
            this->particles[i].position.y = glm::linearRand( ( -5.0f ) , ( 5.0f ) );
            this->particles[i].position.z = glm::linearRand( ( -1.0f ) , ( 8.0f ) );
            this->particles[i].lifetime = glm::linearRand( ( 100.0f ) , ( 140.0f ) );
        }

        // move the particle down depending on the delta time
        this->particles[i].position -= vec3( 0.0f , 0.0f , dt*.05f );

        // update the position buffer
        this->positions[i*4+0] = this->particles[i].position[0];
        this->positions[i*4+1] = this->particles[i].position[1];
        this->positions[i*4+2] = this->particles[i].position[2];
        this->positions[i*4+3] = this->particles[i].lifetime;
    }
}



void SimpleEmitter::draw()
{
    glBindVertexArray(VAO);

    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 4 );

    // update the position buffer
    glBindBuffer( GL_ARRAY_BUFFER , this->positionBuffer );
    glBufferSubData( GL_ARRAY_BUFFER , 0 , this->particles.size()*4*sizeof(float) , this->positions );

    // vertex buffer
    glBindBuffer( GL_ARRAY_BUFFER , this->vertexBuffer );
    glVertexAttribPointer( 0 , 3 , GL_FLOAT , GL_FALSE , 0 , nullptr );

    // position buffer
    glBindBuffer( GL_ARRAY_BUFFER , this->positionBuffer );
    glVertexAttribPointer( 4 , 4 , GL_FLOAT , GL_FALSE , 0 , nullptr );
    glVertexAttribDivisor( 4 , 1 );

    // draw triangles
    glDrawArraysInstanced( GL_TRIANGLE_STRIP , 0 , 4 , this->particles.size() );

    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 4 );

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

SimpleParticleShader::SimpleParticleShader()
{

    m_shader = ShaderLoader::createShaderProgram(":/resources/shaders/particles.vert",
                                                 ":/resources/shaders/particles.frag");

    this->u_M_v =glGetUniformLocation(m_shader, "M_v" );
    this->u_M_p = glGetUniformLocation( m_shader,"M_p" );
    this->u_particleSize = glGetUniformLocation( m_shader,"particleSize" );
}

void SimpleParticleShader::setUniformViewMatrix( const mat4& M_v )
{
     glUniformMatrix4fv(this->u_M_v,1,false, glm::value_ptr(M_v));
}

void SimpleParticleShader::setUniformProjectionMatrix( const mat4& M_p )
{
    glUniformMatrix4fv( this->u_M_p, 1,false, glm::value_ptr(M_p) );
}

GLuint& SimpleParticleShader::get_m_shader(){
    return this->m_shader;
}

void SimpleParticleShader::setUniformParticleSize( const float particleSize )
{
   glUniform1f( this->u_particleSize , particleSize );
}

SimpleController::SimpleController()
{

}

SimpleController::SimpleController(bool init )
{
    this->shader = new SimpleParticleShader();
    this->emitter = new SimpleEmitter();
}

void SimpleController::draw( const float dt , const mat4 M_p , const mat4& M_v )
{
    this->emitter->update( dt );

    glUseProgram(this->shader->get_m_shader());

    this->shader->setUniformProjectionMatrix( M_p );
    this->shader->setUniformViewMatrix( M_v );
    this->shader->setUniformParticleSize( 0.02f );
    this->emitter->draw();

   glUseProgram(0);
}
