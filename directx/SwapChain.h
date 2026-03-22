#pragma once

#include"CommandQueue.h"

class SwapChain
{
public:
	SwapChain() = default;
	~SwapChain() = default;

	bool creatre(const CommandQueue& commandQueue)noexcept;

	IDXGISwapChain3* get()const noexcept;

	const DXGI_SWAP_CHAIN_DESC1& getDesc()const noexcept;

private:
	Microsoft::WRL::ComPtr<IDXGISwapChain3> swapChain_{};
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
};

