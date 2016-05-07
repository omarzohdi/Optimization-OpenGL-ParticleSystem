#include <Math.h>
#include <assert.h>
#include "Vect4d.h"
#include "Matrix.h"



Matrix::Matrix()
	:m0(0.0f),m1(0.0f),m2(0.0f),m3(0.0f),m4(0.0f),m5(0.0f),m6(0.0f),m7(0.0f),m8(0.0f),m9(0.0f),m10(0.0f),m11(0.0f),m12(0.0f),m13(0.0f),m14(0.0f),m15(0.0f)
{	// constructor for the matrix
}

Matrix::Matrix(const Vect4D &row1,const Vect4D &row2,const Vect4D &row3,const Vect4D &row4)
	:m0(row1.x),m1(row1.y),m2(row1.z),m3(row1.w),
	m4(row2.x),m5(row2.y),m6(row2.z),m7(row2.w),
	m8(row3.x),m9(row3.y),m10(row3.z),m11(row3.w),
	m12(row4.x),m13(row4.y),m14(row4.z),m15(row4.w)
{	// constructor for the matrix
}


Matrix::Matrix(float m0,float m1,float m2,float m3,float m4,float m5,float m6,float m7,float m8,float m9,float m10,float m11,float m12,float m13,float m14,float m15)
	:m0(m0),m1(m1),m2(m2),m3(m3),m4(m4),m5(m5),m6(m6),m7(m7),m8(m8),m9(m9),m10(m10),m11(m11),m12(m12),m13(m13),m14(m14),m15(m15)
{	// constructor for the matrix
}

Matrix::Matrix(const Matrix& t)
	:m0(t.m0),m1(t.m1),m2(t.m2),m3(t.m3),m4(t.m4),m5(t.m5),m6(t.m6),m7(t.m7),m8(t.m8),m9(t.m9),m10(t.m10),m11(t.m11),m12(t.m12),m13(t.m13),m14(t.m14),m15(t.m15)
{ // copy constructor
}


Matrix::~Matrix()
{
	// nothign to delete
}

void Matrix::setIdentMatrix()
{ // initialize to the identity matrix
	this->m0 = 1.0;
	this->m1 = 0.0;
	this->m2 = 0.0;
	this->m3 = 0.0;

	this->m4 = 0.0;
	this->m5 = 1.0;
	this->m6 = 0.0;
	this->m7 = 0.0;

	this->m8 = 0.0;
	this->m9 = 0.0;
	this->m10 = 1.0;
	this->m11 = 0.0;
	
	this->m12 = 0.0;
	this->m13 = 0.0;
	this->m14 = 0.0;
	this->m15 = 1.0;
}

void Matrix::setTransMatrix(const Vect4D *t)
{ // set the translation matrix (note: we are row major)
	this->m0 = 1.0;
	this->m1 = 0.0;
	this->m2 = 0.0;
	this->m3 = 0.0;

	this->m4 = 0.0;
	this->m5 = 1.0;
	this->m6 = 0.0;
	this->m7 = 0.0;

	this->m8 = 0.0;
	this->m9 = 0.0;
	this->m10 = 1.0;
	this->m11 = 0.0;
	
	this->m12 = t->x;
	this->m13 = t->y;
	this->m14 = t->z;
	this->m15 = 1.0;
}

void Matrix::set( MatrixRowEnum row, Vect4D *t )
{
	// initialize the rows of the matrix
	switch( row )
	{
	case MATRIX_ROW_0:
		this->m0 = t->x;
		this->m1 = t->y;
		this->m2 = t->z;
		this->m3 = t->w;
		break;

	case MATRIX_ROW_1:
		this->m4 = t->x;
		this->m5 = t->y;
		this->m6 = t->z;
		this->m7 = t->w;
		break;

	case MATRIX_ROW_2:
		this->m8 = t->x;
		this->m9 = t->y;
		this->m10 = t->z;
		this->m11 = t->w;
		break;

	case MATRIX_ROW_3:
		this->m12 = t->x;
		this->m13 = t->y;
		this->m14 = t->z;
		this->m15 = t->w;
		break;

	default:
		// should never get here, if we are here something bad has happened
		assert(0);
	}
}

