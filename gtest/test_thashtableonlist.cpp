#include "pch.h"
#include "../base/THashTableOnList.h"
#include "../base/THashTableOnList.cpp"
//#include "../base/TBaseTable.h"


TEST(THashTableOnList, can_create_hash_table) //возможность создать таблицу
{
	ASSERT_NO_THROW(THashTableOnList testTable);
}

TEST(THashTableOnList, can_insert_data) //возможность вставить полином
{
	Data testData;
	string testString = "xyz";
	testData.polinomString = testString;
	TPolinom testPolinom(testString);
	testData.key = "testPolinom";
	testData._polinom = testPolinom;
	THashTableOnList testTab;
	ASSERT_NO_THROW(testTab.insert(testData));
}

TEST(THashTableOnList, cant_insert_twice) //невозможность вставить дважды один и тот же полином
{
	Data testData;
	string testString = "xyz";
	testData.polinomString = testString;
	TPolinom testPolinom(testString);

	testData.key = "testPolinom";
	testData._polinom = testPolinom;

	THashTableOnList testTab;
	testTab.insert(testData);

	ASSERT_ANY_THROW(testTab.insert(testData));
}

TEST(THashTableOnList, cant_insert_data_with_same_name) //невозможность вставить полиномы с одинаковыми именами
{
	string testString = "xyz";
	string addS = "+2xz";
	THashTableOnList testTab;
	Data testData;
	string tS = testString;
	testData.polinomString = tS;
	TPolinom testPolinom(tS);
	testData.key = "testPolinom";
	testData._polinom = testPolinom;
	testTab.insert(testData);
	testString += addS;
	tS = testString;
	testData.polinomString = tS;
	TPolinom testPolinom1(tS);
	testData.key = "testPolinom";
	testData._polinom = testPolinom1;
	ASSERT_ANY_THROW(testTab.insert(testData));
}

TEST(THashTableOnList, can_find_existing_data) //возможность найти полином в таблице
{
	Data testData;
	string testString = "xyz";
	string tS = testString;
	int rightHash = 0;
	for (unsigned int i = 0; i < testString.size(); i++) { rightHash += (int)testString[i]; }
	rightHash *= testString.size();
	rightHash %= 1000;
	testData.polinomString = testString;
	TPolinom testPoly(testString);
	testData.key = "testPolinom";
	testData._polinom = testPoly;
	THashTableOnList testTab;
	testTab.insert(testData);
	Data* testAdd = testTab.find("testPolinom");
	EXPECT_EQ(tS, testAdd->polinomString);
}

TEST(THashTableOnList, can_find_not_existing_data) //возвращение nullptr, если ничего не нашлось
{
	THashTableOnList testTable;
	EXPECT_EQ(nullptr, testTable.find("testData"));
}

TEST(THashTableOnList, can_delete_existing_data) //возможность удаления полинома
{
	THashTableOnList testTab;
	Data testData;
	string testString = "xyz";
	testData.polinomString = testString;
	TPolinom testPoly(testString);
	testData.key = "testPolinom";
	testData._polinom = testPoly;
	testTab.insert(testData);
	ASSERT_NO_THROW(testTab.deleteByKey("testPolinom"));
}

TEST(THashTableOnList, cant_delete_not_existing_data) //возможность удаления полинома
{
	THashTableOnList testTab;
	Data testData;
	string testString = "xyz";
	testData.polinomString = testString;
	TPolinom testPoly(testString);
	testData.key = "testPolinom";
	testData._polinom = testPoly;
	testTab.insert(testData);
	ASSERT_ANY_THROW(testTab.deleteByKey("testPolinom1"));
}

TEST(THashTableOnList, cant_delete_data_when_empty) //возможность удаления из пустой таблицы
{
	THashTableOnList testTable;
	ASSERT_ANY_THROW(testTable.deleteByKey("testPolinom"));
}
