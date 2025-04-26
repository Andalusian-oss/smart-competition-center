#include "terrianspage.h"
#include <QHeaderView>

TerrainsPage::TerrainsPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void TerrainsPage::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Terrains Management");
    title->setStyleSheet("font-size: 20px; font-weight: bold;");
    layout->addWidget(title);

    terrainsTable = new QTableWidget(this);
    terrainsTable->setColumnCount(3);
    terrainsTable->setHorizontalHeaderLabels(QStringList() << "Terrain ID" << "Name" << "Location");
    terrainsTable->horizontalHeader()->setStretchLastSection(true);
    terrainsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    terrainsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layout->addWidget(terrainsTable);

    addButton = new QPushButton("➕ Add Terrain");
    layout->addWidget(addButton);
    QPieSeries *series = new QPieSeries();
    series->append("North Location", 2);
    series->append("South Location", 1);
    series->append("Central Location", 2);

    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Terrain Locations");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(250);

    layout->addWidget(chartView);
}
