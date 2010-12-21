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
*/
#include "tobiieyetracker.h"
#include <iostream>
#include <tet.h>


using namespace ot;


/**
 *	Constructor
 */
TobiiEyeTracker::TobiiEyeTracker( char * host, long port )
{
	// Create and launch the eye tracking thread
	_host = host;
	_port = port;
}


/**
 *	Destructor
 */
TobiiEyeTracker::~TobiiEyeTracker()
{
}


/**
 *	Start tracking
 */
void TobiiEyeTracker::startTracking()
{
}


/**
 *	Stop tracking
 */
void TobiiEyeTracker::stopTracking()
{
}


/**
 *	Query the eye track status
 */
EyeTracker::Gaze TobiiEyeTracker::getCurrentGaze()
{
	EyeTracker::Gaze gaze;
	_gazeMutex.lock();
	gaze = _currentGaze;
	_gazeMutex.unlock();
	return gaze;
}


/**
 *  Tobii Callback Function
 */
void __stdcall callback_function( ETet_CallbackReason reason, void *pData, void *pApplicationData )
{
//    static int iteration = 0;

    if( pData != NULL ) {
        STet_GazeData *gaze_data = (STet_GazeData *)pData;
/*        std::cout << "Timestamp : " << gaze_data->timestamp_sec << "s " << gaze_data->timestamp_microsec << "us" << std::endl;
        std::cout << "Left eye" << std::endl;
        std::cout << "  GazePos X : " << gaze_data->x_gazepos_lefteye << std::endl;
        std::cout << "  GazePos Y : " << gaze_data->y_gazepos_lefteye << std::endl;
        std::cout << "  CamPos X  : " << gaze_data->x_camerapos_lefteye << std::endl;
        std::cout << "  CamPos Y  : " << gaze_data->y_camerapos_righteye << std::endl;
        std::cout << "  PupilDiam : " << gaze_data->diameter_pupil_lefteye << std::endl;
        std::cout << "  Distance  : " << gaze_data->distance_lefteye << std::endl;
        std::cout << "  Validity  : " << gaze_data->validity_lefteye << std::endl;
        std::cout << "Right eye" << std::endl;
        std::cout << "  GazePos X : " << gaze_data->x_gazepos_righteye << std::endl;
        std::cout << "  GazePos Y : " << gaze_data->y_gazepos_righteye << std::endl;
        std::cout << "  CamPos X  : " << gaze_data->x_camerapos_righteye << std::endl;
        std::cout << "  CamPos Y  : " << gaze_data->y_camerapos_righteye << std::endl;
        std::cout << "  PupilDiam : " << gaze_data->diameter_pupil_righteye << std::endl;
        std::cout << "  Distance  : " << gaze_data->distance_righteye << std::endl;
        std::cout << "  Validity  : " << gaze_data->validity_righteye << std::endl;
*/
		EyeTracker::Gaze gaze;
		gaze.left.normX = gaze_data->x_gazepos_lefteye;
		gaze.left.normY = gaze_data->y_gazepos_lefteye;
		gaze.left.valid = gaze_data->validity_lefteye == 0;
		gaze.right.normX = gaze_data->x_gazepos_righteye;
		gaze.right.normY = gaze_data->y_gazepos_righteye;
		gaze.right.valid = gaze_data->validity_righteye == 0;

		TobiiEyeTracker *tet = (TobiiEyeTracker *)pApplicationData;
		tet->updateGaze( gaze );
    }

    //if ( iteration > MAX_ITERATIONS ) {
    //    Tet_Stop();
    //}
}

#define CHECK_ERROR(call_name) \
    if ( err != TET_NO_ERROR ) { \
        std::cerr << "ERROR. " << call_name << " (" << Tet_GetLastError() << ") : " << Tet_GetLastErrorAsText(pErrBuf) << std::endl; \
        throw -1; \
    }

/**
 *  Thread's run method.  Must be implemented by derived classes.
 *  This is where the action happens.
 */
void TobiiEyeTracker::run()
{
    long err;
    char pErrBuf[256];

	std::cout << "Connecting to " << _host << " on port " << _port << std::endl;

    // Note: this calls must be performed within the same thread
    err = Tet_Connect(_host, _port, TET_SYNC_NONE);
	CHECK_ERROR("Tet_Connect")

    std::cout << "Checking eye tracker..." << std::endl;
    err = Tet_PerformSystemCheck();
	CHECK_ERROR("Tet_PerformSystemCheck");
	char serial_diode_controller[64];
    char serial_camera[64];
    err = Tet_GetSerialNumber( serial_diode_controller, serial_camera );
    if ( err == TET_NO_ERROR ) {
        std::cout << "Serial diode controller : " << serial_diode_controller << std::endl;
        std::cout << "Serial camera : " << serial_camera << std::endl;
    }
    else {
        std::cerr << "ERROR. Tet_GetSerialNumber (" << Tet_GetLastError() << ") : " << Tet_GetLastErrorAsText(pErrBuf) << std::endl;
        throw -1;
    }

    /*
    err = Tet_CalibLoadFromFile( CALIBRATION_FILE );
    if ( err != TET_NO_ERROR ) {
        std::cerr << "ERROR. Tet_CalibLoadFromFile (" << Tet_GetLastError() << ") : " << Tet_GetLastErrorAsText(pErrBuf) << std::endl;
        return -1;
    }
    */

    long interval = 0;  // 0 = wait until there are new data
//    STet_GazeData gaze_data;
//    err = Tet_Start( callback_function, &gaze_data, interval );
    err = Tet_Start( callback_function, this, interval );
	CHECK_ERROR("Tet_Start")
    // ...

    Tet_Disconnect();
}


/**
 *	Update the gaze information
 *	This method is meant to be called from the eye tracking thread
 *	and so the gaze access is protected by the mutex
 */
void TobiiEyeTracker::updateGaze( Gaze &gaze )
{
	_gazeMutex.lock();
	_currentGaze = gaze;
	_gazeMutex.unlock();
}
