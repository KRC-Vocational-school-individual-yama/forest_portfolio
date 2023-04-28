#pragma once
#include"libs/object.h"

/// <summary>
/// �w�i
/// </summary>
class BackImage :public Object {
public:
	BackImage(Scene* sc);
	~BackImage()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	void SetScroll(float scrol) { scrollX = scrol; }
	float GetScroll() { return scrollX; }
private:
	struct Pos {
		float  x, y;
	};
	//�w�i���w��̈ʒu�ŕ`��
	void DispGraph(float x,float y);
	void DispGraph(Pos p) { DispGraph(p.x,p.y); }

	Pos pos;
	float scrollX;
	int hImage;
};