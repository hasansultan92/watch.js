#include "consts.h"

int main()
{
    const char *defaultPath = "/Users/hasansultan/Downloads"; // Adjust the default path as needed
    EventEmitter *emitter = init(defaultPath);
    observer(emitter, tagDirEvent);
    monitor(emitter);

    return 0;
}