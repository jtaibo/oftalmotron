/**
    Oftalmotron - A set of interactive 3D applications based 
        on eye tracking technology
    Copyright (C) 2010 Javier Taibo <javier.taibo@gmail.com>
    Faculty of Communication Sciences. University of Coruña. Spain

    This file is part of Oftalmotron.

    Oftalmotron is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Oftalmotron is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Oftalmotron.  If not, see <http://www.gnu.org/licenses/>.

	EyeMouse - An eye controled virtual mouse device
	Copyright (C) 2010 Alberto Jaspe <ajaspe@gmail.com>
*/
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
	float oldX=0, oldY=0;
	bool oldValid = true;
	while(true) {
		ot::EyeTracker::Gaze gaze = tet->getCurrentGaze();
		x = gaze.normX() * width;
		y = gaze.normY() * height;
		SetCursorPos((int)((x+oldX)/2.0),(int)((y+oldY)/2.0));
		oldX=x;
		oldY=y;
/*
		if(gaze.left.valid && (!oldValid)) {
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			oldValid = true;
		}
		if(!gaze.left.valid && oldValid) {
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			oldValid = false;
		}
*/
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
