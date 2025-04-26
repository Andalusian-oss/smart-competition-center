#ifndef REPORTSPAGE_H
#define REPORTSPAGE_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QVBoxLayout>
#include <QLabel>

QT_CHARTS_USE_NAMESPACE

    class ReportsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ReportsPage(QWidget *parent = nullptr);
    void setupUI();
    void createPieChart();

private:
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QChartView *chartView;
};

#endif // REPORTSPAGE_H
