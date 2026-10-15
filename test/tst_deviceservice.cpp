//
// Created by Piotr Suwara on 16/10/2026.
//

#include <gtest/gtest.h>
#include "../app/Domain/GlobalDataStore.h"
#include "../app/Domain/AppState.h"
#include <QObject>

#include "../app/Service/IDeviceService.h"
#include "../app/Service/MOCK/MockDeviceService.h"

class TestDeviceService : public ::testing::Test
{
public:
    std::unique_ptr<IDeviceService> deviceService = std::make_unique<MockDeviceService>();
};

TEST_F(TestDeviceService, TestDeviceFindDevices) {
    // Given
    // deviceService = MockDeviceService(
    //     QList<HeartRateDevice>({
    //         HeartRateDevice()
    //     })
    // );
    // When

    // Then
}