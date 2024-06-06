#include "Player.h"
#include <cassert>
#include <numbers>
#include "MapChipField.h"


void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	//NULLチェック
	assert(model);

	worldTransform_.Initialize();

	//引数の内容をメンバ変数に記録
	model_ = model;
	
	viewProjection_ = viewProjection;

	worldTransform_.translation_ = position;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> /2.0f;

	//Vector3 playerPosition = mapChipFiled->GetMapChipPositionByIndex()

}

/*void Player::Update()
{
	worldTransform_.TransferMatrix();
}

void Player::Draw()
{
	model_->Draw(worldTransform_,*viewProjection_,textureHandle_);
}*/


