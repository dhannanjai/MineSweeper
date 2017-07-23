#pragma once

class Vec2i
{
public:
	int x;
	int y;
	
public:
	Vec2i(int x, int y);
	Vec2i operator+(const Vec2i& rhs)const;
	Vec2i& operator+=(const Vec2i& rhs);
	Vec2i operator-(const Vec2i& rhs)const;
	Vec2i& operator-=(const Vec2i& rhs);
	Vec2i operator*(int rhs)const;
	Vec2i& operator*=(int rhs);
	Vec2i operator/(int rhs)const;
	Vec2i& operator/=(int rhs);
	int GetLengthSq()const;
	float GetLength()const;
};