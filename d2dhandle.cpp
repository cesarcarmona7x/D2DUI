#include "stdafx.h"
using namespace D2D1;
D2DHandle::D2DHandle(){
}
D2DHandle::~D2DHandle(){
	cleanD2D();
	cleanD3D();
}
void D2DHandle::cleanD2D(){
}
void D2DHandle::cleanD3D(){
}
bool D2DHandle::InitializeD2D(HWND hwnd,GameSettings& sett){
	HRESULT hr;
    RECT r;
    GetClientRect(hwnd,&r);
	hr=D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED,d2dfactory.GetAddressOf());
    if(hr!=S_OK){
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
        return false;
    }
	hr=DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),(IUnknown**)dwritefactory.GetAddressOf());
    if(hr!=S_OK){
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
        return false;
    }
	D2D1_RENDER_TARGET_PROPERTIES rtp;
	rtp.dpiX=0.0f;
	rtp.dpiY=0.0f;
	rtp.minLevel=D2D1_FEATURE_LEVEL_10;
	rtp.pixelFormat=PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM,D2D1_ALPHA_MODE_PREMULTIPLIED);
	rtp.type=D2D1_RENDER_TARGET_TYPE_HARDWARE;
	rtp.usage=D2D1_RENDER_TARGET_USAGE_NONE;
	DXGI_MODE_DESC modedesc;
	DXGI_RATIONAL rat;
	rat.Denominator = 1;
	rat.Numerator = 30;
	modedesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	modedesc.Width=sett.winwidth;
	modedesc.Height=sett.winheight;
	modedesc.RefreshRate = rat;
	std::stringstream war;
	std::stringstream sar;
	float windowaspectratio=((float)sett.winwidth/(float)sett.winheight);
	war<<boost::format("%.2f") % windowaspectratio;
	windowaspectratio=atof(war.str().c_str());
	float screenaspectratio=((float)sett.screenwidth/(float)sett.screenheight);
	sar<<boost::format("%.2f") % screenaspectratio;
	screenaspectratio=atof(sar.str().c_str());
	if(windowaspectratio==screenaspectratio){
		modedesc.Scaling=DXGI_MODE_SCALING_STRETCHED;
	}
	else{
		modedesc.Scaling=DXGI_MODE_SCALING_CENTERED;
	}
	modedesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	DXGI_SWAP_CHAIN_DESC scdesc;
	ZeroMemory(&scdesc,sizeof(DXGI_SWAP_CHAIN_DESC));
	scdesc.BufferCount=2;
	scdesc.BufferDesc=modedesc;
	scdesc.BufferUsage=DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scdesc.OutputWindow=hwnd;
	scdesc.SwapEffect=DXGI_SWAP_EFFECT_DISCARD;
	scdesc.Flags=DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scdesc.SampleDesc.Count=1;
	scdesc.SampleDesc.Quality=0;
	scdesc.Windowed=!sett.fullscreen;
	D3D10_FEATURE_LEVEL1 levels[]={D3D10_FEATURE_LEVEL_9_3};
	hr=D3D10CreateDevice1(NULL,D3D10_DRIVER_TYPE_HARDWARE,NULL,D3D10_CREATE_DEVICE_BGRA_SUPPORT,levels[0],D3D10_1_SDK_VERSION,d3ddevice.GetAddressOf());
	if(hr!=S_OK){
		MessageBoxA(NULL,"Error creating D3D10_1 device","Error",MB_OK|MB_ICONERROR);
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
		return false;
	}
	hr=d3ddevice.As(&dxgidevice);
	if(hr!=S_OK){
		MessageBoxA(NULL,"Error getting DXGI device","Error",MB_OK|MB_ICONERROR);
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
		return false;
	}
	hr=dxgidevice->GetAdapter(dxgiadapter.GetAddressOf());
	if(hr!=S_OK){
		MessageBoxA(NULL,"Error getting DXGI adapter","Error",MB_OK|MB_ICONERROR);
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
		return false;
	}
	hr=dxgiadapter->GetParent(IID_PPV_ARGS(dxgifactory.GetAddressOf()));
	if(hr!=S_OK){
		MessageBoxA(NULL,"Error getting DXGI factory","Error",MB_OK|MB_ICONERROR);
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
		return false;
	}
	hr=dxgifactory->CreateSwapChain(d3ddevice.Get(),&scdesc,swapchain.GetAddressOf());
	if(hr!=S_OK){
		MessageBoxA(NULL,"Error creating DXGI swap chain","Error",MB_OK|MB_ICONERROR);
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		const TCHAR* description=err.Description();
		std::wstring errordesu=error;
		errordesu+=L": ";
		errordesu+=description;
		MessageBox(NULL,errordesu.c_str(),L"Error",MB_OK|MB_ICONERROR);
		return false;
	}
	hr=swapchain->GetBuffer(0,IID_PPV_ARGS(surface.GetAddressOf()));
	if(hr!=S_OK){
		MessageBoxA(NULL,"Error getting DXGI surface","Error",MB_OK|MB_ICONERROR);
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
		return false;
	}
	hr=d2dfactory->CreateDxgiSurfaceRenderTarget(surface.Get(),rtp,target.GetAddressOf());
	if(hr!=S_OK){
		MessageBoxA(NULL,"Error creating render target","Error",MB_OK|MB_ICONERROR);
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
		return false;
	}
	target->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
	target->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
	hr=d2dfactory->CreateDrawingStateBlock(targetstate.GetAddressOf());
	CoCreateInstance(CLSID_WICImagingFactory,NULL,CLSCTX_INPROC_SERVER,IID_IWICImagingFactory,(LPVOID*)imgfactory.GetAddressOf());
	dwritefactory->CreateTextFormat(L"Microsoft Sans Serif",NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,12.0f,L"en-us",textformat.GetAddressOf());
    return true;
}
