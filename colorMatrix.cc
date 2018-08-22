#include <algorithm>

#include <QtWidgets>

#include "colorMatrix.h"
#include "QColorMatrixStackView.h"

ColorMatrix operator * (const ColorMatrix &m1, const ColorMatrix &m2)
{
  return ColorMatrix({
    m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0] + m1[0][3] * m2[3][0] + m1[0][4] * m2[4][0],
    m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1] + m1[0][3] * m2[3][1] + m1[0][4] * m2[4][1],
    m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2] + m1[0][3] * m2[3][2] + m1[0][4] * m2[4][2],
    m1[0][0] * m2[0][3] + m1[0][1] * m2[1][3] + m1[0][2] * m2[2][3] + m1[0][3] * m2[3][3] + m1[0][4] * m2[4][3],
    m1[0][0] * m2[0][4] + m1[0][1] * m2[1][4] + m1[0][2] * m2[2][4] + m1[0][3] * m2[3][4] + m1[0][4] * m2[4][4],
    m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0] + m1[1][3] * m2[3][0] + m1[1][4] * m2[4][0],
    m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1] + m1[1][3] * m2[3][1] + m1[1][4] * m2[4][1],
    m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2] + m1[1][3] * m2[3][2] + m1[1][4] * m2[4][2],
    m1[1][0] * m2[0][3] + m1[1][1] * m2[1][3] + m1[1][2] * m2[2][3] + m1[1][3] * m2[3][3] + m1[1][4] * m2[4][3],
    m1[1][0] * m2[0][4] + m1[1][1] * m2[1][4] + m1[1][2] * m2[2][4] + m1[1][3] * m2[3][4] + m1[1][4] * m2[4][4],
    m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0] + m1[2][3] * m2[3][0] + m1[2][4] * m2[4][0],
    m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1] + m1[2][3] * m2[3][1] + m1[2][4] * m2[4][1],
    m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2] + m1[2][3] * m2[3][2] + m1[2][4] * m2[4][2],
    m1[2][0] * m2[0][3] + m1[2][1] * m2[1][3] + m1[2][2] * m2[2][3] + m1[2][3] * m2[3][3] + m1[2][4] * m2[4][3],
    m1[2][0] * m2[0][4] + m1[2][1] * m2[1][4] + m1[2][2] * m2[2][4] + m1[2][3] * m2[3][4] + m1[2][4] * m2[4][4],
    m1[3][0] * m2[0][0] + m1[3][1] * m2[1][0] + m1[3][2] * m2[2][0] + m1[3][3] * m2[3][0] + m1[3][4] * m2[4][0],
    m1[3][0] * m2[0][1] + m1[3][1] * m2[1][1] + m1[3][2] * m2[2][1] + m1[3][3] * m2[3][1] + m1[3][4] * m2[4][1],
    m1[3][0] * m2[0][2] + m1[3][1] * m2[1][2] + m1[3][2] * m2[2][2] + m1[3][3] * m2[3][2] + m1[3][4] * m2[4][2],
    m1[3][0] * m2[0][3] + m1[3][1] * m2[1][3] + m1[3][2] * m2[2][3] + m1[3][3] * m2[3][3] + m1[3][4] * m2[4][3],
    m1[3][0] * m2[0][4] + m1[3][1] * m2[1][4] + m1[3][2] * m2[2][4] + m1[3][3] * m2[3][4] + m1[3][4] * m2[4][4],
    m1[4][0] * m2[0][0] + m1[4][1] * m2[1][0] + m1[4][2] * m2[2][0] + m1[4][3] * m2[3][0] + m1[4][4] * m2[4][0],
    m1[4][0] * m2[0][1] + m1[4][1] * m2[1][1] + m1[4][2] * m2[2][1] + m1[4][3] * m2[3][1] + m1[4][4] * m2[4][1],
    m1[4][0] * m2[0][2] + m1[4][1] * m2[1][2] + m1[4][2] * m2[2][2] + m1[4][3] * m2[3][2] + m1[4][4] * m2[4][2],
    m1[4][0] * m2[0][3] + m1[4][1] * m2[1][3] + m1[4][2] * m2[2][3] + m1[4][3] * m2[3][3] + m1[4][4] * m2[4][3],
    m1[4][0] * m2[0][4] + m1[4][1] * m2[1][4] + m1[4][2] * m2[2][4] + m1[4][3] * m2[3][4] + m1[4][4] * m2[4][4]
  });
}

