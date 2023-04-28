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
	//�V�[���̐؂�ւ���t
	void SceneChangeKey()	;
	//���̃N���X������Ă���̌o�ߎ���
	int GetElapsedTime();

	int changeCount;
	DATEDATA Daydata;
};