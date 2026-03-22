#include "SwapChain.h"
#include"DXGI.h"
#include"../window/window.h"

#include<cassert>

bool SwapChain::creatre(const CommandQueue& commandQueue)noexcept {
	const auto [w, h] = Window::instance().size();

	swapChainDesc_ = {};
	swapChainDesc_.BufferCount = 2;
	swapChainDesc_.Width = w;
	swapChainDesc_.Height = h;
	swapChainDesc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc_.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc_.SampleDesc.Count = 1;

    Microsoft::WRL::ComPtr<IDXGISwapChain1> tempSwapChain{};
    {
        const auto hr = Device::instance().dxgi().factory()->CreateSwapChainForHwnd(
            commandQueue.get(), Window::instance().handle(),
            &swapChainDesc_, nullptr, nullptr, tempSwapChain.GetAddressOf());
        if (FAILED(hr)) {
            assert(false && "スワップチェインの作成に失敗");
            return false;
        }
    }

    // スワップチェインのバージョンをアップグレード
    {
        // 一時的なスワップチェインを IDXGISwapChain3 に変換
        const auto hr = tempSwapChain->QueryInterface(IID_PPV_ARGS(&swapChain_));
        if (FAILED(hr)) {
            assert(false && "スワップチェインのアップグレードに失敗");
            return false;
        }
    }

    return true;
}

IDXGISwapChain3* SwapChain::get()const noexcept {
    if (!swapChain_) {
		assert(false && "スワップチェインが未作成です");
    }
	return swapChain_.Get();
}

const DXGI_SWAP_CHAIN_DESC1& SwapChain::getDesc()const noexcept {
    if (!swapChain_) {
        assert(false && "スワップチェインが未作成です");
    }
    return swapChainDesc_;
}