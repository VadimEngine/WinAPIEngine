#pragma once
#include "CustomWinHeader.h"

#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <random>
#include "AbstractGraphics.h"




class Graphics : public AbstractGraphics {
	friend class Bindable;
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
	void EndFrame();
	void BeginFrame(float red, float green, float blue) noexcept;
	void DrawTestTriange(float angle, float x, float y);
	void DrawIndexed(UINT count) noexcept;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void EnableImgui() noexcept;
	void DisableImgui() noexcept;
	bool IsImguiEnabled() const noexcept;
	void SetCamera(DirectX::FXMMATRIX cam) noexcept;
	DirectX::XMMATRIX GetCamera() const noexcept;


	void startFrame();
	void drawFrame();

	void drawMesh(class RenderableMesh& theMesh);

	void drawMesh(class RenderableMesh& theMesh, float x, float y, float z, float angle);
	void setCamera(class Camera* camera);
	void drawString(std::string, float x, float y);
	std::string toString();


private:
	bool imguiEnabled = true;
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX camera;


	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;

	Camera* CustomCamera;
	std::vector<unsigned short> theIndices;
	std::vector<float> theVertices;
};