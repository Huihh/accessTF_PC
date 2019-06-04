#include "pch.h"
#include "CDiskReadWrite.h"


CDiskReadWrite::CDiskReadWrite()
{
}


CDiskReadWrite::~CDiskReadWrite()
{
}


BOOL CDiskReadWrite::ReadSectors(BYTE bDrive, DWORD dwStartSector, WORD wSectors, LPBYTE lpSectBuff)
{
	if (bDrive == 0)
		return 0;

	CHAR devName[] = "\\\\.\\A:";
	devName[4] = 'A' + bDrive - 1;

	HANDLE hDev = CreateFile(devName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hDev == INVALID_HANDLE_VALUE)
		return 0;

	SetFilePointer(hDev, 512 * dwStartSector, 0, FILE_BEGIN);
	DWORD dwCB;
	BOOL ret = ReadFile(hDev, lpSectBuff, 512 * wSectors, &dwCB, NULL);
	CloseHandle(hDev);

	return ret;
}


BOOL CDiskReadWrite::WriteSectors(BYTE bDrive, DWORD dwStartSector, WORD wSectors, LPBYTE lpSectBuff)
{
	if (bDrive == 0)
		return 0;

	CHAR devName[] = "\\\\.\\A:";
	devName[4] = 'A' + bDrive - 1;

	HANDLE hDev = CreateFile(devName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hDev == INVALID_HANDLE_VALUE)
		return 0;

	SetFilePointer(hDev, 512 * dwStartSector, 0, FILE_BEGIN);
	DWORD dwCB;
	BOOL ret = WriteFile(hDev, lpSectBuff, 512 * wSectors, &dwCB, NULL);
	CloseHandle(hDev);


	return ret;
}