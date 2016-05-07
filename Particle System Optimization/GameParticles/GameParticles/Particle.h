#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"

struct ParticleData
{
	ParticleData()
		:position( 0.0f, 0.0f,  0.0f ),velocity( 0.0f, 0.0f,  0.0f ),scale( 1.0f, 1.0f, 1.0f )
	{
		this->rotation = 0.0f;
		this->rotation_velocity = 0.5f;
	}

	Vect4D	position;
	Vect4D	velocity;
	Vect4D	scale;

	float	rotation_velocity;
	float	rotation;


};

class Particle
{
public:
	friend class ParticleEmitter;
	
	Particle();
	Particle(const float _life, const Particle * next, const Particle * prev);
	~Particle();
	void Update(const float& time_elapsed);
	void CopyDataOnly( const Particle *p );
private:

	ParticleData *data;

	float	life;
	Particle *next;
	Particle *prev;


};


#endif //PARTICLE_H
