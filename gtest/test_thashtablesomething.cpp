#include "pch.h"
#include "../base/THashTableSomething.h"
#include "../base/THashTableSomething.cpp"

TEST(THashTableSomething, can_create_hash_table) //возможность создания таблицы
{
	ASSERT_NO_THROW(THashTableSomething testTable);
}

TEST(THashTableSomething, can_insert_data) //возможность вставить полином
{
	Data testData;
	string testString = "xyz";
	testData.polinomString = testString;
	TPolinom testPolinom(testString);
	testData.key = "testPolinom1";
	testData._polinom = testPolinom;
	THashTableSomething testTable;
	ASSERT_NO_THROW(testTable.insert(testData));
}

TEST(THashTableSomething, cant_insert_twice) //невозможность вставить дважды один и тот же полином
{
	Data testData;
	string testString = "xyz";
	testData.polinomString = testString;
	TPolinom testPoly(testString);
	testData.key = "testPolinom";
	testData._polinom = testPoly;
	THashTableSomething testTab;
	testTab.insert(testData);
	ASSERT_ANY_THROW(testTab.insert(testData));
}

TEST(THashTableSomething, cant_insert_data_with_same_name) //невозможность вставить полиномы с одинаковыми именами
{
	string testString = "xyz+z";
	string addS = "+2xz";
	THashTableSomething testTab;
	Data testData;
	string tS = testString;
	testData.polinomString = tS;
	TPolinom testPoly(tS);
	testData.key = "testPolinom";
	testData._polinom = testPoly;
	testTab.insert(testData);
	testString += addS;
	tS = testString;
	testData.polinomString = tS;
	TPolinom testPoly1(tS);
	testData.key = "testPolinom";
	testData._polinom = testPoly1;
	ASSERT_ANY_THROW(testTab.insert(testData));
}

TEST(THashTableSomething, cant_find_anything) //возвращение nullptr, если ничего не нашлось
{
	THashTableSomething testTab;
	EXPECT_EQ(nullptr, testTab.find("testData"));
}

TEST(THashTableSomething, can_find_data) //возможность найти полином в таблице
{
	Data testData;
	string testString = "xyz";
	string tS = testString;
	int rightHash = 0;
	for (unsigned int i = 0; i < testString.size(); i++) 
	{ 
		rightHash += (int)testString[i]; 
	}
	rightHash *= testString.size();
	rightHash %= 1000;
	testData.polinomString = testString;
	TPolinom testPolinom(testString);
	testData.key = "testPolinom";
	testData._polinom = testPolinom;
	THashTableSomething testTab;
	testTab.insert(testData);
	Data* testAdd = testTab.find("testPolinom");
	EXPECT_EQ(tS, testAdd->polinomString);
}
//возможность удаления полинома 
TEST(THashTableSomething, can_delete_data) {
	THashTableSomething testTable;

	Data testData;
	string testString = "y^2 +2x^2y + 3z^2y";
	testData.polinomString = testString;
	TPolinom testPolinom(testString);

	testData.key = "testPolinom";
	testData._polinom = testPolinom;

	testTable.insert(testData);
	ASSERT_NO_THROW(testTable.deleteByKey("testPolinom"));
}

TEST(THashTableSomething, cant_delete_data_when_empty) //возможность удаления пустой таблицы
{
	THashTableSomething testTab;
	ASSERT_ANY_THROW(testTab.deleteByKey("testPoly"));
}