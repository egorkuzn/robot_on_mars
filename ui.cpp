#include "ui.h"

namespace graphics{
    void UI::genDisplayedMatrix(){
        setlocale(LC_CTYPE, "");
        displayedMatrix.resize(high);
        int counter = 0;
        for(std::string& elem : displayedMatrix){
            for(int i = 0; i < width; ++i)
                if((i == 12) && (counter == 3))
                    elem += "🤖";
                else
                    elem += "🟥";
            ++counter;
        }        
    }

    void UI::refreshW(){
        int counter = 0;
        ++x;
        ++y;
        for(std::string& elem : displayedMatrix){
            elem = "";            
            for(int i = 0; i < width; ++i)
                if((i == 25 - x  % 25) && (counter == y % 7))
                    elem += "🤖";
                else
                    elem += "🟥";
            ++counter;
        }        
    }

    void UI::display(){
        refreshW();
        system("clear");
        for(std::string& elem : displayedMatrix)
            std::cout << elem << std::endl;
        std::cout << liveStr << std::endl;
    }

    UI::UI(){
        system("clear");
        genDisplayedMatrix();
        display();
    }

    UI::~UI(){
        system("clear");
    }

    UI::operator bool() const{
        return status;
    }

    void UI::clearLiveStr(){
        liveStr = "";
    }

    Keys UI::reactionOnKeyboard(int ch){
        switch(ch){
            case 'a':
                return Keys::A;
            case 's':
                return Keys::S;
            case 'd':
                return Keys::D;
            case 'q':
                return Keys::Q;
            case 'e':
                return Keys::E;
            case 'f':
                return Keys::F;
            case 'u':
                return Keys::U;
            case 27:
                return Keys::Esc;
            default:
                return Keys::EMPTY;
        }
    }

    int _kbhit() {
        static const int STDIN = 0;
        static bool initialized = false;

        int bytesWaiting;

        if (! initialized) {
            // Use termios to turn off line buffering
            termios term;
            tcgetattr(STDIN, &term);
            term.c_lflag &= ~ICANON;
            tcsetattr(STDIN, TCSANOW, &term);
            setbuf(stdin, NULL);
            initialized = true;
        }

        //int bytesWaiting;
        ioctl(STDIN, FIONREAD, &bytesWaiting);
        return bytesWaiting;
    }

    Keys UI::getKey(){  
        int ch = 0;
        if(_kbhit())   /// If keyboard hit
        {
            ch = safety_input::getch(); /// Character
            return reactionOnKeyboard(ch);
        }

        return Keys::EMPTY;
     }

    bool UI::isChanged(){
        return true;
    }

    void UI::sleepcp(int milliseconds) // Cross-platform sleep function
    {
        clock_t time_end;
        time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
        while (clock() < time_end)
        {
        }
    }


    void UI::error(char* context){
        status = false;
        while(!_kbhit()){
            system("clear");
            std::cout << "ERROR: " << context << ". PRESS ANY KEY" << std::endl;
            sleepcp(500);
            system("clear");
            std::cout << "error: " << context << ". press any key" << std::endl;
            sleepcp(500);
        }
    }

    std::string UI::readCmd(char* context){
        system("clear");
        std::cout << context << ": " ;
        std::string cmd;
        std::cin >> cmd;
        display();
        return cmd;
    }

    int UI::getNum(char* context){
        system("clear");
        std::cout << context << ": ";
        int num;
        std::cin >> num;
        display();
        return num;
    }

    void UI::backDel(std::string& str){
        for(uint8_t i = 0; i < 5; ++i)
            str.push_back();
    }

    void UI::frontDel(std::string& str){
        
    }

    void UI::moveMapDown(){
        for(uint8_t i = 0; i < high - 1; ++i)
            displayedMatrix[i] = displayedMatrix[i + 1];        

        displayedMatrix[high - 1] = "";

        for(uint8_t i = 0; i < width; ++i){
            if(matrixMask[(y + high) % maxY][(x + i) % maxX])
                displayedMatrix[high - 1] += externMatrix[(y + high) % maxY][(x + i) % maxX];
            else 
                displayedMatrix[high - 1] += "🟥"; 
        }
    }

    void UI::moveMapDown(){
        displayedMatrix[0] = "";

        for(uint8_t i = 0; i < width; ++i){
            if(matrixMask[y][(x + i) % maxX])
                displayedMatrix[0] += externMatrix[y][(x + i) % maxX];
            else 
                displayedMatrix[0] += "🟥"; 
        }

        for(uint8_t i = 1; i < high; ++i)
            displayedMatrix[i] = displayedMatrix[i - 1];        
    }

    void UI::moveMapRight(){
        for(uint8_t i = 0; i < high; ++i){
            frontDel(displayedMatrix[i]);
            if(matrixMask[(y + i) % maxY][(x + width) % maxX])
                displayedMatrix[i] += externMatrix[(y + i) % maxY][(x + width) % maxX];
            else 
                displayedMatrix[i] += "🟥"; 
        }        
    }
    
    void UI::moveMapLeft(){
        for(uint8_t i = 0; i < high; ++i){
            backDel(displayedMatrix[i]);
            std::string symb;
            if(matrixMask[(y + i) % maxY][x])
                symb = externMatrix[(y + i) % maxY][(x + width) % maxX];
            else 
                symb = "🟥";
            displayedMatrix[i] = symb + displayedMatrix[i]; 
        }
    }
}