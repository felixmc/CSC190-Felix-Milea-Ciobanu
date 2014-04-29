#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

using std::ostream;

struct Vector2 {
	const float x;
	const float y;
	Vector2(float xv = 0, float yv = 0) : x(xv), y(yv) {};

	// static functions
	inline static Vector2 lerp(const Vector2& v1, const Vector2& v2, float b) {
		return ((1 - b) * v1) + (b * v2);
	}

	inline static float dot(const Vector2& v1, const Vector2& v2) {
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	inline static float cross(const Vector2& v1, const Vector2& v2) {
		return (v1.x * v2.y) - (v1.y * v2.x);
	}


	// instance functions
	inline float dot(const Vector2& v2) const {
		return Vector2::dot(*this, v2);
	}

	inline float cross(const Vector2& v2) const {
		return Vector2::cross(*this, v2);
	}

	inline float length() const {
		return std::sqrt(this->lengthSquared());
	}

	inline float lengthSquared() const {
		return this->dot(*this);
	}

	inline Vector2 normalize() const {
		return *this / this->length();
	}

	inline Vector2 perpCW() const {
		return Vector2();
	}

	inline Vector2 perpCCW() const {
		return Vector2();
	}


	// binary operators
	inline Vector2 operator+ (const Vector2& other) const {
		return Vector2(this->x + other.x, this->y + other.y);
	}

	inline Vector2 operator- (const Vector2& other) const {
		return Vector2(this->x - other.x, this->y - other.y);
	}

	inline Vector2 operator* (float s) const {
		return Vector2(this->x * s, this->y * s);
	}

	inline Vector2 operator/ (float s) const {
		return Vector2(this->x / s, this->y / s);
	}

	inline bool operator== (const Vector2& other) const {
		return this->x == other.x && this->y == other.y;
	}


	// friend operators
	inline friend Vector2 operator* (float s, const Vector2& v) {
		return v * s;
	}

	inline friend ostream& operator<< (ostream& stream, const Vector2& v) {
		return stream << "{" << v.x << ", " << v.y << "}";
	}

};

#endif