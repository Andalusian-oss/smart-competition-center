#ifndef TERRIANSPAGE_H
#define TERRIANSPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

class TerrainsPage : public QWidget
{
    Q_OBJECT

public:
    explicit TerrainsPage(QWidget *parent = nullptr);

private slots:
    void addTerrain();
    void editSelectedTerrain();
    void deleteSelectedTerrain();
    void viewSelectedTerrain();

private:
    void setupUI();
    void openTerrainDialog(bool isEdit = false, int row = -1);
    void refreshChart();

    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QTableWidget *terrainsTable;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *viewButton;
    QChartView *chartView;
    QPieSeries *series;
};

#endif // TERRIANSPAGE_H
