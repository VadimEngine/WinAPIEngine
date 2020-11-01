#include "PixelShader.h"

PixelShader::PixelShader(GraphicsD3D& gfx, const std::wstring& path) {
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(path.c_str(), &pBlob);
	GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
}

void PixelShader::Bind(GraphicsD3D& gfx) noexcept {
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
