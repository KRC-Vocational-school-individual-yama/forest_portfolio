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


	TalkObject::Size treeSize = { 300,400 };//���csv�ǂݍ��݂ɂ���
	//���csv�ǂݍ��݂ɂ���
	std::string csvStr = "���̓����A�^�������s���Ƃ����A����\n�b�𕷂��Ȃ���s�����Ƃ����߂��B";
	//ToDo:�����o�ϐ���ǉ����Ă��� csv�ǂݍ��݂ɂ���
	std::string csvStrTitle = "���";//���
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

	//�Z���t�ǉ�
	mySerif.emplace_back(csvStr);
}

void TalkTree::Update(){
	TalkObject::Update();


	{//�؂���o�Ă��鐁���o�����N���b�N�@ToDo:��
		bool mouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

		if (onPlayer) {//�L�������d�Ȃ��Ă���

			if (speechBubble.MouseOver(mouse && !oldMouse)) {
				/*ToDo:�����Ƀe�L�X�g�E�B���h�E��\��*/

				isTalked = true;
				if (CheckClass<MessegeWindow>())

					GetScene()->Invoke<MessegeWindow>()->SetText(
						{ csvStrTitle,mySerif.at(0),MessegeWindow::Type::tree }
				);

				GetScene()->AllUpdateStop();
				GetScene()->Invoke<MessegeWindow>()->SetMyUpdate();
				GetScene()->Invoke<ClickHint>()->SetMyUpdate();

			}
		}else	//�����o���G�t�F�N�g
			speechBubble.MouseOver(false);




		oldMouse = mouse;
	}

}
