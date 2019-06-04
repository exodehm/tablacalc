#include "myeventfilter.h"
#include "./mitabla.h"
#include <QPushButton>
//#include <QTableView>
#include <QModelIndex>
#include <QEvent>
#include <QHoverEvent>
#include <QMouseEvent>
#include <QDebug>

MyEventFilter::MyEventFilter(MiTabla *table, QObject* parent): QObject(parent),table(table),button(new QPushButton(table))
{
    button->setText("H");
    button->setFixedSize(20, 20);
    button->setVisible(false);

    table->installEventFilter(this);
    table->setAttribute(Qt::WA_Hover);

    connect(button, SIGNAL(clicked()), SLOT(button_clicked()));    
}

bool MyEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if( event->type() == QEvent::HoverMove)
    {
        QHoverEvent * hoverEvent = static_cast<QHoverEvent*>(event);
        QPoint pos = table->viewport()->mapFromParent(hoverEvent->pos());
        //establecer puntero del raton
        if (table->selectionModel()->selectedIndexes().size()>0)//si hay alguna celda seleccionada
        {
            QRect rectSelect = table->visualRect(table->selectionModel()->currentIndex());

            if (pos.x()>=rectSelect.bottomRight().x()-table->LeeTamMarca() &&
                    pos.x()<=rectSelect.bottomRight().x() &&
                    pos.y()>=rectSelect.bottomRight().y()-table->LeeTamMarca() &&
                    pos.y()<=rectSelect.bottomRight().y())
            {
                if (!table->BotonIzquierdoPresionado())
                {
                    table->setCursor(Qt::CrossCursor);
                    table->SetModoSeleccionRestringido();
                }
            }
            else
            {
                table->setCursor(Qt::ArrowCursor);
                if (!table->BotonIzquierdoPresionado())
                {
                    table->SetModoSeleccionNormal();
                }
            }
        }
        //boton en la tercera columna
        currentIndex = table->indexAt(pos);
        QRect rect = table->visualRect(currentIndex);
        button->setVisible(currentIndex.isValid() && currentIndex.column() == 3);

        if( button->isVisible() )
        {
            QPoint point = rect.topRight();
            point.setX(point.x() - button->width());
            button->move(table->viewport()->mapToParent(point));
        }
        event->accept();
        return true;
    }
    else if (event->type() == QEvent::MouseButtonRelease)//quito la cruceta del puntero
    {
        table->setCursor(Qt::ArrowCursor);
        //retorno false para propagar el evento a la tabla y que la funcion tabla::mouseReleaseEvent termine de hacer otras cosas
        //las he puesto ahi por mantener las funciones mas cercanas a la tabla
        //si no, todo se haria desde el filtro de eventos y no haría falta definir mouseReleaseEvent en la tabla
        return false;
    }   
    return QObject::eventFilter(obj,event);
}

void MyEventFilter::button_clicked()
{
    qDebug()<<"button clicked";
}


