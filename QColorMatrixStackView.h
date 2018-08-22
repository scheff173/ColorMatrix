#ifndef Q_COLOR_MATRIX_STACK_VIEW_H
#define Q_COLOR_MATRIX_STACK_VIEW_H

#include <vector>

#include <QAction>
#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTabBar>
#include <QToolBar>

#include "QColorMatrixView.h"

class QColorMatrixStackView: public QWidget {
  Q_OBJECT
  private:
    QString _qAppDir;
    std::vector<ColorMatrix> _mats;
    ColorMatrix _matProd;
    int _iTabNew;
    QGridLayout _qGrid;
    QTabBar _qTabBar;
    QToolBar _qToolBar;
    QHBoxLayout _qHBox;
    QAction _qCmdLeft, _qCmdRight;
    QLabel _qLblName;
    QLineEdit _qEditName;
    QAction _qCmdDelete;
    QColorMatrixView _qEditColMat;
  signals:
    void editingFinished();

  public:
    QColorMatrixStackView(QWidget *pQParent = nullptr);
    virtual ~QColorMatrixStackView() = default;
    QColorMatrixStackView(const QColorMatrixStackView&) = delete;
    QColorMatrixStackView& operator=(const QColorMatrixStackView&) = delete;

    const std::vector<ColorMatrix>& allValues() const { return _mats; }
    const ColorMatrix& values() const { return _matProd; }
    void setValues(const ColorMatrix &values);
    void setValues(const ColorMatrix &values, const QString &text);
    void pushLeft();
    void pushRight();
    void deleteValues();

  private:
    void updateEnable();
    void onTabBarChanged(int i);
    void onTabBarClicked(int i);
    void onTabMoved(int iOld, int iNew);
    void onMatEditFinished();
    void onNameEditFinished();
};

#endif // Q_COLOR_MATRIX_STACK_VIEW_H
