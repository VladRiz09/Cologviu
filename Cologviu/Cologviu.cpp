#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;

class Flow {
public:
    
    template <typename T>
    class TITLE {
    public:
        T titlu;
        T subtitlu;

        TITLE() {}
        TITLE(T titlu, T subtitlu) : titlu(titlu), subtitlu(subtitlu) {}
    };

    
    template <typename T>
    class TITLEDecorator {
    protected:
        TITLE<T>* titleComponent;

    public:
        TITLEDecorator(TITLE<T>* titleComponent) : titleComponent(titleComponent) {}

        virtual T getTitlu() {
            return titleComponent->titlu;
        }

        virtual T getSubtitlu() {
            return titleComponent->subtitlu;
        }
    };

    
    template <typename T>
    class BasicTITLEDecorator : public TITLEDecorator<T> {
    public:
        BasicTITLEDecorator(TITLE<T>* titleComponent) : TITLEDecorator<T>(titleComponent) {}

        T getTitlu() override {
            return TITLEDecorator<T>::getTitlu();
        }

        T getSubtitlu() override {
            return TITLEDecorator<T>::getSubtitlu();
        }
    };



    class TEXT {
    public:
        string titlu;
        string copie;

        TEXT() {}
        TEXT(string& titlu, string& copie) {
            this->titlu = titlu;
            this->copie = copie;
        }
    };

    class TEXT_INPUT {
    public:
        string descriere;
        string intrare;

        TEXT_INPUT() {}
        TEXT_INPUT(string& descriere, string& intrare) {
            this->descriere = descriere;
            this->intrare = intrare;
        }
    };

    class NUMBER_INPUT {
    public:
        string descriere;
        float intrare;

        NUMBER_INPUT() {}
        NUMBER_INPUT(string& descriere, float& intrare) {
            this->descriere = descriere;
            this->intrare = intrare;
        }
    };

    class CALCULUS {
    public:
        int* pasi;
        char operatie;

        CALCULUS() {}
        CALCULUS(int pasi[], char& operatie) {
            this->pasi = pasi;
            this->operatie = operatie;
        }
    };

    class DISPLAY {
    public:
        int pas;

        DISPLAY() {}
        DISPLAY(int& pas) {
            this->pas = pas;
        }
    };

    class TEXT_FILE_INPUT {
    public:
        string descriere;
        string nume_fisier;

        TEXT_FILE_INPUT() {}
        TEXT_FILE_INPUT(string& descriere, string& nume_fisier) {
            this->descriere = descriere;
            this->nume_fisier = nume_fisier;
        }
    };

    class CSV_FILE_INPUT {
    public:
        string descriere;
        string nume_fisier;

        CSV_FILE_INPUT() {}
        CSV_FILE_INPUT(string& descriere, string& nume_fisier) {
            this->descriere = descriere;
            this->nume_fisier = nume_fisier;
        }
    };

    class OUTPUT {
    public:
        int pas;
        string nume_fisier;
        string titlu;
        string descriere;

        OUTPUT() {}
        OUTPUT(int& pas, string& nume_fisier, string& titlu, string& descriere) {
            this->pas = pas;
            this->nume_fisier = nume_fisier;
            this->titlu = titlu;
            this->descriere = descriere;
        }
    };

public:
    static struct Flux {
        TITLE<string>* title;
        TEXT* text;
        TEXT_INPUT* text_input;
        NUMBER_INPUT* number_input;
        CALCULUS* calculus;
        DISPLAY* display;
        TEXT_FILE_INPUT* text_file_input;
        CSV_FILE_INPUT* csv_file_input;
        OUTPUT* output;
    };

    vector<Flux>* flows;

public:
    Flow() {
        cout << "[Flow/Constructor] - Obiect creat.\n";
        flows = new vector<Flux>();
    }

    ~Flow() {
        cout << "[Flow/Destructor] - Obiect distrus.\n";
        ClearFlows();
        delete flows;
    }

public:
    void ClearFlows() {
        flows->clear();
        flows = nullptr;
    }

