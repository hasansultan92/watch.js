const EventClassificationEnum = Object.freeze({
    Created: 0,
    Modified: 1,
    Renamed: 2,
    Deleted: 3
})

const kFSEventStreamEventFlagItemRemoved = 0x00000200
const kFSEventStreamEventFlagItemCreated = 0x00000100
const kFSEventStreamEventFlagItemRenamed = 0x00000800
const kFSEventStreamEventFlagItemModified = 0x00001000

module.exports = {
    kFSEventStreamEventFlagItemRemoved,
    kFSEventStreamEventFlagItemCreated,
    kFSEventStreamEventFlagItemRenamed,
    kFSEventStreamEventFlagItemModified,
    EventClassificationEnum
}
