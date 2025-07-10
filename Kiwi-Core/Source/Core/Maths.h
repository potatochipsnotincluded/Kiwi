#pragma once

#include <raylib.h>

namespace Kiwi {

	struct Vec3
	{
		float x;
		float y;
		float z;

		Vec3(float x, float y, float z);

		Vec3 operator+(Vec3 other);
		Vec3 operator-(Vec3 other);
		Vec3 operator*(Vec3 other);
		Vec3 operator/(Vec3 other);

		Vec3 operator*(float by);
		Vec3 operator/(float by);

		Vec3& operator*=(Vec3 other);
		Vec3& operator/=(Vec3 other);

		Vec3& operator*=(float by);
		Vec3& operator/=(float by);

		operator Vector3();
	};

	struct Vec2
	{
		float x;
		float y;

		Vec2(float x, float y);

		Vec2 operator+(Vec2 other);
		Vec2 operator-(Vec2 other);
		Vec2 operator*(Vec2 other);
		Vec2 operator/(Vec2 other);

		Vec2 operator*(float by);
		Vec2 operator/(float by);

		Vec2& operator*=(Vec2 other);
		Vec2& operator/=(Vec2 other);

		Vec2& operator*=(float by);
		Vec2& operator/=(float by);

		operator Vector2();
	};

	struct Colour
	{
		float r;
		float g;
		float b;
		float a;

		Colour(float r, float g, float b, float a);

		Colour operator+(Colour other);
		Colour operator-(Colour other);
		Colour operator*(Colour other);
		Colour operator/(Colour other);

		Colour operator*(float by);
		Colour operator/(float by);

		Colour& operator*=(Colour other);
		Colour& operator/=(Colour other);

		Colour& operator*=(float by);
		Colour& operator/=(float by);

		operator Color();
	};

	struct Transform
	{
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;
	};

	namespace Maths {

		float Lerp(float a, float b, float p);

		Vec2 Lerp(Vec2 a, Vec2 b, float p);

		Vec3 Lerp(Vec3 a, Vec3 b, float p);

		Colour Mix(Colour a, Colour b, float p);

		float Map(float val, float oMin, float oMax, float nMin, float nMax);

	}

}