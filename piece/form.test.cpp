#include "form.hpp"
#include <utility>
#define BOOST_TEST_MODULE FormTest
#include <boost/test/unit_test.hpp>

/* Check initialization and num_entries */
BOOST_AUTO_TEST_CASE(FormInit)
{

  Form f = Form{Cell(0,0)};

  BOOST_CHECK_EQUAL(f.size(), 1);
}
