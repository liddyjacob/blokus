#include "matrix.hpp"
#define BOOST_TEST_MODULE MatrixTest
#include <boost/test/unit_test.hpp>

/* Check initialization and num_entries */
BOOST_AUTO_TEST_CASE(MatrixInit)
{

  Matrix<int> mint(3,3);
  Matrix<float> mfloat(4,2);
  Matrix<bool> mbool(1,1);

  BOOST_CHECK_EQUAL(mint.num_entries(), 9);
  BOOST_CHECK_EQUAL(mfloat.num_entries(), 8);
  BOOST_CHECK_EQUAL(mbool.num_entries(), 1);
}

/* Check if m[i][j] works */
BOOST_AUTO_TEST_CASE(MatrixEntryRetrieve)
{
  Matrix<char> m(3,3);
  char c = 'a';
  for (int i = 0; i < m.num_rows(); ++i){
    for (int j = 0; j < m.num_cols(); ++j){
      m[i][j] = c;
      c++;
    }
  }
  
  c = 'a';
  
  for (int i = 0; i < m.num_rows(); ++i){
    for (int j = 0; j < m.num_cols(); ++j){
      BOOST_CHECK_EQUAL(m[i][j], c);
      c++;
    }
  }

  Matrix<bool> mb(2,2, false);
  
  for (int i = 0; i < mb.num_rows(); ++i){
    for (int j = 0; j < m.num_cols(); ++j){
      BOOST_CHECK_EQUAL(mb[i][j], false);
    }
  }
  
}

/* Check matrix equality */
BOOST_AUTO_TEST_CASE(MatrixEq){
  
  Matrix<char> m1(3,3);
  Matrix<char> m2(3,3);

  char c = 'a';

  for (int i = 0; i < m1.num_rows(); ++i){
    for (int j = 0; j < m1.num_cols(); ++j){
      m1[i][j] = c;
      m2[i][j] = c;
      c++;
    }
  }

  BOOST_CHECK_EQUAL(m1, m2);
}

