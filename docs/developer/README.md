# `rikki`
* [Environment Setup](#environment-setup)
  * [Requirements](#requirements)
  * [Instructions](#instructions)

## Environment Setup
### Requirements
* [Visual Studio (Community)](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=17)
  * Desktop development with C++
    * MSVC v143 - VS 2022 C++ x64/x86 Spectre-mitigated libs (Latest)
    * C++ ATL and MFC for latest v143 build tools with Spectre Mitigations (x86 & x64)
* [Windows 11 Software Development Kit (SDK)](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/)
* [Windows Driver Kit (WDK)](https://go.microsoft.com/fwlink/?linkid=2297653)
* [DebugView](https://learn.microsoft.com/en-us/sysinternals/downloads/debugview)

### Instructions
**Step 1.** Open the `x64 Native Tools for Command Prompt for VS 2022` (this sets up the environment with the right compilers and paths).

**Step 2.** Set the kernel include path so the compiler can locate necessary headers.
```powershell
set INCLUDE=C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\km;%INCLUDE%
```

**Step 3.** Compile the driver with the correct defines, entry point, and libraries.
```powershell
cl /D NDEBUG /D _KERNEL_MODE /D WINNT /D _AMD64_ /D WIN32_LEAN_AND_MEAN rikki.c /link /SUBSYSTEM:NATIVE /DRIVER /NODEFAULTLIB /ENTRY:DriverEntry /OUT:rikki.sys /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\km\x64" ntoskrnl.lib
```

**Step 4.** Open the `x64 Native Tools for Command Prompt for VS 2022` as an administrator and create the service entry.
```bash
sc create Rikki type= kernel binPath= "C:\Users\Victor\Desktop\rikki\rikki.sys"
```

**Step 5.** Enable test signing mode so Windows can load unsigned drivers.
```bash
bcdedit /set testsigning on
```

**Step 6.** Start the driver to load it into the kernel.
```bash
sc start Rikki
```

**Step 7.** Stop the driver when you no longer need it running.
```bash
sc stop Rikki
```

**Step 8.** Disable test signing mode after testing is complete (optional).
```bash
bcdedit /set testsigning off
```

## References
* [Microsoft: Download the WDK](https://learn.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk)