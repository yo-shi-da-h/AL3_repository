#include "GameScene.h"
#include "WorldTransform.h"
#include "Vector3.h"
#include "matrix.h"



void WorldTransform::UpdateMatrix() { 
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_); 

	TransferMatrix();
}