#include "../piece/polyomino.hpp"
#include "polyominoGenerator.hpp"
#include <utility>
#define BOOST_TEST_MODULE generateTest
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <algorithm> // for_each
#include <numeric> //accumulate
/* See if we can generate polyominos on size */
BOOST_AUTO_TEST_CASE(trivialGenerateTest)
{
  std::unordered_set<FreePolyomino> none_test = generate_polyominos_0_to_n(0);

  BOOST_CHECK_EQUAL(none_test.size(), 0);

  std::unordered_set<FreePolyomino> one_test = generate_polyominos_0_to_n(1);

  BOOST_CHECK_EQUAL(one_test.size(), 1);


  FreePolyomino f1 = FreePolyomino(BaseForm({Cell(0,0)}));
  BOOST_CHECK(one_test.find(f1) != one_test.end());
}

BOOST_AUTO_TEST_CASE(two_three_four_five_test)
{
  std::unordered_set<FreePolyomino> two_test = generate_polyominos_0_to_n(2);

  BOOST_CHECK_EQUAL(two_test.size(), 2);

  std::unordered_set<FreePolyomino> three_test = generate_polyominos_0_to_n(3);

  BOOST_CHECK_EQUAL(three_test.size(), 4);

  std::unordered_set<FreePolyomino> four_test = generate_polyominos_0_to_n(4);

  BOOST_CHECK_EQUAL(four_test.size(), 9);

  std::unordered_set<FreePolyomino> five_test = generate_polyominos_0_to_n(5);

  BOOST_CHECK_EQUAL(five_test.size(), 21);
 


  int sa = 0;
  std::for_each(five_test.begin(), five_test.end(), [&sa](FreePolyomino fp){sa += fp.size();});
  std::cout << sa
    << '\n';
  //std::for_each(five_test.begin(), five_test.end(), [](FreePolyomino fp){ std::cout << fp.getBaseForm() << std::endl;});
}

// references 
//http://polyominoes.org/count

BOOST_AUTO_TEST_CASE(six_seven_eight_nine_test)
{
  std::unordered_set<FreePolyomino> six_test = generate_polyominos_0_to_n(6);

  BOOST_CHECK_EQUAL(six_test.size(), 21 + 35);

  std::unordered_set<FreePolyomino> seven_test = generate_polyominos_0_to_n(7);



  BOOST_CHECK_EQUAL(seven_test.size(), 21 + 35 + 107);

  std::unordered_set<FreePolyomino> eight_test = generate_polyominos_0_to_n(8);

  int sa = 0;
  std::for_each(eight_test.begin(), eight_test.end(), [&sa](FreePolyomino fp){sa += fp.size();});

  std::cout << sa
    << '\n';

  BOOST_CHECK_EQUAL(eight_test.size(), 21 + 35 + 107 + 363);

  std::unordered_set<FreePolyomino> nine_test = generate_polyominos_0_to_n(9);

  //std::for_each(eight_test.begin(), eight_test.end(), [](FreePolyomino fp){ std::cout << fp.getBaseForm() << std::endl;});


  BOOST_CHECK_EQUAL(nine_test.size(), 21 + 35 + 107 + 363 + 1248);
}