#pragma once

typedef struct vector_s
{
	double x;
	double y;
}
vector_t;

/// Create new vector
vector_t vec_create(double x, double y);

/// Vector addition a + b
vector_t vec_add(vector_t a, vector_t b);

/// Vector subtraction a - b
vector_t vec_sub(vector_t a, vector_t b);

/// Vector scalar multiplication a * n
vector_t vec_mult_scalar(vector_t a, double n);

/// Vector scalar addition a + n
vector_t vec_add_scalar(vector_t a, double n);
