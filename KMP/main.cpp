/*************
 *           *
 *  KMP算法  *
 *           *
 *************/
#include <iostream>
using namespace std;

struct Str
{
	char *str;
	int length;
};

//简单匹配
int simpleMatched(Str str, Str substr);
//KMP算法
int KMP(Str str, Str substr, int next[]);
//求next数组
void getNext(Str substr, int next[]);
//改进的KMP算法——求next数组的优化
void getNextVal(Str substr, int nextVal[]);
//将串中第一个位置空出来
void strDone(Str str, char c[]);

const int maxSize = 1000;

int main()
{
	Str str, substr;
	char c[maxSize];
	int next[maxSize], nextVal[maxSize];
	cin >> c;
	str.length = strlen(c);
	str.str = new char[str.length + 1];
	strDone(str, c);

	cin >> c;
	substr.length = strlen(c);
	substr.str = new char[substr.length + 1];
	strDone(substr, c);

	getNext(substr, next);
	getNextVal(substr, nextVal);

	cout << "simpleMatched: " << simpleMatched(str, substr) << endl;
	cout << "KMP1: " << KMP(str, substr, next) << endl;
	cout << "KMP2: " << KMP(str, substr, nextVal) << endl;
	return 0;
}

int simpleMatched(Str str, Str substr)
{
	int i = 1, j = 1, k = i;
	while (i <= str.length&&j <= substr.length)
	{
		if (str.str[i] == substr.str[j])
		{
			i++;
			j++;
		}
		else
		{
			j = 1;
			i = ++k;
		}
	}
	if (j > substr.length)
		return k;
	else
		return 0;
}

int KMP(Str str, Str substr, int next[])
{
	int i = 1, j = 1;
	while (i <= str.length&&j <= substr.length)
	{
		if (str.str[i] == substr.str[j] || j == 0)
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j > substr.length)
		return i - substr.length;
	else
		return 0;
}

void getNext(Str substr, int next[])
{
	int j = 1, t = 0;
	next[1] = 0;
	while (j < substr.length)
	{
		if (substr.str[j] == substr.str[t] || t == 0)
		{
			next[j + 1] = t + 1;
			t++;
			j++;
		}
		else
			t = next[t];
	}
}

void getNextVal(Str substr, int nextVal[])
{
	int j = 1, t = 0;
	nextVal[1] = 0;
	while (j < substr.length)
	{
		if (substr.str[j] == substr.str[t] || t == 0)
		{
			if (substr.str[j + 1] != substr.str[t + 1])
				nextVal[j + 1] = t + 1;
			else
				nextVal[j + 1] = nextVal[t + 1];
			j++;
			t++;
		}
		else
			t = nextVal[t];
	}
}

void strDone(Str str, char c[])
{
	str.str[0] = ' ';
	for (int i = 1;i <= str.length;i++)
	{
		str.str[i] = c[i - 1];
	}
	str.str[str.length + 1] = '\0';
	cout << str.str << endl;
}