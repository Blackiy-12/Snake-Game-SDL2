#pragma once

template <typename T> class vec2
{
public:
	T x, y;

public:
	vec2() {};

	vec2(T x, T y) : x(x), y(y) {};

	~vec2() {};

	vec2 operator+(vec2 vec)
	{
		return vec2(this->x + vec.x, this->y + vec.y);
	}

	vec2 operator-(vec2 vec)
	{
		return vec2(this->x - vec.x, this->y - vec.y);
	}

	vec2& operator+=(vec2 vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}

	vec2& operator-=(vec2 vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		return *this;
	}

	vec2 operator* (double coif)
	{
		return vec2(this->x * coif, this->y * coif);
	}

	bool operator== (vec2 vec)
	{
		return (this->x == vec.x) && (this->y == vec.y);
	}

	bool operator!= (vec2 vec)
	{
		return (this->x != vec.x) || (this->y != vec.y);
	}

};


template <typename T> class vec3
{
public:
	T x, y, z;

	vec3() {};

	vec3(T x, T y, T z) : x(x), y(y), z(z) {};

	~vec3() {};
};

template <typename T> vec3<T> cross(vec2<T> Left, vec2<T> Right)
{
	return vec3<T>(0, 0, Left.x * Right.y - Left.y * Right.x);
}

template <typename T> vec3<T> cross(vec3<T> Left, vec3<T> Right)
{
	return vec3<T>(Left.y * Right.z - Left.z * Right.y, Left.z * Right.x - Left.x * Right.z, Left.x * Right.y - Left.y * Right.x);
}