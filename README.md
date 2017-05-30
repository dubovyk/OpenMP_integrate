# OpenMP integral calculator

## Introduction

This is a simple tool, which shows some of the OpenMP's power by numerically calculating integral of the de Jong function for given integration boundaries and step.

## Building

To build this tool you will need simply clone this repository and build it with CMake. Alternatively, you can also import it into your favourite IDE for some debugging. Everybody loves debugging.

## Usage

To use this application you should run the application either with no arguments or with exactly 6 arguments:
- x lower integration bound
- x upper integration bound
- y lower integration bound
- y upper integration bound
- step of the integrating function
- number of threads used

After that, out.txt file will be created with the result data. Also, on the shell you'll see the amount of time spent for this calculation.

## Performance research

As the labwork task states we have conducted a small research on the performance of the OpenMP on two available PC's. On is a laptop with Intel Core i7-6700HQ (4 cores / 8 threads), 16 GiB DDR4 2333 MHz RAM and another is a laptop with Intel Core i3-4010U with 2 cores/4 threads and with 4 GiB of DDR3 1333 MHz RAM. 

According to our research, the best performance is shown best performance for 12 threads case on the Intel Core i7-6700HQ processor, which has 8 hardware threads. It's average (of 5 launches) time to calculate integral in range [0 < x < 10] and [0 < y < 10] was about 1485 milliseconds. On the other hand, Intel Core i3-4300 CPU with 4 hardware threads shows the best performance in case of using 5 threads respectively. And this time for the given test case was 3186 milliseconds.

#### A word on methodology

Both computers were run under Ubuntu 16.04 LTS and compiled with -O3 optimization level with g++ 5.4.0.

To avoid caching and some other things that could influence performance (1st launch -- slow, others -- faster), we conducted the testing during the day of usual use ot the laptops. That allowed to reduce OS and hardware optimizations influence.

Also, it's important to remember, that an major difference in the performance could be influenced by different clock rates as Core i7-6700HQ has basic rate of 2.5GHz and maximal about 3.5GHz and Intel Core i3-4010U clock rate is 1.7GHz. So, that also brings quite a strong difference.

## License

Copyright 2017 Sergey Dubovyk & Bondar Nina

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.