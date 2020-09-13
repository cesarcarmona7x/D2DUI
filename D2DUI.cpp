#include "stdafx.h"
using namespace D2DUI;
namespace D2DUI{
	D2DUISystem& D2DUISystem::getInstance(){
		static D2DUISystem d2dui;
		return d2dui;
	}
	void D2DUISystem::addDrawToQueue(int layer,D2DUIDrawableItem& draw){
		drawOrder[layer].push_back(draw);
	}
	void D2DUISystem::draw(std::shared_ptr<D2DHandle>& d2d){
		for(auto& map:drawOrder){
			for(auto& drawing:map.second){
				if(drawing.get().isVisible()){
					if(map.first%2==0){
						if(drawing.get().drawWindow.size()!=0){
							if(strcmp(typeid(drawing.get().drawWindow.at(0).get()).name(),"class D2DUI::ComboBox")==0){
								ComboBox& cb=(ComboBox&)drawing.get().drawWindow.at(0).get();
								if(cb.usesCustomDrawMode()){
									cb.customDraw(d2d);
									cb.customDrawDropdown(d2d);
								}
								else{
									cb.draw(d2d);
									cb.drawDropdown(d2d);
								}
							}
						}
					}//Check even layers for ComboBox drawing
					else{
						if(drawing.get().drawWindow.size()!=0){
							if(strcmp(typeid(drawing.get().drawWindow.at(0).get()).name(),"class D2DUI::ListBox")==0){
								ListBox& lb=(ListBox&)drawing.get().drawWindow.at(0).get();
								if(lb.usesCustomDrawMode()){lb.customDraw(d2d);}
								else{lb.draw(d2d);}
							}
							else{
								drawing.get().drawWindow.at(0).get().draw(d2d);
							}
						}
						if(drawing.get().drawLayout.size()!=0)drawing.get().drawLayout.at(0).get().draw(d2d);
					}//Check odd layers for any other drawing
				}
			}
		}
	}
	MsgBox::MsgBox(HWND parent,bool modal,std::wstring text,std::wstring title,MSGBoxButtons buttons,MSGBoxIcon icon){
		hwnd=parent;
		this->modal=modal;
		showing=false;
		textContent=std::shared_ptr<TextLabel>(new TextLabel(text));
		textContent->setVisible(true);
		textContent->setPadding(0,0);
		textContent->setHorizontalTextAlignment(HorizontalConstants::LEFT);
		textContent->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		textTitle=std::shared_ptr<TextLabel>(new TextLabel(title));
		textTitle->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
		textTitle->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		this->buttons=buttons;
		this->msgicon=icon;
		contentRow=std::shared_ptr<TableRow>(new TableRow(2));
		contentRow->setVisible(true);
		contentRow->setBackground(0.f,0.f,0.f);
		textTitle->setPadding(0,0);
		contentRow->setPadding(0,0);
		contentRow->setSpacing(10);
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
			buttonsRow->setVisible(true);
			buttonsRow->setBackground(0.f,0.f,0.f);
			buttonsRow->setGravity(LayoutBase::HGravity::CENTERH,LayoutBase::VGravity::CENTERV);
			buttonsRow->setPadding(0,0);
			buttonsRow->setSpacing(10);
			btnOk=std::shared_ptr<Button>(new Button(L"OK",L""));
			btnOk->setVisible(true);
			btnOk->setEnabled(true);
			btnOk->setSize(100,30);
			btnOk->setPadding(0,0);
			btnOk->setLocale(L"en-us");
			btnOk->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnOk->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnOk,1,1);
			break;
		case MSGBOX_OKCANCEL:
			buttonsRow=std::shared_ptr<GridLayout>(new GridLayout(2,1));
			buttonsRow->setVisible(true);
			buttonsRow->setBackground(0.f,0.f,0.f);
			buttonsRow->setGravity(LayoutBase::HGravity::CENTERH,LayoutBase::VGravity::CENTERV);
			buttonsRow->setPadding(0,0);
			buttonsRow->setSpacing(10);
			btnOk=std::shared_ptr<Button>(new Button(L"OK",L""));
			btnOk->setVisible(true);
			btnOk->setLocale(L"en-us");
			btnOk->setEnabled(true);
			btnOk->setSize(100,30);
			btnOk->setPadding(0,0);
			btnOk->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnOk->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnOk,1,1);
			btnCancel=std::shared_ptr<Button>(new Button(L"Cancel",L""));
			btnCancel->setVisible(true);
			btnCancel->setLocale(L"en-us");
			btnCancel->setEnabled(true);
			btnCancel->setSize(100,30);
			btnCancel->setPadding(0,0);
			btnCancel->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnCancel->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnCancel,2,1);
			break;
		case MSGBOX_YESNO:
			buttonsRow=std::shared_ptr<GridLayout>(new GridLayout(2,1));
			buttonsRow->setVisible(true);
			buttonsRow->setBackground(0.f,0.f,0.f);
			buttonsRow->setGravity(LayoutBase::HGravity::CENTERH,LayoutBase::VGravity::CENTERV);
			buttonsRow->setPadding(0,0);
			buttonsRow->setSpacing(10);
			btnYes=std::shared_ptr<Button>(new Button(L"Yes",L""));
			btnYes->setVisible(true);
			btnYes->setEnabled(true);
			btnYes->setSize(100,30);
			btnYes->setPadding(0,0);
			btnYes->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnYes->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnYes,1,1);
			btnNo=std::shared_ptr<Button>(new Button(L"No",L""));
			btnNo->setVisible(true);
			btnNo->setEnabled(true);
			btnNo->setSize(100,30);
			btnNo->setPadding(0,0);
			btnNo->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnNo->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnNo,2,1);
			break;
		case MSGBOX_YESNOCANCEL:
			buttonsRow=std::shared_ptr<GridLayout>(new GridLayout(3,1));
			buttonsRow->setVisible(true);
			buttonsRow->setBackground(0.f,0.f,0.f);
			buttonsRow->setGravity(LayoutBase::HGravity::CENTERH,LayoutBase::VGravity::CENTERV);
			buttonsRow->setPadding(0,0);
			buttonsRow->setSpacing(10);
			btnYes=std::shared_ptr<Button>(new Button(L"Yes",L""));
			btnYes->setVisible(true);
			btnYes->setEnabled(true);
			btnYes->setSize(100,30);
			btnYes->setPadding(0,0);
			btnYes->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnYes->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnYes,1,1);
			btnNo=std::shared_ptr<Button>(new Button(L"No",L""));
			btnNo->setVisible(true);
			btnNo->setEnabled(true);
			btnNo->setSize(100,30);
			btnNo->setPadding(0,0);
			btnNo->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
			btnNo->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
			buttonsRow->add(*btnNo,2,1);
			btnCancel=std::shared_ptr<Button>(new Button(L"Cancel",L""));
			btnCancel->setVisible(true);
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
		drawing=new D2DUIDrawableItem(*this,false);
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
	void MsgBox::Show(){
		DialogBase::Show();
		drawing->setVisible(true);
	}
	void MsgBox::Hide(){
		DialogBase::Hide();
		drawing->setVisible(false);
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
		if(buttonsRow->windows.size()!=0){
			for(int i=0;i<buttonsRow->windows.size();i++){
				buttonsRow->windows.at(i).get().setTextSize(px);
			}
		}
	}
	void MsgBox::setBackground(int R,int G,int B,int A){
		WindowBase::setBackground(R,G,B,A);
	}
	void MsgBox::setBackground(float R,float G,float B,float A){
		WindowBase::setBackground(R,G,B,A);
	}
	void MsgBox::setForeground(int R,int G,int B,int A){
		WindowBase::setForeground(R,G,B,A);
		textTitle->setForeground(R,G,B,A);
		textContent->setForeground(R,G,B,A);
		if(buttonsRow->windows.size()!=0){
			for(int i=0;i<buttonsRow->windows.size();i++){
				buttonsRow->windows.at(i).get().setForeground(R,G,B,A);
			}
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
		d2d->dwritefactory->CreateTextLayout(textTitle->getText().c_str(),wcslen(textTitle->getText().c_str()),formattitle,(float)(r.right-r.left),(float)(r.bottom-r.top),&layouttitle);
		layouttitle->GetMetrics(&titlemetrics);
		int titlewidth=titlemetrics.width;
		int titleheight=titlemetrics.height;
		textTitle->setSize(titlewidth,titleheight);
		d2d->dwritefactory->CreateTextFormat(textContent->getFont(),NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,textContent->getTextSize()*(96.f/72.f),locale,&formatcontent);
		d2d->dwritefactory->CreateTextLayout(textContent->getText().c_str(),wcslen(textContent->getText().c_str()),formatcontent,(float)(r.right-r.left),(float)(r.bottom-r.top),&layoutcontent);
		layoutcontent->GetMetrics(&contentmetrics);
		int textcontentwidth=contentmetrics.layoutWidth/2;
		int textcontentheight=contentmetrics.height*2;
		textContent->setSize(textcontentwidth+textContent->getLeftPadding()+textContent->getRightPadding(),textcontentheight);
		int maxwidth=0;
		int buttonsrowwidth=100*buttonsRow->windows.size();
		buttonsRow->setSize(buttonsrowwidth,40);
		int totalcontentheight=textcontentheight<32? 32: textcontentheight;
		int totalcontentwidth=32+contentRow->getSpacing()+textContent->getLeftPadding()+textcontentwidth+textContent->getRightPadding();
		if(titlewidth>=totalcontentwidth){
			if(titlewidth>=buttonsrowwidth){
				maxwidth=titlewidth;
			}
			else{
				maxwidth=buttonsrowwidth;
			}
		}
		else{
			if(totalcontentwidth>=buttonsrowwidth){
				maxwidth=totalcontentwidth;
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
		contentRow->setBounds(getLeftPadding()+((winwidth/2)-(maxwidth/2)),textTitle->getBounds().bottom+getTopPadding(),getLeftPadding()+((winwidth/2)-(maxwidth/2))+maxwidth,textTitle->getBounds().bottom+getTopPadding()+totalcontentheight);
		buttonsRow->setBounds(getLeftPadding()+((winwidth/2)-(buttonsrowwidth/2)),contentRow->getBounds().bottom,getLeftPadding()+((winwidth/2)-(buttonsrowwidth/2))+buttonsrowwidth,contentRow->getBounds().bottom+buttonsRow->getHeight());
		formattitle->Release();
		formatcontent->Release();
		layouttitle->Release();
		layoutcontent->Release();
	}
	void MsgBox::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		reorderComponents(d2d);
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA_bg[0],fRGBA_bg[1],fRGBA_bg[2]),solidbrush.ReleaseAndGetAddressOf());
		solidbrush->SetOpacity(fRGBA_bg[3]*opacity);
		textTitle->recreateResources(d2d);
		contentRow->recreateResources(d2d);
		buttonsRow->recreateResources(d2d);
	}
	void MsgBox::draw(std::shared_ptr<D2DHandle>& d2d){
		solidbrush->SetColor(ColorF(ColorF::Black));
		solidbrush->SetOpacity(0.5f*opacity);
		d2d->target->FillRectangle(RectF((float)getBounds().left+2,(float)getBounds().top+2,(float)getBounds().right+2,(float)getBounds().bottom+2),solidbrush.Get());
		solidbrush->SetColor(ColorF(fRGBA_bg[0],fRGBA_bg[1],fRGBA_bg[2]));
		solidbrush->SetOpacity(fRGBA[3]*opacity);
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),solidbrush.Get());
		solidbrush->SetColor(ColorF(ColorF::White));
		solidbrush->SetOpacity(opacity);
		d2d->target->DrawRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),solidbrush.Get());
		textTitle->draw(d2d);
		contentRow->draw(d2d);
		buttonsRow->draw(d2d);
	}
	InfoBox::InfoBox(HWND parent,std::wstring text){
		this->hwnd=parent;
		textContent=std::shared_ptr<TextLabel>(new TextLabel(text));
		textContent->setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
		textContent->setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		textContent->setPadding(0,0);
		setFont(L"Microsoft Sans Serif");
		setTextSize(12.0f);
		setBackground(1.f,0.f,1.f,1.f);
		setForeground(1.f,1.f,1.f,1.f);
		drawing=new D2DUIDrawableItem(*this,false);
	}
	void InfoBox::setFont(wchar_t* font){
		this->font=font;
		textContent->setFont(font);
	}
	void InfoBox::setTextSize(float px){
		WindowBase::setTextSize(px);
		textContent->setTextSize(px);
	}
	void InfoBox::Show(){
		DialogBase::Show();
		drawing->setVisible(true);
	}
	void InfoBox::Hide(){
		DialogBase::Hide();
		drawing->setVisible(false);
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
		setPadding(10,5);
		DWRITE_TEXT_METRICS contentmetrics;
		IDWriteTextFormat* formatcontent;
		IDWriteTextLayout* layoutcontent;
		d2d->dwritefactory->CreateTextFormat(textContent->getFont(),NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,textContent->getTextSize()*(96.f/72.f),locale,&formatcontent);
		d2d->dwritefactory->CreateTextLayout(textContent->getText().c_str(),wcslen(textContent->getText().c_str()),formatcontent,(float)(r.right-r.left),(float)(r.bottom-r.top),&layoutcontent);
		layoutcontent->GetMetrics(&contentmetrics);
		int textcontentwidth=contentmetrics.widthIncludingTrailingWhitespace;
		int textcontentheight=contentmetrics.height*2;
		textContent->setSize(textcontentwidth,textcontentheight);
		setBounds(((winwidth/2)-((textcontentwidth)/2)),((winheight/2)-((textcontentheight)/2)),((winwidth/2)-(textcontentwidth/2))+textcontentwidth,((winheight/2)-(textcontentheight/2))+textcontentheight);
		textContent->setBounds(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding(),getBounds().right-getRightPadding(),getBounds().bottom-getBottomPadding());
	}
	void InfoBox::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		reorderComponents(d2d);
		textContent->recreateResources(d2d);
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA_bg[0],fRGBA_bg[1],fRGBA_bg[2]),solidbrush.ReleaseAndGetAddressOf());
		solidbrush->SetOpacity(fRGBA_bg[3]*opacity);
	}
	void InfoBox::draw(std::shared_ptr<D2DHandle>& d2d){
		solidbrush->SetColor(ColorF(ColorF::Black));
		solidbrush->SetOpacity(0.5f*opacity);
		d2d->target->FillRectangle(RectF((float)getBounds().left+2,(float)getBounds().top+2,(float)getBounds().right+2,(float)getBounds().bottom+2),solidbrush.Get());
		solidbrush->SetColor(ColorF(fRGBA_bg[0],fRGBA_bg[1],fRGBA_bg[2]));
		solidbrush->SetOpacity(fRGBA[3]*opacity);
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),solidbrush.Get());
		solidbrush->SetColor(ColorF(ColorF::White));
		solidbrush->SetOpacity(opacity);
		d2d->target->DrawRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),solidbrush.Get());
		textContent->draw(d2d);
	}
	PopupNotification::PopupNotification(HWND parent,std::wstring text,long duration){
		this->hwnd=parent;
		this->duration=duration;
		textContent=std::shared_ptr<TextLabel>(new TextLabel(text));
		textContent->setPadding(0,0);
		setPadding(0,0);
		showing=false;
		opacity=0;
		setFont(L"Microsoft Sans Serif");
		setForeground(0.f,0.f,0.f);
		setTextSize(12.0f);
		drawing=new D2DUIDrawableItem(*this,false);
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
		d2d->dwritefactory->CreateTextLayout(textContent->getText().c_str(),wcslen(textContent->getText().c_str()),formatcontent,(float)(r.right-r.left),(float)(r.bottom-r.top),&layoutcontent);
		layoutcontent->GetMetrics(&contentmetrics);
		int textcontentwidth=contentmetrics.widthIncludingTrailingWhitespace;
		int textcontentheight=contentmetrics.height*2;
		textContent->setSize(textcontentwidth,textcontentheight);
		setBounds(((winwidth/2)-((textcontentwidth)/2)),((winheight/2)-((textcontentheight)/2)),((winwidth/2)-(textcontentwidth/2))+textcontentwidth,((winheight/2)-(textcontentheight/2))+textcontentheight);
		textContent->setBounds(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding(),getBounds().right-getRightPadding(),getBounds().bottom-getBottomPadding());
	}
	void PopupNotification::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		reorderComponents(d2d);
		textContent->recreateResources(d2d);
	}
	void PopupNotification::draw(std::shared_ptr<D2DHandle>& d2d){
		setForeground(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity);
		d2d->target->PushAxisAlignedClip(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),D2D1_ANTIALIAS_MODE_ALIASED);
		textContent->draw(d2d);
		d2d->target->PopAxisAlignedClip();
	}
	void WindowBase::setParentLayout(std::shared_ptr<LayoutBase> parent){
		this->parent=parent;
	}
	std::shared_ptr<LayoutBase> WindowBase::getParentLayout(){
		return parent;
	}
	void LayoutBase::setParentLayout(std::shared_ptr<LayoutBase> parent){
		this->parent=parent;
	}
	std::shared_ptr<LayoutBase> LayoutBase::getParentLayout(){
		return parent;
	}
	void LayoutBase::setVisible(bool visible){
		drawing->setVisible(visible);
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
		drawing=new D2DUIDrawableItem(*this,false);
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
		if(!isinwindows){
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
						windows.at(j).get().setBounds(left,top,left+windows.at(j).get().getWidth(),top+windows.at(j).get().getHeight());
						top+=windows.at(j).get().getHeight()+getSpacing();
						break;
					}
				}
				for(int j=0;j<layouts.size();j++){
					if(layouts.at(j).get().getIndex()==i){
						layouts.at(j).get().setBounds(left,top,left+layouts.at(j).get().getWidth(),top+layouts.at(j).get().getHeight());
						top+=layouts.at(j).get().getHeight()+getSpacing();
						break;
					}
				}
			}
		}//Vertical Placement
		else if(getOrientation()==HORIZONTAL){
			for(int i=0;i<components;i++){
				for(int j=0;j<windows.size();j++){
					if(windows.at(j).get().getIndex()==i){
						windows.at(j).get().setBounds(left,top,left+windows.at(j).get().getWidth(),top+windows.at(j).get().getHeight());
						left+=windows.at(j).get().getWidth()+getSpacing();
						break;
					}
				}
				for(int j=0;j<layouts.size();j++){
					if(layouts.at(j).get().getIndex()==i){
						layouts.at(j).get().setBounds(left,top,left+layouts.at(j).get().getWidth(),top+layouts.at(j).get().getHeight());
						left+=layouts.at(j).get().getWidth()+getSpacing();
						break;
					}
				}
			}
		}//Horizontal Placement
	}
	void LinearLayout::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		reorderComponents();
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2]),solidbrush.ReleaseAndGetAddressOf());
		solidbrush->SetOpacity(fRGBA[3]);
		if(windows.size()!=0){
			for(int i=0;i<windows.size();i++){
				if(windows.at(i).get().isVisible())windows.at(i).get().recreateResources(d2d);
			}
		}
		if(layouts.size()!=0){
			for(int i=0;i<layouts.size();i++){
				if(layouts.at(i).get().drawing->isVisible())layouts.at(i).get().recreateResources(d2d);
			}
		}
	}
	void LinearLayout::draw(std::shared_ptr<D2DHandle>& d2d){
		solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2]));
		solidbrush->SetOpacity(fRGBA[3]);
		d2d->target->FillRoundedRectangle(RoundedRect(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),radius_x,radius_y),solidbrush.Get());
		d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
		if(&leftBorder!=NULL){
			solidbrush->SetColor(ColorF(leftBorder.fRGBA[0],leftBorder.fRGBA[1],leftBorder.fRGBA[2],leftBorder.fRGBA[3]));
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
				break;
			}
		}
		if(&topBorder!=NULL){
			solidbrush->SetColor(ColorF(topBorder.fRGBA[0],topBorder.fRGBA[1],topBorder.fRGBA[2],topBorder.fRGBA[3]));
			switch(topBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),solidbrush.Get(),getTopBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),solidbrush.Get(),getTopBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),solidbrush.Get(),getTopBorder().getStrokeWidth());
				break;
			}
		}
		if(&rightBorder!=NULL){
			solidbrush->SetColor(ColorF(rightBorder.fRGBA[0],rightBorder.fRGBA[1],rightBorder.fRGBA[2],rightBorder.fRGBA[3]));
			switch(rightBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),solidbrush.Get(),getRightBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),solidbrush.Get(),getRightBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),solidbrush.Get(),getRightBorder().getStrokeWidth());
				break;
			}
		}
		if(&bottomBorder!=NULL){
			solidbrush->SetColor(ColorF(bottomBorder.fRGBA[0],bottomBorder.fRGBA[1],bottomBorder.fRGBA[2],bottomBorder.fRGBA[3]));
			switch(bottomBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),solidbrush.Get(),getBottomBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),solidbrush.Get(),getBottomBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),solidbrush.Get(),getBottomBorder().getStrokeWidth());
				break;
			}
		}
		d2d->target->PushAxisAlignedClip(RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),D2D1_ANTIALIAS_MODE_ALIASED);
		d2d->target->SaveDrawingState(d2d->targetstate.Get());
		d2d->target->SetTransform(Matrix3x2F::Translation(getBounds().left,getBounds().top));
		if(layouts.size()!=0){
			for(int i=0;i<layouts.size();i++){
				if(layouts.at(i).get().drawing->isVisible())layouts.at(i).get().draw(d2d);
			}
		}
		if(windows.size()!=0){
			for(int i=0;i<windows.size();i++){
				if(windows.at(i).get().isVisible())windows.at(i).get().draw(d2d);
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
		drawing=new D2DUIDrawableItem(*this,false);
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
		if(!inwindows){
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
		int cellwidth=((getBounds().right-getBounds().left)-getLeftPadding()-getRightPadding()-(getSpacing()*(rows-1)))/rows;
		int cellheight=((getBounds().bottom-getBounds().top)-getTopPadding()-getBottomPadding()-(getSpacing()*(cols-1)))/cols;
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
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
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
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
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
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
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
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
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
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
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
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
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
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
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
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
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
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
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
						switch(hg){
						case HGravity::LEFT:
							switch(vg){
							case VGravity::TOP:
								if(layouts.at(l).get().getHeight()>cellheight){
									layouts.at(l).get().height=cellheight;
								}
								if(layouts.at(l).get().getWidth()>cellwidth){
									layouts.at(l).get().width=cellwidth;
								}
								layouts.at(l).get().setBounds(left,top,left+layouts.at(l).get().getWidth(),top+layouts.at(l).get().getHeight());
								if(k==rows){
									left=initialleft;
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
								}
								break;
							case VGravity::CENTERV:
								if(layouts.at(l).get().getHeight()>cellheight){
									layouts.at(l).get().height=cellheight;
								}
								if(layouts.at(l).get().getWidth()>cellwidth){
									layouts.at(l).get().width=cellwidth;
								}
								layouts.at(l).get().setBounds(left,top+((cellheight/2)-(layouts.at(l).get().getHeight()/2)),left+layouts.at(l).get().getWidth(),top+((cellheight/2)-(layouts.at(l).get().getHeight()/2))+layouts.at(l).get().getHeight());
								if(k==rows){
									left=initialleft;
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
								}
								break;
							case VGravity::BOTTOM:
								if(layouts.at(l).get().getHeight()>cellheight){
									layouts.at(l).get().height=cellheight;
								}
								if(layouts.at(l).get().getWidth()>cellwidth){
									layouts.at(l).get().width=cellwidth;
								}
								layouts.at(l).get().setBounds(left,top+cellheight-layouts.at(l).get().getHeight(),left+layouts.at(l).get().getWidth(),top+cellheight);
								if(k==rows){
									left=initialleft;
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
								}
								break;
							}
							break;
						case HGravity::CENTERH:
							switch(vg){
							case VGravity::TOP:
								if(layouts.at(l).get().getHeight()>cellheight){
									layouts.at(l).get().height=cellheight;
								}
								if(layouts.at(l).get().getWidth()>cellwidth){
									layouts.at(l).get().width=cellwidth;
								}
								layouts.at(l).get().setBounds(left+((cellwidth/2)-(layouts.at(l).get().getHeight()/2)),top,left+((cellwidth/2)-(layouts.at(l).get().getWidth()/2))+layouts.at(l).get().getWidth(),top+layouts.at(l).get().getHeight());
								if(k==rows){
									left=initialleft;
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
								}
								break;
							case VGravity::CENTERV:
								if(layouts.at(l).get().getHeight()>cellheight){
									layouts.at(l).get().height=cellheight;
								}
								if(layouts.at(l).get().getWidth()>cellwidth){
									layouts.at(l).get().width=cellwidth;
								}
								layouts.at(l).get().setBounds(left+((cellwidth/2)-(layouts.at(l).get().getWidth()/2)),top+((cellheight/2)-(layouts.at(l).get().getHeight()/2)),left+((cellwidth/2)-(layouts.at(l).get().getWidth()/2))+layouts.at(l).get().getWidth(),top+((cellheight/2)-(layouts.at(l).get().getHeight()/2))+layouts.at(l).get().getHeight());
								if(k==rows){
									left=initialleft;
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
								}
								break;
							case VGravity::BOTTOM:
								if(layouts.at(l).get().getHeight()>cellheight){
									layouts.at(l).get().height=cellheight;
								}
								if(layouts.at(l).get().getWidth()>cellwidth){
									layouts.at(l).get().width=cellwidth;
								}
								layouts.at(l).get().setBounds(left+((cellwidth/2)-(layouts.at(l).get().getWidth()/2)),top+cellheight-layouts.at(l).get().getHeight(),left+((cellwidth/2)-(layouts.at(l).get().getWidth()/2))+layouts.at(l).get().getWidth(),top+cellheight);
								if(k==rows){
									left=initialleft;
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
								}
								break;
							}
							break;
						case HGravity::RIGHT:
							switch(vg){
							case VGravity::TOP:
								if(layouts.at(l).get().getHeight()>cellheight){
									layouts.at(l).get().height=cellheight;
								}
								if(layouts.at(l).get().getWidth()>cellwidth){
									layouts.at(l).get().width=cellwidth;
								}
								layouts.at(l).get().setBounds(left+cellwidth-layouts.at(l).get().getWidth(),top,left+cellwidth,top+layouts.at(l).get().getHeight());
								if(k==rows){
									left=initialleft;
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
								}
								break;
							case VGravity::CENTERV:
								if(layouts.at(l).get().getHeight()>cellheight){
									layouts.at(l).get().height=cellheight;
								}
								if(layouts.at(l).get().getWidth()>cellwidth){
									layouts.at(l).get().width=cellwidth;
								}
								layouts.at(l).get().setBounds(left+cellwidth-layouts.at(l).get().getWidth(),top+((cellheight/2)-(layouts.at(l).get().getHeight()/2)),left+cellwidth,top+((cellheight/2)-(layouts.at(l).get().getHeight()/2))+layouts.at(l).get().getHeight());
								if(k==rows){
									left=initialleft;
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
								}
								break;
							case VGravity::BOTTOM:
								if(layouts.at(l).get().getHeight()>cellheight){
									layouts.at(l).get().height=cellheight;
								}
								if(layouts.at(l).get().getWidth()>cellwidth){
									layouts.at(l).get().width=cellwidth;
								}
								layouts.at(l).get().setBounds(left+cellwidth-layouts.at(l).get().getWidth(),top+cellheight-layouts.at(l).get().getHeight(),left+cellwidth,top+cellheight);
								if(k==rows){
									left=initialleft;
									top+=cellheight+getSpacing();
								}
								else{
									left+=cellwidth+getSpacing();
								}
								break;
							}
							break;
						}
						break;
					}
				}
			}
		}
	}
	void GridLayout::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2]),solidbrush.ReleaseAndGetAddressOf());
		solidbrush->SetOpacity(fRGBA[3]);
		switch(leftBorder.getStroke()){
		case Border::DOTTED:
			d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
			break;
		case Border::DASHED:
			d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
			break;
		case Border::INSET:
			break;
		case Border::OUTSET:
			break;
		case Border::SOLID:
			break;
		}
		switch(topBorder.getStroke()){
		case Border::DOTTED:
			d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
			break;
		case Border::DASHED:
			d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
			break;
		case Border::INSET:
			break;
		case Border::OUTSET:
			break;
		case Border::SOLID:
			break;
		}
		switch(rightBorder.getStroke()){
		case Border::DOTTED:
			d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
			break;
		case Border::DASHED:
			d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
			break;
		case Border::INSET:
			break;
		case Border::OUTSET:
			break;
		case Border::SOLID:
			d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_SOLID,0.0f),NULL,0,strokestyle.GetAddressOf());
			break;
		}
		switch(leftBorder.getStroke()){
		case Border::DOTTED:
			d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
			break;
		case Border::DASHED:
			d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
			break;
		case Border::INSET:
			break;
		case Border::OUTSET:
			break;
		case Border::SOLID:
			break;
		}
		reorderComponents();
		if(windows.size()!=0){
			for(int i=0;i<windows.size();i++){
				if(windows.at(i).get().isVisible())windows.at(i).get().recreateResources(d2d);
			}
		}
		if(layouts.size()!=0){
			for(int i=0;i<layouts.size();i++){
				if(windows.at(i).get().isVisible())layouts.at(i).get().recreateResources(d2d);	
			}
		}
	}
	void GridLayout::draw(std::shared_ptr<D2DHandle>& d2d){
		d2d->target->FillRoundedRectangle(RoundedRect(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),radius_x,radius_y),solidbrush.Get());
		solidbrush->SetColor(ColorF(leftBorder.fRGBA[0],leftBorder.fRGBA[1],leftBorder.fRGBA[2],leftBorder.fRGBA[3]));
		//d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
		d2d->target->PushAxisAlignedClip(RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),D2D1_ANTIALIAS_MODE_ALIASED);
		for(int i=0;i<windows.size();i++){
			if(windows.at(i).get().isVisible())windows.at(i).get().draw(d2d);
		}
		for(int i=0;i<layouts.size();i++){
			if(layouts.at(i).get().drawing->isVisible())layouts.at(i).get().draw(d2d);
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
				top+=height+getSpacing();
			}
		}
	}
	void TableLayout::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2]),solidbrush.ReleaseAndGetAddressOf());
		solidbrush->SetOpacity(fRGBA[3]);
		if(&leftBorder!=NULL){
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				break;
			}
		}
		if(&topBorder!=NULL){
			switch(topBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				break;
			}
		}
		if(&rightBorder!=NULL){
			switch(rightBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				break;
			}
		}
		if(&bottomBorder!=NULL){
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				break;
			}
		}
		reorderComponents();
		if(windows.size()!=0){
			for(int i=0;i<windows.size();i++){
				windows.at(i).get().recreateResources(d2d);
			}
		}
		if(layouts.size()!=0){
			for(int i=0;i<layouts.size();i++){
				layouts.at(i).get().recreateResources(d2d);	
			}
		}
	}
	void TableLayout::draw(std::shared_ptr<D2DHandle>& d2d){
		ComPtr<ID2D1StrokeStyle> strokestyle;
		solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2]));
		solidbrush->SetOpacity(fRGBA[3]);
		d2d->target->FillRoundedRectangle(RoundedRect(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),radius_x,radius_y),solidbrush.Get());
		if(&leftBorder!=NULL){
			solidbrush->SetColor(ColorF(leftBorder.fRGBA[0],leftBorder.fRGBA[1],leftBorder.fRGBA[2],leftBorder.fRGBA[3]));
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),solidbrush.Get(),getLeftBorder().getStrokeWidth());
				break;
			}
		}
		if(&topBorder!=NULL){
			solidbrush->SetColor(ColorF(topBorder.fRGBA[0],topBorder.fRGBA[1],topBorder.fRGBA[2],topBorder.fRGBA[3]));
			switch(topBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),solidbrush.Get(),getTopBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),solidbrush.Get(),getTopBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getTopBorder().getStrokeWidth()/2),(float)getBounds().top+(getTopBorder().getStrokeWidth()/2)),solidbrush.Get(),getTopBorder().getStrokeWidth());
				break;
			}
		}
		if(&rightBorder!=NULL){
			solidbrush->SetColor(ColorF(rightBorder.fRGBA[0],rightBorder.fRGBA[1],rightBorder.fRGBA[2],rightBorder.fRGBA[3]));
			switch(rightBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),solidbrush.Get(),getRightBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),solidbrush.Get(),getRightBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().top+(getRightBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getRightBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getRightBorder().getStrokeWidth()/2)),solidbrush.Get(),getRightBorder().getStrokeWidth());
				break;
			}
		}
		if(&bottomBorder!=NULL){
			solidbrush->SetColor(ColorF(bottomBorder.fRGBA[0],bottomBorder.fRGBA[1],bottomBorder.fRGBA[2],bottomBorder.fRGBA[3]));
			switch(bottomBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),solidbrush.Get(),getBottomBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,&strokestyle);
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getBottomBorder().getStrokeWidth()/2)),solidbrush.Get(),getBottomBorder().getStrokeWidth(),strokestyle.Get());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				d2d->target->DrawLine(Point2F((float)getBounds().left+(getBottomBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().right-(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),solidbrush.Get(),getBottomBorder().getStrokeWidth());
				break;
			}
		}
		d2d->target->PushAxisAlignedClip(RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),D2D1_ANTIALIAS_MODE_ALIASED);
		if(rows.size()!=0){
			for(int i=0;i<rows.size();i++){
				if(rows.at(i).get().drawing->isVisible())rows.at(i).get().draw(d2d);
			}
		}
		d2d->target->PopAxisAlignedClip();
	}
	TableRow::TableRow(int cols){
		TableRow::cols=cols;
		setBorder(Border());
		setGravity(HGravity::CENTERH,VGravity::CENTERV);
		setBounds(0,0,0,0);
		drawing=new D2DUIDrawableItem(*this,false);
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
		if(!inwindows){
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
		int leftpadding=getLeftPadding();
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
							left+=cellwidth+getSpacing();
							break;
						case VGravity::CENTERV:
							windows.at(j).get().setBounds(left,top+((maxheight/2)-(windows.at(j).get().getHeight()/2)),left+windows.at(j).get().getWidth(),top+((maxheight/2)-(windows.at(j).get().getHeight()/2))+windows.at(j).get().getHeight());
							left+=cellwidth+getSpacing();
							break;
						case VGravity::BOTTOM:
							windows.at(j).get().setBounds(left,top+maxheight-windows.at(j).get().getHeight(),left+windows.at(j).get().getWidth(),top+maxheight);
							left+=cellwidth+getSpacing();
							break;
						}
						break;
					case HGravity::CENTERH:
						switch(vg){
						case VGravity::TOP:
							windows.at(j).get().setBounds(left+((cellwidth/2)-(windows.at(j).get().getWidth()/2)),top,left+((cellwidth/2)-(windows.at(j).get().getWidth()/2))+windows.at(j).get().getWidth(),top+windows.at(j).get().getHeight());
							left+=cellwidth+getSpacing();
							break;
						case VGravity::CENTERV:
							windows.at(j).get().setBounds(left+((cellwidth/2)-(windows.at(j).get().getWidth()/2)),top+((maxheight/2)-(windows.at(j).get().getHeight()/2)),left+((cellwidth/2)-(windows.at(j).get().getWidth()/2))+windows.at(j).get().getWidth(),top+((maxheight/2)-(windows.at(j).get().getHeight()/2))+windows.at(j).get().getHeight());
							left+=cellwidth+getSpacing();
							break;
						case VGravity::BOTTOM:
							windows.at(j).get().setBounds(left+((cellwidth/2)-(windows.at(j).get().getWidth()/2)),top+maxheight-windows.at(j).get().getHeight(),left+((cellwidth/2)-(windows.at(j).get().getWidth()/2))+windows.at(j).get().getWidth(),top+maxheight);
							left+=cellwidth+getSpacing();
							break;
						}
						break;
					case HGravity::RIGHT:
						switch(vg){
						case VGravity::TOP:
							windows.at(j).get().setBounds(left+cellwidth-windows.at(j).get().getWidth(),top,left+cellwidth,top+windows.at(j).get().getHeight());
							left+=cellwidth+getSpacing();
							break;
						case VGravity::CENTERV:
							windows.at(j).get().setBounds(left+cellwidth-windows.at(j).get().getWidth(),top+((maxheight/2)-(windows.at(j).get().getHeight()/2)),left+cellwidth,top+((maxheight/2)-(windows.at(j).get().getHeight()/2))+windows.at(j).get().getHeight());
							left+=cellwidth+getSpacing();
							break;
						case VGravity::BOTTOM:
							windows.at(j).get().setBounds(left+cellwidth-windows.at(j).get().getWidth(),top+maxheight-windows.at(j).get().getHeight(),left+cellwidth,top+maxheight);
							left+=cellwidth+getSpacing();
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
							left+=cellwidth+getSpacing();
							break;
						case VGravity::CENTERV:
							layouts.at(k).get().setBounds(left,top+((maxheight/2)-(layouts.at(k).get().getHeight()/2)),left+layouts.at(k).get().getWidth(),top+((maxheight/2)-(layouts.at(k).get().getHeight()/2))+layouts.at(k).get().getHeight());
							left+=cellwidth+getSpacing();
							break;
						case VGravity::BOTTOM:
							layouts.at(k).get().setBounds(left,top+maxheight-layouts.at(k).get().getHeight(),left+layouts.at(k).get().getWidth(),top+maxheight);
							left+=cellwidth+getSpacing();
							break;
						}
						break;
					case HGravity::CENTERH:
						switch(vg){
						case VGravity::TOP:
							layouts.at(k).get().setBounds(left+((cellwidth/2)-(layouts.at(k).get().getWidth()/2)),top,left+((cellwidth/2)-(layouts.at(k).get().getWidth()/2))+layouts.at(k).get().getWidth(),top+layouts.at(k).get().getHeight());
							left+=cellwidth+getSpacing();
							break;
						case VGravity::CENTERV:
							layouts.at(k).get().setBounds(left+((cellwidth/2)-(layouts.at(k).get().getWidth()/2)),top+((maxheight/2)-(layouts.at(k).get().getHeight()/2)),left+((cellwidth/2)-(layouts.at(k).get().getWidth()/2))+layouts.at(k).get().getWidth(),top+((maxheight/2)-(layouts.at(k).get().getHeight()/2))+layouts.at(k).get().getHeight());
							left+=cellwidth+getSpacing();
							break;
						case VGravity::BOTTOM:
							layouts.at(k).get().setBounds(left+((cellwidth/2)-(layouts.at(k).get().getWidth()/2)),top+maxheight-layouts.at(k).get().getHeight(),left+((cellwidth/2)-(layouts.at(k).get().getWidth()/2))+layouts.at(k).get().getWidth(),top+maxheight);
							left+=cellwidth+getSpacing();
							break;
						}
						break;
					case HGravity::RIGHT:
						switch(vg){
						case VGravity::TOP:
							layouts.at(k).get().setBounds(left+cellwidth-layouts.at(k).get().getWidth(),top,left+cellwidth,top+layouts.at(k).get().getHeight());
							left+=cellwidth+getSpacing();
							break;
						case VGravity::CENTERV:
							layouts.at(k).get().setBounds(left+cellwidth-layouts.at(k).get().getWidth(),top+((maxheight/2)-(layouts.at(k).get().getHeight()/2)),left+cellwidth,top+((maxheight/2)-(layouts.at(k).get().getHeight()/2))+layouts.at(k).get().getHeight());
							left+=cellwidth+getSpacing();
							break;
						case VGravity::BOTTOM:
							layouts.at(k).get().setBounds(left+cellwidth-layouts.at(k).get().getWidth(),top+maxheight-layouts.at(k).get().getHeight(),left+cellwidth,top+maxheight);
							left+=cellwidth+getSpacing();
							break;
						}
						break;
					}
				}
			}
		}
	}
	void TableRow::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2]),solidbrush.ReleaseAndGetAddressOf());
		solidbrush->SetOpacity(fRGBA[3]);
		if(&leftBorder!=NULL){
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				break;
			}
		}
		if(&topBorder!=NULL){
			switch(topBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				break;
			}
		}
		if(&rightBorder!=NULL){
			switch(rightBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				break;
			}
		}
		if(&bottomBorder!=NULL){
			switch(leftBorder.getStroke()){
			case Border::DOTTED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_CAP_STYLE_ROUND,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DOT,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::DASHED:
				d2d->d2dfactory->CreateStrokeStyle(StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_CAP_STYLE_FLAT,D2D1_LINE_JOIN_MITER,10.0f,D2D1_DASH_STYLE_DASH,0.0f),NULL,0,strokestyle.GetAddressOf());
				break;
			case Border::INSET:
				break;
			case Border::OUTSET:
				break;
			case Border::SOLID:
				break;
			}
		}
		reorderComponents();
		if(windows.size()!=0){
			for(int i=0;i<windows.size();i++){
				if(windows.at(i).get().isVisible())windows.at(i).get().recreateResources(d2d);
			}
		}
		if(layouts.size()!=0){
			for(int i=0;i<layouts.size();i++){
				if(layouts.at(i).get().drawing->isVisible())layouts.at(i).get().recreateResources(d2d);	
			}
		}
	}
	void TableRow::draw(std::shared_ptr<D2DHandle>& d2d){
		d2d->target->FillRoundedRectangle(RoundedRect(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),radius_x,radius_y),solidbrush.Get());
		//solidbrush->SetColor(ColorF(leftBorder.fRGBA[0],leftBorder.fRGBA[1],leftBorder.fRGBA[2],leftBorder.fRGBA[3]));
		//d2d->target->DrawLine(Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().top+(getLeftBorder().getStrokeWidth()/2)),Point2F((float)getBounds().left+(getLeftBorder().getStrokeWidth()/2),(float)getBounds().bottom-(getLeftBorder().getStrokeWidth()/2)),solidbrush.Get(),getLeftBorder().getStrokeWidth(),strokestyle.Get());
		d2d->target->PushAxisAlignedClip(RectF((float)getBounds().left+getLeftPadding(),(float)getBounds().top+getTopPadding(),(float)getBounds().right-getRightPadding(),(float)getBounds().bottom-getBottomPadding()),D2D1_ANTIALIAS_MODE_ALIASED);
		for(int i=0;i<windows.size();i++){
			if(windows.at(i).get().isVisible())windows.at(i).get().draw(d2d);
		}
		for(int i=0;i<layouts.size();i++){
			if(layouts.at(i).get().drawing->isVisible())layouts.at(i).get().draw(d2d);
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
	TextLabel::TextLabel(std::wstring text){
		states.push_back(NONE);
		TextLabel::text=text;
		setForeground(0.f,0.f,0.f);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
		drawing=new D2DUIDrawableItem(*this,false);
	}
	void TextLabel::recreateResources(std::shared_ptr<D2DHandle>& d2d){
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
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),solidbrush.ReleaseAndGetAddressOf());
		std::wstring wtext(getText());
		d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),textlayout.ReleaseAndGetAddressOf());
		DWRITE_TEXT_RANGE rng;
		rng.startPosition=0;
		rng.length=wtext.length();
		textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
		textlayout->SetFontFamilyName(font,rng);
		textlayout->SetLocaleName(locale,rng);
	}
	void TextLabel::draw(std::shared_ptr<D2DHandle>& d2d){
		solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2]));
		solidbrush->SetOpacity(fRGBA[3]*opacity);
		d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),textlayout.Get(),solidbrush.Get());
	}
	TextBox::TextBox(std::wstring text){
		states.push_back(NONE);
		TextBox::text=text;
		setHorizontalTextAlignment(HorizontalConstants::LEFT);
		setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		setForeground(0,0,0);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
		drawing=new D2DUIDrawableItem(*this,false);
	}
	void TextBox::measureCaret(int x,int y){
		DWORD caretWidth=1;
		SystemParametersInfo(SPI_GETCARETWIDTH,0,&caretWidth,0);
		DWORD halfCaret=caretWidth/2u;
		float px,py;
		DWRITE_TEXT_METRICS txtmetrics;
		textlayout->GetMetrics(&txtmetrics);
		DWRITE_HIT_TEST_METRICS htmetrics;
		textlayout->HitTestPoint(x,y,&trail,&inside,&htmetrics);
		measureCaret(htmetrics.textPosition);
	}
	void TextBox::measureCaret(int pos){
		DWORD caretWidth=1;
		SystemParametersInfo(SPI_GETCARETWIDTH,0,&caretWidth,0);
		DWORD halfCaret=caretWidth/2u;
		float px,py;
		DWRITE_TEXT_METRICS txtmetrics;
		textlayout->GetMetrics(&txtmetrics);
		DWRITE_HIT_TEST_METRICS htmetrics;
		textlayout->HitTestTextPosition(pos,trail,&px,&py,&htmetrics);
		caretRect.left=getBounds().left+getLeftPadding()+px-halfCaret;
		caretRect.top=getBounds().top+getTopPadding()+htmetrics.top;
		caretRect.right=getBounds().left+getLeftPadding()+px+(caretWidth-halfCaret);
		caretRect.bottom=caretRect.top+htmetrics.height;
	}
	void TextBox::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		if(isEnabled()){
			if(hasFocus()){
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\textbox_focus.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
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
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				textlayout->SetFontFamilyName(font,rng);
				textlayout->SetLocaleName(locale,rng);
			}
			else{
				d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\textbox.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
				d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
				d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
				d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
				d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
				d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
				d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
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
				d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),solidbrush.ReleaseAndGetAddressOf());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				textlayout->SetFontFamilyName(font,rng);
				textlayout->SetLocaleName(locale,rng);
			}
		}
		else{
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\textbox_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
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
			d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),solidbrush.ReleaseAndGetAddressOf());
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),textlayout.ReleaseAndGetAddressOf());
			DWRITE_TEXT_RANGE rng;
			rng.startPosition=0;
			rng.length=wtext.length();
			textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
			textlayout->SetFontFamilyName(font,rng);
			textlayout->SetLocaleName(locale,rng);
		}
	}
	void TextBox::draw(std::shared_ptr<D2DHandle>& d2d){
		if(hasFocus()){
			d2d->target->DrawBitmap(bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity));
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),textlayout.Get(),solidbrush.Get());
			if(&caretRect!=NULL){
				solidbrush->SetColor(ColorF(ColorF::Chocolate,opacity));
				d2d->target->FillRectangle(RectF(caretRect.left,caretRect.top,caretRect.right,caretRect.bottom),solidbrush.Get());
			}
		}
		else{
			d2d->target->DrawBitmap(bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity));
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),textlayout.Get(),solidbrush.Get());
		}
	}
	Button::Button(std::wstring text,wchar_t* icon){
		Button::text=text;
		Button::icon=icon;
		setForeground(0.f,0.f,0.f);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
		drawing=new D2DUIDrawableItem(*this,false);
	}
	void Button::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		//Button pressed recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\button_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed.ReleaseAndGetAddressOf());
		//Button hovered recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\button_hovered.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_hovered.ReleaseAndGetAddressOf());
		//Button normal recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\button.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
		//Button disabled recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\button_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_disabled.ReleaseAndGetAddressOf());
		//Text recreation
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
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),solidbrush.ReleaseAndGetAddressOf());
		d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),textlayout.ReleaseAndGetAddressOf());
		DWRITE_TEXT_RANGE rng;
		rng.startPosition=0;
		rng.length=wtext.length();
		textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
		textlayout->SetFontFamilyName(font,rng);
		textlayout->SetLocaleName(locale,rng);
	}
	void Button::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isEnabled()){
			if(isPressed()){
				d2d->target->DrawBitmap(bmp_pressed.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
			else if(isHovered()){
				d2d->target->DrawBitmap(bmp_hovered.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
			else{
				d2d->target->DrawBitmap(bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
		}
		else{
			d2d->target->DrawBitmap(bmp_disabled.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
		}
		solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity));
		d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),textlayout.Get(),solidbrush.Get());
	}
	ArrowButton::ArrowButton(ArrowButton_Type type,ArrowButton_Direction dir):Button(){
		ArrowButton::parentContainer=type;
		ArrowButton::direction=dir;
		drawing=new D2DUIDrawableItem(*this,false);
	}
	void ArrowButton::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		//Pressed ArrowButton recreation
		if(parentContainer==SPINNER){
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_pressed_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());	
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed_up.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_pressed_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed_down.ReleaseAndGetAddressOf());
		}//Spinner
		else{
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_pressed_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed_up.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_pressed_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed_down.ReleaseAndGetAddressOf());
		}//ComboBox
		//Hovered ArrowButton recreation
		if(parentContainer==SPINNER){
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_hovered_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_hovered_up.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_hovered_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_hovered_down.ReleaseAndGetAddressOf());
		}//Spinner
		else{
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_hovered_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_hovered_up.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_hovered_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_hovered_down.ReleaseAndGetAddressOf());
		}//ComboBox
		//Normal ArrowButton recreation
		if(parentContainer==SPINNER){
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_up.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_down.ReleaseAndGetAddressOf());
		}//Spinner
		else{
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_up.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_down.ReleaseAndGetAddressOf());
		}//ComboBox
		//Disabled ArrowButton recreation
		if(parentContainer==SPINNER){
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_disabled_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_disabled_up.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\spinner_arrowbutton_disabled_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_disabled_down.ReleaseAndGetAddressOf());
		}//Spinner
		else{
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_disabled_up.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_disabled_up.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\combobox_arrowbutton_disabled_down.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_disabled_down.ReleaseAndGetAddressOf());
		}//ComboBox
	}
	void ArrowButton::draw(std::shared_ptr<D2DHandle>& d2d){
		if(direction==UP){
			if(isEnabled()){
				if(isPressed()){
					d2d->target->DrawBitmap(bmp_pressed_up.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);	
				}
				else if(isHovered()){
					d2d->target->DrawBitmap(bmp_hovered_up.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				}
				else{
					d2d->target->DrawBitmap(bmp_up.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				}
			}
			else{
				d2d->target->DrawBitmap(bmp_disabled_up.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
		}
		else{
			if(isEnabled()){
				if(isPressed()){
					d2d->target->DrawBitmap(bmp_pressed_down.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);	
				}
				else if(isHovered()){
					d2d->target->DrawBitmap(bmp_hovered_down.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				}
				else{
					d2d->target->DrawBitmap(bmp_down.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				}
			}
			else{
				d2d->target->DrawBitmap(bmp_disabled_down.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
		}
	}
	Spinner::Spinner(int minValue,int maxValue,int value){
		Spinner::minValue=minValue;
		Spinner::maxValue=maxValue;
		Spinner::value=value;
		states.push_back(NONE);
		std::wstring text(L"");
		text+=std::to_wstring(value);
		valuemodifier=std::shared_ptr<TextBox>(new TextBox(text));
		up=std::shared_ptr<ArrowButton>(new ArrowButton(SPINNER,UP));
		down=std::shared_ptr<ArrowButton>(new ArrowButton(SPINNER,DOWN));
		setFont(L"Microsoft Sans Serif");
		setTextSize(12.0f);
		setForeground(0,0,0);
		drawing=new D2DUIDrawableItem(*this,false);
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
		drawing->setVisible(visible);
	}
	void Spinner::setBounds(int left,int top,int right,int bottom){
		WindowBase::setBounds(left,top,right,bottom);
		valuemodifier->setBounds(bounds.left,bounds.top,bounds.right-30,bounds.bottom);
		up->setBounds(bounds.right-30,bounds.top,bounds.right,bounds.top+((bounds.bottom-bounds.top)/2));
		down->setBounds(bounds.right-30,bounds.top+((bounds.bottom-bounds.top)/2),bounds.right,bounds.bottom);
	}
	void Spinner::setHorizontalTextAlignment(HorizontalConstants H){
		WindowBase::setHorizontalTextAlignment(H);
		valuemodifier->setHorizontalTextAlignment(H);
	}
	void Spinner::setVerticalTextAlignment(VerticalConstants V){
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
		std::wstring text=std::to_wstring(value);
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
	void Spinner::recreateResources(std::shared_ptr<D2DHandle>& d2d){
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
		up->recreateResources(d2d);
		down->recreateResources(d2d);
		valuemodifier->recreateResources(d2d);
	}
	void Spinner::draw(std::shared_ptr<D2DHandle>& d2d){
		valuemodifier->draw(d2d);
		up->draw(d2d);
		down->draw(d2d);
	}
	CheckBox::CheckBox(bool checked,std::wstring text){
		states.push_back(NONE);
		setChecked(checked);
		CheckBox::text=text;
		setForeground(0,0,0);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
		drawing=new D2DUIDrawableItem(*this,false);
	}
	void CheckBox::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		//Checkbox pressed-checked recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_pressed_checked.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed_checked.ReleaseAndGetAddressOf());
		//CheckBox hovered-checked recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_hovered_checked.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_hovered_checked.ReleaseAndGetAddressOf());
		//CheckBox checked recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_checked.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_checked.ReleaseAndGetAddressOf());
		//CheckBox pressed recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed.ReleaseAndGetAddressOf());
		//CheckBox hovered recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_hovered.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_hovered.ReleaseAndGetAddressOf());
		//CheckBox normal recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
		//CheckBox disabled-checked recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_disabled_checked.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_disabled_checked.ReleaseAndGetAddressOf());
		//CheckBox disabled recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\checkbox_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_disabled.ReleaseAndGetAddressOf());
		//Text recreation
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
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),solidbrush.ReleaseAndGetAddressOf());
		d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),textlayout.ReleaseAndGetAddressOf());
		DWRITE_TEXT_RANGE rng;
		rng.startPosition=0;
		rng.length=wtext.length();
		textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
		textlayout->SetFontFamilyName(font,rng);
		textlayout->SetLocaleName(locale,rng);
	}
	void CheckBox::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isEnabled()){
			if(isChecked()){
				if(isPressed()){
					d2d->target->DrawBitmap(bmp_pressed_checked.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				}
				else if(isHovered()){
					d2d->target->DrawBitmap(bmp_hovered_checked.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				}
				else{
					d2d->target->DrawBitmap(bmp_checked.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				}
			}
			else{
				if(isPressed()){
					d2d->target->DrawBitmap(bmp_pressed.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				}
				else if(isHovered()){
					d2d->target->DrawBitmap(bmp_hovered.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				}
				else{
					d2d->target->DrawBitmap(bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				}
			}
		}
		else{
			if(isChecked()){
				d2d->target->DrawBitmap(bmp_disabled_checked.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
			}
			else{
				d2d->target->DrawBitmap(bmp_disabled.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
			}
		}
		solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity));
		d2d->target->DrawTextLayout(Point2F((getBounds().bottom-getBounds().top)+getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),textlayout.Get(),solidbrush.Get());
	}
	DialogueBox::DialogueBox(std::wstring text):TextLabel(text){
		showncharacters=0;
		decorationfile=L"";
		decorationlevel=DECORATIONBELOWDIALOGUEBOX;
		useDecoration=false;
	}
	bool DialogueBox::usesDecoration(){
		return useDecoration;
	}
	void DialogueBox::setDecoration(wchar_t* file,DIALOGUEBOX_DECORATION_LEVEL decorationlevel,float opacity){
		decorationfile=file;
		DialogueBox::decorationlevel=decorationlevel;
		decorationopacity=opacity;
		useDecoration=true;
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
	void DialogueBox::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		if(usesDecoration()){
			d2d->imgfactory->CreateDecoderFromFilename(decorationfile,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getDecorationBounds().bottom-getDecorationBounds().top,getDecorationBounds().bottom-getDecorationBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
		}
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA_bg[0],fRGBA_bg[1],fRGBA_bg[2],fRGBA_bg[3]*opacity),solidbrush.ReleaseAndGetAddressOf());
	}
	void DialogueBox::draw(std::shared_ptr<D2DHandle>& d2d){
		if(usesDecoration()&&getDecorationLevel()==DECORATIONBELOWDIALOGUEBOX){
			d2d->target->DrawBitmap(bmp.Get(),RectF((float)getDecorationBounds().left,(float)getDecorationBounds().top,(float)getDecorationBounds().right,(float)getDecorationBounds().bottom),decorationopacity);
		}
		solidbrush->SetColor(ColorF(fRGBA_bg[0],fRGBA_bg[1],fRGBA_bg[2],fRGBA_bg[3]*opacity));
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),solidbrush.Get());
		if(usesDecoration()&&getDecorationLevel()==DECORATIONOVERDIALOGUEBOX){
			d2d->target->DrawBitmap(bmp.Get(),RectF((float)getDecorationBounds().left,(float)getDecorationBounds().top,(float)getDecorationBounds().right,(float)getDecorationBounds().bottom),decorationopacity);
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
		d2d->dwritefactory->CreateTextLayout(wtext.c_str(),showncharacters,d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),textlayout.ReleaseAndGetAddressOf());
		DWRITE_TEXT_RANGE rng;
		rng.startPosition=0;
		rng.length=wtext.length();
		textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
		textlayout->SetFontFamilyName(font,rng);
		textlayout->SetLocaleName(locale,rng);
		solidbrush->SetColor(ColorF(ColorF::Black));
		d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding()+2,getBounds().top+getTopPadding()+2),textlayout.Get(),solidbrush.Get());
		solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity));
		d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),textlayout.Get(),solidbrush.Get());
	}
	RadioButton::RadioButton(RadioGroup& parent,bool selected,std::wstring text): rgParent(parent){
		setParent(parent);
		setSelected(selected);
		RadioButton::text=text;
		setForeground(0,0,0);
		setTextSize(12.0f);
		setFont(L"Microsoft Sans Serif");
		drawing=new D2DUIDrawableItem(*this,false);
	}
	void RadioButton::setRBIndex(int index){
		rbIndex=index;
	}
	int RadioButton::getRBIndex(){
		return rbIndex;
	}
	void RadioButton::setParent(RadioGroup& rg){
		rg.add(*this);
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
	void RadioButton::setSelected(bool selected){
		bool foundinstates=false;
		if(selected){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==SELECTED){
					foundinstates=true;
					break;
				}
			}
			if(!foundinstates){
				states.push_back(SELECTED);
				rgParent.setSelectedIndex(getRBIndex());
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
	void RadioButton::removeParent(RadioGroup& rg){
		rgParent.remove(this->getRBIndex());
		setIndex(-1);
	}
	void RadioButton::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		//RadioButton pressed-selected recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_pressed_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed_selected.ReleaseAndGetAddressOf());
		//RadioButton hovered-selected recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_hovered_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_hovered_selected.ReleaseAndGetAddressOf());
		//RadioButton selected recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_selected.ReleaseAndGetAddressOf());
		//RadioButton pressed recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed.ReleaseAndGetAddressOf());
		//RadioButton hovered recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_hovered.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_hovered.ReleaseAndGetAddressOf());
		//RadioButton normal recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
		//RadioButton disabled-selected recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_disabled_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_disabled_selected.ReleaseAndGetAddressOf());
		//RadioButton disabled recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\radiobutton_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().bottom-getBounds().top,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_disabled.ReleaseAndGetAddressOf());
		//Text recreation
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
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity),solidbrush.ReleaseAndGetAddressOf());
		d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),textlayout.ReleaseAndGetAddressOf());
		DWRITE_TEXT_RANGE rng;
		rng.startPosition=0;
		rng.length=wtext.length();
		textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
		textlayout->SetFontFamilyName(font,rng);
		textlayout->SetLocaleName(locale,rng);
	}
	void RadioButton::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isEnabled()){
			if(isSelected()){
				if(isPressed()){
					d2d->target->DrawBitmap(bmp_pressed_selected.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				}
				else if(isHovered()){
					d2d->target->DrawBitmap(bmp_hovered_selected.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				}
				else{
					d2d->target->DrawBitmap(bmp_selected.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				}
			}
			else{
				if(isPressed()){
					d2d->target->DrawBitmap(bmp_pressed.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				}
				else if(isHovered()){
					d2d->target->DrawBitmap(bmp_hovered.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				}
				else{
					d2d->target->DrawBitmap(bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
				}
			}
		}
		else{
			if(isSelected()){
				d2d->target->DrawBitmap(bmp_disabled_selected.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
			}
			else{
				d2d->target->DrawBitmap(bmp_disabled.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().left+(getBounds().bottom-getBounds().top),(float)getBounds().bottom),opacity);
			}
		}
		d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),textlayout.Get(),solidbrush.Get());
	}
	ToggleButton::ToggleButton(ToggleGroup& parent,bool selected,std::wstring text,wchar_t* icon):WindowBase(),tgParent(parent){
		setParent(parent);
		ToggleButton::text=text;
		ToggleButton::icon=icon;
		setForeground(0,0,0);
		setTextSize(12.0f);
		setSelected(selected);
		setFont(L"Microsoft Sans Serif");
		drawing=new D2DUIDrawableItem(*this,false);
	}
	void ToggleButton::setTBIndex(int index){
		tbIndex=index;
	}
	int ToggleButton::getTBIndex(){
		return tbIndex;
	}
	void ToggleButton::setParent(ToggleGroup& tg){
		tg.add(*this);
	}
	ToggleGroup& ToggleButton::getParent(){
		return tgParent;
	}
	void ToggleButton::setSelected(bool selected){
		bool foundinstates=false;
		if(selected){
			for(int i=0;i<states.size();i++){
				if(states.at(i)==SELECTED){
					foundinstates=true;
					break;
				}
			}
			if(!foundinstates){
				states.push_back(SELECTED);
				tgParent.setSelectedIndex(getTBIndex());
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
	void ToggleButton::removeParent(ToggleGroup& rg){
		tgParent.remove(this->getIndex());
		setIndex(-1);
	}
	void ToggleButton::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		//ToggleButton selected recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton_selected.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_selected.ReleaseAndGetAddressOf());
		//ToggleButton pressed recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed.ReleaseAndGetAddressOf());
		//ToggleButton hovered recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton_hovered.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_hovered.ReleaseAndGetAddressOf());
		//ToggleButton normal recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
		//ToggleButton disabled recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\togglebutton_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_disabled.ReleaseAndGetAddressOf());
		//Text recreation
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
		d2d->target->CreateSolidColorBrush(ColorF(ToggleButton::fRGBA[0],ToggleButton::fRGBA[1],ToggleButton::fRGBA[2],ToggleButton::fRGBA[3]*opacity),solidbrush.ReleaseAndGetAddressOf());
		d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),textlayout.ReleaseAndGetAddressOf());
		DWRITE_TEXT_RANGE rng;
		rng.startPosition=0;
		rng.length=wtext.length();
		textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
		textlayout->SetFontFamilyName(font,rng);
		textlayout->SetLocaleName(locale,rng);
	}
	void ToggleButton::draw(std::shared_ptr<D2DHandle>& d2d){ 
		//DrawTextLayout measuring are just magic numbers made to fit the image proportions. Use your own proportions when using another image.
		if(isEnabled()){
			if(isSelected()){
				d2d->target->DrawBitmap(bmp_selected.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+((getBounds().right-getBounds().left)/50.f)+getLeftPadding(),getBounds().top+getTopPadding()),textlayout.Get(),solidbrush.Get());
			}
			else if(isPressed()){
				d2d->target->DrawBitmap(bmp_pressed.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+((getBounds().right-getBounds().left)/50.f)+getLeftPadding(),getBounds().top+getTopPadding()),textlayout.Get(),solidbrush.Get());
			}
			else if(isHovered()){
				d2d->target->DrawBitmap(bmp_hovered.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),textlayout.Get(),solidbrush.Get());
			}
			else{
				d2d->target->DrawBitmap(bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
				d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),textlayout.Get(),solidbrush.Get());
			}
		}
		else{
			d2d->target->DrawBitmap(bmp_disabled.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			d2d->target->DrawTextLayout(Point2F(getBounds().left+((getBounds().right-getBounds().left)/50.f)+getLeftPadding(),getBounds().top+getTopPadding()),textlayout.Get(),solidbrush.Get());
		}	
	}
	ImageView::ImageView(wchar_t* file){
		ImageView::path=file;
		states.push_back(NONE);
		drawing=new D2DUIDrawableItem(*this,true);
	}
	void ImageView::setFile(wchar_t* file){
		path=file;
	}
	wchar_t* ImageView::getFilePath(){
		return path;
	}
	void ImageView::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		d2d->imgfactory->CreateDecoderFromFilename(getFilePath(),NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
	}	
	void ImageView::draw(std::shared_ptr<D2DHandle>& d2d){
		d2d->target->DrawBitmap(bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
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
	void GifView::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		frame_bmp.clear();
		d2d->imgfactory->CreateDecoderFromFilename(getFilePath(),NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrameCount(&totalframes);
		for(int i=0;i<totalframes;i++){
			d2d->bmpdecoder->GetFrame(i,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			ComPtr<ID2D1Bitmap>bmp;
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());	
			frame_bmp.push_back(bmp);
		}
	}
	void GifView::draw(std::shared_ptr<D2DHandle>& d2d){
		d2d->target->DrawBitmap(frame_bmp.at(currentframe).Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
		if(currentframe<(totalframes-1)){
			currentframe++;
		}
		else{
			if(loop)currentframe=0;
		}
	}
	void OpacityMaskGifView::setMaskFile(wchar_t* maskfile){
		this->maskfile=maskfile;
	}
	wchar_t* OpacityMaskGifView::getMaskFile(){
		return maskfile;
	}
	void OpacityMaskGifView::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		if(frame_bmp.size()!=0){
			for(int i=0;i<frame_bmp.size();i++){
				frame_bmp.at(i).Reset();
			}
		}
		frame_bmp.clear();
		//Recreate image
		d2d->imgfactory->CreateDecoderFromFilename(getFilePath(),NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
		d2d->target->CreateBitmapBrush(bmp.Get(),bmp_brush.ReleaseAndGetAddressOf());
		//Recreate opacity mask
		d2d->imgfactory->CreateDecoderFromFilename(getMaskFile(),NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrameCount(&totalframes);
		for(int i=0;i<totalframes;i++){
			d2d->bmpdecoder->GetFrame(i,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			ComPtr<ID2D1Bitmap>new_bmp;
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,new_bmp.ReleaseAndGetAddressOf());	
			frame_bmp.push_back(new_bmp);
		}
	}
	void OpacityMaskGifView::draw(std::shared_ptr<D2DHandle>& d2d){
		d2d->target->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
		d2d->target->FillOpacityMask(frame_bmp.at(currentframe).Get(),bmp_brush.Get(),D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
		d2d->target->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
		if(currentframe<(totalframes-1)){
			currentframe++;
		}
		else{
			if(loop)currentframe=0;
		}
	}
	ImageButton::ImageButton(wchar_t* file,std::wstring text){
		disabledpath=pressedpath=hoveredpath=enabledpath=file;
		this->text=text;
		setForeground(0,0,0);
		setTextSize(12.0f);
		setHorizontalTextAlignment(HorizontalConstants::CENTER_HORIZONTAL);
		setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
		setFont(L"Microsoft Sans Serif");
		drawing=new D2DUIDrawableItem(*this,true);
	}
	ImageButton::ImageButton(wchar_t* enabledfile,wchar_t* disabledfile,wchar_t* pressedfile,wchar_t* hoveredfile,std::wstring text){
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
		drawing=new D2DUIDrawableItem(*this,true);
	}
	void ImageButton::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		//ImageButton pressed recreation
		if(wcscmp(pressedpath,L"")!=0){
			d2d->imgfactory->CreateDecoderFromFilename(pressedpath,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed.ReleaseAndGetAddressOf());
		}
		//ImageButton hovered recreation
		if(wcscmp(hoveredpath,L"")!=0){
			d2d->imgfactory->CreateDecoderFromFilename(hoveredpath,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_hovered.ReleaseAndGetAddressOf());
		}
		//ImageButton normal recreation
		if(wcscmp(enabledpath,L"")!=0){
			d2d->imgfactory->CreateDecoderFromFilename(enabledpath,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
		}
		if(wcscmp(disabledpath,L"")!=0){
			d2d->imgfactory->CreateDecoderFromFilename(disabledpath,NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_disabled.ReleaseAndGetAddressOf());
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
		//Text recreation
		d2d->target->CreateSolidColorBrush(ColorF(fRGBA[0],fRGBA[1],fRGBA[2]),solidbrush.ReleaseAndGetAddressOf());
		solidbrush->SetOpacity(fRGBA[3]*opacity);
		d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),textlayout.ReleaseAndGetAddressOf());
		DWRITE_TEXT_RANGE rng;
		rng.startPosition=0;
		rng.length=wtext.length();
		textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
		textlayout->SetFontFamilyName(font,rng);
		textlayout->SetLocaleName(locale,rng);
	}
	void ImageButton::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isEnabled()){
			if(isPressed()){
				d2d->target->DrawBitmap(bmp_pressed.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
			if(isHovered()){
				d2d->target->DrawBitmap(bmp_hovered.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
			else{
				d2d->target->DrawBitmap(bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
		}
		else{
			d2d->target->DrawBitmap(bmp_disabled.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
		}
		solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2]));
		solidbrush->SetOpacity(fRGBA[3]*opacity);
		d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),textlayout.Get(),solidbrush.Get());
	}
	wchar_t* ListItem::getFont(){
		return font;
	}
	void ListItem::setFont(wchar_t* font){
		ListItem::font=font;
	}
	wchar_t* ListItem::getIcon(){
		return icon;
	}
	void ListItem::setIcon(wchar_t* icon){
		ListItem::icon=icon;
	}
	float ListItem::getTextSize(){
		return textSize;
	}
	void ListItem::setTextSize(float px){
		ListItem::textSize=px;
	}
	std::wstring ListItem::getData(){
		return text;
	}
	wchar_t* ListItem::getTag(){
		wchar_t* nonconsttag=new wchar_t[wcslen(tag)];
		wcscpy(nonconsttag,tag);
		return nonconsttag;
	}
	void ListItem::setBounds(int left,int top,int right,int bottom){
		bounds.left=left;
		bounds.top=top;
		bounds.right=right;
		bounds.bottom=bottom;
	}
	RECT ListItem::getBounds(){
		return bounds;
	}
	void ListItem::setEnabled(bool enabled){
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
			if(!foundinstates){
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
	bool ListItem::isEnabled(){
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
	void ListItem::setPressed(bool pressed){
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
			if(!foundinstates){
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
	bool ListItem::isPressed(){
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
	void ListItem::setHovered(bool hovered){
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
			if(!foundinstates){
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
	bool ListItem::isHovered(){
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
	void ListItem::setSelected(bool selected){
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
			if(!foundinstates){
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
	bool ListItem::isSelected(){
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
	void ComboBox::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		tb->recreateResources(d2d);
		dropdown->recreateResources(d2d);
		vScrollBar->recreateResources(d2d);
		d2d->target->CreateSolidColorBrush(ColorF(ColorF::White),solidbrush.ReleaseAndGetAddressOf());
		solidbrush->SetOpacity(opacity);
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
		if(list.size()!=0){
			for(int i=0;i<list.size();i++){
				std::wstring wtext(list.at(i).getData());
				d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),list.at(i).textlayout.ReleaseAndGetAddressOf());
				DWRITE_TEXT_RANGE rng;
				rng.startPosition=0;
				rng.length=wtext.length();
				list.at(i).textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
				list.at(i).textlayout->SetFontFamilyName(font,rng);
				list.at(i).textlayout->SetLocaleName(locale,rng);
			}
		}
	}
	void ComboBox::drawDropdown(std::shared_ptr<D2DHandle>& d2d){
		if(isDropdownVisible()){
			solidbrush->SetColor(ColorF(ColorF::White));
			solidbrush->SetOpacity(opacity);
			d2d->target->FillRectangle(RectF(getBounds().left,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight()),solidbrush.Get());
			d2d->target->PushAxisAlignedClip(RectF(getBounds().left,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight()),D2D1_ANTIALIAS_MODE_ALIASED);
			float topY=(getTotalHeight()/vScrollBar->portions)*vScrollBar->position;
			d2d->target->SaveDrawingState(d2d->targetstate.Get());
			d2d->target->SetTransform(Matrix3x2F::Translation(0,-topY));
			if(list.size()!=0){
				for(int i=0;i<list.size();i++){
					if(list.at(i).isEnabled()){
						if(list.at(i).isSelected()){
							solidbrush->SetColor(ColorF(fRGBA_selected[0],fRGBA_selected[1],fRGBA_selected[2]));
							solidbrush->SetOpacity(fRGBA_selected[3]*opacity);
							d2d->target->FillRectangle(RectF(list.at(i).getBounds().left,list.at(i).getBounds().top,list.at(i).getBounds().right,list.at(i).getBounds().bottom),solidbrush.Get());
						}
						else if(list.at(i).isPressed()){
							solidbrush->SetColor(ColorF(fRGBA_pressed[0],fRGBA_pressed[1],fRGBA_pressed[2]));
							solidbrush->SetOpacity(fRGBA_pressed[3]*opacity);
							d2d->target->FillRectangle(RectF(list.at(i).getBounds().left,list.at(i).getBounds().top,list.at(i).getBounds().right,list.at(i).getBounds().bottom),solidbrush.Get());
						}
						else if(list.at(i).isHovered()){
							solidbrush->SetColor(ColorF(fRGBA_hovered[0],fRGBA_hovered[1],fRGBA_hovered[2]));
							solidbrush->SetOpacity(fRGBA_hovered[3]*opacity);
							d2d->target->FillRectangle(RectF(list.at(i).getBounds().left,list.at(i).getBounds().top,list.at(i).getBounds().right,list.at(i).getBounds().bottom),solidbrush.Get());
						}
					}
					else{
						solidbrush->SetColor(ColorF(fRGBA_disabled[0],fRGBA_disabled[1],fRGBA_disabled[2]));
						solidbrush->SetOpacity(fRGBA_disabled[3]*opacity);
						d2d->target->FillRectangle(RectF(list.at(i).getBounds().left,list.at(i).getBounds().top,list.at(i).getBounds().right,list.at(i).getBounds().bottom),solidbrush.Get());
					}
					solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2]));
					solidbrush->SetOpacity(fRGBA[3]*opacity);
					d2d->target->DrawTextLayout(Point2F(list.at(i).getBounds().left+getLeftPadding(),list.at(i).getBounds().top+getTopPadding()),list.at(i).textlayout.Get(),solidbrush.Get());
				}
			}
			d2d->target->PopAxisAlignedClip();
			d2d->target->RestoreDrawingState(d2d->targetstate.Get());
			if(vScrollBar->isVerticalScrollingEnabled()){
				vScrollBar->draw(d2d);
			}
		}
	}
	void ComboBox::draw(std::shared_ptr<D2DHandle>& d2d){
		tb->draw(d2d);
		dropdown->draw(d2d);
	}
	void ListBox::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		d2d->target->CreateSolidColorBrush(ColorF(ColorF::White),solidbrush.ReleaseAndGetAddressOf());
		solidbrush->SetOpacity(opacity);
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
		for(int i=0;i<list.size();i++){
			std::wstring wtext(list.at(i).getData());
			d2d->dwritefactory->CreateTextLayout(wtext.c_str(),wtext.length(),d2d->textformat.Get(),(float)(getBounds().right-getBounds().left-getLeftPadding()-getRightPadding()),(float)(getBounds().bottom-getBounds().top-getTopPadding()-getBottomPadding()),list.at(i).textlayout.ReleaseAndGetAddressOf());
			DWRITE_TEXT_RANGE rng;
			rng.startPosition=0;
			rng.length=wtext.length();
			list.at(i).textlayout->SetFontSize(textsize*(96.0f/72.0f),rng);
			list.at(i).textlayout->SetFontFamilyName(font,rng);
			list.at(i).textlayout->SetLocaleName(locale,rng);
		}
	}
	void ListBox::draw(std::shared_ptr<D2DHandle>& d2d){
		solidbrush->SetColor(ColorF(ColorF::White));
		solidbrush->SetOpacity(opacity);
		if(getViewportBounds().right>getBounds().right){
			hScrollBar->enableHorizontalScrolling();
		}
		if(getTotalHeight()>(getBounds().bottom)){
			vScrollBar->enableVerticalScrolling();
		}
		d2d->target->FillRectangle(RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),solidbrush.Get());
		d2d->target->PushAxisAlignedClip(RectF(getViewportBounds().left,getViewportBounds().top,getBounds().right,getBounds().bottom),D2D1_ANTIALIAS_MODE_ALIASED);
		float topY=((float)(getBounds().bottom-getBounds().top)/vScrollBar->portions)*vScrollBar->position;
		float leftY=((float)(getBounds().right-getBounds().left)/hScrollBar->portions)*hScrollBar->position;
		d2d->target->SaveDrawingState(d2d->targetstate.Get());
		d2d->target->SetTransform(Matrix3x2F::Translation(-leftY,-topY));
		for(int i=0;i<list.size();i++){
			if(list.at(i).isEnabled()){
				if(list.at(i).isSelected()){
					solidbrush->SetColor(ColorF(fRGBA_selected[0],fRGBA_selected[1],fRGBA_selected[2]));
					solidbrush->SetOpacity(fRGBA_selected[3]*opacity);
				}//Selected enabled ListItem
				else if(list.at(i).isPressed()){
					solidbrush->SetColor(ColorF(fRGBA_pressed[0],fRGBA_pressed[1],fRGBA_pressed[2]));
					solidbrush->SetOpacity(fRGBA_pressed[3]*opacity);
				}//Pressed enabled ListItem
				else if(list.at(i).isHovered()){
					solidbrush->SetColor(ColorF(fRGBA_hovered[0],fRGBA_hovered[1],fRGBA_hovered[2]));
					solidbrush->SetOpacity(fRGBA_hovered[3]*opacity);
				}//Hovered enabled ListItem
			}//Enabled ListItem
			else{
				solidbrush->SetColor(ColorF(fRGBA_disabled[0],fRGBA_disabled[1],fRGBA_disabled[2]));
				solidbrush->SetOpacity(fRGBA_disabled[3]*opacity);
			}//Disabled ListItem
			d2d->target->FillRectangle(RectF((float)getBounds().left+list.at(i).getBounds().left,(float)getBounds().top+list.at(i).getBounds().top,(float)getBounds().left+list.at(i).getBounds().right,(float)getBounds().top+list.at(i).getBounds().bottom),solidbrush.Get());
			solidbrush->SetColor(ColorF(fRGBA[0],fRGBA[1],fRGBA[2],fRGBA[3]*opacity));
			d2d->target->DrawTextLayout(Point2F(getBounds().left+getLeftPadding(),getBounds().top+getTopPadding()),list.at(i).textlayout.Get(),solidbrush.Get());
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
		drawing=new D2DUIDrawableItem(*this,false);
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
	void Slider::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		d2d->target->CreateSolidColorBrush(ColorF(ColorF::LightGray,opacity),solidbrush.ReleaseAndGetAddressOf());
		float size=(float)(getBounds().bottom-getBounds().top);
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\slide_thumb.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),size,size,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
	}
	void Slider::draw(std::shared_ptr<D2DHandle>& d2d){
		float size=(float)(getBounds().bottom-getBounds().top);
		float totalwidth=(float)(getBounds().right-getBounds().left);
		float trackheight=(size*2.f)/3.f;
		float pad=size-trackheight;
		float scale=(float)totalwidth/(float)maxValue;
		float top=getBounds().top+((size/2.f)-(trackheight/2.f));
		float thumbleft=getBounds().left + ((float)value*scale) - (size/2.f);
		d2d->target->FillRectangle(RectF((float)getBounds().left,top,(float)getBounds().right,(float)(top+trackheight)),solidbrush.Get());
		d2d->target->DrawBitmap(bmp.Get(),RectF((float)thumbleft,(float)getBounds().top,(float)(thumbleft+size),(float)getBounds().bottom),opacity);
	}
	LoadSlot::LoadSlot(std::wstring gamedat,std::wstring sysdate,std::wstring storyarc,wchar_t* thumb){
		gamedate=std::shared_ptr<TextLabel>(new TextLabel(gamedat));
		gamedate->setPadding(0,0);
		arc=std::shared_ptr<TextLabel>(new TextLabel(storyarc));
		arc->setPadding(0,0);
		systemdate=std::shared_ptr<TextLabel>(new TextLabel(sysdate));
		systemdate->setPadding(0,0);
		thumbnail=std::shared_ptr<ImageView>(new ImageView(thumb));
		setOpacity();
		setLocale(L"en-us");
		setTextSize(12.f);
		setFont(L"Microsoft Sans Serif");
		setHorizontalTextAlignment(HorizontalConstants::LEFT);
		setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
	}
	void LoadSlot::setBounds(int left,int top,int right,int bottom){
		//These numbers are based on the image proportions. Use your own when using a custom image.
		int width=right-left;
		int height=bottom-top;
		WindowBase::setBounds(left,top,right,bottom);
		int tnwidth=(int)((float)width*(4.f/15.f));
		int tnheight=(int)((float)tnwidth/(16.f/9.f));
		int tnleft=left+(width/15);
		int tntop=top+(height/2-tnheight/2);
		int tbright=right-(width/15);
		thumbnail->setBounds(tnleft,tntop,tnleft+tnwidth,tntop+tnheight);
		systemdate->setBounds(thumbnail->getBounds().right+(width/15),thumbnail->getBounds().bottom-(width/15),tbright-(width/30),thumbnail->getBounds().bottom);
		arc->setBounds(systemdate->getBounds().left,systemdate->getBounds().top-(width/15),tbright,systemdate->getBounds().top);
		gamedate->setBounds(arc->getBounds().left,arc->getBounds().top-(width/15),tbright,arc->getBounds().top);
	}
	void LoadSlot::setHorizontalTextAlignment(HorizontalConstants H){
		WindowBase::setHorizontalTextAlignment(H);
		gamedate->setHorizontalTextAlignment(H);
		arc->setHorizontalTextAlignment(H);
		systemdate->setHorizontalTextAlignment(H);
	}
	void LoadSlot::setVerticalTextAlignment(VerticalConstants V){
		WindowBase::setVerticalTextAlignment(V);
		gamedate->setVerticalTextAlignment(V);
		arc->setVerticalTextAlignment(V);
		systemdate->setVerticalTextAlignment(V);
	}
	void LoadSlot::setFont(wchar_t* font){
		WindowBase::setFont(font);
		gamedate->setFont(font);
		arc->setFont(font);
		systemdate->setFont(font);
	}
	void LoadSlot::setTextSize(float px){
		WindowBase::setTextSize(px);
		gamedate->setTextSize(px);
		arc->setTextSize(px);
		systemdate->setTextSize(px);
	}
	void LoadSlot::setForeground(int R,int G,int B,int A){
		WindowBase::setForeground(R,G,B,A);
		gamedate->setForeground(R,G,B,A);
		arc->setForeground(R,G,B,A);
		systemdate->setForeground(R,G,B,A);
	}
	void LoadSlot::setForeground(float R,float G,float B,float A){
		WindowBase::setForeground(R,G,B,A);
		gamedate->setForeground(R,G,B,A);
		arc->setForeground(R,G,B,A);
		systemdate->setForeground(R,G,B,A);
	}
	void LoadSlot::setOpacity(float opacity){
		WindowBase::setOpacity(opacity);
		gamedate->setOpacity(opacity);
		arc->setOpacity(opacity);
		systemdate->setOpacity(opacity);
		thumbnail->setOpacity(opacity);
	}
	void LoadSlot::setLocale(wchar_t* locale){
		WindowBase::setLocale(locale);
		gamedate->setLocale(locale);
		arc->setLocale(locale);
		systemdate->setLocale(locale);
	}
	void LoadSlot::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		//Pressed LoadSlot recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\loadslot_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed.ReleaseAndGetAddressOf());
		//Normal LoadSlot recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\loadslot.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
		//Disabled LoadSlot recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\loadslot_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_disabled.ReleaseAndGetAddressOf());
		thumbnail->recreateResources(d2d);
		gamedate->recreateResources(d2d);
		arc->recreateResources(d2d);
		systemdate->recreateResources(d2d);
	}
	void LoadSlot::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isEnabled()){
			if(isPressed()){
				d2d->target->DrawBitmap(bmp_pressed.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
			else{
				d2d->target->DrawBitmap(bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
		}
		else{
			d2d->target->DrawBitmap(bmp_disabled.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
		}
		thumbnail->draw(d2d);
		gamedate->draw(d2d);
		arc->draw(d2d);
		systemdate->draw(d2d);
	}
	SaveSlot::SaveSlot(std::wstring gamedat,std::wstring sysdate,std::wstring storyarc,wchar_t* thumb){
		gamedate=std::shared_ptr<TextLabel>(new TextLabel(gamedat));
		gamedate->setPadding(0,0);
		arc=std::shared_ptr<TextLabel>(new TextLabel(storyarc));
		arc->setPadding(0,0);
		systemdate=std::shared_ptr<TextLabel>(new TextLabel(sysdate));
		systemdate->setPadding(0,0);
		thumbnail=std::shared_ptr<ImageView>(new ImageView(thumb));
		setOpacity();
		setLocale(L"en-us");
		setTextSize(12.f);
		setFont(L"Microsoft Sans Serif");
		setHorizontalTextAlignment(HorizontalConstants::LEFT);
		setVerticalTextAlignment(VerticalConstants::CENTER_VERTICAL);
	}
	void SaveSlot::setBounds(int left,int top,int right,int bottom){
		//These numbers are based on the image proportions. Use your own when using a custom image.
		int width=right-left;
		int height=bottom-top;
		WindowBase::setBounds(left,top,right,bottom);
		int tnwidth=(int)((float)width*(4.f/15.f));
		int tnheight=(int)((float)tnwidth/(16.f/9.f));
		int tnleft=left+(width/15);
		int tntop=top+(height/2-tnheight/2);
		int tbright=right-(width/15);
		thumbnail->setBounds(tnleft,tntop,tnleft+tnwidth,tntop+tnheight);
		systemdate->setBounds(thumbnail->getBounds().right+(width/15),thumbnail->getBounds().bottom-(width/15),tbright-(width/30),thumbnail->getBounds().bottom);
		arc->setBounds(systemdate->getBounds().left,systemdate->getBounds().top-(width/15),tbright,systemdate->getBounds().top);
		gamedate->setBounds(arc->getBounds().left,arc->getBounds().top-(width/15),tbright,arc->getBounds().top);
	}
	void SaveSlot::setHorizontalTextAlignment(HorizontalConstants H){
		WindowBase::setHorizontalTextAlignment(H);
		gamedate->setHorizontalTextAlignment(H);
		arc->setHorizontalTextAlignment(H);
		systemdate->setHorizontalTextAlignment(H);
	}
	void SaveSlot::setVerticalTextAlignment(VerticalConstants V){
		WindowBase::setVerticalTextAlignment(V);
		gamedate->setVerticalTextAlignment(V);
		arc->setVerticalTextAlignment(V);
		systemdate->setVerticalTextAlignment(V);
	}
	void SaveSlot::setFont(wchar_t* font){
		WindowBase::setFont(font);
		gamedate->setFont(font);
		arc->setFont(font);
		systemdate->setFont(font);
	}
	void SaveSlot::setTextSize(float px){
		WindowBase::setTextSize(px);
		gamedate->setTextSize(px);
		arc->setTextSize(px);
		systemdate->setTextSize(px);
	}
	void SaveSlot::setForeground(int R,int G,int B,int A){
		WindowBase::setForeground(R,G,B,A);
		gamedate->setForeground(R,G,B,A);
		arc->setForeground(R,G,B,A);
		systemdate->setForeground(R,G,B,A);
	}
	void SaveSlot::setForeground(float R,float G,float B,float A){
		WindowBase::setForeground(R,G,B,A);
		gamedate->setForeground(R,G,B,A);
		arc->setForeground(R,G,B,A);
		systemdate->setForeground(R,G,B,A);
	}
	void SaveSlot::setOpacity(float opacity){
		WindowBase::setOpacity(opacity);
		gamedate->setOpacity(opacity);
		arc->setOpacity(opacity);
		systemdate->setOpacity(opacity);
		thumbnail->setOpacity(opacity);
	}
	void SaveSlot::setLocale(wchar_t* locale){
		WindowBase::setLocale(locale);
		gamedate->setLocale(locale);
		arc->setLocale(locale);
		systemdate->setLocale(locale);
	}
	void SaveSlot::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		//Pressed SaveSlot recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\saveslot_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed.ReleaseAndGetAddressOf());
		//Normal SaveSlot recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\saveslot.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
		//Disabled SaveSlot recreation
		d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\saveslot_disabled.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
		d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
		d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
		d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
		d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
		d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
		d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_disabled.ReleaseAndGetAddressOf());
		thumbnail->recreateResources(d2d);
		gamedate->recreateResources(d2d);
		arc->recreateResources(d2d);
		systemdate->recreateResources(d2d);
	}
	void SaveSlot::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isEnabled()){
			if(isPressed()){
				d2d->target->DrawBitmap(bmp_pressed.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
			else{
				d2d->target->DrawBitmap(bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
			}
		}
		else{
			d2d->target->DrawBitmap(bmp_disabled.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
		}
		thumbnail->draw(d2d);
		gamedate->draw(d2d);
		arc->draw(d2d);
		systemdate->draw(d2d);
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
	void ScrollBar::setVisible(bool visible){
		WindowBase::setVisible(visible);
		drawing->setVisible(visible);
	}
	void ScrollBar::recreateResources(std::shared_ptr<D2DHandle>& d2d){
		if(isVerticalScrollingEnabled()){
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_track_pressed.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_track.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
			float height=(float)(getBounds().bottom-getBounds().top)/portions;
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_thumb.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,(int)height,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_thumb.ReleaseAndGetAddressOf());
		}
		else if(isHorizontalScrollingEnabled()){
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_track_pressed_horizontal.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_pressed.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_track_horizontal.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,getBounds().bottom-getBounds().top,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateDecoderFromFilename(L"Images\\UI\\scrollbar_thumb_horizontal.png",NULL,GENERIC_READ,WICDecodeMetadataCacheOnLoad,d2d->bmpdecoder.ReleaseAndGetAddressOf());
			d2d->bmpdecoder->GetFrame(0,d2d->bmpframedecoder.ReleaseAndGetAddressOf());
			d2d->imgfactory->CreateBitmapScaler(d2d->bmpscaler.ReleaseAndGetAddressOf());
			float topY=(float)(getBounds().top)+((((float)(getBounds().bottom-getBounds().top))/portions)*position);
			float height=(float)(getBounds().bottom-getBounds().top)/portions;
			d2d->bmpscaler->Initialize(d2d->bmpframedecoder.Get(),getBounds().right-getBounds().left,(int)height,WICBitmapInterpolationModeFant);
			d2d->imgfactory->CreateFormatConverter(d2d->formatconverter.ReleaseAndGetAddressOf());
			d2d->formatconverter->Initialize(d2d->bmpscaler.Get(),GUID_WICPixelFormat32bppPRGBA,WICBitmapDitherTypeNone,NULL,0.0,WICBitmapPaletteTypeCustom);
			d2d->target->CreateBitmapFromWicBitmap(d2d->formatconverter.Get(),NULL,bmp_thumb.ReleaseAndGetAddressOf());
		}
	}
	void ScrollBar::draw(std::shared_ptr<D2DHandle>& d2d){
		if(isPressed()){
			d2d->target->DrawBitmap(bmp_pressed.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
		}
		else{
			d2d->target->DrawBitmap(bmp.Get(),RectF((float)getBounds().left,(float)getBounds().top,(float)getBounds().right,(float)getBounds().bottom),opacity);
		}
		float topY=(float)(getBounds().top)+((((float)(getBounds().bottom-getBounds().top))/portions)*position);
		float height=(float)(getBounds().bottom-getBounds().top)/portions;
		d2d->target->DrawBitmap(bmp_thumb.Get(),RectF((float)getBounds().left,topY,(float)getBounds().right,topY+height),opacity);
	}
}