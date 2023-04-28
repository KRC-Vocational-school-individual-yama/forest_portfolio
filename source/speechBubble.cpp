#include"speechBubble.h"

namespace {
	char* pass = "data/texture/speechBubble.png";
}

SpeechBubble::SpeechBubble()
	:myCollider{0,0,0,0}
	,hImage{-1}
	,nowMouseClick{false}
{

}
SpeechBubble::~SpeechBubble() {
	if (hImage > 0)
		DeleteGraph(hImage);
}
void SpeechBubble::Init() {
	hImage = LoadGraph(pass);
	assert(hImage > 0);

	//画像の大きさを貰う
	int x = 0; int y = 0;
	GetGraphSize(hImage,&x,&y);
	myCollider.sizeX = x;
	myCollider.sizeY = y;

	//Init
	myCollider.posX = 0;
	myCollider.posY = 0;

}
void SpeechBubble::Update() {

	//スクロール量は外部から

	//マウスオーバーをフラグに入れる
	int x = 0; int y = 0;
	GetMousePoint(&x, &y);
	Rect rec = { (float)x,(float)y,5,5 };
	nowMouseOver= SquareCollision(myCollider, rec);
}
void SpeechBubble::Draw() {
	
	
	//描画
		int blend = 255;
		
		//マウス座標取得
		int x = 0; int y = 0;
		GetMousePoint(&x, &y);

		if (not nowMouseOver) {//マウスが吹き出しに重なっていないなら
			blend /= 1.2;//半透明
		}


		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
		Vec2 p = { myCollider.posX,myCollider.posY };
		DrawGraph(p.x, p.y, hImage, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	//__描画


#ifdef _DEBUG //白い枠
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255/3);
	int xSize = myCollider.sizeX+myCollider.posX ; int ySize = myCollider.sizeY+myCollider.posY;
	DrawBox(p.x,p.y,xSize,ySize,0xffffff,nowMouseClick);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#endif
}

bool SpeechBubble::MouseOver(bool on) {
	//引数がfalseだったら無効
	if(not on) {
		nowMouseClick = false;
		return false;
	}

	//マウス座標取得
	int x = 0;int y=0;
	GetMousePoint(&x,&y);

	//当たり判定
	Rect rec = {(float)x,(float)y,5,5 };
	nowMouseClick = SquareCollision(myCollider, rec);
	
	return nowMouseClick;
}