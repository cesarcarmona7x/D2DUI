#ifdef XBOX
#endif
#ifdef _WIN32
#ifndef D2DUI_INCLUDED
#define D2DUI_INCLUDED
#include "stdafx.h"
namespace D2DUI{
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
		VISIBLE=8
	}WINDOW_STATES;
	class HorizontalConstants{
	public:
		HorizontalConstants(){}
		~HorizontalConstants(){}
		static const int LEFT=0;
		static const int CENTER_HORIZONTAL=1;
		static const int RIGHT=2;
	};
	class VerticalConstants{
	public:
		VerticalConstants(){}
		~VerticalConstants(){}
		static const int TOP=3;
		static const int CENTER_VERTICAL=4;
		static const int BOTTOM=5;
	};
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
		WindowBase(): tbParent(*(ToggleGroup*)NULL), rbParent(*(RadioGroup*)NULL), parent(*(LayoutBase*)NULL){}
		WindowBase(wchar_t* text): text(text), tbParent(*(ToggleGroup*)NULL), rbParent(*(RadioGroup*)NULL), parent(*(LayoutBase*)NULL){}
		WindowBase(int c,wchar_t* path): path(path), rbParent(*(RadioGroup*)NULL), tbParent(*(ToggleGroup*)NULL), parent(*(LayoutBase*)NULL){}
		WindowBase(wchar_t* text,wchar_t* icon): text(text), icon(icon), rbParent(*(RadioGroup*)NULL), tbParent(*(ToggleGroup*)NULL), parent(*(LayoutBase*)NULL){}
		WindowBase(bool checked,wchar_t* text): text(text), rbParent(*(RadioGroup*)NULL), tbParent(*(ToggleGroup*)NULL), parent(*(LayoutBase*)NULL){}
		WindowBase(RadioGroup* rg,bool checked,wchar_t* text): rbParent(*rg), text(text), tbParent(*(ToggleGroup*)NULL), parent(*(LayoutBase*)NULL){}
		WindowBase(ToggleGroup* tg,bool checked, wchar_t* text,wchar_t* icon): tbParent(*tg), text(text), icon(icon), rbParent(*(RadioGroup*)NULL), parent(*(LayoutBase*)NULL){}
		~WindowBase(){}
		wchar_t* wndId;
		wchar_t* locale;
		int index;
		float opacity;
		float fRGBA_bg[4];
		int iRGBA_bg[4];
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
		RadioGroup& rbParent;
		ToggleGroup& tbParent;
		wchar_t* path;
		wchar_t* text;
		wchar_t* icon;
		int height;
		int width;
		int row,col;
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
		virtual void setParentLayout(LayoutBase& layout);
		virtual LayoutBase& getParentLayout(){
			return parent;
		}
		//Sets the text for the window.
		virtual void setText(wchar_t* text)=0;
		virtual wchar_t* getText()=0;
		//Sets the font for the window.
		virtual void setFont(wchar_t* font)=0;
		//Retrieves the font being used by the window as a wchar_t* value.
		virtual wchar_t* getFont()=0;
		//Defines the coordinates of the window.
		virtual void setBounds(int left,int top,int right,int bottom)=0;
		//Retrieves the bounding rectangle for the window.
		virtual RECT getBounds()=0;
		//Sets an image file as an icon to the left of the button.
		virtual void setIcon(wchar_t* icon)=0;
		//Retrieves the file used as icon for the button, if any.
		virtual wchar_t* getIcon()=0;
		//Sets the text's horizontal alignment.
		virtual void setHorizontalTextAlignment(const int h)=0;
		//Retrieves the horizontal text alignment as an int.
		virtual int getHorizontalTextAlignment()=0;
		//Set the text's vertical alignment.
		virtual void setVerticalTextAlignment(const int v)=0;
		//Retrieves the vertical text alignment as an int.
		virtual int getVerticalTextAlignment()=0;
		//Defines the colour of the text. Values go from 0.0 to 1.0
		virtual void setForeground(float R,float G,float B,float A=1.0f)=0;
		//Defines the colour of the text. Values go from 0 to 255.
		virtual void setForeground(int R,int G,int B,int A=255)=0;
		//Retrieves the foreground's RGBA values, as an int array.
		virtual int* getForegroundInt()=0;
		//Retrieves the foreground's RGBA values, as a float array.
		virtual float* getForegroundFloat()=0;
		//Sets the size of the text, in floating point pixels
		virtual void setTextSize(float px)=0;
		//Retrieves the text size, as a float.
		virtual float getTextSize()=0;
		/* Sets the margin for the window to write text.
		If the window has an icon, it will be placed according the padding,
		and the text will be placed after the right margin of the button.*/
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1)=0;
		//Enables or disables a window.
		virtual void setEnabled(bool enabled)=0;
		//Retrieves whether the window is enabled or not.
		virtual bool isEnabled()=0;
		//Displays mouse-over effects.
		virtual void setHovered(bool hovered)=0;
		//Retrieves whether the mouse is over the window or not.
		virtual bool isHovered()=0;
		//Displays mouse click effects.
		virtual void setPressed(bool pressed)=0;
		//Retrieves whether the window is being pressed or not.
		virtual bool isPressed()=0;
		//Selects the current button from the group.
		virtual void setSelected(bool selected)=0;
		//Retrieves if the button is the one being selected.
		virtual bool isSelected()=0;
		//Allows you (or not) to write over a TextBox window.
		virtual void setEditable(bool editable)=0;
		//Retrieves whether the TextBox's text can be manipulated.
		virtual bool isEditable()=0;
		//Enables a TextBox to write over it.
		virtual void setFocus(bool focus)=0;
		//Retrieves whether the TextBox is selected for writing.
		virtual bool hasFocus()=0;
		//Retrieves the left margin of the window, as an int.
		virtual int getLeftPadding()=0;
		//Retrieves the top margin of the window, as an int.
		virtual int getTopPadding()=0;
		//Retrieves the right margin of the window, as an int.
		virtual int getRightPadding()=0;
		//Retrieves the bottom margin of the window, as an int.
		virtual int getBottomPadding()=0;
		//Displays or hides the window.
		virtual void setVisible(bool visible)=0;
		//Retrieves whether the window is showing or not.
		virtual bool isVisible()=0;
		//Checks or unchecks a CheckBox window.
		virtual void setChecked(bool checked)=0;
		//Retrieves whether a CheckBox is checked or not.
		virtual bool isChecked()=0;
		//Draws the contents of the window over a Direct2D render target
		virtual void draw(std::shared_ptr<D2DHandle>& d2d)=0;
		bool operator== (WindowBase& other){
			if(this->wndId==NULL||other.wndId==NULL){
				return false;
			}
			else{
				const char* type=typeid(this).name();
				return (wcscmp(wndId,other.wndId)==0);
			}
		}
	protected:
		LayoutBase& parent;
	};
	class ScrollBar:public WindowBase{
	public:
		ScrollBar(){
			states.push_back(NONE);
			portions=1;
			position=0;
		}
		~ScrollBar(){}
		enum Orientation{
			HORIZONTAL=0,
			VERTICAL=1
		};
		RECT bounds;
		int thumbwidth;
		std::vector<D2DUI::WINDOW_STATES> states;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int hAlignment;
		int vAlignment;
		float fRGBA[4];
		int iRGBA[4];
		wchar_t* text;
		wchar_t* font;
		wchar_t* icon;
		float textsize;
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
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setPressed(bool pressed);
		virtual bool isPressed();
		virtual void setHovered(bool hovered);
		virtual bool isHovered();
		void setOrientation(Orientation o);
		virtual void setVisible(bool visible);
		virtual bool isVisible();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setText(wchar_t* text){}
		virtual wchar_t* getText(){return L"";}
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
		virtual void setHorizontalTextAlignment(const int H){}
		virtual void setVerticalTextAlignment(const int V){}
		virtual int getHorizontalTextAlignment(){return 0;}
		virtual int getVerticalTextAlignment(){return 0;}
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
		LayoutBase(): parent(*(LayoutBase*)NULL){}
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
		RECT bounds;
		int width;
		int height;
		int row;
		int col;
		HGravity hg;
		VGravity vg;
		wchar_t* layId;
		int index;
		int iRGBA[4];
		float fRGBA[4];
		float radius_x;
		float radius_y;
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
		virtual void add(WindowBase& window)=0;
		virtual void add(WindowBase& window,int row,int col)=0;
		virtual void add(LayoutBase& layout)=0;
		virtual void add(LayoutBase& layout,int row,int col)=0;
		virtual void remove(wchar_t* id)=0;
		virtual void remove(int row,int col)=0;
		virtual void setRadius(float x,float y=-1)=0;
		virtual float getXRadius()=0;
		virtual float getYRadius()=0;
		virtual void setBounds(int left,int top,int right,int bottom)=0;
		virtual void setOrientation(Orientation o)=0;
		virtual Orientation getOrientation()=0;
		virtual void setBackground(int R=0,int G=0,int B=0,int A=0)=0;
		virtual void setBackground(float R=0.f,float G=0.f,float B=0.f,float A=0.f)=0;
		virtual RECT getBounds()=0;
		virtual void setViewportBounds(int left,int top,int right,int bottom)=0;
		virtual RECT getViewportBounds()=0;
		virtual void setScrollbarVisible(bool visible)=0;
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1)=0;
		virtual int getLeftPadding()=0;
		virtual int getTopPadding()=0;
		virtual int getRightPadding()=0;
		virtual int getBottomPadding()=0;
		Border leftBorder;
		Border topBorder;
		Border rightBorder;
		Border bottomBorder;
		Orientation o;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		std::vector<std::reference_wrapper<WindowBase>>windows;
		std::vector<std::reference_wrapper<LayoutBase>>layouts;
		virtual void setBorder(Border border)=0;
		virtual void setLeftBorder(Border border)=0;
		virtual void setTopBorder(Border border)=0;
		virtual void setRightBorder(Border border)=0;
		virtual void setBottomBorder(Border border)=0;
		virtual void setGravity(HGravity h,VGravity v)=0;
		virtual Border getLeftBorder()=0;
		virtual Border getTopBorder()=0;
		virtual Border getRightBorder()=0;
		virtual Border getBottomBorder()=0;
		bool operator== (LayoutBase& other){
			if(this->layId==NULL||other.layId==NULL){
				return false;
			}
			else{
				return wcscmp(this->layId,other.layId)==0;
			}
		}
		LayoutBase& operator= (LayoutBase& other){
			return other;
		}
		virtual void setParentLayout(LayoutBase& parent){
			this->parent=parent;
		}
		virtual void draw(std::shared_ptr<D2DHandle>& d2d)=0;
	protected:
		LayoutBase& parent;
	};
	class LinearLayout:public LayoutBase{
	public:
		LinearLayout(Orientation o=VERTICAL);
		~LinearLayout(){}
		virtual void add(WindowBase& t);
		virtual void add(LayoutBase& t);
		virtual void remove(wchar_t* id);
		virtual void setBackground(int R=0,int G=0,int B=0,int A=0);
		virtual void setBackground(float R=0.f,float G=0.f,float B=0.f,float A=0.f);
		virtual void setOrientation(Orientation o);
		virtual Orientation getOrientation();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void setRadius(float x,float y=-1);
		virtual float getXRadius();
		virtual float getYRadius();
		virtual void setBorder(Border b);
		virtual void setLeftBorder(Border b);
		virtual void setRightBorder(Border b);
		virtual void setTopBorder(Border b);
		virtual void setBottomBorder(Border b);
		virtual Border getLeftBorder();
		virtual Border getTopBorder();
		virtual Border getBottomBorder();
		virtual Border getRightBorder();
		virtual void reorderComponents();
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
		virtual void setGravity(HGravity h,VGravity v);
		virtual void setRadius(float x,float y=-1);
		virtual float getXRadius();
		virtual float getYRadius();
		virtual void setBorder(Border b);
		virtual void setLeftBorder(Border b);
		virtual void setRightBorder(Border b);
		virtual void setTopBorder(Border b);
		virtual void setBottomBorder(Border b);
		virtual Border getLeftBorder();
		virtual Border getTopBorder();
		virtual Border getRightBorder();
		virtual Border getBottomBorder();
		virtual void setBackground(int R,int G,int B,int A=0);
		virtual void setBackground(float R,float G,float B,float A=0.0f);
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void reorderComponents();
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
		virtual void setBackground(int R,int G,int B,int A=0);
		virtual void setBackground(float R,float G,float B,float A=0.0f);
		virtual void setBorder(Border b);
		virtual void setLeftBorder(Border b);
		virtual void setTopBorder(Border b);
		virtual void setRightBorder(Border b);
		virtual void setBottomBorder(Border b);
		virtual Border getLeftBorder();
		virtual Border getTopBorder();
		virtual Border getRightBorder();
		virtual Border getBottomBorder();
		virtual void setGravity(HGravity h,VGravity v);
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void reorderComponents();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
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
		TableLayout(){}
		~TableLayout(){}
		std::vector<std::reference_wrapper<TableRow>> rows;
		virtual void add(TableRow& row);
		virtual void remove(wchar_t* id);
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void setRadius(float x,float y);
		virtual float getXRadius();
		virtual float getYRadius();
		virtual void setGravity(HGravity hg,VGravity vg);
		virtual void setBorder(Border b);
		virtual void setLeftBorder(Border b);
		virtual Border getLeftBorder();
		virtual void setTopBorder(Border b);
		virtual Border getTopBorder();
		virtual void setRightBorder(Border b);
		virtual Border getRightBorder();
		virtual void setBottomBorder(Border b);
		virtual Border getBottomBorder();
		virtual void setBackground(int R,int G,int B,int A=0);
		virtual void setBackground(float R,float G,float B,float A=0.0f);
		virtual void reorderComponents();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
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
		std::vector<std::reference_wrapper<WindowBase>>windows;
		std::vector<std::reference_wrapper<LayoutBase>>layouts;
		virtual void add(WindowBase& window,WindowBase& left=*((WindowBase*)NULL),WindowBase& top=*((WindowBase*)NULL),WindowBase& right=*((WindowBase*)NULL),WindowBase& bottom=*(WindowBase*)NULL);
		virtual void remove(wchar_t* id);
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		RECT bounds;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
	private:
		virtual void setViewportBounds(int left,int top,int right,int bottom){}
		virtual void setScrollbarVisible(bool visible){}
		virtual void setGravity(HGravity h,VGravity v){}
	};
	class RadioButton:public WindowBase{
	public:
		RadioButton(RadioGroup& parent,bool selected=false,wchar_t* text=L"");
		~RadioButton(){}
		wchar_t* tag;
		RECT bounds;
		RadioGroup& parent;
		std::vector<D2DUI::WINDOW_STATES> states;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int hAlignment;
		int vAlignment;
		float fRGBA[4];
		int iRGBA[4];
		wchar_t* text;
		wchar_t* font;
		wchar_t* icon;
		float textsize;
		void setTag(wchar_t* tag=L"nulltag");
		wchar_t* getTag();
		void setParent(RadioGroup& rg);
		void removeParent(RadioGroup& rg);
		int rbIndex;
		RadioGroup& getParent();
		void setRBIndex(int index);
		int getRBIndex();
		virtual void setTextSize(float px);
		virtual float getTextSize();
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.0f);
		virtual float* getForegroundFloat();
		virtual int* getForegroundInt();
		virtual void setSelected(bool check);
		virtual bool isSelected();
		virtual wchar_t* getText();
		virtual void setText(wchar_t* text);
		virtual void setFont(wchar_t* font);
		virtual wchar_t* getFont();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setVisible(bool visible);
		virtual bool isVisible();
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual void setEnabled(bool enabled);
		virtual bool isEnabled();
		virtual void setHovered(bool hovered);
		virtual bool isHovered();
		virtual void setPressed(bool pressed);
		virtual bool isPressed();
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void setHorizontalTextAlignment(const int h);
		virtual int getHorizontalTextAlignment();
		virtual void setVerticalTextAlignment(const int v);
		virtual int getVerticalTextAlignment();
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
		int selectedindex;
	};
	class ToggleButton:public WindowBase{
	public:
		ToggleButton(ToggleGroup& parent,bool selected=false,wchar_t* text=L"",wchar_t* icon=L"");
		~ToggleButton(){}
		void setIcon(wchar_t* icon);
		wchar_t* getIcon();
		RECT bounds;
		std::vector<D2DUI::WINDOW_STATES> states;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int hAlignment;
		int vAlignment;
		float fRGBA[4];
		int iRGBA[4];
		wchar_t* text;
		wchar_t* font;
		wchar_t* icon;
		float textsize;
		ToggleGroup& parent;
		void setParent(ToggleGroup& rg);
		void removeParent(ToggleGroup& rg);
		virtual void setVisible(bool visible);
		virtual bool isVisible();
		virtual void setFont(wchar_t* font);
		virtual wchar_t* getFont();
		void setTBIndex(int index);
		int getTBIndex();
		int tbIndex;
		ToggleGroup& getParent();
		virtual void setSelected(bool check);
		virtual bool isSelected();
		virtual void setTextSize(float px);
		virtual float getTextSize();
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.0f);
		virtual float* getForegroundFloat();
		virtual int* getForegroundInt();
		wchar_t* getText();
		virtual void setText(wchar_t* text);
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setPadding(int left,int top,int right=0,int bottom=0);
		virtual void setEnabled(bool enabled);
		virtual bool isEnabled();
		virtual void setHovered(bool hovered);
		virtual bool isHovered();
		virtual void setPressed(bool pressed);
		virtual bool isPressed();
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void setHorizontalTextAlignment(const int h);
		virtual int getHorizontalTextAlignment();
		virtual void setVerticalTextAlignment(const int v);
		virtual int getVerticalTextAlignment();
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
		int selectedindex;
		void setSelectedIndex(int index);
		int getSelectedIndex();
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
		TextLabel(wchar_t* text=L"");
		~TextLabel(){}
		RECT bounds;
		std::vector<D2DUI::WINDOW_STATES> states;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int hAlignment;
		int vAlignment;
		float fRGBA[4];
		int iRGBA[4];
		wchar_t* text;
		wchar_t* font;
		wchar_t* icon;
		float textsize;
		virtual void setTextSize(float px);
		virtual float getTextSize();
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.0f);
		virtual float* getForegroundFloat();
		virtual int* getForegroundInt();
		virtual void setText(wchar_t* text);
		virtual wchar_t* getText();
		virtual void setFont(wchar_t* font);
		virtual wchar_t* getFont();
		virtual void setVisible(bool visible);
		virtual bool isVisible();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setHorizontalTextAlignment(const int h);
		virtual int getHorizontalTextAlignment();
		virtual void setVerticalTextAlignment(const int v);
		virtual int getVerticalTextAlignment();
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
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
		TextBox(wchar_t* text=L"");
		~TextBox(){}
		RECT bounds;
		std::vector<D2DUI::WINDOW_STATES> states;
		int caretPos;
		BOOL trail,inside;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int hAlignment;
		int vAlignment;
		float fRGBA[4];
		int iRGBA[4];
		ComPtr<IDWriteTextLayout> textlayout;
		RECT caretRect;
		wchar_t* text;
		wchar_t* font;
		wchar_t* icon;
		float textsize;
		virtual void setTextSize(float px);
		virtual float getTextSize();
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.0f);
		virtual float* getForegroundFloat();
		virtual int* getForegroundInt();
		virtual wchar_t* getText();
		virtual void setText(wchar_t* text);
		virtual void setFont(wchar_t* font);
		virtual wchar_t* getFont();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setHorizontalTextAlignment(const int h);
		virtual int getHorizontalTextAlignment();
		virtual void setVerticalTextAlignment(const int v);
		virtual int getVerticalTextAlignment();
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual void setVisible(bool visible);
		virtual bool isVisible();
		virtual void setEnabled(bool enabled);
		virtual bool isEnabled();
		virtual void setEditable(bool editable);
		virtual bool isEditable();
		virtual void setFocus(bool focus);
		virtual bool hasFocus();
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
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
		Button(wchar_t* text=L"");
		Button(wchar_t* text,wchar_t* icon=L"");
		~Button(){}
		RECT bounds;
		std::vector<D2DUI::WINDOW_STATES> states;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int hAlignment;
		int vAlignment;
		float fRGBA[4];
		int iRGBA[4];
		wchar_t* text;
		wchar_t* font;
		wchar_t* icon;
		float textsize;
		virtual void setTextSize(float px);
		virtual float getTextSize();
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.0f);
		virtual float* getForegroundFloat();
		virtual int* getForegroundInt();
		virtual wchar_t* getText();
		virtual void setText(wchar_t* text);
		virtual void setFont(wchar_t* font);
		virtual wchar_t* getFont();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setIcon(wchar_t* icon);
		virtual wchar_t* getIcon();
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual void setVisible(bool visible);
		virtual bool isVisible();
		virtual void setEnabled(bool enabled);
		virtual bool isEnabled();
		virtual void setHovered(bool hovered);
		virtual bool isHovered();
		virtual void setPressed(bool pressed);
		virtual bool isPressed();
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void setHorizontalTextAlignment(const int h);
		virtual int getHorizontalTextAlignment();
		virtual void setVerticalTextAlignment(const int v);
		virtual int getVerticalTextAlignment();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
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
	private:
		virtual void setHorizontalTextAlignment(const int H) override{}
		virtual void setVerticalTextAlignment(const int V) override{}
		virtual int getHorizontalTextAlignment() override{return 0;}
		virtual int getVerticalTextAlignment() override{return 0;}
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1) override{}
		virtual int getLeftPadding() override{return 0;}
		virtual int getTopPadding() override{return 0;}
		virtual int getRightPadding() override{return 0;}
		virtual int getBottomPadding() override{return 0;}
		virtual wchar_t* getText() override{return L"";}
		virtual void setText(wchar_t* text) override{}
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
		DialogueBox(wchar_t* text=L"");
		~DialogueBox(){}
		int ibgRGBA[4];
		float fbgRGBA[4];
		wchar_t* decorationfile;
		RECT decorationbounds;
		float decorationopacity;
		bool shadowenabled;
		int showedcharacters;
		DIALOGUEBOX_DECORATION_LEVEL decorationlevel;
		void setBackground(int R,int G,int B,int A=0);
		void setBackground(float R,float G,float B,float A=0.0f);
		int* getBackgroundInt();
		float* getBackgroundFloat();
		void setDecoration(wchar_t* file,DIALOGUEBOX_DECORATION_LEVEL decorationlevel=DECORATIONATSAMELEVELDIALOGUEBOX,float opacity=1.0f);
		wchar_t* getDecoration();
		DIALOGUEBOX_DECORATION_LEVEL getDecorationLevel();
		void setDecorationBounds(int left,int top,int right,int bottom);
		float getDecorationOpacity();
		RECT getDecorationBounds();
		void setTextShadow(bool shadow);
		bool hasTextShadow();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d) override;
	private:
	};
	class Spinner:public WindowBase{
	public:
		Spinner(int minValue=0,int maxValue=0,int value=0);
		~Spinner(){}
		int maxValue;
		int minValue;
		int value;
		std::vector<D2DUI::WINDOW_STATES>states;
		RECT bounds;
		int iRGBA[4];
		float fRGBA[4];
		std::shared_ptr<ArrowButton> up;
		std::shared_ptr<ArrowButton> down;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int vAlignment;
		int hAlignment;
		float textsize;
		wchar_t* font;
		void setValue(int value);
		void setMinimumValue(int minValue);
		void setMaximumValue(int maxValue);
		int getValue();
		int getMaximumValue();
		int getMinimumValue();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setVisible(bool visible);
		virtual bool isVisible();
		virtual void setEnabled(bool enabled);
		virtual bool isEnabled();
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void setHorizontalTextAlignment(const int H);
		virtual int getHorizontalTextAlignment();
		virtual void setVerticalTextAlignment(const int V);
		virtual int getVerticalTextAlignment();
		virtual void setEditable(bool editable);
		virtual bool isEditable();
		virtual void setFocus(bool focus);
		virtual bool hasFocus();
		virtual void setPressed(bool pressed);
		virtual bool isPressed();
		virtual void setHovered(bool hovered);
		virtual bool isHovered();
		virtual void setFont(wchar_t* font);
		virtual wchar_t* getFont();
		virtual void setTextSize(float px);
		virtual float getTextSize();
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual int* getForegroundInt();
		virtual void setForeground(float R,float G,float B,float A=1.0f);
		virtual float* getForegroundFloat();
		virtual void setOpacity(float opacity=1.0f) override;
		virtual void setLocale(wchar_t* locale) override;
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	protected:
		std::shared_ptr<TextBox> valuemodifier;
	private:
		virtual void setChecked(bool checked){}
		virtual bool isChecked(){return false;}
		virtual void setSelected(bool selected){}
		virtual bool isSelected(){return false;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setText(wchar_t* text){}
		virtual wchar_t* getText(){return L"";}
	};
	class CheckBox:public WindowBase{
	public:
		CheckBox(bool checked=true,wchar_t* text=L"");
		~CheckBox(){}
		RECT bounds;
		std::vector<D2DUI::WINDOW_STATES> states;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int hAlignment;
		int vAlignment;
		float fRGBA[4];
		int iRGBA[4];
		wchar_t* text;
		wchar_t* font;
		wchar_t* icon;
		float textsize;
		virtual void setChecked(bool check);
		virtual bool isChecked();
		virtual void setTextSize(float px);
		virtual float getTextSize();
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.0f);
		virtual float* getForegroundFloat();
		virtual int* getForegroundInt();
		virtual wchar_t* getText();
		virtual void setText(wchar_t* text);
		virtual void setFont(wchar_t* font);
		virtual wchar_t* getFont();
		virtual void setVisible(bool visible);
		virtual bool isVisible();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual void setEnabled(bool enabled);
		virtual bool isEnabled();
		virtual void setHovered(bool hovered);
		virtual bool isHovered();
		virtual void setPressed(bool pressed);
		virtual bool isPressed();
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void setHorizontalTextAlignment(const int h);
		virtual int getHorizontalTextAlignment();
		virtual void setVerticalTextAlignment(const int v);
		virtual int getVerticalTextAlignment();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
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
	template<class T> class ListItem{
	public:
		ListItem(){
			states.push_back(NONE);
		}
		~ListItem(){
		}
		std::vector<D2DUI::WINDOW_STATES> states;
		T t;
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
		T& getData();
		bool operator== (const ListItem<T>& other) const{
			wchar_t* tag1=new wchar_t[wcslen(this->tag)];
			wcscpy(tag1,this->tag);
			wchar_t* tag2=new wchar_t[wcslen(other.tag)];
			wcscpy(tag2,other.tag);
			return wcscmp(tag1,tag2)==0;
		}
	};
	template<class T> class ListBase{
	public:
		ListBase(){}
		~ListBase(){}
		RECT viewportbounds;
		int dropdownheight;
		int totalheight;
		virtual T& getSelectedItem()=0;
		virtual void setSelectedItem(T& t)=0;
		virtual void setSelectedIndex(int index)=0;
		virtual int getSelectedIndex()=0;
		virtual void setSelectedItemColor(int R,int G,int B,int A=0)=0;
		virtual int* getSelectedItemColorInt()=0;
		virtual void setSelectedItemColor(float R,float G,float B,float A=0.0f)=0;
		virtual float* getSelectedItemColorFloat()=0;
		virtual void setPressedItemColor(int R,int G,int B,int A=0)=0;
		virtual int* getPressedItemColorInt()=0;
		virtual void setPressedItemColor(float R,float G,float B,float A=0.0f)=0;
		virtual float* getPressedItemColorFloat()=0;
		virtual void setHoveredItemColor(int R,int G,int B,int A=0)=0;
		virtual int* getHoveredItemColorInt()=0;
		virtual void setHoveredItemColor(float R,float G,float B,float A=0.0f)=0;
		virtual float* getHoveredItemColorFloat()=0;
		virtual void setDisabledItemColor(int R,int G,int B,int A=0)=0;
		virtual int* getDisabledItemColorInt()=0;
		virtual void setDisabledItemColor(float R,float G,float B,float A=0.0f)=0;
		virtual float* getDisabledItemColorFloat()=0;
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
		virtual void add(T t)=0;
		//Adds a vector to the list.
		virtual void addAll(std::vector<T> t)=0;
		virtual void remove(int index)=0;
		virtual void drawDropdown(std::shared_ptr<D2DHandle>& d2d)=0;
	};
	template<class T> class ComboBox:public WindowBase,public ListBase<T>{
	public:
		ComboBox(){
			states.push_back(NONE);
			tb=std::shared_ptr<TextBox>(new TextBox());
			dropdown=std::shared_ptr<ArrowButton>(new ArrowButton());
			hScrollBar=std::shared_ptr<ScrollBar>(new ScrollBar());
			hScrollBar->disableVerticalScrolling();
			hScrollBar->disableHorizontalScrolling();
			vScrollBar=std::shared_ptr<ScrollBar>(new ScrollBar());
			vScrollBar->position=0;
			vScrollBar->portions=1;
			vScrollBar->disableHorizontalScrolling();
			vScrollBar->disableVerticalScrolling();
			setTotalHeight(0);
			setDropdownHeight(0);
			setFont(L"Microsoft Sans Serif");
			setTextSize(12.0f);
			setForeground(0.f,0.f,0.f,1.f);
		}
		~ComboBox(){
			tb.reset();
			dropdown.reset();
			vScrollBar.reset();
			hScrollBar.reset();
		}
		float fRGBA_hovered[4];
		int iRGBA_hovered[4];
		float fRGBA_pressed[4];
		int iRGBA_pressed[4];
		float fRGBA_selected[4];
		int iRGBA_selected[4];
		float fRGBA_disabled[4];
		int iRGBA_disabled[4];
		RECT bounds;
		std::function<void()> onClick;
		std::function<void()> onItemSelected;
		std::function<void()> onItemPressed;
		std::function<void()> onItemHovered;
		std::function<void()> onItemEnabled;
		std::vector<D2DUI::WINDOW_STATES> states;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int hAlignment;
		int vAlignment;
		float fRGBA[4];
		int iRGBA[4];
		wchar_t* text;
		wchar_t* font;
		wchar_t* icon;
		float textsize;
		std::shared_ptr<TextBox> tb;
		virtual void setTextSize(float px);
		virtual float getTextSize();
		virtual void setText(wchar_t* text);
		virtual wchar_t* getText();
		virtual void setFont(wchar_t* font);
		virtual wchar_t* getFont();
		virtual void setEnabled(bool enabled);
		virtual bool isEnabled();
		virtual void setEditable(bool editable);
		virtual bool isEditable();
		virtual void setVisible(bool visible);
		virtual bool isVisible();
		virtual void setFocus(bool focus);
		virtual bool hasFocus();
		virtual void setSelectedItemColor(int R,int G,int B,int A=0);
		virtual int* getSelectedItemColorInt();
		virtual void setSelectedItemColor(float R,float G,float B,float A=0.0f);
		virtual float* getSelectedItemColorFloat();
		virtual void setPressedItemColor(int R,int G,int B,int A=0);
		virtual int* getPressedItemColorInt();
		virtual void setPressedItemColor(float R,float G,float B,float A=0.0f);
		virtual float* getPressedItemColorFloat();
		virtual void setHoveredItemColor(int R,int G,int B,int A=0);
		virtual int* getHoveredItemColorInt();
		virtual void setHoveredItemColor(float R,float G,float B,float A=0.0f);
		virtual float* getHoveredItemColorFloat();
		virtual void setDisabledItemColor(int R,int G,int B,int A=0);
		virtual int* getDisabledItemColorInt();
		virtual void setDisabledItemColor(float R,float G,float B,float A=0.0f);
		virtual float* getDisabledItemColorFloat();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.0f);
		virtual float* getForegroundFloat();
		virtual int* getForegroundInt();
		std::shared_ptr<ArrowButton> dropdown;
		std::shared_ptr<ScrollBar> hScrollBar;
		std::shared_ptr<ScrollBar> vScrollBar;
		std::vector<T> list;
		virtual void setLocale(wchar_t* locale) override;
		virtual void setOpacity(float opacity=1.0f) override;
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void setHorizontalTextAlignment(const int H);
		virtual int getHorizontalTextAlignment();
		virtual void setVerticalTextAlignment(const int V);
		virtual int getVerticalTextAlignment();
		virtual void setSelectedItem(T& t);
		virtual T& getSelectedItem();
		virtual void setSelectedIndex(int index);
		virtual void setDropdownHeight(int height);
		virtual int getDropdownHeight();
		virtual int getSelectedIndex();
		virtual void setTotalHeight(int height);
		virtual int getTotalHeight();
		virtual void add(T t);
		virtual void addAll(std::vector<T> t);
		virtual void remove(int index);
		int index;
		T selecteditem;
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
		virtual void drawDropdown(std::shared_ptr<D2DHandle>& d2d);
		ComboBox<T>& operator= (ComboBox<T>& other){
			return other;
		}
	private:
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
	template<class T> class ListBox:public WindowBase,public ListBase<T>{
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
			states.push_back(NONE);
		}
		~ListBox(){}
		RECT bounds;
		std::vector<D2DUI::WINDOW_STATES> states;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int hAlignment;
		int vAlignment;
		float fRGBA[4];
		int iRGBA[4];
		float fRGBA_hovered[4];
		int iRGBA_hovered[4];
		float fRGBA_pressed[4];
		int iRGBA_pressed[4];
		float fRGBA_selected[4];
		int iRGBA_selected[4];
		float fRGBA_disabled[4];
		int iRGBA_disabled[4];
		wchar_t* text;
		wchar_t* font;
		wchar_t* icon;
		float textsize;
		std::shared_ptr<ScrollBar> hScrollBar;
		std::shared_ptr<ScrollBar> vScrollBar;
		std::vector<T> list;
		T selecteditem;
		virtual void setFont(wchar_t* font);
		virtual wchar_t* getFont();
		virtual void setTextSize(float px);
		virtual float getTextSize();
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setEnabled(bool enabled);
		virtual bool isEnabled();
		virtual void setHovered(bool hovered);
		virtual bool isHovered();
		virtual void setPressed(bool pressed);
		virtual bool isPressed();
		virtual void setVisible(bool visible);
		virtual bool isVisible();
		virtual void setHorizontalTextAlignment(const int H);
		virtual int getHorizontalTextAlignment();
		virtual void setVerticalTextAlignment(const int V);
		virtual int getVerticalTextAlignment();
		virtual void setSelectedItem(T& t);
		virtual T& getSelectedItem();
		virtual void setPressedItemColor(int R,int G,int B,int A=0);
		virtual void setPressedItemColor(float R,float G,float B,float A=0.0f);
		virtual int* getPressedItemColorInt();
		virtual float* getPressedItemColorFloat();
		virtual void setHoveredItemColor(int R,int G,int B,int A=0);
		virtual void setHoveredItemColor(float R,float G,float B,float A=0.0f);
		virtual int* getHoveredItemColorInt();
		virtual float* getHoveredItemColorFloat();
		virtual void setDisabledItemColor(int R,int G,int B,int A=0);
		virtual void setDisabledItemColor(float R,float G,float B,float A=0.0f);
		virtual int* getDisabledItemColorInt();
		virtual float* getDisabledItemColorFloat();
		virtual void setSelectedItemColor(int R,int G,int B,int A=0);
		virtual void setSelectedItemColor(float R,float G,float B,float A=0.0f);
		virtual int* getSelectedItemColorInt();
		virtual float* getSelectedItemColorFloat();
		virtual void setSelectedIndex(int index);
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.0f);
		virtual int* getForegroundInt();
		virtual float* getForegroundFloat();
		virtual int getSelectedIndex();
		virtual void setViewportBounds(int left,int top,int right,int bottom);
		virtual RECT getViewportBounds();
		virtual void add(T t);
		virtual void setTotalHeight(int height);
		virtual int getTotalHeight();
		virtual void addAll(std::vector<T> t);
		virtual void remove(int index);
		int index;
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setDropdownHeight(int height){}
		virtual int getDropdownHeight(){return 0;}
		virtual void setFocus(bool focus){}
		virtual bool hasFocus(){return false;}
		virtual void setText(wchar_t* text){}
		virtual wchar_t* getText(){return L"";}
		virtual void setIcon(wchar_t* text){}
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
		std::vector<D2DUI::WINDOW_STATES>states;
		RECT bounds;
		int iRGBA[4];
		float fRGBA[4];
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		wchar_t* text;
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
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setVisible(bool visible);
		virtual bool isVisible();
		virtual void setEnabled(bool enabled);
		virtual bool isEnabled();
		virtual void setHovered(bool hovered);
		virtual bool isHovered();
		virtual void setPressed(bool pressed);
		virtual bool isPressed();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setHorizontalTextAlignment(const int H){}
		virtual int getHorizontalTextAlignment(){return 0;}
		virtual void setVerticalTextAlignment(const int V){}
		virtual int getVerticalTextAlignment(){return 0;}
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
		virtual void setText(wchar_t* text){}
		virtual wchar_t* getText(){return L"";}
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
		RECT bounds;
		std::vector<D2DUI::WINDOW_STATES> states;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int hAlignment;
		int vAlignment;
		float fRGBA[4];
		int iRGBA[4];
		wchar_t* text;
		wchar_t* font;
		wchar_t* icon;
		float textsize;
		wchar_t* path;
		void setFile(wchar_t* file);
		wchar_t* getFilePath();
		virtual void setVisible(bool visible);
		virtual bool isVisible();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setText(wchar_t* text){}
		virtual wchar_t* getText(){return L"";}
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
		virtual void setHorizontalTextAlignment(const int H){}
		virtual int getHorizontalTextAlignment(){return -1;}
		virtual void setVerticalTextAlignment(const int V){}
		virtual int getVerticalTextAlignment(){return -1;}
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
		virtual void draw(std::shared_ptr<D2DHandle> d2d);
	private:
		int currentframe;
		bool loop;
	};
	class ImageButton:public WindowBase{
	public:
		ImageButton(wchar_t* file=L"", wchar_t* text=L"");
		ImageButton(wchar_t* enabledfile,wchar_t* disabledfile,wchar_t* pressedfile,wchar_t* hoveredfile,wchar_t* text=L"");
		~ImageButton(){}
		wchar_t* text;
		wchar_t* font;
		wchar_t* enabledpath;
		wchar_t* disabledpath;
		wchar_t* pressedpath;
		wchar_t* hoveredpath;
		RECT bounds;
		std::vector<D2DUI::WINDOW_STATES> states;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int hAlignment;
		int vAlignment;
		float fRGBA[4];
		int iRGBA[4];
		wchar_t* icon;
		float textsize;
		virtual void setFont(wchar_t* text);
		virtual wchar_t* getFont();
		void setEnabledFile(wchar_t* file);
		void setDisabledFile(wchar_t* file);
		void setPressedFile(wchar_t* file);
		void setHoveredFile(wchar_t* file);
		virtual void setText(wchar_t* text);
		virtual wchar_t* getText();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void setHorizontalTextAlignment(const int H);
		virtual int getHorizontalTextAlignment();
		virtual void setVerticalTextAlignment(const int V);
		virtual int getVerticalTextAlignment();
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual int getLeftPadding();
		virtual int getTopPadding();
		virtual int getRightPadding();
		virtual int getBottomPadding();
		virtual void setEnabled(bool enabled);
		virtual bool isEnabled();
		virtual void setTextSize(float px);
		virtual float getTextSize();
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual void setForeground(float R,float G,float B,float A=1.0f);
		virtual int* getForegroundInt();
		virtual float* getForegroundFloat();
		virtual void setPressed(bool pressed);
		virtual bool isPressed();
		virtual void setVisible(bool visible);
		virtual bool isVisible();
		virtual void setHovered(bool hovered);
		virtual bool isHovered();
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
		virtual void setGameDate(wchar_t* gamedate)=0;
		virtual wchar_t* getGameDate()=0;
		virtual void setSystemDate(wchar_t* sysdate)=0;
		virtual wchar_t* getSystemDate()=0;
		virtual void setStoryArc(wchar_t* storyarc)=0;
		virtual wchar_t* getStoryArc()=0;
		virtual void setLastDialogue(wchar_t* dialogue)=0;
		virtual wchar_t* getLastDialogue()=0;
	};
	class LoadSlot:public WindowBase, public SlotBase{
	public:
		LoadSlot(wchar_t* gamedate=L"NO DATA",wchar_t* sysdate=L"",wchar_t* storyarc=L"");
		~LoadSlot(){
			delete gd;
			delete sd;
			delete arc;
			delete tn;
		}
		RECT bounds;
		std::vector<D2DUI::WINDOW_STATES> states;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int hAlignment;
		int vAlignment;
		float fRGBA[4];
		int iRGBA[4];
		wchar_t* text;
		wchar_t* font;
		wchar_t* icon;
		float textsize;
		TextLabel* gd;
		TextLabel* sd;
		TextLabel* arc;
		wchar_t* lastdialogue;
		ImageView* tn;
		virtual void setGameDate(wchar_t* gamedate);
		virtual wchar_t* getGameDate();
		virtual void setSystemDate(wchar_t* sysdate);
		virtual wchar_t* getSystemDate();
		virtual void setStoryArc(wchar_t* storyarc);
		virtual wchar_t* getStoryArc();
		virtual void setLastDialogue(wchar_t* dialogue);
		virtual wchar_t* getLastDialogue();
		virtual void setEnabled(bool enabled);
		virtual bool isEnabled();
		virtual void setHovered(bool hovered);
		virtual bool isHovered();
		virtual void setPressed(bool pressed);
		virtual bool isPressed();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setText(wchar_t* text){}
		virtual wchar_t* getText(){return L"";}
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
		virtual void setHorizontalTextAlignment(const int H){}
		virtual int getHorizontalTextAlignment(){return -1;}
		virtual void setVerticalTextAlignment(const int V){}
		virtual int getVerticalTextAlignment(){return -1;}
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
	class SaveSlot:public WindowBase, public SlotBase{
	public:
		SaveSlot(wchar_t* gamedate=L"NO DATA",wchar_t* sysdate=L"",wchar_t* storyarc=L"");
		~SaveSlot(){}
		RECT bounds;
		std::vector<D2DUI::WINDOW_STATES> states;
		int leftPadding;
		int topPadding;
		int rightPadding;
		int bottomPadding;
		int hAlignment;
		int vAlignment;
		float fRGBA[4];
		int iRGBA[4];
		wchar_t* text;
		wchar_t* font;
		wchar_t* icon;
		float textsize;
		TextLabel* gd;
		TextLabel* sd;
		TextLabel* arc;
		ImageButton* trashcan;
		wchar_t* lastdialogue;
		ImageView* tn;
		virtual void setGameDate(wchar_t* gamedate);
		virtual wchar_t* getGameDate();
		virtual void setSystemDate(wchar_t* sysdate);
		virtual wchar_t* getSystemDate();
		virtual void setStoryArc(wchar_t* storyarc);
		virtual wchar_t* getStoryArc();
		virtual void setLastDialogue(wchar_t* dialogue);
		virtual wchar_t* getLastDialogue();
		virtual void setEnabled(bool enabled);
		virtual bool isEnabled();
		virtual void setHovered(bool hovered);
		virtual bool isHovered();
		virtual void setPressed(bool pressed);
		virtual bool isPressed();
		virtual void setBounds(int left,int top,int right,int bottom);
		virtual RECT getBounds();
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setText(wchar_t* text){}
		virtual wchar_t* getText(){return L"";}
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
		virtual void setHorizontalTextAlignment(const int H){}
		virtual int getHorizontalTextAlignment(){return -1;}
		virtual void setVerticalTextAlignment(const int V){}
		virtual int getVerticalTextAlignment(){return -1;}
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
		MsgBox(HWND parent,bool modal,wchar_t* text,wchar_t* title,MSGBoxButtons buttons,MSGBoxIcon icon);
		~MsgBox(){
		}
		std::shared_ptr<TextLabel> textContent, textTitle;
		std::shared_ptr<ImageView> msgboxicon;
		RECT bounds;
		wchar_t* font;
		float textSize;
		float fRGBA[4];
		int iRGBA[4];
		virtual void setTextSize(float px);
		virtual float getTextSize();
		virtual void setFont(wchar_t* text);
		virtual wchar_t* getFont();
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual int* getForegroundInt();
		virtual void setForeground(float R,float G,float B,float A=1.f);
		virtual float* getForegroundFloat();
		virtual void setOpacity(float opacity=1.0f) override;
		virtual void setLocale(wchar_t* locale) override;
		std::shared_ptr<TableRow> contentRow;
		std::shared_ptr<GridLayout> buttonsRow;
		std::shared_ptr<Button> btnOk, btnYes, btnNo, btnCancel;
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	protected:
		virtual void reorderComponents(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setText(wchar_t* text){}
		virtual wchar_t* getText(){return L"";}
		virtual void setEnabled(bool enabled){}
		virtual bool isEnabled(){return false;}
		virtual void setHorizontalTextAlignment(const int H){}
		virtual void setVerticalTextAlignment(const int V){}
		virtual int getHorizontalTextAlignment(){return 0;}
		virtual int getVerticalTextAlignment(){return 0;}
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
		int leftPadding,topPadding,rightPadding,bottomPadding;
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual int getLeftPadding(){return leftPadding;}
		virtual int getTopPadding(){return topPadding;}
		virtual int getRightPadding(){return rightPadding;}
		virtual int getBottomPadding(){return bottomPadding;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setBounds(int left,int top,int right,int bottom){
			bounds.left=left;
			bounds.top=top;
			bounds.right=right;
			bounds.bottom=bottom;
		}
		virtual RECT getBounds(){return bounds;}
		MSGBoxButtons buttons;
		MSGBoxIcon msgicon;
	};
	class InfoBox:public WindowBase, public DialogBase{
	public:
		InfoBox(HWND parent,wchar_t* text);
		~InfoBox(){
		}
		std::shared_ptr<TextLabel> textContent;
		RECT bounds;
		wchar_t* font;
		float textSize;
		float fRGBA[4];
		int iRGBA[4];
		virtual void setTextSize(float px);
		virtual float getTextSize();
		virtual void setFont(wchar_t* text);
		virtual wchar_t* getFont();
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual int* getForegroundInt();
		virtual void setForeground(float R,float G,float B,float A=1.f);
		virtual float* getForegroundFloat();
		virtual void setOpacity(float opacity=1.0f) override;
		virtual void setLocale(wchar_t* locale) override;
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	protected:
		virtual void reorderComponents(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setText(wchar_t* text){}
		virtual wchar_t* getText(){return L"";}
		virtual void setEnabled(bool enabled){}
		virtual bool isEnabled(){return false;}
		virtual void setHorizontalTextAlignment(const int H){}
		virtual void setVerticalTextAlignment(const int V){}
		virtual int getHorizontalTextAlignment(){return 0;}
		virtual int getVerticalTextAlignment(){return 0;}
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
		int leftPadding,topPadding,rightPadding,bottomPadding;
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual int getLeftPadding(){return leftPadding;}
		virtual int getTopPadding(){return topPadding;}
		virtual int getRightPadding(){return rightPadding;}
		virtual int getBottomPadding(){return bottomPadding;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setBounds(int left,int top,int right,int bottom){
			bounds.left=left;
			bounds.top=top;
			bounds.right=right;
			bounds.bottom=bottom;
		}
		virtual RECT getBounds(){return bounds;}
	};
	class PopupNotification:public WindowBase, public DialogBase{
	public:
		PopupNotification(HWND parent,wchar_t* text,long duration);
		~PopupNotification(){}
		RECT bounds;
		float opacity;
		long duration;
		wchar_t* font;
		float textSize;
		float fRGBA[4];
		int iRGBA[4];
		virtual void setTextSize(float px);
		virtual float getTextSize();
		virtual void setFont(wchar_t* text);
		virtual wchar_t* getFont();
		virtual void setForeground(int R,int G,int B,int A=255);
		virtual int* getForegroundInt();
		virtual void setForeground(float R,float G,float B,float A=1.f);
		virtual float* getForegroundFloat();
		TextLabel* textContent;
		virtual void draw(std::shared_ptr<D2DHandle>& d2d);
	protected:
		virtual void reorderComponents(std::shared_ptr<D2DHandle>& d2d);
	private:
		virtual void setText(wchar_t* text){}
		virtual wchar_t* getText(){return L"";}
		virtual void setEnabled(bool enabled){}
		virtual bool isEnabled(){return false;}
		virtual void setHorizontalTextAlignment(const int H){}
		virtual void setVerticalTextAlignment(const int V){}
		virtual int getHorizontalTextAlignment(){return 0;}
		virtual int getVerticalTextAlignment(){return 0;}
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
		int leftPadding,topPadding,rightPadding,bottomPadding;
		virtual void setPadding(int left,int top,int right=-1,int bottom=-1);
		virtual int getLeftPadding(){return leftPadding;}
		virtual int getTopPadding(){return topPadding;}
		virtual int getRightPadding(){return rightPadding;}
		virtual int getBottomPadding(){return bottomPadding;}
		virtual void setIcon(wchar_t* icon){}
		virtual wchar_t* getIcon(){return L"";}
		virtual void setBounds(int left,int top,int right,int bottom){
			bounds.left=left;
			bounds.top=top;
			bounds.right=right;
			bounds.bottom=bottom;
		}
		virtual RECT getBounds(){return bounds;}
	};
}
#endif//Windows code
#endif