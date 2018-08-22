#include <cassert>

#include <QtWidgets>

#include "QColorMatrixStackView.h"

QColorMatrixStackView::QColorMatrixStackView(QWidget *pQParent):
  QWidget(pQParent),
#ifdef _DEBUG
  _qAppDir(QDir::currentPath()),
#else // (not) _DEBUG
  _qAppDir(QApplication::applicationDirPath()),
#endif // _DEBUG
  _mats(1, Identity),
  _matProd(Identity),
  _iTabNew(0),
  _qCmdLeft(QIcon(_qAppDir + QString::fromUtf8("/left.svg")),
    QString::fromUtf8("Push Left")),
  _qCmdRight(QIcon(_qAppDir + QString::fromUtf8("/right.svg")),
    QString::fromUtf8("Push Right")),
  _qLblName(QString::fromUtf8("Name:")),
  _qCmdDelete(QIcon(_qAppDir + QString::fromUtf8("/window-close.svg")),
    QString::fromUtf8("Delete Matrix"))
{
  _qTabBar.setMovable(true);
  _qGrid.addWidget(&_qTabBar, 0, 0, 1, 2);
  _qToolBar.addAction(&_qCmdLeft);
  _qToolBar.addAction(&_qCmdRight);
  _qToolBar.addWidget(&_qLblName);
  _qToolBar.addWidget(&_qEditName);
  _qToolBar.addAction(&_qCmdDelete);
  _qGrid.addWidget(&_qToolBar, 1, 0, 1, 2);
  _qGrid.addWidget(&_qEditColMat, 2, 0, 1, 2);
  setLayout(&_qGrid);
  _qTabBar.addTab(QString::fromUtf8("Identity"));
  _qTabBar.addTab(QString::fromUtf8(" + ")); _iTabNew = 1;
  // install signal handlers
  connect(&_qTabBar, &QTabBar::currentChanged,
    this, &QColorMatrixStackView::onTabBarChanged);
  connect(&_qTabBar, &QTabBar::tabBarClicked,
    this, &QColorMatrixStackView::onTabBarClicked);
  connect(&_qTabBar, &QTabBar::tabMoved,
    this, &QColorMatrixStackView::onTabMoved);
  connect(&_qCmdLeft, &QAction::triggered,
    this, &QColorMatrixStackView::pushLeft);
  connect(&_qCmdRight, &QAction::triggered,
    this, &QColorMatrixStackView::pushRight);
  connect(&_qCmdDelete, &QAction::triggered,
    this, &QColorMatrixStackView::deleteValues);
  connect(&_qEditColMat, &QColorMatrixView::editingFinished,
    this, &QColorMatrixStackView::onMatEditFinished);
  connect(&_qEditName, &QLineEdit::editingFinished,
    this, &QColorMatrixStackView::onNameEditFinished);
  // initialize
  if (_qTabBar.currentIndex() != 0) _qTabBar.setCurrentIndex(0);
  else onTabBarChanged(0);
}

void QColorMatrixStackView::setValues(
  const ColorMatrix &values, const QString &text)
{
  const int i = _qTabBar.currentIndex();
  const int iMat = i > _iTabNew ? i - 1 : i;
  if (iMat >= 0 && iMat < (int)_mats.size()) {
    _qTabBar.setTabText(i, text);
    _qEditColMat.setValues(_mats[iMat] = values);
    _qEditName.setText(text);
    _matProd = Identity;
    for (auto mat : _mats) _matProd *= mat;
  }
}

void QColorMatrixStackView::pushLeft()
{
  const int i = _qTabBar.currentIndex();
  const int iMat = i > _iTabNew ? i - 1 : i;
  if (iMat > 0 && iMat < (int)_mats.size()) {
    const int iNew = i - 1 == _iTabNew ? i - 2 : i - 1;
    _qTabBar.moveTab(i, iNew);
    _qTabBar.setCurrentIndex(iNew);
  }
}

void QColorMatrixStackView::pushRight()
{
  const int i = _qTabBar.currentIndex();
  const int iMat = i > _iTabNew ? i - 1 : i;
  if (iMat >= 0 && iMat + 1 < (int)_mats.size()) {
    const int iNew = i + 1 == _iTabNew ? i + 2 : i + 1;
    _qTabBar.moveTab(i, iNew);
    _qTabBar.setCurrentIndex(iNew);
  }
}

