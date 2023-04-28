#pragma once
#include"libs/object.h"

class GameMasterAi :public Object {
public:
	GameMasterAi(Scene* sc);
	~GameMasterAi()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;


private:

};