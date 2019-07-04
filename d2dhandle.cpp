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
	ID2D1Factory* d2dfact;
    hr=D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED,&d2dfact);
    if(hr!=S_OK){
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
        return false;
    }
	d2dfactory=std::shared_ptr<ID2D1Factory>(d2dfact,[](ID2D1Factory* p){p->Release();});
	IDWriteFactory* dwfact;
	hr=DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),(IUnknown**)&dwfact);
    if(hr!=S_OK){
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
        return false;
    }
	dwritefactory=std::shared_ptr<IDWriteFactory>(dwfact,[](IDWriteFactory* p){p->Release();});
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
	ID3D10Device1* d3ddev;
	hr=D3D10CreateDevice1(NULL,D3D10_DRIVER_TYPE_HARDWARE,NULL,D3D10_CREATE_DEVICE_BGRA_SUPPORT,levels[0],D3D10_1_SDK_VERSION,&d3ddev);
	if(hr!=S_OK){
		MessageBoxA(NULL,"Error creating D3D10_1 device","Error",MB_OK|MB_ICONERROR);
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
		return false;
	}
	d3ddevice=std::shared_ptr<ID3D10Device1>(d3ddev,[](ID3D10Device1* p){p->Release();});
	IDXGIDevice1* dxgidev;
	hr=d3ddevice->QueryInterface(&dxgidev);
	if(hr!=S_OK){
		MessageBoxA(NULL,"Error getting DXGI device","Error",MB_OK|MB_ICONERROR);
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
		return false;
	}
	dxgidevice=std::shared_ptr<IDXGIDevice1>(dxgidev,[](IDXGIDevice1* p){p->Release();});
	IDXGIAdapter* dxgiad;
	hr=dxgidevice->GetAdapter(&dxgiad);
	if(hr!=S_OK){
		MessageBoxA(NULL,"Error getting DXGI adapter","Error",MB_OK|MB_ICONERROR);
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
		return false;
	}
	dxgiadapter=std::shared_ptr<IDXGIAdapter>(dxgiad,[](IDXGIAdapter* p){p->Release();});
	IDXGIFactory* dxgifact;
	hr=dxgiadapter->GetParent(IID_PPV_ARGS(&dxgifact));
	if(hr!=S_OK){
		MessageBoxA(NULL,"Error getting DXGI factory","Error",MB_OK|MB_ICONERROR);
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
		return false;
	}
	dxgifactory=std::shared_ptr<IDXGIFactory>(dxgifact,[](IDXGIFactory* p){p->Release();});
	IDXGISwapChain* dxgisch;
	hr=dxgifactory->CreateSwapChain(d3ddevice.get(),&scdesc,&dxgisch);
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
	swapchain=std::shared_ptr<IDXGISwapChain>(dxgisch,[](IDXGISwapChain* p){
		p->SetFullscreenState(false,NULL);
		p->Release();
	});
	IDXGISurface* sur;
	hr=swapchain->GetBuffer(0,IID_PPV_ARGS(&sur));
	if(hr!=S_OK){
		MessageBoxA(NULL,"Error getting DXGI surface","Error",MB_OK|MB_ICONERROR);
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
		return false;
	}
	surface=std::shared_ptr<IDXGISurface>(sur,[](IDXGISurface*p){p->Release();});
	ID2D1RenderTarget* rt;
	hr=d2dfactory->CreateDxgiSurfaceRenderTarget(surface.get(),rtp,&rt);
	if(hr!=S_OK){
		MessageBoxA(NULL,"Error creating render target","Error",MB_OK|MB_ICONERROR);
		_com_error err(hr);
		const TCHAR* error=err.ErrorMessage();
		MessageBox(NULL,error,L"Error",MB_OK|MB_ICONERROR);
		return false;
	}
	target=std::shared_ptr<ID2D1RenderTarget>(rt,[](ID2D1RenderTarget* p){p->Release();});
	target->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
	target->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
	ID2D1DrawingStateBlock* rtst;
	hr=d2dfactory->CreateDrawingStateBlock(&rtst);
	targetstate=std::shared_ptr<ID2D1DrawingStateBlock>(rtst,[](ID2D1DrawingStateBlock* p){p->Release();});
	IWICImagingFactory* wicif;
	CoCreateInstance(CLSID_WICImagingFactory,NULL,CLSCTX_INPROC_SERVER,IID_IWICImagingFactory,(LPVOID*)&wicif);
	imgfactory=std::shared_ptr<IWICImagingFactory>(wicif,[](IWICImagingFactory* p){p->Release();});
    return true;
}
