#include "ViewProjection.h"

#pragma once
class CameraController
{
	public:
		void Initialize();

		void Update();

		void SetTraget(Player* traget) {traget_ = traget;}

private:
	ViewProjection viewProjection_;
	Player* traget_ = nullptr;
};
class Player;

