#include "pch.h"
#include "../base/TStack.h"

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, cant_create_stack_with_zero_length)
{
	ASSERT_ANY_THROW(TStack<int> st(0));
}


TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, cant_push_if_stack_full)
{
	TStack<int> st(2);
	st.push(1);
	st.push(2);
	ASSERT_ANY_THROW(st.push(4));
}

TEST(TStack, cant_pop_if_stack_empty)
{
	TStack<int> st(2);
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, can_push_and_pop_element)
{
	TStack<int> st(5);
	st.push(4);
	st.push(5);
	EXPECT_EQ(5, st.Pop());
	//EXPECT_EQ(4, st.top());
}

TEST(TStack, function_full_is_correct)
{
	TStack<int> st(2);
	st.push(4);
	st.push(4);
	ASSERT_TRUE(st.isFull());
}

TEST(TStack, function_empty_is_correct)
{
	TStack<int> st(2);
	ASSERT_TRUE(st.isEmpty());
}