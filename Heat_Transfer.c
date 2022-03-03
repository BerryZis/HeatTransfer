#include <cvirte.h>		
#include <userint.h>
#include "Heat_Transfer.h"

static int panelHandle, panelHandle2;

typedef struct Materials {
	
	double mass;
	double cap;
	double temp;
	

} Material;

static double interval=0.01;
static int flag=0;
static int startflag=0;
static Material mat1,mat2;
static int count=0;
static double xarr[10000] = {0.0};
static double y1arr[10000] = {0.0};
static double y2arr[10000] = {0.0};

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Heat_Transfer.uir", PANEL)) < 0)
		return -1;
	if ((panelHandle2 = LoadPanel (0, "Heat_Transfer.uir", PANEL_2)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	MessagePopup ("Welcome", "Welcome to a Heat Transfer simulator\n\n\nCreated by Berry Ziskind - 308183037\n\nFor more information and features click the Flame about!");
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

//Exit Panel 1
int CVICALLBACK exitQ (int panel, int event, void *callbackData,
					   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}


int CVICALLBACK Time (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	
	double cond;
	double I1,I2,dQ1,dQ2,dT1,dT2;
	double dTac = 0.005;
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			
			
			//flames control
			if((int)(count*interval)%2==0){
				SetCtrlAttribute (panelHandle, PANEL_FLAME, ATTR_VISIBLE, 1);
				SetCtrlAttribute (panelHandle, PANEL_FLAME_2, ATTR_VISIBLE, 0);}
			else{
				SetCtrlAttribute (panelHandle, PANEL_FLAME, ATTR_VISIBLE, 0);
				SetCtrlAttribute (panelHandle, PANEL_FLAME_2, ATTR_VISIBLE, 1);}
			  
			//Getting values
			GetCtrlAttribute (panelHandle, PANEL_START, ATTR_CTRL_VAL,&flag );
			
			GetCtrlVal (panelHandle, PANEL_MASS1, &mat1.mass);
			GetCtrlVal (panelHandle, PANEL_MASS2, &mat2.mass);
			GetCtrlVal (panelHandle, PANEL_CAP1, &mat1.cap);
			GetCtrlVal (panelHandle, PANEL_CAP2, &mat2.cap);
			GetCtrlVal (panelHandle, PANEL_TEMP1, &mat1.temp);
			GetCtrlVal (panelHandle, PANEL_TEMP2, &mat2.temp);
			GetCtrlVal (panelHandle, PANEL_COND, &cond);
			
			//saving each teamperature measured to an array
			y1arr[count] =  mat1.temp;
			y2arr[count] =  mat2.temp;
		
			//chaniging color while simulation running
			SetCtrlAttribute (panelHandle, PANEL_MAT1, ATTR_FRAME_COLOR, MakeColor ((mat1.temp/200)*255,0,0));
			SetCtrlAttribute (panelHandle, PANEL_MAT2, ATTR_FRAME_COLOR, MakeColor ((mat2.temp/200)*255,0,0));
			SetCtrlAttribute (panelHandle, PANEL_TEMP1, ATTR_FILL_COLOR, MakeColor ((mat1.temp/200)*255,0,0));
			SetCtrlAttribute (panelHandle, PANEL_TEMP2, ATTR_FILL_COLOR, MakeColor ((mat2.temp/200)*255,0,0));
			
			//physics
			I1 = cond*(mat2.temp - mat1.temp);
			I2 = - I1;
			
			dQ1 = I1 * interval;
			dQ2 = I2 * interval;
			
			dT1 = dQ1/(mat1.mass * mat1.cap);
			dT2 = dQ2/(mat2.mass * mat2.cap);
			
			
			mat1.temp = mat1.temp + dT1;
			mat2.temp = mat2.temp + dT2;
			
			//chaning tempreture showed on the slides
			SetCtrlVal (panelHandle, PANEL_TEMP1, mat1.temp);
			SetCtrlVal (panelHandle, PANEL_TEMP2, mat2.temp);
			
			//The Delta Temperature Accuracy
			GetCtrlVal (panelHandle,PANEL_TEMPAC, &dTac); 
			
			//The condition to stop (depends on Delta Temperature Accuracy) 
			if (((mat1.temp - mat2.temp) < dTac && (mat1.temp - mat2.temp) > -dTac) || flag==0)
			{
				SetCtrlAttribute (panelHandle, PANEL_START, ATTR_CTRL_VAL, 0);
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
				
			}	
			
			//Creates array of time in seconds
			xarr[count] = count*interval; 
			count++;
			
			//show time to user in seconds
			SetCtrlVal (panelHandle, PANEL_TIMING,(int)(count*interval));
		
			
			break;
	}
	return 0;
}
//Start button function
int CVICALLBACK Func (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal(panelHandle,PANEL_TIMEINT, &interval);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_INTERVAL, interval);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
			startflag=1;

			break;
	}
	return 0;
}

