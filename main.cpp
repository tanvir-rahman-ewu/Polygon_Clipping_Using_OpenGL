#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include<bits/stdc++.h>
using namespace std;

#define Point pair<double,double>

double xmin,xmax,ymin,ymax,x,y,o_x_h=0,o_y_h=0,o_x_l = 1000000,o_y_l = 1000000;
int vertex_nember;
string sequence,p_sequence,s1,s2,s3,s4;
pair<double, double> p;
vector< Point > v,r,lft,rght,top,bottom,global;


void draw_axis()
{
     glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINES);

      glVertex3d (o_x_l-5, ymin, 0.0);
      glVertex3d (o_x_h+5, ymin, 0.0);

      glVertex3d (xmin, o_y_l-20, 0.0);
      glVertex3d (xmin, o_y_h+20, 0.0);

      glVertex3d (o_x_l-5, ymax, 0.0);
      glVertex3d (o_x_h+5, ymax, 0.0);

      glVertex3d (xmax, o_y_l-5, 0.0);
      glVertex3d (xmax, o_y_h+5, 0.0);

	glEnd();
}

void draw_base_polygon()
{
    glClear(GL_COLOR_BUFFER_BIT);

     glColor3f(0.1f, 0.1f, 0.1f);

	glBegin(GL_POLYGON);

        for(int i = 0; i < r.size(); i++)
        {
           // cout<<r[i].first<<"          "<<r[i].second<<endl;
            glVertex3d(r[i].first,r[i].second,0.0);
        }

	glEnd();
}
void display_right(void)
{

    draw_base_polygon();

	glColor3f(1.0, 0.5, 0.0);

	glBegin(GL_POLYGON);

        for(int i = 0; i < rght.size(); i++)
        {
            glVertex3d(rght[i].first,rght[i].second,0.0);
        }

	glEnd();

    draw_axis();

	glFlush();
}

void display_left(void)
{
    draw_base_polygon();

	glColor3f(1.0, 0.5, 0.0);

	glBegin(GL_POLYGON);

        for(int i = 0; i < lft.size(); i++)
        {
            glVertex3d(lft[i].first,lft[i].second,0.0);
        }

	glEnd();

	draw_axis();

	glFlush();
}

void display_top(void)
{
    draw_base_polygon();

	glColor3f(1.0, 0.5, 0.0);

	glBegin(GL_POLYGON);

        for(int i = 0; i < top.size(); i++)
        {
            glVertex3d(top[i].first,top[i].second,0.0);
        }

	glEnd();

	draw_axis();

	glFlush();
}
void display_bottom(void)
{
    draw_base_polygon();

	glColor3f(1.0, 0.5, 0.0);

	glBegin(GL_POLYGON);

        for(int i = 0; i < bottom.size(); i++)
        {
            glVertex3d(bottom[i].first,bottom[i].second,0.0);
        }

	glEnd();

	draw_axis();

	glFlush();
}



void init(void)
{
	glClearColor (0.2, 0.3, 0.3, 1.0);
	glOrtho(o_x_l-5, o_x_h+5, o_y_l-5, o_y_h+5, -1.0, 1.0);
}



void draw()
{
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (300, 300);


    for(int i=0;i<4;i++)
    {
        if(sequence[i] == 'T')
        {
            glutCreateWindow("Top");
            init();
            glutDisplayFunc(display_top);
        }
        else if(sequence[i] == 'B')
        {
            glutCreateWindow("Bottom");
            init();
            glutDisplayFunc(display_bottom);
        }
        else if(sequence[i] =='R')
        {
            glutCreateWindow("Right");
            init();
            glutDisplayFunc(display_right);
        }
        else
        {
            glutCreateWindow("left");
            init();
            glutDisplayFunc(display_left);
        }
    }

	glutMainLoop();
}
void input_file()
{
    ifstream infile;

    infile.open("C:\\Users\\Win10\\Desktop\\line\\b.txt");

    if(infile.fail())
    {
        cout<<"error";
    }
    else
    {
        while(!infile.eof())
        {
            infile >> xmin >> xmax >> ymin >> ymax;

            infile >> s1 >> s2 >> s3>> s4;

            sequence = sequence + s1 + s2 + s3 + s4;

            infile >> vertex_nember;

            for(int i = 0 ; i < vertex_nember; i++)
            {
                infile >> x >> y;
                v.push_back(make_pair(x,y));

                if(x > o_x_h)
                {
                    o_x_h = x;
                }
                if(y > o_y_h)
                {
                    o_y_h = y;
                }
                if(x < o_x_l)
                {
                    o_x_l = x;
                }
                if(y < o_y_l)
                {
                    o_y_l = y;
                }
            }
        }
    }
    infile.close();
    r = v;
}

