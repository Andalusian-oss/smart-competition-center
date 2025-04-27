#include "TeamsPage.h"
#include <QDialog>
#include <QFormLayout>
#include <QMessageBox>

TeamsPage::TeamsPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void TeamsPage::setupUI()
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
            background-color: #3b82f6;
            color: white;
            border: none;
        }
        .btn:hover {
            background-color: #2563eb;
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

    setupTitle(mainLayout);
    setupCard(mainLayout);
    setupButtons(mainLayout);

    // Chart
    series = new QPieSeries();
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
    mainLayout->addWidget(chartView);

    setLayout(mainLayout);
}

void TeamsPage::setupTitle(QVBoxLayout *layout)
{
    titleLabel = new QLabel("⚽ Teams Management", this);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    layout->addWidget(titleLabel);
}

void TeamsPage::setupCard(QVBoxLayout *layout)
{
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
    QHBoxLayout *searchLayout = new QHBoxLayout();
    QLineEdit *searchInput = new QLineEdit(this);
    searchInput->setPlaceholderText("🔍 Search Team...");
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
    teamsTable = new QTableWidget(this);
    teamsTable->setColumnCount(3);
    teamsTable->setHorizontalHeaderLabels(QStringList() << "Team Name" << "Coach" << "Category");
    teamsTable->horizontalHeader()->setStretchLastSection(true);
    teamsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    teamsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    teamsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    // Example data
    teamsTable->setRowCount(2);
    teamsTable->setItem(0, 0, new QTableWidgetItem("Team A"));
    teamsTable->setItem(0, 1, new QTableWidgetItem("Coach Alpha"));
    teamsTable->setItem(0, 2, new QTableWidgetItem("Senior"));

    teamsTable->setItem(1, 0, new QTableWidgetItem("Team B"));
    teamsTable->setItem(1, 1, new QTableWidgetItem("Coach Beta"));
    teamsTable->setItem(1, 2, new QTableWidgetItem("Junior"));

    cardLayout->addWidget(teamsTable);
}

void TeamsPage::setupButtons(QVBoxLayout *layout)
{
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    addButton = new QPushButton("➕ Add Team", this);
    editButton = new QPushButton("✏️ Edit Team", this);
    deleteButton = new QPushButton("🗑️ Delete Team", this);
    viewButton = new QPushButton("👀 View Team", this);

    addButton->setStyleSheet("background-color: #3b82f6; color: white; font-weight: bold;");
    editButton->setStyleSheet("background-color: #3b82f6; color: white; font-weight: bold;");
    deleteButton->setStyleSheet("background-color: #ef4444; color: white; font-weight: bold;");
    viewButton->setStyleSheet("background-color: #3b82f6; color: white; font-weight: bold;");

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(viewButton);
    layout->addLayout(buttonLayout);

    connect(addButton, &QPushButton::clicked, this, &TeamsPage::addTeam);
    connect(editButton, &QPushButton::clicked, this, &TeamsPage::editSelectedTeam);
    connect(deleteButton, &QPushButton::clicked, this, &TeamsPage::deleteSelectedTeam);
    connect(viewButton, &QPushButton::clicked, this, &TeamsPage::viewSelectedTeam);
}

// CRUD Slots

void TeamsPage::addTeam()
{
    openTeamDialog(false);
}

void TeamsPage::editSelectedTeam()
{
    int row = teamsTable->currentRow();
    if (row >= 0)
        openTeamDialog(true, row);
    else
        QMessageBox::warning(this, "Edit Team", "Please select a team to edit.");
}

void TeamsPage::deleteSelectedTeam()
{
    int row = teamsTable->currentRow();
    if (row >= 0) {
        if (QMessageBox::question(this, "Delete Team", "Are you sure you want to delete this team?") == QMessageBox::Yes) {
            teamsTable->removeRow(row);
            refreshChart();
        }
    } else {
        QMessageBox::warning(this, "Delete Team", "Please select a team to delete.");
    }
}

void TeamsPage::viewSelectedTeam()
{
    int row = teamsTable->currentRow();
    if (row >= 0) {
        QString name = teamsTable->item(row, 0)->text();
        QString coach = teamsTable->item(row, 1)->text();
        QString category = teamsTable->item(row, 2)->text();

        QMessageBox::information(this, "Team Details", QString("Name: %1\nCoach: %2\nCategory: %3")
                                                           .arg(name, coach, category));
    } else {
        QMessageBox::warning(this, "View Team", "Please select a team to view.");
    }
}

void TeamsPage::openTeamDialog(bool isEdit, int row)
{
    QDialog dialog(this);
    dialog.setWindowTitle(isEdit ? "Edit Team" : "Add Team");
    dialog.setFixedSize(400, 250);

    QFormLayout *form = new QFormLayout(&dialog);
    QLineEdit *nameField = new QLineEdit();
    QLineEdit *coachField = new QLineEdit();
    QLineEdit *categoryField = new QLineEdit();

    if (isEdit && row >= 0) {
        nameField->setText(teamsTable->item(row, 0)->text());
        coachField->setText(teamsTable->item(row, 1)->text());
        categoryField->setText(teamsTable->item(row, 2)->text());
    }

    form->addRow("Team Name:", nameField);
    form->addRow("Coach:", coachField);
    form->addRow("Category:", categoryField);

    QPushButton *saveBtn = new QPushButton(isEdit ? "Save Changes" : "Add Team");
    QPushButton *cancelBtn = new QPushButton("Cancel");

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(saveBtn);
    form->addRow(btnLayout);

    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);
    connect(saveBtn, &QPushButton::clicked, &dialog, &QDialog::accept);

    if (dialog.exec() == QDialog::Accepted) {
        if (nameField->text().isEmpty() || coachField->text().isEmpty() || categoryField->text().isEmpty()) {
            QMessageBox::warning(this, "Warning", "All fields are required!");
            return;
        }

        if (isEdit && row >= 0) {
            teamsTable->item(row, 0)->setText(nameField->text());
            teamsTable->item(row, 1)->setText(coachField->text());
            teamsTable->item(row, 2)->setText(categoryField->text());
        } else {
            int newRow = teamsTable->rowCount();
            teamsTable->insertRow(newRow);
            teamsTable->setItem(newRow, 0, new QTableWidgetItem(nameField->text()));
            teamsTable->setItem(newRow, 1, new QTableWidgetItem(coachField->text()));
            teamsTable->setItem(newRow, 2, new QTableWidgetItem(categoryField->text()));
        }

        refreshChart();
    }
}

void TeamsPage::refreshChart()
{
    int senior = 0, junior = 0;
    for (int i = 0; i < teamsTable->rowCount(); ++i) {
        QString category = teamsTable->item(i, 2)->text().toLower();
        if (category.contains("senior")) senior++;
        else if (category.contains("junior")) junior++;
    }

    series->clear();
    series->append("Senior Teams", senior);
    series->append("Junior Teams", junior);

    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
    }
}
