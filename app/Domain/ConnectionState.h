//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_CONNECTIONSTATE_H
#define BLE_HEART_RATE_DEMO_CONNECTIONSTATE_H

#include <QString>

enum class ConnectionState { Disconnected, Connecting, Connected };

inline QString toString(ConnectionState state) {
    switch (state) {
        case ConnectionState::Connected: return QStringLiteral("Connected");
        case ConnectionState::Disconnected: return QStringLiteral("Disconnected");
        case ConnectionState::Connecting: return QStringLiteral("Connecting…");
    }
}

#endif //BLE_HEART_RATE_DEMO_CONNECTIONSTATE_H
