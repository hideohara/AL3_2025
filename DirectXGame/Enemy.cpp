#include "Enemy.h"

#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;


void Enemy::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position)
{
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	worldTransform_.translation_ = position;

	// 引数の内容をメンバ変数に記録
	camera_ = camera;

	// ワールド変換の初期化
	worldTransform_.Initialize();

	// 初期回転
	worldTransform_.rotation_.y = -std::numbers::pi_v<float> / 2.0f;

	// 速度を設定する
	velocity_ = { -kWalkSpeed, 0, 0 };


	walkTimer_ = 0.0f;

}

// 更新
void Enemy::Update()
{
	// 移動
	worldTransform_.translation_ += velocity_;

	// タイマーを加算
	walkTimer_ += 1.0f / 60.0f;

	// 回転アニメーション
	worldTransform_.rotation_.x = std::sin(walkTimer_*5.0f);

	//アフィン変換行列の作成
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Enemy::Draw()
{
	// 3Dモデルを描画
	model_->Draw(worldTransform_, *camera_);
}

// ワールド座標を取得
Vector3 Enemy::GetWorldPosition()
{

	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

// AABBを取得
AABB Enemy::GetAABB()
{
	Vector3 worldPos = GetWorldPosition();
	AABB aabb;
	aabb.min = { worldPos.x - 1.0f / 2.0f, worldPos.y - 1.0f / 2.0f, worldPos.z - 1.0f / 2.0f };
	aabb.max = { worldPos.x + 1.0f / 2.0f, worldPos.y + 1.0f / 2.0f, worldPos.z + 1.0f / 2.0f };
	return aabb;
}

// 衝突応答
void Enemy::OnCollision(const Player* player) {
	(void)player;
}

