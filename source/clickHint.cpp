#include "clickHint.h"
#include"libs/scene.h"
#include"messegeWindow.h"
#include"talkObjectManager.h"
#include"backImage.h"

namespace {
	char* pass = "data/texture/used paper.jpg";
	char* fontPass = "data/font/natumemozi.dft";
	char* clickFontPass = "data/font/Honoka-Shin-Antique-Maru_R.dft";

	//ToDo:後でcsv群
	ClickHint::Size uiSize = { 90,112 };
	std::string csvStr = "黒猫の発言は\nどこか怪しい\n注意しながら話を聞こう";
	ClickHint::Pos uiBackPos = { 1081 ,0 };//ui 黒背景
	ClickHint::Size uiBackSize = { 90,112 };
	ClickHint::Pos uiClickStrPos = { 1103,84 };//ui Clickの文字
	ClickHint::Size uiClickStrSize = { 45,18 };
	ClickHint::Pos uiUsedPaperPos = { 1115,19 };//ui古紙
	ClickHint::Size uiUsedPaperSize = { 39,55 };
	const float scaleRatio = 1.1f;//mouseOver
	ClickHint::Size uiUsedPaperMouseOverSize = { 39.f* scaleRatio,55.f* scaleRatio };

	const float uiUsedPaperRotate = 25;
	ClickHint::Pos hintTextPos = {387,245 };//hint 本文
	ClickHint::Size hintTextSize = {4,41};//hintFont 行,高さ
	ClickHint::Pos hintPagePos = {873,464};//hint ページ数
	ClickHint::Size hintPageSize = {22,41};
	ClickHint::Pos hintUsedPaperPos = {335,120};//hint 背景古紙
	ClickHint::Size hintUsedPaperSize = {577,392};
	ClickHint::Pos hintBackButtonPos = {23,610};//hint 戻るボタン
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
	//Clickを押したらヒント表示
	int x = 0, y = 0;
	GetMousePoint(&x, &y);
	Rect mouse{ (float)x,(float)y,5,5 };
		
	Rect clickButton = { hintBackButtonPos.x,hintBackButtonPos.y,hintBackButtonSize.x,hintBackButtonSize.y };
	if (nowUi) 
		clickButton={ uiBackPos.x,uiBackPos.y,uiBackSize.x,uiBackSize.y };
	
	buttonMouseOver = SquareCollision(mouse, clickButton);

	if (buttonMouseOver && (GetMouseInput() & MOUSE_INPUT_LEFT)) //クリックしたらヒント画面へ
		if (nowUi) {//右上にちょこん
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

	//画像サイズを得る
	int gSizeX = 0;	int gSizeY = 0;
	GetGraphSize(hImage, &gSizeX, &gSizeY);

	//大きさの半分
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
	{//ui　黒背景
		float x = uiBackPos.x;
		float y = uiBackPos.y;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
		DrawBox(x, y, x + uiBackSize.x, uiBackSize.y + y, 0, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//ui 古紙
	Size paperSize = uiUsedPaperSize;
	Pos paperPos = uiUsedPaperPos;
	paperPos.x+= uiUsedPaperSize.x/2;
	paperPos.y+= uiUsedPaperSize.y/2;
	if (buttonMouseOver) {
		paperSize = uiUsedPaperMouseOverSize;
	}
	DispGraph(paperPos, paperSize, uiUsedPaperRotate,false,true);

	//ui Clickの文字
	DrawFormatStringToHandle(uiClickStrPos.x, uiClickStrPos.y, 0xffffff, hFontClick, "Click");

}

void ClickHint::DispHintMain(){

	{//ui　黒背景
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
		DrawBox(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, 0, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	//古紙
	DispGraph(hintUsedPaperPos,hintUsedPaperSize,0,true);//ToDo:マジックナンバー
	//本文
	DrawFormatStringToHandle(hintTextPos.x,hintTextPos.y,0,hFont,csvStr.c_str());
	//ページ数
	DrawFormatStringToHandle(hintPagePos.x,hintPagePos.y,0,hFont,"1");//ToDo:マジックナンバー

	//戻るボタン
	int fontSize = GetFontSize();
	if(buttonMouseOver)
		SetFontSize(hintBackButtonMouseOverSize.y);
	else
		SetFontSize(hintBackButtonSize.y);

	DrawFormatString(hintBackButtonPos.x,hintBackButtonPos.y,0xffffff,"戻る");
	SetFontSize(fontSize);
}

