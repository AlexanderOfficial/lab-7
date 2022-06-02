#include "pch.h"
//#include "../Text/TTextProg.h"
#include "../Text/TTextProg.h"
//#include "../Text/TTextProg.cpp"
//#include "../Text/TProgLink.h"
//#include "../Text/TProgLink.cpp"


TEST(TTextProg, can_create_ttextprog) //+
{
	ASSERT_NO_THROW(TTextProg t);
}

TEST(TTextProg, can_creating_double_variable)//+
{
	TTextProg t;
	var_compiller new_var;
	var_compiller new_var2;
	new_var.valueOfDoubleVar = double(7.123);
	new_var.doubleOrInteger = 0;
	new_var.nameOfVar = "Res";
	new_var2.doubleOrInteger = 0;
	t.itsVar("Res: double=7,123;");
	new_var2 = t.getVar("Res");
	bool is_eq = !(new_var2.valueOfDoubleVar - 7.123);
	EXPECT_EQ(0, is_eq);
}


TEST(TTextProg, get_name_int_var) //+
{
	TTextProg t;
	var_compiller new_var;
	var_compiller new_var2;
	new_var.valueOfIntVar = int(1);
	new_var.doubleOrInteger = 1;
	new_var.nameOfVar = "Res";
	t.itsVar("Res: integer=1;");
	new_var2 = t.getVar("Res");
	EXPECT_EQ("Res", new_var2.nameOfVar);
}

TEST(TTextProg, get_type_int_var) //+
{
	TTextProg t;
	var_compiller new_var;
	var_compiller new_var2;
	new_var.valueOfIntVar = int(1);
	new_var.doubleOrInteger = 1;
	new_var.nameOfVar = "Res";
	t.itsVar("Res: integer=1;");
	new_var2 = t.getVar("Res");
	EXPECT_EQ(1, new_var2.doubleOrInteger);
}

TEST(TTextProg, can_creating_double_const) //+
{
	TTextProg t;
	const_compiller new_var;
	const_compiller new_var2;
	new_var.nameOfConst = "Res";
	new_var.valueOfDoubleConst = double(7.123);
	new_var.doubleOrInteger = 0;
	t.itsConst("Res: double=7,123;");
	new_var2 = t.getConst("Res");
	bool is_eq = !(new_var2.valueOfDoubleConst - 7.123);
	EXPECT_EQ(0, is_eq);
}

TEST(TTextProg, can_creating_integer_const)//+
{
	TTextProg t;
	const_compiller new_const;
	const_compiller new_const2;
	new_const.valueOfIntConst = int(1);
	new_const.doubleOrInteger = 1;
	new_const.nameOfConst = "Res";
	t.itsConst("Res: double=1;");
	new_const2 = t.getConst("Res");
	bool is_eq = !(new_const2.valueOfIntConst - 1);
	EXPECT_EQ(0, is_eq);
}

TEST(TTextProg, creating_int_variable) //+
{
	TProgLink::InitMemSystem(100);
	TTextProg t;
	var_compiller new_var;
	t.itsVar("Res: integer=5;");
	new_var = t.getVar("Res");
	EXPECT_EQ(5, new_var.valueOfIntVar);
}

TEST(TTextProg, creating_floating_const_and_get_value)
{
	TProgLink::InitMemSystem(100);
	TTextProg t;
	const_compiller new_const;
	t.itsConst("Res: double=5.25;");
	new_const = t.getConst("Res");
	bool is_ql = !(5.25-new_const.valueOfDoubleConst);
}

TEST(TTextProg, get_value_int_const) //+
{
	TProgLink::InitMemSystem(100);
	TTextProg t;
	const_compiller new_const;
	t.itsConst("Res: integer=5;");
	new_const = t.getConst("Res");
	EXPECT_EQ(5, new_const.valueOfIntConst);
}

TEST(TTextProg, get_name_int_const) //+
{
	TProgLink::InitMemSystem(100);
	TTextProg t;
	const_compiller new_const;
	t.itsConst("Res: integer=5;");
	new_const = t.getConst("Res");
	EXPECT_EQ("Res", new_const.nameOfConst);
}

TEST(TTextProg, get_type_int_const) //+
{
	TProgLink::InitMemSystem(100);
	TTextProg t;
	const_compiller new_const;
	t.itsConst("Res: integer=5;");
	new_const = t.getConst("Res");
	EXPECT_EQ(1, new_const.doubleOrInteger);
}

TEST(TTextProg, can_open_pas_file) //+
{
	TProgLink::InitMemSystem(100);
	TTextProg t;
	ASSERT_NO_THROW(t.FindError("test.pas"));
} //+

TEST(TTextProg, cant_open_pas_file_which_does_not_exist) //+
{
	TTextProg t;
	ASSERT_ANY_THROW(t.FindError("test1.pas"));
} //+

