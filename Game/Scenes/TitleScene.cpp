#include "TitleScene.h"
#include "ImGuiManger.h"

TitleScene::~TitleScene()
{
}
void TitleScene::Initialize()
{	
	input = Input::GetInstance();
	engine_ = YTEngine::GetInstance();
	textureManager_ = Texturemanager::GetInstance();

	count = 0;

	texture_ = textureManager_->Load("Resource/title.png");
	title_ = std::make_unique<Sprite>();
	title_->Initialize(texture_);

	title_->position = { 1000,200 };
	title_->size_ = { 20,15 };

	texture2_ = textureManager_->Load("Resource/uvChecker.png");
	title2_ = std::make_unique<Sprite>();
	title2_->Initialize(texture2_);
	
	title2_->position = { 500,200 };
	title2_->size_ = { 20,15 };
}

void TitleScene::Update()
{
	
	ImGui::Begin("SceneManager");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::Text("count %d",count);
	ImGui::End();
	if (input->PushKey(DIK_SPACE)) {
		sceneNum = GAME_SCENE;
		count++;
	}
	
	if (sceneNum < 0) {
		sceneNum = 0;
		
	}
	/*if (count >= 60) {
		sceneNum=GAME_SCENE;
	}*/
}

void TitleScene::Draw()
{
	Transform spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };

	Vector4 spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };

	engine_->SpritePreDraw();

	title_->Draw(spriteUvTransform_, spriteMaterial_);
	title2_->Draw(spriteUvTransform_, spriteMaterial_);
}

void TitleScene::Finalize()
{
}
