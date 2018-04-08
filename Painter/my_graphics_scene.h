#ifndef MY_GRAPHICS_SCENE_H
#define MY_GRAPHICS_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>

class My_graphics_scene: public QGraphicsScene {
    Q_OBJECT

public:
    explicit My_graphics_scene(QObject* parent=nullptr);
    ~My_graphics_scene();

signals:
    void mouseMoved();
    void mousePressed();
    void mouseReleased();

public slots:
    QPoint get_first();
    QPoint get_last();

private slots:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    QPoint first; // start point
    QPoint last;  // finish point
};

#endif // MY_GRAPHICS_SCENE_H
