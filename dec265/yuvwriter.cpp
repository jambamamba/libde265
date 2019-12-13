#include "yuvwriter.h"
#include <memory.h>

YuvWriter::YuvWriter(std::function<void (const uint8_t* data, size_t size)> yuvFrame)
   : fp(nullptr)
   , FrameData(nullptr)
   , FrameSize(0)
   , YuvFrame(yuvFrame)
{
   fp = fopen("/tmp/frames.yuv", "wb");
   fclose(fp);
}

YuvWriter::~YuvWriter()
{
}

void YuvWriter::open()
{
   fp = fopen("/tmp/frames.yuv", "wb");
}
size_t YuvWriter::write(const uint8_t* data, int size)
{
   FrameData = (uint8_t*) realloc(FrameData, FrameSize + size);
   memcpy(&FrameData[FrameSize], data, size);
   FrameSize += size;
   return fwrite(data, size, 1, fp);
}

int YuvWriter::close()
{
   YuvFrame(FrameData, FrameSize);
   FrameSize = 0;
   return fclose(fp);
}
