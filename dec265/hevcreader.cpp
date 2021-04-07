#include "hevcreader.h"

#include <stdlib.h>
#include <memory.h>
#include <string.h>

HevcReader::HevcReader(std::function<void ()> waitfn,  std::atomic<bool> &stop)
   : wait(waitfn)
   , head(1)
   , tail(0)
   , capacity(1024*16)
   , ringbuffer((char*)malloc(capacity))
   , fp(nullptr)//fopen("/tmp/frames.hevc", "wb")
   , _stop(stop)
{}

HevcReader::~HevcReader()
{
   free(ringbuffer);
}

int HevcReader::eof()
{
   return 0;
}

size_t HevcReader::read(void * data, size_t size)
{
   size_t copied = Remove((char*)data, size);
   return copied;
}

int HevcReader::close()
{
   if(fp) {fclose(fp);}
   return 0;
}

void HevcReader::receivedData(char *data, size_t size)
{
   if(fp) {fwrite(data, size, 1, fp);}
   Insert(data, size);
}

bool HevcReader::IsFull()
{
   return (tail == head);
}
bool HevcReader::IsEmpty()
{
   return ((head + capacity - tail) % capacity == 1);
}

size_t HevcReader::Insert(char *buffer, size_t size)
{
   size_t i;
   for(i = 0; i < size; ++i)
   {
      while(IsFull())
      {
         wait();
      }
      ringbuffer[head] = buffer[i];
      head = (head + 1) % capacity;
   }
   return i;
}

size_t HevcReader::Remove(char *buffer, size_t size)
{
   size_t copied = 0;
   for(size_t i = 0; i < size; ++i)
   {
     if(_stop)
     {
         return 0;
     }
      while(IsEmpty())
      {
         wait();
      }
       tail = (tail + 1) % capacity;
       buffer[i] = ringbuffer[tail];
       copied ++;
   }
   return copied;
}
