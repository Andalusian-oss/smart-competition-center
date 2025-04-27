#ifndef TICKETSPAGE_H
#define TICKETSPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QDateTimeEdit>

class TicketsPage : public QWidget
{
    Q_OBJECT

public:
    explicit TicketsPage(QWidget *parent = nullptr);

private slots:
    void addTicket();
    void editSelectedTicket();
    void deleteSelectedTicket();
    void viewSelectedTicket();
    void searchTickets();
    void sortTickets(int index);

private:
    QTableWidget *ticketsTable;
    QPushButton *addTicketButton;
    QPushButton *editTicketButton;
    QPushButton *deleteTicketButton;
    QPushButton *viewTicketButton;
    QLineEdit *searchBar;
    QComboBox *sortComboBox;

    void setupUI();
    void populateTable();
    void addOrEditTicketDialog(bool isEdit, int row);  // New method to handle add/edit dialogs
};

#endif // TICKETSPAGE_H
