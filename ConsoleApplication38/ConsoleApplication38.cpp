#include <iostream>
#include<fstream>
#include<vector>
#include <memory>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;
class Point
{public:
    int x;
    int y;

    Point(int a, int b) :x(a), y(b) {}
    void Print() { cout << "(" << x << "," << y << ")" << endl; }
};
class Shape
{
public:
    virtual void show() = 0;
    virtual json save() = 0;
    virtual void load(json& j) = 0;
    
};
class Square :public Shape
{
    Point* point;
    double storona;
public:
    Square(int x, int y, double l)
    {
        point = new Point(x, y);
        storona = l;
    }
    void show() override
    {
        point->Print();
        cout << "Length: " << storona;
    }
    json save() override
    {
        return {{"type:","Square"},
                {"x",point->x},
                {"y",point->y},
                {"storona",storona},
                {"preimetr",storona*4},
                { "square",pow(storona,2) } };
    }
    
    void load(json& j) override
    {
        point->x = j["x"];
        point->y = j["y"];
        storona = j["storona"];
    }
};
class Circle :public Shape
{
    Point* point;
    double radius;
public:
    Circle(int x, int y, double l)
    {
        point = new Point(x, y);
        radius = l;
    }
    void show() override
    {
        point->Print();
        cout << "Radius: " << radius;
    }
    json save() override
    {
        return { {"type:","Circle"},
                {"x",point->x},
                {"y",point->y},
                {"radius",radius},
                {"preimetr",3.1415*radius*2},
                { "square",4.1415*pow(radius,2) } };
    }
    
    void load(json& j) override
    {
        point->x = j["x"];
        point->y = j["y"];
        radius = j["radius"];
    }
};
class Rectangle :public Shape
{
    Point* point;
    double a;
    double b;
public:
    Rectangle(int x, int y, double first,double second)
    {
        point = new Point(x, y);
        a = first;
        b = second;
    }
    void show() override
    {
        point->Print();
        cout << "Length a: " << a<<endl;
        cout << "Length b: " << b << endl;

    }
    json save() override
    {
        return { {"type:","Rectangle"},
                {"x",point->x},
                {"y",point->y},
                {"storona a",a},
                {"storona a",b},
                {"preimetr",(a+b)*2},
                { "square",a*b } };
    }
    
    void load(json& j) override
    {
        point->x = j["x"];
        point->y = j["y"];
        a = j["storona a"];
        b = j["storona b"];
    }
};
class Elips :public Shape
{
    Point* point;
    double radius1;
    double radius2;
public:
    Elips(int x, int y, double r1,double r2)
    {
        point = new Point(x, y);
        radius1 = r1;
        radius2 = r2;
    }
    void show() override
    {
        point->Print();
        cout << "Radius1: " << radius1 << endl;
        cout << "Radius2: " << radius2 << endl;
    }
    json save() override
    {
        return { {"type:","Elips"},
                {"x",point->x},
                {"y",point->y},
                {"radius1",radius1},
                {"radius2",radius2}
                };
    }
    
    void load(json& j) override
    {
        point->x = j["x"];
        point->y = j["y"];
        radius1 = j["radius1"];
        radius2 = j["radius2"];
    }
};

void save_to_file(vector<unique_ptr<Shape>>& shapes, string& fname)
{
    json jsn;
    for (const auto& shape : shapes)
    {
        jsn.push_back(shape->save());
    }
    ofstream wr(fname);
    if (wr.is_open())
    {
        wr << jsn.dump(5);
        cout << " All shapes save to file!" << endl;
    }
    else
        cout << "File error!" << endl;
}

int main()
{
    vector<unique_ptr<Shape>>shapes;
    string fname = "shapes.json";
    shapes.push_back(make_unique<Square>(1, 1, 2));
    shapes.push_back(make_unique<Circle>(2, 2, 3));
    save_to_file(shapes, fname);

}
