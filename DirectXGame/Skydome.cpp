#include "Skydome.h"

using namespace KamataEngine;

// 初期化
void Skydome::Initialize(Model* model, Camera* camera)
{
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	// 引数の内容をメンバ変数に記録
	camera_ = camera;

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

// 更新
void Skydome::Update()
{
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

// 描画
void Skydome::Draw()
{
	// 3Dモデルを描画
	model_->Draw(worldTransform_, *camera_);
}