ColorVector operator*(const ColorMatrix &m, const ColorVector &v)
{
  return ColorVector({
    m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3] + m[0][4] * v[4],
    m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3] + m[1][4] * v[4],
    m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3] + m[2][4] * v[4],
    m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3] + m[3][4] * v[4],
    m[4][0] * v[0] + m[4][1] * v[1] + m[4][2] * v[2] + m[4][3] * v[3] + m[4][4] * v[4]
  });
}

ColorMatrix& ColorMatrix::operator*=(const ColorMatrix &mat)
{
  return *this = *this * mat;
}

const ColorMatrix Identity({
  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f, 1.0f
});

template <typename T>
T clamp(T value, T min, T max)
{
  return value < min ? min
    : value > max ? max
    : value;
}

QRgb transform(const ColorMatrix &mat, const QRgb &color)
{
  ColorVector vec({
    qRed(color) / 255.0f, qGreen(color) / 255.0f, qBlue(color) / 255.0f, qAlpha(color) / 255.0f, 1.0f });
  vec = mat * vec;
  if (vec[4] != 0.0f) {
    vec[0] /= vec[4]; vec[1] /= vec[4]; vec[2] /= vec[4]; vec[3] /= vec[4]; // vec[4] = 1.0f;
  }
  return qRgba(
    clamp<int>(255 * vec[0], 0, 255),
    clamp<int>(255 * vec[1], 0, 255),
    clamp<int>(255 * vec[2], 0, 255),
    clamp<int>(255 * vec[3], 0, 255));
}

QImage transform(const ColorMatrix &mat, const QImage &qImg)
{
  const int w = qImg.width(), h = qImg.height();
  QImage qImgDst(w, h, qImg.format());
  for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
    qImgDst.setPixel(x, y, transform(mat, qImg.pixel(x, y)));
  }
  return qImgDst;
}

QImage open(QWidget *pQParent)
{
  return QImage(
    QFileDialog::getOpenFileName(pQParent,
      QString::fromUtf8("Open Image File"),
      QString()));
}

