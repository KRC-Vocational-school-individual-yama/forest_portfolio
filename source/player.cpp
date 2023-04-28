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

	Player::Pos charaPos{627,306};//���csv�ǂݍ��݂ɂ���
	Player::Size charaSize{177,202};//���csv�ǂݍ��݂ɂ���
	float charaSpeed = 100;//���csv�ǂݍ��݂ɂ���
	const float maxJumpCount = 0.5;//�W�����v����
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
		//���E�ړ�
		BackImage* backImagePointer = GetScene()->Invoke<BackImage>();

		if (leftKey) {
			isRight = false;//�E�������Ă��Ȃ�

			
			float scrollNum = charaSpeed * GetDeltaTime();//�X�N���[����

			backImagePointer->SetScroll(scrollNum);//�w�i�ɃX�N���[���ʂ𑗂�
			pos.x = max(0, pos.x - scrollNum);//�ړ��K�p
		}
		if (rightKey) {
			isRight = true;//�E�������Ă���

			
			float scrollNum = charaSpeed * GetDeltaTime();//�X�N���[����

			backImagePointer->SetScroll(-scrollNum);//�w�i�ɃX�N���[���ʂ𑗂�
			pos.x = min(SCREEN_WIDTH - charaSize.x, pos.x + scrollNum);//�ړ��K�p
		}

		//�X�N���[�����Ȃ�
		if (lrKey || anLRKey)
			backImagePointer->SetScroll(0);
	}


	{
		//���Ⴊ��
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



	{//ToDo:�ǂ����̋������ǂ�������

	 //�W�����v
		
		 //�{�^���𒷉����@�܂��́@maxJumpCount�b����
		bool jumpFlag = jumpKey||jumpTimeCount<maxJumpCount; 

		if (jumpFlag){
			if (endJump /*ToDo:�A���W�����v���邩*//*|| vecY==0*/ ) {//�W�����v���I����ā@�n�ʂɒ�������@�A���W�����v?
			isJump = true;
			endJump = false;
			jumpTimeCount = 0;
			}
		}
		else {
			isJump = false;
		
			if(vecY == 0 )//�󒆃W�����v�h�~
				endJump = true;
		
		}

		//�V��
		if (pos.y + vecY < 0) {
			pos.y = 0;
			isJump = false;
		}


		//�R�b�Ԑ�����
		if (jumpTimeCount < maxJumpCount)
			jumpTimeCount += 1.f * GetDeltaTime();

		//�W�����v�K�p
		if (isJump) {
			vecY = -9;
		}

		//�d��  
		vecY += 3.1;
		//�n��
		if (pos.y + vecY > SCREEN_HEIGHT / 2.5) {
			vecY = 0;
			pos.y = SCREEN_HEIGHT / 2.5;
		}

		//�d�͓K�p
		pos.y += vecY;
	}

	{//�؂Ȃǂ̃I�u�W�F�N�g�̓����蔻�� 
		using ToManager = TalkObjectManager;
		if (CheckClass<ToManager>()) {

			//�����蔻������@
			Rect rec = { pos.x,pos.y,charaSize.x,charaSize.y };
			if (not GetScene()->Invoke<ToManager>()->OnCollision(rec)) {

				//�����o����߂� //ToDo:������
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

void Player::DispPlayer(float x,float y){ //�� ������ς�����DebugDisp���ύX����
	//�摜�T�C�Y�𓾂�
	int gSizeX = 0;	int gSizeY=0;
	GetGraphSize(hImage, &gSizeX, &gSizeY);
	
	//�傫���̔���
	Size halfSize{charaSize.x/2.f, charaSize.y/2.f};

	//�|�ꂽ���̒���	ToDo:�v���k �L�����̑����ʒu�ɂ���ĕς�邽��
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

	//�摜�T�C�Y�𓾂�
	int gSizeX = 0;	int gSizeY = 0;
	GetGraphSize(hImage, &gSizeX, &gSizeY);

	//�傫���̔���
	Size halfSize{ charaSize.x / 2.f, charaSize.y / 2.f };

	//�|�ꂽ���̒���	ToDo:�v���k �L�����̑����ʒu�ɂ���ĕς�邽��
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
