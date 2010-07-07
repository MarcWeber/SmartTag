#include <aheader.h>
#include <bheader.h>

struct A {
	struct C *pC;
};

void func()
{
	struct A a;
	//    #MC
	a.pC->m1;
}

/* vim: set ft=c ts=4 noet :*/
