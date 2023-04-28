#pragma once
#include"libs/object.h"
class OneCharacterSpacing;

/// <summary>
/// ���b�Z�[�W�E�B���h�E�@
/// ���i�͌����Ȃ�
/// �e�L�X�g�𑗂��Č�����悤�ɂ���
/// �I�������@�Ō�̃N���b�N�Ō����Ȃ��Ȃ�or���̃E�B���h�E�\��
/// </summary>
class MessegeWindow :public Object {
public:
	MessegeWindow(Scene* sc);
	~MessegeWindow()	override;
	void Init()			override;
	void Update()		override;
	void Draw()			override;

	void DispGraph(int img,float x,float y,float sx,float sy);//ToDo:����͋��ʉ�������
	void SetDisp(bool flag = false) { myDisp = flag; }


	enum Type { //ToDo: ��łǂ����邩�l����
		non=-1
		,player
		, tree
		, cat
		,flower
		,max
	};
	struct Text {
		std::string title="";//���O�Ȃ�
		std::string text;//�{��
		Type type=Type::non;
	};

	void SetText(Text t);
	

	struct Pos {
		Pos(float x,float y):x{x},y{y}
		{}
		float x, y;
	};
	struct Size {
		float x, y;
	};
private:

	OneCharacterSpacing* oneMesse;
	Text messe;
	std::vector<int> hImage;
	Pos pos;
	Size size;
	int hFont;//ToDo:�� ��Ƀ��b�Z�[�W��pString�����Ȃ������
	int hImageWindow;
	bool myDisp;
	bool mouseKeyStop;//�ŏ�����S���\�����Ȃ����߂̖���������
};