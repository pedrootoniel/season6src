/*#include "happyhttp.h"
#include "sha1.h"*/
#include "StdAfx.h"
#include <winsock2.h>

#if !defined(AFX_PROTECT_H__F6763674_2EFE_4243_9D00_45971CECFBB8__INCLUDED_)
#define AFX_PROTECT_H__F6763674_2EFE_4243_9D00_45971CECFBB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)

static DWORD HDTYPE;
static char HDNAME[16];
static char HDSERIAL[18];
static SYSTEM_INFO HDSYSTEM;

#define ENC_NUMBER 850

#define HD_TYPE_1 895742 //NORMAL
#define HD_TYPE_2 106671 //TEMP
#define HD_TYPE_3 789541 //EXTENDED

#define  SMART_GET_VERSION		0x00074080
#define  SMART_RCV_DRIVE_DATA	 0x0007c088
#define  IDE_ATAPI_IDENTIFY	   0xA1
#define  IDE_ATA_IDENTIFY		 0xEC

struct DRIVER_STATUS
{
	BYTE  bDriverError;	 //  Error code from driver, or 0 if no error.
	BYTE  bIDEStatus;	   //  Contents of IDE Error register.
	BYTE  bReserved[10];	//  Reserved for future expansion.
};

struct DRIVER_DATA
{
	DWORD cBufferSize;		  //  Size of bBuffer in bytes
	DRIVER_STATUS DriverStatus; //  Driver status structure.
	BYTE bBuffer[512];		  //  Buffer of arbitrary length in which to store the data read from the drive.
};

struct DRIVER_VERSION
{
	BYTE bVersion;		   // Binary driver version.
	BYTE bRevision;		  // Binary driver revision.
	BYTE bReserved;		  // Not used.
	BYTE bIDEDeviceMap;	  // Bit map of IDE devices.
	DWORD fCapabilities;	 // Bit mask of driver capabilities.
	DWORD dwReserved[4];	 // For future use.
};

struct DRIVER_INFO
{
	BYTE bFeaturesReg;	   // Used for specifying SMART "commands".
	BYTE bSectorCountReg;	// IDE sector count register
	BYTE bSectorNumberReg;   // IDE sector number register
	BYTE bCylLowReg;		 // IDE low order cylinder value
	BYTE bCylHighReg;		// IDE high order cylinder value
	BYTE bDriveHeadReg;	  // IDE drive/head register
	BYTE bCommandReg;		// Actual IDE command.
	BYTE bReserved;		  // reserved for future use.  Must be zero.
};

struct DRIVER_BASE
{
	DWORD cBufferSize;	   // Buffer size in bytes
	DRIVER_INFO DriverInfo;  // Structure with drive register values.
	BYTE bDriveNumber;	   // Physical drive number to send command to (0,1,2,3).
	BYTE bReserved[16];	  // Reserved for future expansion.
};

#pragma pack(1)

typedef struct _IDENTIFY_DATA {
	USHORT GeneralConfiguration;			// 00 00
	USHORT NumberOfCylinders;			   // 02  1
	USHORT Reserved1;					   // 04  2
	USHORT NumberOfHeads;				   // 06  3
	USHORT UnformattedBytesPerTrack;		// 08  4
	USHORT UnformattedBytesPerSector;	   // 0A  5
	USHORT SectorsPerTrack;				 // 0C  6
	USHORT VendorUnique1[3];				// 0E  7-9
	USHORT SerialNumber[10];				// 14  10-19
	USHORT BufferType;					  // 28  20
	USHORT BufferSectorSize;				// 2A  21
	USHORT NumberOfEccBytes;				// 2C  22
	USHORT FirmwareRevision[4];			 // 2E  23-26
	USHORT ModelNumber[20];				 // 36  27-46
	UCHAR  MaximumBlockTransfer;			// 5E  47
	UCHAR  VendorUnique2;				   // 5F
	USHORT DoubleWordIo;					// 60  48
	USHORT Capabilities;					// 62  49
	USHORT Reserved2;					   // 64  50
	UCHAR  VendorUnique3;				   // 66  51
	UCHAR  PioCycleTimingMode;			  // 67
	UCHAR  VendorUnique4;				   // 68  52
	UCHAR  DmaCycleTimingMode;			  // 69
	USHORT TranslationFieldsValid:1;		// 6A  53
	USHORT Reserved3:15;
	USHORT NumberOfCurrentCylinders;		// 6C  54
	USHORT NumberOfCurrentHeads;			// 6E  55
	USHORT CurrentSectorsPerTrack;		  // 70  56
	ULONG  CurrentSectorCapacity;		   // 72  57-58
	USHORT CurrentMultiSectorSetting;	   //	 59
	ULONG  UserAddressableSectors;		  //	 60-61
	USHORT SingleWordDMASupport : 8;		//	 62
	USHORT SingleWordDMAActive : 8;
	USHORT MultiWordDMASupport : 8;		 //	 63
	USHORT MultiWordDMAActive : 8;
	USHORT AdvancedPIOModes : 8;			//	 64
	USHORT Reserved4 : 8;
	USHORT MinimumMWXferCycleTime;		  //	 65
	USHORT RecommendedMWXferCycleTime;	  //	 66
	USHORT MinimumPIOCycleTime;			 //	 67
	USHORT MinimumPIOCycleTimeIORDY;		//	 68
	USHORT Reserved5[2];					//	 69-70
	USHORT ReleaseTimeOverlapped;		   //	 71
	USHORT ReleaseTimeServiceCommand;	   //	 72
	USHORT MajorRevision;				   //	 73
	USHORT MinorRevision;				   //	 74
	USHORT Reserved6[50];				   //	 75-126
	USHORT SpecialFunctionsEnabled;		 //	 127
	USHORT Reserved7[128];				  //	 128-255
} IDENTIFY_DATA,*PIDENTIFY_DATA;

