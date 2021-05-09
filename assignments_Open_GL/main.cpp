
#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <algorithm>
#include<iostream>
using namespace std;

#define PI 3.14159265

/*
/*int *retX , *retY ;
retX = new int(Size) ;
retY = new int(Size) ;
delete retX;
delete retY;

int Size_x , Size_y ;
int x_real[4]  , y_real[4] ;
int x_Device[4], y_Device[4] , x_Device_fit[4] , y_Device_fit[4];
int n , D_max_X,D_min_X,D_max_Y,D_min_Y;
int R_max_X,R_max_Y,R_min_Y,R_min_X ;
int F_max_X,F_max_Y,F_min_Y,F_min_X ;
double x_scale , y_scale ,Scale;
struct point
{
    int x;
    int y;
};

void initial_window(int initPos_X ,int initPos_Y ,int Size_x ,int Size_y ,char name[] , int min_x , int max_x , int min_y , int max_y);
void Draw_Point(int x , int y);
void input_data(int *x_real , int *y_real);
void line(int x1 , int y1 , int x2 , int y2 , point arr_point[] , int &arrSize);
void polyline(int *x , int *y , int Size , point arr_point[] , int &arrSize);
void polygon(int *x , int *y , int Size , point arr_point[] , int &arrSize);
void polyline_mapping();
void polyline_mapping_fit();
void mapping(int *x_Device , int *y_Device);
void mapping_with_maxFit(int *x_Device , int *y_Device);

int main()
{

    input_data(x_real , y_real );
    mapping(x_Device , y_Device);
    initial_window(100 , 100 , Size_x , Size_y ,"Mapping" , D_min_X , D_max_X ,D_min_Y , D_max_Y);
    glutDisplayFunc(polyline_mapping);

    mapping_with_maxFit(x_Device_fit , y_Device_fit);
    initial_window(100 , 100 , Size_x , Size_y ,"Mapping with maximum Fit" , D_min_X , D_max_X ,D_min_Y , D_max_Y);
    glutDisplayFunc(polyline_mapping_fit);
    glutMainLoop();
    return 0 ;
}

void initial_window(int initPos_X ,int initPos_Y ,int Size_x ,int Size_y ,char name[] , int min_x , int max_x , int min_y , int max_y)
{
    glutInitWindowPosition(initPos_X , initPos_Y);
    glutInitWindowSize(Size_x , Size_y);
    glutCreateWindow(name);
    glClearColor(1.0,1.0,1.0,0.0);
    glLoadIdentity();
    gluOrtho2D(min_x , max_x , min_y , max_y);
}

void Draw_Point(int x , int y)
{
    glPointSize(2);
    glBegin(GL_POINTS);
    glColor3f(0,0,0);
    glVertex2i(x , y) ;
    glEnd();
}

void input_data(int *x_real , int *y_real )
{
    cout << "enter number of points please ";
    cin >> n;
    cout << "please enter value of device max for x";
    cin >> D_max_X;
    cout << "please enter value of device max for y";
    cin >> D_max_Y;
    cout << "please enter value of device min for x";
    cin >> D_min_X;
    cout << "please enter value of device min for y";
    cin >> D_min_Y;
    cout << "please enter value of Real max for x";
    cin >> R_max_X;
    cout << "please enter value of Real max for y";
    cin >> R_max_Y;
    cout << "please enter value of Real min for x";
    cin >> R_min_X;
    cout << "please enter value of Real min for y";
    cin >> R_min_Y;
    for(int i = 0 ; i < n ; i++)
    {
        cout << "Enter Value of point " << i+1 << endl;
        cin >> x_real[i]>>y_real[i];
        if(i == 0)
        {
            F_max_X = F_min_X = x_real[i] ;
            F_max_Y = F_min_Y = y_real[i] ;
        }
        if(x_real[i] > F_max_X)
        {
            F_max_X = x_real[i]+2 ;
        }
        else if(x_real[i] < F_min_X)
        {
            F_min_X = x_real[i]-2 ;
        }
        if(y_real[i] > F_max_Y)
        {
            F_max_Y = y_real[i]+2 ;
        }
        else if(y_real[i] < F_min_Y)
        {
            F_min_Y = y_real[i]-2 ;
        }
    }
    Size_x = D_max_X - D_min_X;
    Size_y = D_max_Y - D_min_Y;
}

void mapping(int *x_Device , int *y_Device)
{

    if( (R_max_X-R_min_X) == 0)
    {
        x_scale = 10000 ;
    }
    else
    {
        x_scale = ((D_max_X-D_min_X)/(R_max_X-R_min_X));
    }
    cout << "the value of x_scale " << x_scale << endl;

    if( (R_max_Y-R_min_Y) == 0)
    {
        y_scale = 10000 ;
    }
    else
    {
        y_scale = ((D_max_Y-D_min_Y)/(R_max_Y-R_min_Y));
    }
    cout << "the value of y_scale " << y_scale << endl;

    if(x_scale < y_scale)
    {
        Scale = x_scale ;
    }
    else if(x_scale > y_scale)
    {
        Scale = y_scale ;
    }
    else
    {
        Scale = y_scale = x_scale ;
    }
    for(int i = 0 ; i < n ; i++)
    {
        x_Device[i] = (D_min_X+(Scale*(x_real[i]-R_min_X)));

    }
    for(int j = 0 ; j < n ; j++ )
    {
        y_Device[j] = (D_min_Y+(Scale*(y_real[j]-R_min_Y)));
    }

    cout << "the values of device point are "<<endl;
    for(int i = 0 ; i < n ; i++)
    {
        cout << x_Device[i] << "  "<<y_Device[i]<<endl;
    }

}

void mapping_with_maxFit(int *x_Device_fit , int *y_Device_fit)
{

    if( (F_max_X-F_min_X) == 0)
    {
        x_scale = 10000 ;
    }
    else
    {
        x_scale = ((D_max_X-D_min_X)/(F_max_X-F_min_X));
    }
    cout << "the value of x_scale " << x_scale << endl;

    if( (F_max_Y-F_min_Y) == 0)
    {
        y_scale = 10000 ;
    }
    else
    {
        y_scale = ((D_max_Y-D_min_Y)/(F_max_Y-F_min_Y));
    }
    cout << "the value of y_scale " << y_scale << endl;

    if(x_scale < y_scale)
    {
        Scale = x_scale ;
    }
    else if(x_scale > y_scale)
    {
        Scale = y_scale ;
    }
    else
    {
        Scale = y_scale = x_scale ;
    }
    for(int i = 0 ; i < n ; i++)
    {
        x_Device_fit[i] = (D_min_X+(Scale*(x_real[i]-R_min_X)));

    }
    for(int j = 0 ; j < n ; j++ )
    {
        y_Device_fit[j] = (D_min_Y+(Scale*(y_real[j]-R_min_Y)));
    }

    cout << "the values of device point are "<<endl;
    for(int i = 0 ; i < n ; i++)
    {
        cout << x_Device_fit[i] << "  "<<y_Device_fit[i]<<endl;
    }

}

void line(int x1 , int y1 , int x2 , int y2 , point arr_point[] , int &arrSize)
{
    int minX , minY , maxX , maxY ;

    if(x1 > x2)
    {
        maxX = x1 ;
        minX = x2 ;
    }
    else
    {
        maxX = x2 ;
        minX = x1 ;
    }

    if(y1 > y2)
    {
        maxY = y1 ;
        minY = y2 ;
    }
    else
    {
        maxY = y2 ;
        minY = y1 ;
    }

    if(x1 == x2)
    {
       for(int y = minY ; y < maxY ; y++)
       {
           Draw_Point(x1 , y);
           arr_point[arrSize].x = x1  ;
           arr_point[arrSize].y = y ;
           arrSize++;
       }
       return ;
    }

    if(y1 == y2)
    {
       for(int x = minX ; x < maxX ; x++)
       {
           Draw_Point(x , y1);
           arr_point[arrSize].x = x  ;
           arr_point[arrSize].y = y1 ;
           arrSize++;
       }
       return ;
    }

    float m = (float)(y2 - y1)/(x2 - x1);
    float c = y2 - (float)m * x2 ;

    if (abs(int(m)) <= 1)
    {
        int y ;
        for(int x = minX ; x <= maxX ; x++)
        {
            y = (int)((m * x) + c + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
    else
    {
        int x ;
        for(int y = minY ; y <= maxY ; y++)
        {
            x = (int)((( y - c ) / m ) + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
}

void polyline(int *x , int *y , int Size , point arr_point[] , int &arrSize)
{
    for (int i = 0 ; i < (Size - 1 ) ; i++)
    {
        line(x[i] , y[i] , x[i + 1 ] , y[i + 1] ,arr_point ,arrSize);
    }
}

void polygon(int *x , int *y , int Size , point arr_point[] , int &arrSize)
{
    polyline(x , y , Size , arr_point , arrSize);
    line(x[0] , y[0] , x[Size - 1 ] , y[Size - 1] , arr_point , arrSize);
}

void polyline_mapping()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int arrSize = 0 ;
    point arr_point[1500];
    polyline(x_Device , y_Device , n , arr_point , arrSize );
    glFlush();
}
void polyline_mapping_fit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int arrSize = 0 ;
    point arr_point[1500];
    polyline(x_Device_fit , y_Device_fit , n , arr_point , arrSize );
    glFlush();
}


*/

