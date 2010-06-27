#include <aheader.h>
#include <bheader.h>

struct SQuux {
	struct SFoo *pFoo;
};

void func()
{
	struct SQuux quux;
	//        #MFoo
	quux.pFoo->m1;
}
/* vim: set ft=c ts=4 noet :*/
