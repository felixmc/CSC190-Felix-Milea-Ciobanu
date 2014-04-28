#include "Vector2.h"
#include "Vector2Tests.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

void Vector2Tests::runAll() {
	testConstructor();

	// test static methods
	testLerp();
	testStaticDotProduct();
	testStaticCrossProduct();

	// test instance methods
	testDotProduct();
	testCrossProduct();
	testLength();
	testLengthSquared();
	testNormalize();
	testperpCW();
	testPerpCCW();

	// test binary operators
	testSum();
	testDifference();
	testMultiplication();
	testDivision();
	testEquality();

	// test friend operators
	testReverseMultiplication();

	// special tests
	testSpecialNormalize();
	testSpecialSum();
	testSpecialDifference();
	testSpecialDotProduct();
	testSpecialCrossProduct();
}

void Vector2Tests::testConstructor() {
	float x = 2;
	float y = 5;
	Vector2 v(2, 5);
	assert(v.x == x && v.y == y);
}

// test static methods
void Vector2Tests::testLerp() {}
void Vector2Tests::testStaticDotProduct() {}
void Vector2Tests::testStaticCrossProduct() {}

// test instance methods
void Vector2Tests::testDotProduct() {}
void Vector2Tests::testCrossProduct() {}
void Vector2Tests::testLength() {}
void Vector2Tests::testLengthSquared() {}
void Vector2Tests::testNormalize() {}
void Vector2Tests::testperpCW() {}
void Vector2Tests::testPerpCCW() {}

// test binary operators
void Vector2Tests::testSum() {
	Vector2 op1(1, 2);
	Vector2 op2(2, 3);
	Vector2 result = op1 + op2;
	assert(result == Vector2(3, 5));
}

void Vector2Tests::testDifference() {
	Vector2 op1(3, 7);
	Vector2 op2(2, 3);
	Vector2 result = op1 - op2;
	assert(result == Vector2(1, 4));
}

void Vector2Tests::testMultiplication() {
	Vector2 v(3, 7);
	float s = 3;
	Vector2 result = v * s;
	assert(result == Vector2(9, 21));
}

void Vector2Tests::testDivision() {
	Vector2 v(9, 21);
	float s = 3;
	Vector2 result = v / s;
	assert(result == Vector2(3, 7));
}

void Vector2Tests::testEquality() {
	Vector2 v1(1, 2);
	Vector2 v2(1, 2);
	assert(v1.x == v2.x && v1.y == v2.y);
}

// test friend operators
void Vector2Tests::testReverseMultiplication() {
	Vector2 v(3, 7);
	float s = 3;
	Vector2 result = s * v;
	assert(result == Vector2(9, 21));
}

// special tests
void Vector2Tests::testSpecialNormalize() {}
void Vector2Tests::testSpecialSum() {}
void Vector2Tests::testSpecialDifference() {}
void Vector2Tests::testSpecialDotProduct() {}
void Vector2Tests::testSpecialCrossProduct() {}