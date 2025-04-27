#include "arbitrepage.h"
#include <QHeaderView>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>

ArbitrePage::ArbitrePage(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void ArbitrePage::setupUI()
{
    mainLayout = new QVBoxLayout(this);

    titleLabel = new QLabel("🧑‍⚖️ List of Referees", this);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 20px;");
    mainLayout->addWidget(titleLabel);

    arbitresTable = new QTableWidget(this);
    arbitresTable->setColumnCount(3);
    arbitresTable->setHorizontalHeaderLabels({"ID", "Name", "Competences"});
    arbitresTable->horizontalHeader()->setStretchLastSection(true);
    arbitresTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    arbitresTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    arbitresTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    arbitresTable->setSelectionMode(QAbstractItemView::SingleSelection);

    // Example row
    arbitresTable->insertRow(0);
    arbitresTable->setItem(0, 0, new QTableWidgetItem("001"));
    arbitresTable->setItem(0, 1, new QTableWidgetItem("John Doe"));
    arbitresTable->setItem(0, 2, new QTableWidgetItem("Offside, Fouls, VAR Expert"));

    mainLayout->addWidget(arbitresTable);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    addArbitreButton = new QPushButton("➕ Add Referee", this);
    editArbitreButton = new QPushButton("✏️ Edit Referee", this);
    deleteArbitreButton = new QPushButton("🗑️ Delete Referee", this);
    viewArbitreButton = new QPushButton("👀 View Referee", this);

    QString buttonStyle = R"(
        background-color: #3b82f6;
        color: white;
        font-weight: bold;
        padding: 8px 16px;
        border-radius: 8px;
        border: none;
    )";
    addArbitreButton->setStyleSheet(buttonStyle);
    editArbitreButton->setStyleSheet(buttonStyle);
    deleteArbitreButton->setStyleSheet(buttonStyle);
    viewArbitreButton->setStyleSheet(buttonStyle);

    buttonLayout->addWidget(addArbitreButton);
    buttonLayout->addWidget(editArbitreButton);
    buttonLayout->addWidget(deleteArbitreButton);
    buttonLayout->addWidget(viewArbitreButton);
    mainLayout->addLayout(buttonLayout);

    connect(addArbitreButton, &QPushButton::clicked, this, &ArbitrePage::addArbitre);
    connect(editArbitreButton, &QPushButton::clicked, this, &ArbitrePage::editSelectedArbitre);
    connect(deleteArbitreButton, &QPushButton::clicked, this, &ArbitrePage::deleteSelectedArbitre);
    connect(viewArbitreButton, &QPushButton::clicked, this, &ArbitrePage::viewSelectedArbitre);

    // Chart
    series = new QPieSeries();
    series->append("Offside Experts", 1);
    series->append("Foul Specialists", 1);
    series->append("VAR Experts", 1);

    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Referee Competencies");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(250);

    mainLayout->addWidget(chartView);

    setLayout(mainLayout);
}

// --- CRUD functions ---

void ArbitrePage::addArbitre()
{
    openArbitreDialog(false);
}

void ArbitrePage::editSelectedArbitre()
{
    int row = arbitresTable->currentRow();
    if (row >= 0)
        openArbitreDialog(true, row);
    else
        QMessageBox::warning(this, "Edit Referee", "Please select a referee to edit.");
}

void ArbitrePage::deleteSelectedArbitre()
{
    int row = arbitresTable->currentRow();
    if (row >= 0) {
        if (QMessageBox::question(this, "Delete Referee", "Are you sure you want to delete this referee?") == QMessageBox::Yes) {
            arbitresTable->removeRow(row);
            refreshChart();
        }
    } else {
        QMessageBox::warning(this, "Delete Referee", "Please select a referee to delete.");
    }
}

void ArbitrePage::viewSelectedArbitre()
{
    int row = arbitresTable->currentRow();
    if (row >= 0) {
        QString id = arbitresTable->item(row, 0)->text();
        QString name = arbitresTable->item(row, 1)->text();
        QString competences = arbitresTable->item(row, 2)->text();

        QMessageBox::information(this, "Referee Details", QString("ID: %1\nName: %2\nCompetences: %3")
                                                              .arg(id, name, competences));
    } else {
        QMessageBox::warning(this, "View Referee", "Please select a referee to view.");
    }
}

void ArbitrePage::openArbitreDialog(bool isEdit, int row)
{
    QDialog dialog(this);
    dialog.setWindowTitle(isEdit ? "Edit Referee" : "Add Referee");
    dialog.setFixedSize(400, 250);

    QFormLayout *form = new QFormLayout(&dialog);
    QLineEdit *idField = new QLineEdit();
    QLineEdit *nameField = new QLineEdit();
    QLineEdit *competencesField = new QLineEdit();

    if (isEdit && row >= 0) {
        idField->setText(arbitresTable->item(row, 0)->text());
        nameField->setText(arbitresTable->item(row, 1)->text());
        competencesField->setText(arbitresTable->item(row, 2)->text());
    }

    form->addRow("ID:", idField);
    form->addRow("Name:", nameField);
    form->addRow("Competences:", competencesField);

    QPushButton *saveBtn = new QPushButton(isEdit ? "Save Changes" : "Add Referee");
    QPushButton *cancelBtn = new QPushButton("Cancel");

    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);
    connect(saveBtn, &QPushButton::clicked, &dialog, &QDialog::accept);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(saveBtn);
    form->addRow(btnLayout);

    if (dialog.exec() == QDialog::Accepted) {
        if (idField->text().isEmpty() || nameField->text().isEmpty() || competencesField->text().isEmpty()) {
            QMessageBox::warning(this, "Warning", "All fields are required!");
            return;
        }

        if (isEdit && row >= 0) {
            arbitresTable->item(row, 0)->setText(idField->text());
            arbitresTable->item(row, 1)->setText(nameField->text());
            arbitresTable->item(row, 2)->setText(competencesField->text());
        } else {
            int newRow = arbitresTable->rowCount();
            arbitresTable->insertRow(newRow);
            arbitresTable->setItem(newRow, 0, new QTableWidgetItem(idField->text()));
            arbitresTable->setItem(newRow, 1, new QTableWidgetItem(nameField->text()));
            arbitresTable->setItem(newRow, 2, new QTableWidgetItem(competencesField->text()));
        }

        refreshChart();
    }
}

void ArbitrePage::refreshChart()
{
    int offside = 0, foul = 0, var = 0;
    for (int i = 0; i < arbitresTable->rowCount(); ++i) {
        QString competence = arbitresTable->item(i, 2)->text().toLower();
        if (competence.contains("offside")) offside++;
        if (competence.contains("foul")) foul++;
        if (competence.contains("var")) var++;
    }

    series->clear();
    series->append("Offside Experts", offside);
    series->append("Foul Specialists", foul);
    series->append("VAR Experts", var);

    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
    }
}
