set INCLUDE=C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\km;%INCLUDE%
cl /D NDEBUG /D _KERNEL_MODE /D WINNT /D _AMD64_ /D WIN32_LEAN_AND_MEAN rikki.c /link /SUBSYSTEM:NATIVE /DRIVER /NODEFAULTLIB /ENTRY:DriverEntry /OUT:rikki.sys /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\km\x64" ntoskrnl.lib
