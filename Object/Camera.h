#pragma once

#include"Object.h"
#include<DirectXMath.h>

namespace game {
	class Camera : public Object
	{
	public:

		Camera() = default;

		virtual ~Camera() = default;

	public:
		virtual void initialize()noexcept override;

		virtual void update()noexcept override;

	public:

		virtual void createDrawBuffer()noexcept override;

		virtual void updateDrawBuffer() noexcept override;

	public:

		DirectX::XMMATRIX XM_CALLCONV viewMatrix() const noexcept;

		DirectX::XMMATRIX XM_CALLCONV projection() const noexcept;

	private:
		DirectX::XMMATRIX view_{};
		DirectX::XMMATRIX projection_{};

		DirectX::XMFLOAT3 position_{};
		DirectX::XMFLOAT3 target_{};
		DirectX::XMFLOAT3 up_{};
	};
}



