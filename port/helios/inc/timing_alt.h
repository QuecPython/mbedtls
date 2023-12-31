
#ifndef MBEDTLS_TIMING_ALT_H
#define MBEDTLS_TIMING_ALT_H

#if defined (PLAT_Qualcomm)
#include <time.h>
time_t qual_mbedtls_time(time_t *t);
#endif
/**
 * \brief          timer structure
 */
struct mbedtls_timing_hr_time
{
    unsigned char opaque[32];
};

/**
 * \brief          Context for mbedtls_timing_set/get_delay()
 */
typedef struct mbedtls_timing_delay_context
{
    struct mbedtls_timing_hr_time   timer;
    unsigned int                    int_ms;
    unsigned int                    fin_ms;
} mbedtls_timing_delay_context;

#endif

