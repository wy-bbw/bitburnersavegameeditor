#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JsonParserTest

#include <boost/test/unit_test.hpp>
#include <boost/assert.hpp>
#include <cstddef>
#include <vector>

#include <core/json/JsonParser.h>

std::vector<std::byte> str2bytevector(const std::string &s) {
    std::vector<std::byte> b;
    std::transform(s.begin(), s.end(), std::back_inserter(b), [] (const char c) {return static_cast<std::byte>(c);});
    return b;
}

BOOST_AUTO_TEST_SUITE(JsonParserTestSuite)

BOOST_AUTO_TEST_CASE(parseEmpty) {
    std::string empty = "{}";
    std::vector<std::byte> b = str2bytevector(empty);
    auto rootnode = json::parseData((b));
    BOOST_CHECK_EQUAL(0, rootnode->childCount());
    std::string itemData = rootnode->data(0).toString().toStdString();
    BOOST_CHECK_EQUAL("{}", itemData);
}
BOOST_AUTO_TEST_SUITE_END()