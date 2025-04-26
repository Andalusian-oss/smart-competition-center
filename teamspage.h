#ifndef TEAMSPAGE_H
#define TEAMSPAGE_H

#include <QWidget>
#include <QVBoxLayout>   // Include for QVBoxLayout
#include <QHBoxLayout>   // Include for QHBoxLayout
#include <QLabel>        // Include for QLabel
#include <QPushButton>   // Include for QPushButton
#include <QTableWidget>  // Include for QTableWidget
#include <QHeaderView>   // Include for QHeaderView
#include <QLineEdit>     // Include for QLineEdit
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
class TeamsPage : public QWidget
{
    Q_OBJECT

public:
    explicit TeamsPage(QWidget *parent = nullptr);

private:
    QChartView *chartView;
    void setupUI();
    void setupTitle(QVBoxLayout *layout);
    void setupCard(QVBoxLayout *layout);
    void setupSearch(QVBoxLayout *cardLayout);
    void setupTable(QVBoxLayout *cardLayout);
    void setupButtons(QVBoxLayout *layout);
};

#endif // TEAMSPAGE_H