float &Matrix::operator[](INDEX_ENUM e)
{
	// get the individual elements
	switch(e)
	{
	case 0:
		return m0;
	case 1:
		return m1;
	case 2:
		return m2;
	case 3:
		return m3;
	case 4:
		return m4;
	case 5:
		return m5;
	case 6:
		return m6;
	case 7:
		return m7;
	case 8:
		return m8;
	case 9:
		return m9;
	case 10:
		return m10;
	case 11:
		return m11;
	case 12:
		return m12;
	case 13:
		return m13;
	case 14:
		return m14;
	case 15:
		return m15;
	default:
		assert(0);
		return m0;
	}
}


void Matrix::get( MatrixRowEnum row, Vect4D *t )
{ // get a row of the matrix
	switch( row )
	{
	case MATRIX_ROW_0:
		t->x = this->m0;
		t->y = this->m1;
		t->z = this->m2;
		t->w = this->m3;
		break;

	case MATRIX_ROW_1:
		t->x = this->m4;
		t->y = this->m5;
		t->z = this->m6;
		t->w = this->m7;
		break;

	case MATRIX_ROW_2:
		t->x = this->m8;
		t->y = this->m9;
		t->z = this->m10;
		t->w = this->m11;
		break;

	case MATRIX_ROW_3:
		t->x = this->m12;
		t->y = this->m13;
		t->z = this->m14;
		t->w = this->m15;
		break;

	default:
		assert(0);
	}
}


Matrix Matrix::operator*(const Matrix& rhs) 
{ // matrix multiplications

	return Matrix(
	(m0*rhs.m0) + (m1*rhs.m4) + (m2*rhs.m8) + (m3*rhs.m12),
	(m0*rhs.m1) + (m1*rhs.m5) + (m2*rhs.m9) + (m3*rhs.m13),
	(m0*rhs.m2) + (m1*rhs.m6) + (m2*rhs.m10) + (m3*rhs.m14),
	(m0*rhs.m3) + (m1*rhs.m7) + (m2*rhs.m11) + (m3*rhs.m15),
	
	(m4*rhs.m0) + (m5*rhs.m4) + (m6*rhs.m8) + (m7*rhs.m12),
	(m4*rhs.m1) + (m5*rhs.m5) + (m6*rhs.m9) + (m7*rhs.m13),
	(m4*rhs.m2) + (m5*rhs.m6) + (m6*rhs.m10) + (m7*rhs.m14),
	(m4*rhs.m3) + (m5*rhs.m7) + (m6*rhs.m11) + (m7*rhs.m15),
	
	(m8*rhs.m0) + (m9*rhs.m4) + (m10*rhs.m8) + (m11*rhs.m12),
	(m8*rhs.m1) + (m9*rhs.m5) + (m10*rhs.m9) + (m11*rhs.m13),
	(m8*rhs.m2) + (m9*rhs.m6) + (m10*rhs.m10) + (m11*rhs.m14),
	(m8*rhs.m3) + (m9*rhs.m7) + (m10*rhs.m11) + (m11*rhs.m15),
	
	(m12*rhs.m0) + (m13*rhs.m4) + (m14*rhs.m8) + (m15*rhs.m12),
	(m12*rhs.m1) + (m13*rhs.m5) + (m14*rhs.m9) + (m15*rhs.m13),
	(m12*rhs.m2) + (m13*rhs.m6) + (m14*rhs.m10) + (m15*rhs.m14),
	(m12*rhs.m3) + (m13*rhs.m7) + (m14 *rhs.m11) + (m15*rhs.m15));
}

Matrix& Matrix::operator/=(const float& rhs)
{ 
	// divide each element by a value
	// using inverse multiply trick, faster that individual divides
	float inv_rhs = (1.0f/rhs);

	m0 *= inv_rhs;
	m1 *= inv_rhs;
	m2 *= inv_rhs;
	m3 *= inv_rhs;
	m4 *= inv_rhs;
	m5 *= inv_rhs;
	m6 *= inv_rhs;
	m7 *= inv_rhs;
	m8 *= inv_rhs;
	m9 *= inv_rhs;
	m10 *= inv_rhs;
	m11 *= inv_rhs;
	m12 *= inv_rhs;
	m13 *= inv_rhs;
	m14 *= inv_rhs;
	m15 *= inv_rhs;

	return *this;
}

