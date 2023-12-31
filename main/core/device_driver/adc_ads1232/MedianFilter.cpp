/*
   MedianFilter.cpp - Median Filter for the Arduino platform.
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
   License aint32_t with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
    A median filter object is created by by passing the desired filter window size on object creation.
   The window size should be an odd number between 3 and 255.

   New data is added to the median filter by passing the data through the in() function.  The new medial value is returned.
   The new data will over-write the oldest data point, then be shifted in the array to place it in the correct location.

   The current median value is returned by the out() function for situations where the result is desired without passing in new data.

   !!! All data must be type INT.  !!!

   Window Size / avg processing time [us]
   5  / 22
   7  / 30
   9  / 40
   11 / 49
   21 / 99

*/

#include "core/device_driver/adc_ads1232/MedianFilter.h"
#include "stdlib.h"
#include "math.h"
#include <iostream>

uint8_t MedianFilter::Constrain(uint8_t value, uint8_t min_val, uint8_t max_val)
{
   if (value < min_val)
      value = min_val;

   else
   {
      if (value > max_val)
         value = max_val;
   }
   return value;
}

MedianFilter::MedianFilter(int32_t size, int32_t seed)
{
   medFilterWin = Constrain(size, 3, 31); // number of samples in sliding median filter window - usually odd #
   medDataPointer = size >> 1;
   sortedData = (int32_t *)calloc(size, sizeof(long));                    // mid point16_t of window
   data = (int32_t *)calloc(size, sizeof(long));                          // array for data
   sizeMap = (uint8_t *)calloc(size, sizeof(uint8_t));     // array for locations of data in sorted list
   locationMap = (uint8_t *)calloc(size, sizeof(uint8_t)); // array for locations of history data in map list
   oldestDataPoint = medDataPointer;                                   // oldest data point16_t location in data array
   totalSum = size * seed;                                             // total of all values

   for (uint8_t i = 0; i < medFilterWin; i++) // initialize the arrays
   {
      sizeMap[i] = i;     // start map with straight run
      locationMap[i] = i; // start map with straight run
      data[i] = seed;
      sortedData[i] = seed; // populate with seed value
   }
}

MedianFilter::~MedianFilter()
{
   // Free up the used memory when the object is destroyed
   free(data);
   free(sortedData);
   free(sizeMap);
   free(locationMap);
}

int32_t MedianFilter::in(int32_t value)
{
   int32_t temp;
   uint8_t loopCounter, k, min;
   loopCounter = medFilterWin - 1;
   do
   {
      data[loopCounter] = data[loopCounter - 1];
      loopCounter--;
   } while (loopCounter > 0);
   data[0] = value;

   loopCounter = 0;
   do
   {
      sortedData[loopCounter] = data[loopCounter];
      loopCounter++;
   } while (loopCounter < medFilterWin);

   loopCounter = 0;
   do
   {
      min = loopCounter;
      k = loopCounter + 1;
      do
      {
         if (sortedData[k] < sortedData[min])
            min = k;
         k++;
      } while (k < medFilterWin);
      temp = sortedData[loopCounter];
      sortedData[loopCounter] = sortedData[min];
      sortedData[min] = temp;
      loopCounter++;
   } while (loopCounter < medFilterWin - 1);
   
   return labs(sortedData[medFilterWin - 1] - sortedData[0]);
}

int32_t MedianFilter::out() // return the value of the median data sample
{
   return sortedData[medFilterWin / 2];
}

int32_t MedianFilter::getMin()
{
   return sortedData[0];
}

int32_t MedianFilter::getMax()
{
   return sortedData[medFilterWin - 1];
}

int32_t MedianFilter::getMean()
{
   return totalSum / medFilterWin;
}

int32_t MedianFilter::getStDev() // Arduino run time [us]: filterSize * 2 + 131
{
   int32_t diffSquareSum = 0;
   int32_t mean = getMean();

   for (int32_t i = 0; i < medFilterWin; i++)
   {
      int32_t diff = sortedData[i] - mean;
      diffSquareSum += diff * diff;
   }

   return long(sqrtf(float(diffSquareSum) / float(medFilterWin - 1)) + 0.5f);
}

// *** debug fuctions ***
/*
void MedianFilter::printData() // display sorting data for debugging
{
   for(int16_t i=0; i<medFilterWin; i++)
   {
      Serial.print(data[i]);
      Serial.print("\t");
   }
   Serial.println("Data in ring buffer");
}

void MedianFilter::printSizeMap()
{
   for(int16_t i=0; i<medFilterWin; i++)
   {
      Serial.print(sizeMap[i]);
      Serial.print("\t");
   }
   Serial.println("Size Map, data sorted by size");
}

void MedianFilter::printLocationMap()
{
   for(int16_t i=0; i<medFilterWin; i++)
   {
      Serial.print(locationMap[i]);
      Serial.print("\t");
   }
   Serial.println("Location Map, size data sorted by age");
}

void MedianFilter::printSortedData() // display data for debugging
{
   for(int16_t i=0; i<medFilterWin; i++)
   {
      Serial.print(data[sizeMap[i]]);
      Serial.print("\t");
   }
   Serial.println("Data sorted by size");
}
*/
