# ColorMatrix
Qt Color Matrix Demo

This project is an extended version of a sample application provided in [StackOverflow](https://stackoverflow.com/a/51952073/7478597).

![Snapshot of colorMatrix program](https://i.stack.imgur.com/qXOFx.png)

The application is developed in C++ based on C++ standard library and Qt5.

The following steps have to be performed to compile and execute the application:

    $ qmake-qt5 colorMatrix.pro
    
    $ make
    
    $ ./colorMatrix

## Usage

Any change in the matrix stack (on left side) is applied immediately to the source image (in the middle) to compute a new result image (on the right).

Matrices are multiplied from left to right. The resulting product matrix is multiplied with each pixel of the source image. Thereby, each RGBA value (each component a byte) is converted to a vector (r / 255.0, g / 255.0, b / 255.0, a / 255.0, 1) which is multiplied with the matrix.

_v'_ = **M** _v_

The result vector is converted back to RGBA.
 
The <kbd> + </kbd> tab can be used to add a new matrix.

The order of matrices can be changed by dragging the resp. tabs.

The <kbd> &#x23f4; </kbd> and <kbd> &#x23f5; </kbd> buttons can be used alternatetively to push a matrix to left or right.

The <kbd> &times; </kbd> button deletes a matrix.

Matrix values may be set manually. Additionally, the buttons below of the matrix provide some default assignments.

When the application starts, it tries to load a default image (of a cat like displayed in the snapshot). Using the <kbd> Open... </kbd> button, another image can be loaded. (The supported image formats depend on the available image loader plug-ins shipped with Qt.)
