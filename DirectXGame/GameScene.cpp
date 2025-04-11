#include "GameScene.h"

using namespace KamataEngine;

// デストラクタ
GameScene::~GameScene()
{
	delete model_;
}

// 初期化
void GameScene::Initialize()
{
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("uvChecker.png");
	// 3Dモデルの生成
	model_ = Model::Create();
	// カメラの初期化
	camera_.Initialize();
}

// 更新
void GameScene::Update()
{
}

// 描画
void GameScene::Draw()
{
}
