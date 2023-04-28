#pragma once

#include"libs/object.h"

class ClickHint :public Object {
public:
	ClickHint(Scene* sc);
	~ClickHint()		override;
	void Init()			override;
	void Update()		override;
	void Draw()			override;

	struct Size {
		float x, y;
	};
	struct Pos {
		float x, y;
	};
private:
	void DispGraph(Pos pos,Size size,float rot=0,bool reverse=false,bool drawCenter=false);
	void DispUi();//ui��(�����ȃN���b�N)���̕`��
	void DispHintMain();//�q���g��ʂ̕`��
	

	int hImage;
	int hFont;
	int hFontClick;
	bool nowUi;//ToDo:�������@�@ui���q���g��ʂ̐ؑ�flag true�Fui
	bool buttonMouseOver;
};