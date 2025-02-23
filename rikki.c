#include <ntddk.h>

// Text goes here.
void ImageLoadCallback(
    PUNICODE_STRING FullImageName,
    HANDLE ProcessId,
    PIMAGE_INFO ImageInfo
) {
    // Text goes here.
    UNREFERENCED_PARAMETER(ImageInfo);

    // Text goes here.
    DbgPrint("Image Loaded: %wZ (Process ID: %lu)\n", FullImageName, (ULONG)(ULONG_PTR)ProcessId);
}

// Text goes here.
void DriverUnload(PDRIVER_OBJECT DriverObject) {
    // Text goes here.
    UNREFERENCED_PARAMETER(DriverObject);
    
    // Text goes here.
    PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);

    // Text goes here.
    DbgPrint("Driver Unloaded\n");
}

// Main entry point for the driver.
NTSTATUS DriverEntry(
    PDRIVER_OBJECT DriverObject,
    PUNICODE_STRING RegistryPath
) {
    // Text goes here.
    UNREFERENCED_PARAMETER(RegistryPath);

    // Text goes here.
    NTSTATUS status;

    // Register the image load callback.
    status = PsSetLoadImageNotifyRoutine(ImageLoadCallback);
    if (!NT_SUCCESS(status)) {
        DbgPrint("Failed to register image load callback: 0x%X\n", status);
        return status;
    }

    // Set up unload function.
    DriverObject->DriverUnload = DriverUnload;
    DbgPrint("Driver Loaded Successfully\n");
    return STATUS_SUCCESS;
}
