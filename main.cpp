#include <iostream>
#include <string>
#include <fstream>
#include <string_view>
#include <regex>
#include <vector>
#include <ctime>


using std::string;

template <typename T>
struct PassChain {

    string Nazwa;
    string Login;
    string Haslo;
    string Kat;
    string Web;

    PassChain* next;
};

template <typename T>
T listSize ( PassChain<T>* current ){
    T tmp = 0;
    while( current ){
        current = current->next;
        tmp++;
    }
    return tmp;
}

template <typename T>
void showList(PassChain<T>* head){

    std::cout << "\n==============Start==of==List=======================\n" << std::endl;
    PassChain<T>* tmp = head;
    int a=listSize( head );
    for (int i = 0; i < a; ++i) {

        std::cout << '\n' <<i+1 << '.' << std::endl;
        std::cout << "Nazwa: " << tmp->Nazwa << std::endl;
        std::cout << "Login: " << tmp->Login << std::endl;
        std::cout << "Haslo: " << tmp->Haslo << std::endl;
        std::cout << "Kat: " << tmp->Kat << std::endl;
        std::cout << "Web: " << tmp->Web << std::endl;
        tmp = tmp->next;

    }
    if (tmp != nullptr){
        tmp = tmp->next;
    }
    std::cout << "\n==============END==of==List=======================\n" << std::endl;
}

template <typename T>
PassChain<T>* toList(const std::vector<char> vec) {



    PassChain<T> *head = nullptr;
    PassChain<T> **current = &head;

//    vec.push_back('\n');

    string
            patern1 = "Nazwa: ",
            patern2 = "Login: ",
            patern3 = "Haslo: ",
            patern4 = "Kat: ",
            patern5 = "Web: ",
            line, Nazwa, Login, Haslo, Kat, Web;

    line="";
    int ln=0;
    bool nline=false,pack=false;

    for (int i = 0; i < vec.size(); ++i) {

        line=line+vec.at(i);

        if(vec.at(i)=='\n') {
            ln++;
            nline=true;
        }

        if(nline){
            if (line.find(patern1) != std::string::npos) {
                std::vector<char> v(line.begin() + patern1.length(), line.end() - 2);
                for (int j = 0; j < v.size(); ++j) {
                    Nazwa = Nazwa + (char) (v.at(j));
                }
            }
            else if (line.find(patern2) != std::string::npos) {
                std::vector<char> v(line.begin() + patern2.length(), line.end() - 2);
                for (int j = 0; j < v.size(); ++j) {
                    Login = Login + v[j];
                }
            }
            else if (line.find(patern3) != std::string::npos) {
                std::vector<char> v(line.begin() + patern3.length(), line.end() - 2);
                for (int j = 0; j < v.size(); ++j) {
                    Haslo = Haslo + v[j];
                }
            }
            else if (line.find(patern4) != std::string::npos) {
                std::vector<char> v(line.begin() + patern4.length(), line.end() - 2);
                for (int j = 0; j < v.size(); ++j) {
                    Kat = Kat + v[j];
                }
            }
            else if (line.find(patern5) != std::string::npos) {
                std::vector<char> v(line.begin() + patern5.length(), line.end() - 2);
                for (int j = 0; j < v.size(); ++j) {
                    Web = Web + v[j];
                }
            }
            else {
                pack=true;
            }

            if (pack ){
                pack=false;

                *current = new PassChain<T>{Nazwa, Login, Haslo, Kat, Web, nullptr};
                current = &(*current)->next;

                Nazwa="",Login="",Haslo="",Kat="",Web="";
            }

            nline= false;
            line="";
        }


    }



    return  head;
}

void toVec(const std::string& name,std::vector<char>& vec){
    string line;
    std::ifstream plik(name);

    if (plik.is_open()){

        while (std::getline(plik,line)){
            std::vector<char> v(line.begin(),line.end());
            for (int i = 0; i < v.size(); ++i) {
                vec.push_back(v.at(i));
            }
            v.clear();
            vec.push_back('\n');
        }
//        vec.push_back('\n');
        plik.close();
    }
}

