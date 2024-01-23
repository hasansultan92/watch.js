const ffi = require("ffi-napi")
const path = require("path")
const callbackFunc = require("./generalFuncs")
const os = require("os")

if (os.platform() != 'darwin') {
    console.error("This package is not compatible with this platform")
    process.exit(1)
}

const libdir = path.join(__dirname, path.normalize('../build/libwat4h.dylib'))
console.log("C library location: ", libdir)
const library = ffi.Library(libdir, {
    'init': ['pointer', ['string']],
    'observer': ['void', ['pointer', 'pointer']],
    'monitor': ['void', ['pointer']]
})

const availableFunctions = library


const setEmitter = (path) => {
    return library.init(`${path}`)
}
exports.observer = library.observer
exports.init = setEmitter
exports.monitor = library.monitor
exports.callback = callbackFunc


