#ifndef MITABLA_H
#define MITABLA_H

#include <QTableView>

class MiTabla : public QTableView
{
    Q_OBJECT
public:

    enum eModoSeleccion{SELECCION_NORMAL, SELECCION_RESTRINGIDA};
    MiTabla(QWidget *parent = nullptr);
    QModelIndex& indiceActual();
    void SetModoSeleccionNormal();
    void SetModoSeleccionRestringido();
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
    bool BotonIzquierdoPresionado();
    int LeeTamMarca();

private slots:
    void CambiarIndiceACtual(const QModelIndex& indice);
    void FiltrarColumnaSeleccion();


private:
    QModelIndex m_indiceActual;
    eModoSeleccion modoSeleccion;
    bool m_BotonIzqPresionado;
    int m_tamMarca;

};

#endif // MITABLA_H
