#include "polyomino.hpp"
#include <utility>
#define BOOST_TEST_MODULE FormTest
#include <boost/test/unit_test.hpp>

/* Check initialization and num_entries */
BOOST_AUTO_TEST_CASE(FormInit)
{
  FreePolyomino f = FreePolyomino(BaseForm{Cell(0,0), Cell(0,1), Cell(0,2), Cell(1,2)});

  BOOST_CHECK_EQUAL(f.size(), 4);

  FreePolyomino f2 = FreePolyomino(BaseForm{Cell(0,0), Cell(0,1)});

  BOOST_CHECK_EQUAL(f2.size(), 2);
}

/* Check if orientation matters for the polymino*/
BOOST_AUTO_TEST_CASE(FormEquality)
{
  FreePolyomino f1 = FreePolyomino(BaseForm{Cell(0,0), Cell(0,1), Cell(0,2), Cell(1,1)});
  FreePolyomino f2 = FreePolyomino(BaseForm{Cell(0,0), Cell(1,0), Cell(1,1), Cell(2,0)});
  BOOST_CHECK(f1 == f2);

  FreePolyomino f3 = FreePolyomino(BaseForm{Cell(0,0), Cell(0,1)});
  FreePolyomino f4 = FreePolyomino(BaseForm{Cell(2,0), Cell(1,0)});
  BOOST_CHECK(f3 == f4);

}

