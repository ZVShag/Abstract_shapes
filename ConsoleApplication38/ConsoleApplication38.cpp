#include <iostream>
#include<fstream>
#include<vector>
#include <memory>
#include<nlohmann/json.hpp>

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
    virtual void load(const json& j) = 0;
    
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
    
    void load(const json& j) override
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
                {"preimetr",3.1415 * radius * 2},
                { "square",4.1415 * pow(radius,2) } };
    }

    void load(const json& j) override
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
                {"storona b",b},
                {"preimetr",(a+b)*2},
                { "square",a*b } };
    }

    void load(const json& j) override
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
    Elips(int x, int y, double r1, double r2)
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
    void load(const json& j) override
    {
        point->x = j["x"];
        point->y = j["y"];
        radius1 = j["radius 1"];
        radius2 = j["radius 2"];
    }
};
void save_to_file(const vector<unique_ptr<Shape>>& shape, string& fname)
{
    json vector_json;
    for (const auto& shp : shape)
    {
        vector_json.push_back(shp->save());
    }
    ofstream wr(fname);
    if (wr.is_open())
        wr << vector_json.dump(2);
    else
        cout << "File error!";
}
vector<unique_ptr<Shape>> load_from_file(const string& fname)
{
    vector<unique_ptr<Shape>> shape;
    ifstream rd(fname);
    json json_vector;
    rd >> json_vector;
    for (const auto& i : json_vector)
    {
        unique_ptr<Shape> shp;
        if (i["type"] == "Square")
        {
            auto square = make_unique<Square>();
            square->load(i);
            shp = move(square);
        }
        else
        {
            if (i["type"] == "Circle")
            {
                auto circle = make_unique<Circle>();
                circle->load(i);
                shp = move(circle);
            }
            else
            {
                if (i["type"] == "Rectangle")
                {
                    auto rect = make_unique<Rectangle>();
                    rect->load(i);
                    shp = move(rect);
                }
                else {
                    if (i["type"] == "Elips")
                    {
                        auto elp = make_unique<Elips>();
                        elp->load(i);
                        shp = move(elp);
                    }
                }
            }
        }
        if (shp)
            shape.push_back(move(shp));
       

    }
    return shape;

}
int main()
{
    vector<unique_ptr<Shape>> shapes;
    string fname = "shapes.json";
    shapes.push_back(make_unique<Square>(1, 1, 4));
    shapes.push_back(make_unique<Circle>(2, 2, 3));
    shapes.push_back(make_unique<Rectangle>(3, 3, 4.0, 5.0));
    shapes.push_back(make_unique<Elips>(2, 3, 6, 2));
    save_to_file(shapes, fname);

}
