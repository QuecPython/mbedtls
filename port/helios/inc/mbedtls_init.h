
#ifndef _MBEDTLS_INIT_H_
#define _MBEDTLS_INIT_H_

#include "../../../include/mbedtls/platform.h"

int mbedtls_platform_setup( mbedtls_platform_context *ctx );
void mbedtls_platform_teardown( mbedtls_platform_context *ctx );

#endif
