#ifndef MJSONTEST_PARSERTEST_HPP
#define MJSONTEST_PARSERTEST_HPP

#include <gtest/gtest.h>
#include <mjson.hpp>

class ParserTest : public testing::Test
{
protected:

    virtual void SetUp();

    mjson::Parser parser;

};

#endif
