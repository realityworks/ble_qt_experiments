
#include <gtest/gtest.h>
#include "../app/Domain/GlobalDataStore.h"
#include "../app/Domain/AppState.h"
#include <QObject>

class TestStore : public ::testing::Test
{
public:
    GlobalDataStore store = GlobalDataStore();
    QObject *context = new QObject();
    bool localScanningValue = false;
    QList<HeartRateDevice> devices;
};

TEST_F(TestStore, TestStoreScanningUpdate)
{
    // Given
    store.update([](AppState &state) {
        state.scanning = false;
    });

    store.observe(
        context,
        &AppState::scanning,
        [this](bool updateScanning) {
            localScanningValue = updateScanning;
    });

    // When
    store.update([](AppState &state) {
        state.scanning = true;
    });

    // Then
    EXPECT_EQ(localScanningValue, true);
    EXPECT_EQ(localScanningValue, store.currentState()->scanning);
}

TEST_F(TestStore, TestStoreDevicesUpdate)
{
    // Given
    store.observe(
        context,
        &AppState::devices,
        [this](QList<HeartRateDevice> newDeviceList) {
            devices = newDeviceList;
    });

    // When
    store.update([](AppState &state) {
        HeartRateDevice device;
        device.batteryLevel = 20;
        device.bpm = 10;

        QList<HeartRateDevice> deviceList = QList<HeartRateDevice>();
        deviceList.append(device);
        state.devices = deviceList;
    });

    // Then
    EXPECT_EQ(devices.count(), 1);
    EXPECT_EQ(devices, store.currentState()->devices);
}
