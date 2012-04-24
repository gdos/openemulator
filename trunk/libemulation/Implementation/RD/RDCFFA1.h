
/**
 * libemulation
 * R&D CFFA1
 * (C) 2011-2012 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Implements an R&D CFFA1 interface card
 */

#include "OEComponent.h"

#include "diskimage.h"

class RDCFFA1 : public OEComponent
{
public:
    RDCFFA1();
    ~RDCFFA1();
    
    bool setValue(string name, string value);
    bool getValue(string name, string& value);
    bool setRef(string name, OEComponent *ref);
    bool init();
    void dispose();
    
    bool postMessage(OEComponent *sender, int message, void *data);
    
    OEChar read(OEAddress address);
    void write(OEAddress address, OEChar value);
    
private:
    string diskImagePath;
    bool forceWriteProtected;
    
    OEComponent *device;
    
    OEComponent *ram;
    OEComponent *rom;
    
    OEComponent *memoryBus;
    
    DIAppleDiskImage diskImage;
    
    OEChar ataBuffer[0x200];
    OEInt ataBufferIndex;
    bool ataError;
    OEUnion ataLBA;
    OEChar ataCommand;
    
    void mapMemory(int message);
    bool openDiskImage(string path);
    void closeDiskImage();
};
