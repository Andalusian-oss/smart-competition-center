#include "matchespage.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QPieSeries>
#include <QPieSlice>
#include <QChart>
#include <QChartView>
#include <QHBoxLayout>

MatchesPage::MatchesPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void MatchesPage::setupUI()
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

    // Main layout
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Title
    titleLabel = new QLabel("⚽ List of Matches", this);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 20px;");
    mainLayout->addWidget(titleLabel);

    // Table to display matches
    matchesTable = new QTableWidget(this);
    matchesTable->setColumnCount(3);
    matchesTable->setHorizontalHeaderLabels({"Match ID", "Team A vs Team B", "Date"});
    matchesTable->horizontalHeader()->setStretchLastSection(true);
    matchesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    matchesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    matchesTable->setSelectionMode(QAbstractItemView::SingleSelection);

    // Example rows (you can replace this with actual data)
    matchesTable->insertRow(0);
    matchesTable->setItem(0, 0, new QTableWidgetItem("001"));
    matchesTable->setItem(0, 1, new QTableWidgetItem("Team Alpha vs Team Beta"));
    matchesTable->setItem(0, 2, new QTableWidgetItem("2025-05-12"));

    matchesTable->insertRow(1);
    matchesTable->setItem(1, 0, new QTableWidgetItem("002"));
    matchesTable->setItem(1, 1, new QTableWidgetItem("Team Gamma vs Team Delta"));
    matchesTable->setItem(1, 2, new QTableWidgetItem("2025-05-15"));

    matchesTable->insertRow(2);
    matchesTable->setItem(2, 0, new QTableWidgetItem("003"));
    matchesTable->setItem(2, 1, new QTableWidgetItem("Team Alpha vs Team Gamma"));
    matchesTable->setItem(2, 2, new QTableWidgetItem("2025-05-18"));

    mainLayout->addWidget(matchesTable);



    // CRUD Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // Create buttons
    addMatchButton = new QPushButton("➕ Add Match", this);
    addMatchButton->setStyleSheet("padding: 8px; font-weight: bold; background-color: #3b82f6; color: white; border-radius: 6px;");
    buttonLayout->addWidget(addMatchButton);

    editMatchButton = new QPushButton("✏️ Edit Match", this);
    editMatchButton->setStyleSheet("padding: 8px; font-weight: bold; background-color: #f59e0b; color: white; border-radius: 6px;");
    buttonLayout->addWidget(editMatchButton);

    deleteMatchButton = new QPushButton("🗑 Delete Match", this);
    deleteMatchButton->setStyleSheet("padding: 8px; font-weight: bold; background-color: #ef4444; color: white; border-radius: 6px;");
    buttonLayout->addWidget(deleteMatchButton);

    viewMatchButton = new QPushButton("👀 View Match", this);
    viewMatchButton->setStyleSheet("padding: 8px; font-weight: bold; background-color: #34d399; color: white; border-radius: 6px;");
    buttonLayout->addWidget(viewMatchButton);

    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    // Pie chart
    QPieSeries *series = new QPieSeries();
    series->append("Team Alpha", 2);  // Team Alpha appears in 2 matches
    series->append("Team Beta", 1);   // Team Beta appears in 1 match
    series->append("Team Gamma", 2);  // Team Gamma appears in 2 matches
    series->append("Team Delta", 1);  // Team Delta appears in 1 match

    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
        slice->setLabelPosition(QPieSlice::LabelOutside);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Team Participation in Matches");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(300);

    mainLayout->addWidget(chartView);
}