#pragma pack()

static int DataCount=0;
static char FeedBack[256];

extern bool IsMeAuth;

class CProtect
{
public:
	CProtect()
	{
	}

	virtual ~CProtect()
	{
	}

	static void GetSerial(int ver1)
	{
		char serial[256];
		char Sys[256];
		char FinalHash[256];

		char temptext[256];

		SYSTEM_INFO system;

		MEMORYSTATUS mi;
		memset( &mi, 0, sizeof(MEMORYSTATUS) );
		mi.dwLength = sizeof(MEMORYSTATUS);
		GlobalMemoryStatus( &mi );

		int hd = 0;

		wchar_t name[256];

		swprintf(name,L"\\\\.\\PhysicalDrive%d",hd);

		HANDLE Drive = CreateFileW(name,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);

		if(Drive == INVALID_HANDLE_VALUE)
		{
			CProtect::CloseProcess();
		}

		DWORD TempSerial = 0;
		GetVolumeInformation("C:\\",NULL,0,&TempSerial,NULL,NULL,NULL,0);
		wsprintf(serial,"%X",TempSerial);
		CloseHandle(Drive);

		GetSystemInfo(&system);

		wsprintf(Sys,"%X|%X|%X|%X|%X|%X|%X",system.dwActiveProcessorMask,system.dwNumberOfProcessors,system.dwProcessorType,system.wProcessorArchitecture,system.wProcessorLevel,system.wProcessorRevision,mi.dwTotalPhys);
		wsprintf(temptext,"%s|%s",Sys,serial);

		SHA1 sha;
		unsigned message_digest1[5];

		sha.Reset();
		sha << temptext;
		sha.Result(message_digest1);

		wsprintf(FinalHash,"%08X-%08X-%08X-%08X-%08X",message_digest1[0],message_digest1[1],message_digest1[2],message_digest1[3],message_digest1[4]);

		char tempAnswer[256];
		char Answer[256];

		wsprintf(tempAnswer,"8%08X",message_digest1[3]);

		sha.Reset();
		sha << tempAnswer;
		sha.Result(message_digest1);

		wsprintf(Answer,"%08X",message_digest1[2]);

		/*HTTP*/
		WSAData wsaData;
		int code = WSAStartup(MAKEWORD(1, 1), &wsaData);
		if( code != 0 )
		{
			wsprintf(temptext,"Erro de acesso ao servidor de licen�as: %d",code);
			MessageBox(0,temptext,"www.supremoteam.tech",0);
			CProtect::CloseProcess();
		}

		wsprintf(temptext,"service=eMUlator&key=%s&ver=%d",FinalHash,ver1);

		const char* body = temptext;

		try {
			CProtect::GetLicense(body);
		}
		catch( happyhttp::Wobbly& e )
		{
			wsprintf(temptext, "Erro de acesso ao servidor de licen�as: %s", e.what() );
			MessageBox(0,temptext,"www.supremoteam.tech",0);
			CProtect::CloseProcess();
		}

		WSACleanup();

		if(strcmp(Answer,FeedBack) != 0)
		{
			MessageBox(0,"Falha na autentica��o!\nVerifique os dados no painel de licen�a ou entre em contato conosco.","www.supremoteam.tech",MB_OK|MB_ICONERROR);
			CProtect::CloseProcess();
		}
		else
		{
			IsMeAuth = true;
		}

		CloseHandle(Drive);
	}

	static void GetLicense(const char* body)
	{
		const char* headers[] =
		{
			"Connection", "close",
			"Content-type", "application/x-www-form-urlencoded",
			"Accept", "text/plain",
			0
		};
		happyhttp::Connection conn("auth.supremoteam.tech", 80);
		conn.setcallbacks(CProtect::OnBegin, CProtect::OnData, CProtect::OnComplete, 0);
		conn.request("POST", "/auth.php", headers, (const unsigned char*)body, strlen(body));

		while( conn.outstanding() )
			conn.pump();
	}

	static void OnBegin( const happyhttp::Response* r, void* userdata )
	{
		DataCount = 0;
	}

	static void OnData( const happyhttp::Response* r, void* userdata, const unsigned char* data, int n )
	{
		wsprintf(&FeedBack[strlen(FeedBack)],"%s",data);
		DataCount += n;
	}

	static void OnComplete( const happyhttp::Response* r, void* userdata )
	{
		FeedBack[8] = '\0';
	}

	static char* ConvertToString(WORD* lpData,int start,int end)
	{
		static char string[1024];
		int pos = 0;

		for(int n=start; n <= end; n++)
		{
			string[pos] = (char)(lpData[n]/256);

			if((BYTE)string[pos] != 0x20)
			{
				pos++;
			}

			string[pos] = (char)(lpData[n]%256);

			if((BYTE)string[pos] != 0x20)
			{
				pos++;
			}
		}

		string[pos] = '\0';

		return string;
	}

	static void CloseProcess()
	{
		//MessageBox(NULL,"Erro de licen�a.\nInicializa��o abortada.","Ferrarezi MU Server",MB_OK|MB_ICONERROR);
		HANDLE process = GetCurrentProcess();
		DWORD exit;
		GetExitCodeProcess(process,&exit);
		TerminateProcess(process,exit);
		ExitProcess(0);
	}
};

#endif // !defined(AFX_PROTECT_H__F6763674_2EFE_4243_9D00_45971CECFBB8__INCLUDED_)