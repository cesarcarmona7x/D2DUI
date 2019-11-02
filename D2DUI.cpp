// D2DUI.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
using namespace D2DUI;
namespace D2DUI{
	MsgBox::MsgBox(HWND parent,bool modal,wchar_t* text,wchar_t* title,MSGBoxButtons buttons,MSGBoxIcon icon){
		hwnd=parent;
		this->modal=modal;
		showing=false;
		textContent=std::shared_ptr<TextLabel>(new TextLabel(text));
		textContent->setPadding(5,0);
		textContent->setHorizontalTextAlignment(HorizontalConstants::LEFT);
		textContent->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		textTitle=std::shared_ptr<TextLabel>(new TextLabel(title));
		textTitle->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
		this->buttons=buttons;
		this->msgicon=icon;
		contentRow=std::shared_ptr<TableRow>(new TableRow(2));
		textTitle->setPadding(0,0);
		contentRow->setPadding(0,0);
		contentRow->setGravity(LayoutBase::HGravity::CENTERH,LayoutBase::VGravity::CENTERV);
		switch(msgicon){
		case MSGBOX_ERROR:
			msgboxicon=std::shared_ptr<ImageView>(new ImageView(L"Images\\UI\\msgbox_error.png"));
			break;
		case MSGBOX_INFORMATION:
			msgboxicon=std::shared_ptr<ImageView>(new ImageView(L"Images\\UI\\msgbox_inf.png"));
			break;
		case MSGBOX_QUESTION:
			msgboxicon=std::shared_ptr<ImageView>(new ImageView(L"Images\\UI\\msgbox_question.png"));
			break;
		case MSGBOX_WARNING:
			msgboxicon=std::shared_ptr<ImageView>(new ImageView(L"Images\\UI\\msgbox_warning.png"));
			break;
		}
		msgboxicon->setSize(32,32);
		msgboxicon->setVisible(true);
		contentRow->add(*msgboxicon);
		contentRow->add(*textContent);
		switch(buttons){
		case MSGBOX_OK:
			buttonsRow=std::shared_ptr<GridLayout>(new GridLayout());
			buttonsRow->setGravity(LayoutBase::HGravity::CENTERH,LayoutBase::VGravity::CENTERV);
			buttonsRow->setPadding(0,0);
			btnOk=std::shared_ptr<Button>(new Button(L"OK",L""));
			btnOk->setEnabled(true);
			btnOk->setSize(100,30);
			btnOk->setPadding(0,0);
			btnOk->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnOk->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnOk,1,1);
			break;
		case MSGBOX_OKCANCEL:
			buttonsRow=std::shared_ptr<GridLayout>(new GridLayout(2,1));
			buttonsRow->setGravity(LayoutBase::HGravity::CENTERH,LayoutBase::VGravity::CENTERV);
			buttonsRow->setPadding(0,0);
			btnOk=std::shared_ptr<Button>(new Button(L"OK",L""));
			btnOk->setEnabled(true);
			btnOk->setSize(100,30);
			btnOk->setPadding(0,0);
			btnOk->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnOk->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnOk,1,1);
			btnCancel=std::shared_ptr<Button>(new Button(L"Cancel",L""));
			btnCancel->setEnabled(true);
			btnCancel->setSize(100,30);
			btnCancel->setPadding(0,0);
			btnCancel->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnCancel->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnCancel,2,1);
			break;
		case MSGBOX_YESNO:
			buttonsRow=std::shared_ptr<GridLayout>(new GridLayout(2,1));
			buttonsRow->setGravity(LayoutBase::HGravity::CENTERH,LayoutBase::VGravity::CENTERV);
			buttonsRow->setPadding(0,0);
			btnYes=std::shared_ptr<Button>(new Button(L"Yes",L""));
			btnYes->setEnabled(true);
			btnYes->setSize(100,30);
			btnYes->setPadding(0,0);
			btnYes->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnYes->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnYes,1,1);
			btnNo=std::shared_ptr<Button>(new Button(L"No",L""));
			btnNo->setEnabled(true);
			btnNo->setSize(100,30);
			btnNo->setPadding(0,0);
			btnNo->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnNo->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnNo,2,1);
			break;
		case MSGBOX_YESNOCANCEL:
			buttonsRow=std::shared_ptr<GridLayout>(new GridLayout(3,1));
			buttonsRow->setGravity(LayoutBase::HGravity::CENTERH,LayoutBase::VGravity::CENTERV);
			buttonsRow->setPadding(0,0);
			btnYes=std::shared_ptr<Button>(new Button(L"Yes",L""));
			btnYes->setEnabled(true);
			btnYes->setSize(100,30);
			btnYes->setPadding(0,0);
			btnYes->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnYes->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnYes,1,1);
			btnNo=std::shared_ptr<Button>(new Button(L"No",L""));
			btnNo->setEnabled(true);
			btnNo->setSize(100,30);
			btnNo->setPadding(0,0);
			btnNo->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnNo->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnNo,2,1);
			btnCancel=std::shared_ptr<Button>(new Button(L"Cancel",L""));
			btnCancel->setEnabled(true);
			btnCancel->setSize(100,30);
			btnCancel->setPadding(0,0);
			btnCancel->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnCancel->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnCancel,3,1);
			break;
		}
		setFont(L"Microsoft Sans Serif");
		setTextSize(12.f);
		setForeground(1.f,1.f,1.f);
	}
	void MsgBox::setOpacity(float opacity){
		WindowBase::setOpacity(opacity);
		textContent->setOpacity(opacity);
		textTitle->setOpacity(opacity);
		msgboxicon->setOpacity(opacity);
		for(int i=0;i<buttonsRow->windows.size();i++){
			buttonsRow->windows.at(i).get().setOpacity(opacity);
		}
	}
	void MsgBox::setLocale(wchar_t* locale){
		WindowBase::setLocale(locale);
		textContent->setLocale(locale);
		textTitle->setLocale(locale);
		for(int i=0;i<buttonsRow->windows.size();i++){
			buttonsRow->windows.at(i).get().setLocale(locale);
		}
	}
	void MsgBox::setFont(wchar_t* font){
		WindowBase::setFont(font);
		textTitle->setFont(font);
		textContent->setFont(font);
		for(int i=0;i<buttonsRow->windows.size();i++){
			buttonsRow->windows.at(i).get().setFont(font);
		}
	}
	void MsgBox::setTextSize(float px){
		WindowBase::setTextSize(px);
		textTitle->setTextSize(px);
		textContent->setTextSize(px);
		for(int i=0;i<buttonsRow->windows.size();i++){
			buttonsRow->windows.at(i).get().setTextSize(px);
		}
	}
	void MsgBox::setForeground(int R,int G,int B,int A){
		WindowBase::setForeground(R,G,B,A);
		textTitle->setForeground(R,G,B,A);
		textContent->setForeground(R,G,B,A);
		for(int i=0;i<buttonsRow->windows.size();i++){
			buttonsRow->windows.at(i).get().setForeground(R,G,B,A);
		}
	}
	void MsgBox::setForeground(float R,float G,float B,float A){
		WindowBase::setForeground(R,G,B,A);
		textTitle->setForeground(R,G,B,A);
		textContent->setForeground(R,G,B,A);
		for(int i=0;i<buttonsRow->windows.size();i++){
			buttonsRow->windows.at(i).get().setForeground(R,G,B,A);
		}
	}
	void MsgBox::reorderComponents(std::shared_ptr<D2DHandle>& d2d){
		RECT r;
		GetClientRect(hwnd,&r);
		setPadding(10,5);
		IDWriteTextFormat* formattitle,* formatcontent;
		IDWriteTextLayout* layouttitle,* layoutcontent;
		DWRITE_TEXT_METRICS titlemetrics,contentmetrics;
		d2d->dwritefactory->CreateTextFormat(textTitle->getFont(),NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,textTitle->getTextSize()*(96.f/72.f),locale,&formattitle);
		d2d->dwritefactory->CreateTextLayout(textTitle->getText(),wcslen(textTitle->getText()),formattitle,(float)(r.right-r.left),(float)(r.bottom-r.top),&layouttitle);
		layouttitle->GetMetrics(&titlemetrics);
		int titlewidth=titlemetrics.width*2;
		int titleheight=titlemetrics.height;
		textTitle->setSize(titlewidth,titleheight);
		d2d->dwritefactory->CreateTextFormat(textContent->getFont(),NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,textContent->getTextSize()*(96.f/72.f),locale,&formatcontent);
		d2d->dwritefactory->CreateTextLayout(textContent->getText(),wcslen(textContent->getText()),formatcontent,(float)(r.right-r.left),(float)(r.bottom-r.top),&layoutcontent);
		layoutcontent->GetMetrics(&contentmetrics);
		int textcontentwidth=contentmetrics.width*2;
		int textcontentheight=contentmetrics.height*2;
		textContent->setSize(textcontentwidth,textcontentheight);
		int maxwidth=0;
		int buttonsrowwidth=100*buttonsRow->windows.size();
		buttonsRow->setSize(buttonsrowwidth,40);
		if(titlewidth>=textcontentwidth){
			if(titlewidth>=buttonsrowwidth){
				maxwidth=titlewidth;
			}
			else{
				maxwidth=buttonsrowwidth;
			}
		}
		else{
			if(textcontentwidth>=buttonsrowwidth){
				maxwidth=textcontentwidth;
			}
			else{
				maxwidth=buttonsrowwidth;
			}
		}
		int winwidth=(r.right-r.left);
		int winheight=(r.bottom-r.top);
		int height=titleheight+textcontentheight+buttonsRow->getHeight()+getTopPadding()+getBottomPadding();
		setBounds(((winwidth/2)-(maxwidth/2)),((winheight/2)-(height/2)),((winwidth/2)-(maxwidth/2))+maxwidth,((winheight/2)-(height/2))+height);
		textTitle->setBounds(getBounds().left,getBounds().top,getBounds().right,getBounds().top+titleheight);
		int totalcontentheight=textcontentheight<32? 32: textcontentheight;
		int totalcontentwidth=textcontentwidth+32;
		contentRow->setBounds(getLeftPadding()+((winwidth/2)-(maxwidth/2)),textTitle->getBounds().bottom+getTopPadding(),getLeftPadding()+((winwidth/2)-(maxwidth/2))+maxwidth,textTitle->getBounds().bottom+getTopPadding()+totalcontentheight);
		buttonsRow->setBounds(getLeftPadding()+((winwidth/2)-(buttonsrowwidth/2)),contentRow->getBounds().bottom,getLeftPadding()+((winwidth/2)-(buttonsrowwidth/2))+buttonsrowwidth,contentRow->getBounds().bottom+buttonsRow->getHeight());
		formattitle->Release();
		formatcontent->Release();
		layouttitle->Release();
		layoutcontent->Release();
	}
	void MsgBox::draw(std::shared_ptr<D2DHandle>& d2d){
		reorderComponents(d2d);
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA_bg[0],fRGBA_bg[1],fRGBA_bg[2],fRGBA_bg[3]),d2d->solidbrush.ReleaseAndGetAddressOf());
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),d2d->solidbrush.Get());
		textTitle->draw(d2d);
		contentRow->draw(d2d);
		buttonsRow->draw(d2d);
	}
	InfoBox::InfoBox(HWND parent,wchar_t* text){
		this->hwnd=parent;
		textContent=std::shared_ptr<TextLabel>(new TextLabel(text));
		textContent->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
		textContent->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		textContent->setPadding(0,0);
		setFont(L"Microsoft Sans Serif");
		setTextSize(12.0f);
		setBackground(1.f,0.f,1.f,1.f);
		setForeground(1.f,1.f,1.f,1.f);
	}
	void InfoBox::setFont(wchar_t* font){
		this->font=font;
		textContent->setFont(font);
	}
	void InfoBox::setTextSize(float px){
		WindowBase::setTextSize(px);
		textContent->setTextSize(px);
	}
	void InfoBox::setForeground(int R,int G,int B,int A){
		WindowBase::setForeground(R,G,B,A);
		textContent->setForeground(R,G,B,A);
	}
	void InfoBox::setForeground(float R,float G,float B,float A){
		WindowBase::setForeground(R,G,B,A);
		textContent->setForeground(R,G,B,A);
	}
	void InfoBox::setOpacity(float opacity){
		this->opacity=opacity;
		textContent->setOpacity(opacity);
	}
	void InfoBox::setLocale(wchar_t* locale){
		this->locale=locale;
		textContent->setLocale(locale);
	}
	void InfoBox::reorderComponents(std::shared_ptr<D2DHandle>& d2d){
		RECT r;
		GetClientRect(hwnd,&r);
		int winwidth=(r.right-r.left);
		int winheight=(r.bottom-r.top);
		setPadding(20,10);
		DWRITE_TEXT_METRICS contentmetrics;
		IDWriteTextFormat* formatcontent;
		IDWriteTextLayout* layoutcontent;
		d2d->dwritefactory->CreateTextFormat(textContent->getFont(),NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,textContent->getTextSize()*(96.f/72.f),locale,&formatcontent);
		d2d->dwritefactory->CreateTextLayout(textContent->getText(),wcslen(textContent->getText()),formatcontent,(float)(r.right-r.left),(float)(r.bottom-r.top),&layoutcontent);
		layoutcontent->GetMetrics(&contentmetrics);
		int textcontentwidth=contentmetrics.widthIncludingTrailingWhitespace;
		int textcontentheight=contentmetrics.height*2;
		textContent->setSize(textcontentwidth,textcontentheight);
		setBounds(((winwidth/2)-((textcontentwidth)/2)),((winheight/2)-((textcontentheight)/2)),((winwidth/2)-(textcontentwidth/2))+textcontentwidth,((winheight/2)-(textcontentheight/2))+textcontentheight);
		textContent->setBounds(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding(),getBounds().right-getRightPadding(),getBounds().bottom-getBottomPadding());
	}
	void InfoBox::draw(std::shared_ptr<D2DHandle>& d2d){
		reorderComponents(d2d);
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA_bg[0],fRGBA_bg[1],fRGBA_bg[2],fRGBA_bg[3]),d2d->solidbrush.ReleaseAndGetAddressOf());
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),d2d->solidbrush.Get());
		textContent->draw(d2d);
	}
	PopupNotification::PopupNotification(HWND parent,wchar_t* text,long duration){
		this->hwnd=parent;
		this->duration=duration;
		textContent=new TextLabel(text);
		textContent->setPadding(0,0);
		setPadding(0,0);
		showing=false;
		opacity=0;
		setFont(L"Microsoft Sans Serif");
		setForeground(0.f,0.f,0.f);
		setTextSize(12.0f);
	}
	void PopupNotification::setTextSize(float px){
		WindowBase::setTextSize(px);
		textContent->setTextSize(px);
	}
	void PopupNotification::setFont(wchar_t* font){
		WindowBase::setFont(font);
		textContent->setFont(font);
	}
	void PopupNotification::setForeground(int R,int G,int B,int A){
		WindowBase::setForeground(R,G,B,A);
		textContent->setForeground(R,G,B,A);
	}
	void PopupNotification::setForeground(float R,float G,float B,float A){
		WindowBase::setForeground(R,G,B,A);
		textContent->setForeground(R,G,B,A);
	}
	void PopupNotification::reorderComponents(std::shared_ptr<D2DHandle>& d2d){
		RECT r;
		GetClientRect(hwnd,&r);
		int winwidth=(r.right-r.left);
		int winheight=(r.bottom-r.top);
		DWRITE_TEXT_METRICS contentmetrics;
		IDWriteTextFormat* formatcontent;
		IDWriteTextLayout* layoutcontent;
		d2d->dwritefactory->CreateTextFormat(textContent->getFont(),NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,textContent->getTextSize()*(96.f/72.f),locale,&formatcontent);
		d2d->dwritefactory->CreateTextLayout(textContent->getText(),wcslen(textContent->getText()),formatcontent,(float)(r.right-r.left),(float)(r.bottom-r.top),&layoutcontent);
		layoutcontent->GetMetrics(&contentmetrics);
		int textcontentwidth=contentmetrics.widthIncludingTrailingWhitespace;
		int textcontentheight=contentmetrics.height*2;
		textContent->setSize(textcontentwidth,textcontentheight);
		setBounds(((winwidth/2)-((textcontentwidth)/2)),((winheight/2)-((textcontentheight)/2)),((winwidth/2)-(textcontentwidth/2))+textcontentwidth,((winheight/2)-(textcontentheight/2))+textcontentheight);
		textContent->setBounds(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding(),getBounds().right-getRightPadding(),getBounds().bottom-getBottomPadding());
	}
	void PopupNotification::draw(std::shared_ptr<D2DHandle>& d2d){
		setForeground(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity);
		reorderComponents(d2d);
		d2d->target->PushAxisAlignedClip(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),D2D1_ANTIALIAS_MODE_ALIASED);
		textContent->draw(d2d);
		d2d->target->PopAxisAlignedClip();
	}
	void WindowBase::setParentLayout(LayoutBase& parent){
		this->parent=parent;	
	}
	void Border::setColor(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=(R/255.0f);
		fRGBA[1]=(G/255.0f);
		fRGBA[2]=(B/255.0f);
		fRGBA[3]=(A/255.0f);
	}
	void Border::setColor(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
	}
	int* Border::getColorInt(){
		return iRGBA;
	}
	float* Border::getColorFloat(){
		return fRGBA;
	}
	void Border::setStroke(Border::Stroke s){
		stroke=s;
	}
	Border::Stroke Border::getStroke(){
		return stroke;
	}
	void Border::setStrokeWidth(float width){
		strokeWidth=width;
	}
	float Border::getStrokeWidth(){
		return strokeWidth;
	}
	LinearLayout::LinearLayout(LayoutBase::Orientation o): LayoutBase(){
		LinearLayout::o=o;
		setBorder(Border());
		setRadius(0.0f);
	}
	void LinearLayout::add(WindowBase& window){
		windows.push_back(window);
		std::wstring wid(random_string(6));
		wchar_t* id=new wchar_t[wid.length()];
		wcscpy(id,wid.c_str());
		window.setId(id);
		int maxIndex=(windows.size()+layouts.size())-1;
		window.setIndex(maxIndex);
	}
	void LinearLayout::add(LayoutBase& layout){
		layouts.push_back(layout);
		std::wstring wid(random_string(6));
		wchar_t* id=new wchar_t[wid.length()];
		wcscpy(id,wid.c_str());
		layout.setId(id);
		int maxIndex=(windows.size()+layouts.size())-1;
		layout.setIndex(maxIndex);
	}
	void LinearLayout::remove(wchar_t* id){
		bool isinwindows=false;
		for(int i=0;i<windows.size();i++){
			if(wcscmp(windows.at(i).get().getId(),id)==0){
				isinwindows=true;
				windows.erase(windows.begin()+i);
				break;
			}
		}
		if(isinwindows){
			for(int i=0;i<layouts.size();i++){
				if(wcscmp(layouts.at(i).get().getId(),id)==0){
					layouts.erase(layouts.begin()+i);
					break;
				}
			}
		}
	}
	void LinearLayout::reorderComponents(){
		int top=getTopPadding();
		int left=getLeftPadding();
		int components=(windows.size()+layouts.size());
		if(getOrientation()==VERTICAL){
			for(int i=0;i<components;i++){
				for(int j=0;j<windows.size();j++){
					if(windows.at(j).get().getIndex()==i){
						windows.at(j).get().setBounds(left,top,left+windows.at(j).get().getWidth()-getRightPadding(),top+windows.at(j).get().getHeight()-getBottomPadding());
						top+=windows.at(j).get().getHeight();
						break;
					}
				}
				for(int j=0;j<layouts.size();j++){
					if(layouts.at(j).get().getIndex()==i){
						layouts.at(j).get().setBounds(left,top,left+layouts.at(j).get().getWidth()-getRightPadding(),top+layouts.at(j).get().getHeight()-getBottomPadding());
						top+=layouts.at(j).get().getHeight();
						break;
					}
				}
			}
		}//Vertical Placement
		else if(getOrientation()==HORIZONTAL){
			for(int i=0;i<components;i++){
				for(int j=0;j<windows.size();j++){
					if(windows.at(j).get().getIndex()==i){
						windows.at(j).get().setBounds(left,top,left+windows.at(j).get().getWidth()-getRightPadding(),top+windows.at(j).get().getHeight()-getBottomPadding());
						left+=windows.at(j).get().getWidth();
						break;
					}
				}
				for(int j=0;j<layouts.size();j++){
					if(layouts.at(j).get().getIndex()==i){
						layouts.at(j).get().setBounds(left,top,left+layouts.at(j).get().getWidth()-getRightPadding(),top+layouts.at(j).get().getHeight()-getBottomPadding());
						left+=layouts.at(j).get().getWidth();
						break;
					}
				}
			}
		}//Horizontal Placement
	}
	void LinearLayout::draw(std::shared_ptr<D2DHandle>& d2d){
		ComPtr<ID2D1StrokeStyle> strokestyle;
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]),d2d->solidbrush.ReleaseAndGetAddressOf());
		d2d->target->FillRoundedRectangle(RoundedRect(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),radius_x,radius_y),d2d->solidbrush.Get());
		if(&leftBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(leftBorder.fRGBA[0],leftBorder.fRGBA[1],leftBorder.fRGBA[2],leftBorder.fRGBA[3]));
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
				break;
			}
		}
		if(&topBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(topBorder.fRGBA[0],topBorder.fRGBA[1],topBorder.fRGBA[2],topBorder.fRGBA[3]));
			switch(topBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getTopBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getTopBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getTopBorder().getStrokeWidth());
				break;
			}
		}
		if(&rightBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(rightBorder.fRGBA[0],rightBorder.fRGBA[1],rightBorder.fRGBA[2],rightBorder.fRGBA[3]));
			switch(rightBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getRightBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getRightBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getRightBorder().getStrokeWidth());
				break;
			}
		}
		if(&bottomBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(bottomBorder.fRGBA[0],bottomBorder.fRGBA[1],bottomBorder.fRGBA[2],bottomBorder.fRGBA[3]));
			switch(bottomBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getBottomBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getBottomBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getBottomBorder().getStrokeWidth());
				break;
			}
		}
		d2d->target->EndDraw();
		reorderComponents();
		d2d->target->PushAxisAlignedClip(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),D2D1_ANTIALIAS_MODE_ALIASED);
		d2d->target->SaveDrawingState(d2d->targetstate.Get());
		d2d->target->SetTransform(Matrix3x2F::Translation(getBounds().left,getBounds().top));
		if(layouts.size()!=0){
			for(int i=0;i<layouts.size();i++){
				layouts.at(i).get().draw(d2d);
			}
		}
		if(windows.size()!=0){
			for(int i=0;i<windows.size();i++){
				windows.at(i).get().draw(d2d);
			}
		}
		d2d->target->PopAxisAlignedClip();
		d2d->target->RestoreDrawingState(d2d->targetstate.Get());
	}
	GridLayout::GridLayout(int rows,int cols){
		GridLayout::rows=rows;
		GridLayout::cols=cols;
		setBorder(Border());
		leftBorder.setColor(0,0,0,255);
		leftBorder.setStrokeWidth(1.0f);
		setBorder(leftBorder);
		setRadius(0.0f);
	}
	void GridLayout::add(WindowBase& window,int row,int col){
		windows.push_back(window);
		window.setPosition(row,col);
	}
	void GridLayout::add(LayoutBase& layout,int row,int col){
		layouts.push_back(layout);
		layout.setPosition(row,col);
	}
	void GridLayout::remove(int row,int col){
		bool inwindows=false;
		if(windows.size()!=0){
			for(int i=0;i<windows.size();i++){
				if(windows.at(i).get().col==col&&windows.at(i).get().row==row){
					windows.at(i).get().setPosition(-1,-1);
					windows.erase(windows.begin()+i);
					inwindows=true;
					break;
				}
			}
		}
		if(inwindows){
			if(layouts.size()!=0){
				for(int i=0;i<layouts.size();i++){
					if(layouts.at(i).get().col==col&&layouts.at(i).get().row==row){
						layouts.at(i).get().setPosition(-1,-1);
						layouts.erase(layouts.begin()+i);
						break;
					}
				}
			}
		}
	}
	void GridLayout::reorderComponents(){
		int components=windows.size()+layouts.size();
		int cellwidth=((getBounds().right-getBounds().left)-getLeftPadding()-getRightPadding())/rows;
		int cellheight=((getBounds().bottom-getBounds().top)-getTopPadding()-getBottomPadding())/cols;
		int left=getBounds().left+getLeftPadding();
		int initialleft=left;
		int top=getBounds().top+getTopPadding();
		int initialtop=top;
		for(int j=1;j<=cols;j++){
			for(int k=1;k<=rows;k++){
				for(int w=0;w<windows.size();w++){
					if(windows.at(w).get().col==j&&windows.at(w).get().row==k){
						switch(hg){
						case HGravity::LEFT:
							switch(vg){
							case VGravity::TOP:
								if(windows.at(w).get().getHeight()>cellheight){
									windows.at(w).get().height=cellheight;
								}
								if(windows.at(w).get().getWidth()>cellwidth){
									windows.at(w).get().width=cellwidth;
								}
								windows.at(w).get().setBounds(left,top,left+windows.at(w).get().getWidth(),top+windows.at(w).get().getHeight());
								if(k==rows){
									left=initialleft;
									top+=cellheight;
								}
								else{
									left+=cellwidth;
								}
								break;
							case VGravity::CENTERV:
								if(windows.at(w).get().getHeight()>cellheight){
									windows.at(w).get().height=cellheight;
								}
								if(windows.at(w).get().getWidth()>cellwidth){
									windows.at(w).get().width=cellwidth;
								}
								windows.at(w).get().setBounds(left,top+((cellheight/2)-(windows.at(w).get().getHeight()/2)),left+windows.at(w).get().getWidth(),top+((cellheight/2)-(windows.at(w).get().getHeight()/2))+windows.at(w).get().getHeight());
								if(k==rows){
									left=initialleft;
									top+=cellheight;
								}
								else{
									left+=cellwidth;
								}
								break;
							case VGravity::BOTTOM:
								if(windows.at(w).get().getHeight()>cellheight){
									windows.at(w).get().height=cellheight;
								}
								if(windows.at(w).get().getWidth()>cellwidth){
									windows.at(w).get().width=cellwidth;
								}
								windows.at(w).get().setBounds(left,top+cellheight-windows.at(w).get().getHeight(),left+windows.at(w).get().getWidth(),top+cellheight);
								if(k==rows){
									left=initialleft;
									top+=cellheight;
								}
								else{
									left+=cellwidth;
								}
								break;
							}
							break;
						case HGravity::CENTERH:
							switch(vg){
							case VGravity::TOP:
								if(windows.at(w).get().getHeight()>cellheight){
									windows.at(w).get().height=cellheight;
								}
								if(windows.at(w).get().getWidth()>cellwidth){
									windows.at(w).get().width=cellwidth;
								}
								windows.at(w).get().setBounds(left+((cellwidth/2)-(windows.at(w).get().getHeight()/2)),top,left+((cellwidth/2)-(windows.at(w).get().getWidth()/2))+windows.at(w).get().getWidth(),top+windows.at(w).get().getHeight());
								if(k==rows){
									left=initialleft;
									top+=cellheight;
								}
								else{
									left+=cellwidth;
								}
								break;
							case VGravity::CENTERV:
								if(windows.at(w).get().getHeight()>cellheight){
									windows.at(w).get().height=cellheight;
								}
								if(windows.at(w).get().getWidth()>cellwidth){
									windows.at(w).get().width=cellwidth;
								}
								windows.at(w).get().setBounds(left+((cellwidth/2)-(windows.at(w).get().getWidth()/2)),top+((cellheight/2)-(windows.at(w).get().getHeight()/2)),left+((cellwidth/2)-(windows.at(w).get().getWidth()/2))+windows.at(w).get().getWidth(),top+((cellheight/2)-(windows.at(w).get().getHeight()/2))+windows.at(w).get().getHeight());
								if(k==rows){
									left=initialleft;
									top+=cellheight;
								}
								else{
									left+=cellwidth;
								}
								break;
							case VGravity::BOTTOM:
								if(windows.at(w).get().getHeight()>cellheight){
									windows.at(w).get().height=cellheight;
								}
								if(windows.at(w).get().getWidth()>cellwidth){
									windows.at(w).get().width=cellwidth;
								}
								windows.at(w).get().setBounds(left+((cellwidth/2)-(windows.at(w).get().getWidth()/2)),top+cellheight-windows.at(w).get().getHeight(),left+((cellwidth/2)-(windows.at(w).get().getWidth()/2))+windows.at(w).get().getWidth(),top+cellheight);
								if(k==rows){
									left=initialleft;
									top+=cellheight;
								}
								else{
									left+=cellwidth;
								}
								break;
							}
							break;
						case HGravity::RIGHT:
							switch(vg){
							case VGravity::TOP:
								if(windows.at(w).get().getHeight()>cellheight){
									windows.at(w).get().height=cellheight;
								}
								if(windows.at(w).get().getWidth()>cellwidth){
									windows.at(w).get().width=cellwidth;
								}
								windows.at(w).get().setBounds(left+cellwidth-windows.at(w).get().getWidth(),top,left+cellwidth,top+windows.at(w).get().getHeight());
								if(k==rows){
									left=initialleft;
									top+=cellheight;
								}
								else{
									left+=cellwidth;
								}
								break;
							case VGravity::CENTERV:
								if(windows.at(w).get().getHeight()>cellheight){
									windows.at(w).get().height=cellheight;
								}
								if(windows.at(w).get().getWidth()>cellwidth){
									windows.at(w).get().width=cellwidth;
								}
								windows.at(w).get().setBounds(left+cellwidth-windows.at(w).get().getWidth(),top+((cellheight/2)-(windows.at(w).get().getHeight()/2)),left+cellwidth,top+((cellheight/2)-(windows.at(w).get().getHeight()/2))+windows.at(w).get().getHeight());
								if(k==rows){
									left=initialleft;
									top+=cellheight;
								}
								else{
									left+=cellwidth;
								}
								break;
							case VGravity::BOTTOM:
								if(windows.at(w).get().getHeight()>cellheight){
									windows.at(w).get().height=cellheight;
								}
								if(windows.at(w).get().getWidth()>cellwidth){
									windows.at(w).get().width=cellwidth;
								}
								windows.at(w).get().setBounds(left+cellwidth-windows.at(w).get().getWidth(),top+cellheight-windows.at(w).get().getHeight(),left+cellwidth,top+cellheight);
								if(k==rows){
									left=initialleft;
									top+=cellheight;
								}
								else{
									left+=cellwidth;
								}
								break;
							}
							break;
						}
						break;
					}
				}
				for(int l=0;l<layouts.size();l++){
					if(layouts.at(l).get().col==j&&layouts.at(l).get().row==k){
						break;
					}
				}
			}
		}
	}
	void GridLayout::draw(std::shared_ptr<D2DHandle>& d2d){
		ComPtr<ID2D1StrokeStyle> strokestyle;
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]),d2d->solidbrush.ReleaseAndGetAddressOf());
		d2d->target->FillRoundedRectangle(RoundedRect(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),radius_x,radius_y),d2d->solidbrush.Get());
		if(&leftBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(leftBorder.fRGBA[0],leftBorder.fRGBA[1],leftBorder.fRGBA[2],leftBorder.fRGBA[3]));
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getLeftBorder().getStrokeWidth());
				break;
			}
		}
		if(&topBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(topBorder.fRGBA[0],topBorder.fRGBA[1],topBorder.fRGBA[2],topBorder.fRGBA[3]));
			switch(topBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getTopBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getTopBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getTopBorder().getStrokeWidth());
				break;
			}
		}
		if(&rightBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(rightBorder.fRGBA[0],rightBorder.fRGBA[1],rightBorder.fRGBA[2],rightBorder.fRGBA[3]));
			switch(rightBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getRightBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getRightBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getRightBorder().getStrokeWidth());
				break;
			}
		}
		if(&bottomBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(bottomBorder.fRGBA[0],bottomBorder.fRGBA[1],bottomBorder.fRGBA[2],bottomBorder.fRGBA[3]));
			switch(bottomBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getBottomBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getBottomBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getBottomBorder().getStrokeWidth());
				break;
			}
		}
		reorderComponents();
		d2d->target->PushAxisAlignedClip(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),D2D1_ANTIALIAS_MODE_ALIASED);
		for(int i=0;i<windows.size();i++){
			windows.at(i).get().draw(d2d);
		}
		d2d->target->PopAxisAlignedClip();
	}
	void TableLayout::add(TableRow& row){
		rows.push_back(row);
		std::wstring wid(random_string(6));
		wchar_t* id=new wchar_t[wid.length()];
		wcscpy(id,wid.c_str());
		row.setId(id);
		int maxIndex=rows.size()-1;
		row.setIndex(maxIndex);
	}
	void TableLayout::remove(wchar_t* id){
		if(rows.size()!=0){
			for(int i=0;i<rows.size();i++){
				if(wcscmp(id,rows.at(i).get().getId())==0){
					rows.erase(rows.begin()+i);
					break;
				}
			}
		}
	}
	void TableLayout::reorderComponents(){
		int components=windows.size()+layouts.size();
		int left=getBounds().left+getLeftPadding();
		int initialleft=left;
		int top=getBounds().top+getTopPadding();
		int initialtop=top;
		if(rows.size()!=0){
			for(int i=0;i<rows.size();i++){
				rows.at(i).get().reorderComponents();
				int width=rows.at(i).get().getWidth();
				int height=rows.at(i).get().getHeight();
				rows.at(i).get().setBounds(left,top,left+width,top+height);
				top+=height;
			}
		}
	}
	void TableLayout::draw(std::shared_ptr<D2DHandle>& d2d){
		ComPtr<ID2D1StrokeStyle> strokestyle;
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]),d2d->solidbrush.ReleaseAndGetAddressOf());
		d2d->target->FillRoundedRectangle(RoundedRect(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),radius_x,radius_y),d2d->solidbrush.Get());
		if(&leftBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(leftBorder.fRGBA[0],leftBorder.fRGBA[1],leftBorder.fRGBA[2],leftBorder.fRGBA[3]));
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getLeftBorder().getStrokeWidth());
				break;
			}
		}
		if(&topBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(topBorder.fRGBA[0],topBorder.fRGBA[1],topBorder.fRGBA[2],topBorder.fRGBA[3]));
			switch(topBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getTopBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getTopBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getTopBorder().getStrokeWidth());
				break;
			}
		}
		if(&rightBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(rightBorder.fRGBA[0],rightBorder.fRGBA[1],rightBorder.fRGBA[2],rightBorder.fRGBA[3]));
			switch(rightBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getRightBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getRightBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getRightBorder().getStrokeWidth());
				break;
			}
		}
		if(&bottomBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(bottomBorder.fRGBA[0],bottomBorder.fRGBA[1],bottomBorder.fRGBA[2],bottomBorder.fRGBA[3]));
			switch(bottomBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getBottomBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getBottomBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getBottomBorder().getStrokeWidth());
				break;
			}
		}
		reorderComponents();
		d2d->target->PushAxisAlignedClip(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),D2D1_ANTIALIAS_MODE_ALIASED);
		if(rows.size()!=0){
			for(int i=0;i<rows.size();i++){
				rows.at(i).get().draw(d2d);
			}
		}
		d2d->target->PopAxisAlignedClip();
	}
	TableRow::TableRow(int cols){
		TableRow::cols=cols;
		setBorder(Border());
		setGravity(HGravity::CENTERH,VGravity::CENTERV);
		setBounds(0,0,0,0);
	}
	void TableRow::add(WindowBase& window){
		windows.push_back(window);
		std::wstring wid(random_string(6));
		wchar_t* id=new wchar_t[wid.length()];
		wcscpy(id,wid.c_str());
		window.setId(id);
		int maxIndex=(windows.size()+layouts.size())-1;
		window.setIndex(maxIndex);
		if(maxIndex+1>cols){
			cols++;
		}
	}
	void TableRow::add(LayoutBase& layout){
		layouts.push_back(layout);
		std::wstring wid(random_string(6));
		wchar_t* id=new wchar_t[wid.length()];
		wcscpy(id,wid.c_str());
		layout.setId(id);
		int maxIndex=(windows.size()+layouts.size())-1;
		layout.setIndex(maxIndex);
		if(maxIndex+1>cols){
			cols++;
		}
	}
	void TableRow::remove(wchar_t* id){
		bool inwindows=false;
		if(windows.size()!=0){
			for(int i=0;i<windows.size();i++){
				if(wcscmp(windows.at(i).get().getId(),id)==0){
					inwindows=true;
					windows.erase(windows.begin()+i);
					break;
				}
			}
		}
		if(inwindows){
			if(layouts.size()!=0){
				for(int i=0;i<layouts.size();i++){
					if(wcscmp(layouts.at(i).get().getId(),id)==0){
						layouts.erase(layouts.begin()+i);
						break;
					}
				}
			}
		}
	}
	void TableRow::reorderComponents(){
		int components=windows.size()+layouts.size();
		int leftpadding=getLeftPadding()*(max(1,cols-1));
		int maxheight=0;
		int cellwidth=0;
		int left=getBounds().left+getLeftPadding();
		int top=getBounds().top+getTopPadding();
		int mhw=0,mhl=0;
		if(windows.size()!=0){
			std::sort(windows.begin(),windows.end(),[](const std::reference_wrapper<WindowBase> a,const std::reference_wrapper<WindowBase> b){
				return a.get().height>=b.get().height;
			});
			mhw=windows.at(0).get().getHeight();
		}
		if(layouts.size()!=0){
			std::sort(layouts.begin(),layouts.end(),[](const std::reference_wrapper<LayoutBase> a,const std::reference_wrapper<LayoutBase> b){
				return a.get().height>=b.get().height;
			});
			mhl=layouts.at(0).get().getHeight();
		}
		if(mhw>=mhl){
			maxheight=mhw;
		}
		else{
			maxheight=mhl;
		}
		for(int i=0;i<components;i++){
			for(int j=0;j<windows.size();j++){
				if(windows.at(j).get().getIndex()==i){
					cellwidth=windows.at(j).get().getWidth();
					switch(hg){
					case HGravity::LEFT:
						switch(vg){
						case VGravity::TOP:
							windows.at(j).get().setBounds(left,top,left+windows.at(j).get().getWidth(),top+windows.at(j).get().getHeight());	
							left+=cellwidth;
							break;
						case VGravity::CENTERV:
							windows.at(j).get().setBounds(left,top+((maxheight/2)-(windows.at(j).get().getHeight()/2)),left+windows.at(j).get().getWidth(),top+((maxheight/2)-(windows.at(j).get().getHeight()/2))+windows.at(j).get().getHeight());
							left+=cellwidth;
							break;
						case VGravity::BOTTOM:
							windows.at(j).get().setBounds(left,top+maxheight-windows.at(j).get().getHeight(),left+windows.at(j).get().getWidth(),top+maxheight);
							left+=cellwidth;
							break;
						}
						break;
					case HGravity::CENTERH:
						switch(vg){
						case VGravity::TOP:
							windows.at(j).get().setBounds(left+((cellwidth/2)-(windows.at(j).get().getWidth()/2)),top,left+((cellwidth/2)-(windows.at(j).get().getWidth()/2))+windows.at(j).get().getWidth(),top+windows.at(j).get().getHeight());
							left+=cellwidth;
							break;
						case VGravity::CENTERV:
							windows.at(j).get().setBounds(left+((cellwidth/2)-(windows.at(j).get().getWidth()/2)),top+((maxheight/2)-(windows.at(j).get().getHeight()/2)),left+((cellwidth/2)-(windows.at(j).get().getWidth()/2))+windows.at(j).get().getWidth(),top+((maxheight/2)-(windows.at(j).get().getHeight()/2))+windows.at(j).get().getHeight());
							left+=cellwidth;
							break;
						case VGravity::BOTTOM:
							windows.at(j).get().setBounds(left+((cellwidth/2)-(windows.at(j).get().getWidth()/2)),top+maxheight-windows.at(j).get().getHeight(),left+((cellwidth/2)-(windows.at(j).get().getWidth()/2))+windows.at(j).get().getWidth(),top+maxheight);
							left+=cellwidth;
							break;
						}
						break;
					case HGravity::RIGHT:
						switch(vg){
						case VGravity::TOP:
							windows.at(j).get().setBounds(left+cellwidth-windows.at(j).get().getWidth(),top,left+cellwidth,top+windows.at(j).get().getHeight());
							left+=cellwidth;
							break;
						case VGravity::CENTERV:
							windows.at(j).get().setBounds(left+cellwidth-windows.at(j).get().getWidth(),top+((maxheight/2)-(windows.at(j).get().getHeight()/2)),left+cellwidth,top+((maxheight/2)-(windows.at(j).get().getHeight()/2))+windows.at(j).get().getHeight());
							left+=cellwidth;
							break;
						case VGravity::BOTTOM:
							windows.at(j).get().setBounds(left+cellwidth-windows.at(j).get().getWidth(),top+maxheight-windows.at(j).get().getHeight(),left+cellwidth,top+maxheight);
							left+=cellwidth;
							break;
						}
						break;
					}
				}
			}
			for(int k=0;k<layouts.size();k++){
				if(layouts.at(k).get().getIndex()==i){
					cellwidth=layouts.at(k).get().getWidth();
					switch(hg){
					case HGravity::LEFT:
						switch(vg){
						case VGravity::TOP:
							layouts.at(k).get().setBounds(left,top,left+layouts.at(k).get().getWidth(),top+layouts.at(k).get().getHeight());
							left+=cellwidth;
							break;
						case VGravity::CENTERV:
							layouts.at(k).get().setBounds(left,top+((maxheight/2)-(layouts.at(k).get().getHeight()/2)),left+layouts.at(k).get().getWidth(),top+((maxheight/2)-(layouts.at(k).get().getHeight()/2))+layouts.at(k).get().getHeight());
							left+=cellwidth;
							break;
						case VGravity::BOTTOM:
							layouts.at(k).get().setBounds(left,top+maxheight-layouts.at(k).get().getHeight(),left+layouts.at(k).get().getWidth(),top+maxheight);
							left+=cellwidth;
							break;
						}
						break;
					case HGravity::CENTERH:
						switch(vg){
						case VGravity::TOP:
							layouts.at(k).get().setBounds(left+((cellwidth/2)-(layouts.at(k).get().getWidth()/2)),top,left+((cellwidth/2)-(layouts.at(k).get().getWidth()/2))+layouts.at(k).get().getWidth(),top+layouts.at(k).get().getHeight());
							left+=cellwidth;
							break;
						case VGravity::CENTERV:
							layouts.at(k).get().setBounds(left+((cellwidth/2)-(layouts.at(k).get().getWidth()/2)),top+((maxheight/2)-(layouts.at(k).get().getHeight()/2)),left+((cellwidth/2)-(layouts.at(k).get().getWidth()/2))+layouts.at(k).get().getWidth(),top+((maxheight/2)-(layouts.at(k).get().getHeight()/2))+layouts.at(k).get().getHeight());
							left+=cellwidth;
							break;
						case VGravity::BOTTOM:
							layouts.at(k).get().setBounds(left+((cellwidth/2)-(layouts.at(k).get().getWidth()/2)),top+maxheight-layouts.at(k).get().getHeight(),left+((cellwidth/2)-(layouts.at(k).get().getWidth()/2))+layouts.at(k).get().getWidth(),top+maxheight);
							left+=cellwidth;
							break;
						}
						break;
					case HGravity::RIGHT:
						switch(vg){
						case VGravity::TOP:
							layouts.at(k).get().setBounds(left+cellwidth-layouts.at(k).get().getWidth(),top,left+cellwidth,top+layouts.at(k).get().getHeight());
							left+=cellwidth;
							break;
						case VGravity::CENTERV:
							layouts.at(k).get().setBounds(left+cellwidth-layouts.at(k).get().getWidth(),top+((maxheight/2)-(layouts.at(k).get().getHeight()/2)),left+cellwidth,top+((maxheight/2)-(layouts.at(k).get().getHeight()/2))+layouts.at(k).get().getHeight());
							left+=cellwidth;
							break;
						case VGravity::BOTTOM:
							layouts.at(k).get().setBounds(left+cellwidth-layouts.at(k).get().getWidth(),top+maxheight-layouts.at(k).get().getHeight(),left+cellwidth,top+maxheight);
							left+=cellwidth;
							break;
						}
						break;
					}
				}
			}
		}
	}
	void TableRow::draw(std::shared_ptr<D2DHandle>& d2d){
		ComPtr<ID2D1StrokeStyle> strokestyle;
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]),d2d->solidbrush.ReleaseAndGetAddressOf());
		d2d->target->FillRoundedRectangle(RoundedRect(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),radius_x,radius_y),d2d->solidbrush.Get());
		if(&leftBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(leftBorder.fRGBA[0],leftBorder.fRGBA[1],leftBorder.fRGBA[2],leftBorder.fRGBA[3]));
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getLeftBorder().getStrokeWidth());
				break;
			}
		}
		if(&topBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(topBorder.fRGBA[0],topBorder.fRGBA[1],topBorder.fRGBA[2],topBorder.fRGBA[3]));
			switch(topBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getTopBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getTopBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getTopBorder().getStrokeWidth());
				break;
			}
		}
		if(&rightBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(rightBorder.fRGBA[0],rightBorder.fRGBA[1],rightBorder.fRGBA[2],rightBorder.fRGBA[3]));
			switch(rightBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getRightBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getRightBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getRightBorder().getStrokeWidth());
				break;
			}
		}
		if(&bottomBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(bottomBorder.fRGBA[0],bottomBorder.fRGBA[1],bottomBorder.fRGBA[2],bottomBorder.fRGBA[3]));
			switch(bottomBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getBottomBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getBottomBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.Get(),getBottomBorder().getStrokeWidth());
				break;
			}
		}
		reorderComponents();
		d2d->target->PushAxisAlignedClip(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),D2D1_ANTIALIAS_MODE_ALIASED);
		if(windows.size()!=0){
			for(int i=0;i<windows.size();i++){
				windows.at(i).get().draw(d2d);
			}
		}
		if(layouts.size()!=0){
			for(int j=0;j<layouts.size();j++){
				layouts.at(j).get().draw(d2d);
			}
		}
		d2d->target->PopAxisAlignedClip();
	}
	void RadioGroup::add(RadioButton& rb){
		rg.push_back(rb);
		rb.setRBIndex(rg.size()-1);
	}
	void RadioGroup::remove(int index){
		int i=index;
		rg.erase(rg.begin()+i);
		if(index==getSelectedIndex()){
			rg.at(0).get().setSelected(true);
		}
		for(int i=0;i<rg.size();i++){
			rg.at(i).get().setRBIndex(i);
			if(rg.at(i).get().isSelected()){
				setSelectedIndex(rg.at(i).get().getRBIndex());
			}
		}//Reorder indexes
	}
	void RadioGroup::setSelectedIndex(int index){
		selectedindex=index;
		for(int i=0;i<rg.size();i++){
			if(rg.at(i).get().getRBIndex()!=index){
				rg.at(i).get().setSelected(false);
			}
		}
	}
	int RadioGroup::getSelectedIndex(){
		return selectedindex;
	}
	void ToggleGroup::add(ToggleButton& tb){
		tg.push_back(tb);
		tb.setTBIndex(tg.size()-1);
	}
	void ToggleGroup::remove(int index){
		int i=index;
		tg.erase(tg.begin()+i);
		if(index==getSelectedIndex()){
			tg.at(0).get().setSelected(true);
		}
		for(int i=0;i<tg.size();i++){
			tg.at(i).get().setTBIndex(i);
			if(tg.at(i).get().isSelected()){
				setSelectedIndex(tg.at(i).get().getTBIndex());
			}
		}//Reorder indexes
	}
	void ToggleGroup::setSelectedIndex(int index){
		selectedindex=index;
		for(int i=0;i<tg.size();i++){
			if(tg.at(i).get().getTBIndex()!=index){
				tg.at(i).get().setSelected(false);
			}
		}
	}
	int ToggleGroup::getSelectedIndex(){
		return selectedindex;
	}
	TextLabel::TextLabel(wchar_t* text){
		states.push_back(NONE);
		TextLabel::text=text;
		setForeground(0.f,0.f,0.f);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
	}
	void TextLabel::draw(std::shared_ptr<D2DHandle>& d2d){
		switch(getHorizontalTextAlignment()){
		case HorizontalConstants::LEFT:
			d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			break;
		case HorizontalConstants::CENTER_HORIZONTAL:
			d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			break;
		case HorizontalConstants::RIGHT:
			d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
			break;
		}
		switch(getVerticalTextAlignment()){
		case VerticalConstants::TOP:
			d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			break;
		case VerticalConstants::CENTER_VERTICAL:
			d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			break;
		case VerticalConstants::BOTTOM:
			d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
			break;
		}
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
		std::wstring wtext(getText());
		d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
		DWRITE_TEXT_RANGE rng;
		rng.startPosition=0;
		rng.length=wtext.length();
		d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
		d2d->textlayout->SetFontFamilyName(font,rng);
		d2d->textlayout->SetLocaleName(locale,rng);
		d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
	}
	TextBox::TextBox(wchar_t* text){
		states.push_back(NONE);
		TextBox::text=text;
		setHorizontalTextAlignment(HorizontalConstants::LEFT);
		setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		setForeground(0,0,0);
		setTextSize(12.0f);
		setFont(L"MS Gothic");
	}
	void TextBox::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isEnabled()){
			if(hasFocus()){
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\textbox_focus.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				std::wstring wtext(getText());
				switch(getVerticalTextAlignment()){
				case VerticalConstants::TOP:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					break;
				case VerticalConstants::CENTER_VERTICAL:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					break;
				case VerticalConstants::BOTTOM:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
					break;
				}
				switch(getHorizontalTextAlignment()){
				case HorizontalConstants::LEFT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					break;
				case HorizontalConstants::CENTER_HORIZONTAL:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					break;
				case HorizontalConstants::RIGHT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					break;
				}
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				d2d->textlayout->SetFontFamilyName(font,rng);
				d2d->textlayout->SetLocaleName(locale,rng);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				d2d->textlayout.CopyTo(textlayout.ReleaseAndGetAddressOf());
				if(&caretRect!=NULL){
					d2d->solidbrush->SetColor(ColorF(ColorF::Chocolate,opacity));
					d2d->target->FillRectangle(RectF(caretRect.left,caretRect.top,caretRect.right,caretRect.bottom),d2d->solidbrush.Get());
				}
			}
			else{
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\textbox.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				std::wstring wtext(getText());
				switch(getVerticalTextAlignment()){
				case VerticalConstants::TOP:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					break;
				case VerticalConstants::CENTER_VERTICAL:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					break;
				case VerticalConstants::BOTTOM:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
					break;
				}
				switch(getHorizontalTextAlignment()){
				case HorizontalConstants::LEFT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					break;
				case HorizontalConstants::CENTER_HORIZONTAL:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					break;
				case HorizontalConstants::RIGHT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					break;
				}
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				d2d->textlayout->SetFontFamilyName(font,rng);
				d2d->textlayout->SetLocaleName(locale,rng);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				d2d->textlayout.CopyTo(textlayout.ReleaseAndGetAddressOf());
			}
		}
		else{
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\textbox_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
			std::wstring wtext(getText());
			switch(getVerticalTextAlignment()){
			case VerticalConstants::TOP:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				break;
			case VerticalConstants::CENTER_VERTICAL:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				break;
			case VerticalConstants::BOTTOM:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				break;
			}
			switch(getHorizontalTextAlignment()){
			case HorizontalConstants::LEFT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				break;
			case HorizontalConstants::CENTER_HORIZONTAL:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				break;
			case HorizontalConstants::RIGHT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				break;
			}
			d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
			DWRITE_TEXT_RANGE rng;
			rng.startPosition=0;
			rng.length=wtext.length();
			d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
			d2d->textlayout->SetFontFamilyName(font,rng);
			d2d->textlayout->SetLocaleName(locale,rng);
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
			d2d->textlayout.CopyTo(textlayout.ReleaseAndGetAddressOf());
		}
	}
	Button::Button(wchar_t* text){
		Button::text=text;
		setForeground(0.f,0.f,0.f);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
	}
	Button::Button(wchar_t* text,wchar_t* icon){
		Button::text=text;
		Button::icon=icon;
		setForeground(0.f,0.f,0.f);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
	}
	void Button::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isEnabled()){
			if(isPressed()){
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\button_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				std::wstring wtext(getText());
				switch(getVerticalTextAlignment()){
				case VerticalConstants::TOP:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					break;
				case VerticalConstants::CENTER_VERTICAL:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					break;
				case VerticalConstants::BOTTOM:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
					break;
				}
				switch(getHorizontalTextAlignment()){
				case HorizontalConstants::LEFT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					break;
				case HorizontalConstants::CENTER_HORIZONTAL:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					break;
				case HorizontalConstants::RIGHT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					break;
				}
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				d2d->textlayout->SetFontFamilyName(font,rng);
				d2d->textlayout->SetLocaleName(locale,rng);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
			}//Pressed button
			else if(isHovered()){
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\button_hovered.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				std::wstring wtext(getText());
				switch(getVerticalTextAlignment()){
				case VerticalConstants::TOP:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					break;
				case VerticalConstants::CENTER_VERTICAL:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					break;
				case VerticalConstants::BOTTOM:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
					break;
				}
				switch(getHorizontalTextAlignment()){
				case HorizontalConstants::LEFT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					break;
				case HorizontalConstants::CENTER_HORIZONTAL:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					break;
				case HorizontalConstants::RIGHT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					break;
				}
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				d2d->textlayout->SetFontFamilyName(font,rng);
				d2d->textlayout->SetLocaleName(locale,rng);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
			}//Hovered button
			else{
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\button.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				std::wstring wtext(getText());
				switch(getVerticalTextAlignment()){
				case VerticalConstants::TOP:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					break;
				case VerticalConstants::CENTER_VERTICAL:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					break;
				case VerticalConstants::BOTTOM:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
					break;
				}
				switch(getHorizontalTextAlignment()){
				case HorizontalConstants::LEFT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					break;
				case HorizontalConstants::CENTER_HORIZONTAL:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					break;
				case HorizontalConstants::RIGHT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					break;
				}
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				d2d->textlayout->SetFontFamilyName(font,rng);
				d2d->textlayout->SetLocaleName(locale,rng);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
			}//Normal button
		}//Enabled button
		else{
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\button_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
			std::wstring wtext(getText());
			switch(getVerticalTextAlignment()){
			case VerticalConstants::TOP:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				break;
			case VerticalConstants::CENTER_VERTICAL:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				break;
			case VerticalConstants::BOTTOM:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				break;
			}
			switch(getHorizontalTextAlignment()){
			case HorizontalConstants::LEFT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				break;
			case HorizontalConstants::CENTER_HORIZONTAL:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				break;
			case HorizontalConstants::RIGHT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				break;
			}
			d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
			DWRITE_TEXT_RANGE rng;
			rng.startPosition=0;
			rng.length=wtext.length();
			d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
			d2d->textlayout->SetFontFamilyName(font,rng);
			d2d->textlayout->SetLocaleName(locale,rng);
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
		}
	}
	ArrowButton::ArrowButton(ArrowButton_Type type,ArrowButton_Direction dir):Button(){
		ArrowButton::parentContainer=type;
		ArrowButton::direction=dir;
	}
	void ArrowButton::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isEnabled()){
			if(isPressed()){
				if(parentContainer==SPINNER){
					if(direction==UP){
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_pressed_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());	
					}
					else{
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_pressed_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					}
				}//Spinner
				else{
					if(direction==UP){
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_pressed_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					}
					else{
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_pressed_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					}
				}//ComboBox
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}//Pressed enabled ArrowButton
			else if(isHovered()){
				if(parentContainer==SPINNER){
					if(direction==UP){
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_hovered_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					}
					else{
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_hovered_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					}
				}//Spinner
				else{
					if(direction==UP){
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_hovered_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					}
					else{
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_hovered_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					}
				}//ComboBox
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}//Hovered enabled ArrowButton
			else{
				if(parentContainer==SPINNER){
					if(direction==UP){
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					}
					else{
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					}
				}//Spinner
				else{
					if(direction==UP){
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					}
					else{
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					}
				}//ComboBox
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}//Normal enabled ArrowButton
		}//Enabled ArrowButton
		else{
			if(parentContainer==SPINNER){
				if(direction==UP){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_disabled_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				}
				else{
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_disabled_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				}
			}//Spinner
			else{
				if(direction==UP){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_disabled_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				}
				else{
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_disabled_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				}
			}//ComboBox
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
			d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
		}//Disabled ArrowButton
	}
	Spinner::Spinner(int minValue,int maxValue,int value){
		Spinner::minValue=minValue;
		Spinner::maxValue=maxValue;
		Spinner::value=value;
		states.push_back(NONE);
		std::wstring wtext(L"");
		wtext+=std::to_wstring(value);
		wchar_t* text=new wchar_t[wtext.length()];
		wcscpy(text,wtext.c_str());
		valuemodifier=std::shared_ptr<TextBox>(new TextBox(text));
		up=std::shared_ptr<ArrowButton>(new ArrowButton(SPINNER,UP));
		down=std::shared_ptr<ArrowButton>(new ArrowButton(SPINNER,DOWN));
		setFont(L"Microsoft Sans Serif");
		setTextSize(12.0f);
		setForeground(0,0,0);
	}
	void Spinner::setTextSize(float px){
		WindowBase::setTextSize(px);
		valuemodifier->setTextSize(px);
	}
	void Spinner::setForeground(int R,int G,int B,int A){
		WindowBase::setForeground(R,G,B,A);
		valuemodifier->setForeground(R,G,B,A);
	}
	void Spinner::setForeground(float R,float G,float B,float A){
		WindowBase::setForeground(R,G,B,A);
		valuemodifier->setForeground(R,G,B,A);
	}
	void Spinner::setFont(wchar_t* font){
		WindowBase::setFont(font);
		valuemodifier->setFont(font);
	}
	void Spinner::setPadding(int left,int top,int right,int bottom){
		WindowBase::setPadding(left,top,right,bottom);
		valuemodifier->setPadding(left,top,right,bottom);
	}
	void Spinner::setEnabled(bool enabled){
		WindowBase::setEnabled(enabled);
		valuemodifier->setEnabled(enabled);
		up->setEnabled(enabled);
		down->setEnabled(enabled);
	}
	void Spinner::setVisible(bool visible){
		WindowBase::setVisible(visible);
		valuemodifier->setVisible(visible);
		up->setVisible(visible);
		down->setVisible(visible);
	}
	void Spinner::setBounds(int left,int top,int right,int bottom){
		WindowBase::setBounds(left,top,right,bottom);
		valuemodifier->setBounds(bounds.left,bounds.top,bounds.right-30,bounds.bottom);
		up->setBounds(bounds.right-30,bounds.top,bounds.right,bounds.top+((bounds.bottom-bounds.top)/2));
		down->setBounds(bounds.right-30,bounds.top+((bounds.bottom-bounds.top)/2),bounds.right,bounds.bottom);
	}
	void Spinner::setHorizontalTextAlignment(const int H){
		WindowBase::setHorizontalTextAlignment(H);
		valuemodifier->setHorizontalTextAlignment(H);
	}
	void Spinner::setVerticalTextAlignment(const int V){
		WindowBase::setVerticalTextAlignment(V);
		valuemodifier->setVerticalTextAlignment(V);
	}
	void Spinner::setEditable(bool editable){
		WindowBase::setEditable(editable);
		valuemodifier->setEditable(editable);
	}
	void Spinner::setFocus(bool focus){
		WindowBase::setFocus(focus);
		valuemodifier->setFocus(focus);
	}
	void Spinner::setValue(int value){
		Spinner::value=value;
		std::wstring wtext=std::to_wstring(value);
		wchar_t* text=new wchar_t[wtext.length()];
		wcscpy(text,wtext.c_str());
		valuemodifier->setText(text);
	}
	int Spinner::getValue(){
		return value;
	}
	void Spinner::setMaximumValue(int maximumValue){
		Spinner::maxValue=maximumValue;
	}
	int Spinner::getMaximumValue(){
		return maxValue;
	}
	void Spinner::setMinimumValue(int minimumValue){
		Spinner::minValue=minimumValue;
	}
	int Spinner::getMinimumValue(){
		return minValue;
	}
	void Spinner::setLocale(wchar_t* locale){
		WindowBase::setLocale(locale);
		up->setLocale(locale);
		down->setLocale(locale);
		valuemodifier->setLocale(locale);
	}
	void Spinner::setOpacity(float opacity){
		WindowBase::setOpacity(opacity);
		up->setOpacity(opacity);
		down->setOpacity(opacity);
		valuemodifier->setOpacity(opacity);
	}
	void Spinner::draw(std::shared_ptr<D2DHandle>& d2d){
		if(value==maxValue){
			up->setEnabled(false);
		}
		else if(value>maxValue){
			setValue(maxValue);
		}
		else{
			up->setEnabled(true);
		}
		if(value==minValue){
			down->setEnabled(false);
		}
		else if(value<minValue){
			setValue(minValue);
		}
		else{
			down->setEnabled(true);
		}
		valuemodifier->draw(d2d);
		up->draw(d2d);
		down->draw(d2d);
	}
	CheckBox::CheckBox(bool checked,wchar_t* text){
		states.push_back(NONE);
		setChecked(checked);
		CheckBox::text=text;
		setForeground(0,0,0);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
	}
	void CheckBox::draw(std::shared_ptr<D2DHandle>& d2d){
		HRESULT hr=S_OK;
		if(isEnabled()){
			if(isChecked()){
				if(isPressed()){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_pressed_checked.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					std::wstring wtext(getText());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getBottomPadding()-getTopPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Pressed and checked checkbox
				else if(isHovered()){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_hovered_checked.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					std::wstring wtext(getText());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Hovered and checked checkbox
				else{
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_checked.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					std::wstring wtext(getText());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Normal checked checkbox
			}//Checked checkbox
			else{
				if(isPressed()){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					std::wstring wtext(getText());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Pressed checkbox
				else if(isHovered()){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_hovered.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					std::wstring wtext(getText());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Hovered checkbox
				else{
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					std::wstring wtext(getText());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Normal checkbox
			}//Unchecked checkbox
		}//Enabled checkbox
		else{
			if(isChecked()){
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_disabled_checked.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				std::wstring wtext(getText());
				switch(getVerticalTextAlignment()){
				case VerticalConstants::TOP:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					break;
				case VerticalConstants::CENTER_VERTICAL:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					break;
				case VerticalConstants::BOTTOM:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
					break;
				}
				switch(getHorizontalTextAlignment()){
				case HorizontalConstants::LEFT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					break;
				case HorizontalConstants::CENTER_HORIZONTAL:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					break;
				case HorizontalConstants::RIGHT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					break;
				}
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				d2d->textlayout->SetFontFamilyName(font,rng);
				d2d->textlayout->SetLocaleName(locale,rng);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
			}
			else{
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				std::wstring wtext(getText());
				switch(getVerticalTextAlignment()){
				case VerticalConstants::TOP:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					break;
				case VerticalConstants::CENTER_VERTICAL:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					break;
				case VerticalConstants::BOTTOM:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
					break;
				}
				switch(getHorizontalTextAlignment()){
				case HorizontalConstants::LEFT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					break;
				case HorizontalConstants::CENTER_HORIZONTAL:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					break;
				case HorizontalConstants::RIGHT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					break;
				}
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				d2d->textlayout->SetFontFamilyName(font,rng);
				d2d->textlayout->SetLocaleName(locale,rng);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
			}//Normal disabled checkbox
		}//Disabled checkbox
	}
	DialogueBox::DialogueBox(wchar_t* text):TextLabel(text){
		decorationfile=NULL;
	}
	void DialogueBox::setDecoration(wchar_t* file,DIALOGUEBOX_DECORATION_LEVEL decorationlevel,float opacity){
		decorationfile=file;
		DialogueBox::decorationlevel=decorationlevel;
		decorationopacity=opacity;
	}
	void DialogueBox::setDecorationBounds(int left,int top,int right,int bottom){
		decorationbounds.left=left;
		decorationbounds.top=top;
		decorationbounds.right=right;
		decorationbounds.bottom=bottom;
	}
	wchar_t* DialogueBox::getDecoration(){
		return decorationfile;
	}
	DIALOGUEBOX_DECORATION_LEVEL DialogueBox::getDecorationLevel(){
		return decorationlevel;
	}
	float DialogueBox::getDecorationOpacity(){
		return decorationopacity;
	}
	RECT DialogueBox::getDecorationBounds(){
		return decorationbounds;
	}
	void DialogueBox::setTextShadow(bool shadow){
		shadowenabled=shadow;
	}
	bool DialogueBox::hasTextShadow(){
		return shadowenabled;
	}
	void DialogueBox::draw(std::shared_ptr<D2DHandle>& d2d){
		if(&decorationfile!=NULL){
			d2d->imgfactory->CreateDecoderFromFilename(decorationfile,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getDecorationBounds().bottom-getDecorationBounds().top,getDecorationBounds().bottom-getDecorationBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
		}
		if(&decorationfile!=NULL&&getDecorationLevel()==DECORATIONBELOWDIALOGUEBOX){
			d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getDecorationBounds().left,(float)getDecorationBounds().top,(float)getDecorationBounds().right,(float)getDecorationBounds().bottom),decorationopacity);
		}
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA_bg[0],fRGBA_bg[1],fRGBA_bg[2],fRGBA_bg[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),d2d->solidbrush.Get());
		if(&decorationfile!=NULL&&getDecorationLevel()==DECORATIONOVERDIALOGUEBOX){
			d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getDecorationBounds().left,(float)getDecorationBounds().top,(float)getDecorationBounds().right,(float)getDecorationBounds().bottom),decorationopacity);
		}
		std::wstring wtext(getText());
		switch(getHorizontalTextAlignment()){
		case HorizontalConstants::LEFT:
			d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			break;
		case HorizontalConstants::CENTER_HORIZONTAL:
			d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			break;
		case HorizontalConstants::RIGHT:
			d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
			break;
		}
		switch(getVerticalTextAlignment()){
		case VerticalConstants::TOP:
			d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			break;
		case VerticalConstants::CENTER_VERTICAL:
			d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			break;
		case VerticalConstants::BOTTOM:
			d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
			break;
		}
		d2d->solidbrush->SetColor(ColorF(ColorF::Black,0.5f));
		d2d->dwritefactory->CreateTextLayout(wtext.c_str(),showedcharacters,d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
		DWRITE_TEXT_RANGE rng;
		rng.startPosition=0;
		rng.length=wtext.length();
		d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
		d2d->textlayout->SetFontFamilyName(font,rng);
		d2d->textlayout->SetLocaleName(locale,rng);
		d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
		d2d->solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity));
		d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
	}
	RadioButton::RadioButton(RadioGroup& parent,bool selected,wchar_t* text): rgParent(parent){
		setParent(parent);
		setSelected(selected);
		RadioButton::text=text;
		setForeground(0,0,0);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
	}
	void RadioButton::setRBIndex(int index){
		rbIndex=index;
	}
	int RadioButton::getRBIndex(){
		return rbIndex;
	}
	void RadioButton::setParent(RadioGroup& rg){
		rgParent=rg;
		parent.add(*this);
	}
	void RadioButton::setTag(wchar_t* tag){
		RadioButton::tag=tag;
	}
	wchar_t* RadioButton::getTag(){
		return tag;
	}
	RadioGroup& RadioButton::getParent(){
		return rgParent;
	}
	void RadioButton::removeParent(RadioGroup& rg){
		rgParent.remove(this->getIndex());
		setIndex(-1);
	}
	void RadioButton::draw(std::shared_ptr<D2DHandle>& d2d){
		std::wstring wtext(getText());
		if(isEnabled()){
			if(isSelected()){
				if(isPressed()){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_pressed_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Pressed and selected radiobutton
				else if(isHovered()){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_hovered_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Hovered and selected radiobutton
				else{
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Normal selected radiobutton
			}//Selected radiobutton
			else{
				if(isPressed()){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Pressed radiobutton
				else if(isHovered()){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_hovered.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Hovered radiobutton
				else{
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Normal enabled radiobutton
			}//Unselected radiobutton
		}//Enabled radiobutton
		else{
			if(isSelected()){
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_disabled_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				switch(getVerticalTextAlignment()){
				case VerticalConstants::TOP:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					break;
				case VerticalConstants::CENTER_VERTICAL:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					break;
				case VerticalConstants::BOTTOM:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
					break;
				}
				switch(getHorizontalTextAlignment()){
				case HorizontalConstants::LEFT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					break;
				case HorizontalConstants::CENTER_HORIZONTAL:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					break;
				case HorizontalConstants::RIGHT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					break;
				}
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				d2d->textlayout->SetFontFamilyName(font,rng);
				d2d->textlayout->SetLocaleName(locale,rng);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
			}//Selected disabled radiobutton
			else{
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				switch(getVerticalTextAlignment()){
				case VerticalConstants::TOP:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					break;
				case VerticalConstants::CENTER_VERTICAL:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					break;
				case VerticalConstants::BOTTOM:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
					break;
				}
				switch(getHorizontalTextAlignment()){
				case HorizontalConstants::LEFT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					break;
				case HorizontalConstants::CENTER_HORIZONTAL:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					break;
				case HorizontalConstants::RIGHT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					break;
				}
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				d2d->textlayout->SetFontFamilyName(font,rng);
				d2d->textlayout->SetLocaleName(locale,rng);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
			}//Unselected disabled radiobutton
		}//Disabled radiobutton
	}
	ToggleButton::ToggleButton(ToggleGroup& parent,bool selected,wchar_t* text,wchar_t* icon):WindowBase(),tgParent(parent){
		setParent(parent);
		ToggleButton::text=text;
		ToggleButton::icon=icon;
		setForeground(0,0,0);
		setTextSize(12.0f);
		setSelected(selected);
		setFont(L"Microsoft Sans Serif");
	}
	void ToggleButton::setTBIndex(int index){
		tbIndex=index;
	}
	int ToggleButton::getTBIndex(){
		return tbIndex;
	}
	void ToggleButton::setParent(ToggleGroup& rg){
		tgParent=rg;
		parent.add(*this);
	}
	ToggleGroup& ToggleButton::getParent(){
		return tgParent;
	}
	void ToggleButton::removeParent(ToggleGroup& rg){
		tgParent.remove(this->getIndex());
		setIndex(-1);
	}
	void ToggleButton::draw(std::shared_ptr<D2DHandle>& d2d){ //DrawText measuring are just magic numbers made to fit the image proportions. Use your own proportions when using another image.
		if(isEnabled()){
			if(isSelected()){
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				std::wstring wtext(getText());
				switch(getVerticalTextAlignment()){
				case VerticalConstants::TOP:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					break;
				case VerticalConstants::CENTER_VERTICAL:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					break;
				case VerticalConstants::BOTTOM:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
					break;
				}
				switch(getHorizontalTextAlignment()){
				case HorizontalConstants::LEFT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					break;
				case HorizontalConstants::CENTER_HORIZONTAL:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					break;
				case HorizontalConstants::RIGHT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					break;
				}
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				d2d->target->CreateSolidColorBrush(ColorF(ToggleButton::fRGBA[0],ToggleButton::fRGBA[1],ToggleButton::fRGBA[2],ToggleButton::fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				d2d->textlayout->SetFontFamilyName(font,rng);
				d2d->textlayout->SetLocaleName(locale,rng);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
			}//Selected ToggleButton
			else{
				if(isPressed()){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					std::wstring wtext(getText());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(ToggleButton::fRGBA[0],ToggleButton::fRGBA[1],ToggleButton::fRGBA[2],ToggleButton::fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Pressed ToggleButton
				else if(isHovered()){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton_hovered.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
					d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					std::wstring wtext(getText());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(ToggleButton::fRGBA[0],ToggleButton::fRGBA[1],ToggleButton::fRGBA[2],ToggleButton::fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Hovered ToggleButton
				else{
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
					d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
					d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
					std::wstring wtext(getText());
					switch(getVerticalTextAlignment()){
					case VerticalConstants::TOP:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
						break;
					case VerticalConstants::CENTER_VERTICAL:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
						break;
					case VerticalConstants::BOTTOM:
						d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
						break;
					}
					switch(getHorizontalTextAlignment()){
					case HorizontalConstants::LEFT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
						break;
					case HorizontalConstants::CENTER_HORIZONTAL:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
						break;
					case HorizontalConstants::RIGHT:
						d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
						break;
					}
					d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
					d2d->target->CreateSolidColorBrush(ColorF(ToggleButton::fRGBA[0],ToggleButton::fRGBA[1],ToggleButton::fRGBA[2],ToggleButton::fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
					d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
					DWRITE_TEXT_RANGE rng;
					rng.startPosition=0;
					rng.length=wtext.length();
					d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
					d2d->textlayout->SetFontFamilyName(font,rng);
					d2d->textlayout->SetLocaleName(locale,rng);
					d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
				}//Normal ToggleButton
			}//Unselected ToggleButton
		}//Enabled ToggleButton
		else{
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
			std::wstring wtext(getText());
			switch(getVerticalTextAlignment()){
			case VerticalConstants::TOP:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				break;
			case VerticalConstants::CENTER_VERTICAL:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				break;
			case VerticalConstants::BOTTOM:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				break;
			}
			switch(getHorizontalTextAlignment()){
			case HorizontalConstants::LEFT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				break;
			case HorizontalConstants::CENTER_HORIZONTAL:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				break;
			case HorizontalConstants::RIGHT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				break;
			}
			d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			d2d->target->CreateSolidColorBrush(ColorF(ToggleButton::fRGBA[0],ToggleButton::fRGBA[1],ToggleButton::fRGBA[2],ToggleButton::fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
			DWRITE_TEXT_RANGE rng;
			rng.startPosition=0;
			rng.length=wtext.length();
			d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
			d2d->textlayout->SetFontFamilyName(font,rng);
			d2d->textlayout->SetLocaleName(locale,rng);
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
		}//Disabled ToggleButton
	}

	ImageView::ImageView(wchar_t* file){
		ImageView::path=file;
		states.push_back(NONE);
	}
	void ImageView::setFile(wchar_t* file){
		path=file;
	}
	wchar_t* ImageView::getFilePath(){
		return path;
	}
	void ImageView::draw(std::shared_ptr<D2DHandle>& d2d){
		d2d->imgfactory->CreateDecoderFromFilename(getFilePath(),NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
		d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
	}
	void GifView::setLoop(bool loop){
		this->loop=loop;
	}
	bool GifView::isLooping(){
		return loop;
	}
	int GifView::getCurrentFrame(){
		return currentframe;
	}
	void GifView::draw(std::shared_ptr<D2DHandle> d2d){
		d2d->imgfactory->CreateDecoderFromFilename(getFilePath(),NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		unsigned int totalframes;
		d2d->bmpdecoder->GetFrameCount(&totalframes);
		d2d->bmpdecoder->GetFrame(currentframe,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
		d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
		if(currentframe<(totalframes-1)){
			currentframe++;
		}
		else{
			if(loop)currentframe=0;
		}
	}
	ImageButton::ImageButton(wchar_t* file,wchar_t* text){
		disabledpath=pressedpath=hoveredpath=enabledpath=file;
		this->text=text;
		setForeground(0,0,0);
		setTextSize(12.0f);
		setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
		setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		setFont(L"Microsoft Sans Serif");
	}
	ImageButton::ImageButton(wchar_t* enabledfile,wchar_t* disabledfile,wchar_t* pressedfile,wchar_t* hoveredfile,wchar_t* text){
		enabledpath=enabledfile;
		disabledpath=disabledfile;
		pressedpath=pressedfile;
		hoveredpath=hoveredfile;
		states.push_back(NONE);
		this->text=text;
		setForeground(0,0,0);
		setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
		setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
	}
	void ImageButton::draw(std::shared_ptr<D2DHandle>& d2d){
		std::wstring wtext(getText());
		if(isEnabled()){
			if(isPressed()&&(wcscmp(pressedpath,L"")!=0)){
				d2d->imgfactory->CreateDecoderFromFilename(pressedpath,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				switch(getHorizontalTextAlignment()){
				case HorizontalConstants::LEFT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					break;
				case HorizontalConstants::CENTER_HORIZONTAL:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					break;
				case HorizontalConstants::RIGHT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					break;
				}
				switch(getVerticalTextAlignment()){
				case VerticalConstants::TOP:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					break;
				case VerticalConstants::CENTER_VERTICAL:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					break;
				case VerticalConstants::BOTTOM:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
					break;
				}
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				d2d->textlayout->SetFontFamilyName(font,rng);
				d2d->textlayout->SetLocaleName(locale,rng);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
			}//Pressed ImageButton
			else if(isHovered()&&(wcscmp(hoveredpath,L"")!=0)){
				d2d->imgfactory->CreateDecoderFromFilename(hoveredpath,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				switch(getHorizontalTextAlignment()){
				case HorizontalConstants::LEFT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					break;
				case HorizontalConstants::CENTER_HORIZONTAL:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					break;
				case HorizontalConstants::RIGHT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					break;
				}
				switch(getVerticalTextAlignment()){
				case VerticalConstants::TOP:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					break;
				case VerticalConstants::CENTER_VERTICAL:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					break;
				case VerticalConstants::BOTTOM:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
					break;
				}
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				d2d->textlayout->SetFontFamilyName(font,rng);
				d2d->textlayout->SetLocaleName(locale,rng);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
			}//Hovered ImageButton
			else if(wcscmp(enabledpath,L"")!=0){
				d2d->imgfactory->CreateDecoderFromFilename(enabledpath,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				switch(getHorizontalTextAlignment()){
				case HorizontalConstants::LEFT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					break;
				case HorizontalConstants::CENTER_HORIZONTAL:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					break;
				case HorizontalConstants::RIGHT:
					d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
					break;
				}
				switch(getVerticalTextAlignment()){
				case VerticalConstants::TOP:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					break;
				case VerticalConstants::CENTER_VERTICAL:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
					break;
				case VerticalConstants::BOTTOM:
					d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
					break;
				}
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				d2d->textlayout->SetFontFamilyName(font,rng);
				d2d->textlayout->SetLocaleName(locale,rng);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
			}//Normal enabled ImageButton
		}//Enabled ImageButton
		else if(wcscmp(disabledpath,L"")!=0){
			d2d->imgfactory->CreateDecoderFromFilename(disabledpath,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
			d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			switch(getHorizontalTextAlignment()){
			case HorizontalConstants::LEFT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				break;
			case HorizontalConstants::CENTER_HORIZONTAL:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				break;
			case HorizontalConstants::RIGHT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				break;
			}
			switch(getVerticalTextAlignment()){
			case VerticalConstants::TOP:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				break;
			case VerticalConstants::CENTER_VERTICAL:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				break;
			case VerticalConstants::BOTTOM:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				break;
			}
			d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
			DWRITE_TEXT_RANGE rng;
			rng.startPosition=0;
			rng.length=wtext.length();
			d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
			d2d->textlayout->SetFontFamilyName(font,rng);
			d2d->textlayout->SetLocaleName(locale,rng);
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
		}//Disabled ImageButton
	}
	template<> bool ListItem<wchar_t*>::isString(){
		if(typeid(wchar_t*)==typeid(t)){
			return true;
		}
		else{
			return false;
		}
	}
	template<> bool ListItem<wchar_t*>::isFile(){
		if(typeid(newifstream)==typeid(t)){
			return true;
		}
		else{
			return false;
		}
	}
	template<> bool ListItem<newifstream>::isString(){
		if(typeid(wchar_t*)==typeid(t)){
			return true;
		}
		else{
			return false;
		}
	}
	template<> bool ListItem<newifstream>::isFile(){
		if(typeid(newifstream)==typeid(t)){
			return true;
		}
		else{
			return false;
		}
	}
	template<> wchar_t* ListItem<wchar_t*>::getFont(){
		return font;
	}
	template<> wchar_t* ListItem<newifstream>::getFont(){
		return font;
	}
	template<> void ListItem<wchar_t*>::setFont(wchar_t* font){
		ListItem::font=font;
	}
	template<> void ListItem<newifstream>::setFont(wchar_t* font){
		ListItem::font=font;
	}
	template<> wchar_t* ListItem<wchar_t*>::getIcon(){
		return icon;
	}
	template<> wchar_t* ListItem<newifstream>::getIcon(){
		return icon;
	}
	template<> void ListItem<wchar_t*>::setIcon(wchar_t* icon){
		ListItem::icon=icon;
	}
	template<> void ListItem<newifstream>::setIcon(wchar_t* icon){
		ListItem::icon=icon;
	}
	template<> float ListItem<wchar_t*>::getTextSize(){
		return textSize;
	}
	template<> float ListItem<newifstream>::getTextSize(){

		return textSize;
	}
	template<> void ListItem<wchar_t*>::setTextSize(float px){
		ListItem::textSize=px;
	}
	template<> void ListItem<newifstream>::setTextSize(float px){
		ListItem::textSize=px;
	}
	template<> wchar_t*& ListItem<wchar_t*>::getData(){
		if(isString()){
			return t;
		}
		else{
			return (wchar_t*&)(L"");
		}
	}
	template<> newifstream& ListItem<newifstream>::getData(){
		if(isFile()){
			return t;
		}
	}
	template<> wchar_t* ListItem<wchar_t*>::getTag(){
		wchar_t* nonconsttag=new wchar_t[wcslen(tag)];
		wcscpy(nonconsttag,tag);
		return nonconsttag;
	}
	template<> wchar_t* ListItem<newifstream>::getTag(){
		wchar_t* nonconsttag=new wchar_t[wcslen(tag)];
		wcscpy(nonconsttag,tag);
		return nonconsttag;
	}
	template<> void ListItem<wchar_t*>::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
	}
	template<> void ListItem<newifstream>::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
	}
	template<> RECT ListItem<wchar_t*>::getBounds(){
		return bounds;
	}
	template<> RECT ListItem<newifstream>::getBounds(){
		return bounds;
	}
	template<> void ListItem<wchar_t*>::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==ENABLED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates){
				states.push_back(ENABLED);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==ENABLED){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	template<> void ListItem<newifstream>::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==ENABLED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates){
				states.push_back(ENABLED);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==ENABLED){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	template<> bool ListItem<wchar_t*>::isEnabled(){
		bool enabled=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==ENABLED){
					enabled=true;
					break;
				}
			}
		}	
		return enabled;
	}
	template<> bool ListItem<newifstream>::isEnabled(){
		bool enabled=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==ENABLED){
					enabled=true;
					break;
				}
			}
		}	
		return enabled;
	}
	template<> void ListItem<wchar_t*>::setPressed(bool pressed){
		bool foundinstates=false;
		if(pressed){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==PRESSED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates){
				states.push_back(PRESSED);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==PRESSED){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	template<> void ListItem<newifstream>::setPressed(bool pressed){
		bool foundinstates=false;
		if(pressed){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==PRESSED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates){
				states.push_back(PRESSED);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==PRESSED){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	template<> bool ListItem<wchar_t*>::isPressed(){
		bool pressed=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==PRESSED){
					pressed=true;
					break;
				}
			}
		}
		return pressed;
	}
	template<> bool ListItem<newifstream>::isPressed(){
		bool pressed=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==PRESSED){
					pressed=true;
					break;
				}
			}
		}
		return pressed;
	}
	template<> void ListItem<wchar_t*>::setHovered(bool hovered){
		bool foundinstates=false;
		if(hovered){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==HOVERED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates){
				states.push_back(HOVERED);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==HOVERED){
						states.erase(states.begin()+i);
						break;
					}
				}
			}		
		}
	}
	template<> void ListItem<newifstream>::setHovered(bool hovered){
		bool foundinstates=false;
		if(hovered){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==HOVERED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates){
				states.push_back(HOVERED);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==HOVERED){
						states.erase(states.begin()+i);
						break;
					}
				}
			}		
		}
	}
	template<> bool ListItem<wchar_t*>::isHovered(){
		bool hovered=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==HOVERED){
					hovered=true;
					break;
				}
			}
		}
		return hovered;
	}
	template<> bool ListItem<newifstream>::isHovered(){
		bool hovered=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==HOVERED){
					hovered=true;
					break;
				}
			}
		}
		return hovered;
	}
	template<> void ListItem<wchar_t*>::setSelected(bool selected){
		bool foundinstates=false;
		if(selected){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==SELECTED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates){
				states.push_back(SELECTED);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==SELECTED){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	template<> void ListItem<newifstream>::setSelected(bool selected){
		bool foundinstates=false;
		if(selected){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==SELECTED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates){
				states.push_back(SELECTED);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==SELECTED){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	template<> bool ListItem<wchar_t*>::isSelected(){
		bool selected=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==SELECTED){
					selected=true;
					break;
				}
			}
		}
		return selected;
	}
	template<> bool ListItem<newifstream>::isSelected(){
		bool selected=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==SELECTED){
					selected=true;
					break;
				}
			}
		}
		return selected;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::drawDropdown(std::shared_ptr<D2DHandle>& d2d){
		d2d->target->CreateSolidColorBrush(ColorF(ColorF::White,opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
		d2d->target->FillRectangle(RectF(getBounds().left,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight()),d2d->solidbrush.Get());
		d2d->target->PushAxisAlignedClip(RectF(getBounds().left,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight()),D2D1_ANTIALIAS_MODE_ALIASED);
		float topY=(getTotalHeight()/vScrollBar->portions)*vScrollBar->position;
		d2d->target->SaveDrawingState(d2d->targetstate.Get());
		d2d->target->SetTransform(Matrix3x2F::Translation(0,-topY));
		for(int i=0;i<list.size();i++){
			if(list.at(i).isEnabled()){
				if(list.at(i).isSelected()){
					d2d->solidbrush->SetColor(ColorF(fRGBA_selected[0],fRGBA_selected[1],fRGBA_selected[2],fRGBA_selected[3]*opacity));
					d2d->target->FillRectangle(RectF(getBounds().left+list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,getBounds().left+list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.Get());
				}
				else if(list.at(i).isPressed()){
					d2d->solidbrush->SetColor(ColorF(fRGBA_pressed[0],fRGBA_pressed[1],fRGBA_pressed[2],fRGBA_pressed[3]*opacity));
					d2d->target->FillRectangle(RectF(list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.Get());
				}
				else if(list.at(i).isHovered()){
					d2d->solidbrush->SetColor(ColorF(fRGBA_hovered[0],fRGBA_hovered[1],fRGBA_hovered[2],fRGBA_hovered[3]*opacity));
					d2d->target->FillRectangle(RectF(list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.Get());
				}
			}
			else{
				d2d->solidbrush->SetColor(ColorF(fRGBA_disabled[0],fRGBA_disabled[1],fRGBA_disabled[2],fRGBA_disabled[3]*opacity));
				d2d->target->FillRectangle(RectF(list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.Get());
			}
			switch(getHorizontalTextAlignment()){
			case HorizontalConstants::LEFT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				break;
			case HorizontalConstants::CENTER_HORIZONTAL:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				break;
			case HorizontalConstants::RIGHT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				break;
			}
			switch(getVerticalTextAlignment()){
			case VerticalConstants::TOP:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				break;
			case VerticalConstants::CENTER_VERTICAL:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				break;
			case VerticalConstants::BOTTOM:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				break;
			}
			d2d->solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity));
			std::wstring wtext(list.at(i).getData());
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
			DWRITE_TEXT_RANGE rng;
			rng.startPosition=0;
			rng.length=wtext.length();
			d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
			d2d->textlayout->SetFontFamilyName(font,rng);
			d2d->textlayout->SetLocaleName(locale,rng);
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
		}
		d2d->target->PopAxisAlignedClip();
		d2d->target->RestoreDrawingState(d2d->targetstate.Get());
	}
	template<> void ComboBox<ListItem<newifstream>>::drawDropdown(std::shared_ptr<D2DHandle>& d2d){
		d2d->target->CreateSolidColorBrush(ColorF(ColorF::White,opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
		d2d->target->FillRectangle(RectF(getBounds().left,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight()),d2d->solidbrush.Get());
		d2d->target->PushAxisAlignedClip(RectF(getBounds().left,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight()),D2D1_ANTIALIAS_MODE_ALIASED);
		float topY=(getTotalHeight()/vScrollBar->portions)*vScrollBar->position;
		d2d->target->SaveDrawingState(d2d->targetstate.Get());
		d2d->target->SetTransform(Matrix3x2F::Translation(0,-topY));
		for(int i=0;i<list.size();i++){
			if(list.at(i).isEnabled()){
				if(list.at(i).isSelected()){
					d2d->solidbrush->SetColor(ColorF(fRGBA_selected[0],fRGBA_selected[1],fRGBA_selected[2],fRGBA_selected[3]*opacity));
					d2d->target->FillRectangle(RectF(getBounds().left+list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,getBounds().left+list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.Get());
				}
				else if(list.at(i).isPressed()){
					d2d->solidbrush->SetColor(ColorF(fRGBA_pressed[0],fRGBA_pressed[1],fRGBA_pressed[2],fRGBA_pressed[3]*opacity));
					d2d->target->FillRectangle(RectF(getBounds().left+list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,getBounds().left+list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.Get());
				}
				else if(list.at(i).isHovered()){
					d2d->solidbrush->SetColor(ColorF(fRGBA_hovered[0],fRGBA_hovered[1],fRGBA_hovered[2],fRGBA_hovered[3]*opacity));
					d2d->target->FillRectangle(RectF(getBounds().left+list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,getBounds().left+list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.Get());
				}
			}
			else{
				d2d->solidbrush->SetColor(ColorF(fRGBA_disabled[0],fRGBA_disabled[1],fRGBA_disabled[2],fRGBA_disabled[3]*opacity));
				d2d->target->FillRectangle(RectF(getBounds().left+list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,getBounds().left+list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.Get());
			}
			switch(getHorizontalTextAlignment()){
			case HorizontalConstants::LEFT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				break;
			case HorizontalConstants::CENTER_HORIZONTAL:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				break;
			case HorizontalConstants::RIGHT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				break;
			}
			switch(getVerticalTextAlignment()){
			case VerticalConstants::TOP:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				break;
			case VerticalConstants::CENTER_VERTICAL:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				topPadding=0;
				break;
			case VerticalConstants::BOTTOM:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				break;
			}
			d2d->solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]));
			std::wstring wtext(list.at(i).getData().getFilename());
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
			DWRITE_TEXT_RANGE rng;
			rng.startPosition=0;
			rng.length=wtext.length();
			d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
			d2d->textlayout->SetFontFamilyName(font,rng);
			d2d->textlayout->SetLocaleName(locale,rng);
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
		}
		d2d->target->PopAxisAlignedClip();
		d2d->target->RestoreDrawingState(d2d->targetstate.Get());
	}
	template<> void ComboBox<ListItem<wchar_t*>>::draw(std::shared_ptr<D2DHandle>& d2d){
		tb->draw(d2d);
		dropdown->draw(d2d);
	}
	template<> void ComboBox<ListItem<newifstream>>::draw(std::shared_ptr<D2DHandle>& d2d){
		tb->draw(d2d);
		dropdown->draw(d2d);
	}
	template<> void ListBox<ListItem<wchar_t*>>::draw(std::shared_ptr<D2DHandle>& d2d){
		if(getViewportBounds().right>getBounds().right){
			hScrollBar->enableHorizontalScrolling();
		}
		if(getTotalHeight()>(getBounds().bottom)){
			vScrollBar->enableVerticalScrolling();
		}
		setBounds(getBounds().left,getBounds().top,getBounds().right,getBounds().bottom);
		setViewportBounds(getViewportBounds().left,getViewportBounds().top,getViewportBounds().right,getViewportBounds().bottom);
		d2d->target->CreateSolidColorBrush(ColorF(ColorF::White,opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),d2d->solidbrush.Get());
		d2d->target->PushAxisAlignedClip(RectF(getViewportBounds().left,getViewportBounds().top,getBounds().right,getBounds().bottom),D2D1_ANTIALIAS_MODE_ALIASED);
		float topY=((float)(getBounds().bottom-getBounds().top)/vScrollBar->portions)*vScrollBar->position;
		float leftY=((float)(getBounds().right-getBounds().left)/hScrollBar->portions)*hScrollBar->position;
		d2d->target->SaveDrawingState(d2d->targetstate.Get());
		d2d->target->SetTransform(Matrix3x2F::Translation(-leftY,-topY));
		for(int i=0;i<list.size();i++){
			if(list.at(i).isEnabled()){
				if(list.at(i).isSelected()){
					d2d->solidbrush->SetColor(ColorF(fRGBA_selected[0],fRGBA_selected[1],fRGBA_selected[2],fRGBA_selected[3]*opacity));
				}//Selected enabled ListItem
				else if(list.at(i).isPressed()){
					d2d->solidbrush->SetColor(ColorF(fRGBA_pressed[0],fRGBA_pressed[1],fRGBA_pressed[2],fRGBA_pressed[3]*opacity));
				}//Pressed enabled ListItem
				else if(list.at(i).isHovered()){
					d2d->solidbrush->SetColor(ColorF(fRGBA_hovered[0],fRGBA_hovered[1],fRGBA_hovered[2],fRGBA_hovered[3]*opacity));
				}//Hovered enabled ListItem
			}//Enabled ListItem
			else{
				d2d->solidbrush->SetColor(ColorF(fRGBA_disabled[0],fRGBA_disabled[1],fRGBA_disabled[2],fRGBA_disabled[3]*opacity));
			}//Disabled ListItem
			d2d->target->FillRectangle(RectF((float)getBounds().left+list.at(i).getBounds().left,(float)getBounds().top+list.at(i).getBounds().top,(float)getBounds().left+list.at(i).getBounds().right,(float)getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.Get());
			d2d->solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity));
			switch(getHorizontalTextAlignment()){
			case HorizontalConstants::LEFT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				break;
			case HorizontalConstants::CENTER_HORIZONTAL:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				leftPadding=0;
				break;
			case HorizontalConstants::RIGHT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				break;
			}
			switch(getVerticalTextAlignment()){
			case VerticalConstants::TOP:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				break;
			case VerticalConstants::CENTER_VERTICAL:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				topPadding=0;
				break;
			case VerticalConstants::BOTTOM:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				break;
			}
			std::wstring wtext(list.at(i).getData());
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
			DWRITE_TEXT_RANGE rng;
			rng.startPosition=0;
			rng.length=wtext.length();
			d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
			d2d->textlayout->SetFontFamilyName(font,rng);
			d2d->textlayout->SetLocaleName(locale,rng);
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
		}
		d2d->target->RestoreDrawingState(d2d->targetstate.Get());
		d2d->target->PopAxisAlignedClip();
		if(hScrollBar->isHorizontalScrollingEnabled()){
			hScrollBar->draw(d2d);
		}
		if(vScrollBar->isVerticalScrollingEnabled()){
			vScrollBar->draw(d2d);
		}
	}
	template<> void ListBox<ListItem<newifstream>>::draw(std::shared_ptr<D2DHandle>& d2d){
		if(getViewportBounds().right>getBounds().right){
			hScrollBar->enableHorizontalScrolling();
		}
		if(getTotalHeight()>(getBounds().bottom-getBounds().top)){
			vScrollBar->enableVerticalScrolling();
		}
		setBounds(getBounds().left,getBounds().top,getBounds().right,getBounds().bottom);
		d2d->target->CreateSolidColorBrush(ColorF(ColorF::White,opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),d2d->solidbrush.Get());
		d2d->target->PushAxisAlignedClip(RectF(getViewportBounds().left,getViewportBounds().top,getBounds().right,getBounds().bottom),D2D1_ANTIALIAS_MODE_ALIASED);
		float topY=((float)(getBounds().bottom-getBounds().top)/vScrollBar->portions)*vScrollBar->position;
		float leftY=((float)(getBounds().right-getBounds().left)/hScrollBar->portions)*hScrollBar->position;
		d2d->target->SaveDrawingState(d2d->targetstate.Get());
		d2d->target->SetTransform(Matrix3x2F::Translation(-leftY,-topY));
		for(int i=0;i<list.size();i++){
			if(list.at(i).isEnabled()){
				if(list.at(i).isSelected()){
					d2d->solidbrush->SetColor(ColorF(fRGBA_selected[0],fRGBA_selected[1],fRGBA_selected[2],fRGBA_selected[3]*opacity));
				}//Selected enabled ListItem
				else if(list.at(i).isPressed()){
					d2d->solidbrush->SetColor(ColorF(fRGBA_pressed[0],fRGBA_pressed[1],fRGBA_pressed[2],fRGBA_pressed[3]*opacity));
				}//Pressed enabled ListItem
				else if(list.at(i).isHovered()){
					d2d->solidbrush->SetColor(ColorF(fRGBA_hovered[0],fRGBA_hovered[1],fRGBA_hovered[2],fRGBA_hovered[3]*opacity));
				}//Hovered enabled ListItem
			}//Enabled ListItem
			else{
				d2d->solidbrush->SetColor(ColorF(fRGBA_disabled[0],fRGBA_disabled[1],fRGBA_disabled[2],fRGBA_disabled[3]*opacity));
			}//Disabled ListItem
			d2d->target->FillRectangle(RectF((float)getBounds().left+list.at(i).getBounds().left,(float)getBounds().top+list.at(i).getBounds().top,(float)getBounds().left+list.at(i).getBounds().right,(float)getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.Get());
			d2d->solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity));
			switch(getHorizontalTextAlignment()){
			case HorizontalConstants::LEFT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				break;
			case HorizontalConstants::CENTER_HORIZONTAL:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				leftPadding=0;
				break;
			case HorizontalConstants::RIGHT:
				d2d->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				break;
			}
			switch(getVerticalTextAlignment()){
			case VerticalConstants::TOP:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				break;
			case VerticalConstants::CENTER_VERTICAL:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				topPadding=0;
				break;
			case VerticalConstants::BOTTOM:
				d2d->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				break;
			}
			std::wstring wtext(list.at(i).getData().getFilename());
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),d2d->textlayout.ReleaseAndGetAddressOf());
			DWRITE_TEXT_RANGE rng;
			rng.startPosition=0;
			rng.length=wtext.length();
			d2d->textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
			d2d->textlayout->SetFontFamilyName(font,rng);
			d2d->textlayout->SetLocaleName(locale,rng);
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.Get(),d2d->solidbrush.Get());
		}
		d2d->target->RestoreDrawingState(d2d->targetstate.Get());
		d2d->target->PopAxisAlignedClip();
		if(hScrollBar->isHorizontalScrollingEnabled()){
			hScrollBar->draw(d2d);
		}
		if(vScrollBar->isVerticalScrollingEnabled()){
			vScrollBar->draw(d2d);
		}
	}
	Slider::Slider(int minValue,int maxValue,int value,int step){
		Slider::minValue=minValue;
		Slider::maxValue=maxValue;
		Slider::value=value;
		Slider::step=step;
		states.push_back(NONE);
	}
	void Slider::setMaximumValue(int maxValue){
		Slider::maxValue=maxValue;
	}
	int Slider::getMaximumValue(){
		return maxValue;
	}
	void Slider::setMinimumValue(int minValue){
		Slider::minValue=minValue;
	}
	int Slider::getMinimumValue(){
		return minValue;
	}
	void Slider::setValue(int value){
		Slider::value=value;
	}
	int Slider::getValue(){
		return value;
	}
	void Slider::setStep(int step){
		Slider::step=step;
	}
	int Slider::getStep(){
		return step;
	}
	void Slider::draw(std::shared_ptr<D2DHandle>& d2d){
		int length=(int)((maxValue-minValue)/step);
		int size=(getBounds().bottom-getBounds().top);
		int trackheight=(size*2)/3;
		int pad=(size*1)/3;
		d2d->target->CreateSolidColorBrush(ColorF(ColorF::LightGray,opacity),d2d->solidbrush.ReleaseAndGetAddressOf());
		int top=getBounds().top+((size/2)-(trackheight/2));
		float thumbleft=(float)(getBounds().left)+(((float)(getBounds().right-getBounds().left))/((float)(maxValue/step))*(float)value);
		d2d->target->FillRectangle(RectF((float)getBounds().left+pad,top,(float)getBounds().right-pad,(float)(top+trackheight)),d2d->solidbrush.Get());
		if(isEnabled()){
			if(isPressed()){
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\slide_thumb.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),size,size,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)thumbleft,(float)getBounds().top,(float)(thumbleft+size),(float)getBounds().bottom),opacity);
			}//Enabled pressed Slider
			else if(isHovered()){
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\slide_thumb.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),size,size,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)thumbleft,(float)getBounds().top,(float)(thumbleft+size),(float)getBounds().bottom),opacity);
			}//Enabled hovered Slider
			else{
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\slide_thumb.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),size,size,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)thumbleft,(float)getBounds().top,(float)(thumbleft+size),(float)getBounds().bottom),opacity);
			}
		}//Enabled Slider
		else{
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\slide_thumb.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),size,size,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
			d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)thumbleft,(float)getBounds().top,(float)(thumbleft+size),(float)getBounds().bottom),opacity);
		}//Disabled Slider
	}
	void ScrollBar::disableHorizontalScrolling(){
		hScroll=false;
	}
	void ScrollBar::enableHorizontalScrolling(){
		hScroll=true;
	}
	void ScrollBar::disableVerticalScrolling(){
		vScroll=false;
	}
	void ScrollBar::enableVerticalScrolling(){
		vScroll=true;
	}
	bool ScrollBar::isHorizontalScrollingEnabled(){
		return hScroll;
	}
	bool ScrollBar::isVerticalScrollingEnabled(){
		return vScroll;
	}
	void ScrollBar::scrollTo(float position){
		ScrollBar::position=position;
	}
	void ScrollBar::setOrientation(Orientation o){
		this->o=o;
	}
	ScrollBar::Orientation ScrollBar::getOrientation(){
		return o;
	}
	void ScrollBar::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isVerticalScrollingEnabled()){
			if(isPressed()){
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_track_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
			else{
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_track.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_thumb.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			float topY=(float)(getBounds().top)+((((float)(getBounds().bottom-getBounds().top))/portions)*position);
			float height=(float)(getBounds().bottom-getBounds().top)/portions;
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,(int)height,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
			d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,topY,(float)getBounds().right,topY+height),opacity);	
		}
		else if(isHorizontalScrollingEnabled()){
			if(isPressed()){
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_track_pressed_horizontal.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
			else{
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_track_horizontal.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
				d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_thumb_horizontal.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			float topY=(float)(getBounds().top)+((((float)(getBounds().bottom-getBounds().top))/portions)*position);
			float height=(float)(getBounds().bottom-getBounds().top)/portions;
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,(int)height,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,d2d->bmp.ReleaseAndGetAddressOf());
			d2d->target->DrawBitmap(d2d->bmp.Get(),RectF((float)getBounds().left,topY,(float)getBounds().right,topY+height),opacity);
		}
	}
}