
#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"
#include <vector>
#include "MapChipField.h"
#include "CameraController.h"
#include "Enemy.h"
#include "DeathParticles.h"
#include "Fade.h"

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

    // デスフラグのgetter
    bool IsFinished() const { return finished_; }

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
    // 3Dモデル 敵
    KamataEngine::Model* modelEnemy_ = nullptr;

    // ブロック
    std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

    // デバッグカメラ有効
    bool isDebugCameraActive_ = false;

    // デバッグカメラ
    KamataEngine::DebugCamera* debugCamera_ = nullptr;

    // キー入力
    KamataEngine::Input* input_ = nullptr;

    // 3Dモデル スカイドーム
    KamataEngine::Model* modelSkydome_ = nullptr;

    // スカイドーム
    Skydome* skydome_ = nullptr;

    // マップチップフィールド
    MapChipField* mapChipField_;

    // 表示ブロックの生成
    void GenerateBlocks();

    // カメラコントローラ
    CameraController* cameraController_;

    // 敵
    //Enemy* enemy_ = nullptr;
    std::list<Enemy*> enemies_;

    // 全ての当たり判定を行う
    void CheckAllCollisions();

    // 3Dモデル デスパーティクル
    KamataEngine::Model* modelDeathParticles_ = nullptr;
    // デスパーティクル
    DeathParticles* deathParticles_ = nullptr;



    // シーンのフェーズ
    enum class Phase {
        kFadeIn,  // フェードイン
        kPlay,    // ゲームプレイ
        kDeath,   // デス演出
        kFadeOut, // フェードアウト
    };


    // ゲームの現在フェーズ（変数）
    Phase phase_;

    // フェーズの切り替え
    void ChangePhase();

    // 終了フラグ
    bool finished_ = false;

    // フェード
    Fade* fade_ = nullptr;
};

