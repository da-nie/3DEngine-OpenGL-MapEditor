#ifndef CRender_H
#define CRender_H

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "common.h"
#include "surface.h"
#include "polygon.h"
#include "shadow.h"
#include "lighting.h"
#include "wc_progress.h"
#include "formats.h"
#include "dl_startposform.h"
#include "dl_selecttextureform.h"
#include "dl_createlightingform.h"
#include "dl_createsegmentform.h"
#include "dl_createsimplysectorform.h"
#include "dl_createsimplydoorform.h"

class CRender
{
 public:
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  CRender(char *FileName);
  //----------------------------------------------------------------------------
};
#endif