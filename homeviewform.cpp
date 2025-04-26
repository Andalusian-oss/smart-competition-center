#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QFont>

class HomePage : public QWidget {
public:
    HomePage(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
        applyTailwindStyles();
    }

private:
    void setupUI() {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(32, 32, 32, 32);
        mainLayout->setSpacing(24);

        QLabel *title = new QLabel("Smart Competition Center");
        title->setProperty("class", "text-3xl font-bold text-gray-800");
        title->setAlignment(Qt::AlignCenter);

        QWidget *buttonPanel = new QWidget();
        QGridLayout *grid = new QGridLayout(buttonPanel);
        grid->setSpacing(16);

        QStringList modules = {
            "Employees", "Competitions", "Teams",
            "Terrains", "Referees", "Matches",
            "Tickets", "Predictions", "Stats"
        };

        int row = 0, col = 0;
        for (const QString &name : modules) {
            QPushButton *btn = new QPushButton(name);
            btn->setProperty("class", "btn btn-primary");
            grid->addWidget(btn, row, col);

            col++;
            if (col >= 3) {
                col = 0;
                row++;
            }
        }

        mainLayout->addWidget(title);
        mainLayout->addWidget(buttonPanel);
    }

    void applyTailwindStyles() {
        this->setStyleSheet(R"(
            QWidget {
                background-color: #f8fafc;
                font-family: 'Segoe UI', sans-serif;
            }
            .btn {
                padding: 16px;
                font-size: 16px;
                font-weight: 600;
                border-radius: 12px;
                background-color: #3b82f6;
                color: white;
                border: 1px solid #2563eb;
            }
            .btn:hover {
                background-color: #2563eb;
            }
            .text-3xl {
                font-size: 32px;
            }
            .font-bold {
                font-weight: 700;
            }
            .text-gray-800 {
                color: #1e293b;
            }
        )");

        QFont defaultFont("Segoe UI", 10);
        QApplication::setFont(defaultFont);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    HomePage home;
    home.setWindowTitle("Home - Smart Competition Center");
    home.resize(1024, 640);
    home.show();

    return app.exec();
}
