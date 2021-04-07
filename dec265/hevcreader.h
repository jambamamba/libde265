#pragma once

#include <atomic>
#include <stdlib.h>
#include <stdint.h>
#include <functional>

struct HevcReader
{
   HevcReader(std::function<void ()> waitfn,  std::atomic<bool> &stop);
   ~HevcReader();
   int eof();
   size_t read(void * data, size_t size);
   int close();

   void receivedData(char *data, size_t size);
   std::function<void ()> wait;
    std::atomic<bool> &_stop;

   bool IsFull();
   bool IsEmpty();
   size_t Insert(char *buffer, size_t size);
   size_t Remove(char *buffer, size_t size);

   size_t head;
   size_t tail;
   size_t capacity;
   char *ringbuffer;

   FILE *fp;
};

