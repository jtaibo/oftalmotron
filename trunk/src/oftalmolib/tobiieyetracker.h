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
#ifndef _TOBIIEYETRACKER_H_
#define _TOBIIEYETRACKER_H_

#include "eyetracker.h"
#include <OpenThreads/Thread>
#include <string>

namespace ot {

    /**
     *  Tobii eye tracker
     */
	class __declspec(dllexport) TobiiEyeTracker : public EyeTracker, public OpenThreads::Thread {
    public:

		/// Constructor
		TobiiEyeTracker( char * host, long port );

		/// Destructor
		~TobiiEyeTracker();

		/// Start tracking
		virtual void startTracking();

		/// Stop tracking
		virtual void stopTracking();

        /// Query the eye track status
        virtual Gaze getCurrentGaze();

		/**
		 *  Thread's run method.  Must be implemented by derived classes.
		 *  This is where the action happens.
		 */
		virtual void run();

		/**
		 *	Update the gaze information
		 *	This method is meant to be called from the eye tracking thread
		 *	and so the gaze access is protected by the mutex
		 */
		void updateGaze( Gaze &gaze );

	private:

		char * _host;

		long _port;

		OpenThreads::Mutex _gazeMutex;

    };

}

#endif //_TOBIIEYETRACKER_H_
