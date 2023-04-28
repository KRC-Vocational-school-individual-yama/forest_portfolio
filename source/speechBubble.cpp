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

	//�摜�̑傫����Ⴄ
	int x = 0; int y = 0;
	GetGraphSize(hImage,&x,&y);
	myCollider.sizeX = x;
	myCollider.sizeY = y;

	//Init
	myCollider.posX = 0;
	myCollider.posY = 0;

}
void SpeechBubble::Update() {

	//�X�N���[���ʂ͊O������

	//�}�E�X�I�[�o�[���t���O�ɓ����
	int x = 0; int y = 0;
	GetMousePoint(&x, &y);
	Rect rec = { (float)x,(float)y,5,5 };
	nowMouseOver= SquareCollision(myCollider, rec);
}
void SpeechBubble::Draw() {
	
	
	//�`��
		int blend = 255;
		
		//�}�E�X���W�擾
		int x = 0; int y = 0;
		GetMousePoint(&x, &y);

		if (not nowMouseOver) {//�}�E�X�������o���ɏd�Ȃ��Ă��Ȃ��Ȃ�
			blend /= 1.2;//������
		}


		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
		Vec2 p = { myCollider.posX,myCollider.posY };
		DrawGraph(p.x, p.y, hImage, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	//__�`��


#ifdef _DEBUG //�����g
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255/3);
	int xSize = myCollider.sizeX+myCollider.posX ; int ySize = myCollider.sizeY+myCollider.posY;
	DrawBox(p.x,p.y,xSize,ySize,0xffffff,nowMouseClick);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#endif
}

bool SpeechBubble::MouseOver(bool on) {
	//������false�������疳��
	if(not on) {
		nowMouseClick = false;
		return false;
	}

	//�}�E�X���W�擾
	int x = 0;int y=0;
	GetMousePoint(&x,&y);

	//�����蔻��
	Rect rec = {(float)x,(float)y,5,5 };
	nowMouseClick = SquareCollision(myCollider, rec);
	
	return nowMouseClick;
}