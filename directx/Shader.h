#pragma once

#include"Device.h"

class Shader final
{
public:

	Shader() = default;

	~Shader() = default;

	bool create()noexcept;

	ID3DBlob* vertexShader()const noexcept;

	ID3DBlob* pixelShader()const noexcept;

private:
	Microsoft::WRL::ComPtr<ID3DBlob> vertexShader_{};
	Microsoft::WRL::ComPtr<ID3DBlob> pixelShader_{};
};

