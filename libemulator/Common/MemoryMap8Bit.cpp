
/**
 * libemulator
 * 8 bit memory map
 * (C) 2010 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Controls a generic 8-bit memory map
 */

#include "MemoryMap8Bit.h"

MemoryMap8Bit::MemoryMap8Bit()
{
	offset = 0;
	
	for (int i = 0; i < MEMORYMAP8BIT_SIZE; i++)
		readMap[i] = writeMap[i] = 0;
}

void MemoryMap8Bit::setRange(OEComponent *component, int start, int end)
{
	start &= MEMORYMAP8BIT_MASK;
	end &= MEMORYMAP8BIT_MASK;
	for (int i = start; i < end; i++)
	{
		readMap[i] = component;
		writeMap[i] = component;
	}
}

int MemoryMap8Bit::ioctl(int message, void *data)
{
	switch(message)
	{
		case OEIOCTL_CONNECT:
		{
			OEIoctlConnection *connection = (OEIoctlConnection *) data;
			OEIoctlMemoryMap memoryMap;
			connection->component->ioctl(OEIOCTL_GET_MEMORYMAP, &memoryMap);
			setRange(memoryMap.component, memoryMap.offset, memoryMap.size);
			break;
		}
		case OEIOCTL_SET_PROPERTY:
		{
			OEIoctlProperty *property = (OEIoctlProperty *) data;
			if (property->name == "offset")
				offset = intValue(property->value);
		}
		case OEIOCTL_GET_MEMORYMAP:
		{
			OEIoctlMemoryMap *memoryMap = (OEIoctlMemoryMap *) data;
			memoryMap->component = this;
			memoryMap->offset = offset;
			memoryMap->size = MEMORYMAP8BIT_SIZE;
			break;
		}
		case OEIOCTL_SET_MEMORYMAP:
		{
			OEIoctlMemoryMap *memoryMap = (OEIoctlMemoryMap *) data;
			setRange(memoryMap->component, memoryMap->offset, memoryMap->size);
			break;
		}
	}
	
	return 0;
}

int MemoryMap8Bit::read(int address)
{
	return readMap[address & MEMORYMAP8BIT_MASK]->read(address);
}

void MemoryMap8Bit::write(int address, int value)
{
	readMap[address & MEMORYMAP8BIT_MASK]->write(address, value);
}
