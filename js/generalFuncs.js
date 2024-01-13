const ffi = require("ffi-napi")
const constants = require("./definitions")


const getRandomNum = (maxNumber) => {
    return Math.floor(Math.random() * maxNumber);
}

const tagDirEvents = ffi.Callback("void", ["string", "uint32"],
    (paths, eventFlags) => {
        try {
            let EventClassification = getRandomNum(3 + 1) // Randomize from the eventClassificationEnum
            if (eventFlags & constants.kFSEventStreamEventFlagItemRemoved) {
                EventClassification = constants.EventClassificationEnum.Deleted
            }
            if (eventFlags & constants.kFSEventStreamEventFlagItemModified) {
                EventClassification = constants.EventClassificationEnum.Modified
            }
            if (eventFlags & constants.kFSEventStreamEventFlagItemCreated) {
                EventClassification = constants.EventClassificationEnum.Created
            }
            if (eventFlags & constants.kFSEventStreamEventFlagItemRenamed) {
                EventClassification = constants.EventClassificationEnum.Renamed
            }
            console.log(
                EventClassification == 0 ? "Created" :
                    EventClassification == 1 ? "Modified" :
                        EventClassification == 2 ? "Renamed" :
                            EventClassification == 3 ? "Deleted" : null,
                "@", paths);
            return EventClassification
        } catch (e) {
            console.log(e)
            return;
        }
    });

module.exports = tagDirEvents