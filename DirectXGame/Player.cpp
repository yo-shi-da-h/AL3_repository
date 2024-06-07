#include "player.h"
#include <cassert>
#include <numbers>
#include <math.h>
#include <string>
#include "Input.h"
#include "Vector3.h"
#define _USE_MATH_DEFINES
#include <assert.h>
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

	//Vector3 playerPosition = mapChipFiled_->GetMapChipPositionByIndex()

}

void Player::Update()
{
	worldTransform_.TransferMatrix();

	//左右移動
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
		//左右加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			acceleration.x += kAcceleration;

		}
		else if(Input::GetInstance()->PushKey(DIK_LEFT))
		{
			acceleration.x -= kAcceleration;
		}
		//加速/減速
		velocity_.x += acceleration.x;
	}
	//移動
	worldTransform_.translation_.x += velocity_.x;
	//行列計算
	worldTransform_.UpdateMatrix();
}

void Player::Draw()
{
	model_->Draw(worldTransform_,*viewProjection_,textureHandle_);
}
