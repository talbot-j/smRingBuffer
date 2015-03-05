/**********************************************************************
*	TEST FOR: Small storage Ring Buffer - max storage size of 256 bytes (uint8_t)
*	
*	Author: Joshua Talbot
*	Date: 5-MAR-2015
*	Revision: 1.0
*	Soruce:  https://github.com/talbot-j ... T.B.D. ...
	
	Purpose:
		Test the functionality of the small ring buffer code.  Use/modify 
		this to test any changes to the smRingBuffer.c, smRingBuffer.h 
		source files.

	Usage:
		Tested using (on Linux with gcc installed):
			Requires: smRingBuffer_TEST.c, smRingBuffer.c smRingBuffer.h in same folder.
				Compile, type-> gcc -c smRingBuffer_TEST.c smRingBuffer.c
				Link, type-> gcc -o smRingBuffer smRingBuffer_TEST.o smRingBuffer.o
				Then execute, type-> ./smRingBuffer_TEST

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
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "smRingBuffer.h"

uint8_t data = 0;

void Write_data_in_buffer(ringBuffer_t *buf, uint8_t data)
{
	if ( RingBuffer_Full(buf) != 1 ) {
		printf("Just wrote %d into an available element.\n", data);
		RingBuffer_Write(buf, data);
	}
	else 
	{
		printf("!!!Buffer FULL!  Dropped data = %d!!!\n", data);
	}
}

uint8_t Read_data_in_buffer( ringBuffer_t *buf )
{
	uint8_t readData = 0;
	if ( RingBuffer_Empty(buf) != 1 ) {
		readData = RingBuffer_Read(buf);
		printf("Used \"Read_data_in_buffer\" to read element, data = %d\n", readData);
	}
	else 
	{
		printf("!!!Used \"Read_data_in_buffer\" to read element, but Buffer EMPTY!!!\n");
	}
	return readData;
}

void Test_Block_Write(ringBuffer_t *buf, uint8_t block_size, uint8_t data)
{
	uint8_t idx;

	for ( idx = 0; idx < block_size; idx++ )
	{
		Write_data_in_buffer( buf, data);
		data++;
	}
}

int main ( void )
{
	uint8_t bufferA[11];
	uint8_t bufferB[22];
	ringBuffer_t ringBufferA;
	ringBuffer_t ringBufferB;
	ringBuffer_t *pRingBuffer;

	uint8_t *pBufferA = bufferA;
	pRingBuffer = &ringBufferA;
	RingBuffer_Init(pRingBuffer, pBufferA, sizeof(bufferA));

	uint8_t *pBufferB = bufferB;
	pRingBuffer = &ringBufferB;
	RingBuffer_Init(pRingBuffer, pBufferB, sizeof(bufferB));

	pRingBuffer = &ringBufferA;
	printf("Available space in RingBuffer A: %d\n", RingBuffer_Avail_Space(pRingBuffer));

	pRingBuffer = &ringBufferB;
	printf("Available space in RingBuffer B: %d\n", RingBuffer_Avail_Space(pRingBuffer));
	printf("Ring buffer empty? %d\n", RingBuffer_Empty(pRingBuffer));
	printf("Ring buffer full? %d\n", RingBuffer_Full(pRingBuffer));
	printf("Ring buffer available space? %d\n", RingBuffer_Avail_Space(pRingBuffer));
	printf("Ring buffer available data? %d\n", RingBuffer_Avail_Data(pRingBuffer));

	uint8_t writeNum = 26;
	printf("Using \"Write_data_in_buffer()\" to write %d into an available buffer element.\n", writeNum);
	Write_data_in_buffer(pRingBuffer, writeNum);
	printf("Ring buffer available space? %d\n", RingBuffer_Avail_Space(pRingBuffer));
	printf("Ring buffer available data? %d\n", RingBuffer_Avail_Data(pRingBuffer));

	uint8_t readNum = Read_data_in_buffer(pRingBuffer);
	if( readNum == writeNum) printf("Read/Write Pairing was a sucess!\n");
	else (printf("Read/Write Pairing FAILED!!!\n"));
	printf("Ring buffer available space? %d\n", RingBuffer_Avail_Space(pRingBuffer));
	printf("Ring buffer available data? %d\n", RingBuffer_Avail_Data(pRingBuffer));

	writeNum = 1;
	uint8_t block_size = 8;
	printf("Use \"Test_Block_Write()\" to write %d sequencial data starting at value = %d\n", block_size, writeNum);
	Test_Block_Write(pRingBuffer, block_size, writeNum);
	uint8_t	idx;
	for ( idx = 0; idx < block_size; idx++)
	{
		Read_data_in_buffer(pRingBuffer);
	}

	writeNum = 100;
	block_size = 25;
	printf("Use \"Test_Block_Write()\" to write %d sequencial data starting at value = %d\n", block_size, writeNum);
	Test_Block_Write(pRingBuffer, block_size, writeNum);
	printf("Ring buffer available space? %d\n", RingBuffer_Avail_Space(pRingBuffer));
	printf("Ring buffer available data? %d\n", RingBuffer_Avail_Data(pRingBuffer));
	for ( idx = 0; idx < block_size; idx++)
	{
		Read_data_in_buffer(pRingBuffer);
	}
	printf("Ring buffer available space? %d\n", RingBuffer_Avail_Space(pRingBuffer));
	printf("Ring buffer available data? %d\n", RingBuffer_Avail_Data(pRingBuffer));

	writeNum = 100;
	block_size = 5;
	printf("Use \"Test_Block_Write()\" to write %d sequencial data starting at value = %d\n", block_size, writeNum);
	Test_Block_Write(pRingBuffer, block_size, writeNum);
	printf("Ring buffer available space? %d\n", RingBuffer_Avail_Space(pRingBuffer));
	printf("Ring buffer available data? %d\n", RingBuffer_Avail_Data(pRingBuffer));
	RingBuffer_Flush(pRingBuffer);
	printf("Flushing buffer!  It should now be empty and the next reads should all fail.\n");
	printf("Ring buffer available space? %d\n", RingBuffer_Avail_Space(pRingBuffer));
	printf("Ring buffer available data? %d\n", RingBuffer_Avail_Data(pRingBuffer));
	for ( idx = 0; idx < block_size; idx++)
	{
		Read_data_in_buffer(pRingBuffer);
	}

	uint8_t *ptrNum = &writeNum;
	block_size = 25;
	printf("Use \"RingBuffer_pWrite()\" to write data = %d\n", *ptrNum);
	RingBuffer_pWrite(pRingBuffer, ptrNum);
	Read_data_in_buffer(pRingBuffer);

	return 0;
}