/***********************************************************************************************************************/

/*
// transform

struct point
{
    int x;
    int y;
};

struct color
{
     float red   ;
     float blue  ;
     float green ;
};

void initial_window(int initPos_X ,int initPos_Y ,int Size_x ,int Size_y ,char name[] , int min_x , int max_x , int min_y , int max_y )
{
    glutInitWindowPosition(initPos_X , initPos_Y);
    glutInitWindowSize(Size_x , Size_y);
    glutCreateWindow(name);
    glClearColor(1.0,1.0,1.0,0.0);
    glLoadIdentity();
    gluOrtho2D(min_x , max_x , min_y , max_y);
}

void Draw_Point(int x , int y)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0.0,0.0,0.0);
    glVertex2i(x , y) ;
    glEnd();
}

void Draw_Point_color(int x , int y , color point_color)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f( point_color.red , point_color.blue , point_color.green );
    glVertex2i(x , y) ;
    glEnd();
}

void line(int x1 , int y1 , int x2 , int y2 , point arr_point[] , int &arrSize)
{
    int minX , minY , maxX , maxY ;

    if(x1 > x2)
    {
        maxX = x1 ;
        minX = x2 ;
    }
    else
    {
        maxX = x2 ;
        minX = x1 ;
    }

    if(y1 > y2)
    {
        maxY = y1 ;
        minY = y2 ;
    }
    else
    {
        maxY = y2 ;
        minY = y1 ;
    }

    if(x1 == x2)
    {
       for(int y = minY ; y < maxY ; y++)
       {
           Draw_Point(x1 , y);
           arr_point[arrSize].x = x1  ;
           arr_point[arrSize].y = y ;
           arrSize++;
       }
       return ;
    }

    if(y1 == y2)
    {
       for(int x = minX ; x < maxX ; x++)
       {
           Draw_Point(x , y1);
           arr_point[arrSize].x = x  ;
           arr_point[arrSize].y = y1 ;
           arrSize++;
       }
       return ;
    }

    float m = (float)(y2 - y1)/(x2 - x1);
    float c = y2 - (float)m * x2 ;

    if (abs(int(m)) <= 1)
    {
        int y ;
        for(int x = minX ; x <= maxX ; x++)
        {
            y = (int)((m * x) + c + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
    else
    {
        int x ;
        for(int y = minY ; y <= maxY ; y++)
        {
            x = (int)((( y - c ) / m ) + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
}

void polyline(int *x , int *y , int Size , point arr_point[] , int &arrSize)
{
    for (int i = 0 ; i < (Size - 1 ) ; i++)
    {
        line(x[i] , y[i] , x[i + 1 ] , y[i + 1] ,arr_point ,arrSize);
    }
}

void polygon(int *x , int *y , int Size , point arr_point[] , int &arrSize)
{
    polyline(x , y , Size , arr_point , arrSize);
    line(x[0] , y[0] , x[Size - 1 ] , y[Size - 1] , arr_point , arrSize);
}

void Transform(int *x , int *y , int Size ,float matrix[3][3])
{
    int *retX , *retY ;
    retX = new int(Size) ;
    retY = new int(Size) ;
    int temp , j ;
    for(int i = 0 ; i < Size ; i++)
    {
        for(int j = 0 ; j < 2 ; j++)
        {
            temp = 0 ;
            temp += (int)(matrix[j][0]*x[i]);
            temp += (int)(matrix[j][1]*y[i]);
            temp += (int)(matrix[j][2]);
            if(j == 0)
            {
                retX[i] = temp ;
            }
            else
            {
                retY[i] = temp ;
            }
        }
    }
    for(int i = 0 ; i < Size ; i++)
    {
        x[i] = retX[i];
        y[i] = retY[i];
    }
    delete retX;
    delete retY;
}

void show()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int arrSize = 0 ;
    point arr_point[10000];
    float trans[][3] = {{1 , 0 , 10} , {0 , 1 , 50} , {0 , 0 , 1}};
    int x[] = {50 , 200 , 400 , 600};
    int y[] = {50 , 300 , 300 , 100};
    Transform(x , y , 4 , trans ) ;
    polygon(x , y , 4 , arr_point , arrSize );
    glFlush();
}

int main()
{
    initial_window(100 , 100 , 800 , 400 ,"Draw Polygon" ,0 , 800 , 0 , 400);
    glutDisplayFunc(show);
    glutMainLoop();
    return 0 ;
}

*/