void toPlik(const std::string& name, std::vector<char>& Tekst){

    std::ofstream plik(name);
    if (plik.is_open()){
        int i=0;
        while(i<Tekst.size()) {
            plik << Tekst.at(i);
            i++;
        }
        plik.close();
    } else
        std::cout << "Problem z otarciem pliku. Blad(class>mathoda>liniaMetody): main>toPlik>" << __LINE__-10 << std::endl;
}

void encrypt(std::vector<char>& Tekst,const int enCode){

    std::vector<char> newVec;
    char n='\n';
    for (int i = 0; i < Tekst.size(); ++i) {
        if (Tekst.at(i)==n)
            newVec.push_back(Tekst.at(i));
        else
            newVec.push_back((char)(Tekst.at(i)+enCode));

    }
    Tekst.clear();
    for (int i = 0; i < newVec.size(); ++i) {
        Tekst.push_back(newVec.at(i));
    }

}

void decrypt(std::vector<char>& Tekst,const int enCode) {

    std::vector<char> newVec;
    char n='\n';
    for (int i = 0; i < Tekst.size(); ++i) {
        if (Tekst.at(i)==n)
            newVec.push_back(Tekst.at(i));
        else
            newVec.push_back((char)(Tekst.at(i)-enCode));
    }
    Tekst.clear();
    for (int i = 0; i < newVec.size(); ++i) {
        Tekst.push_back(newVec.at(i));
    }

}

template <typename T>
void fromList(PassChain<T>* head, std::vector<char>& vec){

    PassChain<T>* tmp = head;
    int a=listSize( head );
    string buf;
    for (int i = 0; i < a; ++i) {

        for (int j = 0; j <6; ++j) {
            switch (j) {
                case 0:
                    buf="Nazwa: " + tmp->Nazwa + ";\n";
                    break;
                case 1:
                    buf="Login: " + tmp->Login + ";\n";
                    break;
                case 2:
                    buf="Haslo: " + tmp->Haslo + ";\n";
                    break;
                case 3:
                    buf="Kat: " + tmp->Kat + ";\n";
                    break;
                case 4:
                    buf="Web: " + tmp->Web + ";\n";
                    break;
                case 5:
                    buf="\n";
                    break;
                default:
                    std::cout << " Something wrong " << std::endl;
            }
            if (tmp->Nazwa.empty()){
                return;
            }
            std::vector<char> v(buf.begin(),buf.end());
            for (int z = 0; z < v.size(); ++z) {
                vec.push_back(v.at(z));
            }

            buf="";
        }
        tmp = tmp->next;
    }
}

template <typename T>
void wyszukaj(PassChain<T>* head, const int& katWysz, const std::string& slowoKlucz){

    std::cout << "==============Start==of==List=======================\n" << std::endl;
    PassChain<T>* tmp = head;
    int a=listSize( head );
    string buf;



    bool czyF=false,czyN= true;

    for (int i = 0; i < a; ++i)
    {
        switch (katWysz) {
            case 1:
                if(tmp->Nazwa==slowoKlucz) {
                    czyF = true ;
                    czyN = false;
                }

                break;
            case 2:
                if(tmp->Login==slowoKlucz) {
                    czyF=true;
                    czyN = false;
                }
                break;
            case 3:
                if(tmp->Haslo==slowoKlucz) {
                    czyF=true;
                    czyN = false;
                }
                break;
            case 4:
                if(tmp->Kat==slowoKlucz) {
                    czyF=true;
                    czyN = false;
                }
                break;
            case 5:
                if(tmp->Web==slowoKlucz) {
                    czyF=true;
                    czyN = false;
                }
                break;

        }

        if (czyF){
            czyF=false;
            std::cout << '\n' <<i+1 << '.' << std::endl;
            std::cout << "Nazwa: " << tmp->Nazwa << std::endl;
            std::cout << "Login: " << tmp->Login << std::endl;
            std::cout << "Haslo: " << tmp->Haslo << std::endl;
            std::cout << "Kat: " << tmp->Kat << std::endl;
            std::cout << "Web: " << tmp->Web << std::endl;
            std::cout << std::endl;
        }

        tmp = tmp->next;
    }

    if(czyN){
        std::cout << "Nie znaleziono zadnego hasla o podanych kategoriach\n" << std::endl;
    }
    std::cout << "================END==of==List=======================\n" << std::endl;
}

