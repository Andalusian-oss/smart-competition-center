#include "reportspage.h"

ReportsPage::ReportsPage(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    createPieChart();
}

void ReportsPage::setupUI()
{
    mainLayout = new QVBoxLayout(this);

    titleLabel = new QLabel("📊 Reports Dashboard", this);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; padding: 12px;");
    mainLayout->addWidget(titleLabel);

    setLayout(mainLayout);
    setStyleSheet(R"(
        QWidget {
            background-color: #f9fafb;
            font-family: 'Segoe UI', sans-serif;
        }
    )");
}

void ReportsPage::createPieChart()
{
    QPieSeries *series = new QPieSeries();
    series->append("Wins", 45);
    series->append("Losses", 30);
    series->append("Draws", 25);

    series->slices().at(0)->setBrush(QColor("#22c55e"));  // Green (Wins)
    series->slices().at(1)->setBrush(QColor("#ef4444"));  // Red (Losses)
    series->slices().at(2)->setBrush(QColor("#facc15"));  // Yellow (Draws)

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Match Outcomes Summary");
    chart->setTitleFont(QFont("Segoe UI", 12, QFont::Bold));
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(300);
    chartView->setStyleSheet("background: white; border-radius: 12px; padding: 8px;");

    mainLayout->addWidget(chartView);
}