    bool LoadFlows() {
        fstream fin("saved_flows.txt", ios::in);

        if (!fin.is_open())
            return false;

        string linie;
        while (!fin.eof()) {
            getline(fin, linie);

            if (linie.find("{") != string::npos) {
                Flux* temp_flux = new Flux();
                while (linie.find("}") == string::npos) {
                    getline(fin, linie);
                    // Pentru o performanta mai buna se anuleaza while ul si se restructureaza if-urile sa fie fara else.
                    if (linie.find("TITLE") != string::npos) {
                        temp_flux->title = new Flow::TITLE<string>();   
                        getline(fin, linie);
                        temp_flux->title->titlu = linie;    
                        getline(fin, linie);
                        temp_flux->title->subtitlu = linie;  
                    }
                    else if (linie.find("TEXT") != string::npos) {
                        temp_flux->text = new TEXT();
                        getline(fin, linie);
                        temp_flux->text->titlu = linie;
                        getline(fin, linie);
                        temp_flux->text->copie = linie;
                    }
                    else if (linie.find("TEXT_INPUT") != string::npos) {
                        temp_flux->text_input = new TEXT_INPUT();
                        getline(fin, linie);
                        temp_flux->text_input->descriere = linie;
                        getline(fin, linie);
                        temp_flux->text_input->intrare = linie;
                    }
                    else if (linie.find("NUMBER_INPUT") != string::npos) {
                        temp_flux->number_input = new NUMBER_INPUT();
                        getline(fin, linie);
                        temp_flux->number_input->descriere = linie;
                        getline(fin, linie);
                        temp_flux->number_input->intrare = stof(linie);
                    }
                    else if (linie.find("CALCULUS") != string::npos) {
                        temp_flux->calculus = new CALCULUS();
                        getline(fin, linie);
                        int pasi[2];
                        int q = 0;
                        char s[51] = { 0 };
                        strcpy(s, linie.c_str());
                        char* p = strtok(s, " ");
                        while (p != NULL) {
                            pasi[q++] = atoi(p);
                            p = strtok(NULL, " ");
                        }
                        temp_flux->calculus->pasi = pasi;
                        getline(fin, linie);
                        temp_flux->calculus->operatie = linie[0];
                    }
                    else if (linie.find("DISPLAY") != string::npos) {
                        temp_flux->display = new DISPLAY();
                        getline(fin, linie);
                        temp_flux->display->pas = atoi(linie.c_str());
                    }
                    else if (linie.find("TEXT_FILE_INPUT") != string::npos) {
                        temp_flux->text_file_input = new TEXT_FILE_INPUT();
                        getline(fin, linie);
                        temp_flux->text_file_input->descriere = linie;
                        getline(fin, linie);
                        temp_flux->text_file_input->nume_fisier = linie;
                    }
                    else if (linie.find("CSV_FILE_INPUT") != string::npos) {
                        temp_flux->csv_file_input = new CSV_FILE_INPUT();
                        getline(fin, linie);
                        temp_flux->csv_file_input->descriere = linie;
                        getline(fin, linie);
                        temp_flux->csv_file_input->nume_fisier = linie;
                    }
                    else if (linie.find("OUTPUT") != string::npos) {
                        temp_flux->output = new OUTPUT();
                        getline(fin, linie);
                        temp_flux->output->pas = atoi(linie.c_str());
                        getline(fin, linie);
                        temp_flux->output->nume_fisier = linie;
                        getline(fin, linie);
                        temp_flux->output->titlu = linie;
                        getline(fin, linie);
                        temp_flux->output->descriere = linie;
                    }
                }
                // Add the parsed flow to the flows list.
                flows->push_back(*temp_flux);
                delete temp_flux;
            }
        }

        return true;
    }

