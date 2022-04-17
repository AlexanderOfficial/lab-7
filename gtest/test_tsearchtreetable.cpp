#include "pch.h"
#include "../base/TSearchTreeTable.h"
#include "../base/TSearchTreeTable.cpp"
TEST(TSearchTreeTable, can_create_linear_table)
{
	ASSERT_NO_THROW(TSearchTreeTable testTable);
}

TEST(TSearchTreeTable, can_insert_elem_in_tab) //возможность вставки полинома в таблицу
{
	Data testData;
	string testStr1= "xyz";
	testData.polinomString = testStr1;
	TPolinom testPolinom(testStr1);

	testData.key = "testPoly";
	testData._polinom = testPolinom;

	TSearchTreeTable testTable;
	ASSERT_NO_THROW(testTable.insert(testData));
}

TEST(TSearchTreeTable, can_insert_elem_in_tab_when_its_not_empty) //возможность вставить полином в таблицу, когда она не пустая
{
	Data testData;
	string testStr1 = "xyz";
	testData.polinomString = testStr1;
	TPolinom testPolinom(testStr1);

	testData.key = "testPolinom1";
	testData._polinom = testPolinom;

	TSearchTreeTable testTable;
	testTable.insert(testData);

	string testStr2 = "2xyz";
	testData.polinomString = testStr2;
	TPolinom testPolinom2(testStr2);
	testData.key = "testPolinom2";
	testData._polinom= testPolinom2;
	ASSERT_NO_THROW(testTable.insert(testData));
}

TEST(TSearchTreeTable, cant_insert_elem_with_same_name) //невозможность вставить полиномы с одинаковыми именами
{
	Data testData;
	string testStr1 = "xyz";
	string testStr2 = "2xyz";
	testData.polinomString = testStr1;
	TPolinom testPolinom(testStr1);

	testData.key = "testPolinom";
	testData._polinom = testPolinom;

	TSearchTreeTable testTable;
	testTable.insert(testData);

	testData.polinomString = testStr2;
	TPolinom testP(testStr2);
	testData.key = "testPolinom";
	testData._polinom = testP;
	ASSERT_ANY_THROW(testTable.insert(testData));
}

TEST(TSearchTreeTable, cant_find_when_is_empty) //невозможность найти полином в пустой таблице (возврат nullptr)
{
	TSearchTreeTable testTable;
	string testStr1 = "xyz";
	EXPECT_EQ(nullptr, testTable.find(testStr1));
}

TEST(TSearchTreeTable, can_find_elem_in_tab) //возможность найти полином в таблице
{
	Data testData;
	string testStr1 = "xyz";
	string tS = testStr1;
	string testName = "testPolinom";
	testData.polinomString = testStr1;
	TPolinom testPolinom(testStr1);

	testData.key = testName;
	testData._polinom = testPolinom;

	TSearchTreeTable testTable;
	testTable.insert(testData);
	Data* testD = testTable.find(testName);
	EXPECT_EQ(tS, testD->polinomString);
}

TEST(TSearchTreeTable, cant_find_elem_in_tab_when_it_isnt_there) //невозможность найти полином в таблице, когда его там нет (возврат nullptr)
{

	Data testData;
	string testStr1 = "xyz";
	testData.polinomString = testStr1;
	TPolinom testPolinom(testStr1);
	testData.key = "testPolinom";
	testData._polinom = testPolinom;
	TSearchTreeTable testTab;
	testTab.insert(testData);
	EXPECT_EQ(nullptr, testTab.find("testPolinom2"));
}

TEST(TSearchTreeTable, cant_delete_elem_when_its_empty) //невозможность удалить полином, когда таблица пустая
{
	TSearchTreeTable testTable;
	ASSERT_ANY_THROW(testTable.deleteByKey("testPolinom"));
}

TEST(TSearchTreeTable, can_delete_existing_elem) //возможность удалить существующий полином
{
	Data testData;
	string testStr1 = "xyz";
	testData.polinomString = testStr1;
	TPolinom testPolinom(testStr1);

	testData.key = "testPolinom";
	testData._polinom = testPolinom;

	TSearchTreeTable testTable;
	testTable.insert(testData);

	ASSERT_NO_THROW(testTable.deleteByKey("testPolinom"));
}

TEST(TSearchTreeTable, cant_delete_non_existing_elem) //невозможность удалить несуществующий полином
{
	Data testData;
	string testStr1 = "xyz";
	testData.polinomString = testStr1;
	TPolinom testPolinom(testStr1);

	testData.key = "testPolinom1";
	testData._polinom = testPolinom;

	TSearchTreeTable testTable;
	testTable.insert(testData);
	ASSERT_ANY_THROW(testTable.deleteByKey("testPolinom2"));
}