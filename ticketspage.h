#ifndef TICKETSPAGE_H
#define TICKETSPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
class TicketsPage : public QWidget
{
    Q_OBJECT

public:
    explicit TicketsPage(QWidget *parent = nullptr);
    void setupUI();

private:
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QTableWidget *ticketsTable;
    QPushButton *addTicketButton;
    QChartView *chartView;
};

#endif // TICKETSPAGE_H
