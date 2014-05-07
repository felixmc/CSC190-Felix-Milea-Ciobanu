#ifndef VECTOR2_TESTS_H
#define VECTOR2_TESTS_H

class Vector2Tests {
public:
	void runAll();

	void testConstructor();

	// test static methods
	void testLerp();
	void testStaticDotProduct();
	void testStaticCrossProduct();

	// test instance methods
	void testDotProduct();
	void testCrossProduct();
	void testLength();
	void testLengthSquared();
	void testNormalize();
	void testperpCW();
	void testPerpCCW();

	// test binary operators
	void testSum();
	void testDifference();
	void testMultiplication();
	void testDivision();
	void testEquality();

	// test friend operators
	void testReverseMultiplication();

	// special tests
	void testSpecialNormalize();
	void testSpecialSum();
	void testSpecialDifference();
	void testSpecialDotProduct();
	void testSpecialCrossProduct();
};

#endif