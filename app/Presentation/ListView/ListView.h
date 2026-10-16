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
        //m_list->setModel(viewModel.model());
        //m_list->setEditTriggers(QAbstractItemView::NoEditTriggers);

        auto *top = new QHBoxLayout;
        top->addWidget(new QLabel(tr("Heart rate devices")));
        top->addStretch();
        top->addWidget(m_scanButton);

        auto *root = new QVBoxLayout(this);
        root->addLayout(top);
        root->addWidget(m_list);

        // View -> view model
        // connect(m_scanButton, &QPushButton::clicked, &m_vm, &DeviceListViewModel::scan);
        // connect(m_list, &QListView::activated, this,
        //         [this](const QModelIndex &i) { m_vm.select(i.row()); });
        //
        // // View model -> view
        // connect(&m_vm, &DeviceListViewModel::scanningChanged, this, &DeviceListView::syncScanning);
        // syncScanning();
    }

private:
    void syncScanning() {
        // m_scanButton->setEnabled(!m_vm.scanning());
        // m_scanButton->setText(m_vm.scanning() ? tr("Scanning…") : tr("Scan"));
    }

    ListViewModel &m_viewModel;
    QPushButton *m_scanButton = nullptr;
    QListView *m_list = nullptr;
};

#endif //BLE_HEART_RATE_DEMO_LISTVIEW_H
