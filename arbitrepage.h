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

private slots:
    void addArbitre();
    void editSelectedArbitre();
    void deleteSelectedArbitre();
    void viewSelectedArbitre();

private:
    void setupUI();
    void openArbitreDialog(bool isEdit = false, int row = -1);
    void refreshChart();

    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QTableWidget *arbitresTable;
    QPushButton *addArbitreButton;
    QPushButton *editArbitreButton;
    QPushButton *deleteArbitreButton;
    QPushButton *viewArbitreButton;
    QChartView *chartView;
    QPieSeries *series;
};

#endif // ARBITREPAGE_H
