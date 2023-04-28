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
	
	TalkObject::Pos catPos = {790,341};//���csv�ǂݍ��݂ɂ���
	TalkObject::Size catSize = { 113,113 };//���csv�ǂݍ��݂ɂ���
	TalkObject::Pos catSpeechBubblePos = {829,265};//���csv�ǂݍ��݂ɂ���
	//���csv�ǂݍ��݂ɂ���
	std::string csvStr = "���̐X�̏o���́A�������܂�������\n�N�ɂ��b�����^�������s���񂾂�B";
	//ToDo:�����o�ϐ���ǉ����Ă��� csv�ǂݍ��݂ɂ���
	std::string csvStrTitle = "���L";//���L
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

	//�Z���t�ǉ�
	mySerif.emplace_back(csvStr);

	mySize = catSize;
	SetPos(catPos.x,catPos.y);
	speechBubble.SetPos(catSpeechBubblePos.x, catSpeechBubblePos.y);
	//speechBubble.SetSize(catSpeechBubbleSize);
	//SetPosSpeechBubble(800+100,300-50); //ToDo:SetPosSpeechBubble ���K�v����
}

void TalkCat::Update(){
	TalkObject::Update();

	{//�L����o�Ă��鐁���o�����N���b�N�@ToDo:��
		bool mouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

		if (onPlayer) {//�L�������d�Ȃ��Ă���

			if (speechBubble.MouseOver(mouse && !oldMouse)) {
				isTalked = true;

				if (CheckClass<MessegeWindow>())//�e�L�X�g�E�B���h�E�\��
					GetScene()->Invoke<MessegeWindow>()->SetText(
						{ csvStrTitle,mySerif.at(0),MessegeWindow::Type::cat }
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
