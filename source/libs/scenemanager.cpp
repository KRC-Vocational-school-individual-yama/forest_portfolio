#include"scenemanager.h"

#include"scenechanger.h"
#include"../titleobject.h"
#include"deltaTime.h"

namespace {
	std::string scene		;//���݃V�[����
	std::string nextScene	;//���̃V�[����
	
	SceneChanger* changer	;//�V�[���؂�ւ�

	Scene* game				;//���݂̃V�[��
	Scene* commonGame		;//�ۑ��p�V�[��

	int frameCount			;//�J�E���^�[
	DeltaTime* time;
}

namespace SceneManager {

	void Init() {
		changer		= new SceneChanger();
		game		= nullptr;
		commonGame	= new Scene();
		scene		= "";
		frameCount	= 0;
		time = new DeltaTime();
#ifdef _DEBUG
		nextScene	= "boot";
#else 
		nextScene	= "Title";
#endif 
	}

	void Update() {
		frameCount++;

		//�V�[���̓���ւ�
		if (nextScene != scene) {
			if(game!=nullptr)
			delete game;
			game = dynamic_cast<Scene*>(changer->Changer(nextScene));
			scene = nextScene;
		}

		//���ꂼ��̍X�V
		game->Update();
		commonGame->Update();
		time->Update();
	}

	void Draw() {
		game->Draw();
		commonGame->Draw();
	}

	void Delete() {
		delete game;
		delete changer;
		delete commonGame;
		delete time;
	}



	void SceneChange(std::string sceneName){
		nextScene = sceneName;
	}

	int GetFrame() {
		return frameCount;
	}

	bool GameEnd() {
		if (scene == "Title") {
			TitleObject* titleObject= game->Invoke<TitleObject>();
			if (titleObject == nullptr)
				return false;

			if (titleObject->EndKeyInput())
				return true;
		}
		return false;
	}

	Scene* GetCommonScene() {
		return commonGame;
	}

	float GetDeltaTime() {
		return time->GetDeltTime();
	}
}