template <typename T>
void sortPass(PassChain<T>* head){

    std::cout << "\n==============Start==of==List=======================\n" << std::endl;
    PassChain<T>* tmp = head;
    int a=listSize( head );
    for (int i = 0; i < a; ++i) {

        std::cout << '\n' <<i+1 << '.' << std::endl;
        std::cout << "Nazwa: " << tmp->Nazwa << std::endl;
        std::cout << "Login: " << tmp->Login << std::endl;
        std::cout << "Haslo: " << tmp->Haslo << std::endl;
        std::cout << "Kat: " << tmp->Kat << std::endl;
        std::cout << "Web: " << tmp->Web << std::endl;
        tmp = tmp->next;

    }
    if (tmp != nullptr){
        tmp = tmp->next;
    }
    std::cout << "\n==============Start==of==List=======================\n" << std::endl;
}

void genHaslo(const std::string& kat, std::string haslo){

    std::vector<char> v(kat.begin(),kat.end());
    int dlugosc,male,duze,cyfr,znSP,pom;

    dlugosc=((v.at(1)-'0')*10)+(v.at(2)-'0');
    male=((v.at(4)-'0')*10)+(v.at(5)-'0');
    duze=((v.at(7)-'0')*10)+(v.at(8)-'0');
    cyfr=((v.at(10)-'0')*10)+(v.at(11)-'0');
    znSP=(v.at(13)-'0');
    srand(time(NULL));
    int kol;
    haslo="";
    while(dlugosc!=0){
        int kol= (std::rand()%4)+1;
        switch (kol) {
            case 1:
                if(male>0){
                    male--;
                    dlugosc--;
                    int los= (std::rand()%20)+0;
                    haslo+=(char)('a'+los);
                }
                break;
            case 2:
                if(duze>0){
                    duze--;
                    dlugosc--;
                    int los= (std::rand()%20)+0;
                    haslo+=(char)('A'+los);
                }
                break;
            case 3:
                if(cyfr>0){
                    cyfr--;
                    dlugosc--;
                    int los= (std::rand()%9)+0;
                    haslo+=(char)('0'+los);
                }
                break;
            case 4:

                int los;
                if (znSP>0){
                    bool l=false;
                    znSP--;
                    dlugosc--;

                    while (!l){
                        los= (std::rand()%97)+32;
                        if(los>32 && los<47){
                            l=true;
                        }else if (los>57 && los<65){
                            l=true;
                        }else if (los>90 && los < 97){
                            l=true;
                        }
                    }
                    haslo+=(char)(los);
                }
                break;
            default:
                std::cout << "blad generacji hasla" <<std::endl;

        }





    }




}

void genKat( std::string& pass, std::string& Kat){

    int il,duze=0,male=0,cyfr=0,znSp=0,i=0;
    bool stop=false;


    while (!stop) {
        std::vector<char> v(pass.begin(),pass.end());
        il=v.size();

        std::remove(v.begin(), v.end(),' ');


        for (int i = 0; i < v.size(); ++i) {
            if (v.at(i) >= 'A' && v.at(i) <= 'Z') {
                duze++;
            } else if (v.at(i) >= 'a' && v.at(i) <= 'z') {
                male++;
            } else if (v.at(i) >= '0' && v.at(i) <= '9') {
                cyfr++;
            } else {
                znSp++;
            }
        }

        if(znSp>9){
            std::cout << "wprowadzono za duzo znakow specjalnych. Wprowadz Haslo jeszcze raz" << std::endl;
            std::cin >> pass;
            v.clear();
        } else {
            stop =true;
        }
    }

    Kat="";
    Kat+(char)('0'+(int)(il/10))+(char)('0'+il%10);

    Kat='I',Kat+=(char)('0'+(int)(il/10)),Kat+=(char)('0'+il%10),
    Kat+='M',Kat+=(char)('0'+(int)(male/10)),Kat+=(char)('0'+male%10),
    Kat+='D',Kat+=(char)('0'+(int)(duze/10)),Kat+=(char)('0'+duze%10),
    Kat+='C',Kat+=(char)('0'+(int)(cyfr/10)),Kat+=(char)('0'+cyfr%10),
    Kat+='@',Kat+=(char)('0'+znSp);
}

