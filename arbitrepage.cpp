#include "arbitrepage.h"
#include <QHeaderView>

ArbitrePage::ArbitrePage(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void ArbitrePage::setupUI()
{
    mainLayout = new QVBoxLayout(this);

    titleLabel = new QLabel("🧑‍⚖️ List of Referees", this);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 18px;");
    mainLayout->addWidget(titleLabel);

    arbitresTable = new QTableWidget(this);
    arbitresTable->setColumnCount(3);
    arbitresTable->setHorizontalHeaderLabels({"ID", "Name", "Competences"});
    arbitresTable->horizontalHeader()->setStretchLastSection(true);
    arbitresTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    arbitresTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    arbitresTable->setSelectionMode(QAbstractItemView::SingleSelection);

    // Example row
    arbitresTable->insertRow(0);
    arbitresTable->setItem(0, 0, new QTableWidgetItem("001"));
    arbitresTable->setItem(0, 1, new QTableWidgetItem("John Doe"));
    arbitresTable->setItem(0, 2, new QTableWidgetItem("Offside, Fouls, VAR Expert"));

    mainLayout->addWidget(arbitresTable);

    addArbitreButton = new QPushButton("➕ Add Referee", this);
    addArbitreButton->setStyleSheet("padding: 8px; font-weight: bold;");
    mainLayout->addWidget(addArbitreButton);

    setLayout(mainLayout);
     QPieSeries *series = new QPieSeries();
    series->append("Offside Experts", 1);
    series->append("Foul Specialists", 1);
    series->append("VAR Experts", 1);

    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Referee Competencies");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(250);

    mainLayout->addWidget(chartView);
}
