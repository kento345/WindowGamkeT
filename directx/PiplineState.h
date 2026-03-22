#pragma once

#include"Device.h"
#include"Shader.h"
#include"RootSignature.h"

class PiplineState final
{
public:
	PiplineState() = default;
	~PiplineState() = default;
	bool create(const Shader& shader, const RootSignature& rootSignature)noexcept;
	ID3D12PipelineState* get()const noexcept;
};

