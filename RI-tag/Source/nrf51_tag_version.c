/**
* @file nrf51_tag_version.c
* @brief Header file for tag version info.
 */

#include "nrf51_tag_error.h"
#include "nrf51_tag_version.h"

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

#define TO_STRING(x) #x
#define APP_NAME_STRING(major_, minor_, rev_)     VERSION_APP_NAME "_" TO_STRING(major_) "." TO_STRING(minor_) "." TO_STRING(rev_)
#define APP_VERSIONE_STRING(major_, minor_, rev_) TO_STRING(major_) "." TO_STRING(minor_) "." TO_STRING(rev_)

static char const strAppName[] = APP_NAME_STRING(VERSION_FW_MAJOR, VERSION_FW_MINOR, VERSION_FW_REVISION);
static char const strVersion[] = APP_VERSIONE_STRING(VERSION_FW_MAJOR, VERSION_FW_MINOR, VERSION_FW_REVISION);

char const * nrf51_tag_version_get_name(void)
{
	return strAppName;
}

char const * nrf51_tag_version_get_version(void)
{
	return strVersion;
}
