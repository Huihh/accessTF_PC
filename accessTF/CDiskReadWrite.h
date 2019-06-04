#pragma once
class CDiskReadWrite
{
public:
	CDiskReadWrite();
	~CDiskReadWrite();


public:

	BOOL ReadSectors(BYTE bDrive, DWORD dwStartSector, WORD wSectors, LPBYTE lpSectBuff);
	BOOL WriteSectors(BYTE bDrive, DWORD dwStartSector, WORD wSectors, LPBYTE lpSectBuff);

};

