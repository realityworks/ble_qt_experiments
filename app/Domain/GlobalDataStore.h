//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_GLOBALDATASTORE_H
#define BLE_HEART_RATE_DEMO_GLOBALDATASTORE_H

#include <QObject>
#include "AppState.h"
#include <functional>
#include <memory>
#include <type_traits>

class GlobalDataStore : public QObject {
    Q_OBJECT
public:
    explicit GlobalDataStore(QObject *parent = nullptr)
    : QObject(parent), m_state(std::make_shared<const AppState>()) {
        qRegisterMetaType<AppStatePtr>();
    }



    void update() {

    }

    // Setup some type of connector to observe data
//signals:

private:
    void apply(const std::function<void(AppState &)> &mutation) {

    }
    AppStatePtr m_state;
};

#endif //BLE_HEART_RATE_DEMO_GLOBALDATASTORE_H
