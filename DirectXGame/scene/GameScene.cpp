
#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "matrix.h"
#include "MapChipField.h"




GameScene::GameScene() {}

GameScene::~GameScene() {
	
	delete debugCamera_;

	delete modelBlock_;
	
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			delete worldTransformBlock;
		}
		

	}
	worldTransformBlocks_.clear();

	//delete modelSkydome_;

	delete mapChipField_;

	delete model_;

	delete player_;
	
}

void GameScene::Initialize() {

	debugCamera_ = new DebugCamera(1280, 720);


	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	

	viewProjection_.Initialize();
	worldTransform_.Initialize();
	modelBlock_ = Model::Create();
	

	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/map.csv");

	GenerateBlock();
	player_=new Player;
	playermodel_ = Model::CreateFromOBJ("player",true);
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1,18);
	model_ = Model::Create();
    player_->Initialize(playermodel_, &viewProjection_,playerPosition);
	
}

void GameScene::Update() {
	debugCamera_->Update();
	player_->Update();

	#ifdef  _DEBUG

	if (input_->TriggerKey(DIK_SPACE)) {
		debugCameraActive_ = !debugCameraActive_;
	}

#endif //  _DEBUG


	if (debugCameraActive_) {

		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
	}


	//skydome_->Update();

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			worldTransformBlock->UpdateMatrix();
		}
	}
	
}

void GameScene::Draw() {
	

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	player_->Draw();
	/// </summary>

	//skydome_->Draw();

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine){
			if (!worldTransformBlock)
				continue;
			modelBlock_->Draw(*worldTransformBlock, viewProjection_);
			
	}
}
	
	
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::GenerateBlock()
{
    uint32_t kNumBlockVirtical = mapChipField_->GetNumBlockVirtical();
    uint32_t kNumBlockHorizonal = mapChipField_->GetNumBlockHorizontal();
	

	worldTransformBlocks_.resize(kNumBlockHorizonal);

	for (uint32_t i = 0; i < kNumBlockVirtical; i++) {
		worldTransformBlocks_[i].resize(kNumBlockHorizonal);
	}

	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(kNumBlockHorizonal);
		for (uint32_t j = 0; j < kNumBlockHorizonal; ++j) {
			
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j,i);
			}
				
			
		}
	}
}




