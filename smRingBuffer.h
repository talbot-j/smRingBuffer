/**********************************************************************
*	Small storage Ring Buffer - max storage size of 256 bytes (uint8_t)
*	
*	Author: Joshua Talbot
*	Date: 5-MAR-2015
*	Revision: 1.0
*	Soruce:  https://github.com/talbot-j ... T.B.D. ...
	
	Purpose:
		This implements a thread (interrupt safe) ring buffer that utilizes
		read and write counts (see http://en.wikipedia.org/wiki/Circular_buffer)
		to insure that the producer only modifies the write count and the
		consumer only modifies the read count.  Using this insures that any 
		delay in the head and tail updates and corrections on them due to 
		overruns is avoided.  This routine was written for use on a small 
		embedded 8-bit system (hense the vast usage of the data type unit8_t).
		please keep that in mind when using.

	License:
		Copyright (C) 2015  Joshua Talbot

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Usage example:
		uint8_t dataA[10];
		ringBuffer_t bufA;  
		ringBuffer_t *pBuf;
		uint8_t *pDataA = dataA;
		pBuf = &bufA;
		RingBuffer_Init(pBuf, pDataA, sizeof(pDataA));
		uint8_t data = 1;
		if ( RingBuffer_Full(pBuf) != 1 )
		{
			printf("Just wrote %d into an available element.\n", data);
			RingBuffer_Write(pBuf, data);
		}
		else 
		{
			printf("!!!Buffer FULL!  Dropped data = %d!!!\n", data);
		}
		if ( RingBuffer_Empty(pBuf) != 1 ) {
			data = RingBuffer_Read(pBuf);
			printf("Used \"Read_data_in_buffer\" to read element, data = %d\n", data);
		}
		else 
		{
			printf("!!!Used \"Read_data_in_buffer\" to read element, but Buffer EMPTY!!!\n");
		}
*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef _SM_RINGBUFFER_H_
#define _SM_RINGBUFFER_H_

#include <stdint.h>

typedef struct {
    uint8_t *data; 				/* block of memory or array of data */
		uint8_t size;			/* the number of elements in the memory block pointed at by *data */
		uint8_t read_count; 	/* the number of reads performed on the data array */
		uint8_t write_count; 	/* the number of writes performed on the data array since inception */
    uint8_t head; 				/* current location where the writes go */
    uint8_t tail; 				/* current location where the reads come from */
} ringBuffer_t;

void RingBuffer_Init ( ringBuffer_t *buf, uint8_t *data, uint8_t size);

uint8_t RingBuffer_Empty ( ringBuffer_t const *buf );

uint8_t RingBuffer_Full ( ringBuffer_t const *buf );

uint8_t RingBuffer_Avail_Data ( ringBuffer_t const *buf );

uint8_t RingBuffer_Avail_Space ( ringBuffer_t const *buf );

uint8_t RingBuffer_Read ( ringBuffer_t *buf );

void RingBuffer_Write ( ringBuffer_t *buf, uint8_t data );

void RingBuffer_pWrite ( ringBuffer_t *buf, uint8_t *pData );

void RingBuffer_Flush ( ringBuffer_t *buf );

#define RingBuffer_Empty(B) ( ( (B)->write_count - (B)->read_count ) == 0 )

#define RingBuffer_Full(B) ( ( (B)->write_count - (B)->read_count ) >= (B)->size )

#define RingBuffer_Avail_Data(B) ( ( (B)->write_count ) - (B)->read_count )

#define RingBuffer_Avail_Space(B) ( (B)->size - RingBuffer_Avail_Data(B) )

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif