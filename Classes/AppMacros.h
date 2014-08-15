#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

/* For demonstrating using one design resolution to match different resources,
   or one resource to match different design resolutions.

   [Situation 1] Using one design resolution to match different resources.
     Please look into Appdelegate::applicationDidFinishLaunching.
     We check current device frame size to decide which resource need to be selected.
     So if you want to test this situation which said in title '[Situation 1]',
     you should change ios simulator to different device(e.g. iphone, iphone-retina3.5, iphone-retina4.0, ipad, ipad-retina),
     or change the window size in "proj.XXX/main.cpp" by "CCEGLView::setFrameSize" if you are using win32 or linux plaform
     and modify "proj.mac/AppController.mm" by changing the window rectangle.

   [Situation 2] Using one resource to match different design resolutions.
     The coordinates in your codes is based on your current design resolution rather than resource size.
     Therefore, your design resolution could be very large and your resource size could be small.
     To test this, just define the marco 'TARGET_DESIGN_RESOLUTION_SIZE' to 'DESIGN_RESOLUTION_2048X1536'
     and open iphone simulator or create a window of 480x320 size.

   [Note] Normally, developer just need to define one design resolution(e.g. 960x640) with one or more resources.
 */

#define DESIGN_RESOLUTION_480X320    0
#define DESIGN_RESOLUTION_1024X768   1
#define DESIGN_RESOLUTION_2048X1536  2

/* If you want to switch design resolution, change next line */
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_1024X768

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;

static Resource smallResource  =  { cocos2d::Size(480, 320),   "iphone" };
static Resource mediumResource =  { cocos2d::Size(1024, 768),  "ipad"   };
static Resource largeResource  =  { cocos2d::Size(2048, 1536), "ipadhd" };

#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
static cocos2d::Size designResolutionSize = cocos2d::Size(1024, 768);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d::Size designResolutionSize = cocos2d::Size(2048, 1536);
#else
#error unknown target design resolution!
#endif

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)


//WINDOWS LOOK LIKE PHONE
typedef struct tagGLViewRect
{
	cocos2d::Rect rect;
	char name[100];
}GLViewRect;

static GLViewRect glviewRect480x800_P  =  { cocos2d::Rect(0,0,480, 800),   "三星 GT-I9003(480x800)" };
static GLViewRect glviewRect480x800_L  =  { cocos2d::Rect(0,0,800, 480),   "三星 GT-I9003(480x800)" };

static GLViewRect glviewRect480x854_P =  { cocos2d::Rect(0,0,480, 854),  "华为 C8860E(480x854)"   };
static GLViewRect glviewRect480x854_L =  { cocos2d::Rect(0,0,854, 480),  "华为 C8860E(480x854)"   };

static GLViewRect glviewRect1920x1080_P  =  { cocos2d::Rect(0,0,1080/2, 1920/2), "HTC_X920e(1920x1080)" };
static GLViewRect glviewRect1920x1080_L  =  { cocos2d::Rect(0,0,1920/2, 1080/2), "HTC_X920e(1920x1080)" };

static GLViewRect glviewRect1280x720_P  =  { cocos2d::Rect(0,0,720/2, 1280/2), "华为_HN3-U01(1280x720)" };
static GLViewRect glviewRect1280x720_L  =  { cocos2d::Rect(0,0,1280/2, 720/2), "华为_HN3-U01(1280x720)" };

static GLViewRect glviewRect960x540_P  =  { cocos2d::Rect(0,0,540, 960), "华为 G610-U00(960x540)" };
static GLViewRect glviewRect960x540_L  =  { cocos2d::Rect(0,0,960, 540), "华为 G610-U00(960x540)" };

static GLViewRect glviewRect1280x800_P  =  { cocos2d::Rect(0,0,800/2, 1280/2), "Sony_Table S(1280x800)" };
static GLViewRect glviewRect1280x800_L  =  { cocos2d::Rect(0,0,1280/2, 800/2), "Sony_Table S(1280x800)" };


#define  targetGLViewRect glviewRect1920x1080_P
#endif /* __APPMACROS_H__ */
