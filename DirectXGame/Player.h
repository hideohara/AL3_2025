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
    static inline const float kLimitRunSpeed = 1.0f;


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






};

