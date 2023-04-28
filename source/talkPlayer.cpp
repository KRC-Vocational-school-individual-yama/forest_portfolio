#include "talkPlayer.h"
#include"libs/scene.h"
#include"TalkObjectManager.h"
#include"talkCat.h"
#include"messegeWindow.h"

namespace {
	//使わない	ない
	std::string graphPass = "data/texture/";
	std::string pass[] = { graphPass + "playerNormal.png"
		,graphPass + "playerLine.png"
		,graphPass + "playerDebug.png"
	};

	TalkObject::Pos catPos = { 0,0 };//使わない
	TalkObject::Size catSize = { 0,0 };//使わない
	TalkObject::Pos catSpeechBubblePos = { 0,0 };//使わない
	//後でcsv読み込みにする
	std::string csvStr = "この黒猫の言っていることは\n本当なのでしょうか？";
	//ToDo:メンバ変数を追加しておく csv読み込みにする
	std::string csvStrTitle = "謎の少女";//謎の少女

}

TalkPlayer::TalkPlayer(Scene* sc)
	:TalkObject(sc)
{

}

TalkPlayer::~TalkPlayer(){
	TalkObject::~TalkObject();
}

void TalkPlayer::Init(){
	TalkObject::Init();

	mySerif.emplace_back(csvStr);
}

void TalkPlayer::Update(){
	TalkObject::Update();

	if (CheckClass<TalkObjectManager>()) {
		TalkObjectManager* tp = GetScene()->Invoke<TalkObjectManager>();
		TalkCat* cp = tp->Invoke<TalkCat>();
		if (cp == nullptr)
			return;

		if (not cp->GetOnPlayer()) {

			if (true)//ToDo:これがTRUEだとPlayerが永遠と話す

				/*ToDo:ここにテキストウィンドウを表示*/
				if (CheckClass<MessegeWindow>())

					GetScene()->Invoke<MessegeWindow>()->SetText(
						{ csvStrTitle,mySerif.at(0),MessegeWindow::Type::player }
			);

		}

	}
}

void TalkPlayer::Draw(){
	//TalkObject::Draw();はしない
	//speechBubble.Draw();吹き出しもいらない

}
