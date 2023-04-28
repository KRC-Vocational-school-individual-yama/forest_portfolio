#pragma once
#include"libs/object.h"
#include"speechBubble.h"

/// <summary>
/// 木や鳥、花、ネコ等の話すキャラ
/// </summary>
class TalkObject :public Object {
public:
	TalkObject(Scene* sc);
	virtual ~TalkObject()	override;
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Draw()		override;



	//画像での当たり判定 true:当たっている
	virtual bool Collision(Rect p);


	//画像を後から変える
	void SetGraph(std::vector<std::string> pass);//ToDo:とりあえず書いた
	//座標を後から変える　キャラ画像
	void SetPos(float x,float y) { pos = {x,y}; }
	//吹き出し座標 //ToDo:仮　必要なかったら　消す　要参照→//ToDo:SetPosSpeechBubble
	void SetPosSpeechBubble(float x, float y) { speechBubble.SetPos(x, y); }
	//プレイヤーが重なっているか　true：重なっている
	bool GetOnPlayer() { return onPlayer; }

	enum Type { //ToDo: 後でどうするか考える
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
	void FaceToPlayer(Rect p);//プレイヤーの方に向く
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
	bool faceToLeft;//trueが右
	bool isTalked;//一回でも話したら true：1回以上吹き出しをクリック
};