#ifndef MATRIX_H
#define MATRIX_H

// includes
#include "Enum.h"

// forward declare
class Vect4D;

// class
class Matrix
{
public:

	// local enumerations
	enum MatrixRowEnum
	{
		MATRIX_ROW_0,
		MATRIX_ROW_1,
		MATRIX_ROW_2,
		MATRIX_ROW_3
	};

	Matrix();
	Matrix(float m0,float m1,float m2,float m3,float m4,float m5,float m6,float m7,float m8,float m9,float m10,float m11,float m12,float m13,float m14,float m15);
	Matrix::Matrix(const Vect4D &row1,const Vect4D &row2,const Vect4D &row3,const Vect4D &row4);
	Matrix( const Matrix& t );	
	~Matrix();

	void set( MatrixRowEnum row, Vect4D *t );
	void get( MatrixRowEnum row, Vect4D *vOut );

	void setIdentMatrix();
	void setTransMatrix(const Vect4D *t );
	void setScaleMatrix(const Vect4D *s );
	void setRotZMatrix( const float& Z_Radians );

	float &operator[]( INDEX_ENUM e);
	
	Matrix operator*( const Matrix &t );
	Matrix operator*( const float& s );

	float Determinant();
	
	Matrix GetAdjugate();
	Matrix& Matrix::operator/=(const float& t);
	
	void Matrix::Inverse( Matrix &out );
	
private:

	// ROW 0
	float m0;
	float m1;
	float m2;
	float m3;

	// ROW 1
	float m4;
	float m5;
	float m6;
	float m7;

	// ROW 2
	float m8;
	float m9;
	float m10;
	float m11;

	// ROW 3
	float m12;
	float m13;
	float m14;
	float m15;
};

#endif  // Matrix.h
