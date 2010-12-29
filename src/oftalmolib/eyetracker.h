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
#ifndef _EYETRACKER_H_
#define _EYETRACKER_H_

#include "export.h"
#include <vector>

namespace ot {

    /**
     *  Eye tracker system abstract interface
     */
    class OFTALMOLIB_EXPORT_DIRECTIVE EyeTracker {
    public:

		/**
		 *	Gaze observer.
		 *
		 *	Registered observers will be notified
		 *	each time new gaze data is available
		 */
		class OFTALMOLIB_EXPORT_DIRECTIVE Observer {
		public:
			virtual void notify() = 0;
		};

		/** 
		 *	Gaze information for one eye
		 */
        class OFTALMOLIB_EXPORT_DIRECTIVE EyeGaze {
		public:
            float normX;	///< X coordinate (normalized)
            float normY;	///< Y coordinate (normalized) (origin=top)
			float distance;	///< Distance from eye to screen (mm)
			float pupilSize;	///< Pupil diameter (mm)
            bool valid;		///< Is this eye correctly tracked?

			/// Constructor
			EyeGaze()
			{ valid = false; }
        };

		/**
		 *	Gaze information for two eyes
		 *
		 *	This struct provides methods for
		 */
        class OFTALMOLIB_EXPORT_DIRECTIVE Gaze {
		public:
            EyeGaze left;   ///< Gaze information of left eye
            EyeGaze right;  ///< Gaze information of right eye

			/// Averaged normalized X coordinate
			float normX();

			/// Averaged normalized Y coordinate
			float normY();

			/// Averaged distance from eyes to screen (mm)
			float distance();

			/// Averaged pupil size (mm)
			float pupilSize();

			bool valid();
        };

        /// Query the eye track status
        virtual Gaze getCurrentGaze() = 0;

		/// Register a new observer
		void registerObserver( Observer *obs );

	protected:

		Gaze _currentGaze;

		/// List of observer objects
		std::vector<Observer *> _observers;

		/// Notify registered observers. New data is available
		void notifyObservers();

    };

}

#endif //_EYETRACKER_H_
