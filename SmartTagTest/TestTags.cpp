// vi:ts=4
#include "TestTags.h"

// Globals
// glob:
static int glob = 0;
// glob2:
static int glob2 = 0;

// a!:
ClassA::ClassA(int blah /* = -1 */)
{
}

// a~:
ClassA::~ClassA()
{
}

ClassAA * // aOv0:
ClassA::override()
{
	// #aIn
	inlineFunc();
	// #aOv0
	override();
	// #aOv1
	override(1);
	// #aOv2
	override(2, 2);
	//#aSA
	mSA = NULL;
}

// aOv1:
int ClassA::override(int blah)
{
	// #glob
	glob = 2;				// Tag to global.
}

// aOv2:
ClassB *ClassA::override(int blah, int blab)
{
}

inline ClassA	// aPre:
ClassA::operator++()		// Pre-increment
{
	return *this;
}

inline const ClassA	// aPost:
ClassA::operator++(int)		// Post-increment
{
	ClassA old = *this;
	++(*this);
	return old;
}

ClassA	// a-1:
ClassA::operator-()			// Unary operator
{
	//      #a!
	return ClassA();
}

ClassA	// a-2:
ClassA::operator-(const ClassA &c)	// Binary operator
{
	//      #a!
	return ClassA();
}

// b!:
ClassB::ClassB()
{
}

// b~:
ClassB::~ClassB()
{
}

ClassAA * // bOv0:
ClassB::override()
{
	// #bBC
	mBandC = 0;
	// #bIn
	inlineFunc();
	// #bOv0
	override();
	// #bOv1
	override(1);
	// #bOv2
	override(2, 2);
	//#bSA
	mSA = NULL;
	// #bSA2
	mS.mSA2 = NULL;
	//#bUA
	mUA = NULL;
	//#bUA2
	mUA2 = NULL;
	// #bUA2
	mU.mUA2 = NULL;
	// #bmN #bNa
	mNested.mNA = NULL;
	// #bmNP  #bNa
	mNestedP->mNA = NULL;
	// #b          #b!
	ClassB b = new ClassB();
	// #b   #bN     #bNN2    #bNN2a
	ClassB::Nested::Nested2::mNA = NULL;
}

// bOv1:
int ClassB::override(int blah)
{
}

// bOv2:
ClassB *ClassB::override(int blah, int blab)
{
	// localGlob:
	int glob = 0;

	// TODO: When tagging to glob below, first you get the local var, then
	// (using :tn) the member of ClassAA and the global var, then it finds
	// partial matches, such as GlobalFunc().  At this point, using :trew does
	// not return us to the original local var match.  This has been lost.

	// #localGlob
	glob = 2;			// Tag to local var.
	// #glob
	::glob = 2;			// Tag to global.
	//       #aag
	ClassAA::glob = 2;	// Tag to member of ClassAA.
}

inline ClassB // bPre:
ClassB::operator++()		// Pre-increment
{
	return *this;
}

inline const ClassB // bPost:
ClassB::operator++(int)		// Post-increment
{
	ClassB old = *this;
	//#bPre
	 ++(*this);
	return old;
}

ClassB // b-1:
ClassB::operator-()			// Unary operator
{
	//      #b!
	return ClassB();
}

ClassB // b-2:
ClassB::operator-(const ClassB &c)	// Binary operator
{
	//      #b!
	return ClassB();
}

// bOvBC:
void ClassB::overrideBandC(int blah)
{
	// #bBC
	mBandC = 0;
}

// argA:
void ClassB::Nested::func(ClassA *a,
						  // argC:
						  ClassC *c,
						  // argAA:
						  ClassAA *aa)
{
	//#bNa
	mNA = NULL;
	// #bNmN2 #bNN2a
	mNested.mNA = NULL;
	// #bNmN3 #bN3a
	mNested3.mNA = NULL;
	//#argA #an
	  a->mNext;
	//#argC #cn
	  c->mNext;
	//#argAA #aal
	  aa->mLeft;
}

template <class Type>
inline void	// c~:
ClassC<Type>::operator delete(void *p, size_t size)
{
}

template <class Type>	// cOvBC:
void ClassC<Type>::overrideBandC(int blah)
{
	// #cBC
	mBandC = 0;
}

// aa!:
ClassAA::ClassAA()
{
}

