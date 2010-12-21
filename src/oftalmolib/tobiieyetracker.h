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

namespace ot {

    /**
     *  Tobii eye tracker
     */
    class TobiiEyeTracker : public EyeTracker {
    public:

        /// System initialization
        virtual void initialize();

        /// Systema shutdown
        virtual void shutDown();

        /// Update
        virtual void update();

        /// Query the eye track status
        virtual Gaze getCurrentStatus();

    };

}

#endif //_TOBIIEYETRACKER_H_
