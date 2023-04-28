#include "bootTestObject.h"

#include"scenemanager.h"

BootTestObject::BootTestObject(Scene* sc)
	:Object		(sc)
	,changeCount(0)
	,Daydata()
{
	changeCount = GetNowCount();
}
BootTestObject::~BootTestObject(){

}
void BootTestObject::Update(){
	GetDateTime(&Daydata);

	


	SceneChangeKey();

	//10秒経ったらTitleSceneへ
	int num = GetElapsedTime();
	if (num>=10)
		SceneManager::SceneChange("Title");
}
void BootTestObject::Draw() {

	DrawFormatString(100,150+50*0,0xffffff, "Sec       %12d",Daydata.Sec);
	DrawFormatString(100,150+50*1,0xffffff, "Min       %12d", Daydata.Min);
	DrawFormatString(100,150+50*2,0xffffff, "Hour      %12d", Daydata.Hour);
	DrawFormatString(100,150+50*3,0xffffff, "nowcount  %12d", GetNowCount());
	DrawFormatString(100,150+50*4,0xffffff, "nowcount  %12lld", GetNowHiPerformanceCount());

	for (int i = 0; i < 5; i++) 
		DrawFormatString(100, 155 + i*50, 0xffffff, "______________________");
	

	//時間経過で切り替わる
	DrawFormatString(500,200,0xffffff,"titleに行くまで %2d 秒",10- GetElapsedTime());
	DrawFormatString(500,200+GetFontSize() * 1, 0xffffff, "or");
	DrawFormatString(500,200+GetFontSize() * 2, 0xffffff, "anyKey");

	//上の説明
	std::string explanation = "";
	explanation += "Now it is a Debug Scene \n";
	explanation += "「Space key」 to TitleScene\n";
	explanation += "「Space and LeftShift key」 to GameScene\n";
	DrawFormatString(100, 50, 0xff66ff,explanation.c_str());

	//debug用の主張
	int size = GetFontSize();
	std::string str = "debug";
	SetFontSize(96);
	
	DrawFormatString(400 - str.size() * 96 / 4, 600 - 128, 0xffffff, str.c_str());

	SetFontSize(size);
}


void BootTestObject::SceneChangeKey() {
	bool spaceKey	= CheckHitKey(KEY_INPUT_SPACE);
	bool lShiftKey	= CheckHitKey(KEY_INPUT_LSHIFT);
	if(not lShiftKey)
	spaceKey |= CheckHitKeyAll();
	
	if (spaceKey&& !lShiftKey) 
		SceneManager::SceneChange("Title");
	if (spaceKey&& lShiftKey) 
		SceneManager::SceneChange("Game");
}

inline int BootTestObject::GetElapsedTime(){
	return (GetNowCount() - changeCount) / 1000;
}
