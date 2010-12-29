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
#include "eyetracker.h"

using namespace ot;

/**
 *	Averaged normalized X coordinate
 */
float EyeTracker::Gaze::normX()
{
	if ( valid() ) {
		return (left.normX+right.normX)/2.0f;
	}
	else if ( left.valid ) {
		return left.normX;
	}
	else if ( right.valid ) {
		return right.normX;
	}
	return -1.0;
}


/**
 *	Averaged normalized Y coordinate
 */
float EyeTracker::Gaze::normY()
{
	if ( valid() ) {
		return (left.normY+right.normY)/2.0f;
	}
	else if ( left.valid ) {
		return left.normY;
	}
	else if ( right.valid ) {
		return right.normY;
	}
	return -1.0;
}


/**
 *	Averaged distance from eyes to screen (mm)
 */
float EyeTracker::Gaze::distance()
{
	if ( valid() ) {
		return (left.distance+right.distance)/2.0f;
	}
	else if ( left.valid ) {
		return left.distance;
	}
	else if ( right.valid ) {
		return right.distance;
	}
	return -1.0;
}


/**
 *	Averaged pupil size (mm)
 */
float EyeTracker::Gaze::pupilSize()
{
	if ( valid() ) {
		return (left.pupilSize+right.pupilSize)/2.0f;
	}
	else if ( left.valid ) {
		return left.pupilSize;
	}
	else if ( right.valid ) {
		return right.pupilSize;
	}
	return -1.0;
}


/**
 *	Valid gaze
 */
bool EyeTracker::Gaze::valid()
{
	return left.valid && right.valid; 
}


/**
 *	Register a new observer
 */
void EyeTracker::registerObserver( Observer *obs )
{
	_observers.push_back(obs);
}


/**
 *	Notify registered observers. New data is available
 */
void EyeTracker::notifyObservers()
{
	for( std::vector<Observer *>::iterator i = _observers.begin() ; i != _observers.end() ; i++ ) {
		(*i)->notify();
	}
}
