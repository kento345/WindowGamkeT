#pragma once

#include<DirectXMath.h>
#include"object.h"

namespace game {

	class Game_Object : public object
	{
	public:

		Game_Object() = default;
		Game_Object(UINT64 parent) : parent_(parent) {};

		virtual ~Game_Object() = default;
	public:

		virtual void initialize()noexcept override;

		virtual void update()noexcept override;

		virtual void setDrawCommand(const command_list& commandlist, UINT slot)noexcept override;

	public:
		virtual void createDrawBuffer()noexcept override;

		virtual void updateDrawBuffer()noexcept override;

	public:
		virtual void OnHit()noexcept {};

		virtual UINT64 hitTargetTypeId() noexcept { return{}; }

	public:
		void setHandle(UINT64 handle)noexcept ;

		UINT64 handle()const noexcept;

		void set(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT4 color,UINT64 shapeId)noexcept;

		DirectX::XMMATRIX world()const noexcept;

		DirectX::XMFLOAT4 color()const noexcept;

		float radius() noexcept { return radius_; };

	protected:
		DirectX::XMMATRIX world_ = DirectX::XMMatrixIdentity();
		DirectX::XMFLOAT4 color_ = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		UINT64 shapeId_{};
		UINT64 handle_{};
		UINT64 parent_{};
		float radius_{};
	};

}


