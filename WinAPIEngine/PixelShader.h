#pragma once
#include "Bindable.h"

class PixelShader : public Bindable {
public:
	PixelShader(GraphicsD3D& gfx, const std::wstring& path);
	void Bind(GraphicsD3D& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};