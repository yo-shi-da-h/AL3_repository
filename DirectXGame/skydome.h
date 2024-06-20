#include "WorldTransform.h"
#include <Model.h>

class Skydome {

public:
	void Initialize(Model* model, ViewProjection* viewProjection);
	void Update();
	void Draw();

private:
	WorldTransform worldTransform_;
	Model* skymodel_ = nullptr;
	ViewProjection* viewProjection_;
};