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
#ifndef _CHECKSOUTWND_H
#define _CHECKSOUTWND_H

#include "../../common/contwnd.h"
#include "../../bfc/wnds/buttwnd.h"
#include "../../common/nsGUID.h"
#include "../../bfc/appcmds.h"

#define CHECKSOUTWND_PARENT ContWnd

class ChecksoutWnd : public CHECKSOUTWND_PARENT, public AppCmdsI {
public:
  ChecksoutWnd() {  
    // Set the titlebar text for the window.
    setName(getWindowTypeName());
		numClicks = 0;
  }

	virtual ~ChecksoutWnd();

  // =========================================================================
  //
  //  Methods required by Window Creation Services
  //
  static const char *getWindowTypeName();
  static GUID getWindowTypeGuid();
  static void setIconBitmaps(ButtonWnd *button);    

  // =========================================================================
  //
  //
  virtual int onInit();
//  virtual int onPaint(Canvas *canvas);

	virtual int getPreferences(int what) ;
	virtual int childNotify(RootWnd *child, int msg, int param1, int param2);

	virtual void appcmds_onCommand(int id, const RECT *buttonRect);
	void AddCommand(const char *name, int _id, int _side=0)
	{ CmdRec *c = new CmdRec(name, _id, _side, 1); appcmds_addCmd(c); }
  
protected:
	ButtonWnd *buttons[12][12];
	FILE *thefile;
	int numClicks;
};

#endif _CHECKSOUTWND_H
