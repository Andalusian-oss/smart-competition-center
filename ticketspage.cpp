#include "ticketspage.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QDateTime>
#include <QLabel>
#include <QDateTimeEdit>

TicketsPage::TicketsPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
    populateTable();
}

void TicketsPage::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Search bar and sort combo
    QHBoxLayout *topLayout = new QHBoxLayout();
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search tickets...");
    sortComboBox = new QComboBox(this);
    sortComboBox->addItem("Sort by ID");
    sortComboBox->addItem("Sort by Name");
    topLayout->addWidget(searchBar);
    topLayout->addWidget(sortComboBox);

    // Tickets Table
    ticketsTable = new QTableWidget(this);
    ticketsTable->setColumnCount(5);  // Add a column for "Match Date"
    QStringList headers = {"Ticket ID", "Ticket Name", "Ticket Price", "Ticket Date", "Match Time"};
    ticketsTable->setHorizontalHeaderLabels(headers);
    ticketsTable->horizontalHeader()->setStretchLastSection(true);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addTicketButton = new QPushButton("Add Ticket", this);
    editTicketButton = new QPushButton("Edit Ticket", this);
    deleteTicketButton = new QPushButton("Delete Ticket", this);
    viewTicketButton = new QPushButton("View Ticket", this);
    buttonLayout->addWidget(addTicketButton);
    buttonLayout->addWidget(editTicketButton);
    buttonLayout->addWidget(deleteTicketButton);
    buttonLayout->addWidget(viewTicketButton);

    // Add everything to the main layout
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(ticketsTable);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    // Connections
    connect(addTicketButton, &QPushButton::clicked, this, &TicketsPage::addTicket);
    connect(editTicketButton, &QPushButton::clicked, this, &TicketsPage::editSelectedTicket);
    connect(deleteTicketButton, &QPushButton::clicked, this, &TicketsPage::deleteSelectedTicket);
    connect(viewTicketButton, &QPushButton::clicked, this, &TicketsPage::viewSelectedTicket);
    connect(searchBar, &QLineEdit::textChanged, this, &TicketsPage::searchTickets);
    connect(sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TicketsPage::sortTickets);
}

void TicketsPage::populateTable()
{
    // Set the row count to 0, leaving the table empty initially
    ticketsTable->setRowCount(0);  // The table is now empty initially
}

void TicketsPage::addTicket()
{
    addOrEditTicketDialog(false, -1);  // Show the add ticket dialog
}

void TicketsPage::editSelectedTicket()
{
    int row = ticketsTable->currentRow();
    if (row >= 0) {
        addOrEditTicketDialog(true, row);  // Show the edit ticket dialog
    } else {
        QMessageBox::warning(this, "Edit Ticket", "Please select a ticket to edit.");
    }
}

void TicketsPage::deleteSelectedTicket()
{
    int row = ticketsTable->currentRow();
    if (row >= 0) {
        ticketsTable->removeRow(row);
        QMessageBox::information(this, "Delete Ticket", "Ticket deleted.");
    } else {
        QMessageBox::warning(this, "Delete Ticket", "Please select a ticket to delete.");
    }
}

void TicketsPage::viewSelectedTicket()
{
    int row = ticketsTable->currentRow();
    if (row >= 0) {
        QString ticketInfo = "Ticket ID: " + ticketsTable->item(row, 0)->text() + "\n"
                             + "Ticket Name: " + ticketsTable->item(row, 1)->text() + "\n"
                             + "Ticket Price: " + ticketsTable->item(row, 2)->text() + "\n"
                             + "Match Date: " + ticketsTable->item(row, 3)->text() + "\n"
                             + "Match time: " + ticketsTable->item(row, 4)->text();
        QMessageBox::information(this, "View Ticket", ticketInfo);
    } else {
        QMessageBox::warning(this, "View Ticket", "Please select a ticket to view.");
    }
}

