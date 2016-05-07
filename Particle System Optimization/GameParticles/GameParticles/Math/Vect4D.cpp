#include <math.h>
#include <assert.h>
#include <xmmintrin.h>
#include <smmintrin.h>

#include "Vect4D.h"


Vect4D::Vect4D()
	:x(0.0f),y(0.0f),z(0.0f),w(1.0f)
{}

Vect4D::Vect4D( const float& tx, const float& ty, const float& tz, const float& tw )
	:x(tx),y(ty),z(tz),w(tw)
{}

Vect4D::~Vect4D()
{
	// nothing to delete
}

inline float Vect4D::_mag(__m128 v)
{
  return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v, v, 0x71)));
}

inline __m128 Vect4D::LoadFloat3(const Vect4D& value)
{
	__m128 x = _mm_load_ss(&value.x);
	__m128 y = _mm_load_ss(&value.y);
	__m128 z = _mm_load_ss(&value.z);
	__m128 xy = _mm_movelh_ps(x, y);
	
	return _mm_shuffle_ps(xy, z, _MM_SHUFFLE(2, 0, 2, 0));
}

void Vect4D::norm(Vect4D& out)
{
	float mag = _mag(LoadFloat3(out));

	if( 0.0f < mag )
	{
		out.x = this->x / mag;
		out.y = this->y / mag;
		out.z = this->z / mag;
		out.w = 1.0f;
	}
}

void Vect4D::operator += (const Vect4D& t ) 
{
	this->x += t.x;
	this->y += t.y;
	this->z += t.z;
}

Vect4D Vect4D::operator + (const Vect4D& t ) 
{
	return Vect4D(this->x + t.x, this->y + t.y, this->z + t.z);
}

Vect4D Vect4D::operator - ( const Vect4D& t )
{
	return Vect4D(this->x - t.x, this->y - t.y, this->z - t.z);
}

Vect4D Vect4D::operator *(const float& scale)
{
	return Vect4D(this->x * scale,this->y * scale,this->z * scale);
}

float& Vect4D::operator[]( VECT_ENUM e )
{
	switch(e)
	{
	case 0:
			return x;			
	case 1:
			return y;			
	case 2: 
			return z;			
	case 3:
			return w;
	default:
			assert(0);
			return x;
	}
}

void Vect4D::Cross( Vect4D& vin, Vect4D& vout)
{
	vout.x = (y*vin.z - z*vin.y);
	vout.y = (z*vin.x - x*vin.z);
	vout.z = (x*vin.y - y*vin.x);
	vout.w = 1.0f;
}

void Vect4D::set(const float& tx, const float& ty, const float& tz, const float& tw)
{
	this->x = tx;
	this->y = ty;
	this->z = tz;
	this->w = tw;
}

// End of file