template <typename T>
void addPass(){

    PassChain<T> *head = nullptr;
    PassChain<T> **current = &head;

    string
            patern1 = "Nazwa: ",
            patern2 = "Login: ",
            patern3 = "Haslo: ",
            patern4 = "Kat: ",
            patern5 = "Web: ",
            line, Nazwa, Login, Haslo, Kat, Web;

    int ch;
    bool stop=false;

    std::cout << "Podaj \"Nazwe\"" <<std::endl;
    std::cin >> Nazwa;
    std::cout << "Podaj \"Login\"" <<std::endl;
    std::cin >> Login;

    while (!stop) {
        std::cout << " Wybierz jedna z opcji: \n"
                     "1. Wpisac haslo recznie; \n"
                     "2. Wygenerowac haslo; " << std::endl;
        std::cin >> ch;

        switch (ch) {
            case 1:

                std::cout << "\"1. Wpisac haslo recznie; \"\n"
                             "Prosze wpisz haslo: \n" << std::endl;
                std::cin >> Haslo;
                std::cout << " Generuje Kategorie " << std::endl;
                genKat(Haslo,Kat);
                stop=true;
                break;
            case 2:
                std::cout << "\"2. Wygenerowac haslo; \"\n"
                             "Wybierz opcje:  \n"
                             "1. Wpisac kategorie do generacji;\n"
                             "2. Wpisac parametry generacji;\n"
                             "Uwaga! Wazne wpisanie tylko 1 dla opcji nr.1. w innym wypadku inicjalizuje sie opcje 2!\n" << std::endl;
                std::cin >> ch;
                switch (ch) {
                    case 1:
                        std::cout << "\"1. Wpisac kategorie do generacji;\"" << std::endl;
                        std::cout << "Podaj klucz generacji" << std::endl;
                        line="";
                        std::cin >> Kat;
                        genHaslo(Kat,Haslo);
                        stop=true;
                        break;
                    default:
                        bool stop2=false;
                        int dlugosc, male, duze, znSP,cyfr;
                        while(!stop2) {
                            std::cout << "\"2. Wpisac parametry generacji;\"\n"
                                         "Podaj dlugosc Hasla (1-26):" << std::endl;

                            std::cin >> dlugosc;
                            std::cout << "Podaj ilosc duzych znakow(0-" <<dlugosc<<"):" << std::endl;
                            std::cin >> duze;
                            if(dlugosc-duze>9){
                                znSP=9;
                            }else{
                                znSP=dlugosc-duze;
                            }
                            std::cout << "Podaj ilosc znakow specjalnych(0-"<< znSP << "):" << std::endl;
                            std::cin >> znSP;
                            std::cout << "Podaj ilosc cyfr (0-" << dlugosc-znSP-duze << "):" << std::endl;
                            std::cin >> cyfr;

                            if(dlugosc<1 || dlugosc >26){
                                std::cout << "wprowadzono bledna dlugosc\n"
                                             "1. Kontynuj aby wpisac ponownie; \n"
                                             "2. Powrot do menu glownego;"
                                             "Uwaga! bledne wprowadzenie opcji inicjalizuje opcje 1!;\n"<<std::endl;
                                std::cin >> ch;
                                if(ch==2){
                                    return;
                                }
                            } else if (duze<0 || duze>dlugosc){
                                std::cout << "wprowadzono bledna ilosc duzych liter\n"
                                             "1. Kontynuj aby wpisac ponownie; \n"
                                             "2. Powrot do menu glownego;"
                                             "Uwaga! bledne wprowadzenie opcji inicjalizuje opcje 1!;\n"<<std::endl;
                                std::cin >> ch;
                                if(ch==2){
                                    return;
                                }
                            }   else if (znSP<0 || znSP>9 || znSP>(dlugosc-duze) ){
                                std::cout << "wprowadzono bledna ilosc znakow specjalnych\n"
                                             "1. Kontynuj aby wpisac ponownie; \n"
                                             "2. Powrot do menu glownego;"
                                             "Uwaga! bledne wprowadzenie opcji inicjalizuje opcje 1!;\n"<<std::endl;
                                std::cin >> ch;
                                if(ch==2){
                                    return;
                                }

                            }  else if (cyfr<0 || cyfr>dlugosc-znSP-duze) {
                                std::cout << "wprowadzono bledna ilosc cyfr\n"
                                             "1. Kontynuj aby wpisac ponownie; \n"
                                             "2. Powrot do menu glownego;"
                                             "Uwaga! bledne wprowadzenie opcji inicjalizuje opcje 1!;\n"<<std::endl;
                                std::cin >> ch;
                                if(ch==2){
                                    return;
                                }
                            } else {
                                stop2=true;
                                stop= true;
                            }
                        }

                        Kat='I',Kat+=(char)('0'+(int)(dlugosc/10)),Kat+=(char)('0'+dlugosc%10),
                        Kat+='M',Kat+=(char)('0'+(int)((dlugosc-znSP-duze-cyfr)/10)),Kat+=(char)('0'+(dlugosc-znSP-duze-cyfr)%10),
                        Kat+='D',Kat+=(char)('0'+(int)(duze/10)),Kat+=(char)('0'+duze%10),
                        Kat+='C',Kat+=(char)('0'+(int)(cyfr/10)),Kat+=(char)('0'+cyfr%10),
                        Kat+='@',Kat+=(char)('0'+znSP);
                        genHaslo(Kat,Haslo);
                }
                break;
            default:
                std::cout << " Wpisano bledna cyfre. Czy wrocic do menu? \n"
                             "1. tak\n"
                             "2. nie\n"
                             "Uwaga przy blednym wprowadzniu opcji zostanie zainicjalizowany powrot do menu!\n"
                          << std::endl;
                std::cin >> ch;
                switch (ch) {
                    case 2:
                        break;
                    default:
                        return;
                }


        }
    }

    std::cout << "Podaj \"Web\"" <<std::endl;
    std::cin >> Web;


    *current = new PassChain<T>{Nazwa, Login, Haslo, Kat, Web, nullptr};
    current = &(*current)->next;

}

