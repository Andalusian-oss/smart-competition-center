#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QFormLayout>
#include <QIcon>
#include <QFont>

class EmployeeTable : public QWidget {
public:
    EmployeeTable(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
        applyTailwindStyles();
        populateData();
    }

private:
    QTableWidget *table;
    QPushButton *addButton;
    QLineEdit *searchBar;

    void setupUI() {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(16, 16, 16, 16);
        mainLayout->setSpacing(16);

        QWidget *headerWidget = new QWidget();
        QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
        headerLayout->setContentsMargins(0, 0, 0, 0);

        QLabel *title = new QLabel("Employee Manager");
        title->setProperty("class", "text-2xl font-bold text-gray-800");

        searchBar = new QLineEdit();
        searchBar->setPlaceholderText("Search employees...");
        searchBar->setProperty("class", "input");

        addButton = new QPushButton("Add Employee");
        addButton->setProperty("class", "btn btn-primary");
        addButton->setIcon(QIcon::fromTheme("list-add"));

        headerLayout->addWidget(title);
        headerLayout->addStretch();
        headerLayout->addWidget(searchBar);
        headerLayout->addWidget(addButton, 0, Qt::AlignRight);

        table = new QTableWidget();
        table->setColumnCount(5);
        table->setHorizontalHeaderLabels({"ID", "Name", "Department", "Email", "Actions"});
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->verticalHeader()->setVisible(false);
        table->setProperty("class", "card");

        mainLayout->addWidget(headerWidget);
        mainLayout->addWidget(table);

        connect(addButton, &QPushButton::clicked, this, &EmployeeTable::showAddDialog);
        connect(searchBar, &QLineEdit::textChanged, this, &EmployeeTable::filterTable);
    }

    void applyTailwindStyles() {
        this->setStyleSheet(
            R"(
            QWidget {
                background-color: #f8fafc;
                font-family: 'Segoe UI', sans-serif;
            }
            .card {
                background: white;
                border-radius: 8px;
                border: 1px solid #e2e8f0;
                padding: 8px;
            }
            .btn {
                padding: 8px 16px;
                border-radius: 6px;
                font-weight: 500;
                transition: all 0.15s ease;
            }
            .btn-primary {
                background-color: #3b82f6;
                color: white;
                border: 1px solid #2563eb;
            }
            .btn-primary:hover {
                background-color: #2563eb;
            }
            .btn-danger {
                background-color: #ef4444;
                color: white;
                border: 1px solid #dc2626;
            }
            .btn-danger:hover {
                background-color: #dc2626;
            }
            .input {
                padding: 8px 12px;
                border: 1px solid #cbd5e1;
                border-radius: 6px;
                min-width: 300px;
            }
            .input:focus {
                border-color: #3b82f6;
                outline: none;
            }
            QHeaderView::section {
                background-color: #f1f5f9;
                color: #64748b;
                padding: 12px;
                border: none;
                font-weight: 600;
            }
            .text-2xl {
                font-size: 24px;
            }
            .font-bold {
                font-weight: 700;
            }
            .text-gray-800 {
                color: #1e293b;
            }
            )"
            );

