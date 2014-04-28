#include <cmath>
#include "Vector2.h"

Vector2::Vector2(float xv, float yv) : x(xv), y(yv) {};

// static functions
Vector2 Vector2::lerp(const Vector2& v1, const Vector2& v2, float b) {
	return ((1 - b) * v1) + (b * v2);
}

float Vector2::dot(const Vector2& v1, const Vector2& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}

float Vector2::cross(const Vector2& v1, const Vector2& v2) {
	return (v1.x * v2.y) - (v1.y * v2.x);
}

// instance functions
float Vector2::dot(const Vector2& v2) const {
	return Vector2::dot(*this, v2);
}

float Vector2::cross(const Vector2& v2) const {
	return Vector2::cross(*this, v2);
}

float Vector2::length() const {
	return std::sqrt(this->lengthSquared());
}

float Vector2::lengthSquared() const {
	return this->dot(*this);
}

Vector2 Vector2::normalize() const {
	return *this / this->length();
}

//Vector2 Vector2::perpCW() const;
//Vector2 Vector2::perpCCW() const;

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