float Matrix::Determinant() 
{
	return (
			(m0 * ((m5 * ((m10 * m15) - (m11 * m14))) - (m6 * ((m9 * m15) - (m11 * m13))) + (m7 * ((m9 * m14) - (m10 * m13)))))
			- (m1 * ((m4 * ((m10 * m15) - (m11 * m14))) - (m6 * ((m8 * m15) - (m11 * m12))) + (m7 * ((m8 * m14) - (m10 * m12)))))
			+ (m2 * ((m4 * ((m9 * m15) - (m11 * m13))) - (m5 * ((m8 * m15) - (m11 * m12))) + (m7 * ((m8 * m13) - (m9 *  m12)))))
			- (m3 * ((m4 * ((m9 * m14) - (m10 * m13))) - (m5 * ((m8 * m14) - (m10 * m12))) + (m6 * ((m8 * m13) - (m9 *  m12)))))
			);
	
}

Matrix Matrix::GetAdjugate() 
{
	return Matrix (
	((m5*((m10*m15) - (m11*m14))) - (m6*((m9*m15) - (m11*m13))) + (m7*((m9*m14) - (m10*m13)))),
	-((m1*((m10*m15) - (m11*m14))) - (m2*((m9*m15) - (m11*m13))) + (m3*((m9*m14) - (m10*m13)))),
	(m1*((m6*m15) - (m7*m14))) - (m2*((m4*m15) - (m7*m12))) + (m3*((m5*m14) - (m6*m13))),
	-( (m1*((m6*m11) - (m7*m10))) - (m2*((m5*m11) - (m7*m9))) + (m3*((m5*m10) - (m6*m9)))),
	-((m4*((m10*m15) - (m11*m14))) - (m6*((m8*m15) - (m11*m12))) + (m7*((m8*m14) - (m10*m12)))),
	(m0*((m10*m15) - (m11*m14))) - (m2*((m8*m15) - (m11*m12))) + (m3*((m8*m14) - (m10*m12))),
	-((m0*((m6*m15) - (m7*m14))) - (m2*((m4*m15) - (m7*m12))) + (m3*((m4*m14) - (m6*m12)))),
	(m0*((m6*m11) - (m7*m10))) - (m2*((m4*m11) - (m7*m8))) + (m3*((m4*m10) - (m6*m8))),
	(m4*((m9*m15) - (m11*m13))) - (m5*((m8*m15) - (m11*m12))) + (m7*((m8*m13) - (m9*m12))),
	-((m0*((m9*m15) - (m11*m13))) - (m1*((m8*m15) - (m11*m12))) + (m3*((m8*m13) - (m9*m12)))),
	(m0*((m5*m15) - (m7*m13))) - (m1*((m4*m15) - (m7*m12))) + (m3*((m4*m13) - (m5*m12))),
	-((m0*((m5*m11) - (m7*m9))) - (m1*((m4*m11) - (m7*m8))) + (m3*((m4*m9) - (m5*m8)))),
	-((m4*((m9*m14) - (m10*m13))) - (m5*((m8*m14) - (m10*m12))) + (m6*((m8*m13) - (m9*m12)))),
	(m0*((m9*m14) - (m10*m13))) - (m1*((m8*m14) - (m10*m12))) + (m2*((m8*m13) - (m9*m12))),
	-( (m0*((m5*m14) - (m6*m13))) - (m1*((m4*m14) - (m6*m12))) + (m3*((m4*m13) - (m5*m12)))),
	(m0*((m5*m10) - (m6*m9))) - (m1*((m4*m10) - (m6*m8))) + (m2*((m4*m9) - (m5*m8)))
	);

}

void Matrix::Inverse( Matrix &out ) 
{
	float det = Determinant();
	if(fabs(det) >= 0.0001f)
	{
		out = GetAdjugate();
		out /= det;

	}
}

void Matrix::setScaleMatrix(const Vect4D *scale)
{
	this->m0 = scale->x;
	this->m5 = scale->y;
	this->m10 = scale->z;
	this->m15 = 1.0f;
}

void Matrix::setRotZMatrix(const float& az)
{
	this->m0 = cos(az);
	this->m1 = -sin(az);
	this->m4 = sin(az);
	this->m5 = cos(az);
	this->m10 = 1.0f;
	this->m15 = 1.0f;
}

// End of file