

#include "../oftalmolib/tobiieyetracker.h"
#include <iostream>
#include <windows.h>

#define TET_SERVER  "localhost"    // NULL = default: "127.0.0.1" or "localhost"
#define PORT        4455       // 0 = default: 4455


int main(int argc, char *argv[])
{
	OpenThreads::Thread::Init();
	char *host = TET_SERVER;
	long port = PORT;

	if ( argc > 1 ) {
		host = argv[1];
	}
	if ( argc > 2 ) {
		port = atoi(argv[2]);
	}
	ot::TobiiEyeTracker *tet = new ot::TobiiEyeTracker( host, port );
	tet->start();
	tet->waitForInit();

    OpenThreads::Thread::microSleep(3000000);
    float x,y;
	
	// Lets take clip rectangle for the win mouse
	RECT screenRect;
	GetClipCursor(&screenRect);
	unsigned int width  = screenRect.right - screenRect.left;
	unsigned int height = screenRect.bottom - screenRect.top;
	
	while(true) {
		x = tet->getCurrentGaze().normX() * width;
		y = tet->getCurrentGaze().normX() * height;
		SetCursorPos(x,y);
        OpenThreads::Thread::microSleep(100000);

#ifdef _DEBUG
		POINT p;
		GetCursorPos(&p);
		std::cout << p.x << "\t" << p.y << std::endl;
#endif

    }

	// Poner esto donde se quiera simular un click
	// mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}