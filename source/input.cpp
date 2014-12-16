#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <3ds.h>
#include "utils.h"
#include "application.h"
#include "input.h"
#include "gui.h"

vector<IMiiWindow *> vButtons;
touchPosition tp;
int x;
void UpdateInput(Input_s* input){
	resetInput(input);
	hidTouchRead(&tp);
	input->touchX = tp.px;
	input->touchY = tp.py;
	
	checkVButtonTouch(input);
	
	hidScanInput();
	u32 kDown = hidKeysDown();
	if(kDown){
		x++;
		char buffer[100];
		sprintf(buffer, "Input, %d\n", x);
		print(buffer);
		if(kDown & KEY_A){
			input->A = true;
		} if(kDown & KEY_B){
			input->B = true;
		} if(kDown & KEY_X){
			input->X = true;
		} if(kDown & KEY_Y){
			input->Y = true;
		}
		
		if(kDown & KEY_UP){
			input->Up = true;
		} if(kDown & KEY_DOWN){
			input->Down = true;
		} if(kDown & KEY_LEFT){
			input->Left = true;
		} if(kDown & KEY_RIGHT){
			input->Right = true;
		}
		
		if(kDown & KEY_START){
			input->Start = true;
		} if(kDown & KEY_SELECT){
			input->Select = true;
		} if(kDown & KEY_L){
			input->L = true;
		} if(kDown & KEY_R){
			input->R = true;
		}
	}
}

void resetInput(Input_s* input){
	input->A = false;
	input->B = false;
	input->X = false;
	input->Y = false;
	input->Up = false;
	input->Down = false;
	input->Left = false;
	input->Right = false;
	input->Start = false;
	input->Select = false;
	input->L = false;
	input->R = false;
	input->touchX = 0;
	input->touchY = 0;
}

void checkVButtonTouch(Input_s* input){
	for(auto &but : vButtons){
		if((input->touchX >= but.x && input->touchX <= but.x2) && (input->touchY >= but.y && input->touchY <= but.y2)){
			but.pressed = true;
			print("PRESSED!!!!!!!!\n");
		}
		else{
			but.pressed = false;
		}
	}
}
void addVButton(vButton_s button){
	vButtons.push_back(button);
}
void clearVButtons(){
	vButton_s but;
	vButtons.push_back(but);
	vButtons.clear();
}

CMiiWindow::CMiiWindow()
{
}

CMiiWindow::~CMiiWindow()
{
	destroy();
}

int CMiiWindow::create(u32 x,u32 y,u32 w,u32 h,u32 id)
{
	sz.left=x;
	sz.top=y;
	sz.right=x+w;
	sz.bottom=y+h;
	ID=id;
	color=0;
	bkcolor=0xffffffff;
	text = NULL;
	cb = NULL;
	accel = 0;
	vButtons.push_back(this);
	return 0;
}

int CMiiWindow::destroy()
{
	if(text){
		free(text);
		text = NULL;
	}
	return 0;
}

int CMiiWindow::draw(u8 *screen)
{
	return 0;
}

int CMiiWindow::set_BkColor(u32 c)
{
	bkcolor = c;
	return 0;
}

int CMiiWindow::set_TextColor(u32 c)
{
	color=c;
	return 0;
}

int CMiiWindow::set_Text(char *s)
{
	if(text != NULL)
		free(text);
	text=NULL;
	if(s){
		text = (char *)malloc(strlen(s)+1);
		if(text == NULL)
			return -1;
		text[0]=0;
		strcpy(text,s);
	}
	return 0;
}

int CMiiWindow::onInput(Input_s* i)
{
	status &= ~1;
	if(i->touchX < sz.left)
		return -1;
	if(i->touchX > sz.right)
		return -2;
	if(i->touchY < sz.top)
		return -3;
	if(i->touchY > sz.bottom)
		return -4;
	//we are inside the widget
	status |= 1;
	if(cb != NULL)
		cb(this);
	return 0;
}

int vButton_s::draw(u8 *screen)
{
	return 0;
}
