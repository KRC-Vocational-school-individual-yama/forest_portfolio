#pragma once
#include"libs/object.h"
class OneCharacterSpacing;

/// <summary>
/// メッセージウィンドウ　
/// 普段は見えない
/// テキストを送って見えるようにする
/// 終わったら　最後のクリックで見えなくなるor次のウィンドウ表示
/// </summary>
class MessegeWindow :public Object {
public:
	MessegeWindow(Scene* sc);
	~MessegeWindow()	override;
	void Init()			override;
	void Update()		override;
	void Draw()			override;

	void DispGraph(int img,float x,float y,float sx,float sy);//ToDo:これは共通化させる
	void SetDisp(bool flag = false) { myDisp = flag; }


	enum Type { //ToDo: 後でどうするか考える
		non=-1
		,player
		, tree
		, cat
		,flower
		,max
	};
	struct Text {
		std::string title="";//名前など
		std::string text;//本文
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
	int hFont;//ToDo:仮 後にメッセージ専用Stringを作るなら消える
	int hImageWindow;
	bool myDisp;
	bool mouseKeyStop;//最初から全文表示しないための役割も持つ
};