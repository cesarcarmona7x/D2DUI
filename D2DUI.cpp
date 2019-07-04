// D2DUI.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
using namespace D2DUI;
std::wstring random_string(size_t length){
	auto chars=[]()->wchar_t{
		const wchar_t charset[]={
			L"0123456789"
			L"abcdefghijklmnopqrstuvwxyz"
			L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		};
		const size_t maxIndex=(sizeof(charset)-1);
		return charset[rand()%maxIndex];
	};
	std::wstring wstr(length,0);
	std::generate_n(wstr.begin(),length,chars);
	return wstr;
}
namespace D2DUI{
	MsgBox::MsgBox(HWND parent,bool modal,wchar_t* text,wchar_t* title,MSGBoxButtons buttons,MSGBoxIcon icon){
		hwnd=parent;
		this->modal=modal;
		showing=false;
		textContent=std::shared_ptr<TextLabel>(new TextLabel(text));
		textContent->setPadding(5,0);
		textContent->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		textTitle=std::shared_ptr<TextLabel>(new TextLabel(title));
		textTitle->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
		showing=false;
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
	void MsgBox::setPadding(int left,int top,int right,int bottom){
		leftPadding=left;
		topPadding=top;
		rightPadding=right;
		bottomPadding=bottom;
		if(rightPadding==-1){
			rightPadding=leftPadding;
		}
		if(bottomPadding==-1){
			bottomPadding=topPadding;
		}
	}
	void MsgBox::setFont(wchar_t* font){
		this->font=font;
		textTitle->setFont(font);
		textContent->setFont(font);
		for(int i=0;i<buttonsRow->windows.size();i++){
			buttonsRow->windows.at(i).get().setFont(font);
		}
	}
	wchar_t* MsgBox::getFont(){
		return font;
	}
	void MsgBox::setTextSize(float px){
		this->textSize=px;
		textTitle->setTextSize(px);
		textContent->setTextSize(px);
		for(int i=0;i<buttonsRow->windows.size();i++){
			buttonsRow->windows.at(i).get().setTextSize(px);
		}
	}
	float MsgBox::getTextSize(){
		return textSize;
	}
	void MsgBox::setForeground(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=R/255.0f;
		fRGBA[1]=G/255.0f;
		fRGBA[2]=B/255.0f;
		fRGBA[3]=A/255.0f;
		textTitle->setForeground(R,G,B,A);
		textContent->setForeground(R,G,B,A);
		for(int i=0;i<buttonsRow->windows.size();i++){
			buttonsRow->windows.at(i).get().setForeground(R,G,B,A);
		}
	}
	int* MsgBox::getForegroundInt(){
		return iRGBA;
	}
	void MsgBox::setForeground(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
		textTitle->setForeground(R,G,B,A);
		textContent->setForeground(R,G,B,A);
		for(int i=0;i<buttonsRow->windows.size();i++){
			buttonsRow->windows.at(i).get().setForeground(R,G,B,A);
		}
	}
	float* MsgBox::getForegroundFloat(){
		return fRGBA;
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
		ID2D1SolidColorBrush* scb;
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA_bg[0],fRGBA_bg[1],fRGBA_bg[2],fRGBA_bg[3]),&scb);
		d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),d2d->solidbrush.get());
		d2d->solidbrush.reset();
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
	wchar_t* InfoBox::getFont(){
		return font;
	}
	void InfoBox::setTextSize(float px){
		this->textSize=px;
		textContent->setTextSize(px);
	}
	float InfoBox::getTextSize(){
		return textSize;
	}
	void InfoBox::setPadding(int left,int top,int right,int bottom){
		leftPadding=left;
		topPadding=top;
		rightPadding=right;
		bottomPadding=bottom;
		if(rightPadding==-1){
			rightPadding=leftPadding;
		}
		if(bottomPadding==-1){
			bottomPadding=topPadding;
		}
	}
	void InfoBox::setForeground(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=R/255.0f;
		fRGBA[1]=G/255.0f;
		fRGBA[2]=B/255.0f;
		fRGBA[3]=A/255.0f;
		textContent->setForeground(R,G,B,A);
	}
	int* InfoBox::getForegroundInt(){
		return iRGBA;
	}
	void InfoBox::setForeground(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
		textContent->setForeground(R,G,B,A);
	}
	float* InfoBox::getForegroundFloat(){
		return fRGBA;
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
		ID2D1SolidColorBrush* scb;
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA_bg[0],fRGBA_bg[1],fRGBA_bg[2],fRGBA_bg[3]),&scb);
		d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),d2d->solidbrush.get());
		d2d->solidbrush.reset();
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
		this->textSize=px;
		textContent->setTextSize(px);
	}
	float PopupNotification::getTextSize(){
		return textSize;
	}
	void PopupNotification::setFont(wchar_t* font){
		this->font=font;
		textContent->setFont(font);
	}
	wchar_t* PopupNotification::getFont(){
		return font;
	}
	void PopupNotification::setPadding(int left,int top,int right,int bottom){
		leftPadding=left;
		topPadding=top;
		rightPadding=right;
		bottomPadding=bottom;
		if(rightPadding==-1){
			rightPadding=leftPadding;
		}
		if(bottomPadding==-1){
			bottomPadding=topPadding;
		}
	}
	void PopupNotification::setForeground(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=R/255.0f;
		fRGBA[1]=G/255.0f;
		fRGBA[2]=B/255.0f;
		fRGBA[3]=A/255.0f;
		textContent->setForeground(R,G,B,A);
	}
	int* PopupNotification::getForegroundInt(){
		return iRGBA;
	}
	void PopupNotification::setForeground(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
		textContent->setForeground(R,G,B,A);
	}
	float* PopupNotification::getForegroundFloat(){
		return fRGBA;		
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
	void LinearLayout::setOrientation(LayoutBase::Orientation o){
		LinearLayout::o=o;
	}
	LayoutBase::Orientation LinearLayout::getOrientation(){
		return o;
	}
	void LinearLayout::setBorder(Border b){
		leftBorder=b;
		topBorder=b;
		rightBorder=b;
		bottomBorder=b;
	}
	void LinearLayout::setRadius(float x,float y){
		LinearLayout::radius_x=x;
		LinearLayout::radius_y=y;
		if(radius_y==-1){
			radius_y=radius_x;
		}
	}
	float LinearLayout::getXRadius(){
		return radius_x;
	}
	float LinearLayout::getYRadius(){
		return radius_y;
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
	void LinearLayout::setLeftBorder(Border b){
		leftBorder=b;
	}
	void LinearLayout::setTopBorder(Border b){
		topBorder=b;
	}
	void LinearLayout::setRightBorder(Border b){
		rightBorder=b;
	}
	void LinearLayout::setBottomBorder(Border b){
		bottomBorder=b;
	}
	Border LinearLayout::getLeftBorder(){
		return leftBorder;
	}
	Border LinearLayout::getTopBorder(){
		return topBorder;
	}
	Border LinearLayout::getRightBorder(){
		return rightBorder;
	}
	Border LinearLayout::getBottomBorder(){
		return bottomBorder;
	}
	void LinearLayout::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
	}
	RECT LinearLayout::getBounds(){
		return bounds;
	}
	void LinearLayout::setBackground(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=(R/255.0f);
		fRGBA[1]=(G/255.0f);
		fRGBA[2]=(B/255.0f);
		fRGBA[3]=(A/255.0f);
	}
	void LinearLayout::setBackground(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
	}
	void LinearLayout::setPadding(int left,int top,int right,int bottom){
		leftPadding=left;
		topPadding=top;
		rightPadding=right;
		bottomPadding=bottom;
		if(rightPadding==-1){
			rightPadding=leftPadding;
		}
		if(bottomPadding==-1){
			bottomPadding=topPadding;
		}
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
		if(isinwindows==false){
			for(int i=0;i<layouts.size();i++){
				if(wcscmp(layouts.at(i).get().getId(),id)==0){
					layouts.erase(layouts.begin()+i);
					break;
				}
			}
		}
	}
	int LinearLayout::getLeftPadding(){
		return leftPadding;
	}
	int LinearLayout::getTopPadding(){
		return topPadding;
	}
	int LinearLayout::getRightPadding(){
		return rightPadding;
	}
	int LinearLayout::getBottomPadding(){
		return bottomPadding;
	}
	void LinearLayout::reorderComponents(){
		int top=getTopPadding();
		int left=getLeftPadding();
		int components=(windows.size()+layouts.size());
		if(o==VERTICAL){
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
		else if(o==HORIZONTAL){
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
		ID2D1StrokeStyle* strokestyle;
		ID2D1SolidColorBrush* scb;
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]),&scb);
		d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
		d2d->target->FillRoundedRectangle(RoundedRect(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),radius_x,radius_y),d2d->solidbrush.get());
		if(&leftBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(leftBorder.fRGBA[0],leftBorder.fRGBA[1],leftBorder.fRGBA[2],leftBorder.fRGBA[3]));
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getLeftBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getLeftBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getLeftBorder().getStrokeWidth());
				break;
			}
			d2d->solidbrush->Release();
			d2d->solidbrush=NULL;
		}
		if(&topBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(topBorder.fRGBA[0],topBorder.fRGBA[1],topBorder.fRGBA[2],topBorder.fRGBA[3]));
			switch(topBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getTopBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getTopBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getTopBorder().getStrokeWidth());
				break;
			}
		}
		if(&rightBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(rightBorder.fRGBA[0],rightBorder.fRGBA[1],rightBorder.fRGBA[2],rightBorder.fRGBA[3]));
			switch(rightBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getRightBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getRightBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getRightBorder().getStrokeWidth());
				break;
			}
		}
		if(&bottomBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(bottomBorder.fRGBA[0],bottomBorder.fRGBA[1],bottomBorder.fRGBA[2],bottomBorder.fRGBA[3]));
			switch(bottomBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getBottomBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getBottomBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getBottomBorder().getStrokeWidth());
				break;
			}
		}
		d2d->solidbrush.reset();
		reorderComponents();
		d2d->target->PushAxisAlignedClip(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),D2D1_ANTIALIAS_MODE_ALIASED);
		d2d->target->SaveDrawingState(d2d->targetstate.get());
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
		d2d->target->RestoreDrawingState(d2d->targetstate.get());
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
		if(inwindows==false){
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
	void GridLayout::setBackground(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=R/255.0f;
		fRGBA[1]=G/255.0f;
		fRGBA[2]=B/255.0f;
		fRGBA[3]=A/255.0f;
	}
	void GridLayout::setBackground(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
	}
	void GridLayout::setBorder(Border b){
		leftBorder=b;
		topBorder=b;
		rightBorder=b;
		bottomBorder=b;
	}
	void GridLayout::setLeftBorder(Border b){
		leftBorder=b;
	}
	void GridLayout::setTopBorder(Border b){
		topBorder=b;
	}
	void GridLayout::setRightBorder(Border b){
		rightBorder=b;
	}
	void GridLayout::setBottomBorder(Border b){
		bottomBorder=b;
	}
	Border GridLayout::getLeftBorder(){
		return leftBorder;
	}
	Border GridLayout::getTopBorder(){
		return topBorder;
	}
	Border GridLayout::getRightBorder(){
		return rightBorder;
	}
	Border GridLayout::getBottomBorder(){
		return bottomBorder;
	}
	void GridLayout::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
	}
	RECT GridLayout::getBounds(){
		return bounds;
	}
	void GridLayout::setRadius(float x,float y){
		radius_x=x;
		radius_y=y;
		if(radius_y==-1){
			radius_y=radius_x;
		}
	}
	float GridLayout::getXRadius(){
		return radius_x;
	}
	float GridLayout::getYRadius(){
		return radius_y;
	}
	void GridLayout::setPadding(int left,int top,int right,int bottom){
		leftPadding=left;
		topPadding=top;
		rightPadding=right;
		bottomPadding=bottom;
		if(rightPadding==-1){
			rightPadding=leftPadding;
		}
		if(bottomPadding==-1){
			bottomPadding=topPadding;
		}
	}
	int GridLayout::getLeftPadding(){
		return leftPadding;
	}
	int GridLayout::getTopPadding(){
		return topPadding;
	}
	int GridLayout::getRightPadding(){
		return rightPadding;
	}
	int GridLayout::getBottomPadding(){
		return bottomPadding;
	}
	void GridLayout::setGravity(LayoutBase::HGravity h,LayoutBase::VGravity v){
		hg=h;
		vg=v;
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
		ID2D1StrokeStyle* strokestyle;
		ID2D1SolidColorBrush* scb;
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]),&scb);
		d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
		d2d->target->FillRoundedRectangle(RoundedRect(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),radius_x,radius_y),d2d->solidbrush.get());
		if(&leftBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(leftBorder.fRGBA[0],leftBorder.fRGBA[1],leftBorder.fRGBA[2],leftBorder.fRGBA[3]));
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getLeftBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getLeftBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getLeftBorder().getStrokeWidth());
				break;
			}
		}
		if(&topBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(topBorder.fRGBA[0],topBorder.fRGBA[1],topBorder.fRGBA[2],topBorder.fRGBA[3]));
			switch(topBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getTopBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getTopBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getTopBorder().getStrokeWidth());
				break;
			}
		}
		if(&rightBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(rightBorder.fRGBA[0],rightBorder.fRGBA[1],rightBorder.fRGBA[2],rightBorder.fRGBA[3]));
			switch(rightBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getRightBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getRightBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getRightBorder().getStrokeWidth());
				break;
			}
		}
		if(&bottomBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(bottomBorder.fRGBA[0],bottomBorder.fRGBA[1],bottomBorder.fRGBA[2],bottomBorder.fRGBA[3]));
			switch(bottomBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getBottomBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getBottomBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getBottomBorder().getStrokeWidth());
				break;
			}
		}
		d2d->solidbrush.reset();
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
	void TableLayout::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
	}
	RECT TableLayout::getBounds(){
		return bounds;
	}
	void TableLayout::setPadding(int left,int top,int right,int bottom){
		leftPadding=left;
		topPadding=top;
		rightPadding=right;
		bottomPadding=bottom;
		if(rightPadding==-1){
			rightPadding=leftPadding;
		}
		if(bottomPadding==-1){
			bottomPadding=topPadding;
		}
	}
	int TableLayout::getLeftPadding(){
		return leftPadding;
	}
	int TableLayout::getTopPadding(){
		return topPadding;
	}
	int TableLayout::getRightPadding(){
		return rightPadding;
	}
	int TableLayout::getBottomPadding(){
		return bottomPadding;
	}
	void TableLayout::setRadius(float x,float y){
		radius_x=x;
		radius_y=y;
	}
	float TableLayout::getXRadius(){
		return radius_x;
	}
	float TableLayout::getYRadius(){
		return radius_y;
	}
	void TableLayout::setBackground(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=R/255.0f;
		fRGBA[1]=G/255.0f;
		fRGBA[2]=B/255.0f;
		fRGBA[3]=A/255.0f;
	}
	void TableLayout::setBackground(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
	}
	void TableLayout::setGravity(HGravity hg,VGravity vg){
		this->hg=hg;
		this->vg=vg;
	}
	void TableLayout::setBorder(Border b){
		leftBorder=b;
		topBorder=b;
		rightBorder=b;
		bottomBorder=b;
	}
	void TableLayout::setLeftBorder(Border b){
		leftBorder=b;
	}
	Border TableLayout::getLeftBorder(){
		return leftBorder;
	}
	void TableLayout::setTopBorder(Border b){
		topBorder=b;
	}
	Border TableLayout::getTopBorder(){
		return topBorder;
	}
	void TableLayout::setRightBorder(Border b){
		rightBorder=b;
	}
	Border TableLayout::getRightBorder(){
		return rightBorder;
	}
	void TableLayout::setBottomBorder(Border b){
		bottomBorder=b;
	}
	Border TableLayout::getBottomBorder(){
		return bottomBorder;
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
		ID2D1StrokeStyle* strokestyle;
		ID2D1SolidColorBrush* scb;
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]),&scb);
		d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
		d2d->target->FillRoundedRectangle(RoundedRect(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),radius_x,radius_y),d2d->solidbrush.get());
		if(&leftBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(leftBorder.fRGBA[0],leftBorder.fRGBA[1],leftBorder.fRGBA[2],leftBorder.fRGBA[3]));
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getLeftBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getLeftBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getLeftBorder().getStrokeWidth());
				break;
			}
		}
		if(&topBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(topBorder.fRGBA[0],topBorder.fRGBA[1],topBorder.fRGBA[2],topBorder.fRGBA[3]));
			switch(topBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getTopBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getTopBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getTopBorder().getStrokeWidth());
				break;
			}
		}
		if(&rightBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(rightBorder.fRGBA[0],rightBorder.fRGBA[1],rightBorder.fRGBA[2],rightBorder.fRGBA[3]));
			switch(rightBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getRightBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getRightBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getRightBorder().getStrokeWidth());
				break;
			}
		}
		if(&bottomBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(bottomBorder.fRGBA[0],bottomBorder.fRGBA[1],bottomBorder.fRGBA[2],bottomBorder.fRGBA[3]));
			switch(bottomBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getBottomBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getBottomBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getBottomBorder().getStrokeWidth());
				break;
			}
		}
		d2d->solidbrush.reset();
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
	void TableRow::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
	}
	RECT TableRow::getBounds(){
		return bounds;
	}
	void TableRow::setBorder(Border b){
		leftBorder=b;
		topBorder=b;
		rightBorder=b;
		bottomBorder=b;
	}
	void TableRow::setLeftBorder(Border b){
		leftBorder=b;
	}
	void TableRow::setTopBorder(Border b){
		topBorder=b;
	}
	void TableRow::setRightBorder(Border b){
		rightBorder=b;
	}
	void TableRow::setBottomBorder(Border b){
		bottomBorder=b;
	}
	Border TableRow::getLeftBorder(){
		return leftBorder;
	}
	Border TableRow::getTopBorder(){
		return topBorder;
	}
	Border TableRow::getRightBorder(){
		return rightBorder;
	}
	Border TableRow::getBottomBorder(){
		return bottomBorder;
	}
	void TableRow::setGravity(LayoutBase::HGravity h,LayoutBase::VGravity v){
		hg=h;
		vg=v;
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
		if(inwindows==false){
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
	void TableRow::setBackground(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=(R/255.0f);
		fRGBA[1]=(G/255.0f);
		fRGBA[2]=(B/255.0f);
		fRGBA[3]=(A/255.0f);
	}
	void TableRow::setBackground(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
	}
	void TableRow::setPadding(int left,int top,int right,int bottom){
		leftPadding=left;
		topPadding=top;
		rightPadding=right;
		bottomPadding=bottom;
		if(rightPadding==-1){
			rightPadding=leftPadding;
		}
		if(bottomPadding==-1){
			bottomPadding=topPadding;
		}
	}
	int TableRow::getLeftPadding(){
		return leftPadding;
	}
	int TableRow::getTopPadding(){
		return topPadding;
	}
	int TableRow::getRightPadding(){
		return rightPadding;
	}
	int TableRow::getBottomPadding(){
		return bottomPadding;
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
		ID2D1StrokeStyle* strokestyle;
		ID2D1SolidColorBrush* scb;
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]),&scb);
		d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
		d2d->target->FillRoundedRectangle(RoundedRect(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),radius_x,radius_y),d2d->solidbrush.get());
		if(&leftBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(leftBorder.fRGBA[0],leftBorder.fRGBA[1],leftBorder.fRGBA[2],leftBorder.fRGBA[3]));
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getLeftBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getLeftBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getLeftBorder().getStrokeWidth());
				break;
			}
		}
		if(&topBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(topBorder.fRGBA[0],topBorder.fRGBA[1],topBorder.fRGBA[2],topBorder.fRGBA[3]));
			switch(topBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getTopBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getTopBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getTopBorder().getStrokeWidth());
				break;
			}
		}
		if(&rightBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(rightBorder.fRGBA[0],rightBorder.fRGBA[1],rightBorder.fRGBA[2],rightBorder.fRGBA[3]));
			switch(rightBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getRightBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getRightBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getRightBorder().getStrokeWidth());
				break;
			}
		}
		if(&bottomBorder!=NULL){
			d2d->solidbrush->SetColor(ColorF(bottomBorder.fRGBA[0],bottomBorder.fRGBA[1],bottomBorder.fRGBA[2],bottomBorder.fRGBA[3]));
			switch(bottomBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getBottomBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getBottomBorder().getStrokeWidth(),strokestyle);
				strokestyle->Release();
				strokestyle=NULL;
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),d2d->solidbrush.get(),getBottomBorder().getStrokeWidth());
				break;
			}
		}
		d2d->solidbrush.reset();
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
			if(rg.at(i).get().isSelected()==true){
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
			if(tg.at(i).get().isSelected()==true){
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
	TextLabel::TextLabel(wchar_t* text): WindowBase(text){
		states.push_back(NONE);
		TextLabel::text=text;
		setForeground(0.f,0.f,0.f);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
	}
	void TextLabel::setTextSize(float px){
		textsize=px;
	}
	float TextLabel::getTextSize(){
		return textsize;
	}
	void TextLabel::setForeground(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=(float)R/255.0f;
		fRGBA[1]=(float)G/255.0f;
		fRGBA[2]=(float)B/255.0f;
		fRGBA[3]=(float)A/255.0f;
	}
	void TextLabel::setForeground(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
	}
	float* TextLabel::getForegroundFloat(){
		return fRGBA;
	}
	int* TextLabel::getForegroundInt(){
		return iRGBA;
	}
	void TextLabel::setBounds(int left,int top,int right,int bottom){
		TextLabel::bounds.left=left;
		TextLabel::bounds.top=top;
		TextLabel::bounds.right=right;
		TextLabel::bounds.bottom=bottom;
	}
	RECT TextLabel::getBounds(){
		RECT r;
		r.left=bounds.left;
		r.top=bounds.top;
		r.right=bounds.right;
		r.bottom=bounds.bottom;
		return r;
	}
	void TextLabel::setText(wchar_t* text){
		TextLabel::text=text;
	}
	wchar_t* TextLabel::getText(){
		return text;
	}
	void TextLabel::setHorizontalTextAlignment(const int H){
		hAlignment=const_cast<int&>(H);
	}
	int TextLabel::getHorizontalTextAlignment(){
		return hAlignment;
	}
	int TextLabel::getVerticalTextAlignment(){
		return vAlignment;
	}
	void TextLabel::setVerticalTextAlignment(const int V){
		vAlignment=const_cast<int&>(V);
	}
	void TextLabel::setPadding(int left,int top,int right,int bottom){
		leftPadding=left;
		topPadding=top;
		rightPadding=right;
		bottomPadding=bottom;
		if(rightPadding==-1){
			rightPadding=leftPadding;
		}
		if(bottomPadding==-1){
			bottomPadding=topPadding;
		}
	}
	void TextLabel::setFont(wchar_t* font){
		TextLabel::font=font;
	}
	wchar_t* TextLabel::getFont(){
		return font;
	}
	int TextLabel::getLeftPadding(){
		return leftPadding;
	}
	int TextLabel::getTopPadding(){
		return topPadding;
	}
	int TextLabel::getRightPadding(){
		return rightPadding;
	}
	int TextLabel::getBottomPadding(){
		return bottomPadding;
	}
	void TextLabel::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(TextLabel::states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
				if(foundinstates==false){
					states.push_back(VISIBLE);
				}
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool TextLabel::isVisible(){
		bool visible=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	void TextLabel::draw(std::shared_ptr<D2DHandle>& d2d){
		IDWriteTextFormat* dwtf;
		d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
		d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
		ID2D1SolidColorBrush* scb;
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
		d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
		std::wstring wtext(getText());
		d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),getBounds().right-getRightPadding(),getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
		d2d->solidbrush.reset();
		d2d->textformat.reset();
	}
	TextBox::TextBox(wchar_t* text): WindowBase(text){
		states.push_back(NONE);
		TextBox::text=text;
		setHorizontalTextAlignment(HorizontalConstants::LEFT);
		setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		setForeground(0,0,0);
		setTextSize(12.0f);
		setFont(L"MS Gothic");
	}
	void TextBox::setTextSize(float px){
		textsize=px;
	}
	float TextBox::getTextSize(){
		return textsize;
	}
	void TextBox::setForeground(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=(float)R/255.0f;
		fRGBA[1]=(float)G/255.0f;
		fRGBA[2]=(float)B/255.0f;
		fRGBA[3]=(float)A/255.0f;
	}
	void TextBox::setForeground(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
	}
	float* TextBox::getForegroundFloat(){
		return fRGBA;
	}
	int* TextBox::getForegroundInt(){
		return iRGBA;
	}
	void TextBox::setBounds(int left,int top,int right,int bottom){
		TextBox::bounds.left=left;
		TextBox::bounds.top=top;
		TextBox::bounds.right=right;
		TextBox::bounds.bottom=bottom;
	}
	RECT TextBox::getBounds(){
		RECT r;
		r.left=bounds.left;
		r.top=bounds.top;
		r.right=bounds.right;
		r.bottom=bounds.bottom;
		return r;
	}
	void TextBox::setText(wchar_t* text){
		TextBox::text=text;
	}
	wchar_t* TextBox::getText(){
		return text;
	}
	void TextBox::setHorizontalTextAlignment(const int H){
		hAlignment=const_cast<int&>(H);
	}
	int TextBox::getHorizontalTextAlignment(){
		return hAlignment;
	}
	int TextBox::getVerticalTextAlignment(){
		return vAlignment;
	}
	void TextBox::setVerticalTextAlignment(const int V){
		vAlignment=const_cast<int&>(V);
	}
	void TextBox::setPadding(int left,int top,int right,int bottom){
		leftPadding=left;
		topPadding=top;
		rightPadding=right;
		bottomPadding=bottom;
		if(rightPadding==-1){
			rightPadding=leftPadding;
		}
		if(bottomPadding==-1){
			bottomPadding=topPadding;
		}
	}
	void TextBox::setFont(wchar_t* font){
		TextBox::font=font;
	}
	wchar_t* TextBox::getFont(){
		return font;
	}
	int TextBox::getLeftPadding(){
		return leftPadding;
	}
	int TextBox::getTopPadding(){
		return topPadding;
	}
	int TextBox::getRightPadding(){
		return rightPadding;
	}
	int TextBox::getBottomPadding(){
		return bottomPadding;
	}
	void TextBox::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
				if(foundinstates==false){
					states.push_back(VISIBLE);
				}
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool TextBox::isVisible(){
		bool visible=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	void TextBox::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled==true){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==ENABLED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				states.push_back(ENABLED);
			}
		}
		else{
			for(int i=0;i<states.size();i++){
				if(states.at(i)==ENABLED){
					states.erase(states.begin()+i);
					break;
				}
			}
		}
	}
	bool TextBox::isEnabled(){
		bool enabled=false;
		for(int i=0;i<states.size();i++){
			if(states.at(i)==ENABLED){
				enabled=true;
				break;
			}
		}
		return enabled;
	}
	void TextBox::setEditable(bool editable){
		bool foundinstates=false;
		if(editable==true){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==EDITABLE){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				states.push_back(EDITABLE);
			}
		}
		else{
			for(int i=0;i<states.size();i++){
				if(states.at(i)==EDITABLE){
					states.erase(states.begin()+i);
					break;
				}
			}
		}
	}
	bool TextBox::isEditable(){
		bool editable=false;
		for(int i=0;i<states.size();i++){
			if(states.at(i)==EDITABLE){
				editable=true;
				break;
			}
		}
		return editable;
	}
	void TextBox::setFocus(bool focus){
		bool foundinstates=false;
		if(focus==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==FOCUSED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
				states.push_back(FOCUSED);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==FOCUSED){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool TextBox::hasFocus(){
		bool focus=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==FOCUSED){
					focus=true;
					break;
				}
			}
		}
		return focus;
	}
	void TextBox::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isEnabled()==true){
			if(hasFocus()==true){
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\textbox_focus.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				std::wstring wtext(getText());
				IDWriteTextFormat* dwtf;
				d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
				d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				ID2D1SolidColorBrush* scb;
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
				d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
				IDWriteTextLayout* dwtl;
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,&dwtl);
				d2d->textlayout=std::shared_ptr<IDWriteTextLayout>(dwtl,[](IDWriteTextLayout* p){p->Release();});
				textlayout.reset();
				textlayout=std::shared_ptr<IDWriteTextLayout>(d2d->textlayout);
				d2d->target->DrawTextLayout(Point2F((float)(getBounds().left+getLeftPadding()),(float)(getBounds().top+getTopPadding())),d2d->textlayout.get(),d2d->solidbrush.get());
				if(&caretRect!=NULL){
					d2d->solidbrush->SetColor(ColorF(ColorF::Chocolate,opacity));
					d2d->target->FillRectangle(RectF(caretRect.left,caretRect.top,caretRect.right,caretRect.bottom),d2d->solidbrush.get());
				}
				d2d->solidbrush.reset();
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
				d2d->textformat.reset();
				d2d->textlayout.reset();
				d2d->bmpscaler.reset();
			}
			else{
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\textbox.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				std::wstring wtext(getText());
				IDWriteTextFormat* dwtf;
				d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
				d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				ID2D1SolidColorBrush* scb;
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
				d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
				IDWriteTextLayout* dwtl;
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.get(),getBounds().right-getBounds().left-getLeftPadding()-getRightPadding(),getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding(),&dwtl);
				d2d->textlayout=std::shared_ptr<IDWriteTextLayout>(dwtl,[](IDWriteTextLayout* p){p->Release();});
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.get(),d2d->solidbrush.get());
				textlayout.reset();
				textlayout=std::shared_ptr<IDWriteTextLayout>(d2d->textlayout);
				d2d->solidbrush.reset();
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
				d2d->textformat.reset();
				d2d->solidbrush.reset();
				d2d->bmpscaler.reset();
				d2d->textformat.reset();
				d2d->textlayout.reset();
			}
		}
		else{
			IWICBitmapDecoder* wicbd;
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\textbox_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
			d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
			IWICBitmapFrameDecode* wicbfd;
			d2d->bmpdecoder->GetFrame(0,&wicbfd);
			d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
			IWICFormatConverter* wicfc;
			d2d->imgfactory->CreateFormatConverter(&wicfc);
			d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
			IWICBitmapScaler* wicbs;
			d2d->imgfactory->CreateBitmapScaler(&wicbs);
			d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			ID2D1Bitmap* wicb;
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
			d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
			std::wstring wtext(getText());
			IDWriteTextFormat* dwtf;
			d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
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
			d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			ID2D1SolidColorBrush* scb;
			d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
			d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
			IDWriteTextLayout* dwtl;
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.size(),d2d->textformat.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,&dwtl);
			d2d->textlayout=std::shared_ptr<IDWriteTextLayout>(dwtl,[](IDWriteTextLayout* p){p->Release();});
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),d2d->textlayout.get(),d2d->solidbrush.get());
			textlayout.reset();
			textlayout=std::shared_ptr<IDWriteTextLayout>(d2d->textlayout);
			d2d->bmpdecoder.reset();
			d2d->bmpframedecoder.reset();
			d2d->formatconverter.reset();
			d2d->bmp.reset();
			d2d->textformat.reset();
			d2d->textlayout.reset();
			d2d->solidbrush.reset();
			d2d->bmpscaler.reset();
		}
	}
	Button::Button(wchar_t* text): WindowBase(text){
		Button::text=text;
		setForeground(0.f,0.f,0.f);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
	}
	Button::Button(wchar_t* text,wchar_t* icon): WindowBase(text){
		Button::text=text;
		Button::icon=icon;
		setForeground(0.f,0.f,0.f);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
	}
	void Button::setTextSize(float px){
		textsize=px;
	}
	float Button::getTextSize(){
		return textsize;
	}
	void Button::setForeground(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=(float)R/255.0f;
		fRGBA[1]=(float)G/255.0f;
		fRGBA[2]=(float)B/255.0f;
		fRGBA[3]=(float)A/255.0f;
	}
	void Button::setForeground(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
	}
	float* Button::getForegroundFloat(){
		return fRGBA;
	}
	int* Button::getForegroundInt(){
		return iRGBA;
	}
	void Button::setFont(wchar_t* font){
		Button::font=font;
	}
	wchar_t* Button::getFont(){
		return font;
	}
	void Button::setIcon(wchar_t* icon){
		Button::icon=icon;
	}
	wchar_t* Button::getIcon(){
		return icon;
	}
	void Button::setBounds(int left,int top,int right,int bottom){
		Button::bounds.left=left;
		Button::bounds.top=top;
		Button::bounds.right=right;
		Button::bounds.bottom=bottom;
	}
	RECT Button::getBounds(){
		RECT r;
		r.left=bounds.left;
		r.top=bounds.top;
		r.right=bounds.right;
		r.bottom=bounds.bottom;
		return r;
	}
	void Button::setText(wchar_t* text){
		Button::text=text;
	}
	wchar_t* Button::getText(){
		return text;
	}
	void Button::setHorizontalTextAlignment(const int H){
		hAlignment=const_cast<int&>(H);
	}
	int Button::getHorizontalTextAlignment(){
		return hAlignment;
	}
	void Button::setVerticalTextAlignment(const int V){
		vAlignment=const_cast<int&>(V);
	}
	int Button::getVerticalTextAlignment(){
		return vAlignment;
	}
	int Button::getLeftPadding(){
		return leftPadding;
	}
	int Button::getTopPadding(){
		return topPadding;
	}
	int Button::getRightPadding(){
		return rightPadding;
	}
	int Button::getBottomPadding(){
		return bottomPadding;
	}
	void Button::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled==true){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==ENABLED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				states.push_back(ENABLED);
			}
		}
		else{
			for(int i=0;i<states.size();i++){
				if(states.at(i)==ENABLED){
					states.erase(states.begin()+i);
					break;
				}
			}
		}
	}
	void Button::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
				if(foundinstates==false){
					states.push_back(VISIBLE);
				}
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool Button::isVisible(){
		bool visible=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	bool Button::isEnabled(){
		bool enabled=false;
		for(int i=0;i<states.size();i++){
			if(states.at(i)==ENABLED){
				enabled=true;
				break;
			}
		}
		return enabled;
	}
	void Button::setHovered(bool hovered){
		bool foundinstates=false;
		if(hovered==true){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==HOVERED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				states.push_back(HOVERED);
			}
		}
		else{
			for(int i=0;i<states.size();i++){
				if(states.at(i)==HOVERED){
					states.erase(states.begin()+i);
					break;
				}
			}
		}
	}
	bool Button::isHovered(){
		bool hovered=false;
		for(int i=0;i<states.size();i++){
			if(states.at(i)==HOVERED){
				hovered=true;
				break;
			}
		}	
		return hovered;
	}
	void Button::setPressed(bool pressed){
		bool foundinstates=false;
		if(pressed==true){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==PRESSED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				states.push_back(PRESSED);
			}
		}
		else{
			for(int i=0;i<states.size();i++){
				if(states.at(i)==PRESSED){
					states.erase(states.begin()+i);
					break;
				}
			}
		}
	}
	bool Button::isPressed(){
		bool pressed=false;
		for(int i=0;i<states.size();i++){
			if(states.at(i)==PRESSED){
				pressed=true;
				break;
			}		
		}
		return pressed;
	}
	void Button::setPadding(int left,int top,int right,int bottom){
		leftPadding=left;
		topPadding=top;
		rightPadding=right;
		bottomPadding=bottom;
		if(rightPadding==-1){
			rightPadding=leftPadding;
		}
		if(bottomPadding==-1){
			bottomPadding=topPadding;
		}
	}
	void Button::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isEnabled()==true){
			if(isPressed()==true){
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\button_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				std::wstring wtext(getText());
				IDWriteTextFormat* dwtf;
				d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
				d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				ID2D1SolidColorBrush* scb;
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
				d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
				d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
				d2d->bmpscaler.reset();
				d2d->textformat.reset();
				d2d->solidbrush.reset();
			}//Pressed button
			else if(isHovered()==true){
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\button_hovered.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				std::wstring wtext(getText());
				IDWriteTextFormat* dwtf;
				d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
				d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				ID2D1SolidColorBrush* scb;
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
				d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
				d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
				d2d->bmpscaler.reset();
				d2d->textformat.reset();
				d2d->solidbrush.reset();
			}//Hovered button
			else{
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\button.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				std::wstring wtext(getText());
				IDWriteTextFormat* dwtf;
				d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
				d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				ID2D1SolidColorBrush* scb;
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
				d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
				d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
				d2d->bmpscaler.reset();
				d2d->textformat.reset();
				d2d->solidbrush.reset();
			}//Normal button
		}//Enabled button
		else{
			IWICBitmapDecoder* wicbd;
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\button_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
			d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
			IWICBitmapFrameDecode* wicbfd;
			d2d->bmpdecoder->GetFrame(0,&wicbfd);
			d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
			IWICBitmapScaler* wicbs;
			d2d->imgfactory->CreateBitmapScaler(&wicbs);
			d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			IWICFormatConverter* wicfc;
			d2d->imgfactory->CreateFormatConverter(&wicfc);
			d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
			d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			ID2D1Bitmap* wicb;
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
			d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
			std::wstring wtext(getText());
			IDWriteTextFormat* dwtf;
			d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,16.0F,locale,&dwtf);
			d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
			d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			ID2D1SolidColorBrush* scb;
			d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
			d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
			d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
			d2d->bmpdecoder.reset();
			d2d->bmpframedecoder.reset();
			d2d->formatconverter.reset();
			d2d->bmp.reset();
			d2d->bmpscaler.reset();
			d2d->textformat.reset();
			d2d->solidbrush.reset();
		}
	}
	ArrowButton::ArrowButton(ArrowButton_Type type,ArrowButton_Direction dir):Button(){
		ArrowButton::parentContainer=type;
		ArrowButton::direction=dir;
	}
	void ArrowButton::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isEnabled()==true){
			if(isPressed()==true){
				IWICBitmapDecoder* wicbd;
				if(parentContainer==SPINNER){
					if(direction==UP){
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_pressed_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);	
					}
					else{
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_pressed_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					}
				}//Spinner
				else{
					if(direction==UP){
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_pressed_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);	
					}
					else{
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_pressed_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					}
				}//ComboBox
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
				d2d->bmpscaler.reset();
			}//Pressed enabled ArrowButton
			else if(isHovered()==true){
				IWICBitmapDecoder* wicbd;
				if(parentContainer==SPINNER){
					if(direction==UP){
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_hovered_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);	
					}
					else{
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_hovered_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					}
				}//Spinner
				else{
					if(direction==UP){
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_hovered_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);	
					}
					else{
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_hovered_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					}
				}//ComboBox
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
				d2d->bmpscaler.reset();
			}//Hovered enabled ArrowButton
			else{
				IWICBitmapDecoder* wicbd;
				if(parentContainer==SPINNER){
					if(direction==UP){
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);	
					}
					else{
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					}
				}//Spinner
				else{
					if(direction==UP){
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);	
					}
					else{
						d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					}
				}//ComboBox
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
				d2d->bmpscaler.reset();
			}//Normal enabled ArrowButton
		}//Enabled ArrowButton
		else{
			IWICBitmapDecoder* wicbd;
			if(parentContainer==SPINNER){
				if(direction==UP){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_disabled_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);	
				}
				else{
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_disabled_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				}
			}//Spinner
			else{
				if(direction==UP){
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_disabled_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);	
				}
				else{
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_disabled_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				}
			}//ComboBox
			d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
			IWICBitmapFrameDecode* wicbfd;
			d2d->bmpdecoder->GetFrame(0,&wicbfd);
			d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
			IWICBitmapScaler* wicbs;
			d2d->imgfactory->CreateBitmapScaler(&wicbs);
			d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			IWICFormatConverter* wicfc;
			d2d->imgfactory->CreateFormatConverter(&wicfc);
			d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
			d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			ID2D1Bitmap* wicb;
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
			d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
			d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			d2d->bmpdecoder.reset(),
				d2d->bmpframedecoder.reset();
			d2d->formatconverter.reset();
			d2d->bmp.reset();
			d2d->bmpscaler.reset();
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
		textsize=px;
		valuemodifier->setTextSize(px);
	}
	float Spinner::getTextSize(){
		return textsize;
	}
	void Spinner::setForeground(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=(float)R/255.0f;
		fRGBA[1]=(float)G/255.0f;
		fRGBA[2]=(float)B/255.0f;
		fRGBA[3]=(float)A/255.0f;
		valuemodifier->setForeground(R,G,B,A);
	}
	void Spinner::setForeground(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
		valuemodifier->setForeground(R,G,B,A);
	}
	float* Spinner::getForegroundFloat(){
		return fRGBA;
	}
	int* Spinner::getForegroundInt(){
		return iRGBA;
	}
	void Spinner::setFont(wchar_t* font){
		this->font=font;
		valuemodifier->setFont(font);
	}
	wchar_t* Spinner::getFont(){
		return font;
	}
	void Spinner::setPadding(int left,int top,int right,int bottom){
		leftPadding=left;
		topPadding=top;
		rightPadding=right;
		bottomPadding=bottom;
		if(rightPadding==-1){
			rightPadding=leftPadding;
		}
		if(bottomPadding==-1){
			bottomPadding=topPadding;
		}
		valuemodifier->setPadding(left,top,right,bottom);
	}
	int Spinner::getLeftPadding(){
		return leftPadding;
	}
	int Spinner::getTopPadding(){
		return topPadding;
	}
	int Spinner::getRightPadding(){
		return rightPadding;
	}
	int Spinner::getBottomPadding(){
		return bottomPadding;
	}
	void Spinner::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==ENABLED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
				states.push_back(ENABLED);
			}
		}
		else{
			for(int i=0;i<states.size();i++){
				if(states.at(i)==ENABLED){
					states.erase(states.begin()+i);
					break;
				}
			}
		}
		valuemodifier->setEnabled(enabled);
		up->setEnabled(enabled);
		down->setEnabled(enabled);
	}
	void Spinner::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
				states.push_back(VISIBLE);
				valuemodifier->states.push_back(VISIBLE);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
		valuemodifier->setVisible(visible);
		up->setVisible(visible);
		down->setVisible(visible);
	}
	bool Spinner::isVisible(){
		bool visible=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	bool Spinner::isEnabled(){
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
	void Spinner::setHovered(bool hovered){
		bool foundinstates=false;
		if(hovered==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==HOVERED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
	bool Spinner::isHovered(){
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
	void Spinner::setPressed(bool pressed){
		bool foundinstates=false;
		if(pressed==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==PRESSED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
	bool Spinner::isPressed(){
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
	void Spinner::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
		valuemodifier->setBounds(bounds.left,bounds.top,bounds.right-30,bounds.bottom);
		up->setBounds(bounds.right-30,bounds.top,bounds.right,bounds.top+((bounds.bottom-bounds.top)/2));
		down->setBounds(bounds.right-30,bounds.top+((bounds.bottom-bounds.top)/2),bounds.right,bounds.bottom);
	}
	RECT Spinner::getBounds(){
		return bounds;
	}
	void Spinner::setHorizontalTextAlignment(const int H){
		hAlignment=const_cast<int&>(H);
		valuemodifier->setHorizontalTextAlignment(H);
	}
	int Spinner::getHorizontalTextAlignment(){
		return hAlignment;
	}
	void Spinner::setVerticalTextAlignment(const int V){
		vAlignment=const_cast<int&>(V);
		valuemodifier->setVerticalTextAlignment(V);
	}
	int Spinner::getVerticalTextAlignment(){
		return vAlignment;
	}
	void Spinner::setEditable(bool editable){
		bool foundinstates=false;
		if(editable==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==EDITABLE){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
				states.push_back(EDITABLE);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==EDITABLE){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
		valuemodifier->setEditable(editable);
	}
	bool Spinner::isEditable(){
		bool editable=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==EDITABLE){
					editable=true;
					break;
				}
			}
		}
		return editable;
	}
	void Spinner::setFocus(bool focus){
		bool foundinstates=false;
		if(focus==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==FOCUSED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
				states.push_back(FOCUSED);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==FOCUSED){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
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
	bool Spinner::hasFocus(){
		bool focus=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==FOCUSED){
					focus=true;
					break;
				}
			}
		}
		return focus;
	}
	void Spinner::setLocale(wchar_t* locale){
		this->locale=locale;
		up->setLocale(locale);
		down->setLocale(locale);
		valuemodifier->setLocale(locale);
	}
	void Spinner::setOpacity(float opacity){
		this->opacity=opacity;
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
	CheckBox::CheckBox(bool checked,wchar_t* text): WindowBase(checked,text){
		states.push_back(NONE);
		setChecked(checked);
		CheckBox::text=text;
		setForeground(0,0,0);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
	}
	void CheckBox::setTextSize(float px){
		textsize=px;
	}
	float CheckBox::getTextSize(){
		return textsize;
	}
	void CheckBox::setForeground(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=(float)R/255.0f;
		fRGBA[1]=(float)G/255.0f;
		fRGBA[2]=(float)B/255.0f;
		fRGBA[3]=(float)A/255.0f;
	}
	void CheckBox::setForeground(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
	}
	float* CheckBox::getForegroundFloat(){
		return fRGBA;
	}
	int* CheckBox::getForegroundInt(){
		return iRGBA;
	}
	void CheckBox::setFont(wchar_t* font){
		this->font=font;
	}
	wchar_t* CheckBox::getFont(){
		return font;
	}
	void CheckBox::setPadding(int left,int top,int right,int bottom){
		leftPadding=left;
		topPadding=top;
		rightPadding=right;
		bottomPadding=bottom;
		if(rightPadding==-1){
			rightPadding=leftPadding;
		}
		if(bottomPadding==-1){
			bottomPadding=topPadding;
		}
	}
	int CheckBox::getLeftPadding(){
		return leftPadding;
	}
	int CheckBox::getTopPadding(){
		return topPadding;
	}
	int CheckBox::getRightPadding(){
		return rightPadding;
	}
	int CheckBox::getBottomPadding(){
		return bottomPadding;
	}
	void CheckBox::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==ENABLED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
				states.push_back(ENABLED);
			}
		}
		else{
			for(int i=0;i<states.size();i++){
				if(states.at(i)==ENABLED){
					states.erase(states.begin()+i);
					break;
				}
			}
		}
	}
	void CheckBox::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
				states.push_back(VISIBLE);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool CheckBox::isVisible(){
		bool visible=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	bool CheckBox::isEnabled(){
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
	void CheckBox::setHovered(bool hovered){
		bool foundinstates=false;
		if(hovered==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==HOVERED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
	bool CheckBox::isHovered(){
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
	void CheckBox::setPressed(bool pressed){
		bool foundinstates=false;
		if(pressed==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==PRESSED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
	bool CheckBox::isPressed(){
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
	void CheckBox::setChecked(bool checked){
		bool foundinstates=false;
		if(checked==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==CHECKED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
				states.push_back(CHECKED);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==CHECKED){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool CheckBox::isChecked(){
		bool checked=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==CHECKED){
					checked=true;
					break;
				}
			}
		}
		return checked;
	}
	void CheckBox::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
	}
	RECT CheckBox::getBounds(){
		return bounds;
	}
	void CheckBox::setText(wchar_t* text){
		CheckBox::text=text;
	}
	wchar_t* CheckBox::getText(){
		return CheckBox::text;
	}
	void CheckBox::setHorizontalTextAlignment(const int H){
		hAlignment=const_cast<int&>(H);
	}
	int CheckBox::getHorizontalTextAlignment(){
		return hAlignment;
	}
	void CheckBox::setVerticalTextAlignment(const int V){
		vAlignment=const_cast<int&>(V);
	}
	int CheckBox::getVerticalTextAlignment(){
		return vAlignment;
	}
	void CheckBox::draw(std::shared_ptr<D2DHandle>& d2d){
		HRESULT hr=S_OK;
		if(isEnabled()==true){
			if(isChecked()==true){
				if(isPressed()==true){
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_pressed_checked.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					std::wstring wtext(getText());
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Pressed and checked checkbox
				else if(isHovered()==true){
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_hovered_checked.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					std::wstring wtext(getText());
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Hovered and checked checkbox
				else{
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_checked.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					std::wstring wtext(getText());
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Normal checked checkbox
			}//Checked checkbox
			else{
				if(isPressed()==true){
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					std::wstring wtext(getText());
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Pressed checkbox
				else if(isHovered()==true){
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_hovered.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					std::wstring wtext(getText());
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Hovered checkbox
				else{
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					std::wstring wtext(getText());
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Normal checkbox
			}//Unchecked checkbox
		}//Enabled checkbox
		else{
			if(isChecked()==true){
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_disabled_checked.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				std::wstring wtext(getText());
				IDWriteTextFormat* dwtf;
				d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
				d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				ID2D1SolidColorBrush* scb;
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
				d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
				d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
				d2d->textformat.reset();
				d2d->solidbrush.reset();
				d2d->bmpscaler.reset();
			}
			else{
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				std::wstring wtext(getText());
				IDWriteTextFormat* dwtf;
				d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
				d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				ID2D1SolidColorBrush* scb;
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
				d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
				d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
				d2d->textformat.reset();
				d2d->solidbrush.reset();
				d2d->bmpscaler.reset();
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
	void DialogueBox::setBackground(int R,int G,int B,int A){
		ibgRGBA[0]=R;
		ibgRGBA[1]=G;
		ibgRGBA[2]=B;
		ibgRGBA[3]=A;
		fbgRGBA[0]=(float)R/255.0f;
		fbgRGBA[1]=(float)G/255.0f;
		fbgRGBA[2]=(float)B/255.0f;
		fbgRGBA[3]=(float)A/255.0f;
	}
	void DialogueBox::setBackground(float R,float G,float B,float A){
		fbgRGBA[0]=R;
		fbgRGBA[1]=G;
		fbgRGBA[2]=B;
		fbgRGBA[3]=A;
		ibgRGBA[0]=(int)(R*255.0f);
		ibgRGBA[1]=(int)(G*255.0f);
		ibgRGBA[2]=(int)(B*255.0f);
		ibgRGBA[3]=(int)(A*255.0f);
	}
	int* DialogueBox::getBackgroundInt(){
		return ibgRGBA;
	}
	float* DialogueBox::getBackgroundFloat(){
		return fbgRGBA;
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
			IWICBitmapDecoder* wicbd;
			d2d->imgfactory->CreateDecoderFromFilename(decorationfile,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
			d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
			IWICBitmapFrameDecode* wicbfd;
			d2d->bmpdecoder->GetFrame(0,&wicbfd);
			d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
			IWICBitmapScaler* wicbs;
			d2d->imgfactory->CreateBitmapScaler(&wicbs);
			d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getDecorationBounds().bottom-getDecorationBounds().top,getDecorationBounds().bottom-getDecorationBounds().top,WICBitmapInterpolationModeFant);
			IWICFormatConverter* wicfc;
			d2d->imgfactory->CreateFormatConverter(&wicfc);
			d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
			d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			ID2D1Bitmap* wicb;
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
			d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
		}
		if(&decorationfile!=NULL&&getDecorationLevel()==DECORATIONBELOWDIALOGUEBOX){
			d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getDecorationBounds().left,(float)getDecorationBounds().top,(float)getDecorationBounds().right,(float)getDecorationBounds().bottom),decorationopacity);
			d2d->bmpdecoder.reset();
			d2d->bmpframedecoder.reset();
			d2d->formatconverter.reset();
			d2d->bmp.reset();
			d2d->bmpscaler.reset();
		}
		ID2D1SolidColorBrush* scb;
		d2d->target->CreateSolidColorBrush(ColorF(fbgRGBA[0],fbgRGBA[1],fbgRGBA[2],fbgRGBA[3]*opacity),&scb);
		d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),d2d->solidbrush.get());
		if(&decorationfile!=NULL&&getDecorationLevel()==DECORATIONOVERDIALOGUEBOX){
			d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getDecorationBounds().left,(float)getDecorationBounds().top,(float)getDecorationBounds().right,(float)getDecorationBounds().bottom),decorationopacity);
			d2d->bmpdecoder.reset();
			d2d->bmpframedecoder.reset();
			d2d->formatconverter.reset();
			d2d->bmp.reset();
			d2d->bmpscaler.reset();
		}
		std::wstring wtext(getText());
		IDWriteTextFormat* dwtf;
		d2d->dwritefactory->CreateTextFormat(getFont(),NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
		d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
		d2d->target->DrawTextW(wtext.c_str(),showedcharacters,d2d->textformat.get(),RectF((float)getBounds().left+getLeftPadding()+2,(float)getBounds().top+getTopPadding()+2,(float)getBounds().right-getRightPadding()+2,(float)getBounds().bottom-getBottomPadding()+2),d2d->solidbrush.get());
		d2d->solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity));
		d2d->target->DrawTextW(wtext.c_str(),showedcharacters,d2d->textformat.get(),RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
		d2d->textformat.reset();
		d2d->solidbrush.reset();
	}
	RadioButton::RadioButton(RadioGroup& parent,bool selected,wchar_t* text): WindowBase(&parent,selected,text), parent(parent){
		setParent(parent);
		setSelected(selected);
		RadioButton::text=text;
		setForeground(0,0,0);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
	}
	void RadioButton::setTextSize(float px){
		textsize=px;
	}
	float RadioButton::getTextSize(){
		return textsize;
	}
	void RadioButton::setForeground(int R,int G,int B,int A){
		iRGBA[0]=R;
		iRGBA[1]=G;
		iRGBA[2]=B;
		iRGBA[3]=A;
		fRGBA[0]=(float)R/255.0f;
		fRGBA[1]=(float)G/255.0f;
		fRGBA[2]=(float)B/255.0f;
		fRGBA[3]=(float)A/255.0f;
	}
	void RadioButton::setForeground(float R,float G,float B,float A){
		fRGBA[0]=R;
		fRGBA[1]=G;
		fRGBA[2]=B;
		fRGBA[3]=A;
		iRGBA[0]=(int)(R*255.0f);
		iRGBA[1]=(int)(G*255.0f);
		iRGBA[2]=(int)(B*255.0f);
		iRGBA[3]=(int)(A*255.0f);
	}
	float* RadioButton::getForegroundFloat(){
		return fRGBA;
	}
	int* RadioButton::getForegroundInt(){
		return iRGBA;
	}
	void RadioButton::setFont(wchar_t* font){
		RadioButton::font=font;
	}
	wchar_t* RadioButton::getFont(){
		return font;
	}
	void RadioButton::setPadding(int left,int top,int right,int bottom){
		leftPadding=left;
		topPadding=top;
		rightPadding=right;
		bottomPadding=bottom;
		if(rightPadding==-1){
			rightPadding=leftPadding;
		}
		if(bottomPadding==-1){
			bottomPadding=topPadding;
		}
	}
	int RadioButton::getLeftPadding(){
		return leftPadding;
	}
	int RadioButton::getTopPadding(){
		return topPadding;
	}
	int RadioButton::getRightPadding(){
		return rightPadding;
	}
	int RadioButton::getBottomPadding(){
		return bottomPadding;
	}
	void RadioButton::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled==true){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==ENABLED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				states.push_back(ENABLED);
			}
		}
		else{
			for(int i=0;i<states.size();i++){
				if(states.at(i)==ENABLED){
					states.erase(states.begin()+i);
					break;
				}
			}
		}
	}
	void RadioButton::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
				if(foundinstates==false){
					states.push_back(VISIBLE);
				}
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool RadioButton::isVisible(){
		bool visible=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	bool RadioButton::isEnabled(){
		bool enabled=false;
		for(int i=0;i<states.size();i++){
			if(states.at(i)==ENABLED){
				enabled=true;
				break;
			}
		}
		return enabled;
	}
	void RadioButton::setRBIndex(int index){
		rbIndex=index;
	}
	int RadioButton::getRBIndex(){
		return rbIndex;
	}
	void RadioButton::setHovered(bool hovered){
		bool foundinstates=false;
		if(hovered==true){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==HOVERED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				states.push_back(HOVERED);
			}
		}
		else{
			for(int i=0;i<states.size();i++){
				if(states.at(i)==HOVERED){
					states.erase(states.begin()+i);
					break;
				}
			}
		}
	}
	bool RadioButton::isHovered(){
		bool hovered=false;
		for(int i=0;i<states.size();i++){
			if(states.at(i)==HOVERED){
				hovered=true;
				break;
			}
		}	
		return hovered;
	}
	void RadioButton::setPressed(bool pressed){
		bool foundinstates=false;
		if(pressed==true){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==PRESSED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				states.push_back(PRESSED);
			}
		}
		else{
			for(int i=0;i<states.size();i++){
				if(states.at(i)==PRESSED){
					states.erase(states.begin()+i);
					break;
				}
			}
		}
	}
	bool RadioButton::isPressed(){
		bool pressed=false;
		for(int i=0;i<states.size();i++){
			if(states.at(i)==PRESSED){
				pressed=true;
				break;
			}		
		}
		return pressed;
	}
	void RadioButton::setSelected(bool selected){
		bool foundinstates=false;
		if(selected==true){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==SELECTED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				states.push_back(SELECTED);
				getParent().setSelectedIndex(getRBIndex());
			}
		}
		else{
			for(int i=0;i<states.size();i++){
				if(states.at(i)==SELECTED){
					states.erase(states.begin()+i);
					break;
				}
			}
		}
	}
	bool RadioButton::isSelected(){
		bool selected=false;
		for(int i=0;i<states.size();i++){
			if(states.at(i)==SELECTED){
				selected=true;
				break;
			}
		}
		return selected;
	}
	void RadioButton::setBounds(int left,int top,int right,int bottom){
		RadioButton::bounds.left=left;
		RadioButton::bounds.top=top;
		RadioButton::bounds.right=right;
		RadioButton::bounds.bottom=bottom;
	}
	RECT RadioButton::getBounds(){
		RECT r;
		r.left=RadioButton::bounds.left;
		r.top=RadioButton::bounds.top;
		r.right=RadioButton::bounds.right;
		r.bottom=RadioButton::bounds.bottom;
		return r;
	}
	void RadioButton::setText(wchar_t* text){
		RadioButton::text=text;
	}
	wchar_t* RadioButton::getText(){
		return RadioButton::text;
	}
	void RadioButton::setHorizontalTextAlignment(const int H){
		RadioButton::hAlignment=const_cast<int&>(H);
	}
	int RadioButton::getHorizontalTextAlignment(){
		return RadioButton::hAlignment;
	}
	void RadioButton::setVerticalTextAlignment(const int V){
		RadioButton::vAlignment=const_cast<int&>(V);
	}
	int RadioButton::getVerticalTextAlignment(){
		return RadioButton::vAlignment;
	}
	void RadioButton::setParent(RadioGroup& rg){
		parent=rg;
		parent.add(*this);
	}
	void RadioButton::setTag(wchar_t* tag){
		RadioButton::tag=tag;
	}
	wchar_t* RadioButton::getTag(){
		return tag;
	}
	RadioGroup& RadioButton::getParent(){
		return parent;
	}
	void RadioButton::removeParent(RadioGroup& rg){
		parent.remove(this->getIndex());
		setIndex(-1);
	}
	void RadioButton::draw(std::shared_ptr<D2DHandle>& d2d){
		std::wstring wtext(getText());
		if(isEnabled()==true){
			if(isSelected()==true){
				if(isPressed()==true){
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_pressed_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Pressed and selected radiobutton
				else if(isHovered()==true){
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_hovered_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Hovered and selected radiobutton
				else{
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Normal selected radiobutton
			}//Selected radiobutton
			else{
				if(isPressed()==true){
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Pressed radiobutton
				else if(isHovered()==true){
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_hovered.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Hovered radiobutton
				else{
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Normal enabled radiobutton
			}//Unselected radiobutton
		}//Enabled radiobutton
		else{
			if(isSelected()==true){
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_disabled_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				IDWriteTextFormat* dwtf;
				d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
				d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				ID2D1SolidColorBrush* scb;
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
				d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
				d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
				d2d->textformat.reset();
				d2d->solidbrush.reset();
				d2d->bmpscaler.reset();
			}//Selected disabled radiobutton
			else{
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				IDWriteTextFormat* dwtf;
				d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
				d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				ID2D1SolidColorBrush* scb;
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
				d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
				d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+(getBounds().bottom-getBounds().top)+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
				d2d->textformat.reset();
				d2d->solidbrush.reset();
				d2d->bmpscaler.reset();
			}//Unselected disabled radiobutton
		}//Disabled radiobutton
	}
	ToggleButton::ToggleButton(ToggleGroup& parent,bool selected,wchar_t* text,wchar_t* icon):WindowBase(),parent(parent){
		setParent(parent);
		ToggleButton::text=text;
		ToggleButton::icon=icon;
		setForeground(0,0,0);
		setTextSize(12.0f);
		setSelected(selected);
		setFont(L"Microsoft Sans Serif");
	}
	void ToggleButton::setTextSize(float px){
		ToggleButton::textsize=px;
	}
	float ToggleButton::getTextSize(){
		return ToggleButton::textsize;
	}
	void ToggleButton::setForeground(int R,int G,int B,int A){
		ToggleButton::iRGBA[0]=R;
		ToggleButton::iRGBA[1]=G;
		ToggleButton::iRGBA[2]=B;
		ToggleButton::iRGBA[3]=A;
		ToggleButton::fRGBA[0]=(float)R/255.0f;
		ToggleButton::fRGBA[1]=(float)G/255.0f;
		ToggleButton::fRGBA[2]=(float)B/255.0f;
		ToggleButton::fRGBA[3]=(float)A/255.0f;
	}
	void ToggleButton::setForeground(float R,float G,float B,float A){
		ToggleButton::fRGBA[0]=R;
		ToggleButton::fRGBA[1]=G;
		ToggleButton::fRGBA[2]=B;
		ToggleButton::fRGBA[3]=A;
		ToggleButton::iRGBA[0]=(int)(R*255.0f);
		ToggleButton::iRGBA[1]=(int)(G*255.0f);
		ToggleButton::iRGBA[2]=(int)(B*255.0f);
		ToggleButton::iRGBA[3]=(int)(A*255.0f);
	}
	float* ToggleButton::getForegroundFloat(){
		return ToggleButton::fRGBA;
	}
	int* ToggleButton::getForegroundInt(){
		return ToggleButton::iRGBA;
	}
	void ToggleButton::setFont(wchar_t* font){
		ToggleButton::font=font;
	}
	wchar_t* ToggleButton::getFont(){
		return ToggleButton::font;
	}
	void ToggleButton::setIcon(wchar_t* icon){
		ToggleButton::icon=icon;
	}
	wchar_t* ToggleButton::getIcon(){
		return ToggleButton::icon;
	}
	void ToggleButton::setPadding(int left,int top,int right,int bottom){
		ToggleButton::leftPadding=left;
		ToggleButton::topPadding=top;
		ToggleButton::rightPadding=right;
		ToggleButton::bottomPadding=bottom;
		if(ToggleButton::rightPadding==-1){
			ToggleButton::rightPadding=ToggleButton::leftPadding;
		}
		if(ToggleButton::bottomPadding==-1){
			ToggleButton::bottomPadding=ToggleButton::topPadding;
		}
	}
	int ToggleButton::getLeftPadding(){
		return ToggleButton::leftPadding;
	}
	int ToggleButton::getTopPadding(){
		return ToggleButton::topPadding;
	}
	int ToggleButton::getRightPadding(){
		return ToggleButton::rightPadding;
	}
	int ToggleButton::getBottomPadding(){
		return ToggleButton::bottomPadding;
	}
	void ToggleButton::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled==true){
			for(int i=0;i<ToggleButton::states.size();i++){
				if(ToggleButton::states.at(i)==ENABLED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ToggleButton::states.push_back(ENABLED);
			}
		}
		else{
			for(int i=0;i<ToggleButton::states.size();i++){
				if(ToggleButton::states.at(i)==ENABLED){
					ToggleButton::states.erase(ToggleButton::states.begin()+i);
					break;
				}
			}
		}
	}
	void ToggleButton::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(ToggleButton::states.size()!=0){
				for(int i=0;i<ToggleButton::states.size();i++){
					if(ToggleButton::states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
				if(foundinstates==false){
					ToggleButton::states.push_back(VISIBLE);
				}
			}
		}
		else{
			if(ToggleButton::states.size()!=0){
				for(int i=0;i<ToggleButton::states.size();i++){
					if(ToggleButton::states.at(i)==VISIBLE){
						ToggleButton::states.erase(ToggleButton::states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool ToggleButton::isVisible(){
		bool visible=false;
		if(ToggleButton::states.size()!=0){
			for(int i=0;i<ToggleButton::states.size();i++){
				if(ToggleButton::states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	bool ToggleButton::isEnabled(){
		bool enabled=false;
		for(int i=0;i<ToggleButton::states.size();i++){
			if(ToggleButton::states.at(i)==ENABLED){
				enabled=true;
				break;
			}
		}
		return enabled;
	}
	void ToggleButton::setTBIndex(int index){
		tbIndex=index;
	}
	int ToggleButton::getTBIndex(){
		return tbIndex;
	}
	void ToggleButton::setHovered(bool hovered){
		bool foundinstates=false;
		if(hovered==true){
			for(int i=0;i<ToggleButton::states.size();i++){
				if(ToggleButton::states.at(i)==HOVERED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ToggleButton::states.push_back(HOVERED);
			}
		}
		else{
			for(int i=0;i<ToggleButton::states.size();i++){
				if(ToggleButton::states.at(i)==HOVERED){
					ToggleButton::states.erase(ToggleButton::states.begin()+i);
					break;
				}
			}
		}
	}
	bool ToggleButton::isHovered(){
		bool hovered=false;
		for(int i=0;i<ToggleButton::states.size();i++){
			if(ToggleButton::states.at(i)==HOVERED){
				hovered=true;
				break;
			}
		}	
		return hovered;
	}
	void ToggleButton::setPressed(bool pressed){
		bool foundinstates=false;
		if(pressed==true){
			for(int i=0;i<ToggleButton::states.size();i++){
				if(ToggleButton::states.at(i)==PRESSED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ToggleButton::states.push_back(PRESSED);
			}
		}
		else{
			for(int i=0;i<ToggleButton::states.size();i++){
				if(ToggleButton::states.at(i)==PRESSED){
					ToggleButton::states.erase(ToggleButton::states.begin()+i);
					break;
				}
			}
		}
	}
	bool ToggleButton::isPressed(){
		bool pressed=false;
		for(int i=0;i<ToggleButton::states.size();i++){
			if(ToggleButton::states.at(i)==PRESSED){
				pressed=true;
				break;
			}		
		}
		return pressed;
	}
	void ToggleButton::setSelected(bool selected){
		bool foundinstates=false;
		if(selected==true){
			for(int i=0;i<ToggleButton::states.size();i++){
				if(ToggleButton::states.at(i)==SELECTED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ToggleButton::states.push_back(SELECTED);
				parent.setSelectedIndex(getTBIndex());
			}
		}
		else{
			for(int i=0;i<ToggleButton::states.size();i++){
				if(ToggleButton::states.at(i)==SELECTED){
					ToggleButton::states.erase(ToggleButton::states.begin()+i);
					break;
				}
			}
		}
	}
	bool ToggleButton::isSelected(){
		bool selected=false;
		for(int i=0;i<ToggleButton::states.size();i++){
			if(ToggleButton::states.at(i)==SELECTED){
				selected=true;
				break;
			}
		}
		return selected;
	}
	void ToggleButton::setBounds(int left,int top,int right,int bottom){
		ToggleButton::bounds.left=left;
		ToggleButton::bounds.top=top;
		ToggleButton::bounds.right=right;
		ToggleButton::bounds.bottom=bottom;
	}
	RECT ToggleButton::getBounds(){
		RECT r;
		r.left=ToggleButton::bounds.left;
		r.top=ToggleButton::bounds.top;
		r.right=ToggleButton::bounds.right;
		r.bottom=ToggleButton::bounds.bottom;
		return r;
	}
	void ToggleButton::setText(wchar_t* text){
		ToggleButton::text=text;
	}
	wchar_t* ToggleButton::getText(){
		return ToggleButton::text;
	}
	void ToggleButton::setHorizontalTextAlignment(const int H){
		ToggleButton::hAlignment=const_cast<int&>(H);
	}
	int ToggleButton::getHorizontalTextAlignment(){
		return ToggleButton::hAlignment;
	}
	void ToggleButton::setVerticalTextAlignment(const int V){
		ToggleButton::vAlignment=const_cast<int&>(V);
	}
	int ToggleButton::getVerticalTextAlignment(){
		return ToggleButton::vAlignment;
	}
	void ToggleButton::setParent(ToggleGroup& rg){
		parent=rg;
		parent.add(*this);
	}
	ToggleGroup& ToggleButton::getParent(){
		return parent;
	}
	void ToggleButton::removeParent(ToggleGroup& rg){
		parent.remove(this->getIndex());
		setIndex(-1);
	}
	void ToggleButton::draw(std::shared_ptr<D2DHandle>& d2d){ //DrawText measuring are just magic numbers made to fit the image proportions. Use your own proportions when using another image.
		if(isEnabled()==true){
			if(isSelected()==true){
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				std::wstring wtext(getText());
				IDWriteTextFormat* dwtf;
				d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
				d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				ID2D1SolidColorBrush* scb;
				d2d->target->CreateSolidColorBrush(ColorF(ToggleButton::fRGBA[0],ToggleButton::fRGBA[1],ToggleButton::fRGBA[2],ToggleButton::fRGBA[3]*opacity),&scb);
				d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
				d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+((float)(getBounds().right-getBounds().left)/50.0f)+getLeftPadding(),(float)getBounds().top+((float)(getBounds().bottom-getBounds().top)/10.0f)+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
				d2d->textformat.reset();
				d2d->solidbrush.reset();
				d2d->bmpscaler.reset();
			}//Selected ToggleButton
			else{
				if(isPressed()==true){
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					std::wstring wtext(getText());
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(ToggleButton::fRGBA[0],ToggleButton::fRGBA[1],ToggleButton::fRGBA[2],ToggleButton::fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+((float)(getBounds().right-getBounds().left)/50.0f)+getLeftPadding(),(float)getBounds().top+((float)(getBounds().bottom-getBounds().top)/10.0f)+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Pressed ToggleButton
				else if(isHovered()==true){
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton_hovered.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					std::wstring wtext(getText());
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(ToggleButton::fRGBA[0],ToggleButton::fRGBA[1],ToggleButton::fRGBA[2],ToggleButton::fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+((float)(getBounds().right-getBounds().left)/50.0f)+getLeftPadding(),(float)getBounds().top+((float)(getBounds().bottom-getBounds().top)/10.0f)+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Hovered ToggleButton
				else{
					IWICBitmapDecoder* wicbd;
					d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
					d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
					IWICBitmapFrameDecode* wicbfd;
					d2d->bmpdecoder->GetFrame(0,&wicbfd);
					d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
					IWICBitmapScaler* wicbs;
					d2d->imgfactory->CreateBitmapScaler(&wicbs);
					d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
					d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
					IWICFormatConverter* wicfc;
					d2d->imgfactory->CreateFormatConverter(&wicfc);
					d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
					d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
					ID2D1Bitmap* wicb;
					d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
					d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
					std::wstring wtext(getText());
					IDWriteTextFormat* dwtf;
					d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
					d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
					d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
					ID2D1SolidColorBrush* scb;
					d2d->target->CreateSolidColorBrush(ColorF(ToggleButton::fRGBA[0],ToggleButton::fRGBA[1],ToggleButton::fRGBA[2],ToggleButton::fRGBA[3]*opacity),&scb);
					d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
					d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+((float)(getBounds().right-getBounds().left)/50.0f)+getLeftPadding(),(float)getBounds().top+((float)(getBounds().bottom-getBounds().top)/10.0f)+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
					d2d->bmpdecoder.reset();
					d2d->bmpframedecoder.reset();
					d2d->formatconverter.reset();
					d2d->bmp.reset();
					d2d->textformat.reset();
					d2d->solidbrush.reset();
					d2d->bmpscaler.reset();
				}//Normal ToggleButton
			}//Unselected ToggleButton
		}//Enabled ToggleButton
		else{
			IWICBitmapDecoder* wicbd;
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
			d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
			IWICBitmapFrameDecode* wicbfd;
			d2d->bmpdecoder->GetFrame(0,&wicbfd);
			d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
			IWICBitmapScaler* wicbs;
			d2d->imgfactory->CreateBitmapScaler(&wicbs);
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			IWICFormatConverter* wicfc;
			d2d->imgfactory->CreateFormatConverter(&wicfc);
			d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
			d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			ID2D1Bitmap* wicb;
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
			if(wicb==NULL){
				MessageBox(NULL,L"This thing is null bmp",L"NULL",MB_OK);
			}
			d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
			std::wstring wtext(getText());
			IDWriteTextFormat* dwtf;
			d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
			d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
			d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			ID2D1SolidColorBrush* scb;
			d2d->target->CreateSolidColorBrush(ColorF(ToggleButton::fRGBA[0],ToggleButton::fRGBA[1],ToggleButton::fRGBA[2],ToggleButton::fRGBA[3]*opacity),&scb);
			d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
			d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+((float)(getBounds().right-getBounds().left)/50.0f)+getLeftPadding(),(float)getBounds().top+((float)(getBounds().bottom-getBounds().top)/10.0f)+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
			d2d->bmpdecoder.reset();
			d2d->bmpframedecoder.reset();
			d2d->formatconverter.reset();
			d2d->bmp.reset();
			d2d->textformat.reset();
			d2d->solidbrush.reset();
			d2d->bmpscaler.reset();
		}//Disabled ToggleButton
	}

	ImageView::ImageView(wchar_t* file): WindowBase(1,file){
		ImageView::path=file;
		states.push_back(NONE);
	}
	void ImageView::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
	}
	RECT ImageView::getBounds(){
		return bounds;
	}
	void ImageView::setFile(wchar_t* file){
		path=file;
	}
	wchar_t* ImageView::getFilePath(){
		return path;
	}
	void ImageView::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
				if(foundinstates==true){
					states.push_back(VISIBLE);
				}
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool ImageView::isVisible(){
		bool visible=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	void ImageView::draw(std::shared_ptr<D2DHandle>& d2d){
		IWICBitmapDecoder* wicbd;
		d2d->imgfactory->CreateDecoderFromFilename(getFilePath(),NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
		d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
		IWICBitmapFrameDecode* wicbfd;
		d2d->bmpdecoder->GetFrame(0,&wicbfd);
		d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
		IWICBitmapScaler* wicbs;
		d2d->imgfactory->CreateBitmapScaler(&wicbs);
		d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		IWICFormatConverter* wicfc;
		d2d->imgfactory->CreateFormatConverter(&wicfc);
		d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
		d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		ID2D1Bitmap* wicb;
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
		d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
		d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
		d2d->bmpdecoder.reset();
		d2d->bmpframedecoder.reset();
		d2d->formatconverter.reset();
		d2d->bmpscaler.reset();
		d2d->bmp.reset();
	}
	ImageButton::ImageButton(wchar_t* file,wchar_t* text):WindowBase(text){
		disabledpath=pressedpath=hoveredpath=enabledpath=file;
		ImageButton::text=text;
		setForeground(0,0,0);
		setTextSize(12.0f);
		setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
		setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		setFont(L"Microsoft Sans Serif");
	}
	ImageButton::ImageButton(wchar_t* enabledfile,wchar_t* disabledfile,wchar_t* pressedfile,wchar_t* hoveredfile,wchar_t* text):WindowBase(text){
		enabledpath=enabledfile;
		disabledpath=disabledfile;
		pressedpath=pressedfile;
		hoveredpath=hoveredfile;
		states.push_back(NONE);
		ImageButton::text=text;
		setForeground(0,0,0);
		setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
		setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
	}
	void ImageButton::setBounds(int left,int top,int right,int bottom){
		ImageButton::bounds.left=left;
		ImageButton::bounds.top=top;
		ImageButton::bounds.right=right;
		ImageButton::bounds.bottom=bottom;
	}
	RECT ImageButton::getBounds(){
		RECT r;
		r.left=ImageButton::bounds.left;
		r.top=ImageButton::bounds.top;
		r.right=ImageButton::bounds.right;
		r.bottom=ImageButton::bounds.bottom;
		return r;
	}
	void ImageButton::setText(wchar_t* text){
		ImageButton::text=text;
	}
	wchar_t* ImageButton::getText(){
		return ImageButton::text;
	}
	void ImageButton::setTextSize(float px){
		ImageButton::textsize=px;
	}
	float ImageButton::getTextSize(){
		return ImageButton::textsize;
	}
	void ImageButton::setForeground(int R,int G,int B,int A){
		ImageButton::iRGBA[0]=R;
		ImageButton::iRGBA[1]=G;
		ImageButton::iRGBA[2]=B;
		ImageButton::iRGBA[3]=A;
		ImageButton::fRGBA[0]=(float)R/255.0f;
		ImageButton::fRGBA[1]=(float)G/255.0f;
		ImageButton::fRGBA[2]=(float)B/255.0f;
		ImageButton::fRGBA[3]=(float)A/255.0f;
	}
	void ImageButton::setForeground(float R,float G,float B,float A){
		ImageButton::fRGBA[0]=R;
		ImageButton::fRGBA[1]=G;
		ImageButton::fRGBA[2]=B;
		ImageButton::fRGBA[3]=A;
		ImageButton::iRGBA[0]=(int)(R*255.0f);
		ImageButton::iRGBA[1]=(int)(G*255.0f);
		ImageButton::iRGBA[2]=(int)(B*255.0f);
		ImageButton::iRGBA[3]=(int)(A*255.0f);
	}
	float* ImageButton::getForegroundFloat(){
		return ImageButton::fRGBA;
	}
	int* ImageButton::getForegroundInt(){
		return ImageButton::iRGBA;
	}
	void ImageButton::setFont(wchar_t* font){
		ImageButton::font=font;
	}
	wchar_t* ImageButton::getFont(){
		return ImageButton::font;
	}
	void ImageButton::setHorizontalTextAlignment(const int H){
		ImageButton::hAlignment=const_cast<int&>(H);
	}
	int ImageButton::getHorizontalTextAlignment(){
		return ImageButton::hAlignment;
	}
	void ImageButton::setVerticalTextAlignment(const int V){
		ImageButton::vAlignment=const_cast<int&>(V);
	}
	int ImageButton::getVerticalTextAlignment(){
		return ImageButton::vAlignment;
	}
	void ImageButton::setPadding(int left,int top,int right,int bottom){
		ImageButton::leftPadding=left;
		ImageButton::topPadding=top;
		ImageButton::rightPadding=right;
		ImageButton::bottomPadding=bottom;
		if(ImageButton::rightPadding==-1){
			ImageButton::rightPadding=ImageButton::leftPadding;
		}
		if(ImageButton::bottomPadding==-1){
			ImageButton::bottomPadding=ImageButton::topPadding;
		}
	}
	int ImageButton::getLeftPadding(){
		return ImageButton::leftPadding;
	}
	int ImageButton::getTopPadding(){
		return ImageButton::topPadding;
	}
	int ImageButton::getRightPadding(){
		return ImageButton::rightPadding;
	}
	int ImageButton::getBottomPadding(){
		return ImageButton::bottomPadding;
	}
	void ImageButton::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled==true){
			for(int i=0;i<ImageButton::states.size();i++){
				if(ImageButton::states.at(i)==ENABLED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ImageButton::states.push_back(ENABLED);
			}
		}
		else{
			for(int i=0;i<ImageButton::states.size();i++){
				if(ImageButton::states.at(i)==ENABLED){
					ImageButton::states.erase(ImageButton::states.begin()+i);
					break;
				}
			}
		}
	}
	void ImageButton::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(ImageButton::states.size()!=0){
				for(int i=0;i<ImageButton::states.size();i++){
					if(ImageButton::states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
				if(foundinstates==false){
					ImageButton::states.push_back(VISIBLE);
				}
			}
		}
		else{
			if(ImageButton::states.size()!=0){
				for(int i=0;i<ImageButton::states.size();i++){
					if(ImageButton::states.at(i)==VISIBLE){
						ImageButton::states.erase(ImageButton::states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool ImageButton::isVisible(){
		bool visible=false;
		if(ImageButton::states.size()!=0){
			for(int i=0;i<ImageButton::states.size();i++){
				if(ImageButton::states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	bool ImageButton::isEnabled(){
		bool enabled=false;
		for(int i=0;i<ImageButton::states.size();i++){
			if(ImageButton::states.at(i)==ENABLED){
				enabled=true;
				break;
			}
		}
		return enabled;
	}
	void ImageButton::setHovered(bool hovered){
		bool foundinstates=false;
		if(hovered==true){
			for(int i=0;i<ImageButton::states.size();i++){
				if(ImageButton::states.at(i)==HOVERED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ImageButton::states.push_back(HOVERED);
			}
		}
		else{
			for(int i=0;i<ImageButton::states.size();i++){
				if(ImageButton::states.at(i)==HOVERED){
					ImageButton::states.erase(ImageButton::states.begin()+i);
					break;
				}
			}
		}
	}
	bool ImageButton::isHovered(){
		bool hovered=false;
		for(int i=0;i<ImageButton::states.size();i++){
			if(ImageButton::states.at(i)==HOVERED){
				hovered=true;
				break;
			}
		}	
		return hovered;
	}
	void ImageButton::setPressed(bool pressed){
		bool foundinstates=false;
		if(pressed==true){
			for(int i=0;i<ImageButton::states.size();i++){
				if(ImageButton::states.at(i)==PRESSED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ImageButton::states.push_back(PRESSED);
			}
		}
		else{
			for(int i=0;i<ImageButton::states.size();i++){
				if(ImageButton::states.at(i)==PRESSED){
					ImageButton::states.erase(ImageButton::states.begin()+i);
					break;
				}
			}
		}
	}
	bool ImageButton::isPressed(){
		bool pressed=false;
		for(int i=0;i<ImageButton::states.size();i++){
			if(ImageButton::states.at(i)==PRESSED){
				pressed=true;
				break;
			}		
		}
		return pressed;
	}
	void ImageButton::draw(std::shared_ptr<D2DHandle>& d2d){
		std::wstring wtext(getText());
		if(isEnabled()==true){
			if(isPressed()==true&&(wcscmp(pressedpath,L"")!=0)){
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(pressedpath,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				IDWriteTextFormat* dwtf;
				d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_REGULAR,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
				d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
				ID2D1SolidColorBrush* scb;
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
				d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
				d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
				d2d->bmp.reset();
				d2d->formatconverter.reset();
				d2d->bmpscaler.reset();
				d2d->bmpframedecoder.reset();
				d2d->bmpdecoder.reset();
				d2d->textformat.reset();
				d2d->solidbrush.reset();
			}//Pressed ImageButton
			else if(isHovered()==true&&(wcscmp(hoveredpath,L"")!=0)){
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(hoveredpath,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				IDWriteTextFormat* dwtf;
				d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_REGULAR,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
				d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
				ID2D1SolidColorBrush* scb;
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
				d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
				d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
				d2d->bmp.reset();
				d2d->formatconverter.reset();
				d2d->bmpscaler.reset();
				d2d->bmpframedecoder.reset();
				d2d->bmpdecoder.reset();
				d2d->textformat.reset();
				d2d->solidbrush.reset();
			}//Hovered ImageButton
			else if(wcscmp(enabledpath,L"")!=0){
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(enabledpath,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				if(wicb==NULL){
					MessageBox(NULL,L"Hello this thing is null bmp",L"Error",MB_OK);
				}
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				IDWriteTextFormat* dwtf;
				d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_REGULAR,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
				d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
				ID2D1SolidColorBrush* scb;
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
				d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
				d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
				d2d->bmp.reset();
				d2d->formatconverter.reset();
				d2d->bmpscaler.reset();
				d2d->bmpframedecoder.reset();
				d2d->bmpdecoder.reset();
				d2d->textformat.reset();
				d2d->solidbrush.reset();
			}//Normal enabled ImageButton
		}//Enabled ImageButton
		else if(wcscmp(disabledpath,L"")!=0){
			IWICBitmapDecoder* wicbd;
			d2d->imgfactory->CreateDecoderFromFilename(disabledpath,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
			d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
			IWICBitmapFrameDecode* wicbfd;
			d2d->bmpdecoder->GetFrame(0,&wicbfd);
			d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
			IWICBitmapScaler* wicbs;
			d2d->imgfactory->CreateBitmapScaler(&wicbs);
			d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			IWICFormatConverter* wicfc;
			d2d->imgfactory->CreateFormatConverter(&wicfc);
			d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
			d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			ID2D1Bitmap* wicb;
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
			d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
			d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			IDWriteTextFormat* dwtf;
			d2d->dwritefactory->CreateTextFormat(font,NULL,DWRITE_FONT_WEIGHT_REGULAR,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
			d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
			ID2D1SolidColorBrush* scb;
			d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),&scb);
			d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
			d2d->target->DrawTextW(wtext.c_str(),wtext.length(),d2d->textformat.get(),RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),d2d->solidbrush.get());
			d2d->bmp.reset();
			d2d->formatconverter.reset();
			d2d->bmpscaler.reset();
			d2d->bmpframedecoder.reset();
			d2d->bmpdecoder.reset();
			d2d->textformat.reset();
			d2d->solidbrush.reset();
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
		if(isString()==true){
			return t;
		}
		else{
			return (wchar_t*&)(L"");
		}
	}
	template<> newifstream& ListItem<newifstream>::getData(){
		if(isFile()==true){
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
		if(enabled==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==ENABLED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
		if(enabled==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==ENABLED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
		if(pressed==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==PRESSED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
		if(pressed==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==PRESSED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
		if(hovered==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==HOVERED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
		if(hovered==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==HOVERED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
		if(selected==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==SELECTED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
		if(selected==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==SELECTED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
	template<> void ComboBox<ListItem<wchar_t*>>::setTextSize(float px){
		ComboBox::textsize=px;
		tb->setTextSize(px);
	}
	template<> void ComboBox<ListItem<newifstream>>::setTextSize(float px){
		ComboBox::textsize=px;
		tb->setTextSize(px);
	}
	template<> float ComboBox<ListItem<wchar_t*>>::getTextSize(){
		return ComboBox::textsize;
	}
	template<> float ComboBox<ListItem<newifstream>>::getTextSize(){
		return ComboBox::textsize;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setForeground(int R,int G,int B,int A){
		ComboBox::iRGBA[0]=R;
		ComboBox::iRGBA[1]=G;
		ComboBox::iRGBA[2]=B;
		ComboBox::iRGBA[3]=A;
		ComboBox::fRGBA[0]=(float)R/255.0f;
		ComboBox::fRGBA[1]=(float)G/255.0f;
		ComboBox::fRGBA[2]=(float)B/255.0f;
		ComboBox::fRGBA[3]=(float)A/255.0f;
		tb->setForeground(R,G,B,A);
	}
	template<> void ComboBox<ListItem<newifstream>>::setForeground(int R,int G,int B,int A){
		ComboBox::iRGBA[0]=R;
		ComboBox::iRGBA[1]=G;
		ComboBox::iRGBA[2]=B;
		ComboBox::iRGBA[3]=A;
		ComboBox::fRGBA[0]=(float)R/255.0f;
		ComboBox::fRGBA[1]=(float)G/255.0f;
		ComboBox::fRGBA[2]=(float)B/255.0f;
		ComboBox::fRGBA[3]=(float)A/255.0f;
		tb->setForeground(R,G,B,A);
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setForeground(float R,float G,float B,float A){
		ComboBox::fRGBA[0]=R;
		ComboBox::fRGBA[1]=G;
		ComboBox::fRGBA[2]=B;
		ComboBox::fRGBA[3]=A;
		ComboBox::iRGBA[0]=(int)(R*255.0f);
		ComboBox::iRGBA[1]=(int)(G*255.0f);
		ComboBox::iRGBA[2]=(int)(B*255.0f);
		ComboBox::iRGBA[3]=(int)(A*255.0f);
		tb->setForeground(R,G,B,A);
	}
	template<> void ComboBox<ListItem<newifstream>>::setForeground(float R,float G,float B,float A){
		ComboBox::fRGBA[0]=R;
		ComboBox::fRGBA[1]=G;
		ComboBox::fRGBA[2]=B;
		ComboBox::fRGBA[3]=A;
		ComboBox::iRGBA[0]=(int)(R*255.0f);
		ComboBox::iRGBA[1]=(int)(G*255.0f);
		ComboBox::iRGBA[2]=(int)(B*255.0f);
		ComboBox::iRGBA[3]=(int)(A*255.0f);
		tb->setForeground(R,G,B,A);
	}
	template<> float* ComboBox<ListItem<wchar_t*>>::getForegroundFloat(){
		return ComboBox::fRGBA;
	}
	template<> float* ComboBox<ListItem<newifstream>>::getForegroundFloat(){
		return ComboBox::fRGBA;
	}
	template<> int* ComboBox<ListItem<wchar_t*>>::getForegroundInt(){
		return ComboBox::iRGBA;
	}
	template<> int* ComboBox<ListItem<newifstream>>::getForegroundInt(){
		return ComboBox::iRGBA;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
		tb->setBounds(left,top,right-30,bottom);
		dropdown->setBounds(tb->getBounds().right,top,right,bottom);
		vScrollBar->setBounds(getBounds().right-20,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight());
	}
	template<> void ComboBox<ListItem<newifstream>>::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
		tb->setBounds(left,top,right-30,bottom);
		dropdown->setBounds(tb->getBounds().right,top,right,bottom);
		vScrollBar->setBounds(getBounds().right-20,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight());
	}
	template<> RECT ComboBox<ListItem<wchar_t*>>::getBounds(){
		RECT r;
		r.left=ComboBox::bounds.left;
		r.top=ComboBox::bounds.top;
		r.right=ComboBox::bounds.right;
		r.bottom=ComboBox::bounds.bottom;
		return r;
	}
	template<> RECT ComboBox<ListItem<newifstream>>::getBounds(){
		RECT r;
		r.left=ComboBox::bounds.left;
		r.top=ComboBox::bounds.top;
		r.right=ComboBox::bounds.right;
		r.bottom=ComboBox::bounds.bottom;
		return r;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setText(wchar_t* text){
		ComboBox::text=text;
		tb->setText(text);
	}
	template<> void ComboBox<ListItem<newifstream>>::setText(wchar_t* text){
		ComboBox::text=text;
		tb->setText(text);
	}
	template<> wchar_t* ComboBox<ListItem<wchar_t*>>::getText(){
		return ComboBox::text;
	}

	template<> wchar_t* ComboBox<ListItem<newifstream>>::getText(){
		return ComboBox::text;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setHorizontalTextAlignment(const int H){
		ComboBox::hAlignment=const_cast<int&>(H);
		tb->setHorizontalTextAlignment(H);
	}
	template<> void ComboBox<ListItem<newifstream>>::setHorizontalTextAlignment(const int H){
		ComboBox::hAlignment=const_cast<int&>(H);
		tb->setHorizontalTextAlignment(H);
	}
	template<> int ComboBox<ListItem<wchar_t*>>::getHorizontalTextAlignment(){
		return ComboBox::hAlignment;
	}
	template<> int ComboBox<ListItem<newifstream>>::getHorizontalTextAlignment(){
		return ComboBox::hAlignment;
	}
	template<> int ComboBox<ListItem<wchar_t*>>::getVerticalTextAlignment(){
		return ComboBox::vAlignment;
	}
	template<> int ComboBox<ListItem<newifstream>>::getVerticalTextAlignment(){
		return ComboBox::vAlignment;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setVerticalTextAlignment(const int V){
		ComboBox::vAlignment=const_cast<int&>(V);
		tb->setVerticalTextAlignment(V);
	}
	template<> void ComboBox<ListItem<newifstream>>::setVerticalTextAlignment(const int V){
		ComboBox::vAlignment=const_cast<int&>(V);
		tb->setVerticalTextAlignment(V);
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setPadding(int left,int top,int right,int bottom){
		ComboBox::leftPadding=left;
		ComboBox::topPadding=top;
		ComboBox::rightPadding=right;
		ComboBox::bottomPadding=bottom;
		if(ComboBox::rightPadding==-1){
			ComboBox::rightPadding=ComboBox::leftPadding;
		}
		if(ComboBox::bottomPadding==-1){
			ComboBox::bottomPadding=ComboBox::topPadding;
		}
		tb->setPadding(left,top,right,bottom);
	}
	template<> void ComboBox<ListItem<newifstream>>::setPadding(int left,int top,int right,int bottom){
		ComboBox::leftPadding=left;
		ComboBox::topPadding=top;
		ComboBox::rightPadding=right;
		ComboBox::bottomPadding=bottom;
		if(ComboBox::rightPadding==-1){
			ComboBox::rightPadding=ComboBox::leftPadding;
		}
		if(ComboBox::bottomPadding==-1){
			ComboBox::bottomPadding=ComboBox::topPadding;
		}
		tb->setPadding(left,top,right,bottom);
	}
	template<> int ComboBox<ListItem<wchar_t*>>::getLeftPadding(){
		return ComboBox::leftPadding;
	}
	template<> int ComboBox<ListItem<newifstream>>::getLeftPadding(){
		return ComboBox::leftPadding;
	}
	template<> int ComboBox<ListItem<wchar_t*>>::getTopPadding(){
		return ComboBox::topPadding;
	}
	template<> int ComboBox<ListItem<newifstream>>::getTopPadding(){
		return ComboBox::topPadding;
	}
	template<> int ComboBox<ListItem<wchar_t*>>::getRightPadding(){
		return ComboBox::rightPadding;
	}
	template<> int ComboBox<ListItem<newifstream>>::getRightPadding(){
		return ComboBox::rightPadding;
	}
	template<> int ComboBox<ListItem<wchar_t*>>::getBottomPadding(){
		return ComboBox::bottomPadding;
	}
	template<> int ComboBox<ListItem<newifstream>>::getBottomPadding(){
		return ComboBox::bottomPadding;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(ComboBox::states.size()!=0){
				for(int i=0;i<ComboBox::states.size();i++){
					if(ComboBox::states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
				if(foundinstates==false){
					ComboBox::states.push_back(VISIBLE);
				}
			}
		}
		else{
			if(ComboBox::states.size()!=0){
				for(int i=0;i<ComboBox::states.size();i++){
					if(ComboBox::states.at(i)==VISIBLE){
						ComboBox::states.erase(ComboBox::states.begin()+i);
						break;
					}
				}
			}
		}
		tb->setVisible(visible);
	}
	template<> void ComboBox<ListItem<newifstream>>::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(ComboBox::states.size()!=0){
				for(int i=0;i<ComboBox::states.size();i++){
					if(ComboBox::states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
				if(foundinstates==false){
					ComboBox::states.push_back(VISIBLE);
				}
			}
		}
		else{
			if(ComboBox::states.size()!=0){
				for(int i=0;i<ComboBox::states.size();i++){
					if(ComboBox::states.at(i)==VISIBLE){
						ComboBox::states.erase(ComboBox::states.begin()+i);
						break;
					}
				}
			}
		}
		tb->setVisible(visible);
	}
	template<> bool ComboBox<ListItem<wchar_t*>>::isVisible(){
		bool visible=false;
		if(ComboBox::states.size()!=0){
			for(int i=0;i<ComboBox::states.size();i++){
				if(ComboBox::states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	template<> bool ComboBox<ListItem<newifstream>>::isVisible(){
		bool visible=false;
		if(ComboBox::states.size()!=0){
			for(int i=0;i<ComboBox::states.size();i++){
				if(ComboBox::states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled==true){
			for(int i=0;i<ComboBox::states.size();i++){
				if(ComboBox::states.at(i)==ENABLED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ComboBox::states.push_back(ENABLED);
			}
		}
		else{
			for(int i=0;i<ComboBox::states.size();i++){
				if(ComboBox::states.at(i)==ENABLED){
					ComboBox::states.erase(ComboBox::states.begin()+i);
					break;
				}
			}
		}
		tb->setEnabled(enabled);
		dropdown->setEnabled(enabled);
	}
	template<> void ComboBox<ListItem<newifstream>>::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled==true){
			for(int i=0;i<ComboBox::states.size();i++){
				if(ComboBox::states.at(i)==ENABLED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ComboBox::states.push_back(ENABLED);
			}
		}
		else{
			for(int i=0;i<ComboBox::states.size();i++){
				if(ComboBox::states.at(i)==ENABLED){
					ComboBox::states.erase(ComboBox::states.begin()+i);
					break;
				}
			}
		}
		tb->setEnabled(enabled);
		dropdown->setEnabled(enabled);
	}
	template<> bool ComboBox<ListItem<wchar_t*>>::isEnabled(){
		bool enabled=false;
		for(int i=0;i<ComboBox::states.size();i++){
			if(ComboBox::states.at(i)==ENABLED){
				enabled=true;
				break;
			}
		}
		return enabled;
	}
	template<> bool ComboBox<ListItem<newifstream>>::isEnabled(){
		bool enabled=false;
		for(int i=0;i<ComboBox::states.size();i++){
			if(ComboBox::states.at(i)==ENABLED){
				enabled=true;
				break;
			}
		}
		return enabled;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setFont(wchar_t* font){
		ComboBox::font=font;
		tb->setFont(font);
	}
	template<> void ComboBox<ListItem<newifstream>>::setFont(wchar_t* font){
		ComboBox::font=font;
		tb->setFont(font);
	}
	template<> wchar_t* ComboBox<ListItem<wchar_t*>>::getFont(){
		return ComboBox::font;
	}
	template<> wchar_t* ComboBox<ListItem<newifstream>>::getFont(){
		return ComboBox::font;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setEditable(bool editable){
		bool foundinstates=false;
		if(editable==true){
			for(int i=0;i<ComboBox::states.size();i++){
				if(ComboBox::states.at(i)==EDITABLE){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ComboBox::states.push_back(EDITABLE);
			}
		}
		else{
			for(int i=0;i<ComboBox::states.size();i++){
				if(ComboBox::states.at(i)==EDITABLE){
					ComboBox::states.erase(ComboBox::states.begin()+i);
					break;
				}
			}
		}
		tb->setEditable(editable);
	}
	template<> void ComboBox<ListItem<newifstream>>::setEditable(bool editable){
		bool foundinstates=false;
		if(editable==true){
			for(int i=0;i<ComboBox::states.size();i++){
				if(ComboBox::states.at(i)==EDITABLE){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ComboBox::states.push_back(EDITABLE);
			}
		}
		else{
			for(int i=0;i<ComboBox::states.size();i++){
				if(ComboBox::states.at(i)==EDITABLE){
					ComboBox::states.erase(ComboBox::states.begin()+i);
					break;
				}
			}
		}
		tb->setEditable(editable);
	}
	template<> bool ComboBox<ListItem<wchar_t*>>::isEditable(){
		bool editable=false;
		for(int i=0;i<ComboBox::states.size();i++){
			if(ComboBox::states.at(i)==EDITABLE){
				editable=true;
				break;
			}
		}
		return editable;
	}
	template<> bool ComboBox<ListItem<newifstream>>::isEditable(){
		bool editable=false;
		for(int i=0;i<ComboBox::states.size();i++){
			if(ComboBox::states.at(i)==EDITABLE){
				editable=true;
				break;
			}
		}
		return editable;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setFocus(bool focus){
		bool foundinstates=false;
		if(focus==true){
			for(int i=0;i<ComboBox::states.size();i++){
				if(ComboBox::states.at(i)==FOCUSED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ComboBox::states.push_back(FOCUSED);
			}
		}
		else{
			for(int i=0;i<ComboBox::states.at(i);i++){
				if(ComboBox::states.at(i)==FOCUSED){
					ComboBox::states.erase(ComboBox::states.begin()+i);
					break;
				}
			}
		}
		tb->setFocus(focus);
	}
	template<> void ComboBox<ListItem<newifstream>>::setFocus(bool focus){
		bool foundinstates=false;
		if(focus==true){
			for(int i=0;i<ComboBox::states.size();i++){
				if(ComboBox::states.at(i)==FOCUSED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ComboBox::states.push_back(FOCUSED);
			}
		}
		else{
			for(int i=0;i<ComboBox::states.at(i);i++){
				if(ComboBox::states.at(i)==FOCUSED){
					ComboBox::states.erase(ComboBox::states.begin()+i);
					break;
				}
			}
		}
		tb->setFocus(focus);
	}
	template<> bool ComboBox<ListItem<wchar_t*>>::hasFocus(){
		bool focus=false;
		for(int i=0;i<ComboBox::states.size();i++){
			if(ComboBox::states.at(i)==FOCUSED){
				focus=true;
				break;
			}
		}
		return focus;
	}
	template<> bool ComboBox<ListItem<newifstream>>::hasFocus(){
		bool focus=false;
		for(int i=0;i<ComboBox::states.size();i++){
			if(ComboBox::states.at(i)==FOCUSED){
				focus=true;
				break;
			}
		}
		return focus;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setSelectedItem(ListItem<wchar_t*>& t){
		selecteditem=t;
		auto it=std::find(list.begin(),list.end(),t);
		int c=std::distance(list.begin(),it);
		setSelectedIndex(c);
	}
	template<> void ComboBox<ListItem<newifstream>>::setSelectedItem(ListItem<newifstream>& t){
		selecteditem=t;
		std::vector<ListItem<newifstream>>::iterator it=std::find(list.begin(),list.end(),t);
		int c=std::distance(list.begin(),it);
		setSelectedIndex(c);
	}
	template<> ListItem<wchar_t*>& ComboBox<ListItem<wchar_t*>>::getSelectedItem(){
		return selecteditem;
	}
	template<> ListItem<newifstream>& ComboBox<ListItem<newifstream>>::getSelectedItem(){
		return selecteditem;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setSelectedIndex(int index){
		ComboBox::index=index;
		for(int i=0;i<list.size();i++){
			list.at(i).setSelected(false);
		}
		list.at(index).setSelected(true);
		setText(list.at(index).getData());
	}
	template<> void ComboBox<ListItem<newifstream>>::setSelectedIndex(int index){
		ComboBox::index=index;
		for(int i=0;i<list.size();i++){
			list.at(i).setSelected(false);
		}
		list.at(index).setSelected(true);
		setText(list.at(index).getData().getFilename());
	}
	template<> int ComboBox<ListItem<wchar_t*>>::getSelectedIndex(){
		return ComboBox::index;
	}
	template<> int ComboBox<ListItem<newifstream>>::getSelectedIndex(){
		return ComboBox::index;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::remove(int index){
		list.erase(list.begin()+index);
		int itemheight=((int)list.at(index).getTextSize())+getTopPadding()+getBottomPadding();
		setTotalHeight(getTotalHeight()-itemheight);
	}
	template<> void ComboBox<ListItem<newifstream>>::remove(int index){
		list.erase(list.begin()+index);
		int itemheight=((int)list.at(index).getTextSize())+getTopPadding()+getBottomPadding();
		setTotalHeight(getTotalHeight()-itemheight);
	}
	template<> void ComboBox<ListItem<wchar_t*>>::add(ListItem<wchar_t*> t){
		int itemheight=((int)t.getTextSize())+getTopPadding()+getBottomPadding();
		int top=0;
		if(list.size()!=0){
			top=list.at(list.size()-1).getBounds().bottom;
		}
		t.setBounds(0,top,getBounds().right,top+itemheight);
		list.push_back(t);
		setTotalHeight(getTotalHeight()+itemheight);
	}
	template<> void ComboBox<ListItem<newifstream>>::add(ListItem<newifstream> t){
		int itemheight=((int)t.getTextSize())+getTopPadding()+getBottomPadding();
		int top=0;
		if(list.size()!=0){
			top=list.at(list.size()-1).getBounds().bottom;
		}
		t.setBounds(0,top,getBounds().right,top+itemheight);
		list.push_back(t);
		setTotalHeight(getTotalHeight()+itemheight);
	}
	template<> void ComboBox<ListItem<wchar_t*>>::addAll(std::vector<ListItem<wchar_t*>> ts){
		for(ListItem<wchar_t*>& t:ts){
			int itemheight=((int)getTextSize())+getTopPadding()+getBottomPadding();
			int top=0;
			if(list.size()!=0){
				top=list.at(list.size()-1).getBounds().bottom;
			}
			t.setBounds(0,top,getBounds().right,top+itemheight);
			list.push_back(t);
			setTotalHeight(getTotalHeight()+itemheight);
		} 
	}
	template<> void ComboBox<ListItem<newifstream>>::addAll(std::vector<ListItem<newifstream>> ts){
		for(ListItem<newifstream>& t:ts){
			int itemheight=((int)t.getTextSize())+getTopPadding()+getBottomPadding();
			int top=0;
			if(list.size()!=0){
				top=list.at(list.size()-1).getBounds().bottom;
			}
			t.setBounds(0,top,getBounds().right,top+itemheight);
			list.push_back(t);
			setTotalHeight(getTotalHeight()+itemheight);
		} 
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setDropdownHeight(int height){
		ComboBox::dropdownheight=height;
		if(getDropdownHeight()<getTotalHeight()&&vScrollBar->isVerticalScrollingEnabled()==false){
			vScrollBar->enableVerticalScrolling();
			vScrollBar->setBounds(getBounds().right-20,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight());
			if(height!=0){
				vScrollBar->portions=(float)getTotalHeight()/(float)getDropdownHeight();
				if(vScrollBar->portions<1)vScrollBar->portions=1;	
			}
			else{
				vScrollBar->portions=1;
			}
		}
		else{
			vScrollBar->disableVerticalScrolling();
		}
	}
	template<> void ComboBox<ListItem<newifstream>>::setDropdownHeight(int height){
		ComboBox::dropdownheight=height;
		if(getDropdownHeight()<getTotalHeight()&&vScrollBar->isVerticalScrollingEnabled()==false){
			vScrollBar->enableVerticalScrolling();
			vScrollBar->setBounds(getBounds().right-20,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight());
			if(height!=0){
				vScrollBar->portions=(float)((float)getTotalHeight()/(float)getDropdownHeight());
				if(vScrollBar->portions<1)vScrollBar->portions=1;	
			}
			else{
				vScrollBar->portions=1;
				vScrollBar->position=0;
			}
		}
		else{
			vScrollBar->portions=1;
			vScrollBar->position=0;
			vScrollBar->disableVerticalScrolling();
		}
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setHoveredItemColor(int R,int G,int B,int A){
		iRGBA_hovered[0]=R;
		iRGBA_hovered[1]=G;
		iRGBA_hovered[2]=B;
		iRGBA_hovered[3]=A;
		fRGBA_hovered[0]=R/255.0f;
		fRGBA_hovered[1]=G/255.0f;
		fRGBA_hovered[2]=B/255.0f;
		fRGBA_hovered[3]=A/255.0f;
	}
	template<> void ComboBox<ListItem<newifstream>>::setHoveredItemColor(int R,int G,int B,int A){
		iRGBA_hovered[0]=R;
		iRGBA_hovered[1]=G;
		iRGBA_hovered[2]=B;
		iRGBA_hovered[3]=A;
		fRGBA_hovered[0]=R/255.0f;
		fRGBA_hovered[1]=G/255.0f;
		fRGBA_hovered[2]=B/255.0f;
		fRGBA_hovered[3]=A/255.0f;
	}
	template<> int* ComboBox<ListItem<wchar_t*>>::getHoveredItemColorInt(){
		return iRGBA_hovered;
	}
	template<> int* ComboBox<ListItem<newifstream>>::getHoveredItemColorInt(){
		return iRGBA_hovered;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setHoveredItemColor(float R,float G,float B,float A){
		fRGBA_hovered[0]=R;
		fRGBA_hovered[1]=G;
		fRGBA_hovered[2]=B;
		fRGBA_hovered[3]=A;
		iRGBA_hovered[0]=(int)(R*255.0f);
		iRGBA_hovered[1]=(int)(G*255.0f);
		iRGBA_hovered[2]=(int)(B*255.0f);
		iRGBA_hovered[3]=(int)(A*255.0f);
	}
	template<> void ComboBox<ListItem<newifstream>>::setHoveredItemColor(float R,float G,float B,float A){
		fRGBA_hovered[0]=R;
		fRGBA_hovered[1]=G;
		fRGBA_hovered[2]=B;
		fRGBA_hovered[3]=A;
		iRGBA_hovered[0]=(int)(R*255.0f);
		iRGBA_hovered[1]=(int)(G*255.0f);
		iRGBA_hovered[2]=(int)(B*255.0f);
		iRGBA_hovered[3]=(int)(A*255.0f);
	}
	template<> float* ComboBox<ListItem<wchar_t*>>::getHoveredItemColorFloat(){
		return fRGBA_hovered;
	}
	template<> float* ComboBox<ListItem<newifstream>>::getHoveredItemColorFloat(){
		return fRGBA_hovered;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setPressedItemColor(int R,int G,int B,int A){
		iRGBA_pressed[0]=R;
		iRGBA_pressed[1]=G;
		iRGBA_pressed[2]=B;
		iRGBA_pressed[3]=A;
		fRGBA_pressed[0]=R/255.0f;
		fRGBA_pressed[1]=G/255.0f;
		fRGBA_pressed[2]=B/255.0f;
		fRGBA_pressed[3]=A/255.0f;
	}
	template<> void ComboBox<ListItem<newifstream>>::setPressedItemColor(int R,int G,int B,int A){
		iRGBA_pressed[0]=R;
		iRGBA_pressed[1]=G;
		iRGBA_pressed[2]=B;
		iRGBA_pressed[3]=A;
		fRGBA_pressed[0]=R/255.0f;
		fRGBA_pressed[1]=G/255.0f;
		fRGBA_pressed[2]=B/255.0f;
		fRGBA_pressed[3]=A/255.0f;
	}
	template<> int* ComboBox<ListItem<wchar_t*>>::getPressedItemColorInt(){
		return iRGBA_pressed;
	}
	template<> int* ComboBox<ListItem<newifstream>>::getPressedItemColorInt(){
		return iRGBA_pressed;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setPressedItemColor(float R,float G,float B,float A){
		fRGBA_pressed[0]=R;
		fRGBA_pressed[1]=G;
		fRGBA_pressed[2]=B;
		fRGBA_pressed[3]=A;
		iRGBA_pressed[0]=(int)(R*255.0f);
		iRGBA_pressed[1]=(int)(G*255.0f);
		iRGBA_pressed[2]=(int)(B*255.0f);
		iRGBA_pressed[3]=(int)(A*255.0f);
	}
	template<> void ComboBox<ListItem<newifstream>>::setPressedItemColor(float R,float G,float B,float A){
		fRGBA_pressed[0]=R;
		fRGBA_pressed[1]=G;
		fRGBA_pressed[2]=B;
		fRGBA_pressed[3]=A;
		iRGBA_pressed[0]=(int)(R*255.0f);
		iRGBA_pressed[1]=(int)(G*255.0f);
		iRGBA_pressed[2]=(int)(B*255.0f);
		iRGBA_pressed[3]=(int)(A*255.0f);
	}
	template<> float* ComboBox<ListItem<wchar_t*>>::getPressedItemColorFloat(){
		return fRGBA_pressed;
	}
	template<> float* ComboBox<ListItem<newifstream>>::getPressedItemColorFloat(){
		return fRGBA_pressed;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setSelectedItemColor(int R,int G,int B,int A){
		iRGBA_selected[0]=R;
		iRGBA_selected[1]=G;
		iRGBA_selected[2]=B;
		iRGBA_selected[3]=A;
		fRGBA_selected[0]=R/255.0f;
		fRGBA_selected[1]=G/255.0f;
		fRGBA_selected[2]=B/255.0f;
		fRGBA_selected[3]=A/255.0f;
	}
	template<> void ComboBox<ListItem<newifstream>>::setSelectedItemColor(int R,int G,int B,int A){
		iRGBA_selected[0]=R;
		iRGBA_selected[1]=G;
		iRGBA_selected[2]=B;
		iRGBA_selected[3]=A;
		fRGBA_selected[0]=R/255.0f;
		fRGBA_selected[1]=G/255.0f;
		fRGBA_selected[2]=B/255.0f;
		fRGBA_selected[3]=A/255.0f;
	}
	template<> int* ComboBox<ListItem<wchar_t*>>::getSelectedItemColorInt(){
		return iRGBA_selected;
	}
	template<> int* ComboBox<ListItem<newifstream>>::getSelectedItemColorInt(){
		return iRGBA_selected;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setSelectedItemColor(float R,float G,float B,float A){
		fRGBA_selected[0]=R;
		fRGBA_selected[1]=G;
		fRGBA_selected[2]=B;
		fRGBA_selected[3]=A;
		iRGBA_selected[0]=(int)(R*255.0f);
		iRGBA_selected[1]=(int)(G*255.0f);
		iRGBA_selected[2]=(int)(B*255.0f);
		iRGBA_selected[3]=(int)(A*255.0f);
	}
	template<> void ComboBox<ListItem<newifstream>>::setSelectedItemColor(float R,float G,float B,float A){
		fRGBA_selected[0]=R;
		fRGBA_selected[1]=G;
		fRGBA_selected[2]=B;
		fRGBA_selected[3]=A;
		iRGBA_selected[0]=(int)(R*255.0f);
		iRGBA_selected[1]=(int)(G*255.0f);
		iRGBA_selected[2]=(int)(B*255.0f);
		iRGBA_selected[3]=(int)(A*255.0f);
	}
	template<> float* ComboBox<ListItem<wchar_t*>>::getSelectedItemColorFloat(){
		return fRGBA_selected;
	}
	template<> float* ComboBox<ListItem<newifstream>>::getSelectedItemColorFloat(){
		return fRGBA_selected;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setDisabledItemColor(int R,int G,int B,int A){
		iRGBA_disabled[0]=R;
		iRGBA_disabled[1]=G;
		iRGBA_disabled[2]=B;
		iRGBA_disabled[3]=A;
		fRGBA_disabled[0]=R/255.0f;
		fRGBA_disabled[1]=G/255.0f;
		fRGBA_disabled[2]=B/255.0f;
		fRGBA_disabled[3]=A/255.0f;
	}
	template<> void ComboBox<ListItem<newifstream>>::setDisabledItemColor(int R,int G,int B,int A){
		iRGBA_disabled[0]=R;
		iRGBA_disabled[1]=G;
		iRGBA_disabled[2]=B;
		iRGBA_disabled[3]=A;
		fRGBA_disabled[0]=R/255.0f;
		fRGBA_disabled[1]=G/255.0f;
		fRGBA_disabled[2]=B/255.0f;
		fRGBA_disabled[3]=A/255.0f;
	}
	template<> int* ComboBox<ListItem<wchar_t*>>::getDisabledItemColorInt(){
		return iRGBA_disabled;
	}
	template<> int* ComboBox<ListItem<newifstream>>::getDisabledItemColorInt(){
		return iRGBA_disabled;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setDisabledItemColor(float R,float G,float B,float A){
		fRGBA_disabled[0]=R;
		fRGBA_disabled[1]=G;
		fRGBA_disabled[2]=B;
		fRGBA_disabled[3]=A;
		iRGBA_disabled[0]=(int)(R*255.0f);
		iRGBA_disabled[1]=(int)(G*255.0f);
		iRGBA_disabled[2]=(int)(B*255.0f);
		iRGBA_disabled[3]=(int)(A*255.0f);
	}
	template<> void ComboBox<ListItem<newifstream>>::setDisabledItemColor(float R,float G,float B,float A){
		fRGBA_disabled[0]=R;
		fRGBA_disabled[1]=G;
		fRGBA_disabled[2]=B;
		fRGBA_disabled[3]=A;
		iRGBA_disabled[0]=(int)(R*255.0f);
		iRGBA_disabled[1]=(int)(G*255.0f);
		iRGBA_disabled[2]=(int)(B*255.0f);
		iRGBA_disabled[3]=(int)(A*255.0f);
	}
	template<> float* ComboBox<ListItem<wchar_t*>>::getDisabledItemColorFloat(){
		return ComboBox::fRGBA_disabled;
	}
	template<> float* ComboBox<ListItem<newifstream>>::getDisabledItemColorFloat(){
		return ComboBox::fRGBA_disabled;
	}
	template<> int ComboBox<ListItem<wchar_t*>>::getDropdownHeight(){
		return ComboBox::dropdownheight;
	}
	template<> int ComboBox<ListItem<newifstream>>::getDropdownHeight(){
		return ComboBox::dropdownheight;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setTotalHeight(int height){
		ComboBox::totalheight=height;
		if(getDropdownHeight()<getTotalHeight()&&vScrollBar->isVerticalScrollingEnabled()==false){
			vScrollBar->enableVerticalScrolling();
		}
		if(getDropdownHeight()!=0){
			vScrollBar->portions=(float)getTotalHeight()/(float)getDropdownHeight();
			if(vScrollBar->portions<1)vScrollBar->portions=1;
		}
		else{
			vScrollBar->portions=1;
		}
	}
	template<> void ComboBox<ListItem<newifstream>>::setTotalHeight(int height){
		ComboBox::totalheight=height;
		if(getDropdownHeight()<getTotalHeight()&&vScrollBar->isVerticalScrollingEnabled()==false){
			vScrollBar->enableVerticalScrolling();
		}
		if(getDropdownHeight()!=0){
			vScrollBar->portions=(float)getTotalHeight()/(float)getDropdownHeight();
			if(vScrollBar->portions<1){
				vScrollBar->portions=1;
				vScrollBar->position=0;
			}
		}
		else{
			vScrollBar->portions=1;
			vScrollBar->position=0;
		}
	}
	template<> int ComboBox<ListItem<wchar_t*>>::getTotalHeight(){
		return ComboBox::totalheight;
	}
	template<> int ComboBox<ListItem<newifstream>>::getTotalHeight(){
		return ComboBox::totalheight;
	}
	template<> void ComboBox<ListItem<wchar_t*>>::drawDropdown(std::shared_ptr<D2DHandle>& d2d){
		ID2D1SolidColorBrush* scb;
		d2d->target->CreateSolidColorBrush(ColorF(ColorF::White,opacity),&scb);
		d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
		d2d->target->FillRectangle(RectF(getBounds().left,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight()),d2d->solidbrush.get());
		d2d->target->PushAxisAlignedClip(RectF(getBounds().left,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight()),D2D1_ANTIALIAS_MODE_ALIASED);
		float topY=(getTotalHeight()/vScrollBar->portions)*vScrollBar->position;
		d2d->target->SaveDrawingState(d2d->targetstate.get());
		d2d->target->SetTransform(Matrix3x2F::Translation(0,-topY));
		for(int i=0;i<list.size();i++){
			if(list.at(i).isEnabled()==true){
				if(list.at(i).isSelected()==true){
					d2d->solidbrush->SetColor(ColorF(fRGBA_selected[0],fRGBA_selected[1],fRGBA_selected[2],fRGBA_selected[3]*opacity));
					d2d->target->FillRectangle(RectF(getBounds().left+list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,getBounds().left+list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.get());
				}
				else if(list.at(i).isPressed()==true){
					d2d->solidbrush->SetColor(ColorF(fRGBA_pressed[0],fRGBA_pressed[1],fRGBA_pressed[2],fRGBA_pressed[3]*opacity));
					d2d->target->FillRectangle(RectF(list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.get());
				}
				else if(list.at(i).isHovered()==true){
					d2d->solidbrush->SetColor(ColorF(fRGBA_hovered[0],fRGBA_hovered[1],fRGBA_hovered[2],fRGBA_hovered[3]*opacity));
					d2d->target->FillRectangle(RectF(list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.get());
				}
			}
			else{
				d2d->solidbrush->SetColor(ColorF(fRGBA_disabled[0],fRGBA_disabled[1],fRGBA_disabled[2],fRGBA_disabled[3]*opacity));
				d2d->target->FillRectangle(RectF(list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.get());
			}
			IDWriteTextFormat* dwtf;
			d2d->dwritefactory->CreateTextFormat(list.at(i).getFont(),NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,list.at(i).getTextSize()*(96.0f/72.0f),locale,&dwtf);
			d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
			IDWriteTextLayout* dwtl;
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.get(),list.at(i).getBounds().right-list.at(i).getBounds().left-getLeftPadding()-getRightPadding(),list.at(i).getBounds().bottom-list.at(i).getBounds().top-getBottomPadding()-getTopPadding(),&dwtl);
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+list.at(i).getBounds().top+getTopPadding()),d2d->textlayout.get(),d2d->solidbrush.get());
			d2d->textformat.reset();
			d2d->textlayout.reset();
		}
		d2d->solidbrush.reset();
		d2d->target->PopAxisAlignedClip();
		d2d->target->RestoreDrawingState(d2d->targetstate.get());
	}
	template<> void ComboBox<ListItem<newifstream>>::drawDropdown(std::shared_ptr<D2DHandle>& d2d){
		ID2D1SolidColorBrush* scb;
		d2d->target->CreateSolidColorBrush(ColorF(ColorF::White,opacity),&scb);
		d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
		d2d->target->FillRectangle(RectF(getBounds().left,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight()),d2d->solidbrush.get());
		d2d->target->PushAxisAlignedClip(RectF(getBounds().left,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight()),D2D1_ANTIALIAS_MODE_ALIASED);
		float topY=(getTotalHeight()/vScrollBar->portions)*vScrollBar->position;
		d2d->target->SaveDrawingState(d2d->targetstate.get());
		d2d->target->SetTransform(Matrix3x2F::Translation(0,-topY));
		for(int i=0;i<list.size();i++){
			if(list.at(i).isEnabled()==true){
				if(list.at(i).isSelected()==true){
					d2d->solidbrush->SetColor(ColorF(fRGBA_selected[0],fRGBA_selected[1],fRGBA_selected[2],fRGBA_selected[3]*opacity));
					d2d->target->FillRectangle(RectF(getBounds().left+list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,getBounds().left+list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.get());
				}
				else if(list.at(i).isPressed()==true){
					d2d->solidbrush->SetColor(ColorF(fRGBA_pressed[0],fRGBA_pressed[1],fRGBA_pressed[2],fRGBA_pressed[3]*opacity));
					d2d->target->FillRectangle(RectF(getBounds().left+list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,getBounds().left+list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.get());
				}
				else if(list.at(i).isHovered()==true){
					d2d->solidbrush->SetColor(ColorF(fRGBA_hovered[0],fRGBA_hovered[1],fRGBA_hovered[2],fRGBA_hovered[3]*opacity));
					d2d->target->FillRectangle(RectF(getBounds().left+list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,getBounds().left+list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.get());
				}
			}
			else{
				d2d->solidbrush->SetColor(ColorF(fRGBA_disabled[0],fRGBA_disabled[1],fRGBA_disabled[2],fRGBA_disabled[3]*opacity));
				d2d->target->FillRectangle(RectF(getBounds().left+list.at(i).getBounds().left,getBounds().top+list.at(i).getBounds().top,getBounds().left+list.at(i).getBounds().right,getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.get());
			}
			IDWriteTextFormat* dwtf;
			d2d->dwritefactory->CreateTextFormat(list.at(i).getFont(),NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,list.at(i).getTextSize()*(96.0f/72.0f),locale,&dwtf);
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
			IDWriteTextLayout* dwtl;
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.get(),list.at(i).getBounds().right-list.at(i).getBounds().left-getLeftPadding()-getRightPadding(),list.at(i).getBounds().bottom-list.at(i).getBounds().top-getBottomPadding()-getTopPadding(),&dwtl);
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+list.at(i).getBounds().top+getTopPadding()),d2d->textlayout.get(),d2d->solidbrush.get());
			d2d->textformat.reset();
			d2d->textlayout.reset();
		}
		d2d->solidbrush.reset();
		d2d->target->PopAxisAlignedClip();
		d2d->target->RestoreDrawingState(d2d->targetstate.get());
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setLocale(wchar_t* locale){
		this->locale=locale;
		tb->setLocale(locale);
		vScrollBar->setLocale(locale);
		hScrollBar->setLocale(locale);
		dropdown->setLocale(locale);
	}
	template<> void ComboBox<ListItem<newifstream>>::setLocale(wchar_t* locale){
		this->locale=locale;
		tb->setLocale(locale);
		vScrollBar->setLocale(locale);
		hScrollBar->setLocale(locale);
		dropdown->setLocale(locale);
	}
	template<> void ComboBox<ListItem<wchar_t*>>::setOpacity(float opacity){
		this->opacity=opacity;
		tb->setOpacity(opacity);
		vScrollBar->setOpacity(opacity);
		hScrollBar->setOpacity(opacity);
		dropdown->setOpacity(opacity);
	}
	template<> void ComboBox<ListItem<newifstream>>::setOpacity(float opacity){
		this->opacity=opacity;
		tb->setOpacity(opacity);
		vScrollBar->setOpacity(opacity);
		hScrollBar->setOpacity(opacity);
		dropdown->setOpacity(opacity);
	}
	template<> void ComboBox<ListItem<wchar_t*>>::draw(std::shared_ptr<D2DHandle>& d2d){
		tb->draw(d2d);
		dropdown->draw(d2d);
	}
	template<> void ComboBox<ListItem<newifstream>>::draw(std::shared_ptr<D2DHandle>& d2d){
		tb->draw(d2d);
		dropdown->draw(d2d);
	}
	template<> void ListBox<ListItem<wchar_t*>>::setSelectedItem(ListItem<wchar_t*>& t){
		selecteditem=t;
		auto it=std::find(list.begin(),list.end(),t);
		int c=std::distance(list.begin(),it);
		setSelectedIndex(c);
	}
	template<> void ListBox<ListItem<newifstream>>::setSelectedItem(ListItem<newifstream>& t){
		selecteditem=t;
		auto it=std::find(list.begin(),list.end(),t);
		int c=std::distance(list.begin(),it);
		setSelectedIndex(c);
	}
	template<> ListItem<wchar_t*>& ListBox<ListItem<wchar_t*>>::getSelectedItem(){
		return selecteditem;
	}
	template<> ListItem<newifstream>& ListBox<ListItem<newifstream>>::getSelectedItem(){
		return selecteditem;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setSelectedIndex(int index){
		ListBox::index=index;
		for(int i=0;i<list.size();i++){
			list.at(i).setSelected(false);
		}
		list.at(index).setSelected(true);
	}
	template<> void ListBox<ListItem<newifstream>>::setSelectedIndex(int index){
		ListBox::index=index;
		for(int i=0;i<list.size();i++){
			list.at(i).setSelected(false);
		}
		list.at(index).setSelected(true);
	}
	template<> int ListBox<ListItem<wchar_t*>>::getSelectedIndex(){
		return index;
	}
	template<> int ListBox<ListItem<newifstream>>::getSelectedIndex(){
		return index;
	}
	template<> void ListBox<ListItem<wchar_t*>>::remove(int index){
		list.erase(list.begin()+index);
	}
	template<> void ListBox<ListItem<newifstream>>::remove(int index){
		list.erase(list.begin()+index);
	}
	template<> void ListBox<ListItem<wchar_t*>>::setFont(wchar_t* font){
		ListBox::font=font;
	}
	template<> void ListBox<ListItem<newifstream>>::setFont(wchar_t* font){
		ListBox::font=font;
	}
	template<> wchar_t* ListBox<ListItem<wchar_t*>>::getFont(){
		return ListBox::font;
	}
	template<> wchar_t* ListBox<ListItem<newifstream>>::getFont(){
		return ListBox::font;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setTextSize(float px){
		ListBox::textsize=px;
	}
	template<> void ListBox<ListItem<newifstream>>::setTextSize(float px){
		ListBox::textsize=px;
	}
	template<> float ListBox<ListItem<wchar_t*>>::getTextSize(){
		return ListBox::textsize;
	}
	template<> float ListBox<ListItem<newifstream>>::getTextSize(){
		return ListBox::textsize;
	}
	template<> int ListBox<ListItem<wchar_t*>>::getLeftPadding(){
		return ListBox::leftPadding;
	}
	template<> int ListBox<ListItem<newifstream>>::getLeftPadding(){
		return ListBox::leftPadding;
	}
	template<> int ListBox<ListItem<wchar_t*>>::getTopPadding(){
		return ListBox::topPadding;
	}
	template<> int ListBox<ListItem<newifstream>>::getTopPadding(){
		return ListBox::topPadding;
	}
	template<> int ListBox<ListItem<wchar_t*>>::getRightPadding(){
		return ListBox::rightPadding;
	}
	template<> int ListBox<ListItem<newifstream>>::getRightPadding(){
		return ListBox::rightPadding;
	}
	template<> int ListBox<ListItem<wchar_t*>>::getBottomPadding(){
		return ListBox::bottomPadding;
	}
	template<> int ListBox<ListItem<newifstream>>::getBottomPadding(){
		return ListBox::bottomPadding;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setTotalHeight(int totalheight){
		ListBox::totalheight=totalheight;
		int height=getBounds().bottom-getBounds().top;
		int vpheight=getViewportBounds().bottom-getViewportBounds().top;
		if(vpheight<totalheight){
			setViewportBounds(viewportbounds.left,viewportbounds.top,viewportbounds.right,viewportbounds.top+totalheight);
		}
		if(height!=0){
			vScrollBar->portions=totalheight/height;
			if(vScrollBar->portions<1){
				vScrollBar->portions=1;
				vScrollBar->position=0;
			}
		}
		else{
			vScrollBar->portions=1;
			vScrollBar->position=0;
		}
	}
	template<> void ListBox<ListItem<newifstream>>::setTotalHeight(int totalheight){
		ListBox::totalheight=totalheight;
		int height=getBounds().bottom-getBounds().top;
		int vpheight=getViewportBounds().bottom-getViewportBounds().top;
		if(vpheight<totalheight){
			setViewportBounds(viewportbounds.left,viewportbounds.top,viewportbounds.right,viewportbounds.top+totalheight);
		}
		if(height!=0){
			vScrollBar->portions=totalheight/height;
			if(vScrollBar->portions<1){
				vScrollBar->portions=1;
				vScrollBar->position=0;
			}
		}
		else{
			vScrollBar->portions=1;
			vScrollBar->position=0;
		}
	}
	template<> int ListBox<ListItem<wchar_t*>>::getTotalHeight(){
		return ListBox::totalheight;
	}
	template<> int ListBox<ListItem<newifstream>>::getTotalHeight(){
		return ListBox::totalheight;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setViewportBounds(int left,int top,int right,int bottom){
		ListBox::viewportbounds.left=left;
		ListBox::viewportbounds.top=top;
		ListBox::viewportbounds.right=right;
		ListBox::viewportbounds.bottom=bottom;
		if(IsRectEmpty(&getBounds())==false){
			int vpwidth=getViewportBounds().right-getViewportBounds().left;
			int width=getBounds().right-getBounds().left;
			int vpheight=getViewportBounds().bottom-getViewportBounds().top;
			int height=getBounds().bottom-getBounds().top;
			if(vpwidth>width){
				hScrollBar->enableHorizontalScrolling();
				hScrollBar->portions=vpwidth/width;
			}
			else{
				hScrollBar->disableHorizontalScrolling();
				hScrollBar->portions=1;
				hScrollBar->position=0;
				if(viewportbounds.left<bounds.left){
					viewportbounds.left=bounds.left;
					viewportbounds.right=viewportbounds.left+vpwidth;
				}
			}
			if(vpheight>height){
				vScrollBar->enableVerticalScrolling();
				vScrollBar->portions=vpheight/height;
			}
			else{
				vScrollBar->disableVerticalScrolling();
				vScrollBar->portions=1;
				vScrollBar->position=0;
				if(viewportbounds.top<bounds.top){
					viewportbounds.top=bounds.top;
					viewportbounds.bottom=viewportbounds.top+vpheight;
				}
			}
		}
	}	
	template<> void ListBox<ListItem<newifstream>>::setViewportBounds(int left,int top,int right,int bottom){
		ListBox::viewportbounds.left=left;
		ListBox::viewportbounds.top=top;
		ListBox::viewportbounds.right=right;
		ListBox::viewportbounds.bottom=bottom;
		if(IsRectEmpty(&getBounds())==false){
			int vpwidth=getViewportBounds().right-getViewportBounds().left;
			int width=getBounds().right-getBounds().left;
			int vpheight=getViewportBounds().bottom-getViewportBounds().top;
			int height=getBounds().bottom-getBounds().top;
			if(vpwidth>width){
				hScrollBar->enableHorizontalScrolling();
				hScrollBar->portions=vpwidth/width;
			}
			else{
				hScrollBar->disableHorizontalScrolling();
				hScrollBar->portions=1;
				hScrollBar->position=0;
				if(viewportbounds.left<bounds.left){
					viewportbounds.left=bounds.left;
					viewportbounds.right=viewportbounds.left+vpwidth;
				}
			}
			if(vpheight>height){
				vScrollBar->enableVerticalScrolling();
				vScrollBar->portions=vpheight/height;
			}
			else{
				vScrollBar->disableVerticalScrolling();
				vScrollBar->portions=1;
				vScrollBar->position=0;
				if(viewportbounds.top<bounds.top){
					viewportbounds.top=bounds.top;
					viewportbounds.bottom=viewportbounds.top+vpheight;
				}
			}
		}
	}	
	template<> RECT ListBox<ListItem<wchar_t*>>::getViewportBounds(){
		return ListBox::viewportbounds;
	}
	template<> RECT ListBox<ListItem<newifstream>>::getViewportBounds(){
		return ListBox::viewportbounds;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(ListBox::states.size()!=0){
				for(int i=0;i<ListBox::states.size();i++){
					if(ListBox::states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
				if(foundinstates==false){
					ListBox::states.push_back(VISIBLE);
				}
			}
		}
		else{
			if(ListBox::states.size()!=0){
				for(int i=0;i<ListBox::states.size();i++){
					if(ListBox::states.at(i)==VISIBLE){
						ListBox::states.erase(ListBox::states.begin()+i);
						break;
					}
				}
			}
		}
	}
	template<> void ListBox<ListItem<newifstream>>::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(ListBox::states.size()!=0){
				for(int i=0;i<ListBox::states.size();i++){
					if(ListBox::states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
				if(foundinstates==false){
					ListBox::states.push_back(VISIBLE);
				}
			}
		}
		else{
			if(ListBox::states.size()!=0){
				for(int i=0;i<ListBox::states.size();i++){
					if(ListBox::states.at(i)==VISIBLE){
						ListBox::states.erase(ListBox::states.begin()+i);
						break;
					}
				}
			}
		}
	}
	template<> bool ListBox<ListItem<wchar_t*>>::isVisible(){
		bool visible=false;
		if(ListBox::states.size()!=0){
			for(int i=0;i<ListBox::states.size();i++){
				if(ListBox::states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	template<> bool ListBox<ListItem<newifstream>>::isVisible(){
		bool visible=false;
		if(ListBox::states.size()!=0){
			for(int i=0;i<ListBox::states.size();i++){
				if(ListBox::states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled==true){
			for(int i=0;i<ListBox::states.size();i++){
				if(ListBox::states.at(i)==ENABLED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ListBox::states.push_back(ENABLED);
			}
		}
		else{
			for(int i=0;i<ListBox::states.size();i++){
				if(ListBox::states.at(i)==ENABLED){
					ListBox::states.erase(ListBox::states.begin()+i);
					break;
				}
			}
		}
	}
	template<> void ListBox<ListItem<newifstream>>::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled==true){
			for(int i=0;i<ListBox::states.size();i++){
				if(ListBox::states.at(i)==ENABLED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ListBox::states.push_back(ENABLED);
			}
		}
		else{
			for(int i=0;i<ListBox::states.size();i++){
				if(ListBox::states.at(i)==ENABLED){
					ListBox::states.erase(ListBox::states.begin()+i);
					break;
				}
			}
		}
	}
	template<> bool ListBox<ListItem<wchar_t*>>::isEnabled(){
		bool enabled=false;
		for(int i=0;i<ListBox::states.size();i++){
			if(ListBox::states.at(i)==ENABLED){
				enabled=true;
				break;
			}
		}
		return enabled;
	}
	template<> bool ListBox<ListItem<newifstream>>::isEnabled(){
		bool enabled=false;
		for(int i=0;i<ListBox::states.size();i++){
			if(ListBox::states.at(i)==ENABLED){
				enabled=true;
				break;
			}
		}
		return enabled;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setHovered(bool hovered){
		bool foundinstates=false;
		if(hovered==true){
			for(int i=0;i<ListBox::states.size();i++){
				if(ListBox::states.at(i)==HOVERED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ListBox::states.push_back(HOVERED);
			}
		}
		else{
			for(int i=0;i<ListBox::states.size();i++){
				if(ListBox::states.at(i)==HOVERED){
					ListBox::states.erase(ListBox::states.begin()+i);
					break;
				}
			}
		}
	}
	template<> void ListBox<ListItem<newifstream>>::setHovered(bool hovered){
		bool foundinstates=false;
		if(hovered==true){
			for(int i=0;i<ListBox::states.size();i++){
				if(ListBox::states.at(i)==HOVERED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				ListBox::states.push_back(HOVERED);
			}
		}
		else{
			for(int i=0;i<ListBox::states.size();i++){
				if(ListBox::states.at(i)==HOVERED){
					ListBox::states.erase(ListBox::states.begin()+i);
					break;
				}
			}
		}
	}
	template<> bool ListBox<ListItem<wchar_t*>>::isHovered(){
		bool hovered=false;
		for(int i=0;i<ListBox::states.size();i++){
			if(ListBox::states.at(i)==HOVERED){
				hovered=true;
				break;
			}
		}	
		return hovered;
	}
	template<> bool ListBox<ListItem<newifstream>>::isHovered(){
		bool hovered=false;
		for(int i=0;i<ListBox::states.size();i++){
			if(ListBox::states.at(i)==HOVERED){
				hovered=true;
				break;
			}
		}	
		return hovered;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setBounds(int left,int top,int right,int bottom){
		ListBox::bounds.left=left;
		ListBox::bounds.top=top;
		ListBox::bounds.right=right;
		ListBox::bounds.bottom=bottom;
		vScrollBar->setBounds(getBounds().right-20,getBounds().top,getBounds().right,hScrollBar->isHorizontalScrollingEnabled()==true?getBounds().bottom-20:getBounds().bottom);
		hScrollBar->setBounds(getBounds().left,getBounds().bottom-20,vScrollBar->isVerticalScrollingEnabled()==true?getBounds().right-20:getBounds().right,getBounds().bottom);
	}
	template<> void ListBox<ListItem<newifstream>>::setBounds(int left,int top,int right,int bottom){
		ListBox::bounds.left=left;
		ListBox::bounds.top=top;
		ListBox::bounds.right=right;
		ListBox::bounds.bottom=bottom;
		vScrollBar->setBounds(getBounds().right-20,getBounds().top,getBounds().right,hScrollBar->isHorizontalScrollingEnabled()==true?getBounds().bottom-20:getBounds().bottom);
		hScrollBar->setBounds(getBounds().left,getBounds().bottom-20,vScrollBar->isVerticalScrollingEnabled()==true?getBounds().right-20:getBounds().right,getBounds().bottom);
	}
	template<> RECT ListBox<ListItem<wchar_t*>>::getBounds(){
		RECT r;
		r.left=ListBox::bounds.left;
		r.top=ListBox::bounds.top;
		r.right=ListBox::bounds.right;
		r.bottom=ListBox::bounds.bottom;
		return r;
	}
	template<> RECT ListBox<ListItem<newifstream>>::getBounds(){
		RECT r;
		r.left=ListBox::bounds.left;
		r.top=ListBox::bounds.top;
		r.right=ListBox::bounds.right;
		r.bottom=ListBox::bounds.bottom;
		return r;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setPressed(bool pressed){
		bool foundinstates=false;
		if(pressed==true){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==PRESSED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				states.push_back(PRESSED);
			}
		}
		else{
			for(int i=0;i<states.size();i++){
				if(states.at(i)==PRESSED){
					states.erase(states.begin()+i);
					break;
				}
			}
		}
	}
	template<> void ListBox<ListItem<newifstream>>::setPressed(bool pressed){
		bool foundinstates=false;
		if(pressed==true){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==PRESSED){
					foundinstates=true;
					break;
				}
			}
			if(foundinstates==false){
				states.push_back(PRESSED);
			}
		}
		else{
			for(int i=0;i<states.size();i++){
				if(states.at(i)==PRESSED){
					states.erase(states.begin()+i);
					break;
				}
			}
		}
	}
	template<> bool ListBox<ListItem<wchar_t*>>::isPressed(){
		bool pressed=false;
		for(int i=0;i<states.size();i++){
			if(states.at(i)==PRESSED){
				pressed=true;
				break;
			}		
		}
		return pressed;
	}
	template<> bool ListBox<ListItem<newifstream>>::isPressed(){
		bool pressed=false;
		for(int i=0;i<states.size();i++){
			if(states.at(i)==PRESSED){
				pressed=true;
				break;
			}		
		}
		return pressed;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setHorizontalTextAlignment(const int H){
		ListBox::hAlignment=const_cast<int&>(H);
	}
	template<> void ListBox<ListItem<newifstream>>::setHorizontalTextAlignment(const int H){
		ListBox::hAlignment=const_cast<int&>(H);
	}
	template<> int ListBox<ListItem<wchar_t*>>::getHorizontalTextAlignment(){
		return ListBox::hAlignment;
	}
	template<> int ListBox<ListItem<newifstream>>::getHorizontalTextAlignment(){
		return ListBox::hAlignment;
	}
	template<> int ListBox<ListItem<wchar_t*>>::getVerticalTextAlignment(){
		return ListBox::vAlignment;
	}
	template<> int ListBox<ListItem<newifstream>>::getVerticalTextAlignment(){
		return ListBox::vAlignment;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setVerticalTextAlignment(const int V){
		ListBox::vAlignment=const_cast<int&>(V);
	}
	template<> void ListBox<ListItem<newifstream>>::setVerticalTextAlignment(const int V){
		ListBox::vAlignment=const_cast<int&>(V);
	}
	template<> void ListBox<ListItem<wchar_t*>>::setPadding(int left,int top,int right,int bottom){
		ListBox::leftPadding=left;
		ListBox::topPadding=top;
		ListBox::rightPadding=right;
		ListBox::bottomPadding=bottom;
		if(ListBox::rightPadding==-1){
			ListBox::rightPadding=ListBox::leftPadding;
		}
		if(ListBox::bottomPadding==-1){
			ListBox::bottomPadding=ListBox::topPadding;
		}
	}
	template<> void ListBox<ListItem<newifstream>>::setPadding(int left,int top,int right,int bottom){
		ListBox::leftPadding=left;
		ListBox::topPadding=top;
		ListBox::rightPadding=right;
		ListBox::bottomPadding=bottom;
		if(ListBox::rightPadding==-1){
			ListBox::rightPadding=ListBox::leftPadding;
		}
		if(ListBox::bottomPadding==-1){
			ListBox::bottomPadding=ListBox::topPadding;
		}
	}
	template<> void ListBox<ListItem<wchar_t*>>::add(ListItem<wchar_t*> t){
		int itemheight=((int)t.getTextSize())+getTopPadding()+getBottomPadding();
		int top=0;
		if(list.size()!=0){
			top=list.at(list.size()-1).getBounds().bottom;
		}
		if(vScrollBar->isVerticalScrollingEnabled()==true){
			t.setBounds(0,top,getBounds().right,top+itemheight);
		}
		else{
			t.setBounds(0,top,getBounds().right,top+itemheight);
		}
		list.push_back(t);
		setTotalHeight(getTotalHeight()+itemheight);
	}
	template<> void ListBox<ListItem<newifstream>>::add(ListItem<newifstream> t){
		int itemheight=((int)t.getTextSize())+getTopPadding()+getBottomPadding();
		int top=0;
		if(list.size()!=0){
			top=list.at(list.size()-1).getBounds().bottom;
		}
		if(vScrollBar->isVerticalScrollingEnabled()==true){
			t.setBounds(0,top,getViewportBounds().right,top+itemheight);
		}
		else{
			t.setBounds(0,top,getViewportBounds().right,top+itemheight);
		}
		list.push_back(t);
		setTotalHeight(getTotalHeight()+itemheight);
	}
	template<> void ListBox<ListItem<wchar_t*>>::addAll(std::vector<ListItem<wchar_t*>> t){
		for(ListItem<wchar_t*> t1:t){
			list.push_back(t1);
		}
		int itemheight=((int)getTextSize())+getTopPadding()+getBottomPadding();
		setTotalHeight(getTotalHeight()+(itemheight*t.size()));
	}
	template<> void ListBox<ListItem<newifstream>>::addAll(std::vector<ListItem<newifstream>> t){
		for(ListItem<newifstream> t1:t){
			list.push_back(t1);
		}
		int itemheight=((int)getTextSize())+getTopPadding()+getBottomPadding();
		setTotalHeight(getTotalHeight()+(itemheight*t.size()));
	}
	template<> void ListBox<ListItem<wchar_t*>>::setForeground(int R,int G,int B,int A){
		ListBox::iRGBA[0]=R;
		ListBox::iRGBA[1]=G;
		ListBox::iRGBA[2]=B;
		ListBox::iRGBA[3]=A;
		ListBox::fRGBA[0]=(float)R/255.0f;
		ListBox::fRGBA[1]=(float)G/255.0f;
		ListBox::fRGBA[2]=(float)B/255.0f;
		ListBox::fRGBA[3]=(float)A/255.0f;
	}
	template<> void ListBox<ListItem<newifstream>>::setForeground(int R,int G,int B,int A){
		ListBox::iRGBA[0]=R;
		ListBox::iRGBA[1]=G;
		ListBox::iRGBA[2]=B;
		ListBox::iRGBA[3]=A;
		ListBox::fRGBA[0]=(float)R/255.0f;
		ListBox::fRGBA[1]=(float)G/255.0f;
		ListBox::fRGBA[2]=(float)B/255.0f;
		ListBox::fRGBA[3]=(float)A/255.0f;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setForeground(float R,float G,float B,float A){
		ListBox::fRGBA[0]=R;
		ListBox::fRGBA[1]=G;
		ListBox::fRGBA[2]=B;
		ListBox::fRGBA[3]=A;
		ListBox::iRGBA[0]=(int)(R*255.0f);
		ListBox::iRGBA[1]=(int)(G*255.0f);
		ListBox::iRGBA[2]=(int)(B*255.0f);
		ListBox::iRGBA[3]=(int)(A*255.0f);
	}
	template<> void ListBox<ListItem<newifstream>>::setForeground(float R,float G,float B,float A){
		ListBox::fRGBA[0]=R;
		ListBox::fRGBA[1]=G;
		ListBox::fRGBA[2]=B;
		ListBox::fRGBA[3]=A;
		ListBox::iRGBA[0]=(int)(R*255.0f);
		ListBox::iRGBA[1]=(int)(G*255.0f);
		ListBox::iRGBA[2]=(int)(B*255.0f);
		ListBox::iRGBA[3]=(int)(A*255.0f);
	}
	template<> float* ListBox<ListItem<wchar_t*>>::getForegroundFloat(){
		return ListBox::fRGBA;
	}
	template<> float* ListBox<ListItem<newifstream>>::getForegroundFloat(){
		return ListBox::fRGBA;
	}
	template<> int* ListBox<ListItem<wchar_t*>>::getForegroundInt(){
		return ListBox::iRGBA;
	}
	template<> int* ListBox<ListItem<newifstream>>::getForegroundInt(){
		return ListBox::iRGBA;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setHoveredItemColor(int R,int G,int B,int A){
		ListBox::iRGBA_hovered[0]=R;
		ListBox::iRGBA_hovered[1]=G;
		ListBox::iRGBA_hovered[2]=B;
		ListBox::iRGBA_hovered[3]=A;
		ListBox::fRGBA_hovered[0]=R/255.0f;
		ListBox::fRGBA_hovered[1]=G/255.0f;
		ListBox::fRGBA_hovered[2]=B/255.0f;
		ListBox::fRGBA_hovered[3]=A/255.0f;
	}
	template<> void ListBox<ListItem<newifstream>>::setHoveredItemColor(int R,int G,int B,int A){
		ListBox::iRGBA_hovered[0]=R;
		ListBox::iRGBA_hovered[1]=G;
		ListBox::iRGBA_hovered[2]=B;
		ListBox::iRGBA_hovered[3]=A;
		ListBox::fRGBA_hovered[0]=R/255.0f;
		ListBox::fRGBA_hovered[1]=G/255.0f;
		ListBox::fRGBA_hovered[2]=B/255.0f;
		ListBox::fRGBA_hovered[3]=A/255.0f;
	}
	template<> int* ListBox<ListItem<wchar_t*>>::getHoveredItemColorInt(){
		return ListBox::iRGBA_hovered;
	}
	template<> int* ListBox<ListItem<newifstream>>::getHoveredItemColorInt(){
		return ListBox::iRGBA_hovered;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setHoveredItemColor(float R,float G,float B,float A){
		ListBox::fRGBA_hovered[0]=R;
		ListBox::fRGBA_hovered[1]=G;
		ListBox::fRGBA_hovered[2]=B;
		ListBox::fRGBA_hovered[3]=A;
		ListBox::iRGBA_hovered[0]=(int)(R*255.0f);
		ListBox::iRGBA_hovered[1]=(int)(G*255.0f);
		ListBox::iRGBA_hovered[2]=(int)(B*255.0f);
		ListBox::iRGBA_hovered[3]=(int)(A*255.0f);
	}
	template<> void ListBox<ListItem<newifstream>>::setHoveredItemColor(float R,float G,float B,float A){
		ListBox::fRGBA_hovered[0]=R;
		ListBox::fRGBA_hovered[1]=G;
		ListBox::fRGBA_hovered[2]=B;
		ListBox::fRGBA_hovered[3]=A;
		ListBox::iRGBA_hovered[0]=(int)(R*255.0f);
		ListBox::iRGBA_hovered[1]=(int)(G*255.0f);
		ListBox::iRGBA_hovered[2]=(int)(B*255.0f);
		ListBox::iRGBA_hovered[3]=(int)(A*255.0f);
	}
	template<> float* ListBox<ListItem<wchar_t*>>::getHoveredItemColorFloat(){
		return ListBox::fRGBA_hovered;
	}
	template<> float* ListBox<ListItem<newifstream>>::getHoveredItemColorFloat(){
		return ListBox::fRGBA_hovered;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setPressedItemColor(int R,int G,int B,int A){
		ListBox::iRGBA_pressed[0]=R;
		ListBox::iRGBA_pressed[1]=G;
		ListBox::iRGBA_pressed[2]=B;
		ListBox::iRGBA_pressed[3]=A;
		ListBox::fRGBA_pressed[0]=R/255.0f;
		ListBox::fRGBA_pressed[1]=G/255.0f;
		ListBox::fRGBA_pressed[2]=B/255.0f;
		ListBox::fRGBA_pressed[3]=A/255.0f;
	}
	template<> void ListBox<ListItem<newifstream>>::setPressedItemColor(int R,int G,int B,int A){
		ListBox::iRGBA_pressed[0]=R;
		ListBox::iRGBA_pressed[1]=G;
		ListBox::iRGBA_pressed[2]=B;
		ListBox::iRGBA_pressed[3]=A;
		ListBox::fRGBA_pressed[0]=R/255.0f;
		ListBox::fRGBA_pressed[1]=G/255.0f;
		ListBox::fRGBA_pressed[2]=B/255.0f;
		ListBox::fRGBA_pressed[3]=A/255.0f;
	}
	template<> int* ListBox<ListItem<wchar_t*>>::getPressedItemColorInt(){
		return ListBox::iRGBA_pressed;
	}
	template<> int* ListBox<ListItem<newifstream>>::getPressedItemColorInt(){
		return ListBox::iRGBA_pressed;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setPressedItemColor(float R,float G,float B,float A){
		ListBox::fRGBA_pressed[0]=R;
		ListBox::fRGBA_pressed[1]=G;
		ListBox::fRGBA_pressed[2]=B;
		ListBox::fRGBA_pressed[3]=A;
		ListBox::iRGBA_pressed[0]=(int)(R*255.0f);
		ListBox::iRGBA_pressed[1]=(int)(G*255.0f);
		ListBox::iRGBA_pressed[2]=(int)(B*255.0f);
		ListBox::iRGBA_pressed[3]=(int)(A*255.0f);
	}
	template<> void ListBox<ListItem<newifstream>>::setPressedItemColor(float R,float G,float B,float A){
		ListBox::fRGBA_pressed[0]=R;
		ListBox::fRGBA_pressed[1]=G;
		ListBox::fRGBA_pressed[2]=B;
		ListBox::fRGBA_pressed[3]=A;
		ListBox::iRGBA_pressed[0]=(int)(R*255.0f);
		ListBox::iRGBA_pressed[1]=(int)(G*255.0f);
		ListBox::iRGBA_pressed[2]=(int)(B*255.0f);
		ListBox::iRGBA_pressed[3]=(int)(A*255.0f);
	}
	template<> float* ListBox<ListItem<wchar_t*>>::getPressedItemColorFloat(){
		return ListBox::fRGBA_pressed;
	}
	template<> float* ListBox<ListItem<newifstream>>::getPressedItemColorFloat(){
		return ListBox::fRGBA_pressed;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setSelectedItemColor(int R,int G,int B,int A){
		ListBox::iRGBA_selected[0]=R;
		ListBox::iRGBA_selected[1]=G;
		ListBox::iRGBA_selected[2]=B;
		ListBox::iRGBA_selected[3]=A;
		ListBox::fRGBA_selected[0]=R/255.0f;
		ListBox::fRGBA_selected[1]=G/255.0f;
		ListBox::fRGBA_selected[2]=B/255.0f;
		ListBox::fRGBA_selected[3]=A/255.0f;
	}
	template<> void ListBox<ListItem<newifstream>>::setSelectedItemColor(int R,int G,int B,int A){
		ListBox::iRGBA_selected[0]=R;
		ListBox::iRGBA_selected[1]=G;
		ListBox::iRGBA_selected[2]=B;
		ListBox::iRGBA_selected[3]=A;
		ListBox::fRGBA_selected[0]=R/255.0f;
		ListBox::fRGBA_selected[1]=G/255.0f;
		ListBox::fRGBA_selected[2]=B/255.0f;
		ListBox::fRGBA_selected[3]=A/255.0f;
	}
	template<> int* ListBox<ListItem<wchar_t*>>::getSelectedItemColorInt(){
		return iRGBA_selected;
	}
	template<> int* ListBox<ListItem<newifstream>>::getSelectedItemColorInt(){
		return iRGBA_selected;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setSelectedItemColor(float R,float G,float B,float A){
		ListBox::fRGBA_selected[0]=R;
		ListBox::fRGBA_selected[1]=G;
		ListBox::fRGBA_selected[2]=B;
		ListBox::fRGBA_selected[3]=A;
		ListBox::iRGBA_selected[0]=(int)(R*255.0f);
		ListBox::iRGBA_selected[1]=(int)(G*255.0f);
		ListBox::iRGBA_selected[2]=(int)(B*255.0f);
		ListBox::iRGBA_selected[3]=(int)(A*255.0f);
	}
	template<> void ListBox<ListItem<newifstream>>::setSelectedItemColor(float R,float G,float B,float A){
		ListBox::fRGBA_selected[0]=R;
		ListBox::fRGBA_selected[1]=G;
		ListBox::fRGBA_selected[2]=B;
		ListBox::fRGBA_selected[3]=A;
		ListBox::iRGBA_selected[0]=(int)(R*255.0f);
		ListBox::iRGBA_selected[1]=(int)(G*255.0f);
		ListBox::iRGBA_selected[2]=(int)(B*255.0f);
		ListBox::iRGBA_selected[3]=(int)(A*255.0f);
	}
	template<> float* ListBox<ListItem<wchar_t*>>::getSelectedItemColorFloat(){
		return fRGBA_selected;
	}
	template<> float* ListBox<ListItem<newifstream>>::getSelectedItemColorFloat(){
		return fRGBA_selected;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setDisabledItemColor(int R,int G,int B,int A){
		ListBox::iRGBA_disabled[0]=R;
		ListBox::iRGBA_disabled[1]=G;
		ListBox::iRGBA_disabled[2]=B;
		ListBox::iRGBA_disabled[3]=A;
		ListBox::fRGBA_disabled[0]=R/255.0f;
		ListBox::fRGBA_disabled[1]=G/255.0f;
		ListBox::fRGBA_disabled[2]=B/255.0f;
		ListBox::fRGBA_disabled[3]=A/255.0f;
	}
	template<> void ListBox<ListItem<newifstream>>::setDisabledItemColor(int R,int G,int B,int A){
		ListBox::iRGBA_disabled[0]=R;
		ListBox::iRGBA_disabled[1]=G;
		ListBox::iRGBA_disabled[2]=B;
		ListBox::iRGBA_disabled[3]=A;
		ListBox::fRGBA_disabled[0]=R/255.0f;
		ListBox::fRGBA_disabled[1]=G/255.0f;
		ListBox::fRGBA_disabled[2]=B/255.0f;
		ListBox::fRGBA_disabled[3]=A/255.0f;
	}
	template<> int* ListBox<ListItem<wchar_t*>>::getDisabledItemColorInt(){
		return ListBox::iRGBA_disabled;
	}
	template<> int* ListBox<ListItem<newifstream>>::getDisabledItemColorInt(){
		return ListBox::iRGBA_disabled;
	}
	template<> void ListBox<ListItem<wchar_t*>>::setDisabledItemColor(float R,float G,float B,float A){
		ListBox::fRGBA_disabled[0]=R;
		ListBox::fRGBA_disabled[1]=G;
		ListBox::fRGBA_disabled[2]=B;
		ListBox::fRGBA_disabled[3]=A;
		ListBox::iRGBA_disabled[0]=(int)(R*255.0f);
		ListBox::iRGBA_disabled[1]=(int)(G*255.0f);
		ListBox::iRGBA_disabled[2]=(int)(B*255.0f);
		ListBox::iRGBA_disabled[3]=(int)(A*255.0f);
	}
	template<> void ListBox<ListItem<newifstream>>::setDisabledItemColor(float R,float G,float B,float A){
		ListBox::fRGBA_disabled[0]=R;
		ListBox::fRGBA_disabled[1]=G;
		ListBox::fRGBA_disabled[2]=B;
		ListBox::fRGBA_disabled[3]=A;
		ListBox::iRGBA_disabled[0]=(int)(R*255.0f);
		ListBox::iRGBA_disabled[1]=(int)(G*255.0f);
		ListBox::iRGBA_disabled[2]=(int)(B*255.0f);
		ListBox::iRGBA_disabled[3]=(int)(A*255.0f);
	}
	template<> float* ListBox<ListItem<wchar_t*>>::getDisabledItemColorFloat(){
		return ListBox::fRGBA_disabled;
	}
	template<> float* ListBox<ListItem<newifstream>>::getDisabledItemColorFloat(){
		return ListBox::fRGBA_disabled;
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
		ID2D1SolidColorBrush* scb;
		d2d->target->CreateSolidColorBrush(ColorF(ColorF::White,opacity),&scb);
		d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),d2d->solidbrush.get());
		d2d->target->PushAxisAlignedClip(RectF(getViewportBounds().left,getViewportBounds().top,getBounds().right,getBounds().bottom),D2D1_ANTIALIAS_MODE_ALIASED);
		float topY=((float)(getBounds().bottom-getBounds().top)/vScrollBar->portions)*vScrollBar->position;
		float leftY=((float)(getBounds().right-getBounds().left)/hScrollBar->portions)*hScrollBar->position;
		d2d->target->SaveDrawingState(d2d->targetstate.get());
		d2d->target->SetTransform(Matrix3x2F::Translation(-leftY,-topY));
		for(int i=0;i<list.size();i++){
			if(list.at(i).isEnabled()==true){
				if(list.at(i).isSelected()==true){
					d2d->solidbrush->SetColor(ColorF(fRGBA_selected[0],fRGBA_selected[1],fRGBA_selected[2],fRGBA_selected[3]*opacity));
				}//Selected enabled ListItem
				else if(list.at(i).isPressed()==true){
					d2d->solidbrush->SetColor(ColorF(fRGBA_pressed[0],fRGBA_pressed[1],fRGBA_pressed[2],fRGBA_pressed[3]*opacity));
				}//Pressed enabled ListItem
				else if(list.at(i).isHovered()==true){
					d2d->solidbrush->SetColor(ColorF(fRGBA_hovered[0],fRGBA_hovered[1],fRGBA_hovered[2],fRGBA_hovered[3]*opacity));
				}//Hovered enabled ListItem
			}//Enabled ListItem
			else{
				d2d->solidbrush->SetColor(ColorF(fRGBA_disabled[0],fRGBA_disabled[1],fRGBA_disabled[2],fRGBA_disabled[3]*opacity));
			}//Disabled ListItem
			d2d->target->FillRectangle(RectF((float)getBounds().left+list.at(i).getBounds().left,(float)getBounds().top+list.at(i).getBounds().top,(float)getBounds().left+list.at(i).getBounds().right,(float)getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.get());
			d2d->solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity));
			IDWriteTextFormat* dwtf;
			d2d->dwritefactory->CreateTextFormat(list.at(i).getFont(),NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
			d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
			IDWriteTextLayout* dwtl;
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.get(),(float)(list.at(i).getBounds().right-list.at(i).getBounds().left),(float)(list.at(i).getBounds().bottom-list.at(i).getBounds().top),&dwtl);
			d2d->textlayout=std::shared_ptr<IDWriteTextLayout>(dwtl,[](IDWriteTextLayout* p){p->Release();});
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+list.at(i).getBounds().top+getTopPadding()),d2d->textlayout.get(),d2d->solidbrush.get());
			d2d->textlayout.reset();
			d2d->textformat.reset();
		}
		d2d->solidbrush.reset();
		d2d->target->RestoreDrawingState(d2d->targetstate.get());
		d2d->target->PopAxisAlignedClip();
		if(hScrollBar->isHorizontalScrollingEnabled()==true){
			hScrollBar->draw(d2d);
		}
		if(vScrollBar->isVerticalScrollingEnabled()==true){
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
		ID2D1SolidColorBrush* scb;
		d2d->target->CreateSolidColorBrush(ColorF(ColorF::White,opacity),&scb);
		d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),d2d->solidbrush.get());
		d2d->target->PushAxisAlignedClip(RectF(getViewportBounds().left,getViewportBounds().top,getBounds().right,getBounds().bottom),D2D1_ANTIALIAS_MODE_ALIASED);
		float topY=((float)(getBounds().bottom-getBounds().top)/vScrollBar->portions)*vScrollBar->position;
		float leftY=((float)(getBounds().right-getBounds().left)/hScrollBar->portions)*hScrollBar->position;
		d2d->target->SaveDrawingState(d2d->targetstate.get());
		d2d->target->SetTransform(Matrix3x2F::Translation(-leftY,-topY));
		for(int i=0;i<list.size();i++){
			if(list.at(i).isEnabled()==true){
				if(list.at(i).isSelected()==true){
					d2d->solidbrush->SetColor(ColorF(fRGBA_selected[0],fRGBA_selected[1],fRGBA_selected[2],fRGBA_selected[3]*opacity));
				}//Selected enabled ListItem
				else if(list.at(i).isPressed()==true){
					d2d->solidbrush->SetColor(ColorF(fRGBA_pressed[0],fRGBA_pressed[1],fRGBA_pressed[2],fRGBA_pressed[3]*opacity));
				}//Pressed enabled ListItem
				else if(list.at(i).isHovered()==true){
					d2d->solidbrush->SetColor(ColorF(fRGBA_hovered[0],fRGBA_hovered[1],fRGBA_hovered[2],fRGBA_hovered[3]*opacity));
				}//Hovered enabled ListItem
			}//Enabled ListItem
			else{
				d2d->solidbrush->SetColor(ColorF(fRGBA_disabled[0],fRGBA_disabled[1],fRGBA_disabled[2],fRGBA_disabled[3]*opacity));
			}//Disabled ListItem
			d2d->target->FillRectangle(RectF((float)getBounds().left+list.at(i).getBounds().left,(float)getBounds().top+list.at(i).getBounds().top,(float)getBounds().left+list.at(i).getBounds().right,(float)getBounds().top+list.at(i).getBounds().bottom),d2d->solidbrush.get());
			d2d->solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity));
			IDWriteTextFormat* dwtf;
			d2d->dwritefactory->CreateTextFormat(list.at(i).getFont(),NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,getTextSize()*(96.0f/72.0f),locale,&dwtf);
			d2d->textformat=std::shared_ptr<IDWriteTextFormat>(dwtf,[](IDWriteTextFormat* p){p->Release();});
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
			IDWriteTextLayout* dwtl;
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.get(),(float)(list.at(i).getBounds().right-list.at(i).getBounds().left),(float)(list.at(i).getBounds().bottom-list.at(i).getBounds().top),&dwtl);
			d2d->textlayout=std::shared_ptr<IDWriteTextLayout>(dwtl,[](IDWriteTextLayout* p){p->Release();});
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+list.at(i).getBounds().top+getTopPadding()),d2d->textlayout.get(),d2d->solidbrush.get());
			d2d->textlayout.reset();
			d2d->textformat.reset();
		}
		d2d->solidbrush.reset();
		d2d->target->RestoreDrawingState(d2d->targetstate.get());
		d2d->target->PopAxisAlignedClip();
		if(hScrollBar->isHorizontalScrollingEnabled()==true){
			hScrollBar->draw(d2d);
		}
		if(vScrollBar->isVerticalScrollingEnabled()==true){
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
	void Slider::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
	}
	RECT Slider::getBounds(){
		return bounds;
	}
	void Slider::setEnabled(bool enabled){
		bool foundinstates=false;
		if(enabled==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==ENABLED){
						foundinstates=true;
						break;
					}
				}
			}	
			if(foundinstates==false){
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
	bool Slider::isEnabled(){
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
	void Slider::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
				states.push_back(VISIBLE);
			}
		}
		else{
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool Slider::isVisible(){
		bool visible=false;
		if(states.size()!=0){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	void Slider::setPressed(bool pressed){
		bool foundinstates=false;
		if(pressed==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==PRESSED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
	bool Slider::isPressed(){
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
	void Slider::setHovered(bool hovered){
		bool foundinstates=false;
		if(hovered==true){
			if(states.size()!=0){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==HOVERED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
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
	bool Slider::isHovered(){
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
		ID2D1SolidColorBrush* scb;
		d2d->target->CreateSolidColorBrush(ColorF(ColorF::LightGray,opacity),&scb);
		d2d->solidbrush=std::shared_ptr<ID2D1SolidColorBrush>(scb,[](ID2D1SolidColorBrush* p){p->Release();});
		int top=getBounds().top+((size/2)-(trackheight/2));
		float thumbleft=(float)(getBounds().left)+(((float)(getBounds().right-getBounds().left))/((float)(maxValue/step))*(float)value);
		d2d->target->FillRectangle(RectF((float)getBounds().left+pad,top,(float)getBounds().right-pad,(float)(top+trackheight)),d2d->solidbrush.get());
		d2d->solidbrush.reset();
		if(isEnabled()==true){
			if(isPressed()==true){
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\slide_thumb.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),size,size,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)thumbleft,(float)getBounds().top,(float)(thumbleft+size),(float)getBounds().bottom),opacity);
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->bmpscaler.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
			}//Enabled pressed Slider
			else if(isHovered()==true){
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\slide_thumb.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),size,size,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)thumbleft,(float)getBounds().top,(float)(thumbleft+size),(float)getBounds().bottom),opacity);
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->bmpscaler.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
			}//Normal enabled Slider
		}//Enabled Slider
		else{
			IWICBitmapDecoder* wicbd;
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\slide_thumb.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
			d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
			IWICBitmapFrameDecode* wicbfd;
			d2d->bmpdecoder->GetFrame(0,&wicbfd);
			d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
			IWICBitmapScaler* wicbs;
			d2d->imgfactory->CreateBitmapScaler(&wicbs);
			d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),size,size,WICBitmapInterpolationModeFant);
			IWICFormatConverter* wicfc;
			d2d->imgfactory->CreateFormatConverter(&wicfc);
			d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
			d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			ID2D1Bitmap* wicb;
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
			d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
			d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)thumbleft,(float)getBounds().top,(float)(thumbleft+size),(float)getBounds().bottom),opacity);
			d2d->bmpdecoder.reset();
			d2d->bmpframedecoder.reset();
			d2d->bmpscaler.reset();
			d2d->formatconverter.reset();
			d2d->bmp.reset();
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
	void ScrollBar::setPressed(bool pressed){
		bool foundinstates=false;
		if(pressed==true){
			if(ScrollBar::states.size()!=0){
				for(int i=0;i<ScrollBar::states.size();i++){
					if(ScrollBar::states.at(i)==PRESSED){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
				ScrollBar::states.push_back(PRESSED);
			}
		}
		else{
			if(ScrollBar::states.size()!=0){
				for(int i=0;i<ScrollBar::states.size();i++){
					if(ScrollBar::states.at(i)==PRESSED){
						ScrollBar::states.erase(ScrollBar::states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool ScrollBar::isPressed(){
		bool pressed=false;
		if(ScrollBar::states.size()!=0){
			for(int i=0;i<ScrollBar::states.size();i++){
				if(ScrollBar::states.at(i)==PRESSED){
					pressed=true;
					break;
				}
			}
		}
		return pressed;
	}
	void ScrollBar::setVisible(bool visible){
		bool foundinstates=false;
		if(visible==true){
			if(ScrollBar::states.size()!=0){
				for(int i=0;i<ScrollBar::states.size();i++){
					if(ScrollBar::states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
			}
			if(foundinstates==false){
				ScrollBar::states.push_back(VISIBLE);
			}
		}
		else{
			if(ScrollBar::states.size()!=0){
				for(int i=0;i<ScrollBar::states.size();i++){
					if(ScrollBar::states.at(i)==VISIBLE){
						ScrollBar::states.erase(ScrollBar::states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool ScrollBar::isVisible(){
		bool visible=false;
		if(ScrollBar::states.size()!=0){
			for(int i=0;i<ScrollBar::states.size();i++){
				if(ScrollBar::states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
		}
		return visible;
	}
	void ScrollBar::setHovered(bool hovered){
		bool foundinstates=false;
		if(hovered==true){
			if(ScrollBar::states.size()!=0){
				for(int i=0;i<ScrollBar::states.size();i++){
					if(ScrollBar::states.at(i)==HOVERED){
						foundinstates=true;
						break;
					}
				}
				if(foundinstates==false){
					ScrollBar::states.push_back(HOVERED);
				}
			}
		}
		else{
			if(ScrollBar::states.size()!=0){
				for(int i=0;i<ScrollBar::states.size();i++){
					if(ScrollBar::states.at(i)==HOVERED){
						ScrollBar::states.erase(ScrollBar::states.begin()+i);
						break;
					}
				}
			}
		}
	}
	bool ScrollBar::isHovered(){
		bool hovered=false;
		if(ScrollBar::states.size()!=0){
			for(int i=0;i<ScrollBar::states.size();i++){
				if(ScrollBar::states.at(i)==HOVERED){
					hovered=true;
					break;
				}
			}
		}
		return hovered;
	}
	void ScrollBar::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
	}
	RECT ScrollBar::getBounds(){
		return bounds;
	}
	void ScrollBar::scrollTo(float position){
		ScrollBar::position=position;
	}
	void ScrollBar::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isVerticalScrollingEnabled()==true){
			if(isPressed()==true){
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_track_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);	
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->bmpscaler.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
			}
			else{
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_track.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);	
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->bmpscaler.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
			}
			IWICBitmapDecoder* wicbd;
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_thumb.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
			d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
			IWICBitmapFrameDecode* wicbfd;
			d2d->bmpdecoder->GetFrame(0,&wicbfd);
			d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
			IWICBitmapScaler* wicbs;
			d2d->imgfactory->CreateBitmapScaler(&wicbs);
			d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
			float topY=(float)(getBounds().top)+((((float)(getBounds().bottom-getBounds().top))/portions)*position);
			float height=(float)(getBounds().bottom-getBounds().top)/portions;
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,(int)height,WICBitmapInterpolationModeFant);
			IWICFormatConverter* wicfc;
			d2d->imgfactory->CreateFormatConverter(&wicfc);
			d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
			d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			ID2D1Bitmap* wicb;
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
			d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
			d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,topY,(float)getBounds().right,topY+height),opacity);	
			d2d->bmpdecoder.reset();
			d2d->bmpframedecoder.reset();
			d2d->bmpscaler.reset();
			d2d->formatconverter.reset();
			d2d->bmp.reset();
		}
		else if(isHorizontalScrollingEnabled()==true){
			if(isPressed()==true){
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_track_pressed_horizontal.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);	
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->bmpscaler.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
			}
			else{
				IWICBitmapDecoder* wicbd;
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_track_horizontal.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
				d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
				IWICBitmapFrameDecode* wicbfd;
				d2d->bmpdecoder->GetFrame(0,&wicbfd);
				d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
				IWICBitmapScaler* wicbs;
				d2d->imgfactory->CreateBitmapScaler(&wicbs);
				d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				IWICFormatConverter* wicfc;
				d2d->imgfactory->CreateFormatConverter(&wicfc);
				d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
				d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				ID2D1Bitmap* wicb;
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
				d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
				d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);	
				d2d->bmpdecoder.reset();
				d2d->bmpframedecoder.reset();
				d2d->bmpscaler.reset();
				d2d->formatconverter.reset();
				d2d->bmp.reset();
			}
			IWICBitmapDecoder* wicbd;
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_thumb_horizontal.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&wicbd);
			d2d->bmpdecoder=std::shared_ptr<IWICBitmapDecoder>(wicbd,[](IWICBitmapDecoder* p){p->Release();});
			IWICBitmapFrameDecode* wicbfd;
			d2d->bmpdecoder->GetFrame(0,&wicbfd);
			d2d->bmpframedecoder=std::shared_ptr<IWICBitmapFrameDecode>(wicbfd,[](IWICBitmapFrameDecode* p){p->Release();});
			IWICBitmapScaler* wicbs;
			d2d->imgfactory->CreateBitmapScaler(&wicbs);
			d2d->bmpscaler=std::shared_ptr<IWICBitmapScaler>(wicbs,[](IWICBitmapScaler* p){p->Release();});
			float topY=(float)(getBounds().top)+((((float)(getBounds().bottom-getBounds().top))/portions)*position);
			float height=(float)(getBounds().bottom-getBounds().top)/portions;
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.get(),getBounds().right-getBounds().left,(int)height,WICBitmapInterpolationModeFant);
			IWICFormatConverter* wicfc;
			d2d->imgfactory->CreateFormatConverter(&wicfc);
			d2d->formatconverter=std::shared_ptr<IWICFormatConverter>(wicfc,[](IWICFormatConverter* p){p->Release();});
			d2d->formatconverter->Initialize(d2d->bmpscaler.get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			ID2D1Bitmap* wicb;
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.get(),NULL,&wicb);
			d2d->bmp=std::shared_ptr<ID2D1Bitmap>(wicb,[](ID2D1Bitmap* p){p->Release();});
			d2d->target->DrawBitmap(d2d->bmp.get(),RectF((float)getBounds().left,topY,(float)getBounds().right,topY+height),opacity);	
			d2d->bmpdecoder.reset();
			d2d->bmpframedecoder.reset();
			d2d->bmpscaler.reset();
			d2d->formatconverter.reset();
			d2d->bmp.reset();
		}
	}
}