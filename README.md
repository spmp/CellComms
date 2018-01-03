# CellComms
Cell Top Module (CTM) master controller communication class for recieving information from OSBMS CTM's.

## Minimal example
Instantiate the `CellComms` class as:
```
#include <Arduino.h>
#include <CellComms.h>

#define NUMBER_OF_CELLS  12

// Setup serial device to talk to CTM ring:
HardwareSerial Serial1(1)

CellComms cells(NUMBER_OF_CELLS, Serial1);
```

Currently the serial buffer and things need a bit of work, so reading
cell state must be done slowly enough for the complete packet to have
traversed the CTM ring:
```
cells.readCells();
```

