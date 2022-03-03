/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: exitQ */
#define  PANEL_CAP1                       2       /* control type: numeric, callback function: (none) */
#define  PANEL_MASS1                      3       /* control type: numeric, callback function: (none) */
#define  PANEL_CAP2                       4       /* control type: numeric, callback function: (none) */
#define  PANEL_MASS2                      5       /* control type: numeric, callback function: (none) */
#define  PANEL_COND                       6       /* control type: numeric, callback function: (none) */
#define  PANEL_START                      7       /* control type: textButton, callback function: Func */
#define  PANEL_TEMP2                      8       /* control type: scale, callback function: Color */
#define  PANEL_TEMP1                      9       /* control type: scale, callback function: Color */
#define  PANEL_MAT3                       10      /* control type: deco, callback function: (none) */
#define  PANEL_MAT1                       11      /* control type: deco, callback function: (none) */
#define  PANEL_MAT2                       12      /* control type: deco, callback function: (none) */
#define  PANEL_TIMEINT                    13      /* control type: numeric, callback function: (none) */
#define  PANEL_TIMING                     14      /* control type: numeric, callback function: (none) */
#define  PANEL_TIMER                      15      /* control type: timer, callback function: Time */
#define  PANEL_RESET                      16      /* control type: command, callback function: ResetAll */
#define  PANEL_GRAPH                      17      /* control type: command, callback function: Graph */
#define  PANEL_TEMPAC                     18      /* control type: numeric, callback function: (none) */
#define  PANEL_PICTURE                    19      /* control type: picture, callback function: About */
#define  PANEL_FLAME_2                    20      /* control type: picture, callback function: (none) */
#define  PANEL_FLAME                      21      /* control type: picture, callback function: (none) */

#define  PANEL_2                          2       /* callback function: exitQ2 */
#define  PANEL_2_GRAPH                    2       /* control type: graph, callback function: CURSORXY */
#define  PANEL_2_RESETPLOT                3       /* control type: command, callback function: plotReset */
#define  PANEL_2_PLOT                     4       /* control type: command, callback function: plot */
#define  PANEL_2_RING                     5       /* control type: ring, callback function: (none) */
#define  PANEL_2_COLORNUM                 6       /* control type: color, callback function: (none) */
#define  PANEL_2_YCURS                    7       /* control type: numeric, callback function: (none) */
#define  PANEL_2_XCURS                    8       /* control type: numeric, callback function: (none) */
#define  PANEL_2_DECORATION               9       /* control type: deco, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK About(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Color(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CURSORXY(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exitQ(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exitQ2(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Graph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK plot(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK plotReset(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ResetAll(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Time(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
