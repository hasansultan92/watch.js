#include "consts.h"

int main()
{
    const char *defaultPath = "/Users/hasansultan/Downloads"; // Adjust the default path as needed
    EventEmitter *emitter = EventEmitter_new(defaultPath);
    EventEmitter_addObserver(emitter, tagDirEvent);
    EventEmitter_startMonitoring(emitter);

    return 0;
}