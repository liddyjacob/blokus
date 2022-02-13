#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using std::size_t;


template <typename T>
class Matrix{ 
public:

  Matrix(size_t r, size_t c, T init);
  Matrix(size_t r, size_t c);

  // Total number of entries
  size_t num_entries() const { return rows * cols; }

  // Get number of rows and number of entries resp.
  size_t num_rows() const { return rows; }
  size_t num_cols() const { return cols; }

  // You returns a row, so that you can get a col.
  std::vector<T>& operator[](size_t row) { return mat[row]; } 
  std::vector<T> operator[](size_t row) const { return mat[row]; }  

private:
  std::vector<std::vector<T> > mat;
  size_t rows;
  size_t cols;
};





#include "matrix.tpp"
