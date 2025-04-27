#ifndef TEAMSPAGE_H
#define TEAMSPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QLineEdit>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

class TeamsPage : public QWidget
{
    Q_OBJECT

public:
    explicit TeamsPage(QWidget *parent = nullptr);

private slots:
    void addTeam();
    void editSelectedTeam();
    void deleteSelectedTeam();
    void viewSelectedTeam();

private:
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QTableWidget *teamsTable;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *viewButton;
    QChartView *chartView;
    QPieSeries *series;

    void setupUI();
    void setupTitle(QVBoxLayout *layout);
    void setupCard(QVBoxLayout *layout);
    void setupSearch(QVBoxLayout *cardLayout);
    void setupTable(QVBoxLayout *cardLayout);
    void setupButtons(QVBoxLayout *layout);
    void openTeamDialog(bool isEdit = false, int row = -1);
    void refreshChart();
};

#endif // TEAMSPAGE_H
