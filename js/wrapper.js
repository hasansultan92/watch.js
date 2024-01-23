const wat4hjs = require('./init') // wat4h lib init
const functions = require('./generalFuncs')

if (!process.argv[2]) {
    console.log(process.argv)
    process.exit(1)
}
const emitter = wat4hjs.init(process.argv[2])
wat4hjs.observer(emitter, functions)
wat4hjs.monitor(emitter)
