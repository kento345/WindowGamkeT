#include "GameObject.h"
#include"../draw_resource/ShapeContainer.h"
#include<cmath>

namespace {

	struct ConstantBufferData
	{
		DirectX::XMMATRIX world_{};
		DirectX::XMFLOAT4 color_{};
	};
}

namespace game {
	void GameObject::initialize()noexcept {
		createDrawBuffer();
	} 

	void GameObject::setDrawCommand(const CommandList& commandList, UINT slot)noexcept {
		Object::setDrawCommand(commandList, slot);
		ShapeContainer::instance().draw(commandList, shapeId_);
	}

	void GameObject::createDrawBuffer()noexcept {
		if(!constantBuffer_.create(sizeof(ConstantBufferData))) {
			assert(false && "GameObject コンスタントバッファの生成に失敗しました");
		}
	}

	void GameObject::updateDrawBuffer()noexcept {
		Object::updateConstantBuffer(ConstantBufferData{ DirectX::XMMatrixTranspose(world_),color_});
	}

	void GameObject::setHandle(UINT64 handle)noexcept {
		handle_ = handle;
	}

	UINT64 GameObject::handle()const noexcept {
		return handle_;
	}

	void GameObject::set(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT4 color, UINT64 shapeId)noexcept {
		DirectX::XMMATRIX matScale = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
		DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
		DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
		world_ = matScale * rotation * translation;

		color_ = color;
		shapeId_ = shapeId;

		radius_ = (scale.x + scale.y + scale.z) / (3.0f * 2.0f);
	}

	DirectX::XMMATRIX GameObject::world()const noexcept {
		return world_;
	}

	DirectX::XMFLOAT4 GameObject::color()const noexcept {
		return color_;
	}
}