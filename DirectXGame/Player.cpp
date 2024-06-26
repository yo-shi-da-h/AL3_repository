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
#include <algorithm>



void Player::Initialize(Model* model,uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position)
{
	//NULLチェック
	assert(model);

	worldTransform_.Initialize();

	worldTransform_.TransferMatrix();
	//引数の内容をメンバ変数に記録
	model_ = model;

	textureHandle_ = textureHandle;
	
	viewProjection_ = viewProjection;

	worldTransform_.translation_ = position;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> /2.0f;

	//Vector3 playerPosition = mapChipFiled_->GetMapChipPositionByIndex()
	model_ = Model::CreateFromOBJ("player" , true);

}

void Player::Update()
{
	worldTransform_.TransferMatrix();

	//左右移動
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
		//左右加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			acceleration.z += kAcceleration;
			if (velocity_.z < 0.0f) {
				velocity_.z *= (1.0f - kAttenuation);
			}
			if (lrDirection_ != LRDirection::kRight) {
				lrDirection_ = LRDirection::kRight;
    				turnFirstRotationY_ = worldTransform_.rotation_.y;
    				turnTimer_ = kTimeturn;

			}
		}
		else if(Input::GetInstance()->PushKey(DIK_LEFT))
		{
			acceleration.z -= kAcceleration;
			if (velocity_.z > 0.0f) {
				velocity_.z *= (1.0f - kAttenuation);
			}
			if (lrDirection_ != LRDirection::kLeft) {
				lrDirection_ = LRDirection::kLeft;
				    turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeturn;
			}
		}
		//加速/減速
		velocity_.z += acceleration.z;
	    //最大速度制限
		velocity_.z = std::clamp(velocity_.z, -kLimitRunSpeed, kLimitRunSpeed);
	}
	else
	{
		velocity_.z *= (1.0f - kAttenuation);
	}
	//移動
	worldTransform_.translation_.z += velocity_.z;
	//行列計算
	worldTransform_.UpdateMatrix();
	{
		float destinationRotationYTable[] = {
			std::numbers::pi_v<float> / 2.0f,
			std::numbers::pi_v<float> * 3.0f /2.0f
		};
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		worldTransform_.rotation_.y = destinationRotationY;
	}

}

void Player::Draw()
{
	model_->Draw(worldTransform_,*viewProjection_,textureHandle_);
}
