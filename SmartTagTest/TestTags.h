// vi:ts=4
#ifndef __TEST_TAGS_H__
#define __TEST_TAGS_H__

class ClassA;
class ClassB;
class ClassC;
class ClassAA;

// Global function
inline bool // globFunc:
GlobalFunc(ClassA *a)
{
	return (a != NULL);
}

// a:
 class ClassA	// Still finds it with whitespace at the start
{
public:
	// #a!
	ClassA(int blah = -1);
	// #a~
	~ClassA();
	class ClassB *dontThinkClassBStartsHere()
	{
		return NULL;
	}
	// aIn:
	inline bool inlineFunc()
	{
		return false;
	}
	//         #aOv0
	ClassAA *override();
	//         #aOv1
	int override(int blah);
	//         #aOv2
	ClassB *override(int blah, int blab);
	//     #aPre    #aPre
	ClassA operator++();				// Pre-increment
	//           #aPost   #aPost
	const ClassA operator++(int);		// Post-increment
	//     #a-1    #a-1
	ClassA operator-();
	//     #a-2    #a-2         #a
	ClassA operator-(const ClassA &c);

	// Nested named struct definition.
	// aN2:
	struct Nested2
	{
		// aN2a:
		ClassA *mNA;
	};
	// aN3:
	struct Nested3
	{
		// aN3a:
		ClassA *mNA;
	};
	// aN:
	struct Nested
	{
		// aNN2:
		struct Nested2
		{
			// aNN2a:
			ClassA *mNA;
		};
		// aNmN2:
		Nested2 mNested;
		// aNmN3:
		Nested3 mNested3;
		// aNa:
		ClassA *mNA;
		void func()
		{
			//#aNa
			mNA = NULL;
			// #aNmN2 #aNN2a
			mNested.mNA = NULL;
			// #aNmN3 #aN3a
			mNested3.mNA = NULL;
		}
	};
	// amN:
	Nested mNested;
	// amNP:
	Nested *mNestedP;
	// amN2:
	Nested2 mNested2;
	// amN12:
	Nested::Nested2 mNested12;

	// Nameless struct with no associated member.
	// Members of struct are accessed as if they were members of parent class.
	// Eg. a->mSA
	struct
	{
		// aSA:
		ClassA *mSA;
		struct
		{
			struct
			{
				// aAnon:
				ClassA *mAnon;
			};
		};
	};

	// Nameless struct with associated member.
	// Members of struct are accessed via member in parent class.
	// Eg. a->mS.mSA2
	struct
	{
		// aSA2:
		ClassA *mSA2;
		// aS:
	} mS;

	// Similar to above two cases but for unions rather than structs.
	union
	{
		// aUA:
		ClassA *mUA;
		ClassB *mUB;
	};
	union
	{
		// aUA2:
		ClassA *mUA2;
		ClassB *mUB2;
		// aU:
	} mU;

	// aa:
	ClassA *mA;
	// ab:
	ClassB *mB;
	// an:
	ClassA *mNext;
	// ap:
	ClassA *mPrev;
	// al:
	ClassA *mLeft;
	// ar:
	ClassA *mRight;
};

// b:
class ClassB
{
public:
	// #b!
	ClassB();
	//#b~   #b~
	  ~ClassB();
	// bIn:
	inline bool inlineFunc()
	{
		return false;
	}
	//         #bOv0
	ClassAA *override();
	//         #bOv1
	int override(int blah);
	//         #bOv2
	ClassB *override(int blah, int blab);
	//     #bPre    #bPre
	ClassB operator++();				// Pre-increment
	//           #bPost   #bPost
	const ClassB operator++(int);		// Post-increment
	//     #b-1    #b-1
	ClassB operator-();
	//     #b-2    #b-2         #b
	ClassB operator-(const ClassB &c);
	//   #bOvBC
	void overrideBandC(int blah);

	// Nested named struct definition.
	// bN2:
	struct Nested2
	{
		// bN2a:
		ClassA *mNA;
	};
	// bN3:
	struct Nested3
	{
		// bN3a:
		ClassA *mNA;
	};
	// bN:
	struct Nested
	{
		// bNN2:
		struct Nested2
		{
			// bNN2a:
			ClassA *mNA;
		};
		// bNmN2:
		Nested2 mNested;
		// bNmN3:
		Nested3 mNested3;
		// bNa:
		ClassA *mNA;
		void func(ClassA *a, ClassC *c, ClassAA *aa);
		void localFunc()
		{
			//#bNa
			mNA = NULL;
			// #bNmN2 #bNN2a
			mNested.mNA = NULL;
			// #bNmN3 #bN3a
			mNested3.mNA = NULL;
		}
	};
	// bmN:
	Nested mNested;
	// bmNP:
	Nested *mNestedP;
	// bmN2:
	Nested2 mRedHerring1, mRedHerring2, mNested2, mRedHerring3;
	Nested2	mRedHerring4, mRedHerring5,		// Keep a line-break here
			// bHard2: Hard to find type of Hard2, not found in tags command.
			mRedHerring6, mHard2, mRedHerring7;
	// bmN12:
	Nested::Nested2 mRedHerring8, mNested12, mRedHerring9;
	Nested::Nested2		// Keep a line-break here
			// bHard12:
			mHard12;	// Hard to find type, not found in tags command.

	// Nameless struct with no associated member.
	// Members of struct are accessed as if they were members of parent class.
	// Eg. a->mSA
	struct
	{
		// bSA:
		ClassA *mSA;
		struct
		{
			struct
			{
				// bAnon:
				ClassA *mAnon;
			};
		};
	};

	// Nameless struct with associated member.
	// Members of struct are accessed via member in parent class.
	// Eg. a->mS.mSA2
	struct
	{
		// bSA2:
		ClassA *mSA2;
		// bS:
	} mS;

	// Similar to above two cases but for unions rather than structs.
	union
	{
		// bUA:
		ClassA *mUA;
		ClassB *mUB;
	};
	union
	{
		// bUA2:
		ClassA *mUA2;
		ClassB *mUB2;
		// bU:
	} mU;

	// bBC:
	int mBandC;
	// ba:
	ClassA *mA;
	// bb:
	ClassB *mB;
	// bn:
	ClassB *mNext;
	// bp:
	ClassB *mPrev;
	// bl:
	ClassB *mLeft;
	// br:
	ClassB *mRight;
};

union UnionA
{
	// ua:
	ClassA *mA;
	ClassB *mB;
};

template <class Type>	// c:
class ClassC
{
public:
	//          #c~           #c~
	static void operator delete(void *p, size_t size);
	//   #cOvBC
	void overrideBandC(int blah);
	// cBC:
	int mBandC;
	// cn:
	ClassC *mNext;
	// cp:
	ClassC *mPrev;
};
typedef ClassC<float> TypeDefC;

#define DefA ClassA
typedef DefA TypeDefA;

typedef ClassB TypeDefB;
#define DefB TypeDefB

// aa:
class ClassAA : public TypeDefC, public TypeDefA
{
public:
	// #aa!
	ClassAA();
	//         #aaOv0
	ClassAA *override();
	//         #aaOv1
	int override(int blah);
	//         #aaOv2
	ClassB *override(int blah, int blab);

	// aag:
	float	glob;
	// aal:
	ClassAA *mLeft;
	// aar:
	ClassAA *mRight;
};

// Nameless struct defining global variable
struct
{
	// noNameA:
	ClassA *mA;
	// noNameB:
	ClassB *mB;		// This comment makes the search different, so it works.
	// gNoName:
} gNamelessStruct;
#endif // __TEST_TAGS_H__
