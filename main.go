package main

import (
	"fmt"
	"unsafe"

	"golang.org/x/sys/windows"
)

var (
	modNtdll                         = windows.NewLazySystemDLL("ntdll.dll")
	procLdrRegisterDllNotification   = modNtdll.NewProc("LdrRegisterDllNotification")
	procLdrUnregisterDllNotification = modNtdll.NewProc("LdrUnregisterDllNotification")
)

type LdrDllNotificationReason uint32

const (
	LdrDllNotificationReasonLoaded   LdrDllNotificationReason = 1
	LdrDllNotificationReasonUnloaded LdrDllNotificationReason = 2
)

type LdrDllNotificationData struct {
	Flags       uint32
	FullDllName string
	BaseDllName string
	DllBase     uintptr
	SizeOfImage uint32
}

type ldrDllNotification struct {
	NotificationReason LdrDllNotificationReason
	NotificationData   uintptr
}

var callbackHandle uintptr

func dllNotificationCallback(reason uint32, data uintptr, context uintptr) uintptr {
	notificationData := (*LdrDllNotificationData)(unsafe.Pointer(data))
	fmt.Printf("DLL Loaded: %X, Size: %d bytes\n", notificationData.DllBase, notificationData.SizeOfImage)
	return 0
}

func registerDllNotification() error {
	return nil
}

func unregisterDllNotification() {
	procLdrUnregisterDllNotification.Call(callbackHandle)
}

func main() {
	var err error = registerDllNotification()
	if err != nil {
		fmt.Println(err)
		return
	}
	defer unregisterDllNotification()

	fmt.Println("[+] Started Rikki...")
	fmt.Scanln()
}
