#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

using std::ostream;

struct Vector2 {
	const float x;
	const float y;
	Vector2(float xv = 0, float yv = 0);

	// static functions
	static Vector2 lerp(const Vector2& v1, const Vector2& v2, float s);
	static float dot(const Vector2& v1, const Vector2& v2);
	static Vector2 cross(const Vector2& v1, const Vector2& v2);

	// instance functions
	float dot(const Vector2& v2) const;
	Vector2 cross(const Vector2& v2) const;
	float length() const;
	float lengthSquared() const;
	Vector2 normalize() const;
	Vector2 perpCW() const;
	Vector2 perpCCW() const;

	// binary operators
	Vector2 operator+ (const Vector2& other) const;
	Vector2 operator- (const Vector2& other) const;
	Vector2 operator* (float s) const;
	Vector2 operator/ (float s) const;
	bool operator== (const Vector2& other) const;

	// friend operators
	friend ostream& operator<< (ostream& stream, const Vector2& v);
	friend Vector2 operator* (float div, const Vector2& v);
};

#endif