
/**
 * libemulation
 * OEEmulation
 * (C) 2009-2011 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Controls an OpenEmulator emulation
 */

#ifndef _OEEMULATION_H
#define _OEEMULATION_H

#include <vector>

#include "OEDocument.h"
#include "OEComponent.h"
#include "OEDevice.h"

using namespace std;

typedef void (*EmulationDidUpdate)(void *userData);
typedef OEComponent *(*EmulationConstructCanvas)(void *userData, OEComponent *device);
typedef void (*EmulationDestroyCanvas)(void *userData, OEComponent *canvas);

typedef map<string, OEComponent *> OEComponentsMap;

class OEEmulation : public OEComponent, public OEDocument
{
public:
	OEEmulation();
	~OEEmulation();
	
	void setResourcePath(string path);
	void setDidUpdate(EmulationDidUpdate didUpdate);
	void setConstructCanvas(EmulationConstructCanvas constructCanvas);
	void setDestroyCanvas(EmulationDestroyCanvas destroyCanvas);
	void setUserData(void *userData);
	
	bool addComponent(string id, OEComponent *component);
	bool removeComponent(string id);
	OEComponent *getComponent(string id);
	string getId(OEComponent *component);
	
	bool isActive();
	
private:
	string resourcePath;
	OEComponentsMap componentsMap;
	
	EmulationDidUpdate didUpdate;
	EmulationConstructCanvas constructCanvas;
	EmulationDestroyCanvas destroyCanvas;
	void *userData;
	
	int activityCount;
	
	bool constructDocument(xmlDocPtr doc);
	bool constructDevice(string deviceId);
	bool constructComponent(string id, string className);
	bool configureDocument();
	bool configureDevice(string deviceId,
						 string label, string image, string group,
						 xmlNodePtr children);
    bool configureInlets(OEInletMap& inletMap);
	bool configureComponent(string id, xmlNodePtr children);
	bool initDocument();
	bool initComponent(string id);
	bool updateDocument();
	bool updateComponent(string id, xmlNodePtr children);
	void deconfigureDocument();
    void deconfigureDevice(string deviceId);
	void deconfigureComponent(string id, xmlNodePtr children);
	void destroyDocument();
    void destroyDevice(string deviceId);
	void destroyComponent(string id, xmlNodePtr children);
	
	bool hasValueProperty(string value, string propertyName);
	string parseValueProperties(string value, map<string, string>& propertiesMap);
	
    friend class OEDevice;
};

#endif
