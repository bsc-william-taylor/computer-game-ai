
/**
*
* Copyright 2015 : William Taylor : wi11berto@yahoo.co.uk
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* 	http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef __TIMER_H__
#define __TIMER_H__

#include <Windows.h>
#include <iostream>

class Timer {
	// the freq of the processor
	static double frequency;
	// the amount of ticks at the start time
	static __int64 counterStart;
public:
	// A simple static function to start the timer
	static void start() {
		// Get the performance frequency
		LARGE_INTEGER li;
		QueryPerformanceFrequency(&li);
		frequency = double(li.QuadPart) / 1000.0;
		// Then get the current amount of ticks
		QueryPerformanceCounter(&li);
		counterStart = li.QuadPart;
	} 

	// A simple static function to stop the timer & return the resul
	static double stop() {
		// We get the current amount of ticks
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		// subtract the 2 ticks and divide by frequency to return time passed in ms
		return double(li.QuadPart - counterStart) / frequency;
	}
};

#endif