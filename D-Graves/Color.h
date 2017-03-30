#pragma once
#include "Vector3.h"

class Color
{
public:
	Color()
	{
		r = g = b = a = 0;
	}

	Color(int r, int g, int b, int a)
		: r(r), g(g), b(b), a(a) { }

	Color(int r, int g, int b)
		: r(r), g(g), b(b), a(255) { }

	inline Vec4 Get() const
	{
		return Vec4(r, g, b, a);
	}

	inline Vec4 Get(int alpha) const
	{
		return Vec4(r, g, b, alpha);
	}

	inline DWORD GetHex() const
	{
		return static_cast<DWORD>((((a)& 0xff) << 24) | (((r)& 0xff) << 16) | (((g)& 0xff) << 8) | ((b)& 0xff));
	}

	inline DWORD GetHex(int alpha) const
	{
		return static_cast<DWORD>((((alpha)& 0xff) << 24) | (((r)& 0xff) << 16) | (((g)& 0xff) << 8) | ((b)& 0xff));
	}

	inline static Color White() { return Color(255, 255, 255); }
	inline static Color Black() { return Color(0, 0, 0); }
	inline static Color Red() { return Color(255, 0, 0); }
	inline static Color Green() { return Color(0, 255, 0); }
	inline static Color Blue() { return Color(0, 0, 255); }
	inline static Color LightBlue() { return Color(0, 115, 200); }
	inline static Color LightBlue2() { return Color(66, 173, 255); }
	inline static Color	LightGrey2() { return Color(150, 150, 150); }
	inline static Color Grey() { return Color(70, 70, 70); }
	inline static Color LightGrey() { return Color(170, 170, 170); }
	inline static Color DarkGrey() { return Color(45, 45, 45); }
	inline static Color Yellow() { return Color(255, 255, 0); }
	inline static Color Magenta() { return Color(255, 0, 255); }
	inline static Color DarkMagenta() { return Color(139, 0, 139); }
	inline static Color Purple() { return Color(128, 0, 128); }
	inline static Color DarkGreen() { return Color(0, 128, 0); }
	inline static Color DarkGreen2() { return Color(0, 100, 0); }
	inline static Color Crimson() { return Color(220, 20, 60); } // cuz people blush
	inline static Color LightRed2() { return Color(255, 75, 75); }
	inline static Color LightGreen() { return Color(75, 255, 75); }
	inline static Color LightRed() { return Color(255, 50, 50); }
	inline static Color Orange() { return Color(255, 69, 0); }

private:
	int a, r, g, b;
};