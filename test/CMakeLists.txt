find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
set(PROJECT_NAME ble-heart-rate-demo-tests)

set(TEST_SOURCES
    tst_sample.cpp
    main.cpp
        ../app/Domain/GlobalDataStore.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME} ${TEST_SOURCES}
            ../app/Domain/GlobalDataStore.h)
else()
    add_executable(${PROJECT_NAME} ${TEST_SOURCES}
            ../app/Domain/GlobalDataStore.h)
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