void print_file_input()
{
    cout<<"-------Polygon Clipping---------"<<endl<<endl;

    cout << "Xmin = " << xmin << endl  << "Xmax = " << xmax <<endl;
    cout << "Ymin = " << ymin << endl  << "Ymax = " << ymax <<endl<<endl;

    cout <<"Sequence for clipping : " <<sequence[0]<<" "<<sequence[1]<<" "<<sequence[2]<<" "<<sequence[3]<<endl<<endl;

    cout<<"Number of vertices of the polygon : " << v.size() <<endl<<endl;

    for(int i = 0; i < v.size(); i++)
    {
         cout <<"Point "<<i+1<<": "<< v[i].first<< " " << v[i].second<<endl;
    }
}

Point lineLineIntersection(Point A, Point B, Point C, Point D)
{

    double a1 = B.second - A.second;
    double b1 = A.first - B.first;
    double c1 = a1*(A.first) + b1*(A.second);


    double a2 = D.second - C.second;
    double b2 = C.first - D.first;
    double c2 = a2*(C.first)+ b2*(C.second);

    double determinant = a1*b2 - a2*b1;

    if (determinant == 0)
    {
        return make_pair(-100000, -100000);
    }
    else
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        return make_pair(x, y);
    }
}

void right_clip()
{
    vector< Point > temp;
    map<Point,int> m;
    Point p1,p2,p3,p4;

    p1 = make_pair(xmax,ymin);
    p2 = make_pair(xmax,ymax);


    for(int i = 0;i<v.size();i++)
    {
        if(i+1 == v.size())
        {
            p3 = make_pair(v[i].first,v[i].second);
            p4 = make_pair(v[0].first,v[0].second);
        }
        else
        {
            p3 = make_pair(v[i].first,v[i].second);
            p4 = make_pair(v[i+1].first,v[i+1].second);

        }

        if(p1.first<p3.first && p1.first == p4.first)
        {
            if(m.find(p4) == m.end())
            {
                temp.push_back(p4);
                m[p4];
            }
        }
        else if(p1.first<p3.first && p1.first > p4.first)
        {
            Point ans;
            ans = lineLineIntersection(p1,p2,p3,p4);

            temp.push_back(ans);
            temp.push_back(p4);
        }
        else if(p1.first>=p3.first && p1.first < p4.first)
        {
            Point ans;
            ans = lineLineIntersection(p1,p2,p3,p4);

            if(m.find(ans) == m.end())
            {
                temp.push_back(ans);
                m[ans];
            }
        }
        else if(p1.first >= p3.first && p1.first >= p4.first)
        {
            if(m.find(p4) == m.end())
            {
                temp.push_back(p4);
                m[p4];
            }
        }
    }
    v = temp;
    rght =temp;
    cout<<endl;
    cout<<"Clipping with respect to right....."<<endl;
    for(int i =0; i<temp.size();i++)
    {
        cout<<temp[i].first<<"  "<<temp[i].second<<endl;
    }

}

void left_clip()
{
    vector< Point > temp;
    map<Point,int> m;
    Point p1,p2,p3,p4;

    p1 = make_pair(xmin,ymin);
    p2 = make_pair(xmin,ymax);

    for(int i = 0;i<v.size();i++)
    {
        if(i+1 == v.size())
        {
            p3 = make_pair(v[i].first,v[i].second);
            p4 = make_pair(v[0].first,v[0].second);
        }
        else
        {
            p3 = make_pair(v[i].first,v[i].second);
            p4 = make_pair(v[i+1].first,v[i+1].second);
        }

        if(p1.first>p3.first && p1.first == p4.first)
        {
            if(m.find(p4) == m.end())
            {
                temp.push_back(p4);
                m[p4];
            }
        }
        else if(p1.first>p3.first && p1.first < p4.first)
        {
            Point ans;
            ans = lineLineIntersection(p1,p2,p3,p4);
            if(m.find(ans) == m.end())
            {
                temp.push_back(ans);
                m[ans];
            }
            if(m.find(p4) == m.end())
            {
                temp.push_back(p4);
                m[p4];
            }

        }
        else if(p1.first<=p3.first && p1.first > p4.first)
        {
            Point ans;
            ans = lineLineIntersection(p1,p2,p3,p4);

            if(m.find(ans) == m.end())
            {
                temp.push_back(ans);
                m[ans];
            }
        }
        else if(p1.first <= p3.first && p1.first <= p4.first)
        {
            if(m.find(p4) == m.end())
            {
                temp.push_back(p4);
                m[p4];
            }
        }
    }
    v = temp;
    lft = temp;
    cout<<endl;
    cout<<"Clipping with respect to left....."<<endl;
    for(int i =0; i<v.size();i++)
    {
        cout<<v[i].first<<"  "<<v[i].second<<endl;
    }

}

