#pragma once
#include "ConstantBuffers.h"
#include "Drawable.h"
#include <DirectXMath.h>

class TransformCbuf : public Bindable {
public:
	TransformCbuf(GraphicsD3D& gfx, const Drawable& parent);
	void Bind(GraphicsD3D& gfx) noexcept override;
private:
	static std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> pVcbuf;
	const Drawable& parent;
};