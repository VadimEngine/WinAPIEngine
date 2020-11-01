#pragma once
#include "Bindable.h"

class IndexBuffer : public Bindable {
public:
	IndexBuffer(GraphicsD3D& gfx, const std::vector<unsigned short>& indices);
	void Bind(GraphicsD3D& gfx) noexcept override;
	UINT GetCount() const noexcept;
protected:
	UINT count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
};