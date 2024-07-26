/** fullsendx.h - v0.0.0 - public domain

## Usage

In the single file defining `main()`, add:

```c
#define FULLSENDX_IMPLEMENTATION
#include "fullsendx.h"
```

Near the start of `main()`, add:

```c
fullsendx_trust_or_exit();
```

## History

- v0.0.0 (2024-07-26)

## License

See end of file for license information.
**/

#ifndef INCLUDE_FULLSENDX_H
#define INCLUDE_FULLSENDX_H

#ifdef __cplusplus
extern "C" {
#endif

extern void fullsendx_trust_or_exit(void);

#ifdef __cplusplus
}
#endif

#ifdef FULLSENDX_IMPLEMENTATION

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>

void fullsendx_trust_or_exit(void) {
    if (getuid() == 0 || geteuid() == 0) {
        fprintf(stderr, "refusing to run as root\n");
        exit(1);
    }

    CFDictionaryRef cfOptions = CFDictionaryCreate(
        kCFAllocatorDefault, &(const void *){kAXTrustedCheckOptionPrompt},
        &(const void *){kCFBooleanTrue}, true,
        &kCFCopyStringDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    if (!AXIsProcessTrustedWithOptions(cfOptions)) {
        fprintf(stderr, "not trusted for accessibility\n");
        exit(1);
    }
    CFRelease(cfOptions);
}
#endif // FULLSENDX_IMPLEMENTATION
#endif // INCLUDE_FULLSENDX_H

/**
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2024 Johnston Jiaa
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**/
