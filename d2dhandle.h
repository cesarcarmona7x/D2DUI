 #ifndef D2DHANDLE_H_INCLUDED
#define D2DHANDLE_H_INCLUDED
#include "stdafx.h"
class D2DHandle{
public:
    D2DHandle();
    ~D2DHandle();
	bool InitializeD2D(HWND hwnd,GameSettings& sett);
	ComPtr<IWICImagingFactory> imgfactory;
	ComPtr<IWICBitmapDecoder> bmpdecoder;
	ComPtr<ID2D1Multithread> multithread;
	ComPtr<IWICBitmap> wicbitmap;
	ComPtr<ID2D1BitmapBrush> bmpbrush;
	ComPtr<IWICBitmapFrameDecode> bmpframedecoder;
	ComPtr<IWICFormatConverter> formatconverter;
	ComPtr<ID2D1Bitmap> bmp;
	ComPtr<IWICBitmapScaler> bmpscaler;
	ComPtr<ID2D1Factory> d2dfactory;
	ComPtr<IDWriteFactory> dwritefactory;
	ComPtr<IDWriteTextFormat> textformat;
	ComPtr<IDWriteTextLayout> textlayout;
	ComPtr<ID3D10Device1> d3ddevice;
	ComPtr<IDXGIDevice1> dxgidevice;
	ComPtr<IDXGIAdapter> dxgiadapter;
	ComPtr<IDXGIFactory> dxgifactory;
	ComPtr<ID2D1Layer> layer1;
	void cleanD2D();
	void cleanD3D();
	ComPtr<IDXGISwapChain> swapchain;
	ComPtr<IDXGISurface> surface;
	ComPtr<ID2D1RenderTarget> target;
	ComPtr<ID2D1DrawingStateBlock> targetstate;
	ComPtr<ID2D1SolidColorBrush> solidbrush;
	ComPtr<ID2D1LinearGradientBrush> gradientbrush;
	ComPtr<ID2D1GradientStopCollection> gradientcollection;
	void resizeViewport(HWND hwnd,GameSettings settings);
};
#endif // D2DHANDLE_H_INCLUDED
