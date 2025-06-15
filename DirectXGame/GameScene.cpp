#include "GameScene.h"
#include "MyMath.h"


using namespace KamataEngine;

// デストラクタ
GameScene::~GameScene()
{
	// モデル
	delete model_;
	delete modelBlock_;
	delete modelSkydome_;
	delete modelEnemy_;
	delete modelDeathParticles_;

	// ブロック
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}

	worldTransformBlocks_.clear();

	// クラス
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
	delete player_;
	delete skydome_;
	delete debugCamera_;
	delete mapChipField_;
	delete cameraController_;
	delete deathParticles_;
}

// 初期化
void GameScene::Initialize()
{
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("uvChecker.png");
	// 3Dモデルの生成
	//model_ = Model::Create();
	model_ = Model::CreateFromOBJ("player");
	modelBlock_ = Model::CreateFromOBJ("block");
	modelEnemy_ = Model::CreateFromOBJ("enemy");
	modelDeathParticles_ = Model::CreateFromOBJ("deathParticle");

	// カメラの初期化
	camera_.Initialize();




	// マップチップフィールドの生成
	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
	// 表示ブロックの生成
	GenerateBlocks();

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	// 座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(3, 17);
	player_->Initialize(model_, &camera_, playerPosition);
	player_->SetMapChipField(mapChipField_);

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// キー入力の初期化
	input_ = Input::GetInstance();

	// 3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	// スカイドームの生成
	skydome_ = new Skydome();
	// スカイドームの初期化
	skydome_->Initialize(modelSkydome_, &camera_);

	// カメラコントローラの生成
	cameraController_ = new CameraController();
	cameraController_->Initialize();
	cameraController_->SetTarget(player_);
	cameraController_->Reset();

	CameraController::Rect cameraArea = { 12.0f, 100 - 12.0f, 6.0f, 6.0f };
	cameraController_->SetMovableArea(cameraArea);

	// 敵
	//enemy_ = new Enemy();
	//Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(8, 17);
	//enemy_->Initialize(modelEnemy_, &camera_, enemyPosition);

	for (int32_t i = 0; i < 3; ++i) {
		Enemy* newEnemy = new Enemy();
		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(10+i, 15+i);
		newEnemy->Initialize(modelEnemy_, &camera_, enemyPosition);

		enemies_.push_back(newEnemy);
	}

	//// 仮の生成処理。後で消す。
	//deathParticles_ = new DeathParticles;
	//deathParticles_->Initialize(modelDeathParticles_, &camera_, mapChipField_->GetMapChipPositionByIndex(3, 16));

	// ゲームプレイフェーズから開始
	phase_ = Phase::kPlay;
}


// 更新
void GameScene::Update()
{
	switch (phase_) {
	case Phase::kPlay:
		// ゲームプレイフェーズの処理
		// 自キャラの更新
		player_->Update();

		// スカイドームの更新
		skydome_->Update();

		// 敵
		for (Enemy* enemy : enemies_) {
			enemy->Update();
		}

		// デバッグカメラの更新
		//debugCamera_->Update();

		// カメラコントローラ
		cameraController_->Update();

#ifdef _DEBUG
		if (input_->TriggerKey(DIK_0)) {
			//デバッグカメラ有効フラグをトグル
			isDebugCameraActive_ = !isDebugCameraActive_;
		}
#endif

		// カメラの処理
		if (isDebugCameraActive_) {
			// デバッグカメラの更新
			debugCamera_->Update();
			camera_.matView = debugCamera_->GetCamera().matView;
			camera_.matProjection = debugCamera_->GetCamera().matProjection;
			// ビュープロジェクション行列の転送
			camera_.TransferMatrix();
		}
		else {
			camera_.matView = cameraController_->GetViewProjection().matView;
			camera_.matProjection = cameraController_->GetViewProjection().matProjection;
			// ビュープロジェクション行列の転送
			camera_.TransferMatrix();
		}


		// ブロックの更新
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;

				//アフィン変換行列の作成
				worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
				// 定数バッファに転送する
				worldTransformBlock->TransferMatrix();

				// 行列を計算・転送する
				//UpdateMatrix(*worldTransformBlock);
			}
		}

		// 全ての当たり判定を行う
		CheckAllCollisions();


		if (player_->IsDead()==true) {
			// 死亡演出フェーズに切り替え
			phase_ = Phase::kDeath;
			// 自キャラの座標を取得
			const Vector3& deathParticlesPosition = player_->GetWorldPosition();
			deathParticles_ = new DeathParticles;
			deathParticles_->Initialize(modelDeathParticles_, &camera_, deathParticlesPosition);
		}



		break;

	case Phase::kDeath:
		// デス演出フェーズの処理

		// スカイドームの更新
		skydome_->Update();

		// デスパーティクルの更新
		deathParticles_->Update();

		// 敵
		for (Enemy* enemy : enemies_) {
			enemy->Update();
		}

		// カメラコントローラ
		cameraController_->Update();

#ifdef _DEBUG
		if (input_->TriggerKey(DIK_0)) {
			//デバッグカメラ有効フラグをトグル
			isDebugCameraActive_ = !isDebugCameraActive_;
		}
#endif

		// カメラの処理
		if (isDebugCameraActive_) {
			// デバッグカメラの更新
			debugCamera_->Update();
			camera_.matView = debugCamera_->GetCamera().matView;
			camera_.matProjection = debugCamera_->GetCamera().matProjection;
			// ビュープロジェクション行列の転送
			camera_.TransferMatrix();
		}
		else {
			camera_.matView = cameraController_->GetViewProjection().matView;
			camera_.matProjection = cameraController_->GetViewProjection().matProjection;
			// ビュープロジェクション行列の転送
			camera_.TransferMatrix();
		}


		// ブロックの更新
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;

				//アフィン変換行列の作成
				worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
				// 定数バッファに転送する
				worldTransformBlock->TransferMatrix();
			}
		}


		if (deathParticles_ && deathParticles_->IsFinished()) {
			finished_ = true;
		}



		break;
	}

	
if (deathParticles_ && deathParticles_->IsFinished()) {
    finished_ = true;
}



}

// 描画
void GameScene::Draw()
{
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	//ここに3Dモデルインスタンスの描画処理を記述する
	// 
	// 自キャラの描画
	player_->Draw();

	// スカイドームの描画
	skydome_->Draw();

	// デスパーティクルの描画
	if (deathParticles_) {
		deathParticles_->Draw();
	}

	// 敵
	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	}

	// ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			modelBlock_->Draw(*worldTransformBlock, camera_);
		}
	}

	// 3Dモデル描画後処理
	Model::PostDraw();

}

// 表示ブロックの生成
void GameScene::GenerateBlocks()
{
	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	// 要素数を変更する
	// 列数を設定（縦方向のブロック数）
	worldTransformBlocks_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

}

// 全ての当たり判定を行う
void GameScene::CheckAllCollisions()
{

	{
		// 判定対象1と2の座標
		AABB aabb1, aabb2;

		// 自キャラの座標
		aabb1 = player_->GetAABB();

		// 自キャラと敵弾全ての当たり判定
		for (Enemy* enemy : enemies_) {
			// 敵弾の座標
			aabb2 = enemy->GetAABB();

			// AABB同士の交差判定
			if (IsCollision(aabb1, aabb2)) {
				//衝突応答
				// 自キャラの衝突時コールバックを呼び出す
				player_->OnCollision(enemy);
				// 敵弾の衝突時コールバックを呼び出す
				enemy->OnCollision(player_);
			}
		}
	}


}

// フェーズの切り替え
void GameScene::ChangePhase()
{
}

