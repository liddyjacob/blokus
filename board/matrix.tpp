/// A simple Matrix<T> class
/// Features: 
///   * m[i][j]
///   * m1 == m2
///   * m.num_rows(), m.num_cols(), m.num_entries

/*
 * 00
 * 10
 * 20
 * 30
 * 40
 *
 */

template <typename T>
Matrix<T>::Matrix(size_t r, size_t c, T init)
  : rows(r), cols(c), mat(r)
{ 
  std::vector<T> dummy_row(c);
  std::fill(dummy_row.begin(), dummy_row.end(), init);
  std::fill(mat.begin(), mat.end(), dummy_row);
}

template <typename T>
Matrix<T>::Matrix(size_t r, size_t c)
  : rows(r), cols(c), mat(r)
{ 
  std::vector<T> dummy_row(c);
  std::fill(dummy_row.begin(), dummy_row.end(), T());
  std::fill(mat.begin(), mat.end(), dummy_row);
}

/* Just output matrix with spaces */
template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m)
{

  for (int i = 0; i < m.num_rows(); ++i){
    for (int j = 0; j < m.num_cols(); ++j){
      out << m[i][j] << ' ';
    }
    out << '\n';
  }

  return out;
}

/* Matrix equality: Entries are equal and in same position */
template <typename T>
bool operator!=(const Matrix<T>& m1, const Matrix<T>& m2){

  if (m1.num_cols() != m1.num_cols()) { return false; }
  if (m1.num_rows() != m1.num_rows()) { return false; }

  for (int i = 0; i < m1.num_rows(); ++i){
    for (int j = 0; j < m1.num_cols(); ++j){
      if (m1[i][j] == m2[i][j]) { return false; }
    }
  }
  
  return true;
}

/* Matrix equality: Entries are equal and in same position */
template <typename T>
bool operator==(const Matrix<T>& m1, const Matrix<T>& m2){

  if (m1.num_cols() != m1.num_cols()) { return false; }
  if (m1.num_rows() != m1.num_rows()) { return false; }

  for (int i = 0; i < m1.num_rows(); ++i){
    for (int j = 0; j < m1.num_cols(); ++j){
      if (m1[i][j] != m2[i][j]) { return false; }
    }
  }
  
  return true;
}
