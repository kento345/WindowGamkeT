#pragma once

#include"Device.h"
#include"Shader.h"
#include"RootSignature.h"

class PiplineStateObject final
{
public:
	PiplineStateObject() = default;
	~PiplineStateObject() = default;
	bool create(const Shader& shader, const RootSignature& rootSignature)noexcept;
	ID3D12PipelineState* get()const noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D12PipelineState> piplineState_{};
};

