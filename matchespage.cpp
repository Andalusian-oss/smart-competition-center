#include "MatchesPage.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPainter>
#include <QMessageBox>

MatchesPage::MatchesPage(QWidget *parent)
    : QWidget(parent), currentSortOrder(true), addMatchDialog(nullptr)
{
    setupUI();
    setupTableHeader();
    populateTable();

    this->setStyleSheet(R"(
        QWidget {
            background-color: #89CFF0;
            font-family: 'Segoe UI', sans-serif;
        }
        QLabel#title-label {
            font-size: 24px;
            font-weight: 700;
            color: #1e293b;
            padding: 8px 0;
        }
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
        QChartView {
            background-color: transparent;
        }
    )");
}

void MatchesPage::setupUI()
{
    titleLabel = new QLabel("Matches Page");
    titleLabel->setObjectName("title-label");

    searchLineEdit = new QLineEdit();
    searchLineEdit->setObjectName("search-bar");
    connect(searchLineEdit, &QLineEdit::textChanged, this, &MatchesPage::filterMatches);

    searchButton = new QToolButton();
    searchButton->setText("🔍");
    connect(searchButton, &QToolButton::clicked, [=]() {
        filterMatches(searchLineEdit->text());
    });

    sortButton = new QToolButton();
    sortButton->setText("⇅");
    connect(sortButton, &QToolButton::clicked, [=]() {
        sortTable(0);
    });

    matchesTable = new QTableWidget();
    matchesTable->setColumnCount(6);
    matchesTable->setHorizontalHeaderLabels(QStringList()
                                            << "ID Match"
                                            << "Équipe A"
                                            << "Équipe B"
                                            << "Date"
                                            << "Score"
                                            << "Status");
    matchesTable->horizontalHeader()->setStretchLastSection(true);

    chartView = new QChartView(new QChart());
    chartView->setRenderHint(QPainter::Antialiasing);

    addMatchButton = new QPushButton("Add Match");
    editMatchButton = new QPushButton("Edit Match");
    deleteMatchButton = new QPushButton("Delete Match");
    viewMatchButton = new QPushButton("View Match");

    connect(addMatchButton, &QPushButton::clicked, this, &MatchesPage::openAddMatchDialog);
    connect(editMatchButton, &QPushButton::clicked, this, &MatchesPage::editMatch);
    connect(deleteMatchButton, &QPushButton::clicked, this, &MatchesPage::deleteMatch);
    connect(viewMatchButton, &QPushButton::clicked, this, &MatchesPage::viewMatch);

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
    buttonsLayout->addStretch();

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(matchesTable);
    mainLayout->addWidget(chartView);
}

