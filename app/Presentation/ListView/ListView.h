//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_LISTVIEW_H
#define BLE_HEART_RATE_DEMO_LISTVIEW_H

#include <QHBoxLayout>
#include <QLabel>
#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QStringListModel>
#include <QStringList>
#include "ListViewModel.h"

class ListView : public QWidget {
    Q_OBJECT
public:
    explicit ListView(
        ListViewModel &viewModel,
        QWidget *parent = nullptr
    )
        : QWidget(parent), m_viewModel(viewModel)
    {
        m_scanButton = new QPushButton;

        m_list = new QListView;
        m_list->setEditTriggers(QAbstractItemView::NoEditTriggers);

        auto *top = new QHBoxLayout;
        top->addWidget(new QLabel(tr("Heart rate devices")));
        top->addStretch();
        top->addWidget(m_scanButton);

        auto *root = new QVBoxLayout(this);
        root->addLayout(top);
        root->addWidget(m_list);

        // View -> view model
        connectBindings();

        syncScanning();
    }

private:
    void connectBindings() {
        connect(
            m_scanButton,
            &QPushButton::clicked,
            &m_viewModel,
            &ListViewModel::scan
        );

        connect(
            m_list,
            &QListView::activated,
            &m_viewModel,
            &ListViewModel::select
        );

        connect(
            &m_viewModel,
            &ListViewModel::scanningChanged,
            this,
            &ListView::syncScanning
        );

        connect(
            &m_viewModel,
            &ListViewModel::devicesFound,
            this,
            &ListView::syncDeviceList
        );
    }

    void syncScanning() {
        m_scanButton->setEnabled(!m_viewModel.scanning());
        m_scanButton->setText(
            m_viewModel.scanning()
                ? tr("Scanning…")
                : tr("Scan")
        );
    }

    void syncDeviceList() {
        QStringListModel *model = new QStringListModel(m_viewModel.devices(), this);
        m_list->setModel(model);
    }

    ListViewModel &m_viewModel;
    QPushButton *m_scanButton = nullptr;
    QListView *m_list = nullptr;
};

#endif //BLE_HEART_RATE_DEMO_LISTVIEW_H