void QColorMatrixStackView::deleteValues()
{
  int i = _qTabBar.currentIndex();
  const int iMat = i > _iTabNew ? i - 1 : i;
  if (iMat >= 0 && iMat < (int)_mats.size()) {
    if (_mats.size() > 1) {
      _mats.erase(_mats.begin() + iMat);
      if (_iTabNew > i) --_iTabNew;
      _qTabBar.removeTab(i);
      if (_qTabBar.currentIndex() == _iTabNew) {
        if (iMat < (int)_mats.size()) ++i; else --i;
      }
    } else {
      _mats[0] = Identity;
      _qTabBar.setTabText(i, QString::fromUtf8("Identity"));
    }
    if (i != _qTabBar.currentIndex()) _qTabBar.setCurrentIndex(i);
    else onTabBarChanged(i);
    _matProd = Identity;
    for (auto mat : _mats) _matProd *= mat;
    editingFinished();
  }
}

void QColorMatrixStackView::updateEnable()
{
  const int i = _qTabBar.currentIndex();
  const int iMat = i > _iTabNew ? i - 1 : i;
  _qCmdLeft.setEnabled(iMat > 0);
  _qCmdRight.setEnabled(iMat < _qTabBar.count() - 2);
  _qCmdDelete.setEnabled(_qTabBar.count() > 2);
  _qEditName.setEnabled(i != _iTabNew);
  _qEditColMat.setEnabled(i != _iTabNew);
  if (i == _iTabNew) {
    _qEditName.setText(QString());
    _qEditColMat.clear();
  }
}

void QColorMatrixStackView::onTabBarChanged(int i)
{
  if (i == _iTabNew) {
    i = i + 1 >= _qTabBar.count() ? i > 0 ? i - 1 : i + 1 : i;
    _qTabBar.setCurrentIndex(i);
  }
  updateEnable();
  const int iMat = i > _iTabNew ? i - 1 : i;
  if (i != _iTabNew && iMat >= 0 && iMat < (int)_mats.size()) {
    _qEditName.setText(_qTabBar.tabText(i));
    _qEditColMat.setValues(_mats[iMat]);
  }
}

void QColorMatrixStackView::onTabBarClicked(int i)
{
  if (i == _iTabNew) { // plus pressed
    _mats.insert(_mats.begin() + i, Identity);
    _qTabBar.insertTab(i, QString::fromUtf8("Identity"));
    _iTabNew = i + 1;
    _qTabBar.setCurrentIndex(i);
  }
}

void QColorMatrixStackView::onTabMoved(int iOld, int iNew)
{
  if (iOld == _iTabNew) _iTabNew = iNew;
  else {
    if (iOld > _iTabNew) --iOld;
    if (iNew > _iTabNew) --iNew;
    if (iOld < iNew) {
      std::rotate(_mats.begin() + iOld, _mats.begin() + iOld + 1,
        _mats.begin() + iNew + 1);
    } else {
      std::rotate(_mats.begin() + iNew, _mats.begin() + iNew + 1,
        _mats.begin() + iOld + 1);
    }
    _matProd = Identity;
    for (auto mat : _mats) _matProd *= mat;
    editingFinished();
  }
}

void QColorMatrixStackView::onMatEditFinished()
{
  const int i = _qTabBar.currentIndex();
  assert(i != _iTabNew);
  const int iMat = i > _iTabNew ? i - 1 : i;
  if (iMat >= 0 && iMat < (int)_mats.size()) {
    _mats[iMat] = _qEditColMat.values();
    _matProd = Identity;
    for (auto mat : _mats) _matProd *= mat;
    editingFinished();
  }
}

void QColorMatrixStackView::onNameEditFinished()
{
  const int i = _qTabBar.currentIndex();
  assert(i != _iTabNew);
  const int iMat = i > _iTabNew ? i - 1 : i;
  if (iMat >= 0 && i < (int)_mats.size()) {
    _qTabBar.setTabText(i + 1, _qEditName.text());
  }
}
