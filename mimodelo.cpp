#include "mimodelo.h"
#include <ctime>
#include <QDebug>

MiModelo::MiModelo(QObject *parent):QAbstractTableModel(parent)
{
    filas =4;
    columnas = 4;
    srand (time(NULL));
    for (int i = 0;i<filas;i++)
    {
        for (int j=0;j<columnas;j++)
        {
            int datonum = 48 + (std::rand()%(57-48+1));
            int datoletra = 65 + (std::rand()%(90-65+1));
            int dato = (0+(std::rand()%2)==0)?datonum:datoletra;
            m_datos[i][j]=static_cast<QChar>(dato);
        }
    }
}

int MiModelo::columnCount(const QModelIndex &parent) const
{
    return columnas;
}

QVariant MiModelo::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (role == Qt::DisplayRole)
    {
        return QVariant(m_datos[index.row()][index.column()]);
    }
    return QVariant();
}

bool MiModelo::setData(const QModelIndex &index, const QVariant &value, int role)
{
    m_datos[index.row()][index.column()]=static_cast<QChar>(value.toInt());
}

/*Qt::ItemFlags MiModelo::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }
    if (index.column()==2)
    {
        //return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
        return QAbstractTableModel::flags(index) ^ Qt::ItemIsSelectable;
    }
    return  QAbstractTableModel::flags(index);
}*/

int MiModelo::rowCount(const QModelIndex &parent) const
{
    return filas;
}

