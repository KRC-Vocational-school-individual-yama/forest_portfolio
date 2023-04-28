#pragma once
#include<DxLib.h>

class KeyState {
public:
	KeyState(int key);
	bool Down();//‰Ÿ‚µ‚½uŠÔ
	bool Up();//•ú‚µ‚½uŠÔ
	bool Get();//ó‘Ô

	void Update();//g‚¤Update“à‚Ì‰º‚Ì•û‚É’u‚¢‚Ä‚­‚¾‚³‚¢
private:
	int myKey;
	bool keystop;
};