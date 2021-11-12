
#include "../../../port/helios/inc/timing_alt.h"
#include "helios_os.h"
#include <time.h>
#include <stdint.h>
#if defined (PLAT_Qualcomm)
#include "helios_rtc.h"
#endif

#if defined (PLAT_ASR) || defined (PLAT_Qualcomm)
struct timeval { 
	int tv_sec; 
	int tv_usec;
};
#endif

#if !defined (PLAT_Qualcomm)
extern int gettimeofday(struct timeval *tv, void *tz);
#endif

struct _hr_time
{
    struct timeval start;
};

static int hardclock_init = 0;
static struct timeval tv_init;

#if defined (PLAT_Qualcomm)
void qual_gettimeofday(struct timeval *tv, void *tz)
{
	(void)tz;
	unsigned long system_uptime = Helios_RTC_GetTicks();
	tv->tv_sec = system_uptime/1000;
	tv->tv_usec = (system_uptime%1000)*1000;
}
time_t qual_mbedtls_time(time_t *t)
{
	(void)t;
    return (time_t)Helios_RTC_GetSecond();
}
#endif

unsigned long mbedtls_timing_hardclock( void )
{
    struct timeval tv_cur;

    if( hardclock_init == 0 )
    {
#if defined (PLAT_Qualcomm)
		qual_gettimeofday( &tv_init, NULL );
#else
		gettimeofday( &tv_init, NULL );

#endif
        hardclock_init = 1;
    }
#if defined (PLAT_Qualcomm)
	qual_gettimeofday( &tv_cur, NULL ); 
#else
	gettimeofday( &tv_cur, NULL );
#endif
    return( ( tv_cur.tv_sec  - tv_init.tv_sec  ) * 1000000
          + ( tv_cur.tv_usec - tv_init.tv_usec ) );
}

unsigned long mbedtls_timing_get_timer( struct mbedtls_timing_hr_time *val, int reset )
{
    struct _hr_time *t = (struct _hr_time *) val;

    if( reset )
    {
#if defined (PLAT_Qualcomm)
		qual_gettimeofday( &t->start, NULL );   
#else
		gettimeofday( &t->start, NULL );
#endif
        return( 0 );
    }
    else
    {
        unsigned long delta;
        struct timeval now;
#if defined (PLAT_Qualcomm)
		qual_gettimeofday( &now, NULL );
#else
		gettimeofday( &now, NULL );
#endif
        delta = ( now.tv_sec  - t->start.tv_sec  ) * 1000ul
              + ( now.tv_usec - t->start.tv_usec ) / 1000;
        return( delta );
    }
}

volatile int mbedtls_timing_alarmed = 0;

static void alarmhandler(void *argv)
{
    (void)argv;
	mbedtls_timing_alarmed = 1;
}

int mbedtls_set_alarm( int seconds )
{
	Helios_OSTimer_t alarm = 0;

	mbedtls_timing_alarmed = 0;

	if(seconds == 0)
	{
		mbedtls_timing_alarmed = 1;
		return 0;
	}

    Helios_OSTimerAttr OSTimerAttr = 
	{
        .ms = seconds * 1000,
        .cycle_enable = 0,
        .cb = alarmhandler,
        .argv = NULL
    };

    alarm = Helios_OSTimer_Create();
    Helios_OSTimer_Start(alarm, &OSTimerAttr);
	return ( int )alarm;
}

void mbedtls_free_alarm( int alarm )
{
	if(alarm) Helios_OSTimer_Delete((Helios_OSTimer_t)alarm);
}

void mbedtls_timing_set_delay( void *data, uint32_t int_ms, uint32_t fin_ms )
{
    mbedtls_timing_delay_context *ctx = (mbedtls_timing_delay_context *) data;

    ctx->int_ms = int_ms;
    ctx->fin_ms = fin_ms;

    if( fin_ms != 0 )
        (void) mbedtls_timing_get_timer( &ctx->timer, 1 );
}

int mbedtls_timing_get_delay( void *data )
{
    mbedtls_timing_delay_context *ctx = (mbedtls_timing_delay_context *) data;
    unsigned long elapsed_ms;

    if( ctx->fin_ms == 0 )
        return( -1 );

    elapsed_ms = mbedtls_timing_get_timer( &ctx->timer, 0 );

    if( elapsed_ms >= ctx->fin_ms )
        return( 2 );

    if( elapsed_ms >= ctx->int_ms )
        return( 1 );

    return( 0 );
}

