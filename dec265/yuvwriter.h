#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <functional>

#ifdef __cplusplus
extern "C" {
#endif

struct YuvWriter
{
   YuvWriter(std::function<void (const uint8_t* data, size_t size)> yuvFrame);
   ~YuvWriter();

   void open();
   size_t write(const uint8_t* data, int size);
   int close();

   FILE *fp;
   uint8_t *FrameData;
   size_t FrameSize;
   std::function<void (const uint8_t* data, size_t size)> YuvFrame;
};

#ifdef __cplusplus
}
#endif
