#pragma once
#include"talkObject.h"

/// <summary>
/// TalkObject‚Ì”L
/// </summary>
class TalkCat :public TalkObject {
public:
	TalkCat(Scene* sc);
	~TalkCat()		override;
	void Init()		override;
	void Update()	override;
private:

};