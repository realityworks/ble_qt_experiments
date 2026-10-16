//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_DETAILVIEW_H
#define BLE_HEART_RATE_DEMO_DETAILVIEW_H
#include "DetailViewModel.h"

#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class DetailView : public QWidget {
    Q_OBJECT
public:
    explicit DetailView(DetailViewModel &viewModel, QWidget *parent = nullptr)
        : QWidget(parent), m_viewModel(viewModel)
    {
        auto *back = new QPushButton(tr("‹ Back"));
        m_title = new QLabel;
        QFont titleFont = m_title->font();
        titleFont.setPointSize(titleFont.pointSize() + 4);
        titleFont.setBold(true);
        m_title->setFont(titleFont);

        m_status = new QLabel;
        m_bpm = new QLabel;
        QFont bpmFont = m_bpm->font();
        bpmFont.setPointSize(48);
        bpmFont.setBold(true);

        m_bpm->setFont(bpmFont);
        m_bpm->setAlignment(Qt::AlignCenter);

        m_connectButton = new QPushButton;

        auto *top = new QHBoxLayout;
        top->addWidget(back);
        top->addWidget(m_title, 1);

        auto *root = new QVBoxLayout(this);
        root->addLayout(top);
        root->addWidget(m_status);
        root->addWidget(m_bpm);
        root->addWidget(m_connectButton);

        // View -> view model
        connect(back, &QPushButton::clicked, this, &DetailView::backRequested);
        connect(m_connectButton, &QPushButton::clicked, this, [this] {
            if (m_viewModel.state() == ConnectionState::Disconnected)
                m_viewModel.connectToDevice();
            else if (m_viewModel.state() == ConnectionState::Connected)
                m_viewModel.disconnectFromDevice();
        });

        // View model -> view
        connect(&m_viewModel, &DetailViewModel::nameChanged, this, &DetailView::syncName);
        connect(&m_viewModel, &DetailViewModel::bpmChanged, this, &DetailView::syncBpm);
        connect(&m_viewModel, &DetailViewModel::stateChanged, this, &DetailView::syncState);

        syncName();
        syncBpm();
        syncState();
    }

signals:
    void backRequested();

private:
    void syncName() {
        m_title->setText(m_viewModel.name());
    }

    void syncBpm() {
        m_bpm->setText(m_viewModel.bpm() > 0
            ? QStringLiteral("%1 BPM").arg(m_viewModel.bpm())
            : QStringLiteral("-- BPM"));
    }

    void syncState() {
        m_status->setText(m_viewModel.status());
        switch (m_viewModel.state()) {
        case ConnectionState::Disconnected:
            m_connectButton->setText(tr("Connect"));
            m_connectButton->setEnabled(true);
            break;
        case ConnectionState::Connecting:
            m_connectButton->setText(tr("Connecting…"));
            m_connectButton->setEnabled(false);
            break;
        case ConnectionState::Connected:
            m_connectButton->setText(tr("Disconnect"));
            m_connectButton->setEnabled(true);
            break;
        }
    }

    DetailViewModel &m_viewModel;
    QLabel *m_title = nullptr;
    QLabel *m_status = nullptr;
    QLabel *m_bpm = nullptr;
    QPushButton *m_connectButton = nullptr;
};

#endif //BLE_HEART_RATE_DEMO_DETAILVIEW_H
