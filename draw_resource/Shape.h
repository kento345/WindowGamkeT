#pragma once

#include"../directx/Device.h"
#include"../directx/CommandList.h"
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

	bool create() noexcept;

	void draw(const CommandList& commandList)noexcept;

protected:

	virtual bool createVertexBuffer()noexcept = 0;

	virtual bool createIndexBuffer()noexcept = 0;

protected:
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer_{};
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuffer_{};
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};
	D3D12_PRIMITIVE_TOPOLOGY topology_{};
	UINT indexCount_{};
};

