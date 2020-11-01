#pragma once
#include "Bindable.h"

class Sampler : public Bindable {
public:
	Sampler(GraphicsD3D& gfx);
	void Bind(GraphicsD3D& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
};
