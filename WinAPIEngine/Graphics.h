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




class Graphics : public AbstractGraphics {

	struct coords {
		int x;
		int y;
	};


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

	void drawImageTemp(float angle, float x, float z);

	void drawSubImage(float x, float y, float z, float angle,
					  float subX, float subY,
					  float subWidth, float subHeight);

	void drawSubImage2(float x, float y, float z, float angle,
		float subX, float subY,
		float subWidth, float subHeight);

	void drawImage();

	void initMixColorShaders();
	void initTextureShaders();



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

	//image PS
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pImagePixelShader;
	//image VS
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pImageVertexShader;
	//mesh PS
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pMeshPixelShader;
	//mesh VS
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pMeshVertexShader;


	//image pvs
	std::unique_ptr<class VertexShader> pvs;
	std::unique_ptr<class PixelShader> pps;

	Microsoft::WRL::ComPtr<ID3DBlob> pvsBC;
	//pointer to a vertex shader blob?
	//pointer to index buffer
	//pointer to input layout?
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	//view port
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;


	//mesh
	std::unique_ptr<class VertexShader> pMeshvs;
	std::unique_ptr<class PixelShader> pMeshps;
	Microsoft::WRL::ComPtr<ID3DBlob> pMeshvsBC;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pMeshInputLayout;



	Surface theSurface;

	void buildTexturePointers();

	void buildMeshPointers();

	void setImageShaders();

	void setMeshShaders();

	void buildCharMap();

};