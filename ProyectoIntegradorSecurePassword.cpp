#include <iostream>
#include <string>
#include <fstream>
#include <cstdio> 
#include <Windows.h>

using namespace std; 

//funcion que imprime requisitos para contrasena
void InfoReqPassword() {
    cout << "***********************************************************************\n\n";
    cout << "Para crear una contrasena segura se recomienda seguir estos pasos:\n\n";
     
    cout << "Utilizar: \n";
    cout << " * 8 caracteres o mas\n";
    cout << " * Al menos una letra mayuscula y una letra minuscula.\n";
    cout << " * Al menos un numero y un caracter especial\n";
    cout << "   (por ejemplo, !, @, #, $, %, ^, &, *).\n\n";

    cout << "No utilizar: \n";
    cout << " * Informacion personal, como nombres o fechas de nacimiento.\n";
    cout << " * Palabras comunes que se encuentren en el diccionario.\n";
    cout << " * Secuencias simples como: 12345678, qwerty, 1111111, etc.\n";
    cout << " * Misma contrasena para varias cuentas.\n\n";
    cout << "***********************************************************************\n";
}

//funcion para verificar fortaleza
bool Fortaleza(string password) { 

    bool mayuscula = false;
    bool minuscula = false;
    bool numero = false;
    bool caracterEspecial = false;
   
    string passwComun[8] = { "qwerty", "123456","123456789","password","qwerty123","1q2w3e","111111","1234567890" }; //varias contrasenas mas comunes del mundo

    int i;

    for (i = 0; i < 8; i++) { //verifica si la contrasena es comun
        if (password == passwComun[i]) {
            return false;
            break;
        }
    }

    if (password.length() < 8) { //verifica que el password tenga mas de 8 caracteres
        return false;
    }
        
    for (char caracter : password) {
        if (isupper(caracter)) { //isupper verifica si el caracter es una mayuscula
            mayuscula = true;
        }
        if (islower(caracter)) { //islower verifica si el caracter es una minuscula
            minuscula = true;
        }
        if (isdigit(caracter)) { //isdigit verifica si el caracter es un numero
            numero = true;
        }
        if (!isalnum(caracter)) { //isalnum verifica si el caracter es alfanumerico, si no lo es, entonces es un caracter especial
            caracterEspecial = true;
        }
    }

    //planes futuros: comparar con cada palabra del diccionario

    if (mayuscula && minuscula && numero && caracterEspecial == true) { //si el password contiene todas las especificaciones, es fuerte, de lo contrario, es debil
        return true;            
    }
    else {
        return false;
    }
}

