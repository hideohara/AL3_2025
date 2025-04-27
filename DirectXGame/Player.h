#pragma once

#include "KamataEngine.h"

//using namespace KamataEngine;

class Player
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="model">モデル</param>
    /// <param name="textureHandle">テクスチャハンドル</param>
    void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

    // 更新
    void Update();

    // 描画
    void Draw();

    const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }


    const KamataEngine::Vector3& GetVelocity() const { return velocity_; }

private:
    // ワールド変換データ
    KamataEngine::WorldTransform worldTransform_;
    // モデル
    KamataEngine::Model* model_ = nullptr;
    // カメラ
    KamataEngine::Camera* camera_ = nullptr;
    // 移動速度
    KamataEngine::Vector3 velocity_ = {};

    // 加速度
    static inline const float kAcceleration = 0.05f;
    // 減速
    static inline const float kAttenuation = 0.05f;
    // 最大速度
    static inline const float kLimitRunSpeed = 0.5f;


    // 左右
    enum class LRDirection {
        kRight,
        kLeft,
    };
    LRDirection lrDirection_ = LRDirection::kRight;

    // 旋回開始時の角度
    float turnFirstRotationY_ = 0.0f;
    // 旋回タイマー
    float turnTimer_ = 0.0f;
    // 旋回時間<秒>
    static inline const float kTimeTurn = 0.3f;


    // 接地状態フラグ
    bool onGround_ = true;

    // 重力加速度（下方向）
    static inline const float kGravityAcceleration = 0.1f;
    // 最大落下速度（下方向）
    static inline const float kLimitFallSpeed = 1.0f;
    // ジャンプ初速（上方向）
    static inline const float kJumpAcceleration = 1.0f;


};

