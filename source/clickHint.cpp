#include "clickHint.h"
#include"libs/scene.h"
#include"messegeWindow.h"
#include"talkObjectManager.h"
#include"backImage.h"

namespace {
	char* pass = "data/texture/used paper.jpg";
	char* fontPass = "data/font/natumemozi.dft";
	char* clickFontPass = "data/font/Honoka-Shin-Antique-Maru_R.dft";

	//ToDo:���csv�Q
	ClickHint::Size uiSize = { 90,112 };
	std::string csvStr = "���L�̔�����\n�ǂ���������\n���ӂ��Ȃ���b�𕷂���";
	ClickHint::Pos uiBackPos = { 1081 ,0 };//ui ���w�i
	ClickHint::Size uiBackSize = { 90,112 };
	ClickHint::Pos uiClickStrPos = { 1103,84 };//ui Click�̕���
	ClickHint::Size uiClickStrSize = { 45,18 };
	ClickHint::Pos uiUsedPaperPos = { 1115,19 };//ui�Î�
	ClickHint::Size uiUsedPaperSize = { 39,55 };
	const float scaleRatio = 1.1f;//mouseOver
	ClickHint::Size uiUsedPaperMouseOverSize = { 39.f* scaleRatio,55.f* scaleRatio };

	const float uiUsedPaperRotate = 25;
	ClickHint::Pos hintTextPos = {387,245 };//hint �{��
	ClickHint::Size hintTextSize = {4,41};//hintFont �s,����
	ClickHint::Pos hintPagePos = {873,464};//hint �y�[�W��
	ClickHint::Size hintPageSize = {22,41};
	ClickHint::Pos hintUsedPaperPos = {335,120};//hint �w�i�Î�
	ClickHint::Size hintUsedPaperSize = {577,392};
	ClickHint::Pos hintBackButtonPos = {23,610};//hint �߂�{�^��
	ClickHint::Size hintBackButtonSize = {49,25};
	ClickHint::Size hintBackButtonMouseOverSize = {49*scaleRatio,25*scaleRatio};
	
}

ClickHint::ClickHint(Scene* sc)
	:Object(sc)
	,hImage{-1}
	,hFont{-1}
	,hFontClick{-1}
	,nowUi{true}
	,buttonMouseOver{false}
{
}

ClickHint::~ClickHint(){
	if (hImage > 0)
		DeleteGraph(hImage);
	if (hFont > 0)
		DeleteFontToHandle(hFont);
	if (hFontClick > 0)
		DeleteFontToHandle(hFontClick);
}

void ClickHint::Init(){
	hImage = LoadGraph(pass);
	assert(hImage > 0);
	hFont = LoadFontDataToHandle(fontPass);
	assert(hFont > 0);
	hFontClick = LoadFontDataToHandle(clickFontPass);
	assert(hFontClick > 0);

}

void ClickHint::Update(){
	//Click����������q���g�\��
	int x = 0, y = 0;
	GetMousePoint(&x, &y);
	Rect mouse{ (float)x,(float)y,5,5 };
		
	Rect clickButton = { hintBackButtonPos.x,hintBackButtonPos.y,hintBackButtonSize.x,hintBackButtonSize.y };
	if (nowUi) 
		clickButton={ uiBackPos.x,uiBackPos.y,uiBackSize.x,uiBackSize.y };
	
	buttonMouseOver = SquareCollision(mouse, clickButton);

	if (buttonMouseOver && (GetMouseInput() & MOUSE_INPUT_LEFT)) //�N���b�N������q���g��ʂ�
		if (nowUi) {//�E��ɂ��傱��
			nowUi = false;
			GetScene()->AllUpdateStop();
			SetMyUpdate(false);
		}else {
			GetScene()->AllUpdateStart();
			nowUi = true;
		}
	
}

void ClickHint::Draw(){

	if(nowUi)
		DispUi();
	else
		DispHintMain();
}

void ClickHint::DispGraph(Pos pos, Size size, float rot,bool reverse, bool drawCenter){

	//�摜�T�C�Y�𓾂�
	int gSizeX = 0;	int gSizeY = 0;
	GetGraphSize(hImage, &gSizeX, &gSizeY);

	//�傫���̔���
	Size halfSize{ size.x / 2.f, size.y / 2.f };
	if (not drawCenter) {
	DrawRotaGraph3(pos.x + halfSize.x, pos.y + halfSize.y
		, gSizeX / 2, gSizeY / 2
		, size.x / gSizeX, size.y / gSizeY
		, DX_PI_F / 180 * rot, hImage, true,reverse);
	}
	else {
		DrawRotaGraph3(pos.x , pos.y 
			, gSizeX / 2, gSizeY / 2
			, size.x / gSizeX, size.y / gSizeY
			, DX_PI_F / 180 * rot, hImage, true, reverse);
	}
}

void ClickHint::DispUi() {
	{//ui�@���w�i
		float x = uiBackPos.x;
		float y = uiBackPos.y;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
		DrawBox(x, y, x + uiBackSize.x, uiBackSize.y + y, 0, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//ui �Î�
	Size paperSize = uiUsedPaperSize;
	Pos paperPos = uiUsedPaperPos;
	paperPos.x+= uiUsedPaperSize.x/2;
	paperPos.y+= uiUsedPaperSize.y/2;
	if (buttonMouseOver) {
		paperSize = uiUsedPaperMouseOverSize;
	}
	DispGraph(paperPos, paperSize, uiUsedPaperRotate,false,true);

	//ui Click�̕���
	DrawFormatStringToHandle(uiClickStrPos.x, uiClickStrPos.y, 0xffffff, hFontClick, "Click");

}

void ClickHint::DispHintMain(){

	{//ui�@���w�i
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
		DrawBox(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, 0, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	//�Î�
	DispGraph(hintUsedPaperPos,hintUsedPaperSize,0,true);//ToDo:�}�W�b�N�i���o�[
	//�{��
	DrawFormatStringToHandle(hintTextPos.x,hintTextPos.y,0,hFont,csvStr.c_str());
	//�y�[�W��
	DrawFormatStringToHandle(hintPagePos.x,hintPagePos.y,0,hFont,"1");//ToDo:�}�W�b�N�i���o�[

	//�߂�{�^��
	int fontSize = GetFontSize();
	if(buttonMouseOver)
		SetFontSize(hintBackButtonMouseOverSize.y);
	else
		SetFontSize(hintBackButtonSize.y);

	DrawFormatString(hintBackButtonPos.x,hintBackButtonPos.y,0xffffff,"�߂�");
	SetFontSize(fontSize);
}

