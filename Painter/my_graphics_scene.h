#ifndef MY_GRAPHICS_SCENE_H
#define MY_GRAPHICS_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>

/*! \class My_graphics_scene
 * \brief Class with override QGraphicsScene's events slots
 */
class My_graphics_scene: public QGraphicsScene {
    Q_OBJECT

public:
    explicit My_graphics_scene(QObject* parent=nullptr);
    ~My_graphics_scene();

signals:
    /*! Signal emmited when mouse is moved */
    void mouseMoved();
    /*! Signal emmited when mouse is pressed */
    void mousePressed();
    /*! Signal emmited when mouse is released */
    void mouseReleased();

public slots:
    /*! Method to get start point
     * \return Start point: from which selection started
     */
    QPoint get_first();

    /*! Method to get finish point
     * \return Finish point: where selection finished
     */
    QPoint get_last();

private slots:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QPoint first; /*!< start point */
    QPoint last;  /*!< finish point */
};

#endif // MY_GRAPHICS_SCENE_H
