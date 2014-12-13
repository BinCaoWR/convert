// Boost.Convert test and usage example
// Copyright (c) 2009-2014 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#include "./test.hpp"
#include <boost/convert.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>
#include <iostream>

namespace { namespace local
{
    BOOST_DECLARE_HAS_MEMBER(has_begin, begin);
}}

namespace { namespace local
{
    struct test01 { int   begin; };
    struct test02 { char* begin() { return 0; } };
    struct test03
    {
        void begin(int) {}
        int  begin(int, int) { return 0; }
    };
    struct test04
    {
        virtual ~test04() {}

        private: virtual char* begin() { return 0; }
    };
    struct test05
    {
        virtual char* begin() { return 0; }
        virtual ~test05() {}
    };
    struct test06 : public  test04 {};
    struct test07 : private test04 {};
    struct test08 : public  test05 {};
    struct test09 : private test05 {};

    struct test11 { int   no_begin; };
    struct test12 { char* no_begin() { return 0; } };
}}

int
main(int argc, char const* argv[])
{
//#ifndef BOOST_CONVERT_MSVC_SFINAE_BROKEN

    BOOST_TEST(local::has_begin<local::test01>::value     == true);
    BOOST_TEST(local::has_begin<local::test02>::value     == true);
    BOOST_TEST(local::has_begin<local::test03>::value     == true);
    BOOST_TEST(local::has_begin<local::test04>::value     == true);
    BOOST_TEST(local::has_begin<local::test05>::value     == true);
    BOOST_TEST(local::has_begin<local::test06>::value     == true);
    BOOST_TEST(local::has_begin<local::test07>::value     == true);
    BOOST_TEST(local::has_begin<local::test08>::value     == true);
    BOOST_TEST(local::has_begin<local::test09>::value     == true);
    BOOST_TEST(local::has_begin<std::string>::value       == true);
    BOOST_TEST(local::has_begin<std::vector<int> >::value == true);

    BOOST_TEST(local::has_begin<local::test11>::value == false);
    BOOST_TEST(local::has_begin<local::test12>::value == false);
    BOOST_TEST(local::has_begin<std::iostream>::value == false);

//#endif

    return boost::report_errors();
}
