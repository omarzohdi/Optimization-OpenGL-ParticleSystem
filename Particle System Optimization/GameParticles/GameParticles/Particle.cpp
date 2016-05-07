#include "Particle.h"
#include "Matrix.h"

Vect4D z_axis(0.0f, -0.25f, 1.0f);
Vect4D v(3.0f,4.0f,0.0f);

Particle::Particle()
	:data(new ParticleData()),life(0.0f),next(0),prev(0)
{}

Particle::~Particle()
{
}

void Particle::CopyDataOnly( const Particle *p )
{
	// copy the data only
	// this way of copying data is more efficient that element by element
	this->data->position			= p->data->position;
	this->data->velocity			= p->data->velocity;
	this->data->scale				= p->data->scale;
	this->data->rotation			= p->data->rotation;
	this->data->rotation_velocity	= p->data->rotation_velocity;
	this->life						= p->life;
}

void Particle::Update(const float& time_elapsed)
{
	// serious math below - magic secret sauce
	life += time_elapsed;

	data->position = data->position + (data->velocity * time_elapsed);

	data->position.Cross( z_axis, v);
	v.norm(v);
	data->position  += (v * 0.05f * life);

	data->rotation += (data->rotation_velocity * time_elapsed *2.01f);
}


// End of file


