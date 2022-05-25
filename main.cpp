#include <iostream>

using namespace std;

struct ShapeVtable;

struct Shape
{
    ShapeVtable* vtable;
};

struct ShapeVtable
{
    // The constructor is not virtual so it does not exist here
    double (*GetArea)(Shape*);
    void (*PrintInfo)(Shape*);
    void (*Destroy)(Shape*); // The destructor is virtual
};

double ShapeGetArea(Shape* current)
{
    return current->vtable->GetArea(current);
}

void ShapePrintInfo(Shape* current)
{
    current->vtable->PrintInfo(current);
}

void ShapeDestroy(Shape* current)
{
    current->vtable->Destroy(current);
}

struct Circle
{
    Shape parent;
    int radius;
    double area;
};

double CircleGetArea(Circle* circle)
{
    return circle->area;
}

void CirclePrintInfo(Circle* circle)
{
    cout<<"Circle - ";
    cout<<"radius:"<<circle->radius<<endl;
}

void CircleDestroy(Circle* circle)
{
    // cout<<"CircleDestroy\n "
}

ShapeVtable circle_vtable=
{
    (double(*)(Shape*)) CircleGetArea,
    (void(*)(Shape*)) CirclePrintInfo,
    (void(*)(Shape*)) CircleDestroy
};

void CircleInitialize(Circle* circle, int radius)
{
    circle->parent.vtable=&circle_vtable;
    circle->radius=radius;
    circle->area=(3.14)*(radius*radius);
}

struct Rectangle
{
    Shape parent;
    int length;
    int width;
    double area;
};

double RectangleGetArea(Rectangle* rectangle)
{
    return rectangle->area;
}

void RectanglePrintInfo(Rectangle* rectangle)
{
    cout<<"Rectangle - ";
    cout<<"length: "<<rectangle->length;
    cout<<", width: "<<rectangle->width<<endl;
}

void RectangleDestroy(Rectangle* rectangle)
{
    // cout<<"RectangleDestroy\n "
}

ShapeVtable rectangle_vtable=
{
    (double(*)(Shape*)) RectangleGetArea,
    (void(*)(Shape*)) RectanglePrintInfo,
    (void(*)(Shape*)) RectangleDestroy
};

void RectangleInitialize(Rectangle* rectangle, int width, int length)
{
    rectangle->parent.vtable=&rectangle_vtable;
    rectangle->length=length;
    rectangle->width=width;
    rectangle->area=length*width;
}

struct Ellipse
{
    Shape parent;
    int radius1;
    int radius2;
    double area;
};

double EllipseGetArea(Ellipse* ellipse)
{
    return ellipse->area;
}

void EllipsePrintInfo(Ellipse* ellipse)
{
    cout<<"Ellipse - ";
    cout<<"radius1: "<<ellipse->radius1;
    cout<<", radius2: "<<ellipse->radius2<<endl;
}

void EllipseDestroy(Ellipse* ellipse)
{
    // cout<<"EllipseDestroy\n "
}

ShapeVtable ellipse_vtable=
{
    (double(*)(Shape*)) EllipseGetArea,
    (void(*)(Shape*)) EllipsePrintInfo,
    (void(*)(Shape*)) EllipseDestroy
};

void EllipseInitialize(Ellipse* ellipse, int radius1, int radius2)
{
    ellipse->parent.vtable=&ellipse_vtable;
    ellipse->radius1=radius1;
    ellipse->radius2=radius2;
    ellipse->area=radius1*radius2*3.14;
}

double GetArea(Shape* shape)
{
    return shape->vtable->GetArea(shape);
}

void PrintInfo(Shape* shape)
{
    shape->vtable->PrintInfo(shape);
}

int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10

    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5

    Ellipse ellipse;
    EllipseInitialize(&ellipse, 10, 12); // ellipse with radius 10, 12

    Shape* shapes[3];
    shapes[0]=(Shape*)&circle ;
    shapes[1]=(Shape*)&rectangle ;
    shapes[2]=(Shape*)&ellipse ;

    double total_area=0;

    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
        PrintInfo(shapes[i]); // prints (cout) the radius if circle, width and height if rectangle, ... etc
    }
    cout<<total_area<<endl; // check if the value is correct

    return 0;
}
