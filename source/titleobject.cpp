#include "titleobject.h"

#include"libs/scenemanager.h"

TitleObject::TitleObject(Scene* sc)
	:Object				(sc)
	,keystop			(true)
	,endKeyStop			(true)
{}

TitleObject::~TitleObject(){
}

void TitleObject::Init(){
}

void TitleObject::Update(){
	ChangeScene();
}

void TitleObject::Draw(){
	int oldFontSize=GetFontSize();
	SetFontSize(64);
	DrawFormatString(200,200,0xeeeeee, "TitleScene");
	SetFontSize(oldFontSize);

	DrawFormatString(300,400,0xffffff,"スペースキーを押してGameScene");
}



bool TitleObject::EndKeyInput(){
	bool endKey = CheckHitKey(KEY_INPUT_ESCAPE);
	if (endKey&&!endKeyStop) 
		return true;
	
	endKeyStop = endKey;
	return false;
}

void TitleObject::ChangeScene() {
	bool sceneKey = CheckHitKey(KEY_INPUT_SPACE)
		||CheckHitKey(KEY_INPUT_RETURN)
		|| (GetMouseInput()&MOUSE_INPUT_LEFT);
	if (sceneKey && !keystop) 
		SceneManager::SceneChange("Game");
	
	bool backKey = CheckHitKey(KEY_INPUT_TAB);
	if (backKey && !keystop) 
		SceneManager::SceneChange("boot");
	
	keystop = sceneKey || backKey;
}