/***********************************************************************************************************************/

/*
// seed Fill


struct point
{
    int x;
    int y;
};

struct color
{
     float red   ;
     float blue  ;
     float green ;
};

void initial_window(int initPos_X ,int initPos_Y ,int Size_x ,int Size_y ,char name[] , int min_x , int max_x , int min_y , int max_y )
{
    glutInitWindowPosition(initPos_X , initPos_Y);
    glutInitWindowSize(Size_x , Size_y);
    glutCreateWindow(name);
    glClearColor(1.0,1.0,1.0,0.0);
    glLoadIdentity();
    gluOrtho2D(min_x , max_x , min_y , max_y);
}

void Draw_Point(int x , int y)
{
    glPointSize(1);
    glBegin(GL_POINTS);
    glColor3f(0.0,0.0,0.0);
    glVertex2i(x , y) ;
    glEnd();
}

void Draw_Point_color(int x , int y , color point_color)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f( point_color.red , point_color.blue , point_color.green );
    glVertex2i(x , y) ;
    glEnd();
}

void line(int x1 , int y1 , int x2 , int y2 , point arr_point[] , int &arrSize)
{
    int minX , minY , maxX , maxY ;

    if(x1 > x2)
    {
        maxX = x1 ;
        minX = x2 ;
    }
    else
    {
        maxX = x2 ;
        minX = x1 ;
    }

    if(y1 > y2)
    {
        maxY = y1 ;
        minY = y2 ;
    }
    else
    {
        maxY = y2 ;
        minY = y1 ;
    }

    if(x1 == x2)
    {
       for(int y = minY ; y < maxY ; y++)
       {
           Draw_Point(x1 , y);
           arr_point[arrSize].x = x1  ;
           arr_point[arrSize].y = y ;
           arrSize++;
       }
       return ;
    }

    if(y1 == y2)
    {
       for(int x = minX ; x < maxX ; x++)
       {
           Draw_Point(x , y1);
           arr_point[arrSize].x = x  ;
           arr_point[arrSize].y = y1 ;
           arrSize++;
       }
       return ;
    }

    float m = (float)(y2 - y1)/(x2 - x1);
    float c = y2 - (float)m * x2 ;

    if (abs(int(m)) <= 1)
    {
        int y ;
        for(int x = minX ; x <= maxX ; x++)
        {
            y = (int)((m * x) + c + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
    else
    {
        int x ;
        for(int y = minY ; y <= maxY ; y++)
        {
            x = (int)((( y - c ) / m ) + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
}

void polyline(int *x , int *y , int Size , point arr_point[] , int &arrSize)
{
    for (int i = 0 ; i < (Size - 1 ) ; i++)
    {
        line(x[i] , y[i] , x[i + 1 ] , y[i + 1] ,arr_point ,arrSize);
    }
}

void polygon(int *x , int *y , int Size , point arr_point[] , int &arrSize)
{
    polyline(x , y , Size , arr_point , arrSize);
    line(x[0] , y[0] , x[Size - 1 ] , y[Size - 1] , arr_point , arrSize);
}

void seed_fill(int x , int y , color Fpoint_color , color Bpoint_color)
{
    color Rpoint_color ;
    glReadPixels(x , y , 1 , 1 , GL_RED   , GL_FLOAT , &(Rpoint_color.red  )) ;
    glReadPixels(x , y , 1 , 1 , GL_GREEN , GL_FLOAT , &(Rpoint_color.green)) ;
    glReadPixels(x , y , 1 , 1 , GL_BLUE  , GL_FLOAT , &(Rpoint_color.blue )) ;
    if( ( (Rpoint_color.red ) == (Fpoint_color.red) && (Rpoint_color.green ) == (Fpoint_color.green) && (Rpoint_color.blue ) == (Fpoint_color.blue) ) || ( (Rpoint_color.red ) == (Bpoint_color.red) && (Rpoint_color.green ) == (Bpoint_color.green) && (Rpoint_color.blue ) == (Bpoint_color.blue) ) )
    {
        return ;
    }
    Draw_Point_color( x , y , Fpoint_color) ;
    seed_fill(x + 1 , y , Fpoint_color , Bpoint_color );
    seed_fill(x - 1 , y , Fpoint_color , Bpoint_color );
    seed_fill(x , y + 1 , Fpoint_color , Bpoint_color );
    seed_fill(x , y - 1 , Fpoint_color , Bpoint_color );
}

void show_seed_fill()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int arrSize = 0 ;
    point arr_point[10000];
    color Fpoint_color = {0 , 0 , 0};
    color Bpoint_color = {0 , 0 , 0};
    int x[] = {50 , 200 , 200 , 50};
    int y[] = {50 , 50 , 200 , 200};
    polygon(x , y , 4 , arr_point , arrSize );
    seed_fill(51 , 51 , Fpoint_color , Bpoint_color );
    glFlush();
}

int main()
{
    initial_window(100 , 100 , 800 , 400 ,"Draw Polygon" ,0 , 800 , 0 , 400);
    glutDisplayFunc(show_seed_fill);
    glutMainLoop();
    return 0 ;
}
*/


