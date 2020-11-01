#include "InputLayout.h"

InputLayout::InputLayout(GraphicsD3D& gfx,
						 const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
						 ID3DBlob* pVertexShaderBytecode) {
	GetDevice(gfx)->CreateInputLayout(
		layout.data(), (UINT)layout.size(),
		pVertexShaderBytecode->GetBufferPointer(),
		pVertexShaderBytecode->GetBufferSize(),
		&pInputLayout
	);
}

void InputLayout::Bind(GraphicsD3D& gfx) noexcept {
	GetContext(gfx)->IASetInputLayout(pInputLayout.Get());
}
