#include "MatchesPage.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPainter>

MatchesPage::MatchesPage(QWidget *parent)
    : QWidget(parent), currentSortOrder(true)
{
    setupUI();
    setupTableHeader();
    populateTable();

    // Apply the stylesheet after UI is set up
    this->setStyleSheet(R"(
        /* Base Styles */
        QWidget {
            background-color: #89CFF0; /* Baby blue background */
            font-family: 'Segoe UI', sans-serif;
        }

        /* Title */
        QLabel#title-label {
            font-size: 24px;
            font-weight: 700;
            color: #1e293b;
            padding: 8px 0;
        }

        /* Search Bar */
        QLineEdit#search-bar {
            border: 1px solid #cbd5e1;
            border-radius: 6px;
            padding: 8px 12px;
            padding-right: 30px;
            min-width: 250px;
            font-size: 14px;
            background-color: white;
        }

        QLineEdit#search-bar:focus {
            border-color: #3b82f6;
            outline: none;
            box-shadow: 0 0 0 1px #3b82f6;
        }

        /* Table */
        QTableWidget {
            background-color: transparent;
            border: none;
            gridline-color: #e2e8f0;
            font-size: 14px;
        }

        QHeaderView::section {
            background-color: #e0f2fe;
            padding: 8px;
            border: 1px solid #cbd5e1;
            font-weight: bold;
        }

        /* Buttons */
        QPushButton {
            background-color: #3b82f6;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 8px;
            font-size: 14px;
        }

        QPushButton:hover {
            background-color: #2563eb;
        }

        /* Chart */
        QChartView {
            background-color: transparent;
        }
    )");
}

void MatchesPage::setupUI()
{
    // Title
    titleLabel = new QLabel("Matches Page");
    titleLabel->setObjectName("title-label");

    // Search Bar and Buttons
    searchLineEdit = new QLineEdit();
    searchLineEdit->setObjectName("search-bar");
    connect(searchLineEdit, &QLineEdit::textChanged, this, &MatchesPage::filterMatches);

    searchButton = new QToolButton();
    searchButton->setText("🔍");

    sortButton = new QToolButton();
    sortButton->setText("⇅");
    connect(sortButton, &QToolButton::clicked, [=]() {
        sortTable(0);
    });

    // Table
    matchesTable = new QTableWidget();
    matchesTable->setColumnCount(3);
    matchesTable->setHorizontalHeaderLabels(QStringList() << "Name" << "Date" << "Status");
    matchesTable->horizontalHeader()->setStretchLastSection(true);

    // Chart
    chartView = new QChartView(new QChart());
    chartView->setRenderHint(QPainter::Antialiasing);

    // CRUD Buttons
    addMatchButton = new QPushButton("Add Match");
    editMatchButton = new QPushButton("Edit Match");
    deleteMatchButton = new QPushButton("Delete Match");
    viewMatchButton = new QPushButton("View Match");

    // Layouts
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(titleLabel);
    topLayout->addStretch();
    topLayout->addWidget(searchLineEdit);
    topLayout->addWidget(searchButton);
    topLayout->addWidget(sortButton);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(addMatchButton);
    buttonsLayout->addWidget(editMatchButton);
    buttonsLayout->addWidget(deleteMatchButton);
    buttonsLayout->addWidget(viewMatchButton);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(matchesTable);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(chartView);
}

void MatchesPage::setupTableHeader()
{
    matchesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MatchesPage::populateTable()
{
    matchesTable->setRowCount(5);
    for (int row = 0; row < 5; ++row) {
        matchesTable->setItem(row, 0, new QTableWidgetItem(QString("Match %1").arg(row + 1)));
        matchesTable->setItem(row, 1, new QTableWidgetItem("2025-04-01"));
        matchesTable->setItem(row, 2, new QTableWidgetItem("Active"));
    }

    // Populate chart with simple data
    QPieSeries *series = new QPieSeries();
    series->append("Active", 4);
    series->append("Inactive", 1);

    chartView->chart()->addSeries(series);
    chartView->chart()->setTitle("Match Status Overview");
}

void MatchesPage::filterMatches(const QString &text)
{
    for (int row = 0; row < matchesTable->rowCount(); ++row) {
        bool match = false;
        for (int col = 0; col < matchesTable->columnCount(); ++col) {
            if (matchesTable->item(row, col)->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        matchesTable->setRowHidden(row, !match);
    }
}

void MatchesPage::sortTable(int column)
{
    matchesTable->sortItems(column, currentSortOrder ? Qt::AscendingOrder : Qt::DescendingOrder);
    currentSortOrder = !currentSortOrder;
}
