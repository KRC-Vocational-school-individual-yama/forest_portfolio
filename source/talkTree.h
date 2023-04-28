#pragma once
#include"talkObject.h"

class TalkTree :public TalkObject {
public:
	TalkTree(Scene* sc);
	~TalkTree()		override;
	void Init()		override;
	void Update()	override;
private:

};