int main()
{
    cout << "***********************************************\n";
    cout << "*                                             *\n";
    cout << "*       Bienvenidos a SecurePassword          *\n";
    cout << "*                                             *\n";
    cout << "*     Este programa te ayudara a guardar      *\n";
    cout << "*     y cifrar tus contraseñas de forma       *\n";
    cout << "*      segura en un archivo de texto.         *\n";
    cout << "*                                             *\n";
    cout << "*      Te informa sobre como crear una        *\n";
    cout << "*        contrasena segura y verifica         *\n";
    cout << "*           cuan fuerte o debil es.           *\n";
    cout << "*                                             *\n";
    cout << "***********************************************\n";  

    //sistema para crear una cuenta   
    int contador1 = 0;
    int answer;
    while (contador1 == 0) {
        
        cout << "***********************************************\n";
        cout << "*             Ingrese una opcion:             *\n";
        cout << "*                                             *\n";
        cout << "* 1- Crear una cuenta                         *\n";
        cout << "* 2- Iniciar sesion                           *\n";
        cout << "*                                             *\n";
        cout << "***********************************************\n";
        cin >> answer;

        if (answer == 1) {

                int seguir;
                cout << "**************************************************************\n";
                cout << "\n ALERTA: Si ya hay una cuenta existente, se eliminara       \n";
                cout << "           al crear una nueva.      \n\n";
                cout << " Desea continuar?\n";
                cout << " 1- SI\n";
                cout << " 2- NO\n\n";
                cout << "**************************************************************\n";
                cin >> seguir;

                if (seguir == 2) {
                    cout << "***********************************************\n";
                    cout << "*      Ha salido del programa con exito.      *\n";
                    cout << "***********************************************\n";
                    return 0;
                }
                else if (seguir == 1) {
                    string filename = "cuenta1.txt";

                    if (remove(filename.c_str()) != 0) {
                    }

                    string savedUser, savedPassword;
                    cout << "**************************************************************\n";
                    cout << "                      *CREAR CUENTA*                  \n\n";

                    cout << " Entre el nombre de usuario: ";
                    cin >> savedUser;

                    do {
                        cout << " Entre la contrasena: ";
                        cin >> savedPassword;

                        if (Fortaleza(savedPassword) == false) {
                            cout << "\n ***La contrasena es debil.***\n\n";
                            cout << " Intente otra contrasena mas segura.\n";
                            InfoReqPassword();
                        }
                        else {
                            ofstream outfile("cuenta1.txt", std::ios::app);
                            outfile << savedUser << " " << savedPassword << endl;
                            cout << "\n**********Cuenta creada exitosamente***********" << endl;
                            contador1 = 1;
                        }

                    } while (Fortaleza(savedPassword) == false);
                }
                else {
                    cout << "Opcion Invalida. Intente de nuevo\n";
                }           
        } 

        if (answer == 2) {

          //login 
            cout << "***********************************************\n";
            cout << "          Ingrese sus credenciales: \n\n";

            string user, password;
            bool login = false;

            int i;
          
                ifstream inputFile("cuenta1.txt");

                // lee la linea
                string userPass;
                getline(inputFile, userPass);

                // Close the file
                inputFile.close();
                // cierra el file

                cout << "Entre el nombre de usuario: ";
                cin >> user;
                cout << "Entre la contrasena: ";
                cin >> password;

                if (userPass == user + " " + password) {
                    cout << "               *Login exitoso*                 \n";
                    contador1 = 1; 
                    break;
                }
                else {
                    cout << "Credenciales incorrectas. Inténtelo de nuevo.\n";                   
                }            
        } 
    }

    //planes futuros, que se bloquee la cuenta despues de tres intentos y anadir una recuperacion de contrasena si se le olvida

    int opcion;
    do {
        cout << "***********************************************\n";
        cout << "*                  Menu:                      *\n";
        cout << "*         1- Guardar Contrasena               *\n";
        cout << "*   2- Verificar Fortaleza de Contrasena      *\n";
        cout << "*        3- Ver lista de contrasenas          *\n";
        cout << "*                                             *\n";
        cout << "***********************************************\n";
        cout << "Ingrese una opcion: ";

        cin >> opcion;

        if (opcion > 3 || opcion < 1) {
            cout << "Opcion invalida. Intente de nuevo.\n"; //si se escoge una opcion fuera de 1 o 2, vuelve a preguntar
        }

        string sitio, usuario, password = "";

        switch (opcion) {

        case 1: 
            //guardar contrasena  
            char password1[75], x;
            cout << "***********************************************************************\n";
            cout << "                     Guardar contrasena:\n\n";
            cout << "\nIngrese el nombre del sitio (ejemplo: Facebook, Banco Popular, Gmail): ";
            cin >> sitio;
            cout << "Ingrese el usuario de la cuenta: ";
            cin >> usuario;

            do { //si la contrasena a guardar no es lo suficientemente fuerte, vuelve a preguntar
                cout << "Ingrese la contrasena: ";
                cin >> password;
                cout << "Confirme la contrasena: ";
                cin >> password1; // char para cifrar contrasena Y

                if (password == password1) {

                    if (Fortaleza(password) == false) { //verifica la fortaleza
                        cout << "\n ***La contrasena es debil.***\n\n";
                        cout << " Intente otra contrasena mas segura.\n";
                        InfoReqPassword(); //imprime info sobre requerimientos de contrasena fuerte
                    }
                    else { //guarda el sitio, usuario y contrasena en archivo

                       //cifrado KEY es 18 funciona con dimensiones Y
                        for (int i = 0; (i < 75 && password1[i] != '\0'); i++)
                            password1[i] = password1[i] + 18;// key3

                        ofstream outfile("almacenamiento.txt", std::ios::app);
                        outfile << sitio << ":\n " << usuario << " \n" << password1 << endl;
                    }
                }
            } while (Fortaleza(password) == false);

            cout << "***********************************************************************\n";
            cout << "\n           ***Contrasena guardada exitosamente***\n\n";
            cout << "  Para ver todas tus contrasenas, ve al menu y selecciona la opcion 3. \n";
            cout << "***********************************************************************\n";
            break;
        case 2:
            // verificar cuan fuerte es el password
            int tryAgain;
            do {
                cout << "Ingrese la contrasena a verificar: ";
                cin >> password;
                cout << "***********************************************\n";

                if (Fortaleza(password) == true) {
                    cout << "La contrasena es fuerte.\n";
                }
                else {
                    cout << "La contrasena es debil.\n";
                    InfoReqPassword();
                }
                do {
                    cout << " Desea verificar otra contrasena?\n";
                    cout << " 1- SI\n";
                    cout << " 2- NO\n";
                    cin >> tryAgain;
                } while (tryAgain > 2);
                
            } while (tryAgain == 1);
            break;  
        case 3:
            //ver y desifrar password todo el texto es importante
            cout << "*******************************************************************************\n";
            cout << "       Instrucciones para tener acceso a sus contrasenas:\n\n";

            cout << " Vera en pantalla algo asi: \n\n";
            cout << "      Inter:    <-- sitio\n";
            cout << "       ferrrio   <-- usuario\n";
            cout << "        DEFyzç\[OBK  <-- contrasena cifrada / cifrado\n\n";

            cout << " Para ver una contrasena en especifico, debe copiar el cifrado de la\n";
            cout << " contrasena deseada y pegarlo en el terminal. En este ejemplo, es DEFyzç\[OBK\n\n";

            cout << "******************************************************************************\n\n";

            char desif[75];

            ifstream file("almacenamiento.txt");

            string line;
            while (getline(file, line)) {
                cout << line << '\n';
            }
            file.close();

            cout << "***********************************************\n";
            cout << " Entre el cifrado de la contrasena deseada: \n";
            
            cin >> desif;

            for (int i = 0; (i < 75 && desif[i] != '\0'); i++)
                desif[i] = desif[i] - 18;// key3
            cout << "***********************************************\n";
            cout << " Esta es su contrasena descifrada: \n";
            cout << desif<< "\n";
       
            break;
        }
      
        do {
            //hacer loop para que pregunte si quiere guardar otra contrasena o verificar
            //si si, que vuelva al menu
            cout << "***********************************************\n";
            cout << "       Para volver al menu presione 4\n";
            cout << "           Para salir presione 0\n";
            cout << "***********************************************\n";
            cin >> opcion;
            if (opcion == 0) {
                break;
            }
            if (opcion != 4) {
                cout << "Opcion invalida. Intente de nuevo.\n";
            }
        } while (opcion != 4);
      
    } while (opcion > 3); 
    cout << "***********************************************\n";
    cout << "*      Gracias por utilizar el programa.      *\n";
    cout << "***********************************************\n";
} 

//anadir disclaimer que este programa no puede identificar 100% si una contrasena es segura o no porque no tiene acceso a su informacion personal para saber

//planes futuros: recuperar contrasena olvidada
