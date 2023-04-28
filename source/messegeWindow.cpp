#include "messegeWindow.h"
#include"common/oneCharacterSpacing.h"
#include"common/keystate.h"//ToDo:��
#include"libs/scene.h"

namespace {
	std::string graphPass = "data/texture/messeChara/";
	std::string pass[] = { graphPass + "character_messe.png"
		,graphPass + "treeLine_messe.png"
		,graphPass + "catLine_messe.png"
		,graphPass + "flowerLine_messe.png"};
	char* passMesse = "data/texture/messe.png";
	char* fontPass = "data/font/Honoka-Shin-Antique-Maru_R.dft";
//	char* fontPass = "data/font/natumemozi.dft";

	//ToDo:���csv�Q
	MessegeWindow::Pos messePos = { 325.f,487.f };
	MessegeWindow::Size messeSize = { 504.f,120.f };
	MessegeWindow::Pos messeCharaPos = { 325.f,481.f };//������Ɣ�яo���p
	MessegeWindow::Size messeCharaSize = { 504.f,126.f };
	const int strDispSpeed = 20;//��������̑���

	KeyState* readKey = nullptr;//ToDo:��
}

MessegeWindow::MessegeWindow(Scene* sc)
	:Object(sc)
	,oneMesse{nullptr}
	,messe{"","",Type::non}
	,hImage{}
	,pos{0,0}
	,size{0,0}
	,hFont{-1}
	,hImageWindow{-1}
	,myDisp{false}
	,mouseKeyStop{false}
{
	hImage.clear();
}

MessegeWindow::~MessegeWindow(){
	for (int i = 0; i < hImage.size(); i++) {
		if (hImage.at(i) > 0)
			DeleteGraph(hImage.at(i));
	}

	if (hFont > 0)
		DeleteFontToHandle(hFont);
	if (oneMesse != nullptr)
		delete oneMesse;
	if (hImageWindow > 0)
		DeleteGraph(hImageWindow);
	if (readKey != nullptr)
		delete readKey;
	readKey = nullptr;
}

void MessegeWindow::Init(){
	hImage.resize(static_cast<int>(Type::max));
	for (int i = 0; i < hImage.size(); i++) {
		hImage.at(i) = LoadGraph(pass[i].c_str());
		assert(hImage.at(i) > 0);
	}

	hFont= LoadFontDataToHandle(fontPass);
	 assert(hFont>0);

	 hImageWindow = LoadGraph(passMesse);
	 assert(hImageWindow > 0);
	
	 //�P���������new
	 if(oneMesse==nullptr)
		 oneMesse = new OneCharacterSpacing;

	 //�P���������Init��
	 oneMesse->SetFont(hFont);
	 oneMesse->SetSpeed(strDispSpeed);
	 
	 readKey = new KeyState(KEY_INPUT_RETURN);

	 //��
	 messe.title = "��̏���";
	 messe.text = "���̍��L�̂����Ă��邱�Ƃ�\n�{���Ȃ̂��낤���B";

	 //Init
	 pos = messePos;
	 size = messeSize;
}

void MessegeWindow::Update(){
	oneMesse->Update();//1��������̍X�V


	bool mouse = CheckHitKeyAll();// GetMouseInput()& MOUSE_INPUT_LEFT;
	bool mouseDown = mouse && !mouseKeyStop;
	bool allDispText = readKey->Down()||mouseDown;

	if (allDispText) {//����̃L�[�������ꂽ��
		if (not oneMesse->GetAllDisp()) {//�S���\������Ă��Ȃ�������
			oneMesse->AllDisp();//�\��
		}
		else {
			myDisp = false;//����ȊO�͌����Ȃ�����
		}
	}

	//���b�Z�[�W�E�B���h�E���o�ĂȂ��Ƃ��݂͂�ȓ���
	if (not myDisp) {
		GetScene()->AllUpdateStart();
	}


	mouseKeyStop = mouse;
	readKey->Update();
}

void MessegeWindow::Draw(){
	if (not myDisp)//���i�͌����Ȃ�
		return;

	int x = pos.x; int y = pos.y;
	//SCREEN_WIDTH,SCREEN_HEIGHT

	//���ԂƂ�
	DispGraph(hImageWindow,x,y,size.x,size.y);

	//�^�C�g���e�L�X�g
	DrawFormatStringToHandle(464,505,0xffffff,hFont,messe.title.c_str());
	
	//�{���e�L�X�g
	oneMesse->Draw(482,544,0xffffff);
//	DrawFormatStringToHandle(482,544,0xffffff,hFont,messe.text.c_str());


	//���b�Z�L�����`��     //���W+�T�C�Y
	SetDrawArea(messeCharaPos.x,messeCharaPos.y
		,messeCharaPos.x+messeCharaSize.x, messeCharaSize.y+messeCharaPos.y);
	
	/*���b�Z�L�����̈ʒu
		pos
		x : 335
		y : 481
		size
		x : 103
		y : 126
	*/

	//ToDo:player����anyType��(seter�ŕς��ϐ���)//ToDo:�}�W�b�N�i���o�[�ɂȂ��Ă���
	DispGraph(hImage.at(messe.type),messeCharaPos.x,messeCharaPos.y,103.f,126.f);//ToDo:messeChara�Ɠ�������ɂ���@��ɐ�p�摜�ɕύX�̈�

	SetDrawArea(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);


}

void MessegeWindow::DispGraph(int img , float x, float y, float sx, float sy) {
	//�摜�T�C�Y�𓾂�
	int gSizeX = 0;	int gSizeY = 0;
	GetGraphSize(img, &gSizeX, &gSizeY);

	//���b�Z�[�W�̃L�����T�C�Y
	Size charaSize = {sx,sy};
	//�傫���̔���
	Size halfSize{ charaSize.x / 2.f, charaSize.y / 2.f };

	DrawRotaGraph3(x + halfSize.x, y + halfSize.y
		, gSizeX / 2, gSizeY / 2
		, charaSize.x / gSizeX, charaSize.y / gSizeY
		, 0, img, true, false);
}


void MessegeWindow::SetText(Text t){
	messe = t;
	oneMesse->SetStr(t.text);
	SetDisp(true);
	mouseKeyStop = true;
}
