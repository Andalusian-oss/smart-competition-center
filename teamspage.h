#ifndef TEAMSPAGE_H
#define TEAMSPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

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
    void searchTeams(const QString &query);

private:
    void setupUI();
    void openTeamDialog(bool isEdit = false, int row = -1);
    void refreshChart();

    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLineEdit *searchBar;
    QTableWidget *teamsTable;
    QPushButton *addTeamButton;
    QPushButton *editTeamButton;
    QPushButton *deleteTeamButton;
    QPushButton *viewTeamButton;
    QPieSeries *series;
    QChartView *chartView;
};

#endif // TEAMSPAGE_H
