#pragma once
#include"libs/object.h"

/// <summary>
/// ���C���̑���L���� �V�Ԑl�����삷�铮��������ɔ��f�����
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

	//�`�悷��@����@���W��Ⴄ 
	void DispPlayer(float x, float y);
	void DispPlayer(Pos p) { DispPlayer(p.x, p.y); }

	//�����w�i
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