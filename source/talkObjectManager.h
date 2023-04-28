#pragma once
#include"libs/object.h"
class TalkObject;

/// <summary>
/// TalkObject�̂܂Ƃߖ�
/// </summary>
class TalkObjectManager :public Object {
public:
	TalkObjectManager(Scene*sc);
	~TalkObjectManager()		override;
	void Init()					override;
	void Update()				override;
	void Draw()					override;


	enum Type {
		non=-1
		,player
		,tree
		,cat
		,max
	};

	//�d�Ȃ��Ă��邩 �����蔻��
	bool OnCollision(Rect player);
	//Scene�N���X�ɂ����Ɠ���
	template<class C>
	C* Invoke();
private:
	template<class C>
	C* Create();//����


	std::vector<TalkObject*>objectList;
};

template<class C>
inline C* TalkObjectManager::Invoke(){
	for (int i= 0; i < objectList.size(); i++) {
		C* object= dynamic_cast<C*>(objectList.at(i));
		if (object != nullptr)
			return object;
	}

	return nullptr;
}