ClassAA * // aaOv0:
ClassAA::override()
{
	// #cBC
	mBandC = 0;
	// #aag
	glob = 2;		// Tag to member.
	// #glob
	::glob = 2;		// Tag to global.
	// #aIn
	inlineFunc();
	// #aaOv0
	override();
	// #aaOv2
	override(2, 2);
	// #a   #aOv1
	ClassA::override(1);
	//      #aOv2
	ClassA::override(2, 2);
	// #a              #a!
	ClassA a = new ClassA();
	// #a   #aN     #aNN2    #aNN2a
	ClassA::Nested::Nested2::mNA = NULL;
	//#aSA
	mSA = NULL;
	// #aSA2
	mS.mSA2 = NULL;
	//#aUA
	mUA = NULL;
	//#aUA2
	mUA2 = NULL;
	// #aUA2
	mU.mUA2 = NULL;
	// #amN #aNa
	mNested.mNA = NULL;
	// #amNP  #aNa
	mNestedP->mNA = NULL;
}

// aaOv1:
int ClassAA::override(int blah)
{
}

// aaOv2:
ClassB *ClassAA::override(int blah, int blab)
{
}

int
main()
{
	/*
	 * Don't get confused by things in comments that should be ignored, eg:
	 * ( stray open bracket
	 * BadType b;	// This isn't really b's type.
	 */
	// BadType2 b;	// Also not b's type.

	// La: La2:
	ClassA a(glob), a2,	// Line break to confuse things.
		   // La3: Lp:
		   redHerring[10], a3, *p;
	/*
	 * Don't get confused by something in a comment that seems like the end of
	 * a previous statement, like a semicolon;
	 */
	// Lb: Lb2: Lb3: Lpb:
	ClassB b, b2, b3, *pb;
	// Lc:
	ClassC<int> c;
	// Ltc:
	TypeDefC tc;
	// Laa:
	ClassAA aa;
	// Lta:
	TypeDefA ta;
	// Ldb:
	DefB db;
	// Lu:
	UnionA u;

	// Don't confuse these with local variable declarations.
	a.override(glob);
	int g = glob2;
	bool blah = b && GlobalFunc(a);

	// #globFunc
	GlobalFunc(a);

	// Tag to gotos, with cursor on either the "goto" or the identifier.
	// #gotoBlah
	goto blah;
	//    #gotoThing
	goto thing;

	// Put the cursor on functions below to the appropriate definition.
	// #aIn
	a.inlineFunc();
	// #bIn
	b.inlineFunc();
	// #aIn
	aa.inlineFunc();
	// #aOv0       TODO: aar - only works by coincident at the moment.
	p->override()->mRight;
	// #aaOv1
	aa.override(1);
	// Below, bl is not found because the different override()s have different
	// return types, and choosing between multiple overrides is not done till
	// the end, if multiple matches remain.  Need to do it within the check at
	// each level too.
	// #aaOv2          TODO: bl
	aa.override(1, 2)->mLeft;
	// #bOv2
	b.override(1, 2);
	// #bOvBC
	b.overrideBandC(int blah);
	// #cOvBC
	c.overrideBandC(int blah);
	// #cOvBC
	tc.overrideBandC(int blah);
	// #cOvBC
	aa.overrideBandC(int blah);

	// gotoBlah:
blah:
	// #glob
	glob = 1;
	// #glob2
	glob2 = 2;
	// #aag
	aa.glob = 2;
	// #aal
	aa.mLeft;
	// #an
	aa.mNext;
	// #cBC
	aa.mBandC;
	// #bBC
	b.mBandC;

	// TODO: Scroll-bug: see Bug.vim.  Only happens with nowrap set.  Put
	// cursor on the first mNext below, and do zb ^W^] ^Wq.  We should end up
	// where we were after the zb, but instead cursor line has scrolled towards
	// the top.
	//       #bp    #ba #an    #aOv2
	b.mNext->mPrev->mA->mNext->override(2, 2);
	//       #ba #ap    #ab #bn    #bOv2
	b.mNext->mA->mPrev->mB->mNext->override(2, 2);
	// #aal   #aar    #ap    #al
	aa.mLeft->mRight->mPrev->mLeft = NULL;
	// #a         #aar    #aal    #ar
	((ClassA *)aa.mRight->mLeft)->mRight = NULL;
	//         #a          #aar     #al
	const_cast<ClassA*>(aa.mRight)->mLeft = NULL;

	//  #Lu #ua #aa #ab #bb
		u. mA->mA->mB->mB = NULL;
	// #aSA
	a.mSA = NULL;
	// #aAnon
	a.mAnon = NULL;
	// #aS #aSA2
	a.mS.mSA2 = NULL;
	// #bSA
	b.mSA = NULL;
	// #bAnon
	b.mAnon = NULL;
	// #bS #bSA2
	b.mS.mSA2 = NULL;
	// #aUA
	a.mUA = NULL;
	// #aU #aUA2
	a.mU.mUA2 = NULL;
	// #bUA
	b.mUA = NULL;
	// #bU #bUA2
	b.mU.mUA2 = NULL;
	// #amN   #aNa
	a.mNested.mNA = NULL;
	// #bmNP    #bNa
	b.mNestedP->mNA = NULL;
	// #amN   #aNmN2  #aNN2a
	a.mNested.mNested.mNA = NULL;
	// #bmN   #bNmN2  #bNN2a
	b.mNested.mNested.mNA = NULL;
	// #bmN2   #bN2a
	b.mNested2.mNA = NULL;
	// #bHard2 #bN2a
	b.mHard2.mNA = NULL;
	// #bmN12   #bNN2a
	b.mNested12.mNA = NULL;
	// #bHard12 #bNN2a
	b.mHard12.mNA = NULL;

	// #b     #bIn
	ClassB::inlineFunc();
	//      #bb #bn    #bl
	ClassB::mB->mNext->mLeft = NULL;
	//      #bN     #bNN2    #bNN2a
	ClassB::Nested::Nested2::mNA = NULL;
	//              #bNmN3   #bN3a
	ClassB::Nested::mNested3.mNA = NULL;
	// #c        #cBC
	ClassC<int>::mBandC = NULL;

	// Although the corrent tag for mA is found below, its search pattern
	// matches that of mA in other classes in the same file, and because
	// gNamelessStruct's type is a nameless struct we don't have anything
	// obvious to search for first to get us in the right part of the file.
	// mB works though because a comment in the header file makes the search
	// pattern different in the tags file.  Probably not worth worrying too
	// much about the mA case.  It would be a pretty rare case.
	//               TODO: noNameA
	gNamelessStruct.mA = NULL;		// This one doesn't work.
	// #gNoName      #noNameB
	gNamelessStruct.mB = NULL;		// This one does work.

	// gotoThing:
thing:
	// Put cursor on operators (++ or -) to jump to overloaded operator.
	//  #a-1
	a = -a2;
	//     #a-2
	a = a2 - a3;
	//#aPost
	a++;
	//#aPre
	 ++a;
	//                  #aPost
	p[b.override(5) + 7]++;
	//  #aPre #a-2  #Lp
	a = ++a3++- -++*p;
	//       #aPost
	a = ++a3++- -++*p;
	//          #a-1
	a = ++a3++- -++*p;
	//            #aPre
	a = ++a3++- -++*p;

	//  #b-1
	b = -b2;
	//     #b-2
	b = b2 - b3;
	//#bPost
	b++;
	//#bPre
	 ++b;
	//                   #bPost
	pb[a.override(5) + 7]++;
	//  #bPre #b-2  #Lpb
	b = ++b3++- -++*pb;
	//       #bPost
	b = ++b3++- -++*pb;
	//          #b-1
	b = ++b3++- -++*pb;
	//            #bPre
	b = ++b3++- -++*pb;

	// #aPost
	ta++;
	//#bPre
	 ++db;

	//  #bPre #bn   #bp    #bn  #bPost #b-2 #b-1 #bPre #Lb2 #bn #ba #ab #bb
	b = ++b2.mNext->mPrev->mNext++     -    -    ++   b2.mNext->mA->mB->mB;

	//  #b-1 #bPre #an  #ab #bn    #ba #ab #bn    #bp    #bn
	b = -   ++a2.mNext->mB->mNext->mA->mB->mNext->mPrev->mNext;
	//  #a-1 #aPre                         #ba #an           #an
	a = -   ++a2.mNext->mB->mNext->mA->mB->mA->mNext->mPrev->mNext;

	// Put cursor on "delete" to jump to delete operator if one is defined, or
	// destructor otherwise.
	// #a~ #La
	delete a;
	// #b~ #Lb
	delete b;
	// #a~ #La3
	delete a3;
	// #c~ #Lc
	delete c;
	// #c~ #Laa
	delete aa;
	// #a~ #Lta
	delete ta;
	// #b~ #Ldb
	delete db;
	// #b~
	delete a.mNext->mB->mNext->mA->mB->mNext->mPrev->mNext;
}
