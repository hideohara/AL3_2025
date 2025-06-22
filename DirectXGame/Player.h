#pragma once

#include "KamataEngine.h"

class MapChipField;

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


    // マップチップのセッター
    void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

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

    // マップチップによるフィールド
    MapChipField* mapChipField_ = nullptr;


    // キャラクターの当たり判定サイズ
    static inline const float kWidth = 0.8f;
    static inline const float kHeight = 0.8f;

    // マップとの当たり判定情報
    struct CollisionMapInfo {
        bool ceiling = false;
        bool landing = false;
        bool hitWall = false;
        KamataEngine::Vector3 move;
    };

    // ①移動入力
    void InputMove();

    // ②マップ衝突判定
    void CheckMapCollision(CollisionMapInfo& info);
    // マップ衝突判定_上
    void CheckMapCollisionUp(CollisionMapInfo& info);
    // マップ衝突判定_下
    void CheckMapCollisionDown(CollisionMapInfo& info);
    // マップ衝突判定_右
    void CheckMapCollisionRight(CollisionMapInfo& info);
    // マップ衝突判定_左
    void CheckMapCollisionLeft(CollisionMapInfo& info);

    // ③判定結果を反映して移動させる
    void CheckMapMove(const CollisionMapInfo& info);

    // ④天井に接触している場合の処理
    void CheckMapCeiling(const CollisionMapInfo& info);

    // ⑤壁に接触している場合の処理
    void CheckMapWall(const CollisionMapInfo& info);


    // ⑥接地状態の切り替え処理
    void CheckMapLanding(const CollisionMapInfo& info);

    // ⑦旋回制御
    void AnimateTurn();


    // 角
    enum Corner {
        kRightBottom,    // 右下
        kLeftBottom,     // 左下
        kRightTop,       // 右上
        kLeftTop,        // 左上

        kNumCorner       // 要素数

    };

    // 指定した角の座標計算
    KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);

    // 隙間
    static inline const float kBlank = 0.1f;

    // 着地時の速度減衰率
    static inline const float kAttenuationLanding = 0.5f;
    // 微小な数値 
    static inline const float kGroundSearchHeight = 0.1f;
    // 着地時の速度減衰率
    static inline const float kAttenuationWall = 0.1f;






};

