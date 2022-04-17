#include "TPostfix.h"
#include "TStack.h"

using namespace std;

bool TPostfix::isCorrect(string str)
{
    string unacceptable = "!@#^&.,<>{}[]|=_?";
    int count = 0, countOperation = 0, length = str.length();
    if ((operands.find(str[0]) != string::npos) || (operands.find(str[length - 1]) != string::npos))
        return false;
    for (int i = 0; i < length; i++)
    {
        if (unacceptable.find(str[i]) != string::npos)
            return false;
        if (str[i] == '(')
            count++;
        if (str[i] == ')')
            count--;
        if (operands.find(str[i]) != string::npos)
            countOperation++;
        else
            countOperation = 0;
        if (countOperation > 1)
            return false;
    }
    if (count != 0)
        return false;
    return true;
}

bool TPostfix::ChekInPostfix(int i)
{
	if ((postfix[i] != '+') && (postfix[i] != '-') && (postfix[i] != '*') && (postfix[i] != '/'))
		return true;
	return false;
}


string TPostfix::ToPostfix()
{
    TStack<char> opStack(MaxStackSize);
    string tmp = "+-*/()";
    int length = infix.length();
    int check = -1;
    for (int i = 0; i < length; i++)
    {
        if (tmp.find(infix[i]) == string::npos) {
            //   if (tmp.find(infix[i]) == string::npos)
            postfix += infix[i];
            check = 1;
            if ((infix[i] >= '0') && (infix[i] <= '9'))
            {
                if (i != length)
                {
                    if ((infix[i + 1] < '0') || (infix[i + 1] > '9'))
                        postfix += '>';
                }
                else
                    postfix += '>';
                check = 0;
            }
        }
        else
        {
            if (check != 0 && check != -1)
            {
                postfix += '|';
                check = -1;
            }
            if (infix[i] == '(')
                opStack.push(infix[i]);
            if (infix[i] == ')')
            {
                char temp = opStack.Pop();
                while (temp != '(')
                {
                    postfix += temp;
                    temp = opStack.Pop();
                }
            }
            if (operands.find(infix[i]) != string::npos)
            {
                if (opStack.isEmpty())
                    opStack.push(infix[i]);
                else
                {
                    int index2 = operands.find(infix[i]);
                    while (!opStack.isEmpty())
                    {
                        char temp = opStack.Pop();
                        if (temp == '(')
                        {
                            opStack.push(temp);
                            break;
                        }
                        int index1 = operands.find(temp);
                        if (priority[index2] <= priority[index1])
                            postfix += temp;
                        else
                        {
                            opStack.push(temp);
                            break;
                        }
                    }
                    opStack.push(infix[i]);
                }
            }
        }
        if (i == length - 1)
            if (check != 0 && check != -1)
                postfix += '|';
    }
    while (!opStack.isEmpty())
    {
        postfix += opStack.Pop();
    }
    return postfix;
};

