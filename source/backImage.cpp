#include "backImage.h"

namespace {
	char* pass = "data/texture/backImg.png";
}

BackImage::BackImage(Scene* sc)
	:Object(sc)
	,pos{0,0}
	,scrollX{0}
	,hImage{-1}
{
}

BackImage::~BackImage(){
	if (hImage > 0)
		DeleteGraph(hImage);
}

void BackImage::Init(){
	hImage= LoadGraph(pass);
	assert(hImage>0);
}

void BackImage::Update(){

	//�X�N���[���ʂ�K�p
	pos.x = pos.x + scrollX;
	pos.x = fmod(pos.x ,SCREEN_WIDTH);
}

void BackImage::Draw(){
	DispGraph(pos);//�`��
	DispGraph(pos.x+SCREEN_WIDTH, pos.y);//�E��
	DispGraph(pos.x-SCREEN_WIDTH, pos.y);//����
}

void BackImage::DispGraph(float x, float y){

	DrawExtendGraph(0+x, 0+y
		, SCREEN_WIDTH+x, SCREEN_HEIGHT+y, hImage, true);

}
