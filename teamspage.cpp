#include "TeamsPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QLineEdit>
#include <QHBoxLayout>

TeamsPage::TeamsPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void TeamsPage::setupUI()
{
    // Apply styles directly instead of calling applyTailwindStyles
    this->setStyleSheet(R"(
        QWidget {
            background-color: #f8fafc;
            font-family: 'Segoe UI', sans-serif;
        }
        .card {
            background: white;
            border-radius: 8px;
            border: 1px solid #e2e8f0;
            padding: 8px;
        }
        .btn {
            padding: 8px 16px;
            border-radius: 6px;
            font-weight: 500;
            transition: all 0.15s ease;
        }
        .btn-primary {
            background-color: #3b82f6;
            color: white;
            border: 1px solid #2563eb;
        }
        .btn-primary:hover {
            background-color: #2563eb;
        }
        .btn-danger {
            background-color: #ef4444;
            color: white;
            border: 1px solid #dc2626;
        }
        .btn-danger:hover {
            background-color: #dc2626;
        }
        .input {
            padding: 8px 12px;
            border: 1px solid #cbd5e1;
            border-radius: 6px;
            min-width: 300px;
        }
        .input:focus {
            border-color: #3b82f6;
            outline: none;
        }
        QHeaderView::section {
            background-color: #f1f5f9;
            color: #64748b;
            padding: 12px;
            border: none;
            font-weight: 600;
        }
        .text-2xl {
            font-size: 24px;
        }
        .font-bold {
            font-weight: 700;
        }
        .text-gray-800 {
            color: #1e293b;
        }
    )");

    QVBoxLayout *layout = new QVBoxLayout(this);

    setupTitle(layout);
    setupCard(layout);
    setupButtons(layout);
    QPieSeries *series = new QPieSeries();
    series->append("Senior Teams", 1);
    series->append("Junior Teams", 1);

    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Team Categories");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(250);

    layout->addWidget(chartView);
}

void TeamsPage::setupTitle(QVBoxLayout *layout)
{
    QLabel *titleLabel = new QLabel("⚽ Teams Management");
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; padding: 10px 0;");
    layout->addWidget(titleLabel);
}

void TeamsPage::setupCard(QVBoxLayout *layout)
{
    // Card wrapper
    QWidget *card = new QWidget(this);
    card->setStyleSheet("background-color: #f8fafc; border-radius: 16px; padding: 24px;");
    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setSpacing(16);

    setupSearch(cardLayout);
    setupTable(cardLayout);

    layout->addWidget(card);
}

void TeamsPage::setupSearch(QVBoxLayout *cardLayout)
{
    // Search bar
    QHBoxLayout *searchLayout = new QHBoxLayout();
    QLineEdit *searchInput = new QLineEdit(this);
    searchInput->setPlaceholderText("🔍 Search Match...");
    searchInput->setStyleSheet(R"(
        padding: 8px 12px;
        border: 1px solid #cbd5e1;
        border-radius: 8px;
        background-color: #ffffff;
    )");
    searchLayout->addWidget(searchInput);
    searchLayout->addStretch();
    cardLayout->addLayout(searchLayout);
}

void TeamsPage::setupTable(QVBoxLayout *cardLayout)
{
    // Table to display teams
    QTableWidget *table = new QTableWidget(this);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(QStringList() << "Team Name" << "Coach" << "Category");
    table->horizontalHeader()->setStretchLastSection(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Sample data (replace with real data later)
    table->setRowCount(2);
    table->setItem(0, 0, new QTableWidgetItem("Team A"));
    table->setItem(0, 1, new QTableWidgetItem("Coach Alpha"));
    table->setItem(0, 2, new QTableWidgetItem("Senior"));
    table->setItem(1, 0, new QTableWidgetItem("Team B"));
    table->setItem(1, 1, new QTableWidgetItem("Coach Beta"));
    table->setItem(1, 2, new QTableWidgetItem("Junior"));

    cardLayout->addWidget(table);
}

void TeamsPage::setupButtons(QVBoxLayout *layout)
{
    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addButton = new QPushButton("➕ Add Team");
    QPushButton *editButton = new QPushButton("✏️ Edit Team");
    QPushButton *deleteButton = new QPushButton("🗑 Delete Team");

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch();

    layout->addLayout(buttonLayout);
}
