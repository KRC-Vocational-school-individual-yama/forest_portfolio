#pragma once
#include"libs/object.h"

/// <summary>
/// ƒƒCƒ“‚Ì‘€ìƒLƒƒƒ‰ —V‚Ôl‚ª‘€ì‚·‚é“®‚«‚ª‚±‚ê‚É”½‰f‚³‚ê‚é
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

	//•`‰æ‚·‚é@¶ã@À•W‚ğ–á‚¤ 
	void DispPlayer(float x, float y);
	void DispPlayer(Pos p) { DispPlayer(p.x, p.y); }

	//”’‚¢”wŒi
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