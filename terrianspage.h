#ifndef TERRIANSPAGE_H
#define TERRIANSPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
class TerrainsPage : public QWidget
{
    Q_OBJECT

public:
    explicit TerrainsPage(QWidget *parent = nullptr);

private:
    QTableWidget *terrainsTable;
    QPushButton *addButton;
    QChartView *chartView;
    void setupUI();
};

#endif // TERRIANSPAGE_H
