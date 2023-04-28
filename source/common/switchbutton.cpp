#include "switchbutton.h"
#include"keystate.h"

SwitchButton::SwitchButton(int _key)
	:myKey(_key)
	, myflag(false)
	, key(nullptr)
{
	key = new KeyState(myKey);
}


SwitchButton::~SwitchButton(){
	if (key != nullptr)
		delete key;
}

void SwitchButton::Update()
{
	if (key->Down()) {
		if (myflag)
			myflag = false;
		else
			myflag = true;
	}


	key->Update();
}