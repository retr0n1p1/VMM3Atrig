# **GETTING STARTED**
## Compilation
1. You need to install arm-none-eabi-gcc of any version, you can do this through the package manager on most distributions
2. `cd Release`
3. `make "VMM3Atrig.elf" -j4`
4. To clean after compilation you can use the `make clean` command
## Flash
1. You need to install st-info and st-flash utilities, you can do this through the package manager on most distributions
2. To flash the firmware into stm you need a binary file with the extension `.bin`, you can get it with the command `arm-none-eabi-objcopy -O binary VMM3Atrig.elf VMM3Atrig.bin`
3. Run the command `st-info --probe` to check the correct connection and proper operation of the st-link v2
4. Run `st-flash write VMM3Atrig.bin 0x08000000` to flash firmware
5. Run `st-info --reset` to reset board after flashing
# **CODE NAVIGATION**
## Configuration
You can find configuration settings in `VMM3Atrig/Core/Inc/vmm3a.h`
## Time filtering algorithms
You can find it in `VMM3Atrig/Core/Src/main.c` in infinite while loop
## FIFO (buffer) algorithms
You can find it in `VMM3Atrig/Core/Src/vmm3a.c`
## Trigger interrupt functions
You can find it in `VMM3Atrig/Core/Src/tim.c` and interrupt handler in `VMM3Atrig/Core/Src/stm32g4xx_it.c`
# **CONFIGURATION**
## Board name
This is written to the final data set. It is useful when processing data from multiple detectors
## Buffer size selection
At a high particle flux, it is recommended to try increasing this parameter after evaluating its impact on the ratio of captured particles to the total number of trigger activations. However, this should be done with caution, as it increases the detector's dead time for each trigger activation
## Filtering mode selection
Three modes are available in total:
1. *Filtering by Time Window Only* This mode works well under conditions of low particle flux detected by the detector (all particles, not just those passing through the trigger detector). It should be used with a small buffer size. The key parameter for configuration is the time window. The window size is set in quartz ticks (40 MHz), meaning one tick equals 25 nanoseconds. From all spills recorded in the buffer, the oldest one that falls within this window is selected. For a setup with an 18-tube detector in a room, a small scintillator connected to a CAEN FERS as a trigger and placed directly on the first detector, the optimally selected window was 4000 ticks (100 microseconds)
2. *Filtering by Time Window and Preferred Time* Upon a trigger activation, this mode selects from the buffer all spills that fall within the time window. Then, from the selected spills, it chooses the one closest to the preferred delay `trigDelay`. This mode is preferred for use under high particle flux through the detector (any particles, not just those passing through the trigger detector). During testing on the same setup described in the previous point, it showed slightly better event filtering, but at the cost of missing some events. It potentially increases the detector's dead time due to the more complex processing algorithm
3. *Sending the Last Event from the Buffer* This mode is intended only for tests and debugging. During tests on the setup, it shows an almost uniform distribution across channels
## Sending empty events
This mode allows sending empty events to a free channel for each trigger activation. This helps configure the filtering modes and evaluate the ratio of useful spills to the total number of trigger activations. Additionally, this mode is extremely useful for synchronizing multiple detectors in a cascade. The parameter `chTrig` allows specifying to which channel such events will be sent
