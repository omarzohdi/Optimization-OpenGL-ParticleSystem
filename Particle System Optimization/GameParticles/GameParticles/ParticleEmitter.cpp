#include "DO_NOT_MODIFY\Timer\Timer.h"
#include "DO_NOT_MODIFY\Timer\GlobalTimer.h"
#include "DO_NOT_MODIFY\OpenGL\OpenGLInterface.h"

#include <assert.h>

#include "ParticleEmitter.h"
#include "Settings.h"



ParticleEmitter::ParticleEmitter()
	:bufferCount(0),
	last_active_particle( -1 ),
	headParticle(0),
	drawBuffer( new Particle[NUM_PARTICLES])
{
	data = new ParticleEmitterData();
}

ParticleEmitter::~ParticleEmitter()
{
	// do nothing
}


void ParticleEmitter::SetupCameraMatrix()
{
	Matrix cameraMatrix;
	Vect4D camPosVect;
	// get the camera matrix from OpenGL
	glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<float*>(&cameraMatrix));
		
	// get the position from this matrix
	cameraMatrix.get( Matrix::MATRIX_ROW_3, &camPosVect );
	// camera position
	transCamera.setTransMatrix( &camPosVect );
}

void ParticleEmitter::SpawnParticle()
{
	// create another particle if there are ones free
	if( this->last_active_particle < this->data->max_particles-1 )
	{
	
		// create new particle
		Particle *newParticle = new Particle();

		// initialize the particle
		newParticle->data->position = this->data->start_position;
		newParticle->data->velocity = this->data->start_velocity;

		// apply the variance
		this->Execute(newParticle->data->position, newParticle->data->velocity, newParticle->data->scale);

		// increment count
		this->last_active_particle++;

		// add to list
		this->addParticleToList( newParticle );

	}
}

void ParticleEmitter::update()
{
	// get current time
	float current_time = globalTimer::getTimerInSec();

	// spawn particles
	float time_elapsed = current_time - this->data->last_spawn;
	
	// update
	while( this->data->spawn_frequency < time_elapsed )
	{
		// spawn a particle
		this->SpawnParticle();
		// adjust time
		time_elapsed -= this->data->spawn_frequency;
		// last time
		this->data->last_spawn = current_time;
	}
	
	//// total elapsed
	time_elapsed = current_time - this->data->last_loop;

	Particle *p = this->headParticle;
	// walk the particles
	while( p!= 0 )
	{
		// call every particle and update its position 
		p->Update(time_elapsed);

		// if it's live is greater that the max_life 
		// and there is some on the list
		// remove node
		if((p->life > this->data->max_life) && (this->last_active_particle > 0))
		{
			// particle to remove
			Particle *s = p;

			// need to squirrel it away.
			p=p->next;

			// remove last node
			this->removeParticleFromList( s );

			// update the number of particles
			this->last_active_particle--;
		}
		else
		{
			p = p->next;
		}
	}

	p = this->headParticle;
	this->bufferCount = 0;

	while(p != 0)
	{
		// add to buffer
		// track the current count
		drawBuffer[this->bufferCount++] = *p;
		
		// advance ptr
		p = p->next;
	}
	// make sure the counts track (asserts go away in release - relax Christos)
	assert(bufferCount == (this->last_active_particle+1));
	this->data->last_loop = current_time;
}
	   
void ParticleEmitter::addParticleToList(Particle *p )
{
	assert(p);
	if( this->headParticle == 0 )
	{
		this->headParticle = p;
	}
	else 
	{
		headParticle->prev = p;
		p->next = headParticle;
		headParticle = p;
	}

}

void ParticleEmitter::removeParticleFromList( Particle *p )
{
	// make sure we are not screwed with a null pointer
	assert(p);

	if( p->prev == 0 && p->next == 0  )
	{ // only one on the list
		this->headParticle = 0;
	}
	else if( p->prev == 0 && p->next != 0  )
	{ // first on the list
		p->next->prev = 0;
		this->headParticle = p->next;
	}
	else if( p->prev!= 0 && p->next == 0 )
	{ // last on the list 
		p->prev->next = 0;
	}
	else//( p->next != 0  && p->prev !=0 )
	{ // middle of the list
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	
	// bye bye
	delete p;
}

void ParticleEmitter::draw()
{
	// get the camera matrix from OpenGL
	// need to get the position
	Matrix transParticle;
	Matrix rotParticle;
	Matrix scaleMatrix;
	
	// iterate throught the list of particles
	for (int i = 0; i< this->bufferCount; ++i) //while ( p->next != 0)
	{
		// particle position // rotation matrix // scale Matrix
		
		transParticle.setTransMatrix( &drawBuffer[i].data->position);
		rotParticle.setRotZMatrix( drawBuffer[i].data->rotation );
		//scaleMatrix.setScaleMatrix( &drawBuffer[i].data->scale );

		//Scale seems to be useless...
		Matrix M(/*scaleMatrix **/ transCamera * transParticle * rotParticle );

		// set the transformation matrix
		glLoadMatrixf(reinterpret_cast<float*>(&(M)));

		// draw the trangle strip
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		// clears or flushes some internal setting, used in debug, but is need for performance reasons
		// magic...  really it's magic.
		GLenum glError = glGetError();
		glError;
	}
}


void ParticleEmitter::Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc)
{
	// Add some randomness...

	// Ses it's ugly - I didn't write this so don't bitch at me
	// Sometimes code like this is inside real commerical code ( so now you know how it feels )
	
	// x - variance
	float var = (rand() % 1000) * 0.001f;
	int sign = (rand() % 2);
	float *t_pos = reinterpret_cast<float*>(&pos);
	float *t_var = &this->data->pos_variance[x];
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;

	// y - variance
	var =  (rand() % 1000) * 0.001f;
	sign =  (rand() % 2);
	t_pos++;
	t_var++;
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;
	
	// z - variance
	var =  (rand() % 1000) * 0.001f;
	sign =  (rand() % 2);
	t_pos++;
	t_var++;
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;
	
	var =  (rand() % 1000) * 0.001f;
	sign =  (rand() % 2);
	
	// x  - add velocity
	t_pos = &vel[x];
	t_var = &this->data->vel_variance[x];
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;
	
	// y - add velocity
	var =  (rand() % 1000) * 0.001f;
	sign =  (rand() % 2);
	t_pos++;
	t_var++;
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;
	
	// z - add velocity
	var =  (rand() % 1000) * 0.001f;
	sign =  (rand() % 2);
	t_pos++;
	t_var++;
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;
	
	// correct the sign
	var = 2.0f *  (rand() % 1000) * 0.001f;
	sign =  (rand() % 2);
	
	if(sign == 0)
	{
		var *= -1.0f;
	}
	sc = sc * var;
}


// End of file