void update(
  QLabel &qLblViewResult,
  const QColorMatrixStackView &qEditColMat, const QLabel &qLblViewOrig)
{
  const ColorMatrix &colMat = qEditColMat.values();
  const QPixmap *pQPixmap = qLblViewOrig.pixmap();
  const QImage qImg = pQPixmap ? pQPixmap->toImage() : QImage();
  qLblViewResult.setPixmap(
    QPixmap::fromImage(transform(colMat, qImg)));
}

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  // setup GUI
  // main window
  QWidget qWin;
  qWin.setWindowTitle(QString::fromUtf8("Qt Color Matrix Demo"));
  QGridLayout qGrid;
  QVBoxLayout qVBoxColMat;
  QColorMatrixStackView qEditColMats;
  qVBoxColMat.addWidget(&qEditColMats);
  QPushButton qBtnReset(QString::fromUtf8("Identity"));
  qVBoxColMat.addWidget(&qBtnReset);
  QPushButton qBtnGray(QString::fromUtf8("Grayscale"));
  qVBoxColMat.addWidget(&qBtnGray);
  QPushButton qBtnBrightness(QString::fromUtf8("Brightness"));
  qVBoxColMat.addWidget(&qBtnBrightness);
  QPushButton qBtnContrast(QString::fromUtf8("Contrast"));
  qVBoxColMat.addWidget(&qBtnContrast);
  QPushButton qBtnSaturation(QString::fromUtf8("Saturation"));
  qVBoxColMat.addWidget(&qBtnSaturation);
  qVBoxColMat.addStretch(1);
  qGrid.addLayout(&qVBoxColMat, 0, 0, 2, 1);
  QLabel qLblX(QString::fromUtf8(" \xc3\x97 "));
  qGrid.addWidget(&qLblX, 0, 1);
  QLabel qLblViewOrig;
  qGrid.addWidget(&qLblViewOrig, 0, 2);
  QPushButton qBtnLoad(QString::fromUtf8("Open..."));
  qGrid.addWidget(&qBtnLoad, 1, 2);
  QLabel qLblEq(QString::fromUtf8(" = "));
  qGrid.addWidget(&qLblEq, 0, 3);
  QLabel qLblViewResult;
  qGrid.addWidget(&qLblViewResult, 0, 4);
  qWin.setLayout(&qGrid);
  qWin.show();
  // install signal handlers
  QObject::connect(&qEditColMats, &QColorMatrixStackView::editingFinished,
    [&]() { update(qLblViewResult, qEditColMats, qLblViewOrig); });
  QObject::connect(&qBtnReset, &QPushButton::clicked,
    [&]() {
      qEditColMats.setValues(Identity, QString::fromUtf8("Identity"));
      update(qLblViewResult, qEditColMats, qLblViewOrig);
    });
  QObject::connect(&qBtnGray, &QPushButton::clicked,
    [&]() {
      qEditColMats.setValues(
        ColorMatrix({
          0.33f, 0.59f, 0.11f, 0.0f, 0.0f,
          0.33f, 0.59f, 0.11f, 0.0f, 0.0f,
          0.33f, 0.59f, 0.11f, 0.0f, 0.0f,
          0.00f, 0.00f, 0.00f, 1.0f, 0.0f,
          0.00f, 0.00f, 0.00f, 0.0f, 1.0f
        }),
        QString::fromUtf8("Grayscale"));
      update(qLblViewResult, qEditColMats, qLblViewOrig);
    });
  float brightness = 0.0f;
  QObject::connect(&qBtnBrightness, &QPushButton::clicked,
    [&]() {
      bool ok = false;
      const float b
        = (float)QInputDialog::getDouble(&qWin,
          QString::fromUtf8("Brightness"),
          QString::fromUtf8("Brightness"),
          brightness, -1000.0, 1000.0, 3, &ok);
      if (!ok) return;
      brightness = b;
      qEditColMats.setValues(
        ColorMatrix({
          1.0f, 0.0f, 0.0f, 0.0f,  b  ,
          0.0f, 1.0f, 0.0f, 0.0f,  b  ,
          0.0f, 0.0f, 1.0f, 0.0f,  b  ,
          0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 0.0f, 1.0f
        }),
        QString::fromUtf8("Brightness: ")
          + QString::number(brightness, 'g'));
      update(qLblViewResult, qEditColMats, qLblViewOrig);
    });
  float contrast = 1.0f;
  QObject::connect(&qBtnContrast, &QPushButton::clicked,
    [&]() {
      bool ok = false;
      const float c
        = (float)QInputDialog::getDouble(&qWin,
          QString::fromUtf8("Contrast"),
          QString::fromUtf8("Contrast"),
          contrast, -1000.0, 1000.0, 3, &ok);
      if (!ok) return;
      contrast = c; const float t = (1.0f - c) / 2.0f;
      qEditColMats.setValues(
        ColorMatrix({
           c  , 0.0f, 0.0f, 0.0f,  t  ,
          0.0f,  c  , 0.0f, 0.0f,  t  ,
          0.0f, 0.0f,  c  , 0.0f,  t  ,
          0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
          0.0f, 0.0f, 0.0f, 0.0f, 1.0f
        }),
        QString::fromUtf8("Contrast: ")
          + QString::number(contrast, 'g'));
      update(qLblViewResult, qEditColMats, qLblViewOrig);
    });
  float saturation = 1.0f;
  QObject::connect(&qBtnSaturation, &QPushButton::clicked,
    [&]() {
      bool ok = false;
      const float s
        = (float)QInputDialog::getDouble(&qWin,
          QString::fromUtf8("Saturation"),
          QString::fromUtf8("Saturation"),
          saturation, -1000.0, 1000.0, 3, &ok);
      if (!ok) return;
      saturation = s;
      const float sr = (1.0f - s) * 0.3086f;
      const float sg = (1.0f - s) * 0.6094f;
      const float sb = (1.0f - s) * 0.0820f;
      qEditColMats.setValues(
        ColorMatrix({
          sr + s,   sg  ,   sb  , 0.0f, 0.0f,
            sr  , sg + s,   sb  , 0.0f, 0.0f,
            sr  ,   sg  , sb + s, 0.0f, 0.0f,
           0.0f ,  0.0f ,  0.0f , 1.0f, 0.0f,
           0.0f ,  0.0f ,  0.0f , 0.0f, 1.0f
        }),
        QString::fromUtf8("Saturation: ")
          + QString::number(saturation, 'g'));
      update(qLblViewResult, qEditColMats, qLblViewOrig);
    });
  QObject::connect(&qBtnLoad, &QPushButton::clicked,
    [&]() {
      qLblViewOrig.setPixmap(QPixmap::fromImage(open(&qBtnLoad)));
      update(qLblViewResult, qEditColMats, qLblViewOrig);
    });
  // initial contents
  {
    QImage qImg("colorMatrixDefault.jpg");
    qLblViewOrig.setPixmap(QPixmap::fromImage(qImg));
    update(qLblViewResult, qEditColMats, qLblViewOrig);
  }
  // runtime loop
  return app.exec();
}
