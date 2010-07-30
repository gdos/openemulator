
/**
 * libemulation
 * Host
 * (C) 2010 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Controls host events
 */

#include "Host.h"

bool Host::setProperty(const string &name, const string &value)
{
	if (name == "notes")
		notes = value;
	else if (name == "powerState")
	{
		powerState = getInt(value);
		postNotification(HOST_POWERSTATE_CHANGED, &powerState);
	}
	else if (name == "videoWindow")
		videoWindow = value;
	else if (name == "hidMouseCapture")
		hidMouseCapture = getInt(value);
	else if (name == "hidKeyboardLEDs")
		hidKeyboardLEDs = getInt(value);
	else
		return false;
	
	return true;
}

bool Host::getProperty(const string &name, string &value)
{
	if (name == "notes")
		value = notes;
	else if (name == "powerState")
		value = getString(powerState);
	else if (name == "videoWindow")
		value = videoWindow;
	else if (name == "hidMouseCapture")
		value = getString(hidMouseCapture);
	else if (name == "hidKeyboardLEDs")
		value = getString(hidKeyboardLEDs);
	else
		return false;
	
	return true;
}

bool Host::addScreen(HostVideoScreen *screen)
{
	videoScreens.push_back(screen);
	
	return true;
}

bool Host::removeScreen(HostVideoScreen *screen)
{
	HostVideoScreens::iterator first = videoScreens.begin();
	HostVideoScreens::iterator last = videoScreens.end();
	HostVideoScreens::iterator i = remove(first, last, screen);
	bool found = (i != last);
	if (found)
		videoScreens.erase(i, last);
	
	return found;
}

bool Host::postEvent(OEComponent *component, int event, void *data)
{
	switch(event)
	{
		case HOST_REGISTER_VIDEO_CALLBACK:
			break;
			
		case HOST_REGISTER_HID_CALLBACK:
			break;
			
		case HOST_ADD_SCREEN:
			videoUpdated = true;
			return addScreen((HostVideoScreen *) data);
			
		case HOST_REMOVE_SCREEN:
			videoUpdated = true;
			return removeScreen((HostVideoScreen *) data);
	}
	
	return OEComponent::postEvent(component, event, data);
}
