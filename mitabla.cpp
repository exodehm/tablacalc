#include "./mitabla.h"
#include "./mimodelo.h"
#include "./myeventfilter.h"
#include "./midelegado.h"
#include <QMouseEvent>
#include <QPen>
#include <QPainter>
#include <QDebug>

MiTabla::MiTabla(QWidget *parent):QTableView(parent)
{
    m_tamMarca = 5;
    setModel((new MiModelo(this)));
    setMouseTracking(true);
    setItemDelegate(new MiDelegado(this));
    viewport()->installEventFilter(new MyEventFilter(this));

    QObject::connect(this,SIGNAL(pressed(QModelIndex)),this,SLOT(CambiarIndiceACtual(QModelIndex)));
    QObject::connect(selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(FiltrarColumnaSeleccion()));
}

QModelIndex &MiTabla::indiceActual()
{
    return m_indiceActual;
}

void MiTabla::SetModoSeleccionNormal()
{
    modoSeleccion = SELECCION_NORMAL;
}

void MiTabla::SetModoSeleccionRestringido()
{
    modoSeleccion = SELECCION_RESTRINGIDA;
}

void MiTabla::paintEvent(QPaintEvent *event)
{
    QTableView::paintEvent(event);
    if(selectionModel() &&  selectionModel()->selectedIndexes().isEmpty())
    {
        return;
    }
    QPen pen(Qt::black,3);
    QPainter painter(viewport());
    //defino el area seleccionada
    QRect rect = visualRect(selectedIndexes().first()) | visualRect(selectedIndexes().last());
    //dibujo la marca en la esquina inferior derecha del area seleccionada
    painter.setBrush(QBrush(QColor(Qt::black)));
    painter.drawRect(rect.x()+rect.width()-m_tamMarca,rect.y()+rect.height()-m_tamMarca,m_tamMarca,m_tamMarca);
    //si hago la seleccion en modo restringido, saldra un borde
    if (modoSeleccion == SELECCION_RESTRINGIDA)    {

        painter.setPen(pen);
        //painter.drawRect(rect);
        painter.drawLine(rect.x(),rect.y(),rect.x()+rect.width(),rect.y());
        painter.drawLine(rect.x(),rect.y(),rect.x(),rect.y()+rect.height());
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawLine(rect.x()+rect.width(),rect.y(),rect.x()+rect.width(),rect.y()+rect.height());
        painter.drawLine(rect.x(),rect.y()+rect.height(),rect.x()+rect.width(),rect.y()+rect.height());        
    }
    viewport()->update();
}

bool MiTabla::BotonIzquierdoPresionado()
{
    return m_BotonIzqPresionado;
}

int MiTabla::LeeTamMarca()
{
    return m_tamMarca;
}

void MiTabla::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        m_indiceActual = currentIndex();
        setCurrentIndex(this->indexAt(event->pos()));
        m_BotonIzqPresionado = true;
    }
    QTableView::mousePressEvent(event);
}

void MiTabla::mouseReleaseEvent(QMouseEvent *event)
{
    //en la funcion release parece no leer el tipo de boton (izquierdo o derecho)
    if (modoSeleccion == SELECCION_RESTRINGIDA)
    //si estoy en modo restringido efectuo una accion al soltar el boton del raton
    //en este caso igualo todos los valores de la columna al primero de ellos
    {
        foreach (QModelIndex const &i, selectedIndexes() )
        {
            this->model()->setData(i,selectedIndexes().first().data());
        }
    }
    SetModoSeleccionNormal();
    m_BotonIzqPresionado = false;
    QTableView::mouseReleaseEvent(event);
}

void MiTabla::CambiarIndiceACtual(const QModelIndex &indice)
{
    m_indiceActual=indice;
}

void MiTabla::FiltrarColumnaSeleccion()
{
    if (modoSeleccion == SELECCION_RESTRINGIDA)
    {
        for(const QModelIndex& item : selectionModel()->selectedIndexes())
        {
            if( item.column() != m_indiceActual.column())
            {
                selectionModel()->select(item,QItemSelectionModel::Deselect);
            }
        }
    }
}

