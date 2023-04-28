#include "talkObject.h"
#include"speechBubble.h"
#include"libs/scene.h"
#include"backImage.h"
#include"messegeWindow.h"

namespace {//ToDo:�������牼

	std::string graphPass = "data/texture/";
	std::string pass[] = { graphPass + "treeNormal.png"
		,graphPass + "treeLine.png" 
		,graphPass + "treeDebug.png" 
	};


	//ToDo:��ŏ����@�q�I�u�W�F�N�g�ł�邽�߂�������Ȃ�

		TalkObject::Size treeSize = { 300,400 };//���csv�ǂݍ��݂ɂ���
		//���csv�ǂݍ��݂ɂ���
		std::string csvStr = "���̓����A�^�������s���Ƃ����A����\n�b�𕷂��Ȃ���s�����Ƃ����߂��B";
	
}

TalkObject::TalkObject(Scene* sc)
	:Object(sc)
	,speechBubble()
	,pos{0,0}
	,mySize{0,0}
	,mySerif{}
	,hImage{}
	,onPlayer{false}
	,oldMouse{false}
	,faceToLeft{false}
	,isTalked{false}
{
	hImage.clear();
	mySerif.clear();
}

TalkObject::~TalkObject(){
	for (int i = 0; i < hImage.size(); i++) {
		if (hImage.at(i) > 0)
			DeleteGraph(hImage.at(i));
	}
}

void TalkObject::Init(){
	hImage.resize(GraphType::max);
	for (int i = 0; i < hImage.size(); i++) {
		hImage.at(i) = LoadGraph(pass[i].c_str());
		assert(hImage.at(i) > 0);
	}
	

	speechBubble.Init();
	speechBubble.SetPos(200,150);//ToDo:�� ��������Ȃ�
}

void TalkObject::Update() {

	//���̃N���X���p�������q�I�u�W�F�N�g��Update��
	//�Q�[���̗���������Ă���


	/*
	{//�؂���o�Ă��鐁���o�����N���b�N�@ToDo:��
		bool mouse = (GetMouseInput() & MOUSE_INPUT_LEFT);
		
			if (onPlayer) {//�L�������d�Ȃ��Ă���

				if (speechBubble.MouseOver(mouse && !oldMouse)) {
					//ToDo:�����Ƀe�L�X�g�E�B���h�E��\��
					if (CheckClass<MessegeWindow>())
					
						GetScene()->Invoke<MessegeWindow>()->SetText(
							{ "���",mySerif.at(0),MessegeWindow::Type::tree}
					);
					

				}
			}
			else	//�����o����߂�
			{
				speechBubble.MouseOver(false);
				if (CheckClass<MessegeWindow>())
					GetScene()->Invoke<MessegeWindow>()->SetDisp(false);

			}

		

		oldMouse = mouse;
	}
	*/
	


	//�X�N���[����
	if (CheckClass<BackImage>()) {
		float scrol = GetScene()->Invoke<BackImage>()->GetScroll();
		pos.x+= scrol;
		speechBubble.SetScroll(scrol);
	}

	speechBubble.Update();
}

void TalkObject::Draw(){

	int imgIndex = GraphType::normal;
	if (not isTalked)
		imgIndex = GraphType::line;


	//�摜�T�C�Y�擾
	int gSizeX = 0; int gSizeY = 0;
	GetGraphSize(hImage.at(imgIndex), &gSizeX, &gSizeY);

	//�����摜�T�C�Y
	Size halfSize = { mySize.x / 2,mySize.y / 2 };

	float xSizerRate = (float)mySize.x / (float)gSizeX;
	float ySizerRate = (float)mySize.y / (float)gSizeY;


	//�`��
	DrawRotaGraph3(pos.x + halfSize.x, pos.y + halfSize.y
		, gSizeX / 2, gSizeY / 2
		, xSizerRate, ySizerRate
		, 0, hImage.at(imgIndex), true,faceToLeft);

	if(onPlayer)
		speechBubble.Draw();
	
#ifdef _DEBUG
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255/3);
	DrawRotaGraph3(pos.x + halfSize.x, pos.y + halfSize.y
		, gSizeX / 2, gSizeY / 2
		, xSizerRate, ySizerRate
		, 0, hImage.at(GraphType::debug), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#endif
}

bool TalkObject::Collision(Rect p) {
	FaceToPlayer(p);

	Rect rec = { pos.x,pos.y , (float)mySize.x,(float)mySize.y };

	onPlayer = SquareCollision(rec, p);
	return onPlayer;
}


void TalkObject::SetGraph(std::vector<std::string> pass){
	for (int i = 0; i < GraphType::max; i++) {
		if (hImage.at(i) > 0)
			DeleteGraph(hImage.at(i));


		hImage.at(i) = LoadGraph(pass.at(i).c_str());
		assert(hImage.at(i) > 0);
	}
}

void TalkObject::FaceToPlayer(Rect p){
	if (p.posX >= pos.x) 
		faceToLeft = false;
	else
		faceToLeft = true;
	
}
