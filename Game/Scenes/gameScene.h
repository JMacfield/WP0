#pragma once
#include "YTEngine.h"
#include "MyMath.h"
#include "triangle.h"
#include "Iscene.h"
#include "Sprite.h"
#include "Sphere.h"
#include "model.h"
#include "worldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"
#include "GlobalVariables.h"
#include "Particle.h"
#include "Input.h"

class GameScene:public Iscene
{
public:
	~GameScene();
	void Initialize()override;
	void Update()override;
	
	void Draw()override;
	void Finalize()override;
private:
	Input* input_;

	YTEngine* blueMoon_;
	DirectXCommon* directXCommon_;
	Sprite* sprite_;
	Texturemanager* textureManager_;

	Vector4 spritedataLeftTop_;
	Vector4 spritedataRightDown_;
	Transform spriteTransform_;
	Vector4 spriteMaterial;
	Transform SpriteuvTransform;
	Vector4 material[2];
	Triangle* triangle_;
	Matrix4x4 worldMatrix_;
	Sphere* sphere_;
	Vector4 sphereMaterial_;
	Matrix4x4 spherematrix_;
	Particle* particle_[2];
	//Particle* particle2_;
	Model* model_[2];
	Vector4 modelMaterial_[2];
	uint32_t uvResourceNum;
	WorldTransform worldTransformtriangle_[2];
	WorldTransform worldTransformModel_;
	ViewProjection viewProjection_;
	Transform particleTransform_;
	Transform particleuvTransform;
	/*Transform particleTransform2_;
	Transform particleuvTransform2;*/
	Emitter emitter_[2];
	//Emitter emitter2_;
	int monsterBallResourceNum;
	int BlackResourceNum;
	bool triangleIsAlive_;
	bool spriteIsAlive_;
	bool sphereIsAlive_;
	bool modelIsAlive_;
	int blendCount_;
	int particleCo[2]; 
	int particleCo2;

	bool Isparticle[2] = { false };
	//bool Isparticle2 = false;
	void Draw2D();
	void Draw3D();
	void ApplyGlobalVariables();
};

