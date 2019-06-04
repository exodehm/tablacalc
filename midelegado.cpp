#include "./midelegado.h"
#include "./mimodelo.h"
#include "./mitabla.h"
#include <QDebug>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>

MiDelegado::MiDelegado(QObject *parent):QStyledItemDelegate(parent)
{

}

void MiDelegado::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{    
    QPen morado;
    QPen verde;
    morado.setColor(Qt::magenta);
    verde.setColor(Qt::darkGreen);

    if (index.data().toInt()<58)//numeros
    {
        painter->save();
        painter->setPen(morado);
        //painter->setBrush(QColor(255,255,170));
        //painter->drawRect(option.rect);
        painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter, index.data().toString());
        painter->restore();
    }
    else
    {
        painter->save();
        painter->setPen(verde);
        painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter, index.data().toString());
        painter->restore();
    }
    //QStyledItemDelegate::paint(painter,option,index);

}
