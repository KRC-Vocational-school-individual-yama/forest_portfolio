#include "talkCat.h"
#include"libs/scene.h"
#include"messegeWindow.h"
#include"clickHint.h"

namespace {
	std::string graphPass = "data/texture/";
	std::string pass[] = { graphPass + "catNormal.png"
		,graphPass + "catLine.png"
		,graphPass + "catDebug.png"
	};
	
	TalkObject::Pos catPos = {790,341};//後でcsv読み込みにする
	TalkObject::Size catSize = { 113,113 };//後でcsv読み込みにする
	TalkObject::Pos catSpeechBubblePos = {829,265};//後でcsv読み込みにする
	//後でcsv読み込みにする
	std::string csvStr = "この森の出口は、ここをまっすぐさ\n誰にも話さず真っ直ぐ行くんだよ。";
	//ToDo:メンバ変数を追加しておく csv読み込みにする
	std::string csvStrTitle = "黒猫";//黒猫
}

TalkCat::TalkCat(Scene* sc)
	:TalkObject(sc)
{

}

TalkCat::~TalkCat(){
	TalkObject::~TalkObject();


}

void TalkCat::Init(){
	TalkObject::Init();

	std::vector<std::string> sendPass;
	sendPass.resize(GraphType::max);
	for (int i = 0; i <sendPass.size(); i++) {
		sendPass.at(i) = pass[i];
	}
	SetGraph(sendPass);

	//セリフ追加
	mySerif.emplace_back(csvStr);

	mySize = catSize;
	SetPos(catPos.x,catPos.y);
	speechBubble.SetPos(catSpeechBubblePos.x, catSpeechBubblePos.y);
	//speechBubble.SetSize(catSpeechBubbleSize);
	//SetPosSpeechBubble(800+100,300-50); //ToDo:SetPosSpeechBubble 仮必要か謎
}

void TalkCat::Update(){
	TalkObject::Update();

	{//猫から出てくる吹き出しをクリック　ToDo:仮
		bool mouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

		if (onPlayer) {//キャラが重なっている

			if (speechBubble.MouseOver(mouse && !oldMouse)) {
				isTalked = true;

				if (CheckClass<MessegeWindow>())//テキストウィンドウ表示
					GetScene()->Invoke<MessegeWindow>()->SetText(
						{ csvStrTitle,mySerif.at(0),MessegeWindow::Type::cat }
					);
				GetScene()->AllUpdateStop();
				GetScene()->Invoke<MessegeWindow>()->SetMyUpdate();
				GetScene()->Invoke<ClickHint>()->SetMyUpdate();
			}
		}else	//吹き出しエフェクト
			speechBubble.MouseOver(false);




		oldMouse = mouse;
	}

}
