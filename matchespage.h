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
#include <QDialog>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QMessageBox>

class MatchesPage : public QWidget
{
    Q_OBJECT

public:
    explicit MatchesPage(QWidget *parent = nullptr);

private slots:
    void filterMatches(const QString &text);
    void sortTable(int column);
    void openAddMatchDialog();
    void editMatch(); // Edit Functionality
    void deleteMatch(); // Delete Functionality
    void viewMatch(); // View Functionality

private:
    void setupUI();
    void setupTableHeader();
    void populateTable();
    void createAddMatchDialog();

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

    // Dialog Elements
    QDialog *addMatchDialog;
    QLineEdit *matchIDEdit;
    QLineEdit *teamAEdit;
    QLineEdit *teamBEdit;
    QDateEdit *dateEdit;
};

#endif // MATCHESPAGE_H
