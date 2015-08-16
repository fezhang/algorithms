#ifndef _INCLUDED_TYPE_DEF_H_
#define _INCLUDED_TYPE_DEF_H_

//typedef char INT8;
typedef unsigned char UINT8;

typedef short INT16;
typedef unsigned short UINT16;

typedef int INT32;
typedef unsigned int UINT32;

typedef unsigned char			DsBYTE;
typedef unsigned char*			DsPBYTE;
typedef unsigned char* const	DsCPBYTE;

typedef char					DsCHAR;
typedef char*					DsSTR;
typedef char* const				DsCSTR;

typedef UINT32		DsSize;
#define INVALID_DS_SIZE (UINT32)(-1)

typedef UINT32		DsBOOL;
#define DsDsTRUE		1
#define DsDsFALSE		0

#define DsNULL 0

#endif //_INCLUDED_TYPE_DEF_H_
