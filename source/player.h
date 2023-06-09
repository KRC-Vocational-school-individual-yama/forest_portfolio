#pragma once
#include"libs/object.h"

/// <summary>
/// メインの操作キャラ 遊ぶ人が操作する動きがこれに反映される
/// </summary>
class Player : public Object {
public:
	Player(Scene* sc);
	~Player()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	struct Size {
		float x, y;
	};
	struct Pos {
		float x, y;
	};
private:

	//描画する　左上　座標を貰う 
	void DispPlayer(float x, float y);
	void DispPlayer(Pos p) { DispPlayer(p.x, p.y); }

	//白い背景
	void DebugDisp(float x,float y);
	void DebugDisp(Pos p) { DebugDisp(p.x,p.y); }
	

	Pos pos;
	float vecY;
	float myAngle;
	int hImage;
	int hImageDebug;
	float jumpTimeCount;
	bool isRight;
	bool isJump;
	bool endJump;
};