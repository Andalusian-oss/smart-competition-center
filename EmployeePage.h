#ifndef EMPLOYEEPAGE_H
#define EMPLOYEEPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

class EmployeeTable : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeTable(QWidget *parent = nullptr);

private:
    QTableWidget *table;
    QPushButton *addButton;
    QLineEdit *searchBar;
    QChartView *chartView;
    void setupUI();
    void applyTailwindStyles();
    void populateData();
    void addEmployeeRow(const QStringList &data);
    void filterTable(const QString &text);
    void showAddDialog();
    void showEditDialog(int row);
    void deleteEmployee(int row);
    QLineEdit* createFormInput(const QString &placeholder);
    void onHeaderClicked(int logicalIndex);
};

#endif // EMPLOYEEPAGE_H
