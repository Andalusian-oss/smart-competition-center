#ifndef DASHBOARDPAGE_H
#define DASHBOARDPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCalendarWidget>
#include <QFrame>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>

class DashboardPage : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardPage(QWidget *parent = nullptr);
    void setupUI();

private:
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QChartView *teamParticipationChartView;
    QPushButton *addMatchButton;
    QCalendarWidget *calendarWidget;
    QFrame *weatherFrame;
    QFrame *newsFrame;

    QChartView *createTeamParticipationChart();
    QFrame *createWeatherFrame();
    QFrame *createNewsFrame();
};

#endif // DASHBOARDPAGE_H
