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

    // Get a view into the current state object
    AppStatePtr currentState() const {
        return m_state;
    }

    void update(std::function<void(AppState &)> value) {
        // TODO: Make this thread safe
        apply(value);
    }

    // Setup some type of connector to observe data
    template <typename Selector, typename Handler>
    QMetaObject::Connection observe(const QObject *context, Selector selector, Handler handler) {
        // Type path INTO our app state
        using T = std::decay_t<std::invoke_result_t<Selector, const AppState &>>;

        // Get a SmartPtr into the Value of the Type path
        auto current_value = std::make_shared<T>(std::invoke(selector, *currentState()));

        auto functor = [selector, handler, current_value](AppStatePtr state_ptr) {
            T next_value = std::invoke(selector, *state_ptr);
            if (next_value == *current_value) return;
            *current_value = next_value;
            handler(next_value);
        };

        // Create a connect object bound to the value, providing us updates
        return connect(
            this,
            &GlobalDataStore::changed,
            context, // Need context to know lifetimes and threads
            functor
        );
    }

signals:
    void changed(AppStatePtr state_ptr);

private:
    void apply(const std::function<void(AppState &)> &mutation) {

    }
    AppStatePtr m_state;
};

#endif //BLE_HEART_RATE_DEMO_GLOBALDATASTORE_H
