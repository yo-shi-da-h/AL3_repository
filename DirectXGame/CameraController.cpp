#include "CameraController.h"
#include "player.h"
#include "WorldTransform.h"

void CameraController::Initialize()
{

}

void CameraController::Update()
{
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}

void CameraController::Reaet()
{
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;

	viewProjection_.UpdateMatrix();
}
