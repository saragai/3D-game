/*
vector2int.h

(c) 2018 Saragai Takanori
*/
#pragma once

class Vector2Int 
{
public:
	int x;
	int y;

	Vector2Int(): x(0), y(0) {}
	Vector2Int(int x, int y) : x(x), y(y) {}
	Vector2Int(Vector2Int *vector2Int) :x(vector2Int->x), y(vector2Int->y) {}

	void Clear() { x = 0; y = 0; }
};