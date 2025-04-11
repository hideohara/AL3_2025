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
    void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera);
    //void Initialize(KamataEngine::Model* model, uint32_t textureHandle);

    // 更新
    void Update();

    // 描画
    void Draw();

private:
    // ワールド変換データ
    KamataEngine::WorldTransform worldTransform_;
    // モデル
    KamataEngine::Model* model_ = nullptr;
    // テクスチャハンドル
    uint32_t textureHandle_ = 0u;
    // カメラ
    KamataEngine::Camera* camera_ = nullptr;

};

