 #ifndef D2DHANDLE_H_INCLUDED
#define D2DHANDLE_H_INCLUDED
#include "stdafx.h"
class D2DHandle{
public:
    D2DHandle();
    ~D2DHandle();
	bool InitializeD2D(HWND hwnd,GameSettings& sett);
	std::shared_ptr<IWICImagingFactory> imgfactory;
	std::shared_ptr<IWICBitmapDecoder> bmpdecoder;
	std::shared_ptr<ID2D1Multithread> multithread;
	std::shared_ptr<IWICBitmap> wicbitmap;
	std::shared_ptr<ID2D1BitmapBrush> bmpbrush;
	std::shared_ptr<IWICBitmapFrameDecode> bmpframedecoder;
	std::shared_ptr<IWICFormatConverter> formatconverter;
	std::shared_ptr<ID2D1Bitmap> bmp;
	std::shared_ptr<IWICBitmapScaler> bmpscaler;
	std::shared_ptr<ID2D1Factory> d2dfactory;
	std::shared_ptr<IDWriteFactory> dwritefactory;
	std::shared_ptr<IDWriteTextFormat> textformat;
	std::shared_ptr<IDWriteTextLayout> textlayout;
	std::shared_ptr<ID3D11VideoDevice> videodevice;
	std::shared_ptr<ID3D10Device1> d3ddevice;
	std::shared_ptr<IDXGIDevice1> dxgidevice;
	std::shared_ptr<IDXGIAdapter> dxgiadapter;
	std::shared_ptr<IDXGIFactory> dxgifactory;
	std::shared_ptr<ID2D1Layer> layer1;
	void cleanD2D();
	void cleanD3D();
	std::shared_ptr<IDXGISwapChain> swapchain;
	std::shared_ptr<IDXGISurface> surface;
	std::shared_ptr<ID2D1RenderTarget> target;
	std::shared_ptr<ID2D1DrawingStateBlock> targetstate;
	std::shared_ptr<ID2D1SolidColorBrush> solidbrush;
	std::shared_ptr<ID2D1LinearGradientBrush> gradientbrush;
	std::shared_ptr<ID2D1GradientStopCollection> gradientcollection;
	void resizeViewport(HWND hwnd,GameSettings settings);
};
#endif // D2DHANDLE_H_INCLUDED
