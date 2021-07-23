#ifndef LIQUIDPLOT_H
#define LIQUIDPLOT_H

#include <QWidget>

class LiquidPlot : public QWidget
{
    Q_OBJECT

public:
    LiquidPlot(QWidget *parent = 0);
    ~LiquidPlot();

    enum EPlotType
    {
        PLOTTYPE_CIRCULAR,
        PLOTTYPE_RECTANGLE,
        PLOTTYPE_DIAMOND,
    };

public slots:
    void SetPercent(int nPercent);
    int GetPercent() { return m_nPercent; }

    void SetPlotType(EPlotType ePlotType) { m_ePlotType = ePlotType; update(); }

    void SetSpeed(int nSpeed) { m_nSpeed = nSpeed; }
    int GetSpeed() { return m_nSpeed; }

    void SetWaterColor(QColor colorWater) { m_colorWater = colorWater; update(); }
    QColor GetWaterColor() { return m_colorWater; }

    void EnableSpace(bool bEnableSpace) { m_bEnableSpace = bEnableSpace; update(); }

private:
    void paintEvent(QPaintEvent *event);
    void DrawCircularPlot(QPainter *p, QRect rcRect);
    void timerEvent(QTimerEvent *event);

private:
    void CreateAllChildWnd();
    void InitCtrl();
    void InitSolts();
    void Relayout();

private:
    EPlotType m_ePlotType;
    QFont m_iconFont;
    int m_nPercent;
    uint m_fOffset;
    int m_nSpeed;
    bool m_bEnableSpace;

    QColor m_colorWater;
};

#endif // LIQUIDPLOT_H
