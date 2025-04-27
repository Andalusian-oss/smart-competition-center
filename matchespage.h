#ifndef MATCHESPAGE_H
#define MATCHESPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MatchesPage : public QWidget
{
    Q_OBJECT

public:
    explicit MatchesPage(QWidget *parent = nullptr);

private slots:
    void addMatch();
    void editSelectedMatch();
    void deleteSelectedMatch();
    void viewSelectedMatch();

private:
    void setupUI();
    void openMatchDialog(bool isEdit = false, int row = -1);
    void refreshChart();

    QLabel *titleLabel;
    QTableWidget *matchesTable;
    QChartView *chartView;

    // CRUD Buttons
    QPushButton *addMatchButton;
    QPushButton *editMatchButton;
    QPushButton *deleteMatchButton;
    QPushButton *viewMatchButton;

    QVBoxLayout *mainLayout;
    QPieSeries *series;
};

#endif // MATCHESPAGE_H
