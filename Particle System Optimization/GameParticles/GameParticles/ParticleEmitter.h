#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Math\Matrix.h"
#include "Math\Vect4D.h"
#include "Particle.h"
#include "Settings.h"

#include <list>

struct ParticleEmitterData
{
	ParticleEmitterData()
		:start_position( 0.0f, 0.0f, 0.0f ),
		start_velocity( 0.0f, 1.0f, 0.0f),
		vel_variance( 1.0f, 4.0f, 0.4f ),
		pos_variance( 1.0f, 1.0f, 1.0f ),
		spawn_frequency( 0.0000001f ),
		max_life( MAX_LIFE ),
		last_spawn( globalTimer::getTimerInSec() ),
		last_loop(  globalTimer::getTimerInSec() ),
		max_particles( NUM_PARTICLES ),
		scale_variance( 2.5f)
	{
	}

	Vect4D	start_position;
	Vect4D	start_velocity;

	Vect4D	vel_variance;
	Vect4D	pos_variance;

	float	max_life;	
	float	spawn_frequency;
	float	last_spawn;
	float	last_loop;
	int		max_particles;


	// added for speed efficiency
	
	float	scale_variance;
};
class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
	
	void SpawnParticle();
	void update();
	void draw();

	void addParticleToList(Particle *p );
	void removeParticleFromList( Particle *p );

	void Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc);
	void resteDrawBuffer();

	void SetupCameraMatrix();

private:
	
	int bufferCount;
	int		last_active_particle;
	Particle * headParticle;
	Particle * drawBuffer;
	ParticleEmitterData * data;
	Matrix transCamera;

};

#endif // PARTICLEEMITTER_H
