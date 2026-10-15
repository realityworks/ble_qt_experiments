//
// Created by Piotr Suwara on 16/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_CONCURRENCYHELPERS_H
#define BLE_HEART_RATE_DEMO_CONCURRENCYHELPERS_H

#include <memory>
#include <QFuture>
#include <QPromise>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>

template <typename T>
QFuture<T> after(
    int ms, std::function<T()> produce
) {
    // auto promise = std::make_shared<QPromise<T>>();
    // promise->start();
    return QtConcurrent::run([ms, produce]() {
        QThread::msleep(ms);
        return produce();
    });
    // QFuture<T> future = promise->future();
    // QTimer::singleShot(ms, this, [promise, produce = std::move(produce)]{
    //     promise->addResult(produce());
    //     promise->finish();
    // });
}

#endif //BLE_HEART_RATE_DEMO_CONCURRENCYHELPERS_H
