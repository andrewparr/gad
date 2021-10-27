#define BOOST_TEST_MODULE My Test
#include <boost/test/included/unit_test.hpp>

#include "doomsday.h"
#include "date/date.h"

BOOST_AUTO_TEST_CASE(basic_test_1) {
    Doomsday doomsday;
    std::string test_date("2021/12/25");
    bool ret = doomsday.setDateRange(test_date, test_date);

    BOOST_TEST(ret);
    BOOST_TEST(doomsday.date() == "25 December 2021");
    BOOST_TEST(doomsday.day() == date::Saturday);
}

BOOST_AUTO_TEST_CASE(test_invalid_date) {
    Doomsday doomsday;
    std::string test_date("2021/2/29");
    bool ret = doomsday.setDateRange(test_date, test_date);

    BOOST_TEST(!ret);
}

BOOST_AUTO_TEST_CASE(test_invalid_date_2) {
    Doomsday doomsday;
    std::string test_date("1st Jan 2020");
    bool ret = doomsday.setDateRange(test_date, test_date);

    BOOST_TEST(!ret);
}

BOOST_AUTO_TEST_CASE(test_invalid_range) {
    Doomsday doomsday;
    bool ret = doomsday.setDateRange("2021/2/10", "2021/2/9");

    BOOST_TEST(!ret);
}
