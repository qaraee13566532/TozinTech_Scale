/*
  MedianFilter.h - Median Filter for the Arduino platform.
  Copyright (c) 2013 Phillip Schmidt.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
   A median filter object is created by by passing the desired filter window size on object creation.
   The window size should be an odd number between 3 and 255.

   New data is added to the median filter by passing the data through the in() function.  The new medial value is returned.
   The new data will over-write the oldest data point, then be shifted in the array to place it in the correct location.

   The current median value is returned by the out() function for situations where the result is desired without passing in new data.

   !!! All data must be type INT.  !!!
 */

#pragma once

class MedianFilter
{
public:
   MedianFilter(long size, long seed);
   MedianFilter()
   {
   }
   ~MedianFilter();
   long in(long value);
   long out();

   long getMin();
   long getMax();
   long getMean();
   long getStDev();
   unsigned char Constrain(unsigned char value, unsigned char min_val, unsigned char max_val);

private:
   unsigned char medFilterWin;   // number of samples in sliding median filter window - usually odd #
   unsigned char medDataPointer; // mid point of window
   long *data;
   long *sortedData;              // array pointer for data sorted by age in ring buffer
   unsigned char *sizeMap;        // array pointer for locations data in sorted by size
   unsigned char *locationMap;    // array pointer for data locations in history map
   unsigned char oldestDataPoint; // oldest data point location in ring buffer
   long totalSum;
};
