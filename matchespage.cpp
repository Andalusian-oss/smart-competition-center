#include "matchespage.h"
#include <QHeaderView>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QtCharts/QChart>

MatchesPage::MatchesPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void MatchesPage::setupUI()
{
    this->setStyleSheet(R"(
        QWidget {
            background-color: #f8fafc;
            font-family: 'Segoe UI', sans-serif;
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
        }
        .btn-primary:hover {
            background-color: #2563eb;
        }
        .btn-danger {
            background-color: #ef4444;
            color: white;
        }
        .btn-danger:hover {
            background-color: #dc2626;
        }
        QHeaderView::section {
            background-color: #f1f5f9;
            color: #64748b;
            padding: 12px;
            border: none;
            font-weight: 600;
        }
    )");

    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Title
    titleLabel = new QLabel("⚽ List of Matches", this);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 20px;");
    mainLayout->addWidget(titleLabel);

    // Table
    matchesTable = new QTableWidget(this);
    matchesTable->setColumnCount(3);
    matchesTable->setHorizontalHeaderLabels({"Match ID", "Team A vs Team B", "Date"});
    matchesTable->horizontalHeader()->setStretchLastSection(true);
    matchesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    matchesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    matchesTable->setSelectionMode(QAbstractItemView::SingleSelection);

    // Example Data
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

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addMatchButton = new QPushButton("➕ Add Match", this);
    editMatchButton = new QPushButton("✏️ Edit Match", this);
    deleteMatchButton = new QPushButton("🗑 Delete Match", this);
    viewMatchButton = new QPushButton("👀 View Match", this);

    addMatchButton->setStyleSheet("background-color: #3b82f6; color: white; font-weight: bold;");
    editMatchButton->setStyleSheet("background-color: #f59e0b; color: white; font-weight: bold;");
    deleteMatchButton->setStyleSheet("background-color: #ef4444; color: white; font-weight: bold;");
    viewMatchButton->setStyleSheet("background-color: #34d399; color: white; font-weight: bold;");

    buttonLayout->addWidget(addMatchButton);
    buttonLayout->addWidget(editMatchButton);
    buttonLayout->addWidget(deleteMatchButton);
    buttonLayout->addWidget(viewMatchButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);

    connect(addMatchButton, &QPushButton::clicked, this, &MatchesPage::addMatch);
    connect(editMatchButton, &QPushButton::clicked, this, &MatchesPage::editSelectedMatch);
    connect(deleteMatchButton, &QPushButton::clicked, this, &MatchesPage::deleteSelectedMatch);
    connect(viewMatchButton, &QPushButton::clicked, this, &MatchesPage::viewSelectedMatch);

    // Chart
    series = new QPieSeries();
    series->append("Team Alpha", 2);
    series->append("Team Beta", 1);
    series->append("Team Gamma", 2);
    series->append("Team Delta", 1);

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

    setLayout(mainLayout);
}

// CRUD Functions

void MatchesPage::addMatch()
{
    openMatchDialog(false);
}

void MatchesPage::editSelectedMatch()
{
    int row = matchesTable->currentRow();
    if (row >= 0)
        openMatchDialog(true, row);
    else
        QMessageBox::warning(this, "Edit Match", "Please select a match to edit.");
}

void MatchesPage::deleteSelectedMatch()
{
    int row = matchesTable->currentRow();
    if (row >= 0) {
        if (QMessageBox::question(this, "Delete Match", "Are you sure you want to delete this match?") == QMessageBox::Yes) {
            matchesTable->removeRow(row);
            refreshChart();
        }
    } else {
        QMessageBox::warning(this, "Delete Match", "Please select a match to delete.");
    }
}

void MatchesPage::viewSelectedMatch()
{
    int row = matchesTable->currentRow();
    if (row >= 0) {
        QString id = matchesTable->item(row, 0)->text();
        QString teams = matchesTable->item(row, 1)->text();
        QString date = matchesTable->item(row, 2)->text();

        QMessageBox::information(this, "Match Details", QString("ID: %1\nTeams: %2\nDate: %3")
                                                            .arg(id, teams, date));
    } else {
        QMessageBox::warning(this, "View Match", "Please select a match to view.");
    }
}

void MatchesPage::openMatchDialog(bool isEdit, int row)
{
    QDialog dialog(this);
    dialog.setWindowTitle(isEdit ? "Edit Match" : "Add Match");
    dialog.setFixedSize(400, 250);

    QFormLayout *form = new QFormLayout(&dialog);
    QLineEdit *idField = new QLineEdit();
    QLineEdit *teamsField = new QLineEdit();
    QLineEdit *dateField = new QLineEdit();

    if (isEdit && row >= 0) {
        idField->setText(matchesTable->item(row, 0)->text());
        teamsField->setText(matchesTable->item(row, 1)->text());
        dateField->setText(matchesTable->item(row, 2)->text());
    }

    form->addRow("Match ID:", idField);
    form->addRow("Teams:", teamsField);
    form->addRow("Date:", dateField);

    QPushButton *saveBtn = new QPushButton(isEdit ? "Save Changes" : "Add Match");
    QPushButton *cancelBtn = new QPushButton("Cancel");

    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);
    connect(saveBtn, &QPushButton::clicked, &dialog, &QDialog::accept);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(saveBtn);
    form->addRow(btnLayout);

    if (dialog.exec() == QDialog::Accepted) {
        if (idField->text().isEmpty() || teamsField->text().isEmpty() || dateField->text().isEmpty()) {
            QMessageBox::warning(this, "Warning", "All fields are required!");
            return;
        }

        if (isEdit && row >= 0) {
            matchesTable->item(row, 0)->setText(idField->text());
            matchesTable->item(row, 1)->setText(teamsField->text());
            matchesTable->item(row, 2)->setText(dateField->text());
        } else {
            int newRow = matchesTable->rowCount();
            matchesTable->insertRow(newRow);
            matchesTable->setItem(newRow, 0, new QTableWidgetItem(idField->text()));
            matchesTable->setItem(newRow, 1, new QTableWidgetItem(teamsField->text()));
            matchesTable->setItem(newRow, 2, new QTableWidgetItem(dateField->text()));
        }

        refreshChart();
    }
}

void MatchesPage::refreshChart()
{
    QMap<QString, int> teamParticipation;

    for (int i = 0; i < matchesTable->rowCount(); ++i) {
        QString teams = matchesTable->item(i, 1)->text();
        QStringList teamList = teams.split(" vs ");
        for (const QString &team : teamList) {
            teamParticipation[team]++;
        }
    }

    series->clear();
    for (auto it = teamParticipation.begin(); it != teamParticipation.end(); ++it) {
        series->append(it.key(), it.value());
    }

    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
    }
}
