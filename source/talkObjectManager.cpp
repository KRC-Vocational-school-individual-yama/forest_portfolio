#include "talkObjectManager.h"
#include"talkObject.h"
#include"talkCat.h"
#include"talkTree.h"
#include"talkPlayer.h"

namespace {

}

TalkObjectManager::TalkObjectManager(Scene* sc)
	:Object(sc)
	,objectList{}
{
	objectList.clear();
}

TalkObjectManager::~TalkObjectManager(){
	for (int i = 0; i < objectList.size(); i++) {
		if (objectList.at(i) == nullptr)continue;
		delete objectList.at(i);
		objectList.at(i) = nullptr;
	}
	objectList.clear();


}

void TalkObjectManager::Init(){
	objectList.resize(Type::max,nullptr);

	//ここのCreateはType順と同じ順で作成
	Create<TalkPlayer>();
	Create<TalkTree>();
	Create<TalkCat>();


	for (int i = 0; i < objectList.size(); i++) {
		if (objectList.at(i) == nullptr)continue;
		objectList.at(i)->Init();
	}
}

void TalkObjectManager::Update(){

	for (int i = 0; i < objectList.size(); i++) {
		if (objectList.at(i) == nullptr)continue;
		objectList.at(i)->Update();
	}

}

void TalkObjectManager::Draw(){
	for (int i = 0; i < objectList.size(); i++) {
		if (objectList.at(i) == nullptr)continue;
		objectList.at(i)->Draw();
	}

}

bool TalkObjectManager::OnCollision(Rect player){
	bool isCollision = false;
	

	for (int i = 0; i < objectList.size(); i++) {
		if ( objectList.at(i) == nullptr)continue;
		isCollision |= objectList.at(i)->Collision(player);
		
		
	}

	return isCollision;
}

template<class C>
inline C* TalkObjectManager::Create(){

	bool pop = true;
	C* object = new C(GetScene());//生成

	//リストに入れる作業
	for (int i = 0; i < objectList.size(); i++) {
		if (objectList.at(i) != nullptr)continue;
		pop = false;
		objectList.at(i) = object;
		return object; 
	}

	//空きがないから追加
	if (pop) {
		objectList.emplace_back(object);
	}

	return  object;
}
