#pragma once
#include"talkObject.h"

class TalkPlayer :public TalkObject {
public:
	TalkPlayer(Scene* sc);
	~TalkPlayer()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;//TalkObject::Draw();‚Í‚µ‚È‚¢

private:

};