#ifndef ARBITREPAGE_H
#define ARBITREPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
class ArbitrePage : public QWidget
{
    Q_OBJECT

public:
    explicit ArbitrePage(QWidget *parent = nullptr);

private:
    void setupUI();

    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QTableWidget *arbitresTable;
    QPushButton *addArbitreButton;
    QChartView *chartView;
};

#endif // ARBITREPAGE_H
