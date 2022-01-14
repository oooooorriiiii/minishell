#include <gtest/gtest.h>

extern "C" {
#include "lexer.h"
}

TEST(IsQuote, TrueCase)
{
	EXPECT_TRUE(is_quote('\''));
	EXPECT_TRUE(is_quote('\"'));
}

TEST(IsQuote, FalseCase)
{
	EXPECT_FALSE(is_quote(0));
}