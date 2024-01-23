#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATH_LENGTH 256

#if defined(__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#endif

#if defined(__WIN32)
#endif

typedef enum
{
    Created = 0,
    Modified = 1,
    Renamed = 2,
    Deleted = 3
} events;

events tagDirEvent(
    char *paths,
    const FSEventStreamEventFlags);

typedef events (*EventObserverCallback)(
    char *paths,
    const FSEventStreamEventFlags);

typedef struct EventObserver
{
    EventObserverCallback callback;
    struct EventObserver *next;
} EventObserver;

typedef struct EventEmitter
{
    char directory[MAX_PATH_LENGTH];
    EventObserver *observers;
    FSEventStreamRef fsEventStream;
} EventEmitter;

EventEmitter *init(const char *directory);
void observer(EventEmitter *emitter, EventObserverCallback callback);
void monitor(EventEmitter *emitter);
