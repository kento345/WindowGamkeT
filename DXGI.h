#pragma once

#include<d3d12.h>
#include<dxgi1_4.h>
#include<wrl/client.h>

class DXGI final
{
public:
	DXGI() = default;
	~DXGI() = default;

	bool setDisplayAdapter()noexcept;
};

