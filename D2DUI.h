#ifndef D2DUI_INCLUDED
#define D2DUI_INCLUDED
#include "stdafx.h"
namespace D2DUI{
	class D2DUIDrawableItem;
	class newifstream{
	public:
		newifstream(wchar_t* filename=L""){
			newifstream::filename=filename;
		}
		~newifstream(){
		}
		wchar_t* getFilename(){return filename;}
		wchar_t* filename;
		bool operator== (const newifstream& other) const{
			return wcscmp(this->filename,other.filename)==0;
		}
	};
	interface OnClickListener{
		void onClick(int x,int y);
	};
	interface OnKeyListener{
		void onKeyPressed(WPARAM character);
		void onKeyReleased(WPARAM character);
		void onMeasureCaret();
	};
	typedef enum WINDOW_STATES{
		NONE=0,
		ENABLED=1,
		EDITABLE=2,
		HOVERED=3,
		FOCUSED=4,
		PRESSED=5,
		CHECKED=6,
		SELECTED=7,
		VISIBLE=8,
		DROPDOWN_VISIBLE=9
	}WINDOW_STATES;
	typedef enum HorizontalConstants{
		LEFT=0,
		CENTER_HORIZONTAL=1,
		RIGHT=2
	}HorizontalConstants;
	typedef enum VerticalConstants{
		TOP=3,
		CENTER_VERTICAL=4,
		BOTTOM=5
	}VerticalConstants;
	class TabControlConstants{
	public:
		TabControlConstants(){}
		~TabControlConstants(){}
		static const int LEFT=0;
		static const int TOP=1;
		static const int RIGHT=2;
		static const int BOTTOM=3;
		static const int LEFTTORIGHT=4;
		static const int RIGHTTOLEFT=5;
		static const int UPTODOWN=6;
		static const int DOWNTOUP=7;
	};
	class RadioGroup;
	class ToggleGroup;
	class LayoutBase;
	class WindowBase{
	public:
		WindowBase(){
		}
		~WindowBase(){}
		virtual void setOpacity(float opacity=1.0f){
			this->opacity=opacity;
		}
		virtual float getOpacity(){
			return opacity;
		}
		virtual void setLocale(wchar_t* locale){
			this->locale=locale;
		}
		virtual wchar_t* getLocale(){
			return locale;
		}
		virtual void setId(wchar_t* id){this->wndId=id;}
		virtual void setIndex(int index){this->index=index;}
		wchar_t* getId(){return wndId;}
		int getIndex(){return index;}
		static bool compareHeight(WindowBase& a,WindowBase& b){
			return a.height<b.height;
		}
		virtual void setBackground(int R,int G,int B,int A=255){
			iRGBA_bg[0]=R;
			iRGBA_bg[1]=G;
			iRGBA_bg[2]=B;
			iRGBA_bg[3]=A;
			fRGBA_bg[0]=R/255.0f;
			fRGBA_bg[1]=G/255.0f;
			fRGBA_bg[2]=B/255.0f;
			fRGBA_bg[3]=A/255.0f;
		}
		virtual int* getBackgroundInt(){
			return iRGBA_bg;
		}
		virtual void setBackground(float R,float G,float B,float A=1.0f){
			fRGBA_bg[0]=R;
			fRGBA_bg[1]=G;
			fRGBA_bg[2]=B;
			fRGBA_bg[3]=A;
			iRGBA_bg[0]=(int)(R*255.0f);
			iRGBA_bg[1]=(int)(G*255.0f);
			iRGBA_bg[2]=(int)(B*255.0f);
			iRGBA_bg[3]=(int)(A*255.0f);
		}
		virtual float* getBackgroundFloat(){
			return fRGBA_bg;
		}
		virtual void setSize(int width,int height){
			WindowBase::width=width;
			WindowBase::height=height;
		}
		virtual int getWidth(){
			return width;
		}
		virtual int getHeight(){
			return height;
		}
		virtual void setPosition(int row,int col){
			this->row=row;
			this->col=col;
		}
		virtual void setParentLayout(std::shared_ptr<LayoutBase> layout);
		virtual std::shared_ptr<LayoutBase> getParentLayout();
		//Sets the text for the window.
		virtual void setText(std::wstring text){
			this->text=text;
		}
		virtual std::wstring getText(){
			return text;
		}
		//Sets the font for the window.
		virtual void setFont(wchar_t* font){
			this->font=font;
		}
		//Retrieves the font being used by the window as a wchar_t* value.
		virtual wchar_t* getFont(){
			return font;
		}
		//Defines the coordinates of the window.
		virtual void setBounds(int left,int top,int right,int bottom){
			bounds.left=left;
			bounds.top=top;
			bounds.right=right;
			bounds.bottom=bottom;
		}
		//Retrieves the bounding rectangle for the window.
		virtual RECT getBounds(){
			return bounds;
		}
		//Sets an image file as an icon to the left of the button.
		virtual void setIcon(wchar_t* icon){
			this->icon=icon;
		}
		//Retrieves the file used as icon for the button, if any.
		virtual wchar_t* getIcon(){
			return icon;
		}
		//Sets the text's horizontal alignment.
		virtual void setHorizontalTextAlignment(HorizontalConstants h){
			hAlignment=h;
		}
		//Retrieves the horizontal text alignment as HorizontalConstants.
		virtual HorizontalConstants getHorizontalTextAlignment(){
			return hAlignment;
		}
		//Set the text's vertical alignment.
		virtual void setVerticalTextAlignment(VerticalConstants v){
			vAlignment=v;
		}
		//Retrieves the vertical text alignment as VerticalConstants.
		virtual VerticalConstants getVerticalTextAlignment(){
			return vAlignment;
		}
		//Defines the colour of the text. Values go from 0.0 to 1.0
		virtual void setForeground(float R,float G,float B,float A=1.0f){
			fRGBA[0]=R;
			fRGBA[1]=G;
			fRGBA[2]=B;
			fRGBA[3]=A;
			iRGBA[0]=(int)(R*255.0f);
			iRGBA[1]=(int)(G*255.0f);
			iRGBA[2]=(int)(B*255.0f);
			iRGBA[3]=(int)(A*255.0f);
		}
		//Defines the colour of the text. Values go from 0 to 255.
		virtual void setForeground(int R,int G,int B,int A=255){
			iRGBA[0]=R;
			iRGBA[1]=G;
			iRGBA[2]=B;
			iRGBA[3]=A;
			fRGBA[0]=R/255.0f;
			fRGBA[1]=G/255.0f;
			fRGBA[2]=B/255.0f;
			fRGBA[3]=A/255.0f;
		}
		//Retrieves the foreground's RGBA values, as an int array.
		virtual int* getForegroundInt(){
			return iRGBA;
		}
		//Retrieves the foreground's RGBA values, as a float array.
		virtual float* getForegroundFloat(){
			return fRGBA;
		}
		//Sets the size of the text, in floating point pixels
		virtual void setTextSize(float px){
			this->textsize=px;
		}
		//Retrieves the text size, as a float.
		virtual float getTextSize(){
			return textsize;
		}
		/* Sets the margin for the window to write text.
		If the window has an icon, it will be placed according the padding,
		and the text will be placed after the right margin of the button.*/
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1){
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
		//Enables or disables a window.
		virtual void setEnabled(bool enabled){
			bool foundinstates=false;
			if(enabled){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==ENABLED){
						foundinstates=true;
						break;
					}
				}
				if(!foundinstates){
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
		//Retrieves whether the window is enabled or not.
		virtual bool isEnabled(){
			bool enabled=false;
			for(int i=0;i<states.size();i++){
				if(states.at(i)==ENABLED){
					enabled=true;
					break;
				}
			}
			return enabled;
		}
		//Displays mouse-over effects.
		virtual void setHovered(bool hovered){
			bool foundinstates=false;
			if(hovered){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==HOVERED){
						foundinstates=true;
						break;
					}
				}
				if(!foundinstates){
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
		//Retrieves whether the mouse is over the window or not.
		virtual bool isHovered(){
			bool hovered=false;
			for(int i=0;i<states.size();i++){
				if(states.at(i)==HOVERED){
					hovered=true;
					break;
				}
			}
			return hovered;
		}
		//Displays mouse click effects.
		virtual void setPressed(bool pressed){
			bool foundinstates=false;
			if(pressed){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==PRESSED){
						foundinstates=true;
						break;
					}
				}
				if(!foundinstates){
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
		//Retrieves whether the window is being pressed or not.
		virtual bool isPressed(){
			bool pressed=false;
			for(int i=0;i<states.size();i++){
				if(states.at(i)==PRESSED){
					pressed=true;
					break;
				}
			}
			return pressed;
		}
		//Selects the current button from the group.
		virtual void setSelected(bool selected){}
		//Retrieves if the button is the one being selected.
		virtual bool isSelected(){
			bool selected=false;
			for(int i=0;i<states.size();i++){
				if(states.at(i)==SELECTED){
					selected=true;
					break;
				}
			}
			return selected;
		}
		//Allows you (or not) to write over a TextBox window.
		virtual void setEditable(bool editable){
			bool foundinstates=false;
			if(editable){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==EDITABLE){
						foundinstates=true;
						break;
					}
				}
				if(!foundinstates){
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
		//Retrieves whether the TextBox's text can be manipulated.
		virtual bool isEditable(){
			bool editable=false;
			for(int i=0;i<states.size();i++){
				if(states.at(i)==EDITABLE){
					editable=true;
					break;
				}
			}
			return editable;
		}
		//Enables a TextBox to write over it.
		virtual void setFocus(bool focus){
			bool foundinstates=false;
			if(focus){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==FOCUSED){
						foundinstates=true;
						break;
					}
				}
				if(!foundinstates){
					states.push_back(FOCUSED);
				}
			}
			else{
				for(int i=0;i<states.size();i++){
					if(states.at(i)==FOCUSED){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
		//Retrieves whether the TextBox is selected for writing.
		virtual bool hasFocus(){
			bool focused=false;
			for(int i=0;i<states.size();i++){
				if(states.at(i)==FOCUSED){
					focused=true;
					break;
				}
			}
			return focused;
		}
		//Retrieves the left margin of the window, as an int.
		virtual int getLeftPadding(){
			return leftPadding;
		}
		//Retrieves the top margin of the window, as an int.
		virtual int getTopPadding(){
			return topPadding;
		}
		//Retrieves the right margin of the window, as an int.
		virtual int getRightPadding(){
			return rightPadding;
		}
		//Retrieves the bottom margin of the window, as an int.
		virtual int getBottomPadding(){
			return bottomPadding;
		}
		//Displays or hides the window.
		virtual void setVisible(bool visible){
			bool foundinstates=false;
			if(visible){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						foundinstates=true;
						break;
					}
				}
				if(!foundinstates){
					states.push_back(VISIBLE);
				}
			}
			else{
				for(int i=0;i<states.size();i++){
					if(states.at(i)==VISIBLE){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
		//Retrieves whether the window is showing or not.
		virtual bool isVisible(){
			bool visible=false;
			for(int i=0;i<states.size();i++){
				if(states.at(i)==VISIBLE){
					visible=true;
					break;
				}
			}
			return visible;
		}
		//Checks or unchecks a CheckBox window.
		virtual void setChecked(bool checked){
			bool foundinstates=false;
			if(checked){
				for(int i=0;i<states.size();i++){
					if(states.at(i)==CHECKED){
						foundinstates=true;
						break;
					}
				}
				if(!foundinstates){
					states.push_back(CHECKED);
				}
			}
			else{
				for(int i=0;i<states.size();i++){
					if(states.at(i)==CHECKED){
						states.erase(states.begin()+i);
						break;
					}
				}
			}
		}
		//Retrieves whether a CheckBox is checked or not.
		virtual bool isChecked(){
			bool checked=false;
			for(int i=0;i<states.size();i++){
				if(states.at(i)==CHECKED){
					checked=true;
					break;
				}
			}
			return checked;
		}
		//Draws the contents of the window over a Direct2D render target
		virtual void draw(std::shared_ptr<D2DHandle>& d2d)=0;
		bool operator== (WindowBase& other){
			if(this->wndId==NULL||other.wndId==NULL){
				return false;
			}
			else{
				return (wcscmp(wndId,other.wndId)==0);
			}
		}
		int row,col;
		int height;
		int width;
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d)=0;
		ComPtr<ID2D1Bitmap> bmp,bmp_disabled,bmp_pressed,bmp_hovered,bmp_selected,bmp_pressed_selected,bmp_hovered_selected,bmp_disabled_selected,bmp_focused,bmp_checked,bmp_pressed_checked,bmp_hovered_checked,bmp_disabled_checked;
		ComPtr<IDWriteTextLayout>textlayout;
		ComPtr<ID2D1SolidColorBrush>solidbrush;
		std::shared_ptr<LayoutBase> parent;
		D2DUIDrawableItem* drawing;
	protected:
		std::vector<D2DUI::WINDOW_STATES>states;
		wchar_t* wndId;
		wchar_t* locale;
		int index;
		float opacity;
		float fRGBA_bg[4];
		int iRGBA_bg[4];
		wchar_t* font;
		float textsize;
		int iRGBA[4];
		float fRGBA[4];
		RECT bounds;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		VerticalConstants vAlignment;
		HorizontalConstants hAlignment;
		std::wstring text;
		wchar_t* icon;
	};
	class ScrollBar:public WindowBase{
	public:
		ScrollBar(){
			states.push_back(WINDOW_STATES::NONE);
			portions=1;
			position=0;
		}
		~ScrollBar(){}
		enum Orientation{
			HORIZONTAL=0,
			VERTICAL=1
		};
		int thumbwidth;
		void enableHorizontalScrolling();
		void disableHorizontalScrolling();
		void enableVerticalScrolling();
		void disableVerticalScrolling();
		bool isVerticalScrollingEnabled();
		bool isHorizontalScrollingEnabled();
		void scrollTo(float position);
		float portions;
		float position;
		bool vScroll;
		bool hScroll;
		Orientation o;
		void setOrientation(Orientation o);
		virtual void setVisible(bool visible);
		Orientation getOrientation();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
	private:
		ComPtr<ID2D1Bitmap>bmp_thumb;
		virtual void setText(std::wstring text){}
		virtual std::wstring getText(){return L"";}
		virtual void setFont(wchar_t* font){}
		virtual wchar_t* getFont(){return L"";}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
		virtual void setEnabled(bool enabled){}
		virtual bool isEnabled(){return false;}
		virtual void setForeground(int R,int G,int B,int A=255){}
		virtual void setForeground(float R,float G,float B,float A=1.0f){}
		virtual int* getForegroundInt(){
			int color[4]={0,0,0,0};
			return color;
		}
		virtual float* getForegroundFloat(){
			float color[4]={0.f,0.f,0.f,0.f};
			return color;
		}
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1){}
		virtual int getLeftPadding(){return 0;}
		virtual int getTopPadding(){return 0;}
		virtual int getRightPadding(){return 0;}
		virtual int getBottomPadding(){return 0;}
		virtual void setHorizontalTextAlignment(HorizontalConstants H){}
		virtual void setVerticalTextAlignment(VerticalConstants V){}
		virtual HorizontalConstants getHorizontalTextAlignment(){return LEFT;}
		virtual VerticalConstants getVerticalTextAlignment(){return TOP;}
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setTextSize(float px){}
		virtual float getTextSize(){return 0.f;}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
	};
	class Border{
	public:
		Border(){
			setStroke(NONE);
			setColor(0.f,0.f,0.f,1.f);
		}
		~Border(){}
		enum Stroke{
			NONE=0,
			SOLID=1,
			DASHED=2,
			INSET=3,
			OUTSET=4,
			DOTTED=5
		};
		void setColor(int R,int G,int B,int A=0);
		void setColor(float R,float G,float B,float A=0.0f);
		float* getColorFloat();
		int* getColorInt();
		float fRGBA[4];
		int iRGBA[4];
		Stroke stroke;
		float strokeWidth;
		void setStroke(Stroke s);
		Stroke getStroke();
		void setStrokeWidth(float px);
		float getStrokeWidth();
		void draw(std::shared_ptr<D2DHandle>& d2d);
	};
	class LayoutBase{
	public:
		LayoutBase(){}
		~LayoutBase(){}
		enum Orientation{
			VERTICAL=0,
			HORIZONTAL=1
		};
		enum VGravity{
			TOP=1,
			CENTERV=2,
			BOTTOM=3
		};
		enum HGravity{
			LEFT=1,
			CENTERH=2,
			RIGHT=3
		};
		virtual void setPosition(int row,int col){
			this->row=row;
			this->col=col;
		}
		virtual void setId(wchar_t* id){this->layId=id;}
		virtual void setIndex(int index){this->index=index;}
		virtual wchar_t* getId(){return layId;}
		virtual int getIndex(){return index;}
		virtual void reorderComponents()=0;
		virtual void setSize(int width,int height){
			this->width=width;
			this->height=height;
		}
		virtual int getWidth(){
			return width;
		}
		virtual int getHeight(){
			return height;
		}
		virtual void setVisible(bool visible);
		virtual void add(WindowBase& window)=0;
		virtual void add(WindowBase& window,int row,int col)=0;
		virtual void add(LayoutBase& layout)=0;
		virtual void add(LayoutBase& layout,int row,int col)=0;
		virtual void remove(wchar_t* id)=0;
		virtual void remove(int row,int col)=0;
		virtual void setRadius(float x,float y=-1){
			this->radius_x=x;
			this->radius_y=y;
			if(radius_y==-1){
				radius_y=radius_x;
			}
		}
		virtual float getXRadius(){
			return radius_x;
		}
		virtual float getYRadius(){
			return radius_y;
		}
		virtual void setBounds(int left,int top,int right,int bottom){
			bounds.left=left;
			bounds.top=top;
			bounds.right=right;
			bounds.bottom=bottom;
		}
		virtual void setOrientation(Orientation o){
			this->o=o;
		}
		virtual Orientation getOrientation(){
			return o;
		}
		virtual void setBackground(int R=0,int G=0,int B=0,int A=0){
			iRGBA[0]=R;
			iRGBA[1]=G;
			iRGBA[2]=B;
			iRGBA[3]=A;
			fRGBA[0]=R/255.0f;
			fRGBA[1]=G/255.0f;
			fRGBA[2]=B/255.0f;
			fRGBA[3]=A/255.0f;
		}
		virtual void setBackground(float R=0.f,float G=0.f,float B=0.f,float A=0.f){
			fRGBA[0]=R;
			fRGBA[1]=G;
			fRGBA[2]=B;
			fRGBA[3]=A;
			iRGBA[0]=(int)(R*255.0f);
			iRGBA[1]=(int)(G*255.0f);
			iRGBA[2]=(int)(B*255.0f);
			iRGBA[3]=(int)(A*255.0f);
		}
		virtual RECT getBounds(){
			return bounds;
		}
		virtual void setViewportBounds(int left,int top,int right,int bottom){
			viewportbounds.left=left;
			viewportbounds.top=top;
			viewportbounds.right=right;
			viewportbounds.bottom=bottom;
		}
		virtual RECT getViewportBounds(){
			return viewportbounds;
		}
		virtual void setScrollbarVisible(bool visible)=0;
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1){
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
		virtual void setSpacing(int spacing){
			this->spacing=spacing;
		}
		virtual int getSpacing(){
			return spacing;
		}
		virtual int getLeftPadding(){
			return leftPadding;
		}
		virtual int getTopPadding(){
			return topPadding;
		}
		virtual int getRightPadding(){
			return rightPadding;
		}
		virtual int getBottomPadding(){
			return bottomPadding;
		}
		virtual void setBorder(Border border){
			leftBorder=border;
			topBorder=border;
			rightBorder=border;
			bottomBorder=border;
		}
		virtual void setLeftBorder(Border border){
			leftBorder=border;
		}
		virtual void setTopBorder(Border border){
			topBorder=border;
		}
		virtual void setRightBorder(Border border){
			rightBorder=border;
		}
		virtual void setBottomBorder(Border border){
			bottomBorder=border;
		}
		virtual void setGravity(HGravity h,VGravity v){
			this->hg=h;
			this->vg=v;
		}
		virtual HGravity getHorizontalGravity(){
			return hg;
		}
		virtual VGravity getVerticalGravity(){
			return vg;
		}
		virtual Border getLeftBorder(){
			return leftBorder;
		}
		virtual Border getTopBorder(){
			return topBorder;
		}
		virtual Border getRightBorder(){
			return rightBorder;
		}
		virtual Border getBottomBorder(){
			return bottomBorder;
		}
		bool operator== (LayoutBase& other){
			if(this->layId==NULL||other.layId==NULL){
				return false;
			}
			else{
				return wcscmp(this->layId,other.layId)==0;
			}
		}
		virtual void setParentLayout(std::shared_ptr<LayoutBase> parent);
		virtual std::shared_ptr<LayoutBase> getParentLayout();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d)=0;
		int row;
		int col;
		int width;
		int height;
		std::vector<std::reference_wrapper<WindowBase>>windows;
		std::vector<std::reference_wrapper<LayoutBase>>layouts;
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d)=0;
		ComPtr<ID2D1SolidColorBrush> solidbrush;
		D2DUIDrawableItem* drawing;
	protected:
		ComPtr<ID2D1StrokeStyle> strokestyle;
		std::shared_ptr<LayoutBase> parent;
		RECT bounds,viewportbounds;
		HGravity hg;
		VGravity vg;
		wchar_t* layId;
		int index;
		int iRGBA[4];
		float fRGBA[4];
		float radius_x;
		float radius_y;
		Border leftBorder;
		Border topBorder;
		Border rightBorder;
		Border bottomBorder;
		Orientation o;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int spacing;
	};
	class D2DUIDrawableItem{
	public:
		D2DUIDrawableItem(){}
		D2DUIDrawableItem(WindowBase& parentWindow,bool visible){
			drawWindow.push_back(parentWindow);
			this->visible=visible;
		}
		D2DUIDrawableItem(LayoutBase& parentLayout,bool visible){
			drawLayout.push_back(parentLayout);
			this->visible=visible;
		}
		~D2DUIDrawableItem(){}
		std::vector<std::reference_wrapper<WindowBase>> drawWindow;
		std::vector<std::reference_wrapper<LayoutBase>> drawLayout;
		void setVisible(bool visible){this->visible=visible;}
		bool isVisible(){return visible;}
	private:
		bool visible;
	};
	class D2DUISystem{
	public:
		/*
		Layer description (objects in the same layer will be drawn by order of addition):
		1. Used for drawing normal objects.
		2. Used for drawing dropdowns.
		3. Used for drawing modal objects (MsgBox, InfoBox, PopupNotification, etc.) and its children.
		4. Used for drawing dropdowns inside modal objects (see above).
		*/
		void addDrawToQueue(int layer,D2DUIDrawableItem& draw);
		//Call this in your loop update. Once adding at least one item to the drawing system, you won't need to manually add the draw, customDraw or drawDropdown for each element.
		void draw(std::shared_ptr<D2DHandle>& d2d);
		std::map<int,std::vector<std::reference_wrapper<D2DUIDrawableItem>>>drawOrder;
		static D2DUISystem& getInstance();
	private:
		D2DUISystem(){}
		~D2DUISystem(){}
	};

	class LinearLayout:public LayoutBase{
	public:
		LinearLayout(Orientation o=VERTICAL);
		~LinearLayout(){}
		virtual void add(WindowBase& t);
		virtual void add(LayoutBase& t);
		virtual void remove(wchar_t* id);
		virtual void reorderComponents();
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setViewportBounds(int left,int top,int right,int bottom){}
		virtual RECT getViewportBounds(){return RECT();}
		virtual void setScrollbarVisible(bool visible){}
		virtual void add(WindowBase& window,int row,int col){}
		virtual void add(LayoutBase& layout,int row,int col){}
		virtual void remove(int row,int col){}
		virtual void setGravity(HGravity h,VGravity v){}
	};
	class GridLayout:public LayoutBase{
	public:
		GridLayout(int rows=1,int cols=1);
		~GridLayout(){}
		int rows;
		int cols;
		void swapElement(WindowBase& first,WindowBase& second);
		void swapElement(WindowBase& window,LayoutBase& layout);
		void swapElement(LayoutBase& first,LayoutBase& second);
		virtual void add(WindowBase& window,int row,int col);
		virtual void add(LayoutBase& layout,int row,int col);
		virtual void remove(int row,int col);
		virtual void reorderComponents();
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setScrollbarVisible(bool visible){}
		virtual void remove(wchar_t* id){}
		virtual void setViewportBounds(int left,int top,int right,int bottom){}
		virtual RECT getViewportBounds(){return RECT();}
		virtual void setOrientation(Orientation o){}
		virtual Orientation getOrientation(){return Orientation::VERTICAL;}
		virtual void add(WindowBase& window){}
		virtual void add(LayoutBase& layout){}
	};
	class TableRow:public LayoutBase{
	public:
		TableRow(int cols=1);
		~TableRow(){}
		int cols;
		virtual void add(WindowBase& window);
		virtual void add(LayoutBase& layout);
		virtual void remove(wchar_t* id);
		virtual void reorderComponents();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setScrollbarVisible(bool visible){}
		virtual void setViewportBounds(int left,int top,int right,int bottom){}
		virtual RECT getViewportBounds(){return RECT();}
		virtual void add(WindowBase& window,int row,int col){}
		virtual void add(LayoutBase& layout,int row,int col){}
		virtual void remove(int row,int col){}
		virtual void setRadius(float x,float y){}
		virtual float getXRadius(){return 0.f;}
		virtual float getYRadius(){return 0.f;}
		virtual void setOrientation(Orientation o){}
		virtual Orientation getOrientation(){return Orientation::VERTICAL;}
	};
	class TableLayout:public LayoutBase{
	public:
		TableLayout(){
			drawing=new D2DUIDrawableItem(*this,false);
		}
		~TableLayout(){}
		std::vector<std::reference_wrapper<TableRow>> rows;
		virtual void add(TableRow& row);
		virtual void remove(wchar_t* id);
		virtual void reorderComponents();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setViewportBounds(int left,int top,int right,int bottom){}
		virtual RECT getViewportBounds(){return RECT();}
		virtual void setScrollbarVisible(bool visible){}
		virtual void add(WindowBase& window){}
		virtual void add(LayoutBase& layout){}
		virtual void add(WindowBase& window,int col,int row){}
		virtual void add(LayoutBase& layout,int col,int row){}
		virtual void remove(int row,int col){}
		virtual void setOrientation(Orientation o){}
		virtual Orientation getOrientation(){return Orientation::VERTICAL;}

	};
	class RelativeLayout:public LayoutBase{
	public:
		RelativeLayout(){}
		~RelativeLayout(){}
		virtual void add(WindowBase& window,WindowBase& left=*((WindowBase*)NULL),WindowBase& top=*((WindowBase*)NULL),WindowBase& right=*((WindowBase*)NULL),WindowBase& bottom=*(WindowBase*)NULL);
		virtual void remove(wchar_t* id);
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void reorderComponents();
	private:
		virtual void setViewportBounds(int left,int top,int right,int bottom){}
		virtual void setScrollbarVisible(bool visible){}
		virtual void setGravity(HGravity h,VGravity v){}
	};
	class RadioButton:public WindowBase{
	public:
		RadioButton(RadioGroup& parent,bool selected=false,std::wstring text=L"");
		~RadioButton(){}
		wchar_t* tag;
		RadioGroup& rgParent;
		void setTag(wchar_t* tag=L"nulltag");
		wchar_t* getTag();
		void setParent(RadioGroup& rg);
		void removeParent(RadioGroup& rg);
		int rbIndex;
		RadioGroup& getParent();
		virtual void setSelected(bool selected) override;
		void setRBIndex(int index);
		int getRBIndex();
		virtual void setVisible(bool visible){
			WindowBase::setVisible(visible);
			drawing->setVisible(visible);
		}
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
	};
	class RadioGroup{
	public:
		RadioGroup(wchar_t* tag):selectedindex(0), tag(tag){}
		~RadioGroup(){}
		std::vector<std::reference_wrapper<RadioButton>>rg;
		wchar_t* tag;
		void add(RadioButton& rb);
		void remove(int index);
		void setSelectedIndex(int index);
		int getSelectedIndex();
	private:
		int selectedindex;
	};
	class ToggleButton:public WindowBase{
	public:
		ToggleButton(ToggleGroup& parent,bool selected=false,std::wstring text=L"",wchar_t* icon=L"");
		~ToggleButton(){}
		ToggleGroup& tgParent;
		virtual void setSelected(bool selected) override;
		void setParent(ToggleGroup& tg);
		void removeParent(ToggleGroup& tg);
		void setTBIndex(int index);
		void setVisible(bool visible){
			WindowBase::setVisible(visible);
			drawing->setVisible(visible);
		}
		int getTBIndex();
		int tbIndex;
		ToggleGroup& getParent();
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
	};
	class ToggleGroup{
	public:
		ToggleGroup(wchar_t* tag):selectedindex(0), tag(tag){}
		~ToggleGroup(){}
		wchar_t* tag;
		std::vector<std::reference_wrapper<ToggleButton>> tg;
		void add(ToggleButton& tb);
		void remove(int index);
		void setSelectedIndex(int index);
		int getSelectedIndex();
	private:
		int selectedindex;
	};
	class TabControl:public LayoutBase{
	public:
		TabControl(){}
		~TabControl(){}
		int selectedtab;
		int direction;
		//std::vector<std::reference_wrapper<TabContent>>tabs;
		//void addTab(TabContent& content);
		//void removeTab(int index);
		void setTabsPosition(const int pos);
		void setTabDirection(const int dir);
		int getTabPosition();
		int getTabDirection();
		void setCurrentTab(int index);
		int getCurrentTabIndex();
	};
	class TextLabel:public WindowBase{
	public:
		TextLabel(std::wstring text=L"");
		~TextLabel(){}
		virtual void setVisible(bool visible){
			WindowBase::setVisible(visible);
			drawing->setVisible(visible);
		}
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setEnabled(bool enabled){}
		virtual bool isEnabled(){return false;}
		virtual void setHovered(bool hovered){}
		virtual bool isHovered(){return false;}
		virtual void setPressed(bool pressed){}
		virtual bool isPressed(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
	};
	class TextBox:public WindowBase{
	public:
		TextBox(std::wstring text=L"");
		~TextBox(){}
		int caretPos;
		BOOL trail,inside;
		RECT caretRect;
		virtual void setVisible(bool visible){
			WindowBase::setVisible(visible);
			drawing->setVisible(visible);
		}
		virtual void measureCaret(int x,int y);
		virtual void measureCaret(int pos);
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setPressed(bool pressed){}
		virtual bool isPressed(){return false;}
		virtual void setHovered(bool hovered){}
		virtual bool isHovered(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}

	};
	class Button:public WindowBase{
	public:
		Button(std::wstring text=L"",wchar_t* icon=L"");
		~Button(){}
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void setVisible(bool visible){
			WindowBase::setVisible(visible);
			drawing->setVisible(visible);
		}
	private:
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
	};
	typedef enum ArrowButton_Type{
		SPINNER=1,
		COMBOBOX=2
	};
	typedef enum ArrowButton_Direction{
		UP=1,
		DOWN=2
	};
	class ArrowButton:public Button{
	public:
		ArrowButton(ArrowButton_Type type=COMBOBOX,ArrowButton_Direction dir=DOWN);
		~ArrowButton(){}
		ArrowButton_Type parentContainer;
		ArrowButton_Direction direction;
		virtual void draw(std::shared_ptr<D2DHandle>& d2d) override;
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d) override;
	private:
		ComPtr<ID2D1Bitmap>bmp_up,bmp_down,bmp_pressed_up,bmp_pressed_down,bmp_hovered_up,bmp_hovered_down,bmp_disabled_up,bmp_disabled_down;
		virtual void setHorizontalTextAlignment(HorizontalConstants H) override{}
		virtual void setVerticalTextAlignment(VerticalConstants V) override{}
		virtual HorizontalConstants getHorizontalTextAlignment() override{return LEFT;}
		virtual VerticalConstants getVerticalTextAlignment() override{return TOP;}
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1) override{}
		virtual int getLeftPadding() override{return 0;}
		virtual int getTopPadding() override{return 0;}
		virtual int getRightPadding() override{return 0;}
		virtual int getBottomPadding() override{return 0;}
		virtual std::wstring getText() override{return L"";}
		virtual void setText(std::wstring text) override{}
		virtual wchar_t* getFont() override{return L"";}
		virtual wchar_t* getIcon() override{return L"";}
		virtual void setIcon(wchar_t* icon) override{}
		virtual void setForeground(int R,int G,int B,int A=255) override{}
		virtual void setForeground(float R,float G,float B,float A=1.0f) override{}
		virtual int* getForegroundInt() override{int color[4]={0,0,0,0};return color;}
		virtual float* getForegroundFloat() override{float color[4]={0.f,0.f,0.f,0.f};return color;}
		virtual void setTextSize(float px) override{}
		virtual float getTextSize() override{return 0.f;}
	};
	typedef enum DIALOGUEBOX_DECORATION_LEVEL{
		DECORATIONOVERDIALOGUEBOX=1,
		DECORATIONATSAMELEVELDIALOGUEBOX=2,
		DECORATIONBELOWDIALOGUEBOX=3
	};
	class DialogueBox:public TextLabel{
	public:
		DialogueBox(std::wstring text=L"");
		~DialogueBox(){}
		int showncharacters;
		void setDecoration(wchar_t* file,DIALOGUEBOX_DECORATION_LEVEL decorationlevel=DECORATIONATSAMELEVELDIALOGUEBOX,float opacity=1.0f);
		wchar_t* getDecoration();
		DIALOGUEBOX_DECORATION_LEVEL getDecorationLevel();
		void setDecorationBounds(int left,int top,int right,int bottom);
		float getDecorationOpacity();
		RECT getDecorationBounds();
		void setTextShadow(bool shadow);
		bool hasTextShadow();
		bool usesDecoration();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d) override;
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		std::vector<ComPtr<IDWriteTextLayout>>letterlayouts;
	private:
		bool useDecoration;
		wchar_t* decorationfile;
		RECT decorationbounds;
		float decorationopacity;
		bool shadowenabled;
		DIALOGUEBOX_DECORATION_LEVEL decorationlevel;
	};
	class Spinner:public WindowBase{
	public:
		Spinner(int minValue=0,int maxValue=0,int value=0);
		~Spinner(){}
		int maxValue;
		int minValue;
		int value;
		std::shared_ptr<ArrowButton> up;
		std::shared_ptr<ArrowButton> down;
		void setValue(int value);
		void setMinimumValue(int minValue);
		void setMaximumValue(int maxValue);
		int getValue();
		int getMaximumValue();
		int getMinimumValue();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual void setVisible(bool visible);
		virtual void setEnabled(bool enabled);
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual void setHorizontalTextAlignment(HorizontalConstants H);
		virtual void setVerticalTextAlignment(VerticalConstants V);
		virtual void setEditable(bool editable);
		virtual void setFocus(bool focus);
		virtual void setFont(wchar_t* font);
		virtual void setTextSize(float px);
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.0f);
		virtual void setOpacity(float opacity=1.0f);
		virtual void setLocale(wchar_t* locale);
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
	protected:
		std::shared_ptr<TextBox> valuemodifier;
	private:
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setText(std::wstring text){}
		virtual std::wstring getText(){return L"";}
	};
	class CheckBox:public WindowBase{
	public:
		CheckBox(bool checked=true,std::wstring text=L"");
		~CheckBox(){}
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void setVisible(bool visible){
			WindowBase::setVisible(visible);
			drawing->setVisible(visible);
		}
	private:
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
	};
	class ListItem{
	public:
		ListItem(){
			states.push_back(WINDOW_STATES::NONE);
		}
		~ListItem(){
		}
		std::vector<D2DUI::WINDOW_STATES> states;
		ComPtr<IDWriteTextLayout>textlayout;
		std::wstring text;
		wchar_t* tag;
		RECT bounds;
		wchar_t* font;
		wchar_t* icon;
		float textSize;
		void setIcon(wchar_t* icon);
		wchar_t* getIcon();
		void setFont(wchar_t* font);
		wchar_t* getFont();
		void setTextSize(float px);
		float getTextSize();
		wchar_t* getTag();
		void setBounds(int left,int top,int right,int bottom);
		RECT getBounds();
		bool isFile();
		bool isString();
		void setSelected(bool selected);
		bool isSelected();
		void setEnabled(bool enabled);
		bool isEnabled();
		void setHovered(bool hovered);
		bool isHovered();
		void setPressed(bool pressed);
		bool isPressed();
		std::wstring getData();
		bool operator== (const ListItem& other) const{
			wchar_t* tag1=new wchar_t[wcslen(this->tag)];
			wcscpy(tag1,this->tag);
			wchar_t* tag2=new wchar_t[wcslen(other.tag)];
			wcscpy(tag2,other.tag);
			return wcscmp(tag1,tag2)==0;
		}
	};
	class ListBase{
	public:
		ListBase(){}
		~ListBase(){}
		std::vector<ListItem> list;
		virtual ListItem& getSelectedItem(){
			return selecteditem;
		}
		virtual void setSelectedItem(ListItem& t){
			selecteditem=t;
			auto it=std::find(list.begin(),list.end(),t);
			int c=std::distance(list.begin(),it);
			setSelectedIndex(c);
		}
		virtual void setSelectedIndex(int index){
			selectedindex=index;
			for(int i=0;i<list.size();i++){
				list.at(i).setSelected(false);
			}
			list.at(index).setSelected(true);
			selecteditem=list.at(index);
		}
		virtual int getSelectedIndex(){
			return selectedindex;
		}
		virtual void setSelectedItemColor(int R,int G,int B,int A=0){
			iRGBA_selected[0]=R;
			iRGBA_selected[1]=G;
			iRGBA_selected[2]=B;
			iRGBA_selected[3]=A;
			fRGBA_selected[0]=R/255.0f;
			fRGBA_selected[1]=G/255.0f;
			fRGBA_selected[2]=B/255.0f;
			fRGBA_selected[3]=A/255.0f;
		}
		virtual int* getSelectedItemColorInt(){
			return iRGBA_selected;
		}
		virtual void setSelectedItemColor(float R,float G,float B,float A=0.0f){
			fRGBA_selected[0]=R;
			fRGBA_selected[1]=G;
			fRGBA_selected[2]=B;
			fRGBA_selected[3]=A;
			iRGBA_selected[0]=(int)(R*255.0f);
			iRGBA_selected[1]=(int)(G*255.0f);
			iRGBA_selected[2]=(int)(B*255.0f);
			iRGBA_selected[3]=(int)(A*255.0f);
		}
		virtual float* getSelectedItemColorFloat(){
			return fRGBA_selected;
		}
		virtual void setPressedItemColor(int R,int G,int B,int A=0){
			iRGBA_pressed[0]=R;
			iRGBA_pressed[1]=G;
			iRGBA_pressed[2]=B;
			iRGBA_pressed[3]=A;
			fRGBA_pressed[0]=R/255.0f;
			fRGBA_pressed[1]=G/255.0f;
			fRGBA_pressed[2]=B/255.0f;
			fRGBA_pressed[3]=A/255.0f;
		}
		virtual int* getPressedItemColorInt(){
			return iRGBA_pressed;
		}
		virtual void setPressedItemColor(float R,float G,float B,float A=0.0f){
			fRGBA_pressed[0]=R;
			fRGBA_pressed[1]=G;
			fRGBA_pressed[2]=B;
			fRGBA_pressed[3]=A;
			iRGBA_pressed[0]=(int)(R*255.0f);
			iRGBA_pressed[1]=(int)(G*255.0f);
			iRGBA_pressed[2]=(int)(B*255.0f);
			iRGBA_pressed[3]=(int)(A*255.0f);
		}
		virtual float* getPressedItemColorFloat(){
			return fRGBA_pressed;
		}
		virtual void setHoveredItemColor(int R,int G,int B,int A=0){
			iRGBA_hovered[0]=R;
			iRGBA_hovered[1]=G;
			iRGBA_hovered[2]=B;
			iRGBA_hovered[3]=A;
			fRGBA_hovered[0]=R/255.0f;
			fRGBA_hovered[1]=G/255.0f;
			fRGBA_hovered[2]=B/255.0f;
			fRGBA_hovered[3]=A/255.0f;
		}
		virtual int* getHoveredItemColorInt(){
			return iRGBA_hovered;
		}
		virtual void setHoveredItemColor(float R,float G,float B,float A=0.0f){
			fRGBA_hovered[0]=R;
			fRGBA_hovered[1]=G;
			fRGBA_hovered[2]=B;
			fRGBA_hovered[3]=A;
			iRGBA_hovered[0]=(int)(R*255.0f);
			iRGBA_hovered[1]=(int)(G*255.0f);
			iRGBA_hovered[2]=(int)(B*255.0f);
			iRGBA_hovered[3]=(int)(A*255.0f);
		}
		virtual float* getHoveredItemColorFloat(){
			return fRGBA_hovered;
		}
		virtual void setDisabledItemColor(int R,int G,int B,int A=0){
			iRGBA_disabled[0]=R;
			iRGBA_disabled[1]=G;
			iRGBA_disabled[2]=B;
			iRGBA_disabled[3]=A;
			fRGBA_disabled[0]=R/255.0f;
			fRGBA_disabled[1]=G/255.0f;
			fRGBA_disabled[2]=B/255.0f;
			fRGBA_disabled[3]=A/255.0f;
		}
		virtual int* getDisabledItemColorInt(){
			return iRGBA_disabled;
		}
		virtual void setDisabledItemColor(float R,float G,float B,float A=0.0f){
			fRGBA_disabled[0]=R;
			fRGBA_disabled[1]=G;
			fRGBA_disabled[2]=B;
			fRGBA_disabled[3]=A;
			iRGBA_disabled[0]=(int)(R*255.0f);
			iRGBA_disabled[1]=(int)(G*255.0f);
			iRGBA_disabled[2]=(int)(B*255.0f);
			iRGBA_disabled[3]=(int)(A*255.0f);
		}
		virtual float* getDisabledItemColorFloat(){
			return fRGBA_disabled;
		}
		//Height for the dropdown in Combobox. If exceeded, a ScrollBar is shown.
		virtual void setDropdownHeight(int height)=0;
		//Retrieves the height of the dropdown.
		virtual int getDropdownHeight()=0;
		//Visible area for ListBox. If exceeded, a ScrollBar is shown.
		virtual void setViewportBounds(int left,int top,int right,int bottom)=0;
		//Retrieves the visible area of the ListBox.
		virtual RECT getViewportBounds()=0;
		//Sets the final height. All pixels outside of the viewport or dropdown limits will be hidden and accessed only by ScrollBar.
		virtual void setTotalHeight(int height)=0;
		//Retrieves the final height.
		virtual int getTotalHeight()=0;
		//Adds 1 element to the list.
		virtual void add(ListItem t)=0;
		//Adds a vector to the list.
		virtual void addAll(std::vector<ListItem> t)=0;
		//Removes 1 element from the list
		virtual void remove(int index)=0;
		virtual void drawDropdown(std::shared_ptr<D2DHandle>& d2d)=0;
		virtual void useCustomDrawMode(bool useCustomDraw){
			this->useCustomDraw=useCustomDraw;
		}
		virtual bool usesCustomDrawMode(){
			return useCustomDraw;
		}
		std::function<void(std::shared_ptr<D2DHandle>&)> customDraw;
		std::function<void(std::shared_ptr<D2DHandle>&)> customRecreateResources;
	protected:
		bool useCustomDraw;
		RECT viewportbounds;
		int dropdownheight;
		int totalheight;
		int selectedindex;
		ListItem selecteditem;
		float fRGBA_hovered[4];
		int iRGBA_hovered[4];
		float fRGBA_pressed[4];
		int iRGBA_pressed[4];
		float fRGBA_selected[4];
		int iRGBA_selected[4];
		float fRGBA_disabled[4];
		int iRGBA_disabled[4];
	};
	class ComboBox:public WindowBase,public ListBase{
	public:
		ComboBox(){
			dropdownvisible=false;
			states.push_back(WINDOW_STATES::NONE);
			tb=std::shared_ptr<TextBox>(new TextBox());
			dropdown=std::shared_ptr<ArrowButton>(new ArrowButton());
			vScrollBar=std::shared_ptr<ScrollBar>(new ScrollBar());
			vScrollBar->position=0;
			vScrollBar->portions=1;
			vScrollBar->disableHorizontalScrolling();
			vScrollBar->disableVerticalScrolling();
			setTotalHeight(0);
			setDropdownHeight(0);
			setFont(L"Comic Sans MS");
			setTextSize(12.0f);
			setForeground(0.f,0.f,0.f,1.f);
			drawing=new D2DUIDrawableItem(*this,false);
			useCustomDraw=false;
		}
		~ComboBox(){
			tb.reset();
			dropdown.reset();
			vScrollBar.reset();
		}
		std::shared_ptr<TextBox> tb;
		virtual void setTextSize(float px){
			WindowBase::setTextSize(px);
			tb->setTextSize(px);
		}
		virtual void setText(std::wstring text){
			WindowBase::setText(text);
			tb->setText(text);
		}
		virtual void setFont(wchar_t* font){
			WindowBase::setFont(font);
			tb->setFont(font);
		}
		virtual void setEnabled(bool enabled){
			WindowBase::setEnabled(enabled);
			tb->setEnabled(enabled);
			dropdown->setEnabled(enabled);
		}
		virtual void setEditable(bool editable){
			WindowBase::setEditable(editable);
			tb->setEditable(editable);
		}
		virtual void setVisible(bool visible){
			WindowBase::setVisible(visible);
			tb->setVisible(visible);
			dropdown->setVisible(visible);
			drawing->setVisible(visible);
		}
		virtual void setFocus(bool focus){
			WindowBase::setFocus(focus);
			tb->setFocus(focus);
		}
		virtual void setBounds(int left,int top,int right,int bottom){
			WindowBase::setBounds(left,top,right,bottom);
			tb->setBounds(left,top,right-30,bottom);
			dropdown->setBounds(tb->getBounds().right,top,right,bottom);
			vScrollBar->setBounds(getBounds().right-20,getBounds().bottom,getBounds().right,getBounds().bottom+getDropdownHeight());
		}
		virtual void setForeground(int R,int G,int B,int A=255){
			WindowBase::setForeground(R,G,B,A);
			tb->setForeground(R,G,B,A);
		}
		virtual void setForeground(float R,float G,float B,float A=1.0f){
			WindowBase::setForeground(R,G,B,A);
			tb->setForeground(R,G,B,A);
		}
		std::shared_ptr<ArrowButton> dropdown;
		std::shared_ptr<ScrollBar> vScrollBar;
		virtual void setLocale(wchar_t* locale){
			WindowBase::setLocale(locale);
			tb->setLocale(locale);
			dropdown->setLocale(locale);
		}
		virtual void setOpacity(float opacity=1.0f){
			WindowBase::setOpacity(opacity);
			tb->setOpacity(opacity);
			dropdown->setOpacity(opacity);
			vScrollBar->setOpacity(opacity);
		}
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1){
			WindowBase::setPadding(left,top,right,bottom);
			tb->setPadding(left,top,right,bottom);
		}
		virtual void setHorizontalTextAlignment(HorizontalConstants H){
			WindowBase::setHorizontalTextAlignment(H);
			tb->setHorizontalTextAlignment(H);
		}
		virtual void setVerticalTextAlignment(VerticalConstants V){
			WindowBase::setVerticalTextAlignment(V);
			tb->setVerticalTextAlignment(V);
		}
		virtual void setDropdownHeight(int height){
			ComboBox::dropdownheight=height;
			if(getDropdownHeight()<getTotalHeight()){
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
		virtual int getDropdownHeight(){
			return ComboBox::dropdownheight;
		}
		virtual void setTotalHeight(int height){
			ComboBox::totalheight=height;
			if(getDropdownHeight()<getTotalHeight()){
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
		virtual int getTotalHeight(){
			return totalheight;
		}
		virtual void add(ListItem t){
			int itemheight=((int)t.getTextSize())+getTopPadding()+getBottomPadding();
			int top=getBounds().bottom;
			if(list.size()!=0){
				top=list.at(list.size()-1).getBounds().bottom;
			}
			t.setBounds(getBounds().left,top,getBounds().right,top+itemheight);
			list.push_back(t);
			setTotalHeight(getTotalHeight()+itemheight);
		}
		virtual void addAll(std::vector<ListItem> ts){
			for(ListItem& t:ts){
				int itemheight=((int)getTextSize())+getTopPadding()+getBottomPadding();
				int top=getBounds().bottom;
				if(list.size()!=0){
					top=list.at(list.size()-1).getBounds().bottom;
				}
				t.setBounds(getBounds().left,top,getBounds().right,top+itemheight);
				list.push_back(t);
				setTotalHeight(getTotalHeight()+itemheight);
			} 
		}
		virtual void remove(int index){
			list.erase(list.begin()+index);
			int itemheight=((int)list.at(index).getTextSize())+getTopPadding()+getBottomPadding();
			setTotalHeight(getTotalHeight()-itemheight);
		}
		void showDropdown(bool visible){
			this->dropdownvisible=visible;
		}
		bool isDropdownVisible(){
			return dropdownvisible;
		}
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		std::function<void(std::shared_ptr<D2DHandle>& d2d)> customDrawDropdown;
		virtual void drawDropdown(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
	private:
		bool dropdownvisible;
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setHovered(bool hovered){}
		virtual bool isHovered(){return false;}
		virtual void setPressed(bool pressed){}
		virtual bool isPressed(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setViewportBounds(int left,int top,int right,int bottom){}
		virtual RECT getViewportBounds(){return RECT();}
	};
	class ListBox:public WindowBase,public ListBase{
	public:
		ListBox(){
			hScrollBar=std::shared_ptr<ScrollBar>(new ScrollBar);
			hScrollBar->disableHorizontalScrolling();
			hScrollBar->disableVerticalScrolling();
			hScrollBar->position=0;
			hScrollBar->portions=1;
			vScrollBar=std::shared_ptr<ScrollBar>(new ScrollBar);
			vScrollBar->disableVerticalScrolling();
			vScrollBar->disableHorizontalScrolling();
			vScrollBar->position=0;
			vScrollBar->portions=1;
			setTotalHeight(0);
			states.push_back(WINDOW_STATES::NONE);
			drawing=new D2DUIDrawableItem(*this,false);
			useCustomDraw=false;
		}
		~ListBox(){}
		std::shared_ptr<ScrollBar> hScrollBar;
		std::shared_ptr<ScrollBar> vScrollBar;
		virtual void setBounds(int left,int top,int right,int bottom){
			ListBox::bounds.left=left;
			ListBox::bounds.top=top;
			ListBox::bounds.right=right;
			ListBox::bounds.bottom=bottom;
			vScrollBar->setBounds(getBounds().right-20,getBounds().top,getBounds().right,hScrollBar->isHorizontalScrollingEnabled()?getBounds().bottom-20:getBounds().bottom);
			hScrollBar->setBounds(getBounds().left,getBounds().bottom-20,vScrollBar->isVerticalScrollingEnabled()?getBounds().right-20:getBounds().right,getBounds().bottom);
		}
		virtual void setViewportBounds(int left,int top,int right,int bottom){
			ListBox::viewportbounds.left=left;
			ListBox::viewportbounds.top=top;
			ListBox::viewportbounds.right=right;
			ListBox::viewportbounds.bottom=bottom;
			if(IsRectEmpty(&getBounds())){
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
				if(vpheight>height&&height!=0){
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
		virtual RECT getViewportBounds(){
			return viewportbounds;
		}
		virtual void add(ListItem t){
			int itemheight=((int)t.getTextSize())+getTopPadding()+getBottomPadding();
			int top=0;
			if(list.size()!=0){
				top=list.at(list.size()-1).getBounds().bottom;
			}
			if(vScrollBar->isVerticalScrollingEnabled()){
				t.setBounds(0,top,getViewportBounds().right,top+itemheight);
			}
			else{
				t.setBounds(0,top,getViewportBounds().right,top+itemheight);
			}
			list.push_back(t);
			setTotalHeight(getTotalHeight()+itemheight);
		}
		virtual void setTotalHeight(int totalheight){
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
		virtual int getTotalHeight(){
			return totalheight;
		}
		virtual void addAll(std::vector<ListItem> t){
			for(ListItem& t1:t){
				list.push_back(t1);
			}
			int itemheight=((int)getTextSize())+getTopPadding()+getBottomPadding();
			setTotalHeight(getTotalHeight()+(itemheight*t.size()));
		}
		virtual void remove(int index){
			list.erase(list.begin()+index);
		}
		virtual void setVisible(bool visible){
			WindowBase::setVisible(visible);
			drawing->setVisible(visible);
		}
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setDropdownHeight(int height){}
		virtual int getDropdownHeight(){return 0;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
		virtual void setText(std::wstring text){}
		virtual std::wstring getText(){return L"";}
		virtual void setIcon(std::wstring text){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void drawDropdown(std::shared_ptr<D2DHandle>& d2d){}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
	};
	class Slider:public WindowBase{
	public:
		Slider(int minValue=0,int maxValue=0,int value=0,int step=0);
		~Slider(){}
		int value;
		int maxValue;
		int minValue;
		int step;
		void setValue(int value);
		int getValue();
		void setMaximumValue(int maxValue);
		int getMaximumValue();
		void setMinimumValue(int minValue);
		int getMinimumValue();
		void setStep(int step);
		int getStep();
		virtual void setVisible(bool visible){
			WindowBase::setVisible(visible);
			drawing->setVisible(visible);
		}
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setHorizontalTextAlignment(HorizontalConstants H){}
		virtual HorizontalConstants getHorizontalTextAlignment(){return LEFT;}
		virtual void setVerticalTextAlignment(VerticalConstants V){}
		virtual VerticalConstants getVerticalTextAlignment(){return TOP;}
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1){}
		virtual int getTopPadding(){return 0;}
		virtual int getLeftPadding(){return 0;}
		virtual int getRightPadding(){return 0;}
		virtual int getBottomPadding(){return 0;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setTextSize(float px){}
		virtual void setText(std::wstring text){}
		virtual std::wstring getText(){return L"";}
		virtual void setFont(wchar_t* font){}
		virtual wchar_t* getFont(){return L"";}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual float getTextSize(){return 0.f;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
		virtual void setForeground(int R,int G,int B,int A=255){}
		virtual void setForeground(float R,float G,float B,float A=1.0f){}
		virtual int* getForegroundInt(){
			int color[4]={0,0,0,0};
			return color;
		}
		virtual float* getForegroundFloat(){
			float color[4]={0.f,0.f,0.f,0.f};
			return color;
		}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
	};
	class ImageView:public WindowBase{
	public:
		ImageView(wchar_t* file=L"");
		~ImageView(){}
		wchar_t* path;
		void setFile(wchar_t* file);
		wchar_t* getFilePath();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void setVisible(bool visible){
			WindowBase::setVisible(visible);
			drawing->setVisible(visible);
		}
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setText(std::wstring text){}
		virtual std::wstring getText(){return L"";}
		virtual void setEnabled(bool enabled){}
		virtual bool isEnabled(){return false;}
		virtual void setHovered(bool hovered){}
		virtual bool isHovered(){return false;}
		virtual void setPressed(bool pressed){}
		virtual bool isPressed(){return false;}
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setPadding(int left,int top,int right,int bottom){}
		virtual int getLeftPadding(){return -1;}
		virtual int getTopPadding(){return -1;}
		virtual int getRightPadding(){return -1;}
		virtual int getBottomPadding(){return -1;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
		virtual void setHorizontalTextAlignment(HorizontalConstants H){}
		virtual HorizontalConstants getHorizontalTextAlignment(){return LEFT;}
		virtual void setVerticalTextAlignment(VerticalConstants V){}
		virtual VerticalConstants getVerticalTextAlignment(){return TOP;}
		virtual void setFont(wchar_t* font){}
		virtual wchar_t* getFont(){return L"";}
		virtual void setForeground(int R,int G,int B,int A=255){}
		virtual void setForeground(float R,float G,float B,float A=1.0f){}
		virtual int* getForegroundInt(){
			int color[4]={0,0,0,0};
			return color;
		}
		virtual float* getForegroundFloat(){
			float color[4]={0.f,0.f,0.f,0.f};
			return color;
		}
		virtual void setTextSize(float px){}
		virtual float getTextSize(){return 0.f;}
	};
	class GifView:public ImageView{
	public:
		GifView(wchar_t* file): ImageView(file), currentframe(0), loop(false){}
		~GifView(){}
		int getCurrentFrame();
		void setLoop(bool loop);
		bool isLooping();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
	protected:
		unsigned int totalframes;
		std::vector<ComPtr<ID2D1Bitmap>> frame_bmp;
		int currentframe;
		bool loop;
	};
	class OpacityMaskGifView:public GifView{
	public:
		OpacityMaskGifView(wchar_t* imagefile,wchar_t* maskfile): GifView(imagefile), maskfile(maskfile){}
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		wchar_t* getMaskFile();
		void setMaskFile(wchar_t* maskfile);
	private:
		std::vector<ComPtr<ID2D1Bitmap>>bmp_masks;
		ComPtr<ID2D1BitmapBrush> bmp_brush;
		wchar_t* maskfile;
	};
	class ImageButton:public WindowBase{
	public:
		ImageButton(wchar_t* file=L"", std::wstring text=L"");
		ImageButton(wchar_t* enabledfile,wchar_t* disabledfile,wchar_t* pressedfile,wchar_t* hoveredfile,std::wstring text=L"");
		~ImageButton(){}
		wchar_t* enabledpath;
		wchar_t* disabledpath;
		wchar_t* pressedpath;
		wchar_t* hoveredpath;
		void setEnabledFile(wchar_t* file);
		void setDisabledFile(wchar_t* file);
		void setPressedFile(wchar_t* file);
		void setHoveredFile(wchar_t* file);
		virtual void setVisible(bool visible){
			WindowBase::setVisible(visible);
			drawing->setVisible(visible);
		}
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
	};
	class SlotBase{
	public:
		SlotBase(){}
		~SlotBase(){}
		
		virtual void setGameDate(std::wstring date){
			gamedate->setText(date);
		}
		virtual std::wstring getGameDate(){
			return gamedate->getText();
		}
		virtual void setSystemDate(std::wstring date){
			systemdate->setText(date);
		}
		virtual std::wstring getSystemDate(){
			return gamedate->getText();
		}
		virtual void setStoryArc(std::wstring storyarc){
			arc->setText(storyarc);
		}
		virtual std::wstring getStoryArc(){
			return arc->getText();
		}
		virtual void setThumbnail(wchar_t* thumb){
			thumbnail->setFile(thumb);
		}
		virtual wchar_t* getThumbnail(){
			return thumbnail->getFilePath();
		}
		virtual void setSlotNumber(int slotnumber){
			this->slotnumber=slotnumber;
		}
		virtual int getSlotNumber(){
			return slotnumber;
		}
		std::shared_ptr<ImageView> thumbnail;
	protected:
		int slotnumber;
		std::shared_ptr<TextLabel> gamedate;
		std::shared_ptr<TextLabel> systemdate;
		std::shared_ptr<TextLabel> arc;
	};
	class LoadSlot:public WindowBase, public SlotBase{
	public:
		LoadSlot(std::wstring gamedate=L"NO DATA",std::wstring sysdate=L"",std::wstring storyarc=L"",wchar_t* thumb=L"");
		~LoadSlot(){
		}
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual void setHorizontalTextAlignment(HorizontalConstants H);
		virtual void setVerticalTextAlignment(VerticalConstants V);
		virtual void setFont(wchar_t* font);
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.0f);
		virtual void setTextSize(float px);
		virtual void setOpacity(float opacity=1.f);
		virtual void setLocale(wchar_t* locale);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setText(std::wstring text){}
		virtual std::wstring getText(){return L"";}
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setPadding(int left,int top,int right,int bottom){}
		virtual int getLeftPadding(){return -1;}
		virtual int getTopPadding(){return -1;}
		virtual int getRightPadding(){return -1;}
		virtual int getBottomPadding(){return -1;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
	};
	class SaveSlot:public WindowBase, public SlotBase{
	public:
		SaveSlot(std::wstring gamedate=L"NO DATA",std::wstring sysdate=L"",std::wstring storyarc=L"",wchar_t* thumb=L"");
		~SaveSlot(){}
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual void setHorizontalTextAlignment(HorizontalConstants H);
		virtual void setVerticalTextAlignment(VerticalConstants V);
		virtual void setFont(wchar_t* font);
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.0f);
		virtual void setTextSize(float px);
		virtual void setOpacity(float opacity=1.f);
		virtual void setLocale(wchar_t* locale);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setText(std::wstring text){}
		virtual std::wstring getText(){return L"";}
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setPadding(int left,int top,int right,int bottom){}
		virtual int getLeftPadding(){return -1;}
		virtual int getTopPadding(){return -1;}
		virtual int getRightPadding(){return -1;}
		virtual int getBottomPadding(){return -1;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
	};
	typedef enum MSGBoxButtons{
		MSGBOX_OK=1,
		MSGBOX_OKCANCEL=2,
		MSGBOX_YESNO=3,
		MSGBOX_YESNOCANCEL=4
	}MSGBoxButtons;
	typedef enum MSGBoxIcon{
		MSGBOX_INFORMATION=1,
		MSGBOX_ERROR=2,
		MSGBOX_QUESTION=3,
		MSGBOX_WARNING=4
	}MSGBoxIcon;
	class DialogBase{
	public:
		DialogBase(){}
		~DialogBase(){}
		virtual void Show(){
			showing=true;
		}
		virtual void Hide(){
			showing=false;
		}
		virtual bool isShowing(){
			return showing;
		}
		virtual void setModal(bool modal){
			this->modal=modal;
		}
		virtual bool isModal(){
			return modal;
		}
		virtual void SetUserResponse(int userResponse){
			this->userResponse=userResponse;
		}
		virtual int GetUserResponse(){
			return userResponse;
		}
	protected:
		HWND hwnd;
		virtual void reorderComponents(std::shared_ptr<D2DHandle>& d2d)=0;
		int userResponse;
		bool showing,modal;
	};
	class MsgBox:public WindowBase, public DialogBase{
	public:
		MsgBox(HWND parent,bool modal,std::wstring text,std::wstring title,MSGBoxButtons buttons,MSGBoxIcon icon);
		~MsgBox(){
		}
		std::shared_ptr<TextLabel> textContent, textTitle;
		std::shared_ptr<ImageView> msgboxicon;
		virtual void setTextSize(float px);
		virtual void setFont(wchar_t* font);
		virtual void setBackground(int R,int G,int B,int A=255);
		virtual void setBackground(float R,float G,float B,float A=1.f);
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.f);
		virtual void setOpacity(float opacity=1.0f) override;
		virtual void setLocale(wchar_t* locale) override;
		std::shared_ptr<TableRow> contentRow;
		std::shared_ptr<GridLayout> buttonsRow;
		std::shared_ptr<Button> btnOk, btnYes, btnNo, btnCancel;
		virtual void Show();
		virtual void Hide();
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	protected:
		virtual void reorderComponents(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setText(std::wstring text){}
		virtual std::wstring getText(){return L"";}
		virtual void setEnabled(bool enabled){}
		virtual bool isEnabled(){return false;}
		virtual void setHorizontalTextAlignment(HorizontalConstants H){}
		virtual void setVerticalTextAlignment(VerticalConstants V){}
		virtual HorizontalConstants getHorizontalTextAlignment(){return LEFT;}
		virtual VerticalConstants getVerticalTextAlignment(){return TOP;}
		virtual void setPressed(bool pressed){}
		virtual bool isPressed(){return false;}
		virtual void setHovered(bool hovered){}
		virtual bool isHovered(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
		virtual void setVisible(bool visible){}
		virtual bool isVisible(){return false;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		MSGBoxButtons buttons;
		MSGBoxIcon msgicon;
	};
	class InfoBox:public WindowBase, public DialogBase{
	public:
		InfoBox(HWND parent,std::wstring text);
		~InfoBox(){
		}
		std::shared_ptr<TextLabel> textContent;
		virtual void setTextSize(float px);
		virtual void setFont(wchar_t* font);
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.f);
		virtual void setOpacity(float opacity=1.0f) override;
		virtual void setLocale(wchar_t* locale) override;
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		virtual void Show();
		virtual void Hide();
	protected:
		virtual void reorderComponents(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setText(std::wstring text){}
		virtual std::wstring getText(){return L"";}
		virtual void setEnabled(bool enabled){}
		virtual bool isEnabled(){return false;}
		virtual void setHorizontalTextAlignment(HorizontalConstants H){}
		virtual void setVerticalTextAlignment(VerticalConstants V){}
		virtual HorizontalConstants getHorizontalTextAlignment(){return LEFT;}
		virtual VerticalConstants getVerticalTextAlignment(){return TOP;}
		virtual void setPressed(bool pressed){}
		virtual bool isPressed(){return false;}
		virtual void setHovered(bool hovered){}
		virtual bool isHovered(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
		virtual void setVisible(bool visible){}
		virtual bool isVisible(){return false;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
	};
	class PopupNotification:public WindowBase, public DialogBase{
	public:
		PopupNotification(HWND parent,std::wstring text,long duration);
		~PopupNotification(){}
		long duration;
		virtual void setTextSize(float px);
		virtual void setFont(wchar_t* font);
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.f);
		std::shared_ptr<TextLabel> textContent;
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void recreateResources(std::shared_ptr<D2DHandle>& d2d);
		void startPopup();
	protected:
		virtual void reorderComponents(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setText(std::wstring text){}
		virtual std::wstring getText(){return L"";}
		virtual void setEnabled(bool enabled){}
		virtual bool isEnabled(){return false;}
		virtual void setHorizontalTextAlignment(HorizontalConstants H){}
		virtual void setVerticalTextAlignment(VerticalConstants V){}
		virtual HorizontalConstants getHorizontalTextAlignment(){return LEFT;}
		virtual VerticalConstants getVerticalTextAlignment(){return TOP;}
		virtual void setPressed(bool pressed){}
		virtual bool isPressed(){return false;}
		virtual void setHovered(bool hovered){}
		virtual bool isHovered(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setEditable(bool editable){}
		virtual bool isEditable(){return false;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
		virtual void setVisible(bool visible){}
		virtual bool isVisible(){return false;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
	};
}
#endif