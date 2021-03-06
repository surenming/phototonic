/*
 *  Copyright (C) 2013 Ofer Kashayov <oferkv@live.com>
 *  This file is part of Phototonic Image Viewer.
 *
 *  Phototonic is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Phototonic is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Phototonic.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

#include <QGraphicsDropShadowEffect>
#include <exiv2/exiv2.hpp>
#include "Settings.h"
#include "CropRubberband.h"
#include "MetadataCache.h"

class Phototonic;

class ImageViewer : public QWidget {
Q_OBJECT

public:
    bool tempDisableResize;
    int mirrorLayout;
    QString viewerImageFullPath;
    QMenu *ImagePopUpMenu;
    QScrollArea *scrollArea;
    QLabel *imageInfoLabel;
    CropRubberBand *cropRubberBand;

    enum ZoomMethods {
        Disable = 0,
        WidthAndHeight,
        Width,
        Height,
        Disprop
    };

    enum MirrorLayouts {
        LayNone = 0,
        LayDual,
        LayTriple,
        LayQuad,
        LayVDual
    };

    enum Movement {
        MoveUp = 0,
        MoveDown,
        MoveLeft,
        MoveRight
    };

    ImageViewer(QWidget *parent, MetadataCache *metadataCache);

    void loadImage(QString imageFileName);

    void clearImage();

    void resizeImage();

    void setCursorHiding(bool hide);

    void refresh();

    void reload();

    int getImageWidthPreCropped();

    int getImageHeightPreCropped();

    bool isNewImage();

    void keyMoveEvent(int direction);

    void rotateByExifRotation(QImage &image, QString &imageFullPath);

    void setInfo(QString infoString);

    void setFeedback(QString feedbackString);

    void setBackgroundColor();

public slots:

    void monitorCursorState();

    void saveImage();

    void saveImageAs();

    void copyImage();

    void pasteImage();

    void cropToSelection();

private slots:

    void unsetFeedback();

protected:
    void resizeEvent(QResizeEvent *event);

    void showEvent(QShowEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void contextMenuEvent(QContextMenuEvent *event);

    void mouseDoubleClickEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

private:
    Phototonic *phototonic;
    QLabel *imageLabel;
    QPixmap viewerPixmap;
    QImage origImage;
    QImage viewerImage;
    QImage mirrorImage;
    QTimer *mouseMovementTimer;
    QMovie *animation;
    bool newImage;
    bool cursorIsHidden;
    bool moveImageLocked;
    int mouseX;
    int mouseY;
    int layoutX;
    int layoutY;
    bool isAnimation;
    QLabel *feedbackLabel;
    QPoint cropOrigin;
    MetadataCache *metadataCache;

    void setMouseMoveData(bool lockMove, int lMouseX, int lMouseY);

    void centerImage(QSize &imgSize);

    void transform();

    void mirror();

    void colorize();
};

#endif // IMAGE_VIEWER_H

