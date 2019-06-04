#ifndef MIDELEGADO_H
#define MIDELEGADO_H

#include <QObject>
#include <QStyledItemDelegate>

class MiDelegado : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MiDelegado(QObject* parent=nullptr);   
    void paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};

#endif // MIDELEGADO_H