void MatchesPage::setupTableHeader()
{
    matchesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MatchesPage::populateTable()
{
    matchesTable->setRowCount(10);
    for (int row = 0; row < 10; ++row) {
        matchesTable->setItem(row, 0, new QTableWidgetItem(QString::number(1000 + row)));
        matchesTable->setItem(row, 1, new QTableWidgetItem(QString("Team A%1").arg(row + 1)));
        matchesTable->setItem(row, 2, new QTableWidgetItem(QString("Team B%1").arg(row + 1)));
        matchesTable->setItem(row, 3, new QTableWidgetItem("2025-04-01"));
        matchesTable->setItem(row, 4, new QTableWidgetItem(QString("%1 - %2").arg(row + 1).arg(row + 2)));
        matchesTable->setItem(row, 5, new QTableWidgetItem(row % 2 == 0 ? "Active" : "Inactive"));
    }

    QPieSeries *series = new QPieSeries();
    series->append("Active", 5);
    series->append("Inactive", 5);

    chartView->chart()->addSeries(series);
    chartView->chart()->setTitle("Match Status Overview");
}

void MatchesPage::filterMatches(const QString &text)
{
    for (int row = 0; row < matchesTable->rowCount(); ++row) {
        bool match = false;
        for (int col = 0; col < matchesTable->columnCount(); ++col) {
            if (matchesTable->item(row, col) && matchesTable->item(row, col)->text().contains(text, Qt::CaseInsensitive)) {
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

void MatchesPage::createAddMatchDialog()
{
    addMatchDialog = new QDialog(this);
    addMatchDialog->setWindowTitle("Add New Match");

    matchIDEdit = new QLineEdit();
    matchIDEdit->setPlaceholderText("Match ID");

    teamAEdit = new QLineEdit();
    teamAEdit->setPlaceholderText("Team A");

    teamBEdit = new QLineEdit();
    teamBEdit->setPlaceholderText("Team B");

    dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, addMatchDialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, addMatchDialog, &QDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(matchIDEdit);
    layout->addWidget(teamAEdit);
    layout->addWidget(teamBEdit);
    layout->addWidget(dateEdit);
    layout->addWidget(buttonBox);

    addMatchDialog->setLayout(layout);
}

void MatchesPage::openAddMatchDialog()
{
    if (!addMatchDialog) {
        createAddMatchDialog();
    }

    matchIDEdit->clear();
    teamAEdit->clear();
    teamBEdit->clear();
    dateEdit->setDate(QDate::currentDate());

    if (addMatchDialog->exec() == QDialog::Accepted) {
        QString matchID = matchIDEdit->text();
        QString teamA = teamAEdit->text();
        QString teamB = teamBEdit->text();
        QString date = dateEdit->date().toString("yyyy-MM-dd");

        int newRow = matchesTable->rowCount();
        matchesTable->insertRow(newRow);
        matchesTable->setItem(newRow, 0, new QTableWidgetItem(matchID));
        matchesTable->setItem(newRow, 1, new QTableWidgetItem(teamA));
        matchesTable->setItem(newRow, 2, new QTableWidgetItem(teamB));
        matchesTable->setItem(newRow, 3, new QTableWidgetItem(date));
        matchesTable->setItem(newRow, 4, new QTableWidgetItem("0 - 0"));
        matchesTable->setItem(newRow, 5, new QTableWidgetItem("Active"));
    }
}

void MatchesPage::editMatch()
{
    int row = matchesTable->currentRow();
    if (row >= 0) {
        QTableWidgetItem *matchIDItem = matchesTable->item(row, 0);
        QTableWidgetItem *teamAItem = matchesTable->item(row, 1);
        QTableWidgetItem *teamBItem = matchesTable->item(row, 2);
        QTableWidgetItem *dateItem = matchesTable->item(row, 3);

        matchIDEdit->setText(matchIDItem->text());
        teamAEdit->setText(teamAItem->text());
        teamBEdit->setText(teamBItem->text());
        dateEdit->setDate(QDate::fromString(dateItem->text(), "yyyy-MM-dd"));

        if (addMatchDialog->exec() == QDialog::Accepted) {
            matchIDItem->setText(matchIDEdit->text());
            teamAItem->setText(teamAEdit->text());
            teamBItem->setText(teamBEdit->text());
            dateItem->setText(dateEdit->date().toString("yyyy-MM-dd"));
        }
    }
}

void MatchesPage::deleteMatch()
{
    int row = matchesTable->currentRow();
    if (row >= 0) {
        int ret = QMessageBox::warning(this, "Delete Match", "Are you sure you want to delete this match?",
                                       QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            matchesTable->removeRow(row);
        }
    }
}

void MatchesPage::viewMatch()
{
    int row = matchesTable->currentRow();
    if (row >= 0) {
        QString matchDetails = QString("Match ID: %1\nTeam A: %2\nTeam B: %3\nDate: %4\nScore: %5\nStatus: %6")
        .arg(matchesTable->item(row, 0)->text())
            .arg(matchesTable->item(row, 1)->text())
            .arg(matchesTable->item(row, 2)->text())
            .arg(matchesTable->item(row, 3)->text())
            .arg(matchesTable->item(row, 4)->text())
            .arg(matchesTable->item(row, 5)->text());

        QMessageBox::information(this, "Match Details", matchDetails);
    }
}
