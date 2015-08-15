#ifndef _INCLUDED_DS_COMMON_H_
#define _INCLUDED_DS_COMMON_H_

#include "typedef.h"

//#if defined(_WINDOWS) || defined(WIN32)
#include <windows.h>
//#define DS_EXPORT __declspec(dllexport)
//#else
//#define DS_EXPORT
//#endif

#include <stdlib.h>

#define DECLARE_CLASS_NAME(class_name) const DsSTR szNameOfClass##class_name = #class_name;
#define ASSIGN_CLASS_NAME(class_name) m_pClassName = szNameOfClass##class_name;

typedef UINT32 DsRESULT;

const DsRESULT ERROR_OK				= 0X00000000;
const DsRESULT ERROR_OUT_OF_MEMORY	= 0X00000001;

#endif //_INCLUDED_DS_COMMON_H_