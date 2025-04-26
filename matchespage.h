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

class MatchesPage : public QWidget
{
    Q_OBJECT

public:
    explicit MatchesPage(QWidget *parent = nullptr);

private:
    void setupUI();

    QLabel *titleLabel;
    QTableWidget *matchesTable;
    QChartView *chartView;

    // CRUD Buttons
    QPushButton *addMatchButton;
    QPushButton *editMatchButton;
    QPushButton *deleteMatchButton;
    QPushButton *viewMatchButton;

    QVBoxLayout *mainLayout;
};

#endif // MATCHESPAGE_H
