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
#ifndef _EYETRACKER_H_
#define _EYETRACKER_H_

#include "export.h"

namespace ot {

    /**
     *  Eye tracker system abstract interface
     */
    class OFTALMOLIB_EXPORT_DIRECTIVE  EyeTracker {
    public:

        typedef struct {
//            int scrX;   ///< X coordinate in screen space
//            int scrY;   ///< Y coordinate in screen space
            float normX;	///< X coordinate normalized
            float normY;	///< Y coordinate normalized (origin=top)
            bool valid;		///< Is this eye correctly tracked?
        } EyeGaze;

        typedef struct {
            EyeGaze left;   ///< Gaze information of left eye
            EyeGaze right;  ///< Gaze information of right eye
        } Gaze;

        /// Query the eye track status
        virtual Gaze getCurrentGaze() = 0;

	protected:

		Gaze _currentGaze;

    };

}

#endif //_EYETRACKER_H_