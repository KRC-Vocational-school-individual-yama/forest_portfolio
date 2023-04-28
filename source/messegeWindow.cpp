#include "messegeWindow.h"
#include"common/oneCharacterSpacing.h"
#include"common/keystate.h"//ToDo:仮
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

	//ToDo:後のcsv群
	MessegeWindow::Pos messePos = { 325.f,487.f };
	MessegeWindow::Size messeSize = { 504.f,120.f };
	MessegeWindow::Pos messeCharaPos = { 325.f,481.f };//ちょっと飛び出す用
	MessegeWindow::Size messeCharaSize = { 504.f,126.f };
	const int strDispSpeed = 20;//文字送りの速さ

	KeyState* readKey = nullptr;//ToDo:仮
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
	
	 //１文字送りのnew
	 if(oneMesse==nullptr)
		 oneMesse = new OneCharacterSpacing;

	 //１文字送りのInit類
	 oneMesse->SetFont(hFont);
	 oneMesse->SetSpeed(strDispSpeed);
	 
	 readKey = new KeyState(KEY_INPUT_RETURN);

	 //仮
	 messe.title = "謎の少女";
	 messe.text = "この黒猫のいっていることは\n本当なのだろうか。";

	 //Init
	 pos = messePos;
	 size = messeSize;
}

void MessegeWindow::Update(){
	oneMesse->Update();//1文字送りの更新


	bool mouse = CheckHitKeyAll();// GetMouseInput()& MOUSE_INPUT_LEFT;
	bool mouseDown = mouse && !mouseKeyStop;
	bool allDispText = readKey->Down()||mouseDown;

	if (allDispText) {//特定のキーが押されたら
		if (not oneMesse->GetAllDisp()) {//全文表示されていなかったら
			oneMesse->AllDisp();//表示
		}
		else {
			myDisp = false;//それ以外は見えなくする
		}
	}

	//メッセージウィンドウが出てないときはみんな動く
	if (not myDisp) {
		GetScene()->AllUpdateStart();
	}


	mouseKeyStop = mouse;
	readKey->Update();
}

void MessegeWindow::Draw(){
	if (not myDisp)//普段は見えない
		return;

	int x = pos.x; int y = pos.y;
	//SCREEN_WIDTH,SCREEN_HEIGHT

	//ざぶとん
	DispGraph(hImageWindow,x,y,size.x,size.y);

	//タイトルテキスト
	DrawFormatStringToHandle(464,505,0xffffff,hFont,messe.title.c_str());
	
	//本文テキスト
	oneMesse->Draw(482,544,0xffffff);
//	DrawFormatStringToHandle(482,544,0xffffff,hFont,messe.text.c_str());


	//メッセキャラ描画     //座標+サイズ
	SetDrawArea(messeCharaPos.x,messeCharaPos.y
		,messeCharaPos.x+messeCharaSize.x, messeCharaSize.y+messeCharaPos.y);
	
	/*メッセキャラの位置
		pos
		x : 335
		y : 481
		size
		x : 103
		y : 126
	*/

	//ToDo:playerからanyTypeに(seterで変わる変数に)//ToDo:マジックナンバーになっている
	DispGraph(hImage.at(messe.type),messeCharaPos.x,messeCharaPos.y,103.f,126.f);//ToDo:messeCharaと同じ左上にする　後に専用画像に変更の為

	SetDrawArea(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);


}

void MessegeWindow::DispGraph(int img , float x, float y, float sx, float sy) {
	//画像サイズを得る
	int gSizeX = 0;	int gSizeY = 0;
	GetGraphSize(img, &gSizeX, &gSizeY);

	//メッセージのキャラサイズ
	Size charaSize = {sx,sy};
	//大きさの半分
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
