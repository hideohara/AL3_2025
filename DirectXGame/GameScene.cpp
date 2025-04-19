#include "GameScene.h"
#include "MyMath.h"

using namespace KamataEngine;

// デストラクタ
GameScene::~GameScene()
{
	delete model_;
	delete modelBlock_;

	// 自キャラの解放
	delete player_;

	// ブロック
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
		delete worldTransformBlock;
	}
	worldTransformBlocks_.clear();


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

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_, &camera_);

	// 3Dモデルの生成 ブロック 
	modelBlock_ = Model::CreateFromOBJ("cube");


	// 要素数
	const uint32_t kNumBlockHorizontal = 20;
	// ブロック1個分の横幅
	const float kBlockWidth = 2.0f;
	// 要素数を変更する
	worldTransformBlocks_.resize(kNumBlockHorizontal);

	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockHorizontal; ++i) {

		worldTransformBlocks_[i] = new WorldTransform();
		worldTransformBlocks_[i]->Initialize();
		worldTransformBlocks_[i]->translation_.x = kBlockWidth * i;
		worldTransformBlocks_[i]->translation_.y = 0.0f;
	}


}


// 更新
void GameScene::Update()
{

	// 自キャラの更新
	player_->Update();



	// ブロックの更新
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {

		//アフィン変換行列の作成
		worldTransformBlock->matWorld_ = MakeAffin(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

		// 定数バッファに転送する
		worldTransformBlock->TransferMatrix();
	}



}

// 描画
void GameScene::Draw()
{
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	//ここに3Dモデルインスタンスの描画処理を記述する
	// 
	// 自キャラの描画
	//player_->Draw();

	// ブロックの描画
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
		modelBlock_->Draw(*worldTransformBlock, camera_);
	}

	// 3Dモデル描画後処理
	Model::PostDraw();



}

