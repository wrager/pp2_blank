#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <memory>

template <typename T>
bool IsBetween(const T& value, const T& lowerBound, const T& upperBound)
{
	return (value >= lowerBound) && (value <= upperBound);
}