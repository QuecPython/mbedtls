
#ifndef MBEDTLS_FS_ALT_H
#define MBEDTLS_FS_ALT_H

#include "helios_fs.h"

#ifdef FILE
#undef FILE
#endif
#define FILE HeliosFILE

#define PerlIO_error(f) 0

#ifdef fopen
#undef fopen
#endif
#define fopen Helios_fopen

#ifdef fwrite
#undef fwrite
#endif
#define fwrite Helios_fwrite

#ifdef fread
#undef fread
#endif
#define fread Helios_fread

#ifdef fputc
#undef fputc
#endif
#define fputc Helios_fputc

#ifdef fputs
#undef fputs
#endif
#define fputs Helios_fputs

#ifdef fprintf
#undef fprintf
#endif
#define fprintf Helios_fprintf

#ifdef fgetc
#undef fgetc
#endif
#define fgetc Helios_fgetc

#ifdef fgets
#undef fgets
#endif
#define fgets Helios_fgets

#ifdef fscanf
#undef fscanf
#endif
#define fscanf Helios_fscanf

#ifdef fseek
#undef fseek
#endif
#define fseek Helios_fseek

#ifdef ftell
#undef ftell
#endif
#define ftell Helios_ftell

#ifdef frewind
#undef frewind
#endif
#define frewind Helios_frewind

#ifdef fsize
#undef fsize
#endif
#define fsize Helios_fsize

#ifdef fclose
#undef fclose
#endif
#define fclose Helios_fclose

#endif

