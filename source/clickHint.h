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
	void DispUi();//uiの(小さなクリック)等の描画
	void DispHintMain();//ヒント画面の描画
	

	int hImage;
	int hFont;
	int hFontClick;
	bool nowUi;//ToDo:仮説明　　uiかヒント画面の切替flag true：ui
	bool buttonMouseOver;
};