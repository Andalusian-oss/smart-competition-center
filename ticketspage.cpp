#include "ticketspage.h"
#include <QHeaderView>
#include <QTableWidgetItem>

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

    // Add Ticket Button
    addTicketButton = new QPushButton("➕ Add Ticket", this);
    addTicketButton->setStyleSheet(R"(
        background-color: #3b82f6;
        color: white;
        padding: 8px 16px;
        font-weight: bold;
        border: none;
        border-radius: 8px;
    )");
    mainLayout->addWidget(addTicketButton, 0, Qt::AlignLeft);

    setLayout(mainLayout);
    QPieSeries *series = new QPieSeries();
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
}
