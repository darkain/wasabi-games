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
// This is essentially the same project as example1, without all the comments
// and with a less complex window.

//
// Always start with std.h
#include "../../bfc/std.h"
//
#include "Games.h"     //EDITME
#include "llamasweeper.h"
#include "resource.h"
#include "checksoutwnd.h"  //EDITME
//
#include "../../common/xlatstr.h"
// Window creation services includes.
#include "../../studio/services/creators.h"
#include "../../bfc/wndcreator.h"


static WACNAME wac;
WACPARENT *the = &wac;                     

//  *** This is MY GUID.  Get your own!
// {11417678-A5C0-4203-A891-9320D4504BBE}
static const GUID guid =  //EDITME (hint: use guidgen.exe)
{ 0x11417678, 0xa5c0, 0x4203, { 0xa8, 0x91, 0x93, 0x20, 0xd4, 0x50, 0x4b, 0xbe } };



WACNAME::WACNAME() : WACPARENT("Random Games") {
  // So, what did we want to do again?  Oh yes...

  // 1) we are going to make a window,
  registerService(new WndCreateCreatorSingle< CreateWndByGuid<ChecksoutWnd> >);
  registerService(new WndCreateCreatorSingle< CreateWndByGuid<LlamaWnd> >);

  // 2) and have it be listed in the Thinger,
  registerService(new WndCreateCreatorSingle< CreateBucketItem<ChecksoutWnd> >);
  registerService(new WndCreateCreatorSingle< CreateBucketItem<LlamaWnd> >);

  // 3) and in the main context menu.
  registerAutoPopup(ChecksoutWnd::getWindowTypeGuid(), ChecksoutWnd::getWindowTypeName());
  registerAutoPopup(LlamaWnd::getWindowTypeGuid(), LlamaWnd::getWindowTypeName());
}

WACNAME::~WACNAME() {
}

GUID WACNAME::getGUID() {
  return guid;
}

void WACNAME::onCreate() {
  // *** Do startup stuff here that doesn't require you to have a window yet
}

void WACNAME::onDestroy() {
}

