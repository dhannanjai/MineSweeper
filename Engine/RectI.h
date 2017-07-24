#pragma once
#include"Vec2i.h"

class RectI
{
public:
	int top, bottom, left, right;
public:
	RectI() = default;
	RectI(int top, int bottom, int left, int right);
	RectI(const Vec2i& topLeft, const Vec2i& bottomRight);
	RectI(const Vec2i& topLeft, int width, int height);
	
	bool IsOverlappedBy(const RectI& other)const;
	bool IsConstaninedBy(const RectI& other)const;
	bool Contains(Vec2i point)const; // a check for a point.
	RectI GetExpanded(int offset)const;
	Vec2i GetCenter()const;
};