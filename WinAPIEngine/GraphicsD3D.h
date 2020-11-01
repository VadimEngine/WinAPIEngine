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
#include <unordered_map>
#include "Surface.h"


class GraphicsD3D : public AbstractGraphics {
	struct coords {
		int x;
		int y;
	};

	friend class Bindable;

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
	std::vector<unsigned short> imageIndices;
	std::vector<float> imageVertices;

	std::unordered_map<char, coords> charKeyMap;
	class PipelineD3D* imagePipeline;
	class PipelineD3D* meshPipeline;

	Surface theSurface;

public:
	GraphicsD3D(HWND hWnd);
	GraphicsD3D(const GraphicsD3D&) = delete;
	GraphicsD3D& operator=(const GraphicsD3D&) = delete;
	~GraphicsD3D();
	void EndFrame();
	void BeginFrame(float red, float green, float blue) noexcept;
	void DrawIndexed(UINT count) noexcept;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void EnableImgui() noexcept;
	void DisableImgui() noexcept;
	bool IsImguiEnabled() const noexcept;
	void SetCamera(DirectX::FXMMATRIX cam) noexcept;
	DirectX::XMMATRIX GetCamera() const noexcept;

	// Custom functionality
	void startFrame();
	void drawFrame();
	void drawMesh(class RenderableMesh& theMesh);
	void setCamera(class Camera* camera);
	void drawString(std::string, float x, float y);
	std::string toString();
	void drawSubImage(float x, float y, float z, float angle,
					  float subX, float subY,
					  float subWidth, float subHeight);
	void drawImage();
	void buildCharMap();
};