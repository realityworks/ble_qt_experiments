find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
set(PROJECT_NAME ble-heart-rate-demo-tests)

set(TEST_SOURCES
    main.cpp
        ../app/Domain/GlobalDataStore.h
        ../app/Domain/AppState.h
        ../app/Domain/DeviceUseCase.h
        ../app/Service/IDeviceService.h
        ../app/Service/BLE/BleDeviceService.h
        ../app/Service/MOCK/MockDeviceService.h
        ../app/Presentation/DetailView/DetailView.h
        ../app/Presentation/DetailView/DetailViewModel.h
        ../app/Presentation/ListView/ListView.h
        ../app/Presentation/ListView/ListViewModel.h
        ../app/Service/BLE/BleServices.h
        ../app/Service/BLE/CharSpec.h
        ../app/Service/BLE/BleCharacteristics.h
        ../app/Service/BLE/ServiceSpec.h
        ../app/Service/HeartRateDevice.h
        ../app/Service/ConnectionState.h
        ../app/Service/DeviceServiceFactory.h
        tst_deviceservice.cpp
        tst_store.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME} ${TEST_SOURCES}
            ../app/Domain/GlobalDataStore.h
            ../app/Domain/AppState.h
            ../app/Domain/DeviceUseCase.h
            ../app/Service/IDeviceService.h
            ../app/Service/BLE/BleDeviceService.h
            ../app/Service/MOCK/MockDeviceService.h
            ../app/Presentation/DetailView/DetailView.h
            ../app/Presentation/DetailView/DetailViewModel.h
            ../app/Presentation/ListView/ListView.h
            ../app/Presentation/ListView/ListViewModel.h
            ../app/Service/BLE/BleServices.h
            ../app/Service/BLE/CharSpec.h
            ../app/Service/BLE/BleCharacteristics.h
            ../app/Service/BLE/ServiceSpec.h
            ../app/Service/HeartRateDevice.h
            ../app/Service/ConnectionState.h
            ../app/Service/DeviceServiceFactory.h
            tst_deviceservice.cpp
            tst_store.cpp)
else()
    add_executable(${PROJECT_NAME} ${TEST_SOURCES}
            ../app/Domain/GlobalDataStore.h
            ../app/Domain/AppState.h
            ../app/Domain/DeviceUseCase.h
            ../app/Service/IDeviceService.h
            ../app/Service/BLE/BleDeviceService.h
            ../app/Service/MOCK/MockDeviceService.h
            ../app/Presentation/DetailView/DetailView.h
            ../app/Presentation/DetailView/DetailViewModel.h
            ../app/Presentation/ListView/ListView.h
            ../app/Presentation/ListView/ListViewModel.h
            ../app/Service/BLE/BleServices.h
            ../app/Service/BLE/CharSpec.h
            ../app/Service/BLE/BleCharacteristics.h
            ../app/Service/BLE/ServiceSpec.h
            ../app/Service/HeartRateDevice.h
            ../app/Service/ConnectionState.h
            ../app/Service/DeviceServiceFactory.h
            tst_deviceservice.cpp
            tst_store.cpp)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    GTest::gtest
    GTest::gmock
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME} DISCOVERY_MODE PRE_TEST)
