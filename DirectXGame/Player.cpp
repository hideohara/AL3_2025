#include "Player.h"
//#include <cassert>
#include "MyMath.h"

using namespace KamataEngine;

// 初期化
void Player::Initialize(Model* model, uint32_t textureHandle, Camera* camera)
//void Player::Initialize(Model* model, uint32_t textureHandle)
{
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	textureHandle_ = textureHandle;
	model_ = model;

	// 引数の内容をメンバ変数に記録
	camera_ = camera;

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

// 更新
void Player::Update()
{
	//アフィン変換行列の作成
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

// 描画

void Player::Draw()
{
	// 3Dモデルを描画
	model_->Draw(worldTransform_, *camera_);
}
