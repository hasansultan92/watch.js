const ffi = require("ffi-napi")
const path = require("path")
const callbackFunc = require("./generalFuncs")

const libdir = path.join(__dirname, path.normalize('../build/libwat4h.dylib'))
console.log(libdir)
const library = ffi.Library(libdir, {
    'EventEmitter_new': ['pointer', ['string']],
    'EventEmitter_addObserver': ['void', ['pointer', 'pointer']],
    'EventEmitter_startMonitoring': ['void', ['pointer']]
})

const availableFunctions = library


const setEmitter = (path) => {
    return library.EventEmitter_new(`${path}`)
}

module.exports = {setEmitter, availableFunctions, callbackFunc }

