#ifndef VECTOR2_TESTS_H
#define VECTOR2_TESTS_H

#include <iostream>
#include "Vector2.h"

class Vector2Tests {
public:
	void runAll();
	void testNormalize();
	void testSum();
	void testDifference();
	void testDotProduct();
	void testCrossProduct();
};

#endif