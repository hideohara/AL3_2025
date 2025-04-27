#pragma once

#include "KamataEngine.h"

// 前方宣言
class Player;


class CameraController
{

public:
    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    // setter
    void SetTarget(Player* target) { target_ = target; }

    // Reset
    void Reset();

    // getter
    const KamataEngine::Camera& GetViewProjection() const { return camera_; }

    // 矩形
    struct Rect {
        float left = 0.0f;      // 左端
        float right = 1.0f;     // 右端
        float bottom = 0.0f;    // 下端
        float top = 1.0f;       // 上端
    };
    void SetMovableArea(Rect area) { movableArea_ = area; }

private:
    KamataEngine::Camera camera_;

    Player* target_ = nullptr;

    // 追従対象とカメラの座標の差（オフセット）
    KamataEngine::Vector3 targetOffset_ = { 0, 0, -15.0f };

    // カメラ移動範囲
    Rect movableArea_ = { 0, 100, 0, 100 };

    // カメラの目標座標
    KamataEngine::Vector3 targetPosition_;

    // 座標補間割合
    static inline const float kInterpolationRate = 0.05f;


    // 速度掛け率
    static inline const float kVelocityBias = 30;

    static inline const Rect targetMargin = { -9.0f, 9.0f, -5.0f, 5.0f };








};

