#include <gtest/gtest.h>

#include "minishell.h"

TEST(IsQuote, TrueCase)
{
	EXPECT_TRUE(is_quote('\''));
	EXPECT_TRUE(is_quote('\"'));
}

TEST(IsQuote, FalseCase)
{
	EXPECT_FALSE(is_quote(0));
}