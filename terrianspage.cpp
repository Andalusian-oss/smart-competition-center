#include "terrianspage.h"
#include <QHeaderView>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>

TerrainsPage::TerrainsPage(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void TerrainsPage::setupUI()
{
    mainLayout = new QVBoxLayout(this);

    titleLabel = new QLabel("Terrains Management", this);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    terrainsTable = new QTableWidget(this);
    terrainsTable->setColumnCount(3);
    terrainsTable->setHorizontalHeaderLabels(QStringList() << "Terrain ID" << "Name" << "Location");
    terrainsTable->horizontalHeader()->setStretchLastSection(true);
    terrainsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    terrainsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    terrainsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(terrainsTable);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    addButton = new QPushButton("➕ Add Terrain", this);
    editButton = new QPushButton("✏️ Edit Terrain", this);
    deleteButton = new QPushButton("🗑️ Delete Terrain", this);
    viewButton = new QPushButton("👀 View Terrain", this);

    QString buttonStyle = R"(
        background-color: #3b82f6;
        color: white;
        padding: 8px 16px;
        font-weight: bold;
        border: none;
        border-radius: 8px;
    )";

    addButton->setStyleSheet(buttonStyle);
    editButton->setStyleSheet(buttonStyle);
    deleteButton->setStyleSheet(buttonStyle);
    viewButton->setStyleSheet(buttonStyle);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(viewButton);

    mainLayout->addLayout(buttonLayout);

    // Chart
    series = new QPieSeries();
    series->append("North Location", 2);
    series->append("South Location", 1);
    series->append("Central Location", 2);

    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Terrain Locations");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(250);

    mainLayout->addWidget(chartView);

    setLayout(mainLayout);

    // Connect buttons
    connect(addButton, &QPushButton::clicked, this, &TerrainsPage::addTerrain);
    connect(editButton, &QPushButton::clicked, this, &TerrainsPage::editSelectedTerrain);
    connect(deleteButton, &QPushButton::clicked, this, &TerrainsPage::deleteSelectedTerrain);
    connect(viewButton, &QPushButton::clicked, this, &TerrainsPage::viewSelectedTerrain);
}

// --- CRUD functions ---

void TerrainsPage::addTerrain()
{
    openTerrainDialog(false);
}

void TerrainsPage::editSelectedTerrain()
{
    int row = terrainsTable->currentRow();
    if (row >= 0)
        openTerrainDialog(true, row);
    else
        QMessageBox::warning(this, "Edit Terrain", "Please select a terrain to edit.");
}

void TerrainsPage::deleteSelectedTerrain()
{
    int row = terrainsTable->currentRow();
    if (row >= 0) {
        if (QMessageBox::question(this, "Delete Terrain", "Are you sure you want to delete this terrain?") == QMessageBox::Yes) {
            terrainsTable->removeRow(row);
            refreshChart();
        }
    } else {
        QMessageBox::warning(this, "Delete Terrain", "Please select a terrain to delete.");
    }
}

void TerrainsPage::viewSelectedTerrain()
{
    int row = terrainsTable->currentRow();
    if (row >= 0) {
        QString id = terrainsTable->item(row, 0)->text();
        QString name = terrainsTable->item(row, 1)->text();
        QString location = terrainsTable->item(row, 2)->text();

        QMessageBox::information(this, "Terrain Details", QString("ID: %1\nName: %2\nLocation: %3")
                                                              .arg(id, name, location));
    } else {
        QMessageBox::warning(this, "View Terrain", "Please select a terrain to view.");
    }
}

void TerrainsPage::openTerrainDialog(bool isEdit, int row)
{
    QDialog dialog(this);
    dialog.setWindowTitle(isEdit ? "Edit Terrain" : "Add Terrain");
    dialog.setFixedSize(400, 250);

    QFormLayout *form = new QFormLayout(&dialog);
    QLineEdit *idField = new QLineEdit();
    QLineEdit *nameField = new QLineEdit();
    QLineEdit *locationField = new QLineEdit();

    if (isEdit && row >= 0) {
        idField->setText(terrainsTable->item(row, 0)->text());
        nameField->setText(terrainsTable->item(row, 1)->text());
        locationField->setText(terrainsTable->item(row, 2)->text());
    }

    form->addRow("Terrain ID:", idField);
    form->addRow("Name:", nameField);
    form->addRow("Location:", locationField);

    QPushButton *saveBtn = new QPushButton(isEdit ? "Save Changes" : "Add Terrain");
    QPushButton *cancelBtn = new QPushButton("Cancel");
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);
    connect(saveBtn, &QPushButton::clicked, &dialog, &QDialog::accept);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(saveBtn);
    form->addRow(btnLayout);

    if (dialog.exec() == QDialog::Accepted) {
        if (idField->text().isEmpty() || nameField->text().isEmpty() || locationField->text().isEmpty()) {
            QMessageBox::warning(this, "Warning", "All fields are required!");
            return;
        }

        if (isEdit && row >= 0) {
            terrainsTable->item(row, 0)->setText(idField->text());
            terrainsTable->item(row, 1)->setText(nameField->text());
            terrainsTable->item(row, 2)->setText(locationField->text());
        } else {
            int newRow = terrainsTable->rowCount();
            terrainsTable->insertRow(newRow);
            terrainsTable->setItem(newRow, 0, new QTableWidgetItem(idField->text()));
            terrainsTable->setItem(newRow, 1, new QTableWidgetItem(nameField->text()));
            terrainsTable->setItem(newRow, 2, new QTableWidgetItem(locationField->text()));
        }

        refreshChart();
    }
}

void TerrainsPage::refreshChart()
{
    // Rebuild the pie chart based on locations
    QMap<QString, int> locationCounts;

    for (int i = 0; i < terrainsTable->rowCount(); ++i) {
        QString location = terrainsTable->item(i, 2)->text();
        locationCounts[location]++;
    }

    series->clear();
    for (auto it = locationCounts.begin(); it != locationCounts.end(); ++it) {
        series->append(it.key(), it.value());
    }

    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
    }
}
