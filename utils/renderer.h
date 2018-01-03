#include <GL/glut.h>

using namespace std;

class Punct
{
    float x, y;
public:
    Punct(float aux1, float aux2): x(aux1), y(aux2){} 
    Punct(){}
    float get_x() {return x;}
    float get_y() {return y;}
    friend bool operator == (Punct& a, Punct& b)
    {
        if((a.get_x() == b.get_x()) && (a.get_y() == b.get_y()))
            return 1;
        else 
            return 0;
    }

    void initializare(float aux1, float aux2)
    {
        x = aux1;
        y = aux2;
    }

    friend ostream& operator << (ostream& o, Punct p)
    {
        o << " (" << p.x << ", " << p.y << ") ";
        return o;
    }
};

vector<Punct> Acoperire;                //aici vom depozita punctele acoperirii
int scale = 1;
class Renderer
{
    private:
        int windowWidth, windowHeight;
        int windowPosX, windowPosY;
        string windowTitle;
        int argc;
        char **argv;

    public:
        Renderer(int argc, char **argv)
        {
            this->argc = argc;
            this->argv = argv;
            this->windowWidth = 300;
            this->windowHeight = 300;
            this->windowPosX = 100;
            this->windowPosY = 100;
            this->windowTitle = "OpenGL Window";
        }

        Renderer(int argc, char **argv, int width, int height, int x, int y, string title)
        {
            this->argc = argc;
            this->argv = argv;
            this->windowWidth = width;
            this->windowHeight = height;
            this->windowPosX = x;
            this->windowPosY = y;
            this->windowTitle = title;
        }

        static void draw(void)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glLineWidth(2.5); 
            glColor3f(1.0, 0.0, 0.0);
            glScalef((float)scale / 10, (float)scale / 10, (float)scale / 10);
            glBegin(GL_LINES);
            int i;
                for(i=0; i<Acoperire.size()-1; i++)
                {
                    glVertex3f(Acoperire[i].get_x(), Acoperire[i].get_y(), 0.0);
                    glVertex3f(Acoperire[i+1].get_x(), Acoperire[i+1].get_y(), 0.0);
                }

                // si legam si ultimul punct de primul la final
                glVertex3f(Acoperire[i].get_x(), Acoperire[i].get_y(), 0.0f);
                glVertex3f(Acoperire[0].get_x(), Acoperire[0].get_y(), 0.0f);
            glEnd();
            glFlush();
        }

        int init()
        {
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_SINGLE);
            glutInitWindowSize(this->windowWidth, this->windowHeight);
            glutInitWindowPosition(this->windowPosX, this->windowPosY);
            glutCreateWindow(this->windowTitle.c_str());
            glutDisplayFunc(draw);
            glutMainLoop();

            return 0;
        }

};