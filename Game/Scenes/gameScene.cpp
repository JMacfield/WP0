#include "gameScene.h"


GameScene::~GameScene()
{
	
}

void GameScene::Initialize()
{
	input_ = Input::GetInstance();

	blueMoon_ = YTEngine::GetInstance();

	directXCommon_ = DirectXCommon::GetInstance();

	textureManager_ = Texturemanager::GetInstance();

	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,0.0f,-5.0f };
	uvResourceNum = textureManager_->Load("Resource/uvChecker.png");
	monsterBallResourceNum = textureManager_->Load("Resource/monsterBall.png");
	BlackResourceNum = textureManager_->Load("Resource/circle.png");
	uint32_t reference = textureManager_->Load("Resource/reference.png");

	material[0] = { 1.0f,1.0f,1.0f,1.0f };
	material[1] = { 1.0f,1.0f,1.0f,1.0f };
	spritedataLeftTop_ = { 0.0f,0.0f,0.0f,1.0f };
	spritedataRightDown_ = { 320.0f,180.0f,0.0f,1.0f };
	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	spriteMaterial = { 1.0f,1.0f,1.0f,1.0f };
	sphereMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
	SpriteuvTransform =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	
	sphere_ = new Sphere();
	sphere_->Initialize();

	model_[0] = Model::CreateModelFromObj("Resource", "fence.obj");
	model_[1] = new Model();
	model_[1]->Initialize("Resource", "plane.obj");
	for (int i = 0; i < 2; i++) {
		modelMaterial_[i] = { 1.0f,1.0f,1.0f,1.0f };
	}
	triangle_ = new Triangle();
	triangle_->Initialize();
	for (int i = 0; i < 2; i++) {
		worldTransformtriangle_[i].Initialize();
	}
	worldTransformModel_.Initialize();
	sprite_ = new Sprite();
	sprite_->Initialize(reference);
	sprite_->position = { 1000,200 };
	sprite_->size_ = { 20,15 };

	particle_[0] = new Particle();
	particle_[0]->Initialize(10);

	particle_[1] = new Particle();
	particle_[1]->Initialize(10);

	/*particle2_ = new Particle();
	particle2_->Initialize(10);
	*/
	triangleIsAlive_ = false;
	spriteIsAlive_ = true;
	sphereIsAlive_ = false;
	modelIsAlive_ = true;
	particleCo[0] = 30;
	particleCo[1] = 30;
	//particleCo2 = 30;
	emitter_[0].transform = worldTransformtriangle_[1].GetTransform();
	emitter_[1].transform = worldTransformtriangle_[0].GetTransform();
	particleTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	particleuvTransform =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};

	/*emitter2_.transform = worldTransformtriangle_[0].GetTransform();
	particleTransform2_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	particleuvTransform2 =
	{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};*/

	GlovalVariables* globalVariables{};
	globalVariables = GlovalVariables::GetInstance();
	blendCount_ = 0;
	const char* groupName = "Player";
	GlovalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "Test", 90.0f);
	globalVariables->AddItem(groupName, "Translation", worldTransformtriangle_[0].translation_);
	ApplyGlobalVariables();
	
}

void GameScene::Update()
{
	
	
	if (input_->PushKey(DIK_SPACE)) {
		sceneNum = TITLE_SCENE;
	}

	if (input_->PressKey(DIK_UP)) {
		viewProjection_.translation_.y += 0.01f;
	}

	if (input_->PressKey(DIK_DOWN)) {
		viewProjection_.translation_.y -= 0.01f;
	}
	
	if (input_->PressKey(DIK_LEFT)) {
		viewProjection_.translation_.x -= 0.01f;
	}

	if (input_->PressKey(DIK_RIGHT)) {
		viewProjection_.translation_.x += 0.01f;
	}

	worldTransformtriangle_[0].UpdateMatrix();
	worldTransformtriangle_[1].UpdateMatrix();
	particle_[0]->Update();
	particle_[1]->Update();
	
	worldTransformModel_.UpdateMatrix();
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
	ImGui::Begin("camera");
	ImGui::DragFloat3("translate", &viewProjection_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotate", &viewProjection_.rotation_.x, 0.1f);
	ImGui::DragInt("parcount", &particleCo[0]);
	ImGui::DragInt("par2count", &particleCo[1]);
	ImGui::Checkbox("par", &Isparticle[0]);
	ImGui::Checkbox("par2", &Isparticle[1]);
	ImGui::End();
	ImGui::Begin("object");
	ImGui::DragFloat3("translate", &worldTransformtriangle_[0].translation_.x, 0.1f);
	ImGui::DragFloat3("scale", &worldTransformtriangle_[0].scale_.x, 0.1f);
	ImGui::DragFloat3("rotate", &worldTransformtriangle_[0].rotation_.x, 0.1f);
	ImGui::End();

	if (Isparticle[0]) {
		particle_[0]->AddParticle(emitter_[0], particleCo[0]);
	}

	if (Isparticle[1]) {
		particle_[1]->AddParticle(emitter_[1], particleCo[1]);
	}
	Isparticle[0] = false;
	Isparticle[1] = false;
}


void GameScene::Draw()
{
	
	//3D描画準備
	blueMoon_->ModelPreDraw();
	Draw3D();
	//2D描画準備
	blueMoon_->SpritePreDraw();
	Draw2D();
}

void GameScene::Draw3D()
{
	
	sphere_->Draw(sphereMaterial_, worldTransformtriangle_[0], monsterBallResourceNum, viewProjection_);
	model_[0]->Draw(worldTransformModel_, viewProjection_);

	blueMoon_->PariclePreDraw();
	particle_[0]->Draw(viewProjection_, {1.0f,1.0f,1.0f,1.0f}, BlackResourceNum);
	particle_[1]->Draw(viewProjection_, {1.0f,1.0f,1.0f,1.0f}, uvResourceNum);

	blueMoon_->ModelPreDrawWireFrame();
	
	//sphere_->Draw(sphereMaterial_, worldTransformtriangle_[0], monsterBallResourceNum, viewProjection_);
	
	
}

void GameScene::ApplyGlobalVariables()
{
	GlovalVariables* globalVariables = GlovalVariables::GetInstance();

	const char* groupName = "Player";
	//worldTransformtriangle_[0].translation_ = globalVariables->GetVector3Value(groupName, "Translation");
}

void GameScene::Draw2D() {
	blueMoon_->SetBlendMode(kBlendModeNormal);
	if (spriteIsAlive_ ) {
		sprite_->Draw( SpriteuvTransform, spriteMaterial);
	
	}

}
void GameScene::Finalize()
{
	//delete particle2_;
	delete particle_[0];
	delete particle_[1];
	delete sphere_;
	delete  sprite_;
	delete triangle_;
	for (int i = 0; i < 2; i++) {
		delete model_[i];

	}
	
}

