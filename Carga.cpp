#include <iostream>
#include <math.h>
#include <string>
#include <vector>
using namespace std;

 string calcularunidad(int unidad){
        if(unidad==1){
            return "milicoloumn";
        }else if(unidad==2){
            return "nanocoloumn";
        }else if(unidad==3){
            return "microcoloumn";
        }

        return " ";
    }

    float convercion(int valorCarga, int valorselecionado){
        //milicoloumn  coloumn=> x10^-3
       //nanocoloumn  coloumn=> x10^-9
      //microcoloumn coloumn=> x10^-6

       string unidad = calcularunidad(valorselecionado);

        if(unidad=="milicoloumn"){
            return valorCarga*pow(10,-3);
        }else if(unidad=="nanocoloumn"){
            return valorCarga*pow(10,-9);
        }else if(unidad=="microcoloumn"){
            return valorCarga*pow(10,-6);
        }
        return 0.0;
    }

struct Posicion {

    int x;
    int y;
    int z;

    string msjposicion  =+"("+to_string(x)+","+to_string(y)+","+to_string(z)+")";

    string getPosicion(){
        return msjposicion;
    }
    int getPosicionx(){
        return x;
    }
    int getPosicionY(){
        return y;
    }
    int getposicionZ(){
        return z;
    }
};

struct Carga {
    string carga;
    float valorCarga;
    struct Posicion posicion;
    bool status;
    float getvalor(){
        return valorCarga;
    };
    string getCarga(){
        return carga;
    };
    bool getstatus(){
        return status;
    }
};

struct ValoresEjecucion{
    float x;
    float y;
    float z;

    float getValueX(){
        return x;
    }
    float getValueY(){
        return y;
    }
    float getValueZ(){
        return z;
    }
};

void ingresarCargas(){
     int total_cargas;
     int carga;
     int unidad_carga;
     int posicionX;
     int posicionY;
     int posicionZ;
     string resp;
     bool respcarga;
   
    cout << "--- Total de cargas a ingresar ---"<<endl;
    cin  >> total_cargas;
    bool aux =true;
      std::vector<Carga>vector_cargas;
  //struct Carga vector_cargas2[total_cargas];
    for (int i = 1; i <= total_cargas; i++)
    {
       cout << "ingrese la carga "<<i<<" "<<"Q = ";
       cin >> carga;
       cout<< "ingrese la unidad de la carga"<<endl;
       cout<<"1. milicoloumn - 2.nanocoloumn - 3. microcoloumn"<<endl;
       cin>>unidad_carga;
       cout << "ingrese la posicion de la carga en X"<<endl;
       cin >> posicionX;
       cout << "ingrese la posicion de la carga en Y"<<endl;
       cin >> posicionY;
       cout<< "ingrese la posicion de la carga en Z"<<endl;
       cin >> posicionZ;
       if (aux)
       {
           cout<< "Buscar el valor que ejercen sobre esta carga? escriba si O no"<<endl;
           cin >> resp;
           if(resp=="si" || resp=="SI"){
              aux=false;
               respcarga=true;
           }else{
               respcarga=false;
           }
       }else{
           respcarga=false;
       }
       
      float cargacoloumn = convercion(carga,unidad_carga);
        string num = to_string(i);
        Carga c = {to_string(i),cargacoloumn,{posicionX,posicionY,posicionZ},respcarga};
      
       vector_cargas.push_back(c);
    }



     cout << "Imprimiendo los valores de las cargas"<<endl;

    for (int i = 0; i < vector_cargas.size(); i++)
    {
       Carga car = vector_cargas[i];
       cout << "Q"<< car.getCarga() << " -- " <<car.getvalor()<<" "<<"Posiciones"<<endl;
    
    };

    cout<<"Iniciando Operaciones..."<<endl;
    cout<< "Calculando fuerza electrica"<<endl;
    cout<<"------------------------------"<<endl;


    float parte1;
    float parte2;
    float parte3;
    Carga cargatrue;
    for (int i = 0; i < vector_cargas.size(); i++){
        Carga c = vector_cargas[i];
       if(c.getstatus()==true){
        cargatrue=c;
        parte1=c.getvalor();
        parte2=(4*3.1416*(8.85*pow(10,-12)));
        parte3 = (parte1/parte2);
        cout << "    Q          "<<parte1<<endl;
        cout << "---------- =  -----------  =   "<<parte3<<endl;
        cout << " 4*π*Eo       "<<parte2<<endl;
        cout<<" "<<endl;
       }
    }
    vector<ValoresEjecucion> valoresejecucion;
  
    float x,y,z;
    //posiciones al cuadrafo
    
    for(int i=0; i<vector_cargas.size(); i++){
        x=0.0;
        y=0.0;
        z=0.0;
         Carga c = vector_cargas[i];
        if(c.getstatus()!=true){
            x = cargatrue.posicion.getPosicionx()-c.posicion.getPosicionx();
            y = cargatrue.posicion.getPosicionY()-c.posicion.getPosicionY();
            z = cargatrue.posicion.getposicionZ()-c.posicion.getposicionZ();

            float resultado = ((pow(x,2))+(pow(y,2))+pow(z,2));
            float resultado2 = pow(resultado,1.5);

            x=x*c.getvalor()*1;
            y=y*c.getvalor()*1;
            z=z*c.getvalor()*1;

            

            x=x/resultado2;
            y=y/resultado2;
            z=z/resultado2;

            //x=x*parte3;
            //y=y*parte3;
            //z=z*parte3;

             cout<<"calculando"<<i<<endl;
            cout<<x<<"ax"<<" "<<y<<"ay"<<" "<<z<<"az"<<endl;
            cout<<" "<<endl;
            ValoresEjecucion v = {x,y,z};
            valoresejecucion.push_back(v);

        }
    }
    x=0.0;
    y=0.0;
    z=0.0;

    for (int i = 0; i < valoresejecucion.size(); i++)
    {
       
        ValoresEjecucion v = valoresejecucion[i];
        x+=v.getValueX();
        y+=v.getValueY();
        z+=v.getValueZ();
    }
        x=x*parte3;
        y=y*parte3;
        z=z*parte3;
    cout<<" "<<endl;
    cout<<"F = ";
    cout<<x<<"ax"<<" ";
    cout<<y<<"ay"<<" ";
    cout<<z<<"az"<<endl;


    cout<<"calculando campo electrico"<<endl;
    cout<<"E = "<<(x/cargatrue.getvalor())<<"ax "<<(y/cargatrue.getvalor())<<"ay "<<(z/cargatrue.getvalor())<<"az"<<endl;
    

}
void menu(){
    int opcion;
    cout << "----menu----"<<endl;
    cout << "-1. Ingresar Cargas"<<endl;
    cout << "-2. salir"<<endl;
    cout << "-------------------------"<<endl;
    cout << "selecione una opcion"<<endl;
    cin >> opcion;

    if (opcion==1)
    {
        ingresarCargas();
    }else{
        cout << "bye";
    }
    
}

int main(){
  menu();
    //operacion de 
}