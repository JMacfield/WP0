#pragma once

#include "Iscene.h"
#include "Input.h"
#include "Texturemanager.h"
#include "YTEngine.h"
#include "Sprite.h"

class TitleScene:public Iscene
{
private:
	int count;
public:
	~TitleScene()override;
	 void Initialize() override;

	 void Update() override;

	 void Draw() override;
	 void Finalize()override;
private:
	Input* input=nullptr;
	YTEngine* engine_;
	Texturemanager* textureManager_;

	uint32_t texture_;
	std::unique_ptr<Sprite> title_;

	uint32_t texture2_;
	std::unique_ptr<Sprite> title2_;
};