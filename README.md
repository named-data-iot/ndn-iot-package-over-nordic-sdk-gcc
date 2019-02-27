ndn-lite
========

<img src="https://zhiyi-zhang.com/images/ndn-lite-logo.jpg" alt="logo" width="500"/>

The NDN-Lite library implements the Named Data Networking Stack with the high-level application support functionalities and low-level OS/hardware adaptations for Internet of Things (IoT) scenarios.

The library is written in standard C.

Please go to our [wiki page](https://github.com/Zhiyi-Zhang/ndn_standalone/wiki) for the project details.

Compatible Hardware/Software Platforms
--------------------------------------

The network stack can be applied to any platforms that support C.
To work with the network interfaces (e.g., Bluetooth, Bluetooth Low Energy, IEEE 802.15.4, etc.), usually an adaptation layer is required.

So far, we have tested our library with [RIOT OS](https://www.riot-os.org/) and [Nordic NRF52840 Development Kit](https://www.nordicsemi.com/eng/Products/nRF52840-DK).
We also provides related adaptation implementation under `./adaptation/`


About This Repository
-------------------------------------

This Repository provides basic support on nRF52840DK peripheral drivers and their hardware abstraction.
Examples of their usage are also included.
Examples are only tested on macOS, might work on Linux. The implementation is based on Nordic SDK v15.2.0 and borrows some code from [RIOT OS](https://www.riot-os.org/) on board flashing.

### Motivation ###

- Providing NDN-Lite based IoT package \
 NDN Lite is the implementation of the core NDN network stack and NDN-based application support, but without the platform-specific adaptation, leaves the job of organizing dependencies to users.
 This repository provides an IoT package especially for NDN application development over Nordic SDK using GCC.

- Ease-of-Use \
 This repo includes all needed SDKs in folder ```third-party``` and configures them in folder ```toolchain```.
 Therefore, users can focus on application development.

- Platform Features are provided \
 This repo provides hardware abstraction for peripheral drivers in Nordic NRF52 platforms and will be maintained by the NDN IoT development team.

### Usage ###
Try hello world example, which shows the usage of system delay and time function.

- Step 1: Modify Settings \
 Go to ```toolchain/Makefile.posix``` and you will see following statements.
 ```
 GNU_INSTALL_ROOT := /usr/local/Cellar/arm-none-eabi-gcc/7-2018-q2-update/gcc/bin/
 GNU_VERSION ?= 7.3.1
 GNU_PREFIX ?= arm-none-eabi
 ```

 Modify the settings according to your computer. If you ran RIOT based program before, this compiler should already exist in your environment. If not, you need download and install one. On Windows, you can try modify ```toolchain/Makefile.windows```.

 - Step 2: Install [JLink Command Line Tools](https://www.segger.com/products/debug-probes/j-link/tools/j-link-commander/) and [Segger RTT tools](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) \
  If JLink Command Line Tools installed success, call ```JLinkExe``` in your terminal will return some info. You can use ```exit``` to return.
  If Segger RTT tools installed success, call ```JLinkRTTClient``` in your terminal will return some info. You can use ```Ctrl + C``` to return.

 - Step 3: Flash target board \
  Connect nRF52840DK board via cable.
  ```
  cd examples/hello-world
  make flash
  ```
  Generated HEX files will locate in ```hello-world/build``` folder and further be downloaded to the board.

- Step 4: Connect Board via terminal \
 In terimal, call ```JLinkExe``` and then type ```connect```. Press ENTER all the way down (which means use defaut setting), output should stop at displaying
 ```
  ROMTbl[0] @ E00FF000
  ROMTbl[0][0]: E000E000, CID: B105E00D, PID: 000BB00C SCS-M7
  ROMTbl[0][1]: E0001000, CID: B105E00D, PID: 003BB002 DWT
  ROMTbl[0][2]: E0002000, CID: B105E00D, PID: 002BB003 FPB
  ROMTbl[0][3]: E0000000, CID: B105E00D, PID: 003BB001 ITM
  ROMTbl[0][4]: E0040000, CID: B105900D, PID: 000BB9A1 TPIU
  ROMTbl[0][5]: E0041000, CID: B105900D, PID: 000BB925 ETM
  Cortex-M4 identified.
  J-Link>
 ```
 Open another terminal can call ```JLinkExeClient```, you should see output like this
 ```
  ###RTT Client: Connecting to J-Link RTT Server via localhost:19021  Connected.
  SEGGER J-Link V6.42b - Real time terminal output
  J-Link OB-SAM3U128-V2-NordicSemi compiled Jan  7 2019 14:07:15 V1.0, SN=683605425
  Process: JLinkExe
  hello, ndn-lite
  NDN-Lite: current system time: 494 ms
  NDN-Lite: current system time: 997 ms
  NDN-Lite: current system time: 1499 ms
  NDN-Lite: current system time: 2002 ms
  NDN-Lite: current system time: 2504 ms
  NDN-Lite: current system time: 3007 ms
  NDN-Lite: current system time: 3509 ms
        ......   ......   ......
 ```

 You can use ```Ctrl + C``` to exit JLinkExeClient or press RESET button on the board to restart the program. Unless you call ```exit``` in JLink, board is always be "considered" connected.

### Feature Supported ###
- Alarm
  * Hardware Dependencies: RTC0
  * Software Dependencies: nRF-IEEE-802.15.4-driver (Radio module in future)
  * Features: Milliseconds and microseconds time and alarm notification system. This module only support one alarm in runtime. And users should periodically check whether the alarm fires.

- UART
  * Hardware Dependencies: UART0
  * Software Dependencies: None
  * Features: Data exchange via serial port.

- Non-Volatile Memory
  * Hardware Dependencies: NVM Controller

### Feature In Plan ###
- Radio
  * Hardware Dependencies: Radio, RTC0
  * Software Dependencies: Alarm
  * Motivation: Current "face to driver" adaptation only enables send/receive. drivers specific setting interfaces (e.g., transmission power, with or without link layer ACK) are needed.
  * Features: 802.15.4 and BLE drivers abstraction.

- Sensor

### Porting Other Platforms to This Branch ##
- SDK Inclusion
  * Add third party SDKs in folder ```third-party```. Please only include necessary files you need, whole SDK package might be very large.

- Hardware Adaptation
  * Create folder ```adaptation/platform/*board*``` and implement header files in ```adaptation/platform```

- Toolchain Configuration
  * Create folder ```toolchain/*board*``` and add makefiles to configure SDK compiling and target port.
  * Add other necessary platform and SDK independent files folder ```toolchain```.
  * This branch use Segger JLink as default flashing tool. If other tools needed, please include them in ```third-party``` and configure them ```toolchain/*board*```.
