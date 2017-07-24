#include "RectI.h"

RectI::RectI(int top, int bottom, int left, int right)
{
	this->top = top;
	this->bottom = bottom;
	this->left = left;
	this->right=right;
}

RectI::RectI(const Vec2i & topLeft, const Vec2i & bottomRight)
	:
	RectI(topLeft.y, bottomRight.y, topLeft.x, bottomRight.x)
{
}

RectI::RectI(const Vec2i & topLeft, int width, int height)
	:
	RectI(topLeft, topLeft + Vec2i(width, height))
{
}

bool RectI::IsOverlappedBy(const RectI & other) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}

bool RectI::IsConstaninedBy(const RectI & other) const
{
	return top < other.top && left < other.left && right < other.right && bottom < other.bottom;
}

RectI RectI::GetExpanded(int offset) const
{
	return RectI(top - offset, bottom + offset, left - offset, right + offset);
}

Vec2i RectI::GetCenter() const
{
	return Vec2i(left + (right - left) / 2, top + (bottom - top) / 2);
} 
