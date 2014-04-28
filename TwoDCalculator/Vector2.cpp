#include "Vector2.h"

Vector2::Vector2(float xv, float yv) : x(xv), y(yv) {};

//// static functions
//static Vector2 lerp(const Vector2& v1, const Vector2& v2, float s);
//static Vector2 dot(const Vector2& v1, const Vector2& v2);
//static Vector2 cross(const Vector2& v1, const Vector2& v2);

//// instance functions
//Vector2 dot(const Vector2&) const;
//Vector2 cross(const Vector2&) const;
//float length() const;
//float lengthSquared() const;
//Vector2 normalize() const;
//Vector2 perpCW() const;
//Vector2 perpCCW() const;

// binary operators
Vector2 Vector2::operator+ (const Vector2& other) const {
	return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator- (const Vector2& other) const {
	return Vector2(this->x - other.x, this->y - other.y);
}

Vector2 Vector2::operator* (float s) const {
	return Vector2(this->x * s, this->y * s);
}

Vector2 Vector2::operator/ (float s) const {
	return Vector2(this->x / s, this->y / s);
}

bool Vector2::operator== (const Vector2& other) const {
	return this->x == other.x && this->y == other.y;
}

// friend operators
ostream& operator<< (ostream& stream, const Vector2& v) {
	return stream << "{" << v.x << ", " << v.y << "}";
}

Vector2 operator* (float s, const Vector2& v) {
	return v * s;
}


//
//	float length() const {
//		static const float length = 1;
//		return length;
//	}
