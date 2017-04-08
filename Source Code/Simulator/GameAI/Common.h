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

#ifndef __COMMON_H__
#define __COMMON_H__

#include <gl/freeglut.h>
#include <functional>
#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>

#include "Timer.h"

#pragma comment(lib, "freeglut.lib")

// Simple debug macro for printing out values to the console
#define DEBUG(str) std::cout << str << std::endl; std::cin.get();

#endif