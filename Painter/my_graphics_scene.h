#ifndef MY_GRAPHICS_SCENE_H
#define MY_GRAPHICS_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>

class My_graphics_scene : public QGraphicsScene {
public:
    My_graphics_scene();

public slots:
    QPoint get_first();
    QPoint get_last();

private slots:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    QPoint first;
    QPoint last;
};

#endif // MY_GRAPHICS_SCENE_H
