#include <stdio.h>

void Function(int&& num);
void Function(int* num);
void Function(int& num);

int main()
{
	int number1 = 2;
	int number2 = 2;
	int number3 = 2;

	Function(number1);
	Function(&number2);
	Function(number3);
	printf("%d", number1);
	printf("%d", number2);
	printf("%d", number3);
	return 0;
}

void Function(int* num)
{
	*num = *num * 2;
}

void Function(int& num)
{
	num = num * 2;
}
void Function(int&& num)
{
	num = num * 2;
}