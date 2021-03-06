/*=========================================================================

  Program:   OpenIGTLink Library
  Module:    $HeadURL: $
  Language:  C
  Date:      $Date: 2010-11-23 14:47:40 -0500 (Tue, 23 Nov 2010) $
  Version:   $Revision: 6958 $

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __IGTL_CAPABILITY_H
#define __IGTL_CAPABILITY_H

#include "igtl_win32header.h"
#include "igtl_util.h"
#include "igtl_types.h"
#include "igtl_win32header.h"

#define IGTL_CAPABILITY_HEADER_SIZE          4

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  igtl_uint32      ntypes;
  unsigned char ** typenames;
} igtl_capability_info;


/*
 * Initialize igtl_ndarray_info
 */
void igtl_export igtl_capability_init_info(igtl_capability_info * info);


/*
 * Allocate / free ndarray info
 *
 * Allocate size array and ND-array pointed from igtl_ndarray_info.
 * 'type' and 'dim' in igtl_ndarray_info must be specified before
 * calling igtl_ndarray_alloc_info().
 */

int igtl_export igtl_capability_alloc_info(igtl_capability_info * info, int ntypes);
int igtl_export igtl_capability_free_info(igtl_capability_info * info);


/*
 * Calculate capability data size
 *
 * This function calculates size of the pixel array, which will be
 * transferred with the specified header.
 */

igtl_uint32 igtl_export igtl_capability_get_length(igtl_capability_info * info);


/*
 * Unpack CAPABILITY message
 *
 * Extract information in a byte array of CAPABILITY messages and store
 * it in a igtl_capability_info structure. 'type' argument specifies
 * a message type prefix (none, GET_, STT_, STP_ or RTS_) by IGTL_TYPE_PREFIX_* macro.
 * Returns 1 if success, otherwise 0.
 */

int igtl_export igtl_capability_unpack(void * byte_array, igtl_capability_info * info, igtl_uint64 pack_size);


/*
 * Pack CAPABILITY message
 *
 * Convert an igtl_capability_info structure to a byte array. 
 * 'byte_array' should be allocated prior to calling igtl_capability_pack() with memory size
 * calculated by igtl_capability_get_size(). 'type' argument specifies a message type prefix
 * (none, or GET_) by IGTL_TYPE_PREFIX_* macro. Returns 1 if success, otherwise 0.
 */

int igtl_export igtl_capability_pack(igtl_capability_info * info, void * byte_array);


/*
 * CRC calculation
 *
 * This function calculates CRC of image data body including header
 * and array of pixel data.
 *
 */

igtl_uint64 igtl_export igtl_capability_get_crc(igtl_capability_info* info, void* capability);

#ifdef __cplusplus
}
#endif

#endif /* __IGTL_CAPABILITY_H */




