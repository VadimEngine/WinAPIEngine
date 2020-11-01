#pragma once
#include "Bindable.h"

class Texture : public Bindable {
public:
	Texture(GraphicsD3D& gfx, const class Surface& s);
	void Bind(GraphicsD3D& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
};
