#pragma once

#include"libs/myDxLib.h"

/// <summary>
/// 吹き出し　付属品の様に使う
/// </summary>
class SpeechBubble  {
public:
	
	SpeechBubble();
	~SpeechBubble()	;
	void Init()		;
	void Update()	;
	void Draw()		;

	//引数がtrueの時のみこの関数が動く
	bool MouseOver(bool on=false);
	
	void SetPos(float x, float y) { myCollider.posX = x, myCollider.posY = y; }
	//場所に足して使われる 親オブジェクトと同じタイミングで入れて使う
	void SetScroll(float scr) { myCollider.posX+=scr; }
private:

	Rect myCollider;
	int hImage;

	bool nowMouseClick;
	bool nowMouseOver;
};