        QFont defaultFont("Segoe UI", 10);
        QApplication::setFont(defaultFont);
    }

    void populateData() {
        addEmployeeRow({"1", "John Doe", "Engineering", "john@company.com"});
        addEmployeeRow({"2", "Jane Smith", "Marketing", "jane@company.com"});
        addEmployeeRow({"3", "Bob Wilson", "Sales", "bob@company.com"});
    }

    void addEmployeeRow(const QStringList &data) {
        int row = table->rowCount();
        table->insertRow(row);

        for(int col = 0; col < data.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(data[col]);
            item->setTextAlignment(Qt::AlignCenter);
            table->setItem(row, col, item);
        }

        QWidget *btnWidget = new QWidget();
        QHBoxLayout *btnLayout = new QHBoxLayout(btnWidget);
        btnLayout->setContentsMargins(0, 0, 0, 0);
        btnLayout->setSpacing(8);

        QPushButton *editBtn = new QPushButton("Edit");
        editBtn->setProperty("class", "btn btn-primary");
        QPushButton *deleteBtn = new QPushButton("Delete");
        deleteBtn->setProperty("class", "btn btn-danger");

        connect(editBtn, &QPushButton::clicked, [this, row]() { showEditDialog(row); });
        connect(deleteBtn, &QPushButton::clicked, [this, row]() { deleteEmployee(row); });

        btnLayout->addWidget(editBtn);
        btnLayout->addWidget(deleteBtn);
        table->setCellWidget(row, 4, btnWidget);
        table->resizeRowsToContents();
        filterTable(searchBar->text());
    }

    void filterTable(const QString &text) {
        QString searchText = text.trimmed().toLower();
        for(int row = 0; row < table->rowCount(); ++row) {
            bool match = false;
            for(int col = 0; col < table->columnCount() - 1; ++col) {
                if(table->item(row, col)->text().toLower().contains(searchText)) {
                    match = true;
                    break;
                }
            }
            table->setRowHidden(row, !match);
        }
    }

    void showAddDialog() {
        QDialog dialog(this);
        dialog.setProperty("class", "card");
        dialog.setWindowTitle("Add Employee");
        dialog.setFixedSize(400, 300);

        QFormLayout *form = new QFormLayout(&dialog);
        form->setContentsMargins(16, 16, 16, 16);
        form->setSpacing(12);

        QLineEdit *idField = createFormInput("ID:");
        QLineEdit *nameField = createFormInput("Name:");
        QLineEdit *deptField = createFormInput("Department:");
        QLineEdit *emailField = createFormInput("Email:");

        form->addRow("ID:", idField);
        form->addRow("Name:", nameField);
        form->addRow("Department:", deptField);
        form->addRow("Email:", emailField);

        QPushButton *submitBtn = new QPushButton("Add Employee");
        submitBtn->setProperty("class", "btn btn-primary");
        QPushButton *cancelBtn = new QPushButton("Cancel");
        cancelBtn->setProperty("class", "btn");

        QHBoxLayout *btnLayout = new QHBoxLayout();
        btnLayout->addStretch();
        btnLayout->addWidget(cancelBtn);
        btnLayout->addWidget(submitBtn);
        form->addRow(btnLayout);

        connect(submitBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
        connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);

        if(dialog.exec() == QDialog::Accepted) {
            if(!idField->text().isEmpty() && !nameField->text().isEmpty()) {
                addEmployeeRow({
                    idField->text(),
                    nameField->text(),
                    deptField->text(),
                    emailField->text()
                });
            } else {
                QMessageBox::warning(this, "Warning", "ID and Name are required fields!");
            }
        }
    }

    void showEditDialog(int row) {
        QDialog dialog(this);
        dialog.setProperty("class", "card");
        dialog.setWindowTitle("Edit Employee");
        dialog.setFixedSize(400, 300);

        QFormLayout *form = new QFormLayout(&dialog);
        form->setContentsMargins(16, 16, 16, 16);
        form->setSpacing(12);

        QLineEdit *idField = createFormInput("ID:");
        QLineEdit *nameField = createFormInput("Name:");
        QLineEdit *deptField = createFormInput("Department:");
        QLineEdit *emailField = createFormInput("Email:");

        idField->setText(table->item(row, 0)->text());
        nameField->setText(table->item(row, 1)->text());
        deptField->setText(table->item(row, 2)->text());
        emailField->setText(table->item(row, 3)->text());

        form->addRow("ID:", idField);
        form->addRow("Name:", nameField);
        form->addRow("Department:", deptField);
        form->addRow("Email:", emailField);

        QPushButton *submitBtn = new QPushButton("Save Changes");
        submitBtn->setProperty("class", "btn btn-primary");
        QPushButton *cancelBtn = new QPushButton("Cancel");
        cancelBtn->setProperty("class", "btn");

        QHBoxLayout *btnLayout = new QHBoxLayout();
        btnLayout->addStretch();
        btnLayout->addWidget(cancelBtn);
        btnLayout->addWidget(submitBtn);
        form->addRow(btnLayout);

        connect(submitBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
        connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);

        if(dialog.exec() == QDialog::Accepted) {
            table->item(row, 0)->setText(idField->text());
            table->item(row, 1)->setText(nameField->text());
            table->item(row, 2)->setText(deptField->text());
            table->item(row, 3)->setText(emailField->text());
        }
    }

    QLineEdit* createFormInput(const QString &placeholder) {
        QLineEdit *input = new QLineEdit();
        input->setProperty("class", "input");
        input->setPlaceholderText(placeholder);
        return input;
    }

    void deleteEmployee(int row) {
        QMessageBox confirmDialog(this);
        confirmDialog.setWindowTitle("Confirm Delete");
        confirmDialog.setText("Are you sure you want to delete this employee?");
        confirmDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        confirmDialog.setDefaultButton(QMessageBox::No);
        confirmDialog.setProperty("class", "card");

        if(confirmDialog.exec() == QMessageBox::Yes) {
            table->removeRow(row);
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    EmployeeTable window;
    window.resize(1280, 720);
    window.setWindowTitle("Employee Management System");
    window.show();

    return app.exec();
}
