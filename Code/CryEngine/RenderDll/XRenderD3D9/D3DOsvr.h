// Copyright 2001-2016 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once
#ifdef INCLUDE_OSVR_SDK

	#include <CrySystem/VR/IHMDDevice.h>
	#include <CrySystem/VR/IHmdOSVRDevice.h>
	#include <CryRenderer/IStereoRenderer.h>

class CD3D9Renderer;
class CTexture;
namespace CryVR
{
namespace Osvr
{
class CD3DOsvrRenderer : public IHmdRenderer
{
public:

	CD3DOsvrRenderer(IOsvrDevice* pDevice, CD3D9Renderer* pRenderer, CD3DStereoRenderer* pStereoRenderer);
	virtual ~CD3DOsvrRenderer();

	// IHDMRenderer implementation
	virtual bool                      Initialize() override;
	virtual void                      Shutdown() override;
	virtual void                      CalculateBackbufferResolution(int eyeWidth, int eyeHeight, int* pBackbufferWidth, int* pBackbufferHeight) override;
	virtual void                      OnResolutionChanged() override;
	virtual void                      ReleaseBuffers() override;
	virtual void                      PrepareFrame() override;
	virtual void                      SubmitFrame() override;
	virtual void                      RenderSocialScreen() override;
	virtual RenderLayer::CProperties* GetQuadLayerProperties(RenderLayer::EQuadLayers id) override   { return nullptr; }
	virtual RenderLayer::CProperties* GetSceneLayerProperties(RenderLayer::ESceneLayers id) override { return nullptr; }
private:

	static const uint32 EyeCount = 2;

	struct EyeTextures
	{
		TArray<CTexture*> textures;
	};

	CryVR::Osvr::IOsvrDevice* m_pDevice;
	CD3D9Renderer*            m_pRenderer;
	CD3DStereoRenderer*       m_pStereoRenderer;

	uint32                    m_eyeWidth;
	uint32                    m_eyeHeight;

	EyeTextures               m_eyeTextures[EyeCount];

	int                       m_swapSetCount;
	int                       m_currentFrame;

	void CreateTextureSwapSets(uint32 width, uint32 height, uint32 swapSetCount);
	void ReleaseTextureSwapSets();

	void RestoreDeviceStateAfterFrameSubmit();

};
}
}
#endif
