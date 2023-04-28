#pragma once
#include<DxLib.h>

class KeyState {
public:
	KeyState(int key);
	bool Down();//押した瞬間
	bool Up();//放した瞬間
	bool Get();//状態

	void Update();//使うUpdate内の下の方に置いてください
private:
	int myKey;
	bool keystop;
};