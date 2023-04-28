#pragma once
class KeyState;

//オンオフの切り替え用
class SwitchButton {
public:
	SwitchButton(int _key);
	~SwitchButton();
	void Update();
	bool Get() { return myflag; }
	void On() { myflag = true; }
	void Off() { myflag = false; }
private:
	int myKey;
	bool myflag;
	KeyState* key;
};