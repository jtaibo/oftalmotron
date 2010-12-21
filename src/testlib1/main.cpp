/**
    Oftalmotron - A set of interactive 3D applications based 
        on eye tracking technology
    Copyright (C) 2010 Javier Taibo <javier.taibo@gmail.com>
    Faculty of Communication Sciences. University of Coru�a. Spain

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
*/

#include "../oftalmolib/tobiieyetracker.h"
#include <iostream>

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

    OpenThreads::Thread::microSleep(3000000);
    while(true) {
        std::cout << "Left X : " << tet->getCurrentGaze().left.normX << std::endl;
        std::cout << "Left Y : " << tet->getCurrentGaze().left.normY << std::endl;
        std::cout << "Left valid : " << tet->getCurrentGaze().left.valid << std::endl;
        std::cout << "Right X : " << tet->getCurrentGaze().right.normX << std::endl;
        std::cout << "Right Y : " << tet->getCurrentGaze().right.normY << std::endl;
        std::cout << "Right valid : " << tet->getCurrentGaze().right.valid << std::endl;
        OpenThreads::Thread::microSleep(1000000);
    }
}