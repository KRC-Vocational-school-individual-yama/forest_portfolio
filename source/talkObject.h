#pragma once
#include"libs/object.h"
#include"speechBubble.h"

/// <summary>
/// �؂Ⓓ�A�ԁA�l�R���̘b���L����
/// </summary>
class TalkObject :public Object {
public:
	TalkObject(Scene* sc);
	virtual ~TalkObject()	override;
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Draw()		override;



	//�摜�ł̓����蔻�� true:�������Ă���
	virtual bool Collision(Rect p);


	//�摜���ォ��ς���
	void SetGraph(std::vector<std::string> pass);//ToDo:�Ƃ肠����������
	//���W���ォ��ς���@�L�����摜
	void SetPos(float x,float y) { pos = {x,y}; }
	//�����o�����W //ToDo:���@�K�v�Ȃ�������@�����@�v�Q�Ɓ�//ToDo:SetPosSpeechBubble
	void SetPosSpeechBubble(float x, float y) { speechBubble.SetPos(x, y); }
	//�v���C���[���d�Ȃ��Ă��邩�@true�F�d�Ȃ��Ă���
	bool GetOnPlayer() { return onPlayer; }

	enum Type { //ToDo: ��łǂ����邩�l����
		tree
		,cat
		,bird
		,flower
	};
	struct Size {
		int x, y;
	};
	struct Pos {
		float x; float y;
	};
private:
	void FaceToPlayer(Rect p);//�v���C���[�̕��Ɍ���
	std::vector<int>hImage;

protected:
	enum GraphType{
		normal
		,line
		,debug
		,max
	};

	SpeechBubble speechBubble;
	Pos pos;
	Size mySize;
	std::vector<std::string>mySerif;
	bool onPlayer;
	bool oldMouse;//keyStop
	bool faceToLeft;//true���E
	bool isTalked;//���ł��b������ true�F1��ȏ㐁���o�����N���b�N
};