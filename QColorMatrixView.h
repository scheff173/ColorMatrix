#ifndef Q_COLOR_MATRIX_VIEW_H
#define Q_COLOR_MATRIX_VIEW_H

#include <QLineEdit>
#include <QGridLayout>
#include <QWidget>

#include "colorMatrix.h"

class QColorMatrixView: public QWidget {
  Q_OBJECT
  private:
    QGridLayout _qGrid;
    QLineEdit _qEdit[5][5];
  signals:
    void editingFinished();
  public:
    QColorMatrixView(QWidget *pQParent = nullptr);
    virtual ~QColorMatrixView() = default;
    QColorMatrixView(const QColorMatrixView&) = delete;
    QColorMatrixView& operator=(const QColorMatrixView&) = delete;

    void clear();
    ColorMatrix values() const;
    void setValues(const ColorMatrix &mat);
};

#endif // Q_COLOR_MATRIX_VIEW_H
