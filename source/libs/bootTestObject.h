#pragma once

#include"object.h"

class BootTestObject :public Object {
public:
	BootTestObject(Scene* sc);
	~BootTestObject()			override;
	void Init() {}
	void Update()	override;
	void Draw()		override;

private:
	//シーンの切り替え受付
	void SceneChangeKey()	;
	//このクラスが作られてからの経過時間
	int GetElapsedTime();

	int changeCount;
	DATEDATA Daydata;
};