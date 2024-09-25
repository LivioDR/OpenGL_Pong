#include <gl/glut.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
using namespace std;

// variables globales...
string jug1="Jugador 1",jug2="Jugador 2";//nombre de los jugadores
float Mov1=0; //movimiento paleta 1
float Mov2=0; //movimiento paleta 2
int DirX=1,DirY=1; // vector unitario de mov de la pelota
float MovX=2.0,MovY=-3.0; // pos. inicial de la pelota
bool start=false, fuego=false; // interruptores de inicio y del evento fuego
float colorfuego1, colorfuego2, colorfuego3; //color de pelota en modo fuego
float choque1,choque2; // modulo de distancia entre pelota y paletas
float color=1.0; // color de la linea central
int Puntos1=0, Puntos2=0; // puntaje de cada jugador
float vel_pelota, vel_jugadores; // velocidades de pelota y paletas
float angulo=90; // angulo de giro de pelota (modo fuego)


void inicio(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2,0.2,0.2,0.0);
}

void dibujar(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	
	glTranslatef(0.0,Mov1,0.0);
	
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON); // paleta 1
	glVertex2i(-12,-3);
	glVertex2i(-12,3);
	glVertex2i(-11,3);
	glVertex2i(-11,-3);
	glEnd();
	
	glPopMatrix();
	
	glPushMatrix();
	
	glTranslatef(0.0,Mov2,0.0);
	
	glBegin(GL_POLYGON); // paleta 2
	glVertex2i(12,-3);
	glVertex2i(12,3);
	glVertex2i(11,3);
	glVertex2i(11,-3);
	glEnd();
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslatef(MovX,MovY,0.0);
	if(fuego)glRotatef(angulo,0.0,0.0,1.0);
	glBegin(GL_POLYGON); //pelotita (cuadrada)
	if(fuego){
		colorfuego1=1.0;
		colorfuego2=0.5;
		colorfuego3=0.0;
	}
	if(!fuego){
		colorfuego1=1.0;
		colorfuego2=1.0;
		colorfuego3=1.0;
	}
	glColor3f(colorfuego1,colorfuego2,colorfuego3);
	glVertex2f(-0.5,-0.5);
	glVertex2f(0.5,-0.5);
	glVertex2f(0.5,0.5);
	glVertex2f(-0.5,0.5);
	
	glEnd();
	
	glPopMatrix();
	

	glColor3f(color,color,color);
	glBegin(GL_LINES);// linea del medio... se puede sacar/poner con 1/2
	glVertex2i(0,-15);
	glVertex2i(0,15);
	glEnd();
	
	
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON); // recuadro del "escenario"
	glVertex2i(-15,-15);
	glVertex2i(-15,15);
	glVertex2i(15,15);
	glVertex2i(15,-15);
	glEnd();
	
	glutSwapBuffers();
	
}

void teclado(unsigned char key, int x, int y){
	switch(key)
	{
	case 27: exit(0);
	case 'w': {if(Mov1<=12)
				Mov1+=vel_jugadores;break;}
	case 's': {if(Mov1>=-12)
				Mov1-=vel_jugadores;break;}
	case 'y': {if(Mov2<=12)
				Mov2+=vel_jugadores;break;}
	case 'h': {if(Mov2>=-12)
				Mov2-=vel_jugadores;break;}
	case 'f': {glutFullScreen();break;}
	case 'r': {glutReshapeWindow(256,256);break;}
	case 'W': {if(Mov1<=12)
		Mov1+=vel_jugadores;break;}
	case 'S': {if(Mov1>=-12)
		Mov1-=vel_jugadores;break;}
	case 'Y': {if(Mov2<=12)
		Mov2+=vel_jugadores;break;}
	case 'H': {if(Mov2>=-12)
		Mov2-=vel_jugadores;break;}
	case 'F': {glutFullScreen();break;}
	case 'R': {glutReshapeWindow(256,256);break;}
	case 13:{start=true;break;} // Empieza el juego o saca la pausa...
	case 'P':{start=false;break;} // Pone el juego en Pausa
	case 'p':{start=false;break;}
	case '1':{
			color=0.0;
		break;}
	case '2':{	
			color=1.0;
		break;}
	}
	
}

void redibujar(int w, int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluOrtho2D(-15.0,15.0,-15.0,15.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void Idle(int valor){//los 1ros 4 son colision de pelota con escenario
	if(MovX>14.5)
		{
		DirX=(DirX*(-1));
		Puntos1++;
		system("cls");
		cout<<jug1.c_str()<<": "<<Puntos1<<endl
			<<jug2.c_str()<<": "<<Puntos2<<endl;
		}
	if(MovX<-14.5)
		{
		DirX=(DirX*(-1));
		Puntos2++;
		system("cls");
		cout<<jug1.c_str()<<": "<<Puntos1<<endl
			<<jug2.c_str()<<": "<<Puntos2<<endl;
		}
	if(MovY>14.5)
		DirY=(DirY*(-1));
	if(MovY<-14.5)
		DirY=(DirY*(-1));
	if(start==true){// presionar Enter para empezar
		MovX+=(vel_pelota*DirX);
		MovY+=(vel_pelota*DirY);
			}
	if(MovX<-11) // deteccion de colisiones paleta 1
	{
		choque1=sqrt((Mov1-MovY)*(Mov1-MovY)); // modulo de diferencia de altura entre paleta y pelota
		if(choque1<3)
			DirX=DirX*(-1);	
	}
	if(MovX>11) // deteccion de colisiones paleta 2
		{
		choque2=sqrt((Mov2-MovY)*(Mov2-MovY)); // modulo de diferencia de altura entre paleta y pelota
		if(choque2<3)
		DirX=DirX*(-1);	
		}
	angulo+=20;
	if(angulo>=360)
		angulo-=360;
	if((sqrt((Puntos1-Puntos2)*(Puntos1-Puntos2)))>4){// activa el fuego cuando la diferencia es mayor a 4
		fuego=true;}
	else
		fuego=false;
	if(fuego){// velocidades en modo fuego
		vel_pelota=0.3;
		vel_jugadores=0.4;}
	else // velocidades normales...
		{vel_pelota=0.2;
		vel_jugadores=0.25;}
	glutPostRedisplay();
	glutTimerFunc(25, Idle, 0);
}

int main(int argc, char *argv[]){
//	cout<<"Jugador 1, ingrese su nombre:";
//	cin.getline((char*)jug1.c_str(), 256);
//	cout<<"Jugador 2, ingrese su nombre:";
//	cin.getline((char*)jug2.c_str(), 256);
	glutInit(&argc,argv); 
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);

	glutInitWindowSize(256,256);
	glutInitWindowPosition(400,250);
	glutCreateWindow("Pong V1.3b - Creado por Livio D. Reinoso - ");
	
	inicio();
	glutDisplayFunc(dibujar);
	glutReshapeFunc(redibujar);
	glutKeyboardFunc(teclado);
	glutTimerFunc(25, Idle, 0);
	
	
	glutMainLoop(); 
	return 0;
}
