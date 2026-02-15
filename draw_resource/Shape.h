#pragma once

#include"wrl.h"
#include"../directx/device.h"
#include"../directx/command_list.h"
#include<DirectXMath.h>

class Shape
{
public:
	struct ConstBufferData
	{
		DirectX::XMMATRIX world_{};
		DirectX::XMFLOAT4 color_{};
	};
public:

	Shape() = default;
	virtual ~Shape() = default;
	bool create()noexcept;
	void draw(const command_list& commandlist)noexcept;

protected:
	virtual bool createVertexBuffer()noexcept = 0;
	virtual bool createIndexBuffer()noexcept = 0;

protected:
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer_{};      /// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuffer_{};       /// インデックスバッファ
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};
	D3D12_PRIMITIVE_TOPOLOGY topology_{};
	UINT indexCount_{};
};