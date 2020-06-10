#include <iostream>
#include <vector>
#include <math.h>

using namespace std;


struct Circle
{
    enum class Print{WithCordinates,WithoutCordinates};

    void printCircle(ostream &os=cout, Print type=Print::WithCordinates);

    double radius();

    void radius(double rad);

    double centerx();

    double centery();

    Circle(double rad=9);

private:

    struct y1y2
    {
        double y1=0;
        double y2=0;

        y1y2(double x1=0, double x2=0)
            :y1(x1), y2(x2)
        {}
    };

    y1y2 y(double x);

    void markInMap(double x, double y, char ch='*');

    void fillMap();

    double cx; // center x
    double cy; // center y
    double rd; // radius

    vector<vector<char>>map; // hold the map for our circle
};

Circle::y1y2 Circle::y(double x)
{
    // using this equation : y = cy -+ (rd^2 - (x-cx))^0.5
    // where y1 = cy - (rd^2 - (x-cx))^0.5
    // and y2 = cy + (rd^2 - (x-cx))^0.5
    // given x, together with the radius and center cordinates : cx and cy
    // find the possible haves of y
    // we expect 2 values for y : y1 and y2 because of the sqrt in the equation

    double b=pow(rd,2)-pow(x-cx,2);
    if(b<0)b*=-1;
    double c = sqrt(b);
    return{cy-c,cy+c};
}

void Circle::markInMap(double x, double y, char ch)
{
    // marks the sport specified as x,y using the "char"acter ch
    // we accept doubles because most of the calculation result in doubles

    if(
            !(y<0&&map.size()-1<y)&& // do we have that line
            !(x<0&&map[0].size()-1<x)&& // do have that column
            (y==int(y))&& // no approximate values
            (x==int(x))
            )
        map[int(y)][int(x)]=ch;
}

void Circle::fillMap()
{
    // we find those points on the map that are part of the circle and mark it
    // we supply the x values and get the y
    // the we use the cordinate to mark

    for(unsigned int x=cx-rd; x<=cx+rd; x++)
    {
        markInMap(x,y(x).y1);
        markInMap(x,y(x).y2);
    }
    markInMap(cx,cy); // mark the center
}

void Circle::printCircle(ostream &os, Circle::Print type)
{
    // display the circle(map)
    // fill the map before we display it

    fillMap();
    os
            <<"circle\n"
           <<"radius = " << rd << "\n"
          <<"centerx = " << cx << "\n"
         <<"centery = " << cy << "\n"
        <<"Scale :\n"
       <<"\ty-axis : 1line=1unit\n"
      <<"\tx-axis : 2char/2columns=1unit\n\n\n";

    if(rd<8)
        type=Print::WithoutCordinates;

    for(unsigned int y=0; y<map.size(); y++)
    {    for(unsigned int x=0; x<map[0].size(); x++)
        {
            os<<map[y][x]<<' ';

            if(map[y][x]!=' ') // do we have a mark
                if(type==Print::WithCordinates) // should we display a the cordinates of the mark
                    os<<'('<<x<<','<<y<<')'; // display the cordinates of the mark
        }
        os <<"\n";
    }
}

double Circle::radius()
{
    return rd;
}

void Circle::radius(double rad)
{
    // the user is not allowed to specify center because
    // primary output is console and the cordinates provided might conflict
    // and difficult to represent
    // rad : radius

    rd=rad;
    cx=rd+5;
    cy=cx;

    int mapLen=(cx+1)*2; // enough to display all points
    map=vector<vector<char>>(mapLen,vector<char>(mapLen,' '));
}

double Circle::centerx()
{
    return cx;
}

double Circle::centery()
{
    return cy;
}

Circle::Circle(double rad)
{
    radius(rad);
}


void next_line(istream & is)
{
    //clear istream and prepare for a fresh start
    //take every thing from "is"

    for (char ch; is.get(ch);)
        if (ch == '\n') return;
}

void cerr_mg(const string & mg)
{
    //print error massage with a little editing
    cerr << "Error : \n" << mg << "\n";
}

void cin_num(double & n)
{
    while (true)
    {
        cin >> n;
        if (cin) break;
        cin.clear();
        cin.ignore();
        cerr_mg("Bad number, Try again");
    }
}

void cin_num(int & n)
{
    while (true)
    {
        cin >> n;
        if (cin) break;
        cin.clear();
        next_line(cin);
        cerr_mg("Bad number, Try again");
    }
}

void setup()
{
    system("mode 800");
    system("title Draw Circle");
}


void demo()
{
    for(;;)
    {
        cout << "Enter radius : \n>> ";
        double rad;
        cin_num(rad);
        Circle c(rad);
        c.printCircle();
        c.printCircle(cout,Circle::Print::WithoutCordinates);

        cout << "\n\n";
    }
}

void main_app()
{
    Circle c(25);
    c.printCircle();
    c.printCircle(cout,Circle::Print::WithoutCordinates);
}


void prompt()
{
    cout << "Draw Circle; this program sketch circles. \n\n"

            "You enter a value as radius, the program  \n"
            "will draw the circle. \n\n"

            "from radius [1-20], odd radius gives more \n"
            "points. \n\n"

            "Avoid radius below 7 and above 29 (does   \n"
            "not display well on small screens).       \n\n";
}

int main()
{    
    setup();
    prompt();

    bool demo_mode = true;

    if(demo_mode) demo();
    else main_app();

    return 0;
}
































































// 0207775839 kofi, umat
