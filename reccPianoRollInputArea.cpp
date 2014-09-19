#include "reccPianoRollInputArea.h"

#include <QScrollBar>

reccPianoRollInputArea::reccPianoRollInputArea(QWidget *parent) :
    QGraphicsView(parent)
{
    myScene = new QGraphicsScene(this);
    this->setScene(myScene);
    lineItems = new QList<QGraphicsItem*>;

    lineWidth = 0;

    //AutoMinimalLineWidth();



    //initLines();

    //lineWidthNormalize();
}

void reccPianoRollInputArea::Extend()
{
    lineWidth += 100.0;
    lineWidthNormalize();
}

void reccPianoRollInputArea::lineWidthNormalize()
{
    QGraphicsItem *gi;
    foreach(gi,*lineItems)
    {
        delete gi;
    }
    initLines();
}

void reccPianoRollInputArea::initLines()
{
    for(int i = 0;i<9;i++)
    {
#define LINE(n,color) lineItems->append(myScene->addRect(0,-LINE_HEIGHT*(i*12+n),lineWidth,LINE_HEIGHT \
        ,QPen(Qt::NoPen),QBrush(color)));
#define TBLACK QColor(0x00,0x00,0x00,0x20)
#define TWHITE QColor(0xff,0xff,0xff,0x20)
        LINE(0,TWHITE);
        LINE(1,TBLACK);
        LINE(2,TWHITE);
        LINE(3,TBLACK);
        LINE(4,TWHITE);
        LINE(5,TBLACK);
        LINE(6,TWHITE);
        LINE(7,TWHITE);
        LINE(8,TBLACK);
        LINE(9,TWHITE);
        LINE(10,TBLACK);
        LINE(11,TWHITE);
#undef LINE
#undef TBLACK
#undef TWHITE
    }
}

void reccPianoRollInputArea::setPianoImage(reccPianoImage *image)
{
    this->pianoImage = image;
}

void reccPianoRollInputArea::scrollContentsBy(int dx, int dy)
{
    int thisMin,thisMax,thisVal,imMin,imMax;
    thisMin = this->verticalScrollBar()->minimum();
    thisMax = this->verticalScrollBar()->maximum();
    thisVal = this->verticalScrollBar()->value();
    imMin = pianoImage->verticalScrollBar()->minimum();
    imMax = pianoImage->verticalScrollBar()->maximum();

    pianoImage->verticalScrollBar()->setValue(
                ((int)(((thisVal-thisMin)*1.0)/(thisMax-thisMin)*(imMax-imMin)+imMin)));

    qDebug("reccPianoRollInputArea::scrollContentsBy(%d,%d)\nthisVal = %d, thisMin = %d, thisMax = %d\n"
           "imMin = %d, imMax = %d, Target is %d\n"
           ,dx,dy,thisVal,thisMin,thisMax,imMin,imMax,((int)(((thisVal-thisMin)*1.0)/(thisMax-thisMin)*(imMax-imMin)+imMin)));

    QGraphicsView::scrollContentsBy(dx,dy);
}

void reccPianoRollInputArea::AutoMinimalLineWidth()
{
    double lineWidth1 = (mapToScene(size().width(),0)-mapToScene(0,0)).x();
    if(lineWidth1>lineWidth)
    {
        lineWidth = lineWidth1;
        lineWidthNormalize();
    }
}

void reccPianoRollInputArea::resizeEvent(QResizeEvent *event)
{
    AutoMinimalLineWidth();
    QGraphicsView::resizeEvent(event);
}
