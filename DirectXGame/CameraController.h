
#pragma once
#include "ViewProjection.h"
#include "Vector3.h"

class Player;
class CameraController
{
	public:
		void Initialize();

		void Update();

		void SetTraget(Player* target) {target_ = target;}

		void Reaet();

private:
	ViewProjection viewProjection_;
	Player* target_ = nullptr;
	Vector3 targetOffset_ = {0,0,-15.0f};
};

