#include "stdafx.h"
#include "HWID.h"
#include "Protect.h"
#include "Util.h"


cHwid gHwid;

bool cHwid::GetPhysicalDriveSerialNumber(int PhysicalDriveNumber,char* PhysicalDriveSerial,int PhysicalDriveSerialSize) // OK
{
	char PhysicalDrivePath[MAX_PATH];

	wsprintf(PhysicalDrivePath,"\\\\.\\PhysicalDrive%d",PhysicalDriveNumber);

	HANDLE PhysicalDriveHandle = CreateFile(PhysicalDrivePath,0,FILE_SHARE_READ | FILE_SHARE_WRITE,0,OPEN_EXISTING,0,0);

	if(PhysicalDriveHandle == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD BytesReturned;

	STORAGE_PROPERTY_QUERY StoragePropertyQuery;

	STORAGE_DESCRIPTOR_HEADER StorageDescriptorHeader;

	memset(&StoragePropertyQuery,0,sizeof(StoragePropertyQuery));

	memset(&StorageDescriptorHeader,0,sizeof(StorageDescriptorHeader));

	StoragePropertyQuery.PropertyId = StorageDeviceProperty;

	StoragePropertyQuery.QueryType = PropertyStandardQuery;

	if(DeviceIoControl(PhysicalDriveHandle,IOCTL_STORAGE_QUERY_PROPERTY,&StoragePropertyQuery,sizeof(StoragePropertyQuery),&StorageDescriptorHeader,sizeof(StorageDescriptorHeader),&BytesReturned,0) == 0)
	{
		CloseHandle(PhysicalDriveHandle);
		return 0;
	}

	BYTE* PhysicalDriveBuff = new BYTE[StorageDescriptorHeader.Size];

	memset(PhysicalDriveBuff,0,StorageDescriptorHeader.Size);

	if(DeviceIoControl(PhysicalDriveHandle,IOCTL_STORAGE_QUERY_PROPERTY,&StoragePropertyQuery,sizeof(StoragePropertyQuery),PhysicalDriveBuff,StorageDescriptorHeader.Size,&BytesReturned,0) == 0)
	{
		CloseHandle(PhysicalDriveHandle);
		delete[] PhysicalDriveBuff;
		return 0;
	}

	if(((STORAGE_DEVICE_DESCRIPTOR*)PhysicalDriveBuff)->SerialNumberOffset == 0)
	{
		CloseHandle(PhysicalDriveHandle);
		delete[] PhysicalDriveBuff;
		return 0;
	}

	__try
	{
		strcpy_s(PhysicalDriveSerial,PhysicalDriveSerialSize,(char*)(PhysicalDriveBuff+((STORAGE_DEVICE_DESCRIPTOR*)PhysicalDriveBuff)->SerialNumberOffset));
		CloseHandle(PhysicalDriveHandle);
		delete[] PhysicalDriveBuff;
		return 1;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		CloseHandle(PhysicalDriveHandle);
		delete[] PhysicalDriveBuff;
		return 0;
	}
}

char* cHwid::GetHardwareId() //OK
{
	char PhysicalDriveSerial[256];

	memset(PhysicalDriveSerial,0,sizeof(PhysicalDriveSerial));

	for(int n=0;n < 5;n++)
	{
		if(this->GetPhysicalDriveSerialNumber(n,PhysicalDriveSerial,sizeof(PhysicalDriveSerial)) != 0)
		{
			break;
		}
	}

	DWORD ComputerHardwareId1 = *(DWORD*)(&PhysicalDriveSerial[0x00]) ^ *(DWORD*)(&PhysicalDriveSerial[0x10]) ^ 0x3AD3B74A;

	DWORD ComputerHardwareId2 = *(DWORD*)(&PhysicalDriveSerial[0x04]) ^ *(DWORD*)(&PhysicalDriveSerial[0x14]) ^ 0x94FDC685;

	DWORD ComputerHardwareId3 = *(DWORD*)(&PhysicalDriveSerial[0x08]) ^ *(DWORD*)(&PhysicalDriveSerial[0x18]) ^ 0xF45BBF4C;

	DWORD ComputerHardwareId4 = *(DWORD*)(&PhysicalDriveSerial[0x0C]) ^ *(DWORD*)(&PhysicalDriveSerial[0x1C]) ^ 0x8941D8E7;

	static char HardwareId[36];

	wsprintf(HardwareId,"%08X-%08X-%08X-%08X",ComputerHardwareId1,ComputerHardwareId2,ComputerHardwareId3,ComputerHardwareId4);

	return HardwareId;
}

void cHwid::SendHwid()
{
	CG_HWID_SEND pMsg;
	memcpy(pMsg.HardwareId,GetHardwareId(),sizeof(pMsg.HardwareId));
	memcpy(pMsg.DLLVersion,DLL_VERSION,sizeof(pMsg.DLLVersion));
	pMsg.AntihackCRC = gProtect.GetFileCRC(gProtect.m_MainInfo.PluginName1);
	pMsg.AntihackCRC = gProtect.GetFileCRC(gProtect.m_MainInfo.PluginName2);
	pMsg.AntihackCRC = gProtect.GetFileCRC(gProtect.m_MainInfo.PluginName3);
	pMsg.AntihackCRC = gProtect.GetFileCRC(gProtect.m_MainInfo.PluginName4);
	pMsg.AntihackCRC = gProtect.GetFileCRC(gProtect.m_MainInfo.PluginName5);
	pMsg.DllCRC = gProtect.GetFileCRC("Main.dll");
	pMsg.MainCRC = gProtect.GetFileCRC(gProtect.m_MainInfo.ClientName);
	pMsg.PlayerCRC = gProtect.GetFileCRC("Data\\Player\\Player.bmd");
	pMsg.Head.set(0xF3,0xE9,sizeof(pMsg));
	DataSend((BYTE*)&pMsg,pMsg.Head.size);
}