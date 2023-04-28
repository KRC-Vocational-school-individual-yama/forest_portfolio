#include "talkPlayer.h"
#include"libs/scene.h"
#include"TalkObjectManager.h"
#include"talkCat.h"
#include"messegeWindow.h"

namespace {
	//�g��Ȃ�	�Ȃ�
	std::string graphPass = "data/texture/";
	std::string pass[] = { graphPass + "playerNormal.png"
		,graphPass + "playerLine.png"
		,graphPass + "playerDebug.png"
	};

	TalkObject::Pos catPos = { 0,0 };//�g��Ȃ�
	TalkObject::Size catSize = { 0,0 };//�g��Ȃ�
	TalkObject::Pos catSpeechBubblePos = { 0,0 };//�g��Ȃ�
	//���csv�ǂݍ��݂ɂ���
	std::string csvStr = "���̍��L�̌����Ă��邱�Ƃ�\n�{���Ȃ̂ł��傤���H";
	//ToDo:�����o�ϐ���ǉ����Ă��� csv�ǂݍ��݂ɂ���
	std::string csvStrTitle = "��̏���";//��̏���

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

			if (true)//ToDo:���ꂪTRUE����Player���i���Ƙb��

				/*ToDo:�����Ƀe�L�X�g�E�B���h�E��\��*/
				if (CheckClass<MessegeWindow>())

					GetScene()->Invoke<MessegeWindow>()->SetText(
						{ csvStrTitle,mySerif.at(0),MessegeWindow::Type::player }
			);

		}

	}
}

void TalkPlayer::Draw(){
	//TalkObject::Draw();�͂��Ȃ�
	//speechBubble.Draw();�����o��������Ȃ�

}
