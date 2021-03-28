#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "updatable_priority_queue.h"
#define NLINKS 100000000 //maximum number of edges for memory allocation, will increase if needed

using namespace std;


inline unsigned long max3(unsigned long a, unsigned long b, unsigned long c) {
	a = (a > b) ? a : b;
	return (a > c) ? a : c;
}

struct Edge
{
	unsigned long s;
	unsigned long t;
};