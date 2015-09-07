/*
 * Matrix.h
 *
 *  Created on: Sep 6, 2015
 *      Author: Kyle
 */

#ifndef SRC_UTILS_MATRIX_H_
#define SRC_UTILS_MATRIX_H_

#include <iostream>
#include <initializer_list>
#include <cassert>

namespace Citrus
{

template <int R, int C>
class Matrix
{
	double data[R][C];

  public:
	Matrix(std::initializer_list<std::initializer_list<double>> cells)
	{
		assert(R == cells.size() && C == cells.begin()->size());
		int r = 0, c = 0;
		for (std::initializer_list<double> row : cells) {
			for (double cell : row) {
				data[r][c] = cell;
				c++;
			}
			r++;
			c = 0;
		}
	}

	Matrix()
	{
	}

	virtual ~Matrix()
	{
	}

	double* operator[](int pos)
	{
		return data[pos];
	}

	template <int nc>
	Matrix<R, nc> operator*(Matrix<C, nc> rhs)
	{
		Matrix<R, nc> product;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < nc; j++) {
				double sum = 0;
				for (int k = 0; k < C; k++) {
					sum += data[i][k] * rhs[k][j];
				}
				product[i][j] = sum;
			}
		}
		return product;
	}

	Matrix<R, C> operator+(Matrix<R, C> rhs)
	{
		Matrix<R, C> sum;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				sum[i][j] = data[i][j] + rhs[i][j];
			}
		}
		return sum;
	}

	Matrix<R, C> operator-(Matrix<R, C> rhs)
	{
		Matrix<R, C> difference;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				difference[i][j] = data[i][j] - rhs[i][j];
			}
		}
		return difference;
	}
};

template <int R>
using Vector = Matrix<R, 1>;

} /* namespace Citrus */

#endif /* SRC_UTILS_MATRIX_H_ */
