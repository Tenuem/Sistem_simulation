float t, dt, tinic, tfin;
float estado[3]; 
float oldestado[3];
float a, b, c;
float f[3];
int numeq = 3;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void derivacion(float* est, float*f, float tt) 
// espec�fico para el modelo considerado
{
  f[0]=a*est[0]*est[1]-b*est[0];
  f[1]=-a*est[0]*est[1]+est[2]*c;
  f[2]=b*est[0]-est[2]*c;
}


void one_step_runge_kutta(float* inp, float* out, float tt, float hh)
{
 int i, j; 
 float time, incr=0.0;
 float k[numeq][4];
 for (i=0; i<numeq; i++) out[i]=inp[i]; 
 time=tt;
 for (j=0; j<4; j++) {
     derivacion(out,f,time);
     for (i=0; i<numeq; i++) k[i][j]=f[i];
     if (j<2) incr=hh/2;
     //else if (j==0) incr=0;
     else incr=hh;
     time=tt+incr;
     for (i=0; i<numeq; i++) out[i]=inp[i]+k[i][j]*incr;
 }
 for (i=0; i<numeq; i++)
      out[i]=inp[i]+hh/6.0*(k[i][0]+2*k[i][1]+2*k[i][2]+k[i][3]);
      //out[i]=inp[i]+(k[i][0]+2*k[i][1]+2*k[i][2]+k[i][3])/6.0;
}


void one_step_euler(float* inp, float* out, float tt, float hh)
{
  int i;
  derivacion(inp, f, tt);
  for (i=0; i<numeq; i++) out[i]=inp[i]+hh*f[i];
}


int fijar_parametros(int argc, char *argv[]){
    //if (argc<9) return -1;
    //std::cout << argc;
    //for (int i=0; i<argc; i++) std::cout << argv[i] << std::endl;
    a = atof(argv[1]);
    b = atof(argv[2]);
    c = atof(argv[3]);
    dt = atof(argv[4]);
    tinic = atof(argv[5]);
    tfin = atof(argv[6]);
    t = tinic;
    for (int i=0; i<3; i++){
        estado[i] = atof(argv[7+i]);
    }
    printf("a: %f, b: %f, c: %f\ntinic=%f, dt= %f, tfin= %f\nI: %f, S: %f, R: %f\n", a,b,c, tinic,dt,tfin, estado[0],estado[1],estado[2]);
    return 0;
}
#include <fstream>
void salida(){
    std::ofstream outfile;

    outfile.open("results.txt", std::ios_base::app);//std::ios_base::app
    outfile << t << ", " << estado[0] << ", " << estado[1] << ", " << estado[2] << std::endl;

    /*
    std::cout << "Time: " << t << "/" << tfin << std::endl;
    std::cout << "STATUS: I=" << estado[0] << ", S=" << estado[1] << ", R=" << estado[2] << std::endl;
    std::cout << "f(I) = " << f[0] << ", f(S) = " << f[1] << ", f(R) = " << f[2] << std::endl;
    */
}

char** args;
void integracion()
{
   /*
    do {
        //salida();
        for (int i=0; i<3; i++){
            //oldestado[i] = estado[i];
            i+=0;
        }
        //one_step_runge_kutta(oldestado,estado,t,dt); //sustituir por one-step-runge-kutta o por one-step-euler
        //one_step_euler(oldestado,estado,t,dt);
        t+=dt;
    } while (t<tfin);
    //salida();
*/
    //fijar_parametros(10, args);
    do {
        salida();
        for (int i=0; i<3; i++){
            oldestado[i] = estado[i];
        }
        //one_step_runge_kutta(oldestado,estado,t,dt); //sustituir por one-step-runge-kutta o por one-step-euler
        one_step_euler(oldestado,estado,t,dt);
        t+=dt;
    } while (t<tfin);
    salida();
}

int main (int argc, char *argv[]){
    std::cout << "lets see if correct params\n";
    fijar_parametros(argc, argv);
    args = argv;
    //if (result == -1) return -1;
    /*
    for (int i=0; i<argc; i++) std::cout << argv[i] << std::endl;
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    c = atoi(argv[3]);
    dt = atoi(argv[4]);
    tinic = atoi(argv[5]);
    tfin = atoi(argv[6]);
    t = tinic;
    for (int i=0; i<3; i++){
        estado[i] = atoi(argv[7+i]);
    }*/
    //else std::cout << "correct params\n"; 
    t=tinic;
    integracion();
    return 0;
}