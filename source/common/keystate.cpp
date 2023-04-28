#include "keystate.h"

KeyState::KeyState(int key)
	:myKey(key)
	,keystop(false)
{
}

bool KeyState::Down(){
	return (CheckHitKey(myKey) &&!keystop);
}

bool KeyState::Up(){
	return (!CheckHitKey(myKey) && keystop);
}

bool KeyState::Get() {
	return CheckHitKey(myKey);
}

void KeyState::Update()
{
	keystop = CheckHitKey(myKey);
}
