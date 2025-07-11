#include "Maths.h"

namespace Kiwi {

	Vec3::Vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vec3 Vec3::operator+(Vec3 other)
	{
		return Vec3(other.x + x, other.y + y, other.z + z);
	}

	Vec3 Vec3::operator-(Vec3 other)
	{
		return Vec3(other.x - x, other.y - y, other.z - z);
	}

	Vec3 Vec3::operator*(Vec3 other)
	{
		return Vec3(other.x * x, other.y * y, other.z * z);
	}

	Vec3 Vec3::operator/(Vec3 other)
	{
		return Vec3(other.x / x, other.y / y, other.z / z);
	}

	Vec3 Vec3::operator*(float by)
	{
		return Vec3(by * x, by * y, by * z);
	}

	Vec3 Vec3::operator/(float by)
	{
		return Vec3(by / x, by / y, by / z);
	}

	Vec3& Vec3::operator*=(Vec3 other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vec3& Vec3::operator/=(Vec3 other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	Vec3& Vec3::operator*=(float by)
	{
		x *= by;
		y *= by;
		z *= by;
		return *this;
	}

	Vec3& Vec3::operator/=(float by)
	{
		x /= by;
		y /= by;
		z /= by;
		return *this;
	}

	Vec3::operator Vector3()
	{
		return Vector3(x, y, z);
	}

	Vec2::Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vec2 Vec2::operator+(Vec2 other)
	{
		return Vec2(other.x + x, other.y + y);
	}

	Vec2 Vec2::operator-(Vec2 other)
	{
		return Vec2(other.x - x, other.y - y);
	}

	Vec2 Vec2::operator*(Vec2 other)
	{
		return Vec2(other.x * x, other.y * y);
	}

	Vec2 Vec2::operator/(Vec2 other)
	{
		return Vec2(other.x / x, other.y / y);
	}

	Vec2& Vec2::operator*=(Vec2 other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vec2& Vec2::operator/=(Vec2 other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	Vec2& Vec2::operator*=(float by)
	{
		x *= by;
		y *= by;
		return *this;
	}

	Vec2& Vec2::operator/=(float by)
	{
		x /= by;
		y /= by;
		return *this;
	}

	Vec2::operator Vector2()
	{
		return Vector2(x, y);
	}

	Colour::Colour(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Colour Colour::operator+(Colour other)
	{
		return Colour{ r + other.r, g + other.g, b + other.b, a + other.a };
	}

	Colour Colour::operator-(Colour other)
	{
		return Colour{ r - other.r, g - other.g, b - other.b, a - other.a };
	}

	Colour Colour::operator*(Colour other)
	{
		return Colour{ r * other.r, g * other.g, b * other.b, a * other.a };
	}

	Colour Colour::operator/(Colour other)
	{
		return Colour{ r / other.r, g / other.g, b / other.b, a / other.a };
	}

	Colour Colour::operator*(float by)
	{
		return Colour{ r * by, g * by, b * by, a * by };
	}

	Colour Colour::operator/(float by)
	{
		return Colour{ r / by, g / by, b / by, a / by };
	}

	Colour& Colour::operator*=(Colour other)
	{
		r *= other.r;
		g *= other.g;
		b *= other.b;
		a *= other.a;
		return *this;
	}

	Colour& Colour::operator/=(Colour other)
	{
		r /= other.r;
		g /= other.g;
		b /= other.b;
		a /= other.a;
		return *this;
	}

	Colour& Colour::operator*=(float by)
	{
		r *= by;
		g *= by;
		b *= by;
		a *= by;
		return *this;
	}

	Colour& Colour::operator/=(float by)
	{
		r /= by;
		g /= by;
		b /= by;
		a /= by;
		return *this;
	}

	Colour::operator Color()
	{
		return Color(r, g, b, a);
	}

	float Maths::Lerp(float a, float b, float p)
	{
		return a + (b - a) * p;
	}

	Vec2 Maths::Lerp(Vec2 a, Vec2 b, float p)
	{
		return Vec2(Lerp(a.x, b.x, p), Lerp(a.y, b.y, p));
	}

	Vec3 Maths::Lerp(Vec3 a, Vec3 b, float p)
	{
		return Vec3(Lerp(a.x, b.x, p), Lerp(a.y, b.y, p), Lerp(a.z, b.z, p));
	}

	Colour Maths::Mix(Colour a, Colour b, float p)
	{
		return Colour(Lerp(a.r, b.r, p), Lerp(a.g, b.g, p), Lerp(a.b, b.b, p), Lerp(a.a, b.a, p));
	}

	float Maths::Map(float val, float oMin, float oMax, float nMin, float nMax)
	{
		return nMin + (val - oMin) * (nMax - nMin) / (oMax - oMin);
	}

	float Maths::Random(float min, float max)
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dist(min, max);
		return dist(gen);
	}

	int32_t Maths::Random(int32_t min, int32_t max)
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<int32_t> dist(min, max);
		return dist(gen);
	}

	uint32_t Maths::Random(uint32_t min, uint32_t max)
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<int32_t> dist(min, max);
		return dist(gen);
	}

}


