package org.usfirst.frc.team1678.robot.math;

public class Matrix {
	public int rows, cols;
	private double[][] data;

	/**
	 * Normal initialization
	 * @param rows The amount of rows to use
	 * @param cols The amount of columns to use
	 */
	public Matrix(int rows, int cols) {
		data = new double[rows][cols];
		this.cols = cols;
		this.rows = rows;
	}

	/**
	 * Vector initialization
	 * @param rows The amount of rows to use; cols will automatically be set to 1 
	 */
	public Matrix(int rows) {
		this(rows, 1);
	}

	/**
	 * Get the value at a specific location in the matrix
	 * @param row The row of the desired value
	 * @param col The column of the desired value
	 * @return The value at the specified location
	 */
	public double getValue(int row, int col) {
		return data[row][col];
	}

	/**
	 * Set the value at a specific location in the matrix
	 * @param val The value to set the cell to
	 * @param row The row of the cell to set
	 * @param col The column of the cell to set
	 */
	public void setValue(double val, int row, int col) {
		data[row][col] = val;
	}

	/**
	 * Add two matrices together
	 * @param m1 The first matrix, m x n
	 * @param m2 The second matrix, m x n
	 * @return The sum of the two matrices
	 */
	public static Matrix add(Matrix m1, Matrix m2) {
		if (m1.cols != m2.cols && m1.rows != m2.rows) {
			System.out.println("Matrix dimensions do not match");
			return null;
		} else {
			Matrix sum = new Matrix(m1.rows, m1.cols);
			for (int i = 0; i < m1.rows; i++) {
				for (int j = 0; j < m2.cols; j++) {
					sum.setValue(m1.getValue(i, j) + m2.getValue(i, j), i, j);
				}
			}
			return sum;
		}
	}

	/**
	 * Find the difference between two matrices
	 * @param m1 The first matrix, m x n
	 * @param m2 The second matrix, m x n
	 * @return The difference between the two matrices
	 */
	public static Matrix subtract(Matrix m1, Matrix m2) {
		if (m1.cols != m2.cols && m1.rows != m2.rows) {
			System.out.println("Matrix dimensions do not match");
			return null;
		} else {
			Matrix sum = new Matrix(m1.rows, m1.cols);
			for (int i = 0; i < m1.rows; i++) {
				for (int j = 0; j < m2.cols; j++) {
					sum.setValue(m1.getValue(i, j) - m2.getValue(i, j), i, j);
				}
			}
			return sum;
		}
	}

	/**
	 * Multiply two matrices together using a naive algorithm
	 * @param m1 The first matrix, m x n
	 * @param m2 The second matrix, n x o
	 * @return The matrix product
	 */
	public static Matrix multiply(Matrix m1, Matrix m2) {
		if (m1.cols != m2.rows) {
			System.out.println("Matrix dimensions do not match");
			return null;
		} else {
			Matrix product = new Matrix(m1.rows, m2.cols);
			for (int i = 0; i < m1.rows; i++) {
				for (int j = 0; j < m2.cols; j++) {
					double sum = 0;
					for (int k = 0; k < m2.rows; k++) {
						sum += m1.getValue(i, k) * m2.getValue(k, j);
					}
					product.setValue(sum, i, j);
				}
			}
			return product;
		}
	}

	public Matrix add(Matrix m) {
		return Matrix.add(this, m);
	}

	public Matrix subtract(Matrix m) {
		return Matrix.subtract(this, m);
	}

	public Matrix multiply(Matrix m) {
		return Matrix.multiply(this, m);
	}

	/**
	 * Set all values in the matrix at once
	 * @param ds A two-dimensional array of values to set the matrix to
	 */
	public void set(double[][] ds) {
		if (ds.length == rows && ds[0].length == cols)
			data = ds;
		else
			System.out.println("Input array does not match matrix dimensions");
	}

	/**
	 * Multiply a matrix by a constant
	 * @param a The constant to multiply by
	 * @return The product of the matrix and the constant
	 */
	public Matrix multiply(double a) {
		Matrix product = new Matrix(this.rows, this.cols);
		for (int i = 0; i < this.rows; i++) {
			for (int j = 0; j < this.cols; j++) {
				product.setValue(this.getValue(i, j) - this.getValue(i, j), i, j);
			}
		}
		return product;
	}
}
