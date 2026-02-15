#include "Game_Object.h"
#include"../draw_resource/ShapeContainer.h"
#include<cmath>

namespace {
	struct ConstBufferData
	{
		DirectX::XMMATRIX world_{};
		DirectX::XMFLOAT4 color_{};
	};
}

namespace game {
	void Game_Object::initialize()noexcept
	{
		createDrawBuffer();
	}

	void Game_Object::setDrawCommand(const command_list& commandlist,UINT slot)noexcept
	{
		object::setDrawCommand(commandlist, slot);
		ShapeContainer::instance().draw(commandlist, shapeId_);
	}

	void Game_Object::createDrawBuffer() noexcept {
		if (!constantBuffer.create(sizeof(ConstBufferData))) {
			assert(false && "GameObject コンスタントバッファの作成に失敗しました");
		}
	}
	void Gaem_Object::updateDrawBuffer() noexcept
	{
		object::updateConstantBuffer(ConstBufferData{ DirectX::XMMatrixTranspose(world_),color_ });
});
	}
}