TEST(TTextProg, can_remove_slashes_from_string) //+
{
	string tstringl = "Res: integer=5; //teststring";
	string tstring2 = "Res: integer=5;";
	TTextProg t;
	EXPECT_EQ(tstring2, t.removeDoubleSlash(tstringl));
} //+
//counting brackets in an expression
TEST(TTextProg, counting_brackets_in_expression_true) //+
{
	string tstringl = "Res: = (x+y)*(x-z)";
	TTextProg t;
	EXPECT_EQ(false, t.countParenthesesInAString(tstringl));
} //+
TEST(TTextProg, counting_brackets_in_expression_false) //+
{
	string tstringl = "Res: = (x+y)*(x-z))";
	TTextProg t;
	EXPECT_EQ(true, t.countParenthesesInAString(tstringl));
} //+

//test div
TEST(TTextProg, test_div_function) //+
{
	TTextProg t;
	EXPECT_EQ(2, t.itsDiv("5","2"));
} //+

TEST(TTextProg, test_div_function_with_zero) //+
{
	TTextProg t;
    ASSERT_ANY_THROW(t.itsDiv("5", "0"));
} //+

TEST(TTextProg, test_mod_function) //?
{
	TTextProg t;
	EXPECT_EQ(1, t.itsMod("5", "2"));
} //?

TEST(TTextProg, test_mod_function_with_zero) //?
{
	TTextProg t;
	ASSERT_ANY_THROW(t.itsMod("5", "0"));
} //?

TEST(TTextProg, can_set_and_get_infix_form) //?
{
	TTextProg t;
	string infixForm = "x+y mod 3";
	t.SetInfix(infixForm);

	EXPECT_EQ(infixForm, t.GetInfix());
} //?

TEST(TTextProg, can_make_postfix_form_with_mod_and_staples) //?
{
	TTextProg t;
	string infixForm = "(x+y) mod 3";
	string postfixForm = "x y + 3 mod";
	t.SetInfix(infixForm);
	t.ToPostfix();
	EXPECT_EQ(postfixForm, t.GetPostfix());
} //?

TEST(TTextProg, can_make_postfix_form_with_div) //?
{
	TTextProg t;
	string infixForm = "x+y div 3";
	string postfixForm = "x y 3 div +";
	t.SetInfix(infixForm);
	t.ToPostfix();
	EXPECT_EQ(postfixForm, t.GetPostfix());
} 

TEST(TTextProg, can_make_postfix_form_with_div_and_staples) //?
{
	TTextProg t;
	string infixForm = "(x+y) div 3";
	string postfixForm = "x y + 3 div";
	t.SetInfix(infixForm);
	t.ToPostfix();
	EXPECT_EQ(postfixForm, t.GetPostfix());
}

TEST(TTextProg, can_make_postfix_form_with_mod_and_div) //?
{
	TTextProg t;
	string infixForm = "x+y div 3 mod 5";
	string postfixForm = "x y 3 div 5 mod +";
	t.SetInfix(infixForm);
	t.ToPostfix();
	EXPECT_EQ(postfixForm, t.GetPostfix());
} //?

TEST(TTextProg, can_make_postfix_form_with_mod_and_div_and_staples_one) //?
{
	TTextProg t;
	string infixForm = "((x+y) div 3) mod 5";
	string postfixForm = "x y + 3 div 5 mod";
	t.SetInfix(infixForm);
	t.ToPostfix();
	EXPECT_EQ(postfixForm, t.GetPostfix());
} //?

TEST(TTextProg, can_make_postfix_form_with_mod_and_div_and_staples_two) //?
{
	TTextProg t;
	string infixForm = "((x+y) div 3)*5";
	string postfixForm = "x y + 3 div 5 *";
	t.SetInfix(infixForm);
	t.ToPostfix();
	EXPECT_EQ(postfixForm, t.GetPostfix());
} //?

TEST(TTextProg, can_make_postfix_form_with_mod_and_div_and_staples_three) 
{
	TTextProg t;
	string infixForm = "x/y div 3 mod 5";
	string postfixForm = "x y / 3 div 5 mod";
	t.SetInfix(infixForm);
	t.ToPostfix();
	EXPECT_EQ(postfixForm, t.GetPostfix());
} 

TEST(TTextProg, can_create_postfix_form_with_subtraction)
{
	TTextProg t;
	string infixForm = "x-7";
	string postfixForm = "x 7 -";
	t.SetInfix(infixForm);
	t.ToPostfix();
	EXPECT_EQ(postfixForm, t.GetPostfix());
}

TEST(TTextProg, can_create_postfix_form_with_multiplication)
{
	TTextProg t;
	string infixForm = "x*7";
	string postfixForm = "x 7 *";
	t.SetInfix(infixForm);
	t.ToPostfix();
	EXPECT_EQ(postfixForm, t.GetPostfix());
}

TEST(TTextProg, can_create_postfix_form_with_division)
{
	TTextProg t;
	string infixForm = "x/7";
	string postfixForm = "x 7 /";
	t.SetInfix(infixForm);
	t.ToPostfix();
	EXPECT_EQ(postfixForm, t.GetPostfix());
}