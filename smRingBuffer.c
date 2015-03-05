/**********************************************************************
*	Small storage Ring Buffer - max storage size of 256 bytes (uint8_t)
*	
*	Author: Joshua Talbot
*	Date: 5-MAR-2015
*	Revision: 1.0
*	Soruce:  https://github.com/talbot-j ... T.B.D. ...
	
	For a brief description and usage information see the header file.

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
*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "smRingBuffer.h"
#include <stdint.h>

/*
	RingBuffer_Init - required to initalize the buffer.
*/
void RingBuffer_Init ( ringBuffer_t *buf, uint8_t *data, uint8_t size)
{
	buf->size = size;
	buf->data = data;
	buf->head = 0;
	buf->tail = 0;
	buf->read_count = 0;
	buf->write_count = 0;
}

/*
*	RingBuffer_Read - read the next element in the buffer.
*	!WARNING! Be sure to check that the buffer is not empty.
*/
uint8_t RingBuffer_Read ( ringBuffer_t *buf )
{
	/* read the data from the buffer */
	uint8_t readData = buf->data[buf->tail];
	/* setup for the next read: inc the read count and the tail index */
	buf->read_count++;
	if( ++buf->tail == buf->size) 
		buf->tail =0;
	/* leaveing with the data */
	return readData;
}

/*
*	RingBuffer_Write - write an element into the buffer location.
*	!WARNING! Be sure to check prior to using this function
*	 that the buffer is not FULL.
*/
void RingBuffer_Write ( ringBuffer_t *buf, uint8_t data )
{
	/* write the data to the buffer */
	buf->data[buf->head] = data;
	/* setup for the next write: inc the write count and the head index */
	buf->write_count++;
	if( ++buf->head == buf->size) 
		buf->head =0;
}

/*
*	RingBuffer_pWrite - write an element into the buffer location.
*	A pointer is passed to the value that needs to be added.
*	!WARNING! Be sure to check prior to using this function
*	 that the buffer is not FULL.
*/
void RingBuffer_pWrite ( ringBuffer_t *buf, uint8_t *pData )
{
	/* write the data to the buffer */
	buf->data[buf->head] = *pData;
	/* setup for the next write: inc the write count and the head index */
	buf->write_count++;
	if( ++buf->head == buf->size) 
		buf->head =0;
}

/*
*	RingBuffer_Flush - flushes all data in the buffer and
* 	resets the read/write counts.
*/
void RingBuffer_Flush ( ringBuffer_t *buf )
{
	buf->head = 0;
	buf->tail = 0;
	buf->read_count = 0;
	buf->write_count = 0;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */