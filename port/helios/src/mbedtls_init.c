
#include "helios_debug.h"
#include "../../../port/helios/inc/threading_alt.h"
#include "../../../include/mbedtls/threading.h"
#include "../../../include/mbedtls/platform.h"
#include "../../../port/helios/inc/fs_alt.h"

/*
 * Placeholder platform setup that does nothing by default
 */
int mbedtls_platform_setup( mbedtls_platform_context *ctx )
{
    (void)ctx;

	mbedtls_threading_set_alt(
		mbedtls_port_threading_mutex_init,
		mbedtls_port_threading_mutex_free,
		mbedtls_port_threading_mutex_lock,
		mbedtls_port_threading_mutex_unlock);

	mbedtls_platform_set_exit(mbedtls_port_threading_exit);

	mbedtls_platform_set_fprintf(fprintf);

	mbedtls_platform_set_printf(Helios_Debug_Output);

	mbedtls_platform_set_snprintf(snprintf);

    return( 0 );
}

/*
 * Placeholder platform teardown that does nothing by default
 */
void mbedtls_platform_teardown( mbedtls_platform_context *ctx )
{
    (void)ctx;
}

