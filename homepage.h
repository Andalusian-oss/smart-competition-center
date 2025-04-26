#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QIcon>
#include <QLabel>
#include <QStackedWidget>
#include "EmployeePage.h"
#include "MatchesPage.h" // Include additional pages
#include "TeamsPage.h"// Include additional pages
#include "terrianspage.h"
#include "ticketspage.h"  // include the header
#include "arbitrepage.h"
class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);

private slots:
    void showDashboard();
    void showEmployeePage();
    void showMatchesPage();
    void showTeamsPage();
    void showTerrainsPage();
    void showTicketsPage();
    void showAIPage();
    void showArbitrePage();
    void showReportsPage();

private:
    QStackedWidget *stackedWidget;
    QWidget *dashboardPage;
    EmployeeTable *employeePage;
    MatchesPage *matchesPage; // Declare other pages
    TeamsPage *teamsPage;     // Declare other pages
    TerrainsPage *terrainsPage;
    TicketsPage *ticketsPage;
    ArbitrePage *arbitrePage;
    QChartView *chartView;
};

#endif // HOMEPAGE_H
