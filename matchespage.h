#ifndef MATCHESPAGE_H
#define MATCHESPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QChartView>
#include <QPieSeries>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QToolButton>
#include <QHeaderView>

class MatchesPage : public QWidget
{
    Q_OBJECT

public:
    explicit MatchesPage(QWidget *parent = nullptr);

private slots:
    void filterMatches(const QString &text);
    void sortTable(int column);

private:
    void setupUI();
    void setupTableHeader();
    void populateTable();

    // UI Elements
    QLabel *titleLabel;
    QTableWidget *matchesTable;
    QChartView *chartView;
    QLineEdit *searchLineEdit;
    QToolButton *searchButton;
    QToolButton *sortButton;

    // CRUD Buttons
    QPushButton *addMatchButton;
    QPushButton *editMatchButton;
    QPushButton *deleteMatchButton;
    QPushButton *viewMatchButton;

    // Layouts
    QVBoxLayout *mainLayout;
    bool currentSortOrder;
};

#endif // MATCHESPAGE_H
