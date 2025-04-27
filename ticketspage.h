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

private slots:
    void addTicket();
    void editSelectedTicket();
    void deleteSelectedTicket();
    void viewSelectedTicket();

private:
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QTableWidget *ticketsTable;
    QPushButton *addTicketButton;
    QPushButton *editTicketButton;
    QPushButton *deleteTicketButton;
    QPushButton *viewTicketButton;
    QChartView *chartView;
    QPieSeries *series;

    void openTicketDialog(bool isEdit = false, int row = -1);
    void refreshChart();
};

#endif // TICKETSPAGE_H
