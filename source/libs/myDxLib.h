#pragma once

#include<DxLib.h>
#include<assert.h>
#include<cmath>
#include<array>
#include"../main/config.h"
#include"../common/keystate.h"
#include"../common/switchbutton.h"


#define not !

namespace DxLib {
	struct Vec2 {
		int x, y;
	};

	inline Vec2 operator +(const Vec2& a,const Vec2& b) {
		return Vec2{ a.x + b.x,a.y + b.y };
	}
	inline Vec2 operator -(const Vec2& a, const Vec2 b) {
		return Vec2{a.x-b.x,a.y-b.y};
	}
	inline Vec2 operator *(const Vec2& a, const Vec2& b) {
		return Vec2{a.x*b.x,a.y*b.y};
	}
	inline Vec2 operator /(const Vec2& a, const Vec2& b) {
		return Vec2{a.x/b.x,a.y/b.y};
	}
	inline Vec2 operator %(const Vec2& a, const Vec2& b) {
		return Vec2{a.x%b.x,a.y%b.y};
	}

	inline Vec2& operator +=( Vec2& a, const Vec2& b) {
		a.x += b.x;
		a.y += b.y;
		return a;
	}
	inline Vec2 operator -=( Vec2& a, const Vec2& b) {
		a.x -= b.x;
		a.y -= b.y;
		return a;
	}
	inline Vec2 operator *=(Vec2& a, const Vec2& b) {
		a.x *= b.x;
		a.y *= b.y;
		return a;
	}
	inline Vec2 operator /=(Vec2& a, const Vec2& b) {
		a.x /= b.x;
		a.y /= b.y;
		return a;
	}
	inline Vec2 operator %=(Vec2& a, const Vec2& b) {
		a.x %= b.x;
		a.y%= b.y;
		return a;
	}
	inline const bool operator ==(const Vec2& a, const Vec2& b) {
		return a.x==b.x&&a.y==b.y;
	}

	struct Rect {
		Rect(float x, float y, float sx, float sy) 
			:posX(x)
			,posY(y)
			,sizeX(sx)
			,sizeY(sy)
		{}

		float posX;
		float posY;
		float sizeX;
		float sizeY;
	};

	//ŽlŠp“–‚½‚è”»’è
	inline bool SquareCollision(Rect a,Rect b) {
		if (a.posY >= b.posY+b.sizeY)
			return false;//up
		if (a.posY+a.sizeY <= b.posY)
			return false;//down

		if (a.posX >= b.posX+b.sizeX)
			return false;//left
		if (a.posX+a.sizeX <= b.posX)
			return false;//right


		return true;
	}
}