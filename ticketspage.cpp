#include "ticketspage.h"
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>

TicketsPage::TicketsPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void TicketsPage::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(16);

    // Title label
    titleLabel = new QLabel("🎟️ List of Tickets", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #1e293b;");
    mainLayout->addWidget(titleLabel);

    // Card-style container
    QWidget *card = new QWidget(this);
    card->setStyleSheet("background-color: #f8fafc; border-radius: 16px; padding: 16px;");
    QVBoxLayout *cardLayout = new QVBoxLayout(card);

    // Tickets Table
    ticketsTable = new QTableWidget(this);
    ticketsTable->setColumnCount(4);
    ticketsTable->setHorizontalHeaderLabels({"Ticket ID", "Match", "Price", "Status"});
    ticketsTable->horizontalHeader()->setStretchLastSection(true);
    ticketsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ticketsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ticketsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ticketsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ticketsTable->setAlternatingRowColors(true);

    // Example Row
    ticketsTable->insertRow(0);
    ticketsTable->setItem(0, 0, new QTableWidgetItem("TCK-001"));
    ticketsTable->setItem(0, 1, new QTableWidgetItem("Team Alpha vs Team Beta"));
    ticketsTable->setItem(0, 2, new QTableWidgetItem("30 TND"));
    ticketsTable->setItem(0, 3, new QTableWidgetItem("Available"));

    cardLayout->addWidget(ticketsTable);
    mainLayout->addWidget(card);

    // Buttons
    addTicketButton = new QPushButton("➕ Add Ticket", this);
    editTicketButton = new QPushButton("✏️ Edit Ticket", this);
    deleteTicketButton = new QPushButton("🗑️ Delete Ticket", this);
    viewTicketButton = new QPushButton("👀 View Ticket", this);

    QString buttonStyle = R"(
        background-color: #3b82f6;
        color: white;
        padding: 8px 16px;
        font-weight: bold;
        border: none;
        border-radius: 8px;
    )";
    addTicketButton->setStyleSheet(buttonStyle);
    editTicketButton->setStyleSheet(buttonStyle);
    deleteTicketButton->setStyleSheet(buttonStyle);
    viewTicketButton->setStyleSheet(buttonStyle);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addTicketButton);
    buttonLayout->addWidget(editTicketButton);
    buttonLayout->addWidget(deleteTicketButton);
    buttonLayout->addWidget(viewTicketButton);
    mainLayout->addLayout(buttonLayout);

    // Chart
    series = new QPieSeries();
    series->append("Available", 15);
    series->append("Sold", 25);
    series->append("Reserved", 5);

    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Ticket Status");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(250);
    mainLayout->addWidget(chartView);

    setLayout(mainLayout);

    // Connections
    connect(addTicketButton, &QPushButton::clicked, this, &TicketsPage::addTicket);
    connect(editTicketButton, &QPushButton::clicked, this, &TicketsPage::editSelectedTicket);
    connect(deleteTicketButton, &QPushButton::clicked, this, &TicketsPage::deleteSelectedTicket);
    connect(viewTicketButton, &QPushButton::clicked, this, &TicketsPage::viewSelectedTicket);
}

// CRUD Operations
void TicketsPage::addTicket()
{
    openTicketDialog(false);
}

void TicketsPage::editSelectedTicket()
{
    int row = ticketsTable->currentRow();
    if (row >= 0)
        openTicketDialog(true, row);
    else
        QMessageBox::warning(this, "Edit Ticket", "Please select a ticket to edit.");
}

void TicketsPage::deleteSelectedTicket()
{
    int row = ticketsTable->currentRow();
    if (row >= 0) {
        if (QMessageBox::question(this, "Delete Ticket", "Are you sure you want to delete this ticket?") == QMessageBox::Yes) {
            ticketsTable->removeRow(row);
            refreshChart();
        }
    } else {
        QMessageBox::warning(this, "Delete Ticket", "Please select a ticket to delete.");
    }
}

void TicketsPage::viewSelectedTicket()
{
    int row = ticketsTable->currentRow();
    if (row >= 0) {
        QString id = ticketsTable->item(row, 0)->text();
        QString match = ticketsTable->item(row, 1)->text();
        QString price = ticketsTable->item(row, 2)->text();
        QString status = ticketsTable->item(row, 3)->text();

        QMessageBox::information(this, "Ticket Details", QString("ID: %1\nMatch: %2\nPrice: %3\nStatus: %4")
                                                             .arg(id, match, price, status));
    } else {
        QMessageBox::warning(this, "View Ticket", "Please select a ticket to view.");
    }
}

void TicketsPage::openTicketDialog(bool isEdit, int row)
{
    QDialog dialog(this);
    dialog.setWindowTitle(isEdit ? "Edit Ticket" : "Add Ticket");
    dialog.setFixedSize(400, 300);

    QFormLayout *form = new QFormLayout(&dialog);
    QLineEdit *idField = new QLineEdit();
    QLineEdit *matchField = new QLineEdit();
    QLineEdit *priceField = new QLineEdit();
    QLineEdit *statusField = new QLineEdit();

    if (isEdit && row >= 0) {
        idField->setText(ticketsTable->item(row, 0)->text());
        matchField->setText(ticketsTable->item(row, 1)->text());
        priceField->setText(ticketsTable->item(row, 2)->text());
        statusField->setText(ticketsTable->item(row, 3)->text());
    }

    form->addRow("Ticket ID:", idField);
    form->addRow("Match:", matchField);
    form->addRow("Price:", priceField);
    form->addRow("Status:", statusField);

    QPushButton *saveBtn = new QPushButton(isEdit ? "Save Changes" : "Add Ticket");
    QPushButton *cancelBtn = new QPushButton("Cancel");
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);
    connect(saveBtn, &QPushButton::clicked, &dialog, &QDialog::accept);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(saveBtn);
    form->addRow(btnLayout);

    if (dialog.exec() == QDialog::Accepted) {
        if (idField->text().isEmpty() || matchField->text().isEmpty()) {
            QMessageBox::warning(this, "Warning", "Ticket ID and Match are required!");
            return;
        }

        if (isEdit && row >= 0) {
            ticketsTable->item(row, 0)->setText(idField->text());
            ticketsTable->item(row, 1)->setText(matchField->text());
            ticketsTable->item(row, 2)->setText(priceField->text());
            ticketsTable->item(row, 3)->setText(statusField->text());
        } else {
            int newRow = ticketsTable->rowCount();
            ticketsTable->insertRow(newRow);
            ticketsTable->setItem(newRow, 0, new QTableWidgetItem(idField->text()));
            ticketsTable->setItem(newRow, 1, new QTableWidgetItem(matchField->text()));
            ticketsTable->setItem(newRow, 2, new QTableWidgetItem(priceField->text()));
            ticketsTable->setItem(newRow, 3, new QTableWidgetItem(statusField->text()));
        }

        refreshChart();
    }
}

void TicketsPage::refreshChart()
{
    // Refresh the chart (dummy for now — can be improved later)
    int available = 0, sold = 0, reserved = 0;
    for (int i = 0; i < ticketsTable->rowCount(); ++i) {
        QString status = ticketsTable->item(i, 3)->text().toLower();
        if (status.contains("available")) available++;
        else if (status.contains("sold")) sold++;
        else if (status.contains("reserved")) reserved++;
    }

    series->clear();
    series->append("Available", available);
    series->append("Sold", sold);
    series->append("Reserved", reserved);

    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
    }
}
