#include "teamspage.h"
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>

TeamsPage::TeamsPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void TeamsPage::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(16);

    // Title label
    titleLabel = new QLabel("🏆 List of Teams", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #1e293b;");
    mainLayout->addWidget(titleLabel);

    // Search Bar
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("🔍 Search teams...");
    searchBar->setStyleSheet(R"(
        padding: 8px 12px;
        border: 1px solid #d1d5db;
        border-radius: 8px;
        background-color: #f1f5f9;
    )");
    mainLayout->addWidget(searchBar);
    connect(searchBar, &QLineEdit::textChanged, this, &TeamsPage::searchTeams);

    // Card-style container
    QWidget *card = new QWidget(this);
    card->setStyleSheet("background-color: #f8fafc; border-radius: 16px; padding: 16px;");
    QVBoxLayout *cardLayout = new QVBoxLayout(card);

    // Teams Table
    teamsTable = new QTableWidget(this);
    teamsTable->setColumnCount(3);
    teamsTable->setHorizontalHeaderLabels({"Team ID", "Team Name", "Country"});
    teamsTable->horizontalHeader()->setStretchLastSection(true);
    teamsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    teamsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    teamsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    teamsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    teamsTable->setAlternatingRowColors(true);

    // Example Row
    teamsTable->insertRow(0);
    teamsTable->setItem(0, 0, new QTableWidgetItem("TM-001"));
    teamsTable->setItem(0, 1, new QTableWidgetItem("Team Alpha"));
    teamsTable->setItem(0, 2, new QTableWidgetItem("Tunisia"));

    cardLayout->addWidget(teamsTable);
    mainLayout->addWidget(card);

    // Buttons
    addTeamButton = new QPushButton("➕ Add Team", this);
    editTeamButton = new QPushButton("✏️ Edit Team", this);
    deleteTeamButton = new QPushButton("🗑️ Delete Team", this);
    viewTeamButton = new QPushButton("👀 View Team", this);

    QString buttonStyle = R"(
        QPushButton {
            background-color: #5fc2BA;
            color: white;
            padding: 10px 16px;
            font-weight: bold;
            border: none;
            border-radius: 12px;
        }
        QPushButton:hover {
            background-color: #3b556D;
        }
    )";
    addTeamButton->setStyleSheet(buttonStyle);
    editTeamButton->setStyleSheet(buttonStyle);
    deleteTeamButton->setStyleSheet(buttonStyle);
    viewTeamButton->setStyleSheet(buttonStyle);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(12);
    buttonLayout->addWidget(addTeamButton);
    buttonLayout->addWidget(editTeamButton);
    buttonLayout->addWidget(deleteTeamButton);
    buttonLayout->addWidget(viewTeamButton);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    // Connections
    connect(addTeamButton, &QPushButton::clicked, this, &TeamsPage::addTeam);
    connect(editTeamButton, &QPushButton::clicked, this, &TeamsPage::editSelectedTeam);
    connect(deleteTeamButton, &QPushButton::clicked, this, &TeamsPage::deleteSelectedTeam);
    connect(viewTeamButton, &QPushButton::clicked, this, &TeamsPage::viewSelectedTeam);
}

// CRUD Operations
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
        }
    } else {
        QMessageBox::warning(this, "Delete Team", "Please select a team to delete.");
    }
}

void TeamsPage::viewSelectedTeam()
{
    int row = teamsTable->currentRow();
    if (row >= 0) {
        QString id = teamsTable->item(row, 0)->text();
        QString name = teamsTable->item(row, 1)->text();
        QString country = teamsTable->item(row, 2)->text();

        QMessageBox::information(this, "Team Details", QString("ID: %1\nName: %2\nCountry: %3")
                                                           .arg(id, name, country));
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
    QLineEdit *idField = new QLineEdit();
    QLineEdit *nameField = new QLineEdit();
    QLineEdit *countryField = new QLineEdit();

    if (isEdit && row >= 0) {
        idField->setText(teamsTable->item(row, 0)->text());
        nameField->setText(teamsTable->item(row, 1)->text());
        countryField->setText(teamsTable->item(row, 2)->text());
    }

    form->addRow("Team ID:", idField);
    form->addRow("Team Name:", nameField);
    form->addRow("Country:", countryField);

    QPushButton *saveBtn = new QPushButton(isEdit ? "Save Changes" : "Add Team");
    QPushButton *cancelBtn = new QPushButton("Cancel");
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);
    connect(saveBtn, &QPushButton::clicked, &dialog, &QDialog::accept);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(saveBtn);
    form->addRow(btnLayout);

    if (dialog.exec() == QDialog::Accepted) {
        if (idField->text().isEmpty() || nameField->text().isEmpty()) {
            QMessageBox::warning(this, "Warning", "Team ID and Name are required!");
            return;
        }

        if (isEdit && row >= 0) {
            teamsTable->item(row, 0)->setText(idField->text());
            teamsTable->item(row, 1)->setText(nameField->text());
            teamsTable->item(row, 2)->setText(countryField->text());
        } else {
            int newRow = teamsTable->rowCount();
            teamsTable->insertRow(newRow);
            teamsTable->setItem(newRow, 0, new QTableWidgetItem(idField->text()));
            teamsTable->setItem(newRow, 1, new QTableWidgetItem(nameField->text()));
            teamsTable->setItem(newRow, 2, new QTableWidgetItem(countryField->text()));
        }
    }
}

void TeamsPage::searchTeams(const QString &text)
{
    for (int i = 0; i < teamsTable->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < teamsTable->columnCount(); ++j) {
            QTableWidgetItem *item = teamsTable->item(i, j);
            if (item && item->text().toLower().contains(text.toLower())) {
                match = true;
                break;
            }
        }
        teamsTable->setRowHidden(i, !match);
    }
}
