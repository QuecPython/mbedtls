
#include "../../../include/mbedtls/threading.h"
#include "helios_os.h"

/*
 * Thread porting based on QL_RTOS.
 */
void mbedtls_port_threading_mutex_init(mbedtls_threading_mutex_t * mutex)
{
	if(mutex)
	{
        mutex->mutex = Helios_Mutex_Create();
		mutex->is_valid = !!mutex->mutex;
	}
}

void mbedtls_port_threading_mutex_free(mbedtls_threading_mutex_t * mutex)
{
	if(mutex)
	{
        Helios_Mutex_Delete(mutex->mutex);
		mutex->is_valid = 0;
	}
}

int mbedtls_port_threading_mutex_lock(mbedtls_threading_mutex_t * mutex)
{
	if(mutex)
	{
        return Helios_Mutex_Lock(mutex->mutex, HELIOS_WAIT_FOREVER);
	}

	return -1;
}

int mbedtls_port_threading_mutex_unlock(mbedtls_threading_mutex_t * mutex)
{
	if(mutex)
	{
        Helios_Mutex_Unlock(mutex->mutex);
		return 0;
	}

	return -1;
}

void mbedtls_port_threading_exit(int status)
{
	(void)status;
	Helios_Thread_Exit();
}

