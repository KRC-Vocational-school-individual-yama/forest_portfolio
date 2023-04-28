#pragma once

#include"libs/myDxLib.h"

/// <summary>
/// �����o���@�t���i�̗l�Ɏg��
/// </summary>
class SpeechBubble  {
public:
	
	SpeechBubble();
	~SpeechBubble()	;
	void Init()		;
	void Update()	;
	void Draw()		;

	//������true�̎��݂̂��̊֐�������
	bool MouseOver(bool on=false);
	
	void SetPos(float x, float y) { myCollider.posX = x, myCollider.posY = y; }
	//�ꏊ�ɑ����Ďg���� �e�I�u�W�F�N�g�Ɠ����^�C�~���O�œ���Ďg��
	void SetScroll(float scr) { myCollider.posX+=scr; }
private:

	Rect myCollider;
	int hImage;

	bool nowMouseClick;
	bool nowMouseOver;
};