void bottom_clip()
{
    vector< Point > temp;
    map<Point,int> m;
    Point p1,p2,p3,p4;

    p1 = make_pair(xmin,ymin);
    p2 = make_pair(xmax,ymin);

    for(int i = 0;i<v.size();i++)
    {
        if(i+1 == v.size())
        {
            p3 = make_pair(v[i].first,v[i].second);
            p4 = make_pair(v[0].first,v[0].second);
        }
        else
        {
            p3 = make_pair(v[i].first,v[i].second);
            p4 = make_pair(v[i+1].first,v[i+1].second);
        }

        if(p1.second>p3.second && p1.second == p4.second)
        {
            if(m.find(p4) == m.end())
            {
                temp.push_back(p4);
                m[p4];
            }
        }
        else if(p1.second>p3.second && p1.second < p4.second)
        {
            Point ans;
            ans = lineLineIntersection(p1,p2,p3,p4);

            temp.push_back(ans);
            temp.push_back(p4);

        }
        else if(p1.second<=p3.second && p1.second > p4.second)
        {
            Point ans;
            ans = lineLineIntersection(p1,p2,p3,p4);

            if(m.find(ans) == m.end())
            {
                temp.push_back(ans);
                m[ans];
            }
        }
        else if(p1.second <= p3.second && p1.second <= p4.second)
        {
            if(m.find(p4) == m.end())
            {
                temp.push_back(p4);
                m[p4];
            }
        }
    }

    v = temp;
    bottom = temp;
    cout<<endl;
    cout<<"Clipping with respect to bottom....."<<endl;
    for(int i =0; i<v.size();i++)
    {
        cout<<v[i].first<<"  "<<v[i].second<<endl;
    }
}

void top_clip()
{
    vector< Point > temp;
    map<Point,int> m;
    Point p1,p2,p3,p4;

    p1 = make_pair(xmin,ymax);
    p2 = make_pair(xmax,ymax);

    for(int i = 0;i<v.size();i++)
    {

        if(i+1 == v.size())
        {
            p3 = make_pair(v[i].first,v[i].second);
            p4 = make_pair(v[0].first,v[0].second);
        }
        else
        {
            p3 = make_pair(v[i].first,v[i].second);
            p4 = make_pair(v[i+1].first,v[i+1].second);
        }

        if(p1.second < p3.second && p1.second == p4.second)
        {
            if(m.find(p4) == m.end())
            {
                temp.push_back(p4);
                m[p4];
            }
        }
        else if(p1.second < p3.second && p1.second > p4.second)
        {
            Point ans;
            ans = lineLineIntersection(p1,p2,p3,p4);

            temp.push_back(ans);
            temp.push_back(p4);
        }
        else if(p1.second >= p3.second && p1.second < p4.second)
        {
            Point ans;
            ans = lineLineIntersection(p1,p2,p3,p4);

            if(m.find(ans) == m.end())
            {
                temp.push_back(ans);
                m[ans];
            }

        }
        else if(p1.second >= p3.second && p1.second >= p4.second)
        {
            if(m.find(p4) == m.end())
            {
                temp.push_back(p4);
                m[p4];
            }
        }
    }
    v = temp;
    top = temp;
    cout<<endl;
    cout<<"Clipping with respect to top....."<<endl;
    for(int i =0; i<v.size();i++)
    {
        cout<<v[i].first<<"  "<<v[i].second<<endl;
    }
}

void sutherland_hodgman()
{
    for(int i = 0; i < 4; i++)
    {
        if(sequence[i] == 'L')
        {
            left_clip();
        }
        else if(sequence[i] == 'R')
        {
            right_clip();
        }
        else if(sequence[i] == 'T')
        {
            top_clip();
        }
        else
        {
            bottom_clip();
        }
    }
}
int main()
{

    input_file();
    print_file_input();

    sutherland_hodgman();
    draw();

	return 0;
}

