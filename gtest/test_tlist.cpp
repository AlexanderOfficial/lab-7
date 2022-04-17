#include "pch.h"
#include "../base/TList.h"

TEST(TList, can_create_list)
{
	ASSERT_NO_THROW(TList<int> list);
}

TEST(TList, can_create_list_with_argument)
{
	TList<int> list1;
	ASSERT_NO_THROW(TList<int> list2(list1));
}

TEST(TList, can_equate_list)
{
	TList<int> list1, list2;
	list1.PushBack(5);
	ASSERT_NO_THROW(list2 = list1);
}

TEST(TList, can_compare_two_lists_with_value)
{
	TList<int> list1, list2;
	list1.PushBack(10);
	list2.PushBack(10);
	EXPECT_TRUE(list1 == list2);
}

TEST(TList, can_compare_two_lists_with_different_sizes)
{
	TList<int> list1, list2;
	list1.PushBack(1);
	list1.PushBack(2);
	list2.PushBack(1);
	EXPECT_FALSE(list1 == list2);
}

TEST(TList, can_compare_two_lists_with_different_value)
{
	TList<int> list1, list2;
	list1.PushBack(1);
	list2.PushBack(2);
	EXPECT_FALSE(list1 == list2);
}

TEST(TList, can_compare_two_lists_are_not_equal_with_different_value)
{
	TList<int> list1, list2;
	list1.PushBack(5);
	list2.PushBack(3);
	EXPECT_TRUE(list1 != list2);
}

TEST(TList, can_compare_two_lists_are_equal_with_identical_value)
{
	TList<int> list1, list2;
	list1.PushBack(3);
	list2.PushBack(3);
	EXPECT_FALSE(list1 != list2);
}

TEST(TList, can_push_back_in_empty_list)
{
	TList<int> list;
	ASSERT_NO_THROW(list.PushBack(5));
}

TEST(TList, can_pop_front_return_value)
{
	TList<int> list;
	list.PushBack(10);
	EXPECT_EQ(10, list.PopFront());
}

TEST(TList, can_insert_elem_by_iterator)
{
	TList<int> list;
	TList<int>::iterator it;
	it = list.Begin();
	list.Insert(it, 5);
	EXPECT_EQ(5, list.PopFront());
}

TEST(TList, can_erace_elem_by_iterator)
{
	TList<int> list;
	TList<int>::iterator it;
	list.PushBack(10);
	it = list.Begin();
	ASSERT_NO_THROW(list.Erase(it));
}

TEST(TList, can_clear_delete_all_values_of_list)
{
	TList<int> list;
	for (int i = 0; i < 5; i++)
		list.PushBack(i);
	list.Clear();
	EXPECT_TRUE(list.IsEmpty());
}

TEST(TList, can_return_size_of_list)
{
	TList<int> list;
	for (int i = 0; i < 5; i++)
		list.PushBack(i);
	EXPECT_EQ(5, list.GetSize());
}

TEST(TList, can_check_for_empty)
{
	TList<int> list;
	EXPECT_TRUE(list.IsEmpty());
}
