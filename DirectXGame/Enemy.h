#pragma once

#include "KamataEngine.h"
#include "MyMath.h"

class Player;

// 敵
class Enemy
{
public:
    void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

    // 更新
    void Update();

    // 描画
    void Draw();

    // ワールド座標を取得
    KamataEngine::Vector3 GetWorldPosition();

    // AABBを取得
    AABB GetAABB();

    // 衝突応答
    void OnCollision(const Player* player);


private:
    // ワールド変換データ
    KamataEngine::WorldTransform worldTransform_;
    // モデル
    KamataEngine::Model* model_ = nullptr;
    // カメラ
    KamataEngine::Camera* camera_ = nullptr;

    // 歩行の速さ
    static inline const float kWalkSpeed = 0.01f;

    // 速度
    KamataEngine::Vector3 velocity_ = {};


    // 最初の角度[度]
    //static inline const float kWalkMotionAngleStart = 0;
    // 最後の角度[度]
    //static inline const float kWalkMotionAngleEnd = 30;
    // アニメーションの周期となる時間[秒]
    //static inline const float kWalkMotionTime = 100;

    // 経過時間
    float walkTimer_ = 0.0f;



};

