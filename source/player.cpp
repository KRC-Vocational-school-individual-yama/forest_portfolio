#include "player.h"
#include"libs/scenemanager.h"
#include"backImage.h"
#include"talkObjectManager.h"
#include"messegeWindow.h"
#include"talkCat.h"
#include"talkPlayer.h"

namespace {
	std::string graphPass = "data/texture/";
	std::string pass[]={graphPass+"character.png"
		,graphPass+"characterDebug.png"};
	using namespace SceneManager;

	Player::Pos charaPos{627,306};//後でcsv読み込みにする
	Player::Size charaSize{177,202};//後でcsv読み込みにする
	float charaSpeed = 100;//後でcsv読み込みにする
	const float maxJumpCount = 0.5;//ジャンプ時間
}

Player::Player(Scene* sc)
	:Object(sc)
	,pos{0,0}
	,vecY{0}
	,myAngle{0}
	,hImage{-1}
	,hImageDebug{-1}
	,jumpTimeCount{maxJumpCount}
	,isRight{false}
	,isJump{false}
	,endJump{false}
{
}

Player::~Player(){
	if (hImage > 0)
		DeleteGraph(hImage);
	if (hImageDebug > 0)
		DeleteGraph(hImageDebug);
	
}


void Player::Init(){
	hImage = LoadGraph(pass[0].c_str());
	assert(hImage>0);
	hImageDebug = LoadGraph(pass[1].c_str());
	assert(hImageDebug >0);

	//Init
	pos = charaPos;
}

void Player::Update(){

	bool leftKey	= CheckHitKey(KEY_INPUT_LEFT)	||CheckHitKey(KEY_INPUT_A);
	bool rightKey	= CheckHitKey(KEY_INPUT_RIGHT)	||CheckHitKey(KEY_INPUT_D);
	bool downKey	= CheckHitKey(KEY_INPUT_DOWN)	||CheckHitKey(KEY_INPUT_S);
	bool jumpKey	= CheckHitKey(KEY_INPUT_UP)		||CheckHitKey(KEY_INPUT_W)	||CheckHitKey(KEY_INPUT_SPACE);
	bool lrKey = leftKey && rightKey;
	bool anLRKey = not leftKey && not rightKey;

	{
		//左右移動
		BackImage* backImagePointer = GetScene()->Invoke<BackImage>();

		if (leftKey) {
			isRight = false;//右を向いていない

			
			float scrollNum = charaSpeed * GetDeltaTime();//スクロール量

			backImagePointer->SetScroll(scrollNum);//背景にスクロール量を送る
			pos.x = max(0, pos.x - scrollNum);//移動適用
		}
		if (rightKey) {
			isRight = true;//右を向いている

			
			float scrollNum = charaSpeed * GetDeltaTime();//スクロール量

			backImagePointer->SetScroll(-scrollNum);//背景にスクロール量を送る
			pos.x = min(SCREEN_WIDTH - charaSize.x, pos.x + scrollNum);//移動適用
		}

		//スクロールしない
		if (lrKey || anLRKey)
			backImagePointer->SetScroll(0);
	}


	{
		//しゃがみ
		if (vecY==0&&downKey) {
			if (isRight)
				myAngle = 90;
			else
				myAngle = -90;
		}
		else {
			myAngle = 0;
		}
	}



	{//ToDo:どっちの挙動が良いか聞く

	 //ジャンプ
		
		 //ボタンを長押し　または　maxJumpCount秒跳ぶ
		bool jumpFlag = jumpKey||jumpTimeCount<maxJumpCount; 

		if (jumpFlag){
			if (endJump /*ToDo:連続ジャンプするか*//*|| vecY==0*/ ) {//ジャンプが終わって　地面に着いたら　連続ジャンプ?
			isJump = true;
			endJump = false;
			jumpTimeCount = 0;
			}
		}
		else {
			isJump = false;
		
			if(vecY == 0 )//空中ジャンプ防止
				endJump = true;
		
		}

		//天井
		if (pos.y + vecY < 0) {
			pos.y = 0;
			isJump = false;
		}


		//３秒間数える
		if (jumpTimeCount < maxJumpCount)
			jumpTimeCount += 1.f * GetDeltaTime();

		//ジャンプ適用
		if (isJump) {
			vecY = -9;
		}

		//重力  
		vecY += 3.1;
		//地面
		if (pos.y + vecY > SCREEN_HEIGHT / 2.5) {
			vecY = 0;
			pos.y = SCREEN_HEIGHT / 2.5;
		}

		//重力適用
		pos.y += vecY;
	}

	{//木などのオブジェクトの当たり判定 
		using ToManager = TalkObjectManager;
		if (CheckClass<ToManager>()) {

			//当たり判定を取る　
			Rect rec = { pos.x,pos.y,charaSize.x,charaSize.y };
			if (not GetScene()->Invoke<ToManager>()->OnCollision(rec)) {

				//吹き出しを戻す //ToDo:見直し
				if (CheckClass<MessegeWindow>())
					GetScene()->Invoke<MessegeWindow>()->SetDisp(false);

			}

		}
	}
}

void Player::Draw(){
#ifdef _DEBUG
	DebugDisp(pos);
	printfDx("pos.x= %f\n",pos.x);
	printfDx("pos.y= %f\n",pos.y);
	printfDx("jumpTime= %f\n",jumpTimeCount);
#endif
	DispPlayer(pos);
}

void Player::DispPlayer(float x,float y){ //※ ここを変えたらDebugDispも変更する
	//画像サイズを得る
	int gSizeX = 0;	int gSizeY=0;
	GetGraphSize(hImage, &gSizeX, &gSizeY);
	
	//大きさの半分
	Size halfSize{charaSize.x/2.f, charaSize.y/2.f};

	//倒れた時の調整	ToDo:要相談 キャラの足元位置によって変わるため
	float posY = y + halfSize.y;
	{
		if (myAngle >= 90||myAngle<=-90){
			posY += halfSize.y / 2;
		}
	}

	DrawRotaGraph3(x+ halfSize.x,posY
		, gSizeX/2, gSizeY/2
		,charaSize.x/gSizeX,charaSize.y/gSizeY
		,DX_PI_F/180*myAngle, hImage, true,isRight);
}

void Player::DebugDisp(float x, float y){

	//DrawBox(x,y,x+charaSize.x,y+charaSize.y,0xffffff,true);

	//画像サイズを得る
	int gSizeX = 0;	int gSizeY = 0;
	GetGraphSize(hImage, &gSizeX, &gSizeY);

	//大きさの半分
	Size halfSize{ charaSize.x / 2.f, charaSize.y / 2.f };

	//倒れた時の調整	ToDo:要相談 キャラの足元位置によって変わるため
	float posY = y + halfSize.y;
	{
		if (myAngle >= 90 || myAngle <= -90) {
			posY += halfSize.y / 2;

		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255/2);

	DrawRotaGraph3(x + halfSize.x, posY
		, gSizeX / 2, gSizeY / 2
		, charaSize.x / gSizeX, charaSize.y / gSizeY
		, DX_PI_F / 180 * myAngle, hImageDebug, true, isRight);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
