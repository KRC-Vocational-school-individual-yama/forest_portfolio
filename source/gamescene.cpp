#include "gamescene.h"

#include<DxLib.h>
#include"libs/scenemanager.h"
//#include"debug/debug_Prank.h"

#include"backImage.h"
#include"player.h"
#include"talkObjectManager.h"
#include"messegeWindow.h"
#include"clickHint.h"
#include"gameMasterAI.h"

GameScene::GameScene()
	:keystop{true}
{
	Create<BackImage>();
	MessegeWindow* messeP= Create<MessegeWindow>();
	ChangeDispRank(messeP,99);
	Create<TalkObjectManager>();
	Create<Player>();
	Create<ClickHint>();
	//Create<Debug_Prank>();
	Create<GameMasterAi>();


}

GameScene::~GameScene(){
}

void GameScene::Update(){
	Scene::Update();

	bool backKey = CheckHitKey(KEY_INPUT_ESCAPE);
	if (backKey && !keystop) {
		SceneManager::SceneChange("Title");
	}keystop = backKey;
}

void GameScene::Draw() {
	Scene::Draw();

#ifdef _DEBUG
	DrawFormatString(100,100,0xffffff,"GameScene\nescape‚Å–ß‚é");
#endif
}