#pragma once
#include"libs/object.h"
class TalkObject;

/// <summary>
/// TalkObject‚Ì‚Ü‚Æ‚ß–ğ
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

	//d‚È‚Á‚Ä‚¢‚é‚© “–‚½‚è”»’è
	bool OnCollision(Rect player);
	//SceneƒNƒ‰ƒX‚É‚ ‚é‚â‚Â‚Æ“¯‚¶
	template<class C>
	C* Invoke();
private:
	template<class C>
	C* Create();//¶¬


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
