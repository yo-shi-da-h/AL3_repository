#include "WorldTransform.h"
#include "Model.h"

class Player{

	public:
		///<summary>
		///初期化
		///</summary>
		void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
		///<summary>
		///更新
		/// <summary>
		void Update();
		///<summary>
		///描画
		///<summary>
		void Draw();
private:
	WorldTransform worldTransform_;
	Model* model_=nullptr;
	uint32_t textureHandle_ =0u;
	ViewProjection* viewProjection_ = nullptr;
	
};