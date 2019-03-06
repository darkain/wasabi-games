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
#include "checksoutwnd.h"
#include "resource.h"

#include "../../bfc/canvas.h"
#include "../../common/xlatstr.h"
#include "../../bfc/notifmsg.h"

#include <direct.h>


// {603918A5-20B2-4612-973D-38AA4C877B61}
static const GUID Guid_Checksout = 
{ 0x603918a5, 0x20b2, 0x4612, { 0x97, 0x3d, 0x38, 0xaa, 0x4c, 0x87, 0x7b, 0x61 } };


//  Methods required by Window Creation Services
const char *ChecksoutWnd::getWindowTypeName() { return "Checks Out"; }
GUID ChecksoutWnd::getWindowTypeGuid() { return Guid_Checksout; }
void ChecksoutWnd::setIconBitmaps(ButtonWnd *button) {
  button->setBitmaps(the->gethInstance(), IDB_TAB_NORMAL, NULL, IDB_TAB_HILITED, IDB_TAB_SELECTED);
}


ChecksoutWnd::~ChecksoutWnd() {
/*	for (int i1=0; i1<12; i1++) {
		for (int i2=0; i2<12; i2++) {
			FPRINTF(thefile, "%d,", buttons[i1][i2]->getPushed());
		}
	}*/
	FCLOSE(thefile);
}


int ChecksoutWnd::getPreferences(int what)  {
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


int ChecksoutWnd::onInit() {
  int retval = CHECKSOUTWND_PARENT::onInit();

	GuiObject *obj = getGuiObject();
	if (obj) {
		AddCommand(" Reset ", 1, 1);
		obj->guiobject_addAppCmds(this);
	}

  // Do your startup stuff here.

	_mkdir("Games");
	_mkdir("Games/Checks Out");
	thefile = FOPEN("Games/Checks Out/level1.thelevel", "r");

	for (int i1=0; i1<12; i1++) {
		for (int i2=0; i2<12; i2++) {
			ButtonWnd *btn = new ButtonWnd();
			buttons[i1][i2] = btn;
			btn->setNotifyWindow(this);
			btn->setNotifyId((i2*12)+i1);
			addChild(btn, i1*16, i2*16, 16, 16);
			btn->init(this);

			int pushed = 0;
			if (fscanf(thefile, "%d,", &pushed) < 1) pushed = 0;
			btn->setPushed(pushed);
		}
	}
  
  return retval;
}


int ChecksoutWnd::childNotify(RootWnd *child, int msg, int param1, int param2) {
	int retval = CHECKSOUTWND_PARENT::childNotify(child, msg, param1, param2);
	if (child == NULL) return retval;

	if (msg == ChildNotify::BUTTON_LEFTPUSH) {
		{
			char str[256];
			sprintf(str, "%d Clicks", ++numClicks);
			GuiObject *obj = getGuiObject();
			if (obj) obj->guiobject_setStatusText(str);
		}

		int i1 = child->getNotifyId() % 12;
		int i2 = child->getNotifyId() / 12;

		buttons[i1][i2]->setPushed(!buttons[i1][i2]->getPushed());

		if (i1 > 0) buttons[i1-1][i2]->setPushed(!buttons[i1-1][i2]->getPushed());
		if (i1 < 11) buttons[i1+1][i2]->setPushed(!buttons[i1+1][i2]->getPushed());

		if (i2 > 0) buttons[i1][i2-1]->setPushed(!buttons[i1][i2-1]->getPushed());
		if (i2 < 11) buttons[i1][i2+1]->setPushed(!buttons[i1][i2+1]->getPushed());

		for (i1=0; i1<12; i1++) {
			for (i2=0; i2<12; i2++) {
				if (buttons[i1][i2]->getPushed()) return retval;
			}
		}
		char winner[] = "You are teh winner type thingy!!";
		api->messageBox(winner, "A winner is you", 0, "", this);
	}

	return retval;
}


void ChecksoutWnd::appcmds_onCommand(int id, const RECT *buttonRect) {
}