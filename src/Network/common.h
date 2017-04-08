
#pragma once

#include "../../lib/freeglut/include/freeglut.h"
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "Timer.h"

template<typename T>
std::vector<T*> copy_vector(std::vector<std::unique_ptr<T>>& pointers)
{
    std::vector<T*> copies(pointers.size());
    for (auto i = 0; i < pointers.size(); ++i)
       copies[i] = pointers[i].get();
    return copies;
}
