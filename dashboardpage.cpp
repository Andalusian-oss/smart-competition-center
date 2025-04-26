#include "dashboardpage.h"
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QCalendarWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>


DashboardPage::DashboardPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void DashboardPage::setupUI()
{
    // Main layout for the page
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Title label
    titleLabel = new QLabel("Welcome to our smart Football center   ", this);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 24px;");
    mainLayout->addWidget(titleLabel);

    // Add match button
    addMatchButton = new QPushButton("➕ Add Match", this);
    addMatchButton->setStyleSheet("padding: 8px; font-weight: bold;");
    mainLayout->addWidget(addMatchButton);

    // Add the Team Participation Chart
    teamParticipationChartView = createTeamParticipationChart();
    mainLayout->addWidget(teamParticipationChartView);

    // Add calendar widget
    calendarWidget = new QCalendarWidget(this);
    calendarWidget->setStyleSheet("background-color: white;");
    mainLayout->addWidget(calendarWidget);

    // Add weather frame
    weatherFrame = createWeatherFrame();
    mainLayout->addWidget(weatherFrame);

    // Add news frame
    newsFrame = createNewsFrame();
    mainLayout->addWidget(newsFrame);

    setLayout(mainLayout);
}

QChartView *DashboardPage::createTeamParticipationChart()
{
    // Create a pie chart for team participation
    QPieSeries *series = new QPieSeries();
    series->append("Team Alpha", 2);
    series->append("Team Beta", 1);
    series->append("Team Gamma", 2);
    series->append("Team Delta", 1);

    // Customize slices
    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
        slice->setLabelPosition(QPieSlice::LabelOutside);
    }

    // Create and customize the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Team Participation in Matches");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Create chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(300);

    return chartView;
}

QFrame *DashboardPage::createWeatherFrame()
{
    // Placeholder for the weather section (you can replace this with actual weather info)
    QFrame *frame = new QFrame(this);
    QVBoxLayout *layout = new QVBoxLayout(frame);

    QLabel *weatherLabel = new QLabel("☀️ Current Weather: 25°C", this);
    layout->addWidget(weatherLabel);

    frame->setLayout(layout);
    frame->setStyleSheet("background-color: #f2f2f2; padding: 10px;");
    return frame;
}

QFrame *DashboardPage::createNewsFrame()
{
    // Placeholder for the news section (you can replace this with actual news info)
    QFrame *frame = new QFrame(this);
    QVBoxLayout *layout = new QVBoxLayout(frame);

    QLabel *newsLabel = new QLabel("📰 Latest News: Football Tournament Results", this);
    layout->addWidget(newsLabel);

    frame->setLayout(layout);
    frame->setStyleSheet("background-color: #f2f2f2; padding: 10px;");
    return frame;
}