void TicketsPage::searchTickets()
{
    QString searchText = searchBar->text().toLower();
    for (int i = 0; i < ticketsTable->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < ticketsTable->columnCount(); ++j) {
            QTableWidgetItem *item = ticketsTable->item(i, j);
            if (item && item->text().toLower().contains(searchText)) {
                match = true;
                break;
            }
        }
        ticketsTable->setRowHidden(i, !match);
    }
}

void TicketsPage::sortTickets(int index)
{
    if (index == 0) {
        ticketsTable->sortItems(0, Qt::AscendingOrder); // Sort by ID
    } else if (index == 1) {
        ticketsTable->sortItems(1, Qt::AscendingOrder); // Sort by Name
    }
}

void TicketsPage::addOrEditTicketDialog(bool isEdit, int row)
{
    // Create a dialog to add or edit ticket details
    QDialog dialog(this);
    dialog.setWindowTitle(isEdit ? "Edit Ticket" : "Add Ticket");

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLineEdit *idEdit = new QLineEdit(isEdit ? ticketsTable->item(row, 0)->text() : "", &dialog);
    idEdit->setReadOnly(isEdit);  // Ticket ID can't be changed during edit

    QLineEdit *nameEdit = new QLineEdit(isEdit ? ticketsTable->item(row, 1)->text() : "", &dialog);
    QLineEdit *priceEdit = new QLineEdit(isEdit ? ticketsTable->item(row, 2)->text() : "", &dialog);

    // Add DateTimeEdit for the match date and time
    QDateTimeEdit *matchDateEdit = new QDateTimeEdit(isEdit ? QDateTime::fromString(ticketsTable->item(row, 4)->text(), "yyyy-MM-dd hh:mm:ss") : QDateTime::currentDateTime(), &dialog);
    matchDateEdit->setDisplayFormat("hh:mm:ss");

    // Ticket Date will be set to the current time when a new ticket is added
    QDateTimeEdit *ticketDateEdit = new QDateTimeEdit(QDateTime::currentDateTime(), &dialog);
    ticketDateEdit->setDisplayFormat("yyyy-MM-dd");

    QPushButton *submitButton = new QPushButton(isEdit ? "Save Changes" : "Add Ticket", &dialog);

    layout->addWidget(new QLabel("Ticket ID:", &dialog));
    layout->addWidget(idEdit);
    layout->addWidget(new QLabel("Ticket Name:", &dialog));
    layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("Ticket Price:", &dialog));
    layout->addWidget(priceEdit);
    layout->addWidget(new QLabel("Time:", &dialog));
    layout->addWidget(matchDateEdit);
    layout->addWidget(new QLabel("Ticket Date:", &dialog));
    layout->addWidget(ticketDateEdit);
    layout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    if (dialog.exec() == QDialog::Accepted) {
        // Validate that fields are not empty
        if (nameEdit->text().isEmpty() || priceEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
            return;
        }

        if (isEdit) {
            // Update the table with new values (edit mode)
            ticketsTable->item(row, 1)->setText(nameEdit->text());
            ticketsTable->item(row, 2)->setText(priceEdit->text());
            ticketsTable->item(row, 4)->setText(matchDateEdit->text());  // Update match date for edit
        } else {
            // Add a new ticket to the table (add mode)
            int rowCount = ticketsTable->rowCount();
            ticketsTable->insertRow(rowCount);
            ticketsTable->setItem(rowCount, 0, new QTableWidgetItem(QString::number(rowCount + 1)));  // Ticket ID
            ticketsTable->setItem(rowCount, 1, new QTableWidgetItem(nameEdit->text()));  // Ticket Name
            ticketsTable->setItem(rowCount, 2, new QTableWidgetItem(priceEdit->text()));  // Ticket Price
            ticketsTable->setItem(rowCount, 3, new QTableWidgetItem(ticketDateEdit->text()));  // Ticket Date
            ticketsTable->setItem(rowCount, 4, new QTableWidgetItem(matchDateEdit->text()));  // Match Date
        }
    }
}
