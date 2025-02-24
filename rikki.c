#include <ntddk.h>

// Text goes here.
void ImageLoadCallback(
    _In_ PUNICODE_STRING FullImageName,
    _In_ HANDLE ProcessId,
    _In_ PIMAGE_INFO ImageInfo
) {
    UNREFERENCED_PARAMETER(ImageInfo);
    DbgPrint("Image Loaded: %wZ (Process ID: %lu)\n", FullImageName, (ULONG)(ULONG_PTR)ProcessId);
}

// Text goes here.
void DriverUnload(_In_ PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);
    DbgPrint("Driver Unloaded\n");
}

// Main entry point for the driver.
NTSTATUS DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
) {
    UNREFERENCED_PARAMETER(RegistryPath);
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
