#include "talkTree.h"
#include"libs/scene.h"
#include"messegeWindow.h"
#include"clickHint.h"

namespace {

	std::string graphPass = "data/texture/";
	std::string pass[] = { graphPass + "treeNormal.png"
		,graphPass + "treeLine.png"
		,graphPass + "treeDebug.png"
	};


	TalkObject::Size treeSize = { 300,400 };//後でcsv読み込みにする
	//後でcsv読み込みにする
	std::string csvStr = "この道を、真っ直ぐ行くといい、だが\n話を聞きながら行くことを勧めるよ。";
	//ToDo:メンバ変数を追加しておく csv読み込みにする
	std::string csvStrTitle = "大木";//大木
}

TalkTree::TalkTree(Scene* sc)
	:TalkObject(sc)
{

}

TalkTree::~TalkTree(){
	TalkObject::~TalkObject();

}

void TalkTree::Init(){
	TalkObject::Init();



	std::vector<std::string> sendPass;
	sendPass.resize(GraphType::max);
	for (int i = 0; i < sendPass.size(); i++) {
		sendPass.at(i) = pass[i];
	}
	SetGraph(sendPass);
	speechBubble.SetPos(200, 150);
	mySize = treeSize;

	//セリフ追加
	mySerif.emplace_back(csvStr);
}

void TalkTree::Update(){
	TalkObject::Update();


	{//木から出てくる吹き出しをクリック　ToDo:仮
		bool mouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

		if (onPlayer) {//キャラが重なっている

			if (speechBubble.MouseOver(mouse && !oldMouse)) {
				/*ToDo:ここにテキストウィンドウを表示*/

				isTalked = true;
				if (CheckClass<MessegeWindow>())

					GetScene()->Invoke<MessegeWindow>()->SetText(
						{ csvStrTitle,mySerif.at(0),MessegeWindow::Type::tree }
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
