#ifndef MYEVENTFILTER_H
#define MYEVENTFILTER_H

#include <QObject>
#include <QModelIndex>

class MiTabla;
class QPushButton;

class MyEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit MyEventFilter(MiTabla* table, QObject* parent=nullptr);
    bool eventFilter(QObject *obj, QEvent *event) override;


private slots:
    void button_clicked();
    //void CambiarIndiceActual(const QModelIndex& indice);

private:
    MiTabla* table;
    QPushButton * button;
    QModelIndex currentIndex;
    //QModelIndex selectedIndex;
};

#endif // MYEVENTFILTER_H
