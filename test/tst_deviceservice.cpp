//
// Created by Piotr Suwara on 16/10/2026.
//

#include <gtest/gtest.h>
#include "../app/Domain/GlobalDataStore.h"
#include "../app/Domain/AppState.h"
#include <QObject>
#include <QUuid>
#include <sys/socket.h>

#include "../app/Service/IDeviceService.h"
#include "../app/Service/MOCK/MockDeviceService.h"

class TestDeviceService : public ::testing::Test
{
public:
    std::unique_ptr<IDeviceService> deviceService = std::make_unique<MockDeviceService>();
};

TEST_F(TestDeviceService, TestDeviceFoundDevices) {
    // Given
    QList<HeartRateDevice> localList = QList<HeartRateDevice>({
            HeartRateDevice()
        });

    deviceService = std::make_unique<MockDeviceService>(
        localList
    );

    // When
    QList<HeartRateDevice> foundList = deviceService->findDevices(QUuid("1234")).result();

    // Then
    EXPECT_EQ(foundList.count(), 1);
}

TEST_F(TestDeviceService, TestDeviceCorrectDevices) {
    // Given
    QList<HeartRateDevice> localList = QList<HeartRateDevice>({
            HeartRateDevice(QUuid("1234"), "TestDevice", 80, 10),
            HeartRateDevice(QUuid("1234"), "TestDevice", 80, 10),
        });

    deviceService = std::make_unique<MockDeviceService>(
        localList
    );

    // When
    QList<HeartRateDevice> foundList = deviceService->findDevices(QUuid()).result();

    // Then
    EXPECT_EQ(foundList.count(), 2);
    EXPECT_EQ(foundList, localList);
}

TEST_F(TestDeviceService, TestConnectDevice) {
    // Given
    QUuid connectId = QUuid::createUuid();
    QList<HeartRateDevice> localList = QList<HeartRateDevice>({
            HeartRateDevice(connectId, "TestDevice_1", 80, 10),
            HeartRateDevice(QUuid::createUuid(), "TestDevice_2", 23, 10),
        });

    deviceService = std::make_unique<MockDeviceService>(
        localList
    );

    // When
    std::optional<HeartRateDevice> connectedDevice = deviceService->connectDevice(connectId).result();
    std::optional<HeartRateDevice> notConnectedDevice = deviceService->connectDevice(QUuid::createUuid()).result();

    // Then
    EXPECT_EQ(connectedDevice.value().id, connectId);
    EXPECT_EQ(notConnectedDevice, std::nullopt);
}