#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //Shape
    ui->shapeCombo->addItem(tr("Polygon"), ShapeCanvas::Polygon);
    ui->shapeCombo->addItem(tr("Rectangle"), ShapeCanvas::Rect);
    ui->shapeCombo->addItem(tr("Rounded Rectangle"), ShapeCanvas::RoundedRect);
    ui->shapeCombo->addItem(tr("Ellipse"), ShapeCanvas::Ellipse);
    ui->shapeCombo->addItem(tr("Pie"), ShapeCanvas::Pie);
    ui->shapeCombo->addItem(tr("Chord"), ShapeCanvas::Chord);
    ui->shapeCombo->addItem(tr("Text"), ShapeCanvas::Text);
    ui->shapeCombo->addItem(tr("Pixmap"), ShapeCanvas::Pixmap);

    //Pen style
    ui->penStyleCombo->addItem(tr("Solid"), static_cast<int>(Qt::SolidLine));
    ui->penStyleCombo->addItem(tr("Dash"), static_cast<int>(Qt::DashLine));
    ui->penStyleCombo->addItem(tr("Dot"), static_cast<int>(Qt::DotLine));
    ui->penStyleCombo->addItem(tr("Dash Dot"), static_cast<int>(Qt::DashDotLine));
    ui->penStyleCombo->addItem(tr("Dash Dot Dot"), static_cast<int>(Qt::DashDotDotLine));
    ui->penStyleCombo->addItem(tr("None"), static_cast<int>(Qt::NoPen));

    //Pen cap
    ui->penCapCombo->addItem(tr("Flat"), Qt::FlatCap);
    ui->penCapCombo->addItem(tr("Square"), Qt::SquareCap);
    ui->penCapCombo->addItem(tr("Round"), Qt::RoundCap);

    //Pen join
    ui->penJoinCombo->addItem(tr("Miter"), Qt::MiterJoin);
    ui->penJoinCombo->addItem(tr("Bevel"), Qt::BevelJoin);
    ui->penJoinCombo->addItem(tr("Round"), Qt::RoundJoin);

    //Brush style
    ui->brushStyleCombo->addItem(tr("Linear Gradient"),static_cast<int>(Qt::LinearGradientPattern));
    ui->brushStyleCombo->addItem(tr("Radial Gradient"),static_cast<int>(Qt::RadialGradientPattern));
    ui->brushStyleCombo->addItem(tr("Conical Gradient"),static_cast<int>(Qt::ConicalGradientPattern));
    ui->brushStyleCombo->addItem(tr("Texture"), static_cast<int>(Qt::TexturePattern));
    ui->brushStyleCombo->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
    ui->brushStyleCombo->addItem(tr("Horizontal"), static_cast<int>(Qt::HorPattern));
    ui->brushStyleCombo->addItem(tr("Vertical"), static_cast<int>(Qt::VerPattern));
    ui->brushStyleCombo->addItem(tr("Cross"), static_cast<int>(Qt::CrossPattern));
    ui->brushStyleCombo->addItem(tr("Backward Diagonal"), static_cast<int>(Qt::BDiagPattern));
    ui->brushStyleCombo->addItem(tr("Forward Diagonal"), static_cast<int>(Qt::FDiagPattern));
    ui->brushStyleCombo->addItem(tr("Diagonal Cross"), static_cast<int>(Qt::DiagCrossPattern));
    ui->brushStyleCombo->addItem(tr("Dense 1"), static_cast<int>(Qt::Dense1Pattern));
    ui->brushStyleCombo->addItem(tr("Dense 2"), static_cast<int>(Qt::Dense2Pattern));
    ui->brushStyleCombo->addItem(tr("Dense 3"), static_cast<int>(Qt::Dense3Pattern));
    ui->brushStyleCombo->addItem(tr("Dense 4"), static_cast<int>(Qt::Dense4Pattern));
    ui->brushStyleCombo->addItem(tr("Dense 5"), static_cast<int>(Qt::Dense5Pattern));
    ui->brushStyleCombo->addItem(tr("Dense 6"), static_cast<int>(Qt::Dense6Pattern));
    ui->brushStyleCombo->addItem(tr("Dense 7"),static_cast<int> (Qt::Dense7Pattern));
    ui->brushStyleCombo->addItem(tr("None"), static_cast<int>(Qt::NoBrush));

    shapeCanvas = new ShapeCanvas(this);

    ui->canvasLayout->addWidget(shapeCanvas);

    penChanged();
    brushChanged();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_shapeCombo_activated(int index)
{
    ShapeCanvas::Shape shape = ShapeCanvas::Shape(index);
    shapeCanvas->setShape(shape);
}


void Widget::on_penWidthSpin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    penChanged();
}


void Widget::on_penStyleCombo_activated(int index)
{
    Q_UNUSED(index);
    penChanged();
}


void Widget::on_penCapCombo_activated(int index)
{
    penChanged();
}


void Widget::on_penJoinCombo_activated(int index)
{
    Q_UNUSED(index);
    penChanged();
}


void Widget::on_brushStyleCombo_activated(int index)
{
    Q_UNUSED(index);
    brushChanged();
}


void Widget::on_antialisntChackBox_toggled(bool checked)
{
    shapeCanvas->setAntialiased(checked);
}


void Widget::on_transformsChackBox_toggled(bool checked)
{
    shapeCanvas->setTransformed(checked);
}

void Widget::penChanged()
{
    int penWidth = ui->penWidthSpin->value();
    Qt::PenStyle style = Qt::PenStyle(ui->penStyleCombo->itemData(ui->penStyleCombo->currentIndex()).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(ui->penCapCombo->itemData(ui->penCapCombo->currentIndex()).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(ui->penJoinCombo->itemData(ui->penJoinCombo->currentIndex()).toInt());

    QPen pen;
    pen.setWidth(penWidth);
    pen.setStyle(style);
    pen.setCapStyle(cap);
    pen.setJoinStyle(join);

    shapeCanvas->setPen(pen);
}

void Widget::brushChanged()
{
    Qt::BrushStyle style = Qt::BrushStyle(ui->brushStyleCombo->itemData(ui->brushStyleCombo->currentIndex()).toInt());

    if(style == Qt::LinearGradientPattern)
    {
        QLinearGradient linearGradiet(0,0,100,100);
        linearGradiet.setColorAt(0.0,Qt::red);
        linearGradiet.setColorAt(0.2,Qt::green);
        linearGradiet.setColorAt(1.0,Qt::blue);
        shapeCanvas->setBrush(linearGradiet);
    }else if(style == Qt::RadialGradientPattern)
    {
        QRadialGradient radialGradiet(50,50,50,70,70);
        radialGradiet.setColorAt(0.0,Qt::red);
        radialGradiet.setColorAt(0.2,Qt::green);
        radialGradiet.setColorAt(1.0,Qt::blue);
        shapeCanvas->setBrush(radialGradiet);
    }else if(style == Qt::ConicalGradientPattern)
    {
        QConicalGradient conicalGradiet(50,50,150);
        conicalGradiet.setColorAt(0.0,Qt::red);
        conicalGradiet.setColorAt(0.2,Qt::green);
        conicalGradiet.setColorAt(1.0,Qt::blue);
        shapeCanvas->setBrush(conicalGradiet);
    }else if(style == Qt::TexturePattern)
    {
        shapeCanvas->setBrush(QBrush(QPixmap(":/images/E2nvF5aVgAE-UxB.jpeg")));
    }else
    {
        shapeCanvas->setBrush(QBrush(Qt::blue, style));
    }
}

