****************************************************************************
Small storage Ring Buffer - max storage size of 256 bytes (uint8_t)
****************************************************************************
Author: Joshua Talbot
Date: 5-MAR-2015
Revision: 1.0
Soruce:  https://github.com/talbot-j ... T.B.D. ...

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
