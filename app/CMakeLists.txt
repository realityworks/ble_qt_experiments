cmake_minimum_required(VERSION 3.16)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Charts Widgets Bluetooth)

qt_standard_project_setup(REQUIRES 6.8)

set(PROJECT_NAME ble_heart_rate_demo_app)
qt_add_executable(${PROJECT_NAME}
    main.cpp
        Domain/GlobalDataStore.h
        Domain/AppState.h
        Domain/DeviceUseCase.h
        Service/IDeviceService.h
        Service/BLE/BleDeviceService.h
        Service/MOCK/MockDeviceService.h
        Presentation/DetailView/DetailView.h
        Presentation/DetailView/DetailViewModel.h
        Presentation/ListView/ListView.h
        Presentation/ListView/ListViewModel.h
        Service/BLE/BleServices.h
        Service/BLE/CharSpec.h
        Service/BLE/BleCharacteristics.h
        Service/BLE/ServiceSpec.h
        Service/HeartRateDevice.h
        Service/ConnectionState.h
)

qt_add_qml_module(${PROJECT_NAME}
    URI bleheartratedemo
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${PROJECT_NAME} PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${PROJECT_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Quick
    Qt6::Charts
    Qt6::Widgets
    Qt6::Bluetooth
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
