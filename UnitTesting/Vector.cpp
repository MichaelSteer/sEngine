#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../Engine/include/math/Vector.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{		
	TEST_CLASS(VectorTest)
	{
	public:
		TEST_METHOD(VectorEqualsTest) {
			Vector3f v({ 1,2,3 });
			Vector3f w({ 1,2,3 });
			Vector3f x({ 4,5,6 });
			
			// operator==
			Assert::IsTrue(v == w);
			Assert::IsFalse(w == x);

			// operator!=
			Assert::IsFalse(v != w);
			Assert::IsTrue(w != x);

			// Copy Construction
			Vector3f a({ 2,3,4 });
			Vector3f b = a;
			Assert::IsTrue(b == a);
		}

		TEST_METHOD(VectorAdditionTest) {
			Vector3f a({ 2,3,4 });
			Vector3f b({ 4,3,2 });
			Vector3f c({ 6,6,6 });
			Assert::IsTrue((a + b) == c);
		}

	};
}