    bool AddFlow(Flux& flux) {
        if (flows == nullptr)
            throw exception("Empty flow array.");

        // Adaugare flux.

        string choice;
        string titlu;
        string sub_titlu;

        ofstream fout("saved_flows.txt", ios::app);
        fout << endl;
        fout << "{" << endl;
        cout << "Alegeni numele pentru acest flow:" << endl;
        string nume_flow;
        cin >> nume_flow;
        fout << nume_flow << endl;

        char alegere = 0;
        do {
            if (alegere != 0) cout << "Poti alege doar Da(D) sau Nu(N). Incearca din nou.\n";

            cout << "Doriti sa adaugati un TITLU?(DA(D)/NU(N): ";
            cin >> alegere;
            alegere = toupper(alegere);
        } while (alegere != 'D' && alegere != 'N');

        alegere = toupper(alegere);
        if (alegere == 'D') {
            cout << "Alegeti titlu:" << endl;
            fout << "TITLU" << endl;
            cin >> titlu;
            fout << titlu << endl;
            cout << "Alegeti sub titlu" << endl;
            cin >> sub_titlu;
            fout << sub_titlu << endl;
            fout << endl;
        }

        alegere = 0;
        string titluText;
        string sub_titluText;
        do {
            if (alegere != 0) cout << "Poti alege doar Da(D) sau Nu(N). Incearca din nou.\n";

            cout << "Doriti sa adaugati un TEXT?(DA(D)/NU(N): ";
            cin >> alegere;
            alegere = toupper(alegere);
        } while (alegere != 'D' && alegere != 'N');
        if (alegere == 'D') {
            cout << "Alegeti titlul TEXT:" << endl;
            fout << "TEXT" << endl;
            cin >> titluText;
            fout << titluText << endl;
            cout << "Alegeti sub titluText" << endl;
            cin >> sub_titluText;
            fout << sub_titluText << endl;
            fout << endl;
        }

        string descriere;
        string text_imput;
        alegere = 0;
        do {
            if (alegere != 0) cout << "Poti alege doar Da(D) sau Nu(N). Incearca din nou.\n";

            cout << "Doriti sa adaugati un TEXT_IMPUT?(DA(D)/NU(N): ";
            cin >> alegere;
            alegere = toupper(alegere);
        } while (alegere != 'D' && alegere != 'N');

        if (alegere == 'D') {
            cout << "Alegeti descrierea:" << endl;
            fout << "TEXT_IMPUT" << endl;
            cin >> descriere;
            fout << descriere << endl;
            cout << "Alegeti text_imput" << endl;
            cin >> text_imput;
            fout << text_imput << endl;
            fout << endl;
        }

        descriere = '\0';
        float number;
        alegere = 0;
        do {
            if (alegere != 0) cout << "Poti alege doar Da(D) sau Nu(N). Incearca din nou.\n";

            cout << "Doriti sa adaugati un NUMBER_INPUT?(DA(D)/NU(N): ";
            cin >> alegere;
            alegere = toupper(alegere);
        } while (alegere != 'D' && alegere != 'N');

        if (alegere == 'D') {
            cout << "Alegeti descrierea:" << endl;
            fout << "NUMBER_INPUT" << endl;
            cin >> descriere;
            fout << descriere << endl;
            cout << "Cate numere doriti sa introduceti?:";
            int nr;
            cin >> nr;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Valoare invalida. Introduceti un numar de tip float: ";
                cin >> nr;
            }
            int k = 0;
            while (nr > k) {
                cout << "Alegeti numararul" << k + 1 << " (te tip float) : " << endl;
                cin >> number;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Valoare invalida. Introduceti un numar de tip float: ";
                    cin >> number;
                }
                fout << number << " ";
                k = k + 1;
            }
            fout << endl;
        }

        int steps;
        string operasion;

        alegere = 0;
        do {
            if (alegere != 0) cout << "Poti alege doar Da(D) sau Nu(N). Incearca din nou.\n";

            cout << "Doriti sa adaugati un CALCULUS?(DA(D)/NU(N): ";
            cin >> alegere;
            alegere = toupper(alegere);
        } while (alegere != 'D' && alegere != 'N');

        if (alegere == 'D') {
            cout << "Alegeti numarul de stepsuri " << endl;
            int n;
            int p = 0;
            cin >> n;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Valoare invalida. Introduceti un numar: ";
                cin >> n;
            }
            fout << "CALCULUS" << endl;
            while (n > p)
            {
                cout << "Alegeti pasul :" << p + 1 << endl;
                cin >> steps;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Valoare invalida. Introduceti din nou pasul: ";
                    cin >> steps;
                }
                fout << steps << " ";
                p++;
            }
            fout << endl;

            int k = 0;
            while (k != 1) {
                cout << "Alegeti tipul de operatie( - , + , % , * , min , max)" << endl;
                cin >> operasion;
                if (operasion == "-" || operasion == "+" || operasion == "%" || operasion == "*" || operasion == "min" || operasion == "max")
                {
                    k++;
                    fout << operasion << endl;
                }
                else {
                    cout << "Nu ati ales o operatie corespunzatoare" << endl;
                }
            }
            fout << endl;
        }

        int step = 0;
        alegere = 0;
        do {
            if (alegere != 0) cout << "Poti alege doar Da(D) sau Nu(N). Incearca din nou.\n";

            cout << "Doriti sa adaugati un DISPLAY?(DA(D)/NU(N): ";
            cin >> alegere;
            alegere = toupper(alegere);
        } while (alegere != 'D' && alegere != 'N');


        if (alegere == 'D') {
            cout << "Alegeti step-ul :" << endl;
            fout << "DISPLAY" << endl;
            cin >> step;

            while (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Valoare invalida. Introduceti din nou pasul: ";
                cin >> steps;
            }
            fout << step << endl;
        }

        alegere = 0;
        descriere = '\0';
        string file_name;
        do {
            if (alegere != 0) cout << "Poti alege doar Da(D) sau Nu(N). Incearca din nou.\n";

            cout << "Doriti sa adaugati un TEXT_FILE_INPUT?(DA(D)/NU(N): ";
            cin >> alegere;
            alegere = toupper(alegere);
        } while (alegere != 'D' && alegere != 'N');


        if (alegere == 'D') {
            cout << "Alegeti descrierea:" << endl;
            fout << "TEXT_FILE_INPUT" << endl;
            cin >> descriere;
            fout << descriere << endl;
            cout << "Alegeti numele fsierului TEXT" << endl;
            cin >> file_name;
            fout << file_name << endl;
            fout << endl;
        }

        alegere = 0;
        descriere = '\0';
        file_name = '\0';
        do {
            if (alegere != 0) cout << "Poti alege doar Da(D) sau Nu(N). Incearca din nou.\n";

            cout << "Doriti sa adaugati un CSV_FILE_INPUT?(DA(D)/NU(N): ";
            cin >> alegere;
            alegere = toupper(alegere);
        } while (alegere != 'D' && alegere != 'N');

        if (alegere == 'D') {
            cout << "Alegeti descrierea:" << endl;
            fout << "CSV_FILE_INPUT" << endl;
            cin >> descriere;
            fout << descriere << endl;
            cout << "Alegeti numele fsierului CSV" << endl;
            cin >> file_name;
            fout << file_name << endl;
            fout << endl;
        }

        alegere = 0;
        descriere = '\0';
        file_name = '\0';
        titlu = '\0';
        step = 0;
        do {
            if (alegere != 0) cout << "Poti alege doar Da(D) sau Nu(N). Incearca din nou.\n";

            cout << "Doriti sa adaugati un OUTPUT?(DA(D)/NU(N): ";
            cin >> alegere;
            alegere = toupper(alegere);
        } while (alegere != 'D' && alegere != 'N');

        if (alegere == 'D') {
            cout << "Alegeti STEP-ul" << endl;
            fout << " OUTPUT" << endl;
            cin >> step;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Valoare invalida. Introduceti din nou pasul ";
                cin >> step;
            }
            fout << step << endl;
            cout << "Alegeti numele fsierului pentru Output" << endl;
            cin >> file_name;
            fout << file_name << endl;
            cout << "Alegeti Titlu" << endl;
            cin >> titlu;
            fout << titlu << endl;
            cout << "Alegeti descrierea" << endl;
            cin >> descriere;
            fout << descriere << endl;
            fout << endl;
        }

        alegere = 0;
        do {
            if (alegere != 0) cout << "Poti alege doar Da(D) sau Nu(N). Incearca din nou.\n";

            cout << "Doriti sa adaugati un END?(DA(D)/NU(N): ";
            cin >> alegere;
            alegere = toupper(alegere);
        } while (alegere != 'D' && alegere != 'N');

        if (alegere == 'D') {
            cout << "END-ul a fost adaugat" << endl;
            fout << " END" << endl;
        }
        // Se curata buffer-ul cand se trece de la int | char | float la compuse (string).
        cin.get();
        cin.clear();

        auto now = chrono::system_clock::now();
        time_t time_now = chrono::system_clock::to_time_t(now);
        fout << ctime(&time_now) << endl;

        fout << "Flow-ul a fost accesat de : 0 ori" << endl;
        fout << "Flow-ul a fost rulat de : 0 ori" << endl;
        fout << "}" << endl;
        fout << endl;
        fout.close();
    }

    bool DeleteFlow(int& index) {


        ifstream fin("saved_flows.txt");
        if (!fin) {
            throw runtime_error("Failed to open file.");
        }
        cout << "Alegeti indexul flowului pe care doriti sa il stergeti:" << endl;
        cin >> index;
        if (index < 0 || index > flows->size())
            throw out_of_range("Index is out of bounds.");

        vector<string> lines;
        string line;
        int braceCount = 0;
        bool isDeleting = false;
        vector<string> updatedLines;

        while (getline(fin, line)) {
            if (line.find('{') != string::npos) {
                braceCount++;
                if (braceCount == index) {
                    isDeleting = true;
                    continue;
                }
            }

            if (!isDeleting) {
                updatedLines.push_back(line);
            }

            if (line.find('}') != string::npos && isDeleting) {
                isDeleting = false;
            }
        }
        fin.close();

        ofstream fout("saved_flows.txt");
        if (!fout) {
            throw runtime_error("Failed to open file for writing.");
        }

        for (const auto& l : updatedLines) {
            fout << l << endl;
        }
        fout.close();

        return true;
    }

    void FlowDetails(int& index) {
        if (flows == nullptr)
            throw runtime_error("Empty flow array.");

        if (index < 0 || index > flows->size())
            throw out_of_range("Index is out of bounds.");

        ifstream fin("saved_flows.txt");
        if (!fin) {
            throw runtime_error("Failed to open file.");
        }

        cout << "Alegeti flow-ul dorit in functie de index pentru a fi prezentat:" << endl;
        cin >> index;

        vector<string> lines;
        string line;
        while (getline(fin, line)) {
            lines.push_back(line);
        }
        fin.close();

        int braceCount = 0;
        bool isInsideTargetBlock = false;
        for (size_t i = 0; i < lines.size(); ++i) {
            if (lines[i].find('{') != string::npos) {
                braceCount++;
                if (braceCount == index) {
                    isInsideTargetBlock = true;
                }
            }

            if (isInsideTargetBlock) {
                // Afișează liniile din blocul dorit
                cout << lines[i] << endl;

                if (lines[i].find("Flow-ul a fost accesat de :") != string::npos) {
                    size_t pos = lines[i].find(":") + 1;
                    int accessCount = stoi(lines[i].substr(pos)) + 1;
                    lines[i] = "Flow-ul a fost accesat de :" + to_string(accessCount) + " ori";
                }

                if (lines[i].find('}') != string::npos) {
                    isInsideTargetBlock = false;
                }
            }
        }

        ofstream fout("saved_flows.txt");
        if (!fout) {
            throw runtime_error("Failed to open file for writing.");
        }

        for (const auto& ln : lines) {
            fout << ln << endl;
        }
        fout.close();
    }


    void runCalculus(string& nume_flow) {
        ifstream fin("saved_flows.txt");
        if (!fin) {
            throw runtime_error("Failed to open file.");
        }

        float min = numeric_limits<float>::max();
        float max = numeric_limits<float>::lowest();

        string line;
        vector<string> lines;
        vector<double> numbers;
        char operation;
        bool found = false;

        while (getline(fin, line)) {
            lines.push_back(line);

            if (line.find(nume_flow) != string::npos) {
                found = true;
            }

            if (found) {
                if (line.find("NUMBER_INPUT") != string::npos) {

                    getline(fin, line);
                    getline(fin, line);

                    stringstream ss(line);
                    double num;
                    while (ss >> num) {
                        numbers.push_back(num);
                    }
                }
                else if (line.find("CALCULUS") != string::npos) {
                    getline(fin, line);
                    getline(fin, line);

                    stringstream ss(line);
                    ss >> operation;
                    if (numbers.empty()) {
                        throw runtime_error("No numbers provided for calculation.");
                    }

                    double result = 0;
                    if (operation == 'min') {
                        result = *min_element(numbers.begin(), numbers.end());
                    }
                    else if (operation == 'max') {
                        result = *max_element(numbers.begin(), numbers.end());
                    }
                    else {
                        result = numbers[0];
                        for (size_t i = 1; i < numbers.size(); ++i) {
                            switch (operation) {
                            case '+': result += numbers[i]; break;
                            case '-': result -= numbers[i]; break;
                            case '*': result *= numbers[i]; break;
                            case '/': if (numbers[i] != 0) result /= numbers[i];break;
                            default: throw invalid_argument("Operatie necunoscuta.");
                            }
                        }
                    }

                    cout << "Rezultatul calculului: " << result << endl;
                    break;
                }
            }
        }

        fin.close();
       
        for (size_t i = 0; i < lines.size(); ++i) {
            if (lines[i].find("Flow-ul a fost rulat de :") != string::npos && lines[i].find(nume_flow) != string::npos) {
                size_t pos = lines[i].find(":") + 1;
                int runCount = stoi(lines[i].substr(pos)) + 1;
                lines[i] = "Flow-ul a fost rulat de :" + to_string(runCount) + " ori";
                break;
            }
        }

        // Rescrierea conținutului în fișier
        ofstream fout("saved_flows.txt");
        if (!fout) {
            throw runtime_error("Failed to open file for writing.");
        }

        for (const auto& ln : lines) {
            fout << ln << endl;
        }
        fout.close();
    }


    void generateOutput(string& nume_flow) {
        ifstream fin("saved_flows.txt");
        if (!fin) {
            throw runtime_error("Failed to open file.");
        }

        string line, content, outputFileName;
        bool found = false, insideBlock = false, outputFound = false;

        while (getline(fin, line)) {
            if (line.find(nume_flow) != string::npos) {
                found = true;
                insideBlock = true; // Începe să rețină conținutul
            }

            if (found && insideBlock) {
                content += line + "\n";
                if (line.find("OUTPUT") != string::npos) {
                    outputFound = true;
                    getline(fin, line); // Sari peste descriere
                    getline(fin, line); // Numele fișierului de output
                    outputFileName = line;
                }

                if (line.find("}") != string::npos) {
                    insideBlock = false; // Sfârșește blocul
                    break;
                }
            }
        }

        fin.close();

        if (found && !outputFound) {
            cout << "Numele flow-ului '" << nume_flow << "' a fost gasit dar nu are sectiunea 'OUTPUT'.\nIntroduceti un nume pentru fisierul de output: ";
            cin >> outputFileName;
        }

        if (!found) {
            throw runtime_error("Numele flow-ului '" + nume_flow + "' nu a fost gasit.");
        }

        ofstream fout(outputFileName);
        if (!fout) {
            throw runtime_error("Failed to create output file.");
        }

        fout << content;
        fout.close();

        cout << "Fisierul '" << outputFileName << "' a fost creat cu succes." << endl;
    }
    void analytics(string& nume_flow) {

    }
};


