#include "HomePage.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QIcon>
#include <QLabel>
#include "EmployeePage.h"
#include "MatchesPage.h"
#include "TeamsPage.h"
#include "terrianspage.h"
#include "TicketsPage.h"
#include "ArbitrePage.h"
#include "DashboardPage.h"

HomePage::HomePage(QWidget *parent) : QWidget(parent)
{
    // --- Top Navigation Bar ---
    QHBoxLayout *topNavLayout = new QHBoxLayout();

    QPushButton *dashboardButton = new QPushButton("🏠 Dashboard");
    QPushButton *traductionButton = new QPushButton("🌐 Tradution");
    QPushButton *settingsButton = new QPushButton("⚙ Settings");
    QPushButton *logoutButton = new QPushButton("☾ Dark Mode");

    topNavLayout->addWidget(dashboardButton);
    topNavLayout->addWidget(settingsButton);
    topNavLayout->addStretch();
    topNavLayout->addWidget(traductionButton);
    topNavLayout->addWidget(logoutButton);

    // Wrap topNav in a QWidget to apply background + shadow
    QWidget *topNavWidget = new QWidget();
    topNavWidget->setLayout(topNavLayout);
    topNavWidget->setStyleSheet(R"(
        background-color: #f8fafc;
        border-bottom: 1px solid #cbd5e1;
        padding: 10px 20px;
        margin-bottom: 8px;
    )");

    // Style buttons (Tailwind-inspired)
    QString navButtonStyle = R"(
        QPushButton {
            background-color: transparent;
            color: #1e293b;
            font-weight: 600;
            font-size: 16px;
            padding: 8px 16px;
            border-radius: 8px;
        }
        QPushButton:hover {
            background-color: #e2e8f0;
        }
    )";
    dashboardButton->setStyleSheet(navButtonStyle);
    settingsButton->setStyleSheet(navButtonStyle);

    logoutButton->setStyleSheet(R"(
        QPushButton {
            background-color: #000000;
            color: white;
            font-weight: bold;
            padding: 8px 16px;
            border-radius: 8px;
        }
        QPushButton:hover {

        }
    )");

    // --- Sidebar ---
    QListWidget *sideMenu = new QListWidget();
    sideMenu->addItem("👤 Employees");
    sideMenu->addItem("⚽ Matches");
    sideMenu->addItem("👥 Teams");
    sideMenu->addItem("🏟 Terrains");
    sideMenu->addItem("🎟 Tickets");
    sideMenu->addItem("🙋🏽‍ Arbitres");
    sideMenu->addItem("🔮 AI");
    sideMenu->addItem("📊 Reports");

    // --- Pages ---
    stackedWidget = new QStackedWidget(this);

    dashboardPage = new DashboardPage();  // Initialized as DashboardPage
    employeePage = new EmployeeTable();
    matchesPage = new MatchesPage();
    teamsPage = new TeamsPage();
    terrainsPage = new TerrainsPage();
    ticketsPage = new TicketsPage();
    arbitrePage = new ArbitrePage();

    stackedWidget->addWidget(dashboardPage);
    stackedWidget->addWidget(employeePage);
    stackedWidget->addWidget(matchesPage);
    stackedWidget->addWidget(teamsPage);
    stackedWidget->addWidget(terrainsPage);
    stackedWidget->addWidget(ticketsPage);
    stackedWidget->addWidget(arbitrePage);

    // --- Main layout ---
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QWidget *sidebarWidget = new QWidget(this);
    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebarWidget);
    sidebarLayout->addWidget(sideMenu);
    sidebarLayout->setContentsMargins(0, 0, 0, 0);

    sidebarWidget->setStyleSheet(R"(
        background-color: #3b556d;
        color: white;
        font-family: 'Segoe UI', sans-serif;
        font-size: 16px;
        border-right: 2px solid #1A252F;
        margin-top: 10px;
    )");

    mainLayout->addWidget(sidebarWidget, 1);
    mainLayout->addWidget(stackedWidget, 3);

    QVBoxLayout *topLayout = new QVBoxLayout();
    topLayout->addWidget(topNavWidget); // ⬅️ Top Nav Widget with style
    topLayout->addLayout(mainLayout);

    setLayout(topLayout);

    // --- Signal Connections ---
    connect(sideMenu, &QListWidget::currentRowChanged, this, [this](int index) {
        switch (index) {
        case 0: showEmployeePage(); break;
        case 1: showMatchesPage(); break;
        case 2: showTeamsPage(); break;
        case 3: showTerrainsPage(); break;
        case 4: showTicketsPage(); break;
        case 5: showArbitrePage(); break;
        case 6: showAIPage(); break;
        case 7: showReportsPage(); break;
        default: showDashboard(); break;
        }
    });

    // Connect the dashboard button to showDashboard
    connect(dashboardButton, &QPushButton::clicked, this, &HomePage::showDashboard);
}

// --- Page Routing Functions ---
void HomePage::showDashboard() {
    stackedWidget->setCurrentWidget(dashboardPage);  // Show DashboardPage when Dashboard button is clicked
}

void HomePage::showEmployeePage() {
    stackedWidget->setCurrentWidget(employeePage);
}

void HomePage::showMatchesPage() {
    stackedWidget->setCurrentWidget(matchesPage);
}

void HomePage::showTeamsPage() {
    stackedWidget->setCurrentWidget(teamsPage);
}

void HomePage::showTerrainsPage() {
    stackedWidget->setCurrentWidget(terrainsPage);
}

void HomePage::showTicketsPage() {
    stackedWidget->setCurrentWidget(ticketsPage);
}

void HomePage::showArbitrePage() {
    stackedWidget->setCurrentWidget(arbitrePage);
}

void HomePage::showAIPage() {
    // AI Page logic goes here
}

void HomePage::showReportsPage() {
    // Reports Page logic goes here
}