//chaning colors manually on slides
int CVICALLBACK Color (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			
			GetCtrlVal (panelHandle, PANEL_TEMP1, &mat1.temp);
			GetCtrlVal (panelHandle, PANEL_TEMP2, &mat2.temp);
			
			SetCtrlAttribute (panelHandle, PANEL_MAT1, ATTR_FRAME_COLOR, MakeColor ((mat1.temp/200)*255,0,0));
			SetCtrlAttribute (panelHandle, PANEL_MAT2, ATTR_FRAME_COLOR, MakeColor ((mat2.temp/200)*255,0,0));
			
			SetCtrlAttribute (panelHandle, PANEL_TEMP1, ATTR_FILL_COLOR, MakeColor ((mat1.temp/200)*255,0,0));
			SetCtrlAttribute (panelHandle, PANEL_TEMP2, ATTR_FILL_COLOR, MakeColor ((mat2.temp/200)*255,0,0));

			break;
	}
	return 0;
}

//Reset simulation and all parameters 
int CVICALLBACK ResetAll (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			flag=0;
			startflag=0;
			count = 0;
			DeleteGraphPlot (panelHandle2, PANEL_2_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			HidePanel (panelHandle2);
			SetCtrlAttribute (panelHandle, PANEL_START, ATTR_CTRL_VAL, 0);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
			
			SetCtrlVal (panelHandle, PANEL_MASS1, 10.0);
			SetCtrlVal (panelHandle, PANEL_MASS2, 10.0);
			SetCtrlVal (panelHandle, PANEL_CAP1, 0.01);
			SetCtrlVal (panelHandle, PANEL_CAP2, 0.01);
			SetCtrlVal (panelHandle, PANEL_TEMP1, 200.0);
			SetCtrlVal (panelHandle, PANEL_TEMP2, 10.0);
			SetCtrlVal (panelHandle, PANEL_COND, 0.03);
			SetCtrlVal (panelHandle,PANEL_TIMEINT, 0.01);
			SetCtrlVal (panelHandle,PANEL_TEMPAC, 0.005);
			GetCtrlVal (panelHandle, PANEL_TEMP1, &mat1.temp);
			GetCtrlVal (panelHandle, PANEL_TEMP2, &mat2.temp);
			
			SetCtrlAttribute (panelHandle, PANEL_MAT1, ATTR_FRAME_COLOR, MakeColor ((mat1.temp/200)*255,0,0));
			SetCtrlAttribute (panelHandle, PANEL_MAT2, ATTR_FRAME_COLOR, MakeColor ((mat2.temp/200)*255,0,0));
			SetCtrlAttribute (panelHandle, PANEL_TEMP1, ATTR_FILL_COLOR, MakeColor ((mat1.temp/200)*255,0,0));
			SetCtrlAttribute (panelHandle, PANEL_TEMP2, ATTR_FILL_COLOR, MakeColor ((mat2.temp/200)*255,0,0));
			break;
	}
	return 0;
}

//Display Panel2 graphs
int CVICALLBACK Graph (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		
			DisplayPanel (panelHandle2);
			break;
	}
	return 0;
}
//Exit panel 2
int CVICALLBACK exitQ2 (int panel, int event, void *callbackData,
						int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
				HidePanel (panelHandle2);
			break;
	}
	return 0;
}

//Plot the graphs depending on list choice
int CVICALLBACK plot (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	int plot,gc,i;
	double deltarr[10000];
	switch (event)
	{
		case EVENT_COMMIT:

			if (startflag)
			
			{
			GetCtrlVal (panelHandle2, PANEL_2_RING, &plot);
			GetCtrlVal (panelHandle2, PANEL_2_COLORNUM, &gc);
			
			switch (plot)
			{
				case 0:
			
					
					PlotXY (panelHandle2, PANEL_2_GRAPH, xarr, y1arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, gc);
					break;
					
					
				case 1:
					
					
					PlotXY (panelHandle2, PANEL_2_GRAPH, xarr, y2arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, gc);
					break;
					
				case 2:
					for (i=0;i<count;i++)
						deltarr[i]=y1arr[i]-y2arr[i];//temperature delta
					
					PlotXY (panelHandle2, PANEL_2_GRAPH, xarr, deltarr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, gc);
					break;
					
			}
			
			}
			
			else
				MessagePopup ("Data Error", "No data to display\nPlease run the simulator first"); //Wont show graph if the simulation didnt run and no data collected yet (arrays are empty and time is zero)
			break;
		
	}
	return 0;
}

//delete graphs shown
int CVICALLBACK plotReset (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			DeleteGraphPlot (panelHandle2, PANEL_2_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			
			
			break;
	}
	return 0;
}

//cursor option on graph
int CVICALLBACK CURSORXY (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	double xcurs,ycurs;
	switch (event)
	{
		case EVENT_MOUSE_POINTER_MOVE:
			
			 GetGraphCursor (panelHandle2, PANEL_2_GRAPH, 1, &xcurs, &ycurs);
			
			 SetCtrlVal(panelHandle2, PANEL_2_XCURS, xcurs);
			 SetCtrlVal(panelHandle2, PANEL_2_YCURS, ycurs);

			break;
	}
	return 0;
}			 

//about message on picture
int CVICALLBACK About (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			
			MessagePopup ("About", "Features:\n- Delta accuracy selection\n- Time interval selection\n- Reset All button will erase all the data and exit the graphs\n- Graph will not presented if no data collected\n- Zooming option for graph (CTRL+Mouse)\n- Flames moving decoration\n- About button\n\n\nCreated by Berry Ziskind - 308183037 ");
			
			break;
	}
	return 0;
}
