#include "QColorMatrixView.h"

QColorMatrixView::QColorMatrixView(QWidget *pQParent):
  QWidget(pQParent)
{
  QFontMetrics qFontMetrics(font());
  const int w = qFontMetrics.boundingRect(QString("-000.000")).width() + 10;
  for (int r = 0; r < 5; ++r) {
    for (int c = 0; c < 5; ++c) {
      QLineEdit &qEdit = _qEdit[r][c];
      _qGrid.addWidget(&qEdit, r, c);
      qEdit.setFixedWidth(w);
      QObject::connect(&qEdit, &QLineEdit::editingFinished,
        [this, r, c]() {
        _qEdit[r][c].setText(
          QString::number(_qEdit[r][c].text().toFloat(), 'f', 3));
        editingFinished();
      });
    }
  }
  setLayout(&_qGrid);
}

void QColorMatrixView::clear()
{
  for (int r = 0; r < 5; ++r) for (int c = 0; c < 5; ++c) {
    _qEdit[r][c].setText(QString());
  }
}

ColorMatrix QColorMatrixView::values() const
{
  ColorMatrix mat;
  for (int r = 0; r < 5; ++r) for (int c = 0; c < 5; ++c) {
    mat[r][c] = _qEdit[r][c].text().toFloat();
  }
  return mat;
}

void QColorMatrixView::setValues(const ColorMatrix &mat)
{
  for (int r = 0; r < 5; ++r) for (int c = 0; c < 5; ++c) {
    _qEdit[r][c].setText(QString::number(mat[r][c], 'f', 3));
  }
}
