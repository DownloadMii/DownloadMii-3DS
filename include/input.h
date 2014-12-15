#pragma once


#include <iostream>
#include <vector>

using namespace std;

struct Input_s{
	bool Up = false, Down = false, Left = false, Right = false, A = false, B = false, X = false, Y = false, Start = false, Select = false, L= false, R = false;
	u32 lX = 0, lY = 0, rX = 0, rY = 0; //ToDo
	u16 touchX = 0, touchY = 0;
};

typedef struct __RECT{
	s32 left,top,right,bottom;
} RECT,*LPRECT;

struct IMiiWindow{
	virtual int create(u32,u32,u32,u32,u32) = 0;
	virtual int destroy() = 0;
	virtual int draw(u8 *screen) = 0;
	virtual int onInput(Input_s*) = 0;
	virtual int set_BkColor(u32 c) = 0;
	virtual int set_TextColor(u32 c) = 0;
	virtual int set_Text(char *s) = 0;
};

class CMiiWindow : public IMiiWindow {
public:	
	CMiiWindow();
	virtual ~CMiiWindow();
	int create(u32 x,u32 y,u32 w,u32 h,u32 id);
	virtual int destroy();
	virtual int draw(u8 *screen);
	virtual int onInput(Input_s* i);
	int set_BkColor(u32 c);
	int set_TextColor(u32 c);
	int set_Text(char *s);
protected:
	u32 ID,color,bkcolor,status,styles,accel;
	RECT sz;	
	char *text;
	int (*cb)(CMiiWindow *);
};

class vButton_s : public CMiiWindow{
	int draw(u8 *screen);
};

class CScrollBar : public CMiiWindow{
public:
	int draw(u8 *screen){return 0;};
protected:
	u32 pos,min,max;
};

extern vector<IMiiWindow *> vButtons;

void UpdateInput(Input_s*  input);
void resetInput(Input_s*  input);


void checkVButtonTouch(); 
void addVButton(vButton_s button);
void clearVButtons();