class Program {
private:
    Flow* flux;

public:
    Program() {
        cout << "[Program/Constructor] - Obiect creat.\n";
        flux = new Flow();
    }

    ~Program() {
        cout << "[Program/Destructor] - Obiect distrus.\n";
        delete flux;
    }

public:
    void Run() {
        char alegere = 0;
        do {
            if (alegere != 0) cout << "Poti alege doar Da(D) sau Nu(N). Incearca din nou.\n";

            cout << "Doresti sa incarci fluxurile anterioare? (D/N): ";
            cin >> alegere;
            alegere = toupper(alegere);
        } while (alegere != 'D' && alegere != 'N');

        if (alegere == 'D') {
            if (flux->LoadFlows())
                cout << "Fluxurile au fost incarcate cu succes. Pentru a vizualiza lista fluxurilor, folositi comanda: <show_flows>\n\n";
            else throw exception("Fluxurile nu au putut fi incarcate.");

            cin.get();
            cin.clear();
            string choice;
            while (true) {
                cout << "# Meniu central #\n>> Lista comenzilor <<\n";
                cout << "1 - <add_flow>\t Adauga flux in lista.\n";
                cout << "2 - <del_flow> [index]\t Sterge flux de la indexul respectiv din lista.\n";
                cout << "3 - <flows_count>\t Numarul total al fluxurilor existente in lista.\n";
                cout << "4 - <flow_details> [index]\t Detaliile fluxului de la indexul respectiv din lista.\n";
                // un nou meniu pentru a utiliza flow-urile in funtie de nume;(P.S adauga si nume la Flow)
                cout << "5 - <flow_uses>\t Utilizeaza un flow.\n";
                cout << "6 - <exit>\t Inchide programul.\n";

                cout << "> ";
                getline(cin, choice);

                if ("1" == choice || "add_flow" == choice) {

                    Flow::Flux* flux = new Flow::Flux();
                    this->flux->AddFlow(*flux);
                    delete flux;
                }
                else if ('2' == choice[0] || choice.find("del_flow") != string::npos) {
                    choice = choice.erase(0, choice.find_first_of(" ") + 1);
                    int index = atoi(choice.c_str());

                    try {
                        flux->DeleteFlow(index);
                    }
                    catch (exception& any) {
                        cerr << "A intervenit o problema la stergea fluxului: " << any.what() << '\n';
                    }
                }
                else if ("3" == choice || "flows_count" == choice) {
                    cout << "In lista sunt in total " << flux->flows->size() << " fluxuri.\n\n";
                }
                else if ('4' == choice[0] || "flow_details" == choice) {
                    choice = choice.erase(0, choice.find_first_of(" ") + 1);
                    int index = atoi(choice.c_str());

                    try {
                        cout << index << endl;
                        flux->FlowDetails(index);
                    }
                    catch (exception& any) {
                        cerr << "A intervenit o problema la afisarea detaliilor fluxului: " << any.what() << '\n';
                    }
                }
                else if ("5" == choice || "flow_uses" == choice)
                {
                    string nume_flow;
                    cout << "Va rugam sa alegeti numele flow-ului pe care doriti sa il folositi:\n";
                    cin >> nume_flow;
                    bool found = false;

                    string line;
                    ifstream fin("saved_flows.txt");
                    do {
                        // Initial, propunem ca nu e gasit si reluam cautarea fisierului de la inceputul acestuia.
                        found = false;
                        fin.clear();
                        fin.seekg(0);
                        while (!fin.eof()) {
                            getline(fin, line);
                            if (line.find(nume_flow) != string::npos) {
                                found = true;
                                break;
                            }
                        }

                        if (found == false) {
                            cout << "Flow-ul cu numele " << nume_flow << " nu a fost gasit! Reincercati: ";
                            cin >> nume_flow;
                        }
                    } while (found == false);

                    // Daca numele flow-ului a fost gasit, se va prelucra acesta prin metodele de mai jos.
                    while (true) {

                        cout << "# Meniu pentru folosirea unui flow #\n>> Lista comenzilor <<\n";
                        cout << "1 - <CALCULUS_RESULT>\t Rezultatul calculelor\n";
                        cout << "2 - <GENERATE OUTPUT> \t Generarea unui fisier text pentru Rezultat\n";
                        cout << "3 - <Analytics>\t Numarul total al fluxurilor existente in lista.\n";
                        cout << "4 - <exit>\t Inchide programul.\n";

                        cout << "> ";
                        cin >> choice;

                        if ("1" == choice || "CALCULUS_RESULT" == choice) {
                            try {
                                flux->runCalculus(nume_flow);
                            }
                            catch (exception& any) {
                                cerr << "A intervenit o problema la rularea CALCULUS: " << any.what() << '\n';
                            }
                        }
                        if ("2" == choice || "GENERATE OUTPUT" == choice) {
                            try {
                                flux->generateOutput(nume_flow);
                            }
                            catch (exception& any) {
                                cerr << "A intervenit o problema la rularea GENERATE OUTPUT: " << any.what() << '\n';
                            }
                        }
                        if ("3" == choice || "Analytics" == choice) {
                            try {
                                flux->analytics(nume_flow);
                            }
                            catch (exception& any) {
                                cerr << "A intervenit o problema la rularea Analytics: " << any.what() << '\n';
                            }
                        }

                        else if ("4" == choice || "exit" == choice) {
                            // Quit the app.
                            break;
                        }
                    }

                }
                else if ("6" == choice || "exit" == choice) {
                    // Quit the app.
                    return;
                }
                choice.clear();
            }
        }
        else {
            return;
        }
    }
};

int main()
{
    Program* h_programEntry = new Program();
    try {
        h_programEntry->Run();
    }
    catch (exception& any) {
        cerr << "A intervenit o problema: " << any.what() << '\n';
    }
    delete h_programEntry;

    return 0;
}