/***********************************************************************************************************************/
/*

// sort x and y
struct point
{
    int x;
    int y;
};

struct color
{
     float red   ;
     float blue  ;
     float green ;
};

void initial_window(int initPos_X ,int initPos_Y ,int Size_x ,int Size_y ,char name[] , int min_x , int max_x , int min_y , int max_y )
{
    glutInitWindowPosition(initPos_X , initPos_Y);
    glutInitWindowSize(Size_x , Size_y);
    glutCreateWindow(name);
    glClearColor(1.0,1.0,1.0,0.0);
    glLoadIdentity();
    gluOrtho2D(min_x , max_x , min_y , max_y);
}

void Draw_Point(int x , int y)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0,0,0);
    glVertex2i(x , y) ;
    glEnd();
}

void Draw_Point_color(int x , int y , color point_color)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f( point_color.red , point_color.blue , point_color.green );
    glVertex2i(x , y) ;
    glEnd();
}

void line(int x1 , int y1 , int x2 , int y2 , point arr_point[] , int &arrSize)
{
    int minX , minY , maxX , maxY ;

    if(x1 > x2)
    {
        maxX = x1 ;
        minX = x2 ;
    }
    else
    {
        maxX = x2 ;
        minX = x1 ;
    }

    if(y1 > y2)
    {
        maxY = y1 ;
        minY = y2 ;
    }
    else
    {
        maxY = y2 ;
        minY = y1 ;
    }

    if(x1 == x2)
    {
       for(int y = minY ; y < maxY ; y++)
       {
           Draw_Point(x1 , y);
           arr_point[arrSize].x = x1  ;
           arr_point[arrSize].y = y ;
           arrSize++;
       }
       return ;
    }

    if(y1 == y2)
    {
       for(int x = minX ; x < maxX ; x++)
       {
           Draw_Point(x , y1);
           arr_point[arrSize].x = x  ;
           arr_point[arrSize].y = y1 ;
           arrSize++;
       }
       return ;
    }

    float m = (float)(y2 - y1)/(x2 - x1);
    float c = y2 - (float)m * x2 ;

    if (abs(int(m)) <= 1)
    {
        int y ;
        for(int x = minX ; x <= maxX ; x++)
        {
            y = (int)((m * x) + c + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
    else
    {
        int x ;
        for(int y = minY ; y <= maxY ; y++)
        {
            x = (int)((( y - c ) / m ) + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
}

void polyline(int *x , int *y , int Size , point arr_point[] , int &arrSize)
{
    for (int i = 0 ; i < (Size - 1 ) ; i++)
    {
        line(x[i] , y[i] , x[i + 1 ] , y[i + 1] ,arr_point ,arrSize);
    }
}

void polygon(int *x , int *y , int Size , point arr_point[] , int &arrSize)
{
    polyline(x , y , Size , arr_point , arrSize);
    line(x[0] , y[0] , x[Size - 1 ] , y[Size - 1] , arr_point , arrSize);
}


bool compare_y(point i , point j)
{
    if(i.y < j.y)
    {
        return true ;
    }
    else if(i.y > j.y)
    {
        return false ;
    }
    else if(i.x < j.x)
    {
        return true ;
    }
    else
    {
        return false ;
    }
}

bool compare_x(point i , point j)
{
    if(i.x < j.x)
    {
        return true ;
    }
    else if(i.x > j.x)
    {
        return false ;
    }
    else if(i.y < j.y)
    {
        return true ;
    }
    else
    {
        return false ;
    }
}


void Sort(point *arr_point , int arrSize)
{
    std::sort(arr_point , arr_point + arrSize , compare_x) ; // sort on x
    for(long i =0 ; i < arrSize - 1 ; i++ )
    {
        cout << arr_point[i].x << "  " << arr_point[i].y <<endl;
    }
}

void all_point()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int arrSize = 0 ;
    point arr_point[10000];
    int x[] = {100 , 300 , 400 , 50};
    int y[] = {70 , 80 , 150 , 250};
    polygon(x , y , 4 , arr_point , arrSize );
    Sort(arr_point , arrSize );
    glFlush();

}

int main()
{
    all_point();
    return 0;
}
*/
/***********************************************************************************************************************/


// shape fill

struct point
{
    int x;
    int y;
};

struct color
{
     float red   ;
     float blue  ;
     float green ;
};

