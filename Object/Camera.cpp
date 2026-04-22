#include "Camera.h"
#include"../window/Input.h"
#include"../Object/GameObjectManager.h"

#include<cmath>


namespace {

	constexpr float eyeMoveSpeed_ = 0.06f;
	constexpr float	 destTargetToView_ = - 5.0f;

	struct ConstBufferData
	{
		DirectX::XMMATRIX view_{};
		DirectX::XMMATRIX projection_{};
	};
}

namespace game {

	void Camera::initialize()noexcept {
		createDrawBuffer();

		position_ = DirectX::XMFLOAT3(0.0f, 1.5f, destTargetToView_);

		target_ = DirectX::XMFLOAT3(0.0f, 0.0f, 10.0f);

		up_ = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

		projection_ = DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XM_PIDIV4,
			1280.0f / 720.0f,
			0.1f,
			100.0f
		);
	}

	void Camera::update()noexcept {

		static float angle = 0.0f;

		//DirectX::XMFLOAT3 pos{};
		if (Input::instance().getKey(VK_LEFT)) {
			angle += eyeMoveSpeed_;
			position_.x = destTargetToView_ * std::sinf(angle);
			//position_.z = destTargetToView_ * std::sinf(angle);
		}
		if (Input::instance().getKey(VK_RIGHT)) {
			angle -= eyeMoveSpeed_;
			position_.x = destTargetToView_ * std::sinf(angle);
			//position_.z = destTargetToView_ * std::cosf(angle);
		}

		view_ = DirectX::XMMatrixLookAtLH(
                DirectX::XMLoadFloat3(&position_),
                DirectX::XMLoadFloat3(&target_),
                DirectX::XMLoadFloat3(&up_));
	}

	void Camera::createDrawBuffer()noexcept {
		if (!constantBuffer_.create(sizeof(ConstBufferData))) {
			assert(false && "カメラ用コンスタントバッファの作成に失敗しました");
		}
	}

	void Camera::updateDrawBuffer()noexcept {
		Object::updateConstantBuffer(ConstBufferData{ DirectX::XMMatrixTranspose(view_),DirectX::XMMatrixTranspose(projection_) });
	}

	DirectX::XMMATRIX XM_CALLCONV Camera::viewMatrix()const noexcept {
		return view_;
	}

	DirectX::XMMATRIX XM_CALLCONV Camera::projection()const noexcept {
		return projection_;
	}
}