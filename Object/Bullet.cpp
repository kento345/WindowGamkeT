#include "Bullet.h"
#include"Enemy.h"

#include"../draw_resource/ShapeContainer.h"
#include"../draw_resource/QuadPolygon.h"

#include"../Object/GameObjectManager.h"

namespace game {

	void Bullet::initialize()noexcept {
		GameObject::initialize();

		auto quadId = ShapeContainer::instance().create<QuadPolygon>();

		DirectX::XMFLOAT3 parentPos{};
		//if(auto paret = GameObject)
	}
}