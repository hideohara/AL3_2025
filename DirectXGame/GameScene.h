
#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include <vector>


// ゲームシーン
class GameScene
{

public:
    // デストラクタ
    ~GameScene();

    // 初期化
    void Initialize();

    // 更新
    void Update();

    // 描画
    void Draw();

private:
    // テクスチャハンドル
    uint32_t textureHandle_ = 0;
    // 3Dモデル
    KamataEngine::Model* model_ = nullptr;
    // カメラ
    KamataEngine::Camera camera_;

    // 自キャラ
    Player* player_ = nullptr;

    // 3Dモデル ブロック
    KamataEngine::Model* modelBlock_ = nullptr;

    // ブロック
    std::vector<KamataEngine::WorldTransform*> worldTransformBlocks_;



};

