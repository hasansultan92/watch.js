#include "consts.h"

events tagDirEvent(
    char *paths,
    const FSEventStreamEventFlags eventFlags)
{
    events EventClassification;
    if (eventFlags & kFSEventStreamEventFlagItemCreated)
    {
        EventClassification = Created;
#ifdef DEBUG
        printf("File created: %s\n", paths);
#endif
    }
    if (eventFlags & kFSEventStreamEventFlagItemRemoved)
    {
        EventClassification = Deleted;
#ifdef DEBUG
        printf("File deleted: %s\n", paths);
#endif
    }
    if (eventFlags & kFSEventStreamEventFlagItemModified)
    {
        EventClassification = Modified;
#ifdef DEBUG
        printf("File Modified: %s\n", paths);
#endif
    }
    if (eventFlags & kFSEventStreamEventFlagItemRenamed)
    {
        EventClassification = Renamed;
#ifdef DEBUG
        printf("File Renamed: %s\n", paths);
#endif
    }
    return EventClassification;
}

void handleFSEvent(
    ConstFSEventStreamRef streamRef,
    void *clientCallBackInfo,
    size_t numEvents,
    void *eventPaths,
    const FSEventStreamEventFlags eventFlags[],
    const FSEventStreamEventId eventIds[])
{
    EventEmitter *emitter = (EventEmitter *)clientCallBackInfo;

    int EventClassification;
    char **paths = eventPaths;
    for (size_t i = 0; i < numEvents; i++)
    {
        for (EventObserver *observer = emitter->observers; observer != NULL; observer = observer->next)
        {
            observer->callback(paths[i], eventFlags[i]);
        }
    }
}

EventEmitter *EventEmitter_new(const char *directory)
{
    EventEmitter *emitter = (EventEmitter *)malloc(sizeof(EventEmitter));
    strncpy(emitter->directory, directory, sizeof(emitter->directory) - 1);
    emitter->observers = NULL;

    CFStringRef path = CFStringCreateWithCString(NULL, directory, kCFStringEncodingUTF8);
    CFArrayRef pathsToWatch = CFArrayCreate(NULL, (const void **)&path, 1, NULL);

    FSEventStreamContext context = {0, emitter, NULL, NULL, NULL};
    emitter->fsEventStream = FSEventStreamCreate(
        NULL,
        &handleFSEvent,
        &context,
        pathsToWatch,
        kFSEventStreamEventIdSinceNow,
        0,
        kFSEventStreamCreateFlagFileEvents);

    CFRelease(path);
    CFRelease(pathsToWatch);

    return emitter;
}

void EventEmitter_addObserver(EventEmitter *emitter, EventObserverCallback callback)
{
    EventObserver *newObserver = (EventObserver *)malloc(sizeof(EventObserver));
    newObserver->callback = callback;
    newObserver->next = emitter->observers;
    emitter->observers = newObserver;
}

void EventEmitter_startMonitoring(EventEmitter *emitter)
{
    FSEventStreamScheduleWithRunLoop(emitter->fsEventStream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
    FSEventStreamStart(emitter->fsEventStream);
    CFRunLoopRun();
}
