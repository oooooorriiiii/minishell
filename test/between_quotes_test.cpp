#include <gtest/gtest.h>

#include "lexer.h"

TEST (INSERT_SPASES, TrueCase)
{
	char	**line;
	char	tmp[] = "\"abcaa\" aa";

	int i = 0;
	while (tmp[i])
	{
		**line = tmp[i];
		i++;
	}

	EXPECT_TRUE(between_quotes(line));
}

TEST (INSERT_SPASES, FalseCase)
{

	char	**line;
	char	tmp[] = "abc";

	int i = 0;
	while (tmp[i])
	{
		**line = tmp[i];
		i++;
	}
	EXPECT_FALSE(between_quotes(line));
}

TEST (INSERT_SPASES, FalseCase2)
{

	char	**line;
	char	tmp[] = "abc>";

	int i = 0;
	while (tmp[i])
	{
		**line = tmp[i];
		i++;
	}
	EXPECT_FALSE(between_quotes(line));
}

TEST (INSERT_SPASES, FalseCase3)
{

	char	**line;
	char	tmp[] = "abc\"aa";

	int i = 0;
	while (tmp[i])
	{
		**line = tmp[i];
		i++;
	}
	EXPECT_FALSE(between_quotes(line));
}