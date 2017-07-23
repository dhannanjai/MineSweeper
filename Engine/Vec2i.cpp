#include "Vec2i.h"

Vec2i::Vec2i(int x, int y)
{
	this->x = x;
	this->y = y;
}

Vec2i Vec2i::operator+(const Vec2i & rhs) const
{
	return Vec2i(x + rhs.x, y + rhs.y);
}

Vec2i & Vec2i::operator+=(const Vec2i & rhs)
{
	*this = *this + rhs;
	return *this;
	// TODO: insert return statement here
}

Vec2i Vec2i::operator-(const Vec2i & rhs) const
{
	return Vec2i(x - rhs.x, y - rhs.y);
}

Vec2i & Vec2i::operator-=(const Vec2i & rhs)
{
	*this = *this - rhs;
	return *this;
	// TODO: insert return statement here
}

Vec2i Vec2i::operator*(int rhs) const
{
	return Vec2i(x*rhs, y*rhs);
}

Vec2i & Vec2i::operator*=(int rhs)
{
	*this = *this * rhs;
	return *this;
	// TODO: insert return statement here
}

Vec2i Vec2i::operator/(int rhs) const
{
	return Vec2i(static_cast<int>(x / rhs), static_cast<int>(y / rhs));
}

Vec2i & Vec2i::operator/=(int rhs)
{
	*this = *this / rhs;
	return *this;
	// TODO: insert return statement here
}

