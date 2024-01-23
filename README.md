# wat4hjs [![npm version](https://img.shields.io/npm/v/wat4hjs.svg?style=flat-square)](https://www.npmjs.com/package/wat4hjs)

1. What:
wat4hjs is a JavaScript wrapper for native C code that allows some code to "watch" a directory for changes. Changes can include:
   1. Creation of files
   1. Modification of files
   1. Renaming of files
   1. Deletion of files
1. Why: 
At the time of writing this, most libraries and packages that existed did not include the functionality I was looking for. In most cases they would either be a platform abstraction layer or perhaps, not run the code natively. This package is a wrapper to a C library that is shipped as part of the package.
1. When:
The first commit was featured in January of 2024, continued support expected.
1. Who: [Contributors](#contributors)
1. How: (Insert Diagramatic representation)

## Index

1. [Title](#wat4hjs)
1. [Features](#features)
1. [Supported Platforms](#supported-platforms)
1. [Dependencies](#dependencies)
1. [Installation](#installation)
1. [Usage Example](#usage)
1. [History](#history)
1. [Other packages](#other-packages)
1. [Contributors](#contributors)

## Features 

## Supported Platforms
![macOS](https://img.shields.io/badge/macOS-10.7%2B-0047AB?logo=apple&style=flat-square)

## Dependencies
## Installation & Building
Using npm (JavaScript only)

```zsh 
npm install wat4hjs
```

To build the C library, adhere to the following
```zsh
mkdir -p build
cd build
cmake .. 
```

* Please note that by default a production build will be enabled in cmake, to enable a debug build, please enable debug with the debug flag
* By default wat4hjs on npm ships with a production copy of the library for the supported platform


## Usage
For users who want to to interface using JavaScript
```javascript
const wat4h = require("wat4hjs")
const path = require("path")

const emitter = wat4h.init(path.normalize("/"))
wat4h.observer(emitter, wat4h.callback) // Inform the observer
wat4h.monitor(emitter) // Start monitoring
```

Using destructured assignments
```javascript
const {init, observer, monitor, callback} = require("wat4hjs")
const path = require("path")

const emitter = wat4h.init(path.normalize("/"))
wat4h.observer(emitter, wat4h.callback) // Inform the observer
wat4h.monitor(emitter) // Start monitoring
```

If you want to use the C library natively
```C
#include "consts.h"

int main()
{
    const char *defaultPath = ""; // Adjust the default path as needed
    EventEmitter *emitter = init(defaultPath);
    observer(emitter, tagDirEvent); // Inform the observer
    monitor(emitter); // Start monitoring

    return 0;
}
```
<!-- Destructuring assignments -->
## History
## Other packages
1. [Chokidar](https://www.npmjs.com/package/chokidar?activeTab=readme)
1. [libuv](https://github.com/libuv/libuv)
## Contributors
