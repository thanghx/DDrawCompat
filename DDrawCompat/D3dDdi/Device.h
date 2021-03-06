#pragma once

#include <map>
#include <set>

#include <d3d.h>
#include <d3dnthal.h>
#include <d3dumddi.h>

#include "D3dDdi/OversizedResource.h"
#include "D3dDdi/RenderTargetResource.h"

namespace D3dDdi
{
	UINT getBytesPerPixel(D3DDDIFORMAT format);

	class Device
	{
	public:
		Device(HANDLE adapter, HANDLE device);

		HRESULT blt(const D3DDDIARG_BLT& data);
		HRESULT clear(const D3DDDIARG_CLEAR& data, UINT numRect, const RECT* rect);
		HRESULT colorFill(const D3DDDIARG_COLORFILL& data);
		HRESULT createResource(D3DDDIARG_CREATERESOURCE& data);
		HRESULT createResource2(D3DDDIARG_CREATERESOURCE2& data);
		HRESULT destroyResource(HANDLE resource);
		HRESULT drawIndexedPrimitive(const D3DDDIARG_DRAWINDEXEDPRIMITIVE& data);
		HRESULT drawIndexedPrimitive2(const D3DDDIARG_DRAWINDEXEDPRIMITIVE2& data,
			UINT indicesSize, const void* indexBuffer, const UINT* flagBuffer);
		HRESULT drawPrimitive(const D3DDDIARG_DRAWPRIMITIVE& data, const UINT* flagBuffer);
		HRESULT drawPrimitive2(const D3DDDIARG_DRAWPRIMITIVE2& data);
		HRESULT drawRectPatch(const D3DDDIARG_DRAWRECTPATCH& data, const D3DDDIRECTPATCH_INFO* info,
			const FLOAT* patch);
		HRESULT drawTriPatch(const D3DDDIARG_DRAWTRIPATCH& data, const D3DDDITRIPATCH_INFO* info,
			const FLOAT* patch);
		HRESULT lock(D3DDDIARG_LOCK& data);
		HRESULT openResource(D3DDDIARG_OPENRESOURCE& data);
		HRESULT present(const D3DDDIARG_PRESENT& data);
		HRESULT present1(D3DDDIARG_PRESENT1& data);
		HRESULT texBlt(const D3DDDIARG_TEXBLT& data);
		HRESULT texBlt1(const D3DDDIARG_TEXBLT1& data);
		HRESULT unlock(const D3DDDIARG_UNLOCK& data);
		HRESULT updateWInfo(const D3DDDIARG_WINFO& data);

		void prepareForRendering(HANDLE resource, UINT subResourceIndex = UINT_MAX);
		void prepareForRendering();

		static void setGdiResourceHandle(HANDLE resource);
		static void setReadOnlyGdiLock(bool enable);

	private:
		template <typename CreateResourceArg, typename CreateResourceFunc>
		HRESULT createOversizedResource(
			CreateResourceArg& data,
			CreateResourceFunc origCreateResource,
			const D3DNTHAL_D3DEXTENDEDCAPS& caps);

		template <typename CreateResourceArg, typename CreateResourceFunc>
		HRESULT createResourceImpl(CreateResourceArg& data, CreateResourceFunc origCreateResource);

		void prepareForRendering(RenderTargetResource& resource, UINT subResourceIndex = UINT_MAX);

		const D3DDDI_DEVICEFUNCS* m_origVtable;
		HANDLE m_adapter;
		HANDLE m_device;
		std::map<HANDLE, OversizedResource> m_oversizedResources;
		std::map<HANDLE, RenderTargetResource> m_renderTargetResources;
		std::map<HANDLE, RenderTargetResource&> m_lockedRenderTargetResources;
		HANDLE m_sharedPrimary;
	};
}
