#include "file.h"

void func2()
{
	if (1 < 3)
		printf("foo\n");

	if (0 > bar)
		printf("bar\n");

	// #bar
	   bar = 3;

	//#eT  et:
	etype1 et;

	//      #et
	switch (et)
	{
		  // #e1
		case ET_CASE1:
			break;
		  // #e2
		case ET_CASE2:
			break;
		  // #e3
		case ET_CASE3:
			break;
		  // #e4
		case ET_CASE4:
			break;
		  // #e5
		case ET_CASE5:
			break;
	}
}

void func3()
{
	unsigned i;

	for (i = 10; 0 < i; --i)
		printf("foo\n");

	while (1 > bar)
		printf("bar\n");

	// #bar
	   bar = 3;
}

void func4()
{
	while (3 < 1)
		printf("foo\n");

	while (1 > bar)
		printf("bar\n");

	// #bar
	   bar = 3;
}

void func5()
{
	do
		a < b;
	while (1 > bar);

	// #bar
	   bar = 3;
}

void func6()
{
	switch (1 < foo)
	{
		case 1:
			break;
		case 2:
			break;
	}

	while (1 > bar)
		printf("bar\n");

	// #bar
	   bar = 3;
}

void func7()
{
	unsigned i;

	for (i = 0; i < 0; ++i)
		printf("foo\n");

	while (1 > bar)
		printf("bar\n");

	// #bar
	   bar = 3;
}

/* vim: set ft=c ts=4 :*/
