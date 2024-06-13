#include "WorldTransform.h"
#include "Model.h"
#include "MapChipField.h"

class Player{

public:
		static inline const float kAcceleration = 1.0f;
		static inline const float kAttenuation = 1.0f;
		static inline const float kLimitRunSpeed = 3.0f;
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

		Vector3 velocity_ = {};
private:
	WorldTransform worldTransform_;
	Model* model_= nullptr;
	uint32_t textureHandle_ =0u;
	ViewProjection* viewProjection_ = nullptr;
	Player* player_ = nullptr;
	
};

