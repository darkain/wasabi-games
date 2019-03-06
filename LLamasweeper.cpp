/*

  Nullsoft WASABI Source File License

  Copyright 1999-2003 Nullsoft, Inc.

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

*/
#include "../../bfc/std.h"

#include "games.h"
#include "llamasweeper.h"
#include "resource.h"

#include "../../bfc/canvas.h"
#include "../../common/xlatstr.h"
#include "../../bfc/notifmsg.h"

//#include <direct.h>


// {0A389483-2B7F-4aad-884A-ADF5AEC3A702}
static const GUID Guid_Llama = 
{ 0xa389483, 0x2b7f, 0x4aad, { 0x88, 0x4a, 0xad, 0xf5, 0xae, 0xc3, 0xa7, 0x2 } };


int Rand(int n) { if (n==0) return 0; return (rand() % n - 1) + 1; }


//  Methods required by Window Creation Services
const char *LlamaWnd::getWindowTypeName() { return "LLmamasweepers"; }
GUID LlamaWnd::getWindowTypeGuid() { return Guid_Llama; }
void LlamaWnd::setIconBitmaps(ButtonWnd *button) {
  button->setBitmaps(the->gethInstance(), IDB_TAB_NORMAL, NULL, IDB_TAB_HILITED, IDB_TAB_SELECTED);
}


LlamaWnd::~LlamaWnd() {
}


int LlamaWnd::getPreferences(int what)  {
	switch (what)  {
		case SUGGESTED_W: return 192;
		case SUGGESTED_H: return 192;
		case SUGGESTED_X: return -1;
		case SUGGESTED_Y: return -1;
		case MINIMUM_W:   return 192;
		case MINIMUM_H:   return 192;
		case MAXIMUM_W:   return 192;
		case MAXIMUM_H:   return 192;
	}
	return -1;
}


int LlamaWnd::onInit() {
  int retval = LLAMAWND_PARENT::onInit();

	GuiObject *obj = getGuiObject();
	if (obj) {
		AddCommand(" Reset ", 1, 1);
		obj->guiobject_addAppCmds(this);
	}

	ZeroMemory(bombs, sizeof(bombs));

	for (int i1=0; i1<12; i1++) {
		for (int i2=0; i2<12; i2++) {
			ButtonWnd *btn = new ButtonWnd();
			buttons[i1][i2] = btn;
			btn->setNotifyWindow(this);
			btn->setNotifyId((i2*12)+i1);
			addChild(btn, i1*16, i2*16, 16, 16);
			btn->init(this);
		}
	}

	int setbombs = 0;

	while (setbombs < 75) {
		int b = Rand(144);
		int b1 = b % 12;
		int b2 = b / 12;
		if (bombs[b1][b2] == 0) {
			bombs[b1][b2] = 'B';
			setbombs++;
		}
	}

	for (int b1=0; b1<12; b1++) {
		for (int b2=0; b2<12; b2++) {
			if (bombs[b1][b2] == 0) {
				bombs[b1][b2] = '0';
				if (b1>0) if (bombs[b1-1][b2] == 'B') bombs[b1][b2]++;
				if (b2>0) if (bombs[b1][b2-1] == 'B') bombs[b1][b2]++;
				if (b1<11) if (bombs[b1+1][b2] == 'B') bombs[b1][b2]++;
				if (b2<11) if (bombs[b1][b2+1] == 'B') bombs[b1][b2]++;

				if ( (b1>0) & (b2>0) ) if (bombs[b1-1][b2-1] == 'B') bombs[b1][b2]++;
				if ( (b1<11) & (b2<11) ) if (bombs[b1+1][b2+1] == 'B') bombs[b1][b2]++;
				if ( (b1>0) & (b2<11) ) if (bombs[b1-1][b2+1] == 'B') bombs[b1][b2]++;
				if ( (b1<11) & (b2>0) ) if (bombs[b1+1][b2-1] == 'B') bombs[b1][b2]++;
			}
		}
	}
  
  return retval;
}


int LlamaWnd::childNotify(RootWnd *child, int msg, int param1, int param2) {
	int retval = LLAMAWND_PARENT::childNotify(child, msg, param1, param2);
	if (child == NULL) return retval;

	if (msg == ChildNotify::BUTTON_LEFTPUSH) {
		int i1 = child->getNotifyId() % 12;
		int i2 = child->getNotifyId() / 12;

		if (!buttons[i1][i2]->getEnabled()) return retval;
		buttons[i1][i2]->enableButton(FALSE);

		switch (bombs[i1][i2]) {
		case 'B': buttons[i1][i2]->setName("B");	break;
		case '1': buttons[i1][i2]->setName("1");	break;
		case '2': buttons[i1][i2]->setName("2");	break;
		case '3': buttons[i1][i2]->setName("3");	break;
		case '4': buttons[i1][i2]->setName("4");	break;
		case '5': buttons[i1][i2]->setName("5");	break;
		case '6': buttons[i1][i2]->setName("6");	break;
		case '7': buttons[i1][i2]->setName("7");	break;
		case '8': buttons[i1][i2]->setName("8");	break;
		case '9': buttons[i1][i2]->setName("9");	break;
		default:{
				buttons[i1][i2]->setName("-");
				if (i1>0) childNotify(buttons[i1-1][i2], ChildNotify::BUTTON_LEFTPUSH, 0, 0);
				if (i1<11) childNotify(buttons[i1+1][i2], ChildNotify::BUTTON_LEFTPUSH, 0, 0);
				if (i2>0) childNotify(buttons[i1][i2-1], ChildNotify::BUTTON_LEFTPUSH, 0, 0);
				if (i2<11) childNotify(buttons[i1][i2+1], ChildNotify::BUTTON_LEFTPUSH, 0, 0);
			}
		}
	}

	return retval;
}

void LlamaWnd::appcmds_onCommand(int id, const RECT *buttonRect) {
}