void menu(){

    std::string plikName;
    std::cout << "\n          Witam W Menedzerze hasel\n"
                 "Dany menedzer hasel zostal stworzony przez:\n"
                 "          Nazarij Feduniw s20893 \n"
              <<std::endl;
    std::cout << "Podaj nazwe pliku do odczytu" <<std::endl;
    std::cin >> plikName;

    bool open=false;
    while(!open){
        std::fstream file;
        file.open(plikName, std::ios::in);
        if(file.is_open()){
            open=true;
            file.close();
        }else{
            file.close();
            std::cout<<"blad wczytania pliku\n"
                       "wprowadz nazwe pliku ponownie"<<std::endl;
            std::cin >>plikName;
        }
    }
    int enCode;
    std:: cout << "Wprowadz Pin" << std::endl;
    std::cin >> enCode;
    std:: cout << std::endl;

    std::cout << "Otwieram plik: \"" << plikName << "\" \n" << std::endl;
    std::vector<char> vec;
    toVec(plikName,vec);
    decrypt(vec,enCode);
    PassChain<int>* head = toList<int>(vec);

    std::cout << "\n--Witaj w wewnetrznym menu.--\n" <<std::endl;

    bool stop=false;
    int choice;
    string Pom;

    while (!stop){
        std:: cout << " Wybierz numer do dzialania: \n"
                      "0. Zakoncz program;\n"
                      "1. Wyszukaj hasla;\n"
                      "2. Posortuj hasla;\n"
                      "3. Dodaj haslo;\n"
                      "4. Edytuj haslo;\n"
                      "5. Usun haslo;\n"
                      "6. Dodaj kategorie;\n"
                      "7. Usun kategorie;\n"
                      "8. Wyswietl wszystkie hasla;\n"
                   <<std::endl;
        std::cin >> choice;
        bool search=false;
        switch (choice) {
            case 0:
                std::cout << "\"0. Zakoncz program;\" \n"
                             "Do widzenia w przyszlosci :) \n" << std::endl;
//                std::vector<int> sizeV;
//                std::vector<char> vec,vvv;
//                fromList(head,vvv);
//                encrypt(vvv,enCode);
//                toPlik(plikName,vvv);
                stop= true;
                break;
            case 1:
                std::cout << "\"1. Wyszukaj hasla;\" \n" << std::endl;

                std::cout << " Za jakimi parametrami chcesz wyszukiwac? \n"
                             "1. Nazwa; \n"
                             "2. Login; \n"
                             "3. Haslo; \n"
                             "4. Kategoria; \n"
                             "5. Strona WWW/Serwis; \n"
                             "0. Cofnij;" << std::endl;
                std::cout << std::endl;
                std::cin >> choice;
                switch (choice) {
                    case 1:
                        std::cout<< "\"1. Nazwa;\" \n" <<std::endl;
                        std::cout<< "Podaj DOKLADNA nazwe do wyszukiwania" << std::endl;
                        std::cin >> Pom;
                        wyszukaj(head,choice,Pom);
                        break;
                    case 2:
                        std::cout<< "\"2. Login;\" \n" <<std::endl;
                        std::cout<< "Podaj DOKLADNY Login do wyszukiwania" << std::endl;
                        std::cin >> Pom;
                        wyszukaj(head,choice,Pom);
                        break;
                    case 3:
                        std::cout<< "\"3. Haslo;\" \n" <<std::endl;
                        std::cout<< "Podaj Haslo do wyszukiwania" << std::endl;
                        std::cin >> Pom;
                        wyszukaj(head,choice,Pom);
                        break;
                    case 4:
                        std::cout<< "\"4. Kategoria;\" \n" <<std::endl;
                        std::cout<< "Podaj Kategorie do wyszukiwania" << std::endl;
                        std::cin >> Pom;
                        wyszukaj(head,choice,Pom);
                        break;
                    case 5:
                        std::cout<< "\"5. Strona WWW/Serwis;\" \n"<<std::endl;
                        std::cout<< "Podaj strone do wyszukiwania" << std::endl;
                        std::cin >> Pom;
                        wyszukaj(head,choice,Pom);
                        break;
                    case 0:
                        std::cout<< "\"0. Cofnij;\" \n" <<std::endl;
                        break;
                    default:
                        std::cout<< "wybrano bledny parametr wracam na poczatek\n " <<std::endl;

                }
                break;
            case 2:
                std::cout << "\"2. Posortuj hasla;\" \n" << std::endl;
                break;
            case 3:
                std::cout << "\"3. Dodaj haslo;\" \n" << std::endl;
                addPass<string>();
                break;
            case 4:
                std::cout << "\"4. Edytuj haslo;\" \n" << std::endl;
                break;
            case 5:
                std::cout << "\"5. Usun haslo;\" \n" << std::endl;
                break;
            case 6:
                std::cout << "\"6. Dodaj kategorię;\" \n" << std::endl;
                break;
            case 7:
                std::cout << "\"7. Usun kategorie.\" \n" << std::endl;
                break;
            case 8:
                std::cout << "\"8. Wyswietl wszystkie hasla;\\n\"" << std::endl;
                showList(head);
                break;
            default:
                std::cout << "Wybrano niepoprawne dzialanie lub wpisano blednie numer.\n"
                             "Sprobuj ponownie. \n"
                          <<std::endl;
        }
    }


}


void pomEn(){
    string Plik ="t.txt",tekst;
    int code=5;
    std::vector<char> vec;

    toVec(Plik,vec);
    encrypt(vec,code);

//    toPlik(Plik,vec);
}
void pomPom(){
    string Plik ="t.txt",tekst;
    int code=5;

    std::vector<int> sizeV;
    std::vector<char> vec,vvv;


    toVec(Plik,vec);
    decrypt(vec,code);
    PassChain<int>* head = toList<int>(vec);
    showList(head);
    string tt="Microsoft";
    std::vector<char> v(tt.begin(),tt.end());
//    remPass(&head,tt);
    fromList(head,vvv);
    encrypt(vvv,code);
    toPlik(Plik,vvv);
}
//void a(){
//    string Plik ="t.txt",tekst;
//    int code=5;
//
//    std::vector<int> sizeV;
//    std::vector<char> vec,vvv;
//
//
//    toVec(Plik,vec);
//    decrypt(vec,code);
//    PassChain<int>* head = toList<int>(vec);
//    wyszukaj(head,1,"Warframe");
//}

int main() {


//    pomPom();
    menu();

    return 0;
}


