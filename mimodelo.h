#ifndef MIMODELO_H
#define MIMODELO_H

#include <QAbstractTableModel>

class MiModelo : public QAbstractTableModel
{
public:
    MiModelo(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index,int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    //Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    int filas, columnas;
    QChar m_datos[4][4];

};

#endif // MIMODELO_H