void initial_window(int initPos_X ,int initPos_Y ,int Size_x ,int Size_y ,char name[] , int min_x , int max_x , int min_y , int max_y )
{
    glutInitWindowPosition(initPos_X , initPos_Y);
    glutInitWindowSize(Size_x , Size_y);
    glutCreateWindow(name);
    glClearColor(1.0,1.0,1.0,0.0);
    glLoadIdentity();
    gluOrtho2D(min_x , max_x , min_y , max_y);
}

void Draw_Point(int x , int y)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0,0,0);
    glVertex2i(x , y) ;
    glEnd();
}

void Draw_Point_color(int x , int y , color point_color)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f( point_color.red , point_color.blue , point_color.green );
    glVertex2i(x , y) ;
    glEnd();
}

void line(int x1 , int y1 , int x2 , int y2 , point arr_point[] , int &arrSize)
{
    int minX , minY , maxX , maxY ;

    if(x1 > x2)
    {
        maxX = x1 ;
        minX = x2 ;
    }
    else
    {
        maxX = x2 ;
        minX = x1 ;
    }

    if(y1 > y2)
    {
        maxY = y1 ;
        minY = y2 ;
    }
    else
    {
        maxY = y2 ;
        minY = y1 ;
    }

    if(x1 == x2)
    {
       for(int y = minY ; y < maxY ; y++)
       {
           Draw_Point(x1 , y);
           arr_point[arrSize].x = x1  ;
           arr_point[arrSize].y = y ;
           arrSize++;
       }
       return ;
    }

    if(y1 == y2)
    {
       for(int x = minX ; x < maxX ; x++)
       {
           Draw_Point(x , y1);
           arr_point[arrSize].x = x  ;
           arr_point[arrSize].y = y1 ;
           arrSize++;
       }
       return ;
    }

    float m = (float)(y2 - y1)/(x2 - x1);
    float c = y2 - (float)m * x2 ;

    if (abs(int(m)) <= 1)
    {
        int y ;
        for(int x = minX ; x <= maxX ; x++)
        {
            y = (int)((m * x) + c + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
    else
    {
        int x ;
        for(int y = minY ; y <= maxY ; y++)
        {
            x = (int)((( y - c ) / m ) + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
}

bool compare_y(point i , point j)
{
    if(i.y < j.y)
    {
        return true ;
    }
    else if(i.y > j.y)
    {
        return false ;
    }
    else if(i.x < j.x)
    {
        return true ;
    }
    else
    {
        return false ;
    }
}

void Fill(point *arr_point , int arrSize , color point_color)
{
    std::sort(arr_point , arr_point + arrSize , compare_y) ; // sort on y
    for(long i =0 ; i < arrSize - 1 ; i++ )
    {
        if(arr_point[i].y == arr_point[i + 1 ].y)
        {
            for(int j = arr_point[i].x+1 ; j < arr_point[i + 1].x ; j++)
            {
                Draw_Point_color(j , arr_point[i].y , point_color);
            }
        }
    }
}

void polyline(int *x , int *y , int Size , point arr_point[] , int &arrSize)
{
    for (int i = 0 ; i < (Size - 1 ) ; i++)
    {
        line(x[i] , y[i] , x[i + 1 ] , y[i + 1] ,arr_point ,arrSize);
    }
}

void polygon(int *x , int *y , int Size , point arr_point[] , int &arrSize)
{
    polyline(x , y , Size , arr_point , arrSize);
    line(x[0] , y[0] , x[Size - 1 ] , y[Size - 1] , arr_point , arrSize);
}

void show_shape_fill()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int arrSize = 0 ;
    point arr_point[1500];
    color point_color = {0.6 , 0.8 , 0};
    int x[] = {50 , 400 , 400 , 50};
    int y[] = {50 , 50 , 300 , 300};
    polygon(x , y , 4 , arr_point , arrSize );
    Fill(arr_point , arrSize , point_color);
    glFlush();
}


int main()
{
    initial_window(100 , 100 , 800 , 400 ,"Draw and color" ,0 , 800 , 0 , 400);
    glutDisplayFunc(show_shape_fill);
    glutMainLoop();
    return 0 ;
}



/***********************  Assignment 7 & Assignment 8 *******************************************/

/*

float arr3_3x3[3][3] ,mat_inverse[3][3] ,determinant = 0;
float point1_before[3]= {20,10,1} , point2_before[3] = {13,14,1} ,point1_after[3],point2_after[3];

struct point
{
    int x;
    int y;
};

struct color
{
     float red   ;
     float blue  ;
     float green ;
};

void initial_window(int initPos_X ,int initPos_Y ,int Size_x ,int Size_y ,char name[] , int min_x , int max_x , int min_y , int max_y )
{
    glutInitWindowPosition(initPos_X , initPos_Y);
    glutInitWindowSize(Size_x , Size_y);
    glutCreateWindow(name);
    glClearColor(1,1,1,0);
    glLoadIdentity();
    gluOrtho2D(min_x , max_x , min_y , max_y);
}

void matrix_inversion (float mat[3][3])
{
    for(int i = 0; i < 3; i++)
    {
		determinant = determinant + (mat[0][i] * (mat[1][(i+1)%3] * mat[2][(i+2)%3] - mat[1][(i+2)%3] * mat[2][(i+1)%3]));
    }

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++)
        {
			mat_inverse[i][j]=((mat[(j+1)%3][(i+1)%3] * mat[(j+2)%3][(i+2)%3]) - (mat[(j+1)%3][(i+2)%3] * mat[(j+2)%3][(i+1)%3]))/ determinant;
        }
	}

}

void multiply_two_matrices_3x3(float arr1[3][3] , float arr2[3][3] )
{
    float mat[3][3] ;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            mat[i][j] = 0;
            for(int k=0;k<3;k++)
            {
                mat[i][j]+=arr1[i][k]*arr2[k][j];
            }
        }
    }

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            arr3_3x3[i][j] = mat[i][j];
        }
    }

}

void multiply_matrix_3x3_and_3x1(float arr1[3][3] , float arr2[] ,  float *arr3_3x1 )
{
    for(int i = 0 ; i < 3 ; i++)
    {
        arr3_3x1[i] = ( ( (arr1[i][0]) * (arr2[0]) )+( (arr1[i][1]) * (arr2[(1)]) ) +( (arr1[i][2]) * (arr2[(2)]) ) );
    }
}

void Draw_Point_color(int x , int y , color point_color)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f( point_color.red , point_color.blue , point_color.green );
    glVertex2i(x , y) ;
    glEnd();
}

void line(int x1 , int y1 , int x2 , int y2 , point arr_point[] , int &arrSize , color color_line)
{
    int minX , minY , maxX , maxY ;

    if(x1 > x2)
    {
        maxX = x1 ;
        minX = x2 ;
    }
    else
    {
        maxX = x2 ;
        minX = x1 ;
    }

    if(y1 > y2)
    {
        maxY = y1 ;
        minY = y2 ;
    }
    else
    {
        maxY = y2 ;
        minY = y1 ;
    }

    if(x1 == x2)
    {
       for(int y = minY ; y < maxY ; y++)
       {
           Draw_Point_color(x1 , y , color_line);
           arr_point[arrSize].x = x1  ;
           arr_point[arrSize].y = y ;
           arrSize++;
       }
       return ;
    }

    if(y1 == y2)
    {
       for(int x = minX ; x < maxX ; x++)
       {
           Draw_Point_color(x , y1, color_line);
           arr_point[arrSize].x = x  ;
           arr_point[arrSize].y = y1 ;
           arrSize++;
       }
       return ;
    }

    float m = (float)(y2 - y1)/(x2 - x1);
    float c = y2 - (float)m * x2 ;

    if (abs(int(m)) <= 1)
    {
        int y ;
        for(int x = minX ; x <= maxX ; x++)
        {
            y = (int)((m * x) + c + 0.5);
            Draw_Point_color(x , y, color_line);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
    else
    {
        int x ;
        for(int y = minY ; y <= maxY ; y++)
        {
            x = (int)((( y - c ) / m ) + 0.5);
            Draw_Point_color(x , y, color_line);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
}

void Display_line()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int arrSize = 0 ;
    point arr_point[1500];
    color line_before = {0,1,0} ;
    color line_after = {1,0,0} ;
    line(point1_before[0],point1_before[1],point2_before[0],point2_before[1],arr_point,arrSize , line_before );
    line(point1_after[0],point1_after[1],point2_after[0],point2_after[1],arr_point,arrSize,line_after);
    glFlush();

}

void rotate_mat(double *sin_x , double *cos_y ,double setaa ,bool anti_clock)
{

    double seta = setaa *PI/180;
    if (anti_clock == true)
    {
        *sin_x = sin(seta);
        *cos_y = cos(seta);
    }
    else
    {
        *sin_x = sin(-seta);
        *cos_y = cos(-seta);
    }
}

void composite_matrix(float scaling[3][3],float translate[3][3],float shearing[3][3],float rotare[3][3])
{

    multiply_two_matrices_3x3(rotare , shearing);
    multiply_two_matrices_3x3(arr3_3x3 , scaling);
    multiply_two_matrices_3x3(arr3_3x3 , translate);
}


int main ()
{

    double sin_x , cos_y  ;
    rotate_mat(&sin_x , &cos_y , 60 , true);
    int point_x1 = 20 , point_x2 = 13 , point_y1 = 10 , point_y2 = 14 ;
    float ar1[3][3] = {{1,2,3},{4,5,6},{7,8,9}} , ar2[3][3]={{2,4,6},{8,10,12},{14,16,18}} , arr3_3x1[3] ;

    float scaling[3][3]={{1.2,0,0},{0,0.5,0},{0,0,1}} , translate[3][3] ={{1,0,15},{0,1,-7},{0,0,1}} ;
    float shearing[3][3] ={{1,1.3,0},{2.1,1,0},{0,0,1}} , rotare[3][3] = {{cos_y,-sin_x,0},{sin_x,cos_y,0},{0,0,1}};


    composite_matrix(scaling , translate , shearing , rotare);
    matrix_inversion(arr3_3x3);
    multiply_matrix_3x3_and_3x1(arr3_3x3 , point1_before ,&point1_after[0]);
    multiply_matrix_3x3_and_3x1(arr3_3x3 , point2_before ,&point2_after[0]);

    initial_window(100 , 100 , 1000 , 500 ,"Composite Transformation" ,-100 , 100 , -100 , 100);

    glutDisplayFunc(Display_line);

    glutMainLoop();


    return 0 ;
}


*/



/***********************  Assignment 6 [ multiply_two_matrices_3x3 ] *******************************************/
/*
float arr3[3][3];
void multiply_two_matrices_3x3(float arr1[3][3] , float arr2[3][3] )
{
    for(int i = 0 ; i < 3 ; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {

            arr3[i][j] = ( ( (arr1[i][j]) * (arr2[0][j]) )+( (arr1[i][j]) * (arr2[(1)][j]) ) +( (arr1[i][j]) * (arr2[(2)][j]) ) );
        }
    }
}

void print_output_of_multiply()
{
    cout << "out num ar3 "<<endl ;
    for(int i = 0 ; i < 3 ; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            cout << arr3[i][j];
            cout << "   " ;
        }
        cout << endl;
    }
}


int main ()
{
    float ar1[3][3] = {{1,2,3},{0,-3,4},{1,5,2}} , ar2[3][3]={{1,0,1},{0,1,0},{1,0,1}} ;
    multiply_two_matrices_3x3(ar1 , ar2 );
    print_output_of_multiply();
    return 0 ;
}

*/

/***********************  Assignment 5 [multiply_matrix_3x3_and_3x1 ]*******************************************/

/*
void multiply_matrix_3x3_and_3x1(float arr1[3][3] , float arr2[] ,  float *arr3 )
{
    for(int i = 0 ; i < 3 ; i++)
    {
        arr3[i] = ( ( (arr1[i][0]) * (arr2[0]) )+( (arr1[i][1]) * (arr2[(1)]) ) +( (arr1[i][2]) * (arr2[(2)]) ) );
    }
}


int main ()
{
    float ar1[3][3] = {{1,0,0},{0,1,0},{0,0,1}} , ar2[3]={1,2,3} , ar3[3] ;
    multiply_matrix_3x3_and_3x1(ar1 , ar2 ,&ar3[0]);

    for(int i = 0 ; i < 3 ; i++)
    {
        cout<< ar3[i] <<endl ;
    }

    return 0 ;
}

*/

/***********************************************************************************************************************/
/*

//Draw Polygon

struct point
{
    int x;
    int y;
};

void initial_window(int initPos_X ,int initPos_Y ,int Size_x ,int Size_y ,char name[] , int min_x , int max_x , int min_y , int max_y )
{
    glutInitWindowPosition(initPos_X , initPos_Y);
    glutInitWindowSize(Size_x , Size_y);
    glutCreateWindow(name);
    glClearColor(1.0,1.0,1.0,0.0);
    glLoadIdentity();
    gluOrtho2D(min_x , max_x , min_y , max_y);
}

void Draw_Point(int x , int y)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0.0,0.0,0.0);
    glVertex2i(x , y) ;
    glEnd();
}

void line(int x1 , int y1 , int x2 , int y2 , point arr_point[] , int &arrSize)
{
    int minX , minY , maxX , maxY ;

    if(x1 > x2)
    {
        maxX = x1 ;
        minX = x2 ;
    }
    else
    {
        maxX = x2 ;
        minX = x1 ;
    }

    if(y1 > y2)
    {
        maxY = y1 ;
        minY = y2 ;
    }
    else
    {
        maxY = y2 ;
        minY = y1 ;
    }

    if(x1 == x2)
    {
       for(int y = minY ; y < maxY ; y++)
       {
           Draw_Point(x1 , y);
           arr_point[arrSize].x = x1  ;
           arr_point[arrSize].y = y ;
           arrSize++;
       }
       return ;
    }

    if(y1 == y2)
    {
       for(int x = minX ; x < maxX ; x++)
       {
           Draw_Point(x , y1);
           arr_point[arrSize].x = x  ;
           arr_point[arrSize].y = y1 ;
           arrSize++;
       }
       return ;
    }

    float m = (float)(y2 - y1)/(x2 - x1);
    float c = y2 - (float)m * x2 ;

    if (abs(int(m)) <= 1)
    {
        int y ;
        for(int x = minX ; x <= maxX ; x++)
        {
            y = (int)((m * x) + c + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
    else
    {
        int x ;
        for(int y = minY ; y <= maxY ; y++)
        {
            x = (int)((( y - c ) / m ) + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
}

void polyline(int *x , int *y , int Size , point arr_point[] , int &arrSize)
{
    for (int i = 0 ; i < (Size - 1 ) ; i++)
    {
        line(x[i] , y[i] , x[i + 1 ] , y[i + 1] ,arr_point ,arrSize);
    }
}

void polygon(int *x , int *y , int Size , point arr_point[] , int &arrSize)
{
    polyline(x , y , Size , arr_point , arrSize);
    line(x[0] , y[0] , x[Size - 1 ] , y[Size - 1] , arr_point , arrSize);
}

void Show_Polygon()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int arrSize = 0 ;
    point arr_point[1500];
    int x[] ={50 , 400 , 400 ,50};
    int y[] ={50 , 50 , 500 ,500};
    polyline(x,y,4,arr_point,arrSize);
    glFlush();
}

int main()
{
    initial_window(100 , 100 , 800 , 400 ,"Draw Polygon" ,0 , 800 , 0 , 600);
    glutDisplayFunc(Show_Polygon);
    glutMainLoop();
    return 0 ;
}

*/

/***********************************************************************************************************************/
/*

//Draw Line

void initial_window(int initPos_X ,int initPos_Y ,int Size_x ,int Size_y ,char name[] , int min_x , int max_x , int min_y , int max_y )
{
    glutInitWindowPosition(initPos_X , initPos_Y);
    glutInitWindowSize(Size_x , Size_y);
    glutCreateWindow(name);
    glClearColor(1.0,1.0,1.0,0.0);
    glLoadIdentity();
    gluOrtho2D(min_x , max_x , min_y , max_y);
}


struct point
{
    int x;
    int y;
};

void Draw_Point(int x , int y)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0.0,0.0,0.0);
    glVertex2i(x , y) ;
    glEnd();
}


void line(int x1 , int y1 , int x2 , int y2 , point arr_point[] , int &arrSize)
{
    int minX , minY , maxX , maxY ;

    if(x1 > x2)
    {
        maxX = x1 ;
        minX = x2 ;
    }
    else
    {
        maxX = x2 ;
        minX = x1 ;
    }

    if(y1 > y2)
    {
        maxY = y1 ;
        minY = y2 ;
    }
    else
    {
        maxY = y2 ;
        minY = y1 ;
    }

    if(x1 == x2)
    {
       for(int y = minY ; y < maxY ; y++)
       {
           Draw_Point(x1 , y);
           arr_point[arrSize].x = x1  ;
           arr_point[arrSize].y = y ;
           arrSize++;
       }
       return ;
    }

    if(y1 == y2)
    {
       for(int x = minX ; x < maxX ; x++)
       {
           Draw_Point(x , y1);
           arr_point[arrSize].x = x  ;
           arr_point[arrSize].y = y1 ;
           arrSize++;
       }
       return ;
    }

    float m = (float)(y2 - y1)/(x2 - x1);
    float c = y2 - (float)m * x2 ;

    if (abs(int(m)) <= 1)
    {
        int y ;
        for(int x = minX ; x <= maxX ; x++)
        {
            y = (int)((m * x) + c + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
    else
    {
        int x ;
        for(int y = minY ; y <= maxY ; y++)
        {
            x = (int)((( y - c ) / m ) + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
}

void Show_Line()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int arrSize = 0 ;
    point arr_point[1500];
    line(0,0,600,600,arr_point,arrSize);
    glFlush();
}

int main()
{
    initial_window(100 , 100 , 800 , 400 ,"Draw Line" ,0 , 800 , 0 , 400);
    glutDisplayFunc(Show_Line);
    glutMainLoop();
    return 0 ;
}

*/

/************************************* Football Stadium Assignment 1************************/

/*

bool init = false ;

struct point
{
    int x;
    int y;
};

struct color
{
     float red   ;
     float blue  ;
     float green ;
};

void initial_window(int initPos_X ,int initPos_Y ,int Size_x ,int Size_y ,char name[] , int min_x , int max_x , int min_y , int max_y )
{
    glutInitWindowPosition(initPos_X , initPos_Y);
    glutInitWindowSize(Size_x , Size_y);
    glutCreateWindow(name);
    glClearColor(1.0,1.0,1.0,0.0);
    glLoadIdentity();
    gluOrtho2D(min_x , max_x , min_y , max_y);
}

void Draw_Point(int x , int y)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0.0,0.0,0.0);
    glVertex2i(x , y) ;
    glEnd();
}

void Draw_Point_color(int x , int y , color point_color)
{
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f( point_color.red , point_color.blue , point_color.green );
    glVertex2i(x , y) ;
    glEnd();
}

void line(int x1 , int y1 , int x2 , int y2 , point arr_point[] , int &arrSize)
{
    int minX , minY , maxX , maxY ;

    if(x1 > x2)
    {
        maxX = x1 ;
        minX = x2 ;
    }
    else
    {
        maxX = x2 ;
        minX = x1 ;
    }

    if(y1 > y2)
    {
        maxY = y1 ;
        minY = y2 ;
    }
    else
    {
        maxY = y2 ;
        minY = y1 ;
    }

    if(x1 == x2)
    {
       for(int y = minY ; y < maxY ; y++)
       {
           Draw_Point(x1 , y);
           arr_point[arrSize].x = x1  ;
           arr_point[arrSize].y = y ;
           arrSize++;
       }
       return ;
    }

    if(y1 == y2)
    {
       for(int x = minX ; x < maxX ; x++)
       {
           Draw_Point(x , y1);
           arr_point[arrSize].x = x  ;
           arr_point[arrSize].y = y1 ;
           arrSize++;
       }
       return ;
    }

    float m = (float)(y2 - y1)/(x2 - x1);
    float c = y2 - (float)m * x2 ;

    if (abs(int(m)) <= 1)
    {
        int y ;
        for(int x = minX ; x <= maxX ; x++)
        {
            y = (int)((m * x) + c + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
    else
    {
        int x ;
        for(int y = minY ; y <= maxY ; y++)
        {
            x = (int)((( y - c ) / m ) + 0.5);
            Draw_Point(x , y);
            arr_point[arrSize].x = x ;
            arr_point[arrSize].y = y ;
            arrSize++;
        }
    }
}


void draw_Stadium()
{
    int arrSize = 0 ;
    point arr_point[1500];
    color points_1 ={1,0,0};
    color points_2 ={0,0,1};
    srand(time(NULL));
    glClearColor(0,1,0,0);

    glClear(GL_COLOR_BUFFER_BIT);
    line(100 , 0 , 100 , 200 , arr_point , arrSize);


    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_LINE_STRIP);
    int r = 20 ;
    for(float i = 0 ; i < 360 ; i = i +.5)
    {
        glVertex2f(100+sin(i)*r,100+cos(i)*r);
    }


    if (init == false)
    {
        int x = (rand()%200)+1;
        int y = (rand()%200)+1;

        Draw_Point_color(20,10 ,points_1);Draw_Point_color(70,150,points_1);Draw_Point_color(29,73 ,points_1);
        Draw_Point_color(46,190,points_1);Draw_Point_color(73,46 ,points_1);

        Draw_Point_color(120,10 ,points_2);Draw_Point_color(170,150,points_2);Draw_Point_color(129,73 ,points_2);
        Draw_Point_color(146,190,points_2);Draw_Point_color(173,46 ,points_2);

        init = true ;
    }
    else
    {
        int x = (rand()%200)+1;
        int y = (rand()%200)+1;

        glBegin(GL_POINTS);

        glColor3f(1,0,0);
        glVertex2f((20+x)%200,(10+y)%200);glVertex2f((70+x)%200,(150+y)%200);
        glVertex2f((29+x)%200,(73+y)%200);glVertex2f((46+x)%200,(190+y)%200);
        glVertex2f((73+x)%200,(46+y)%200);

        glColor3f(0,0,1);
        glVertex2f((120+x)%200,(10+y)%200);glVertex2f((170+x)%200,(150+y)%200);
        glVertex2f((129+x)%200,(73+y)%200);glVertex2f((146+x)%200,(190+y)%200);
        glVertex2f((173+x)%200,(46+y)%200);
    }

    glEnd();
    glFlush();
    Sleep( 500 );
    glutPostRedisplay();

}

int main ()
{
    initial_window(100 , 100 , 1000 , 500 ,"POINTS" ,0 , 200 , 0 , 200);

    glutDisplayFunc(draw_Stadium);


    glutMainLoop();

    return 0 ;
}

*/

