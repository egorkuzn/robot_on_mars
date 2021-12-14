#include "ui.h"

#define DEFAULT_SYMB "🟥"

//        setlocale(LC_CTYPE, "");


namespace graphics{
    void UI::window(){
        displayedMatrix.resize(high + 1);    
        std::string symb;    
        size_t x0 = x - width/2; 
        size_t y0 = y - high/2;
        displayedMatrix[0] = statusBar;
        for(size_t i = y0; i > 0; --i)
            for(size_t j = 0; j < width; ++j ){                
                if(matrixMask[y - i][x0 + j])
                    emojiTranslator(symb, externMatrix[y - i][x0 + j]);
                else
                    symb = DEFAULT_SYMB;
                displayedMatrix[i] += symb;
            }
        // y with robot
        for(size_t i = y0; i <= high; ++i)
            for(size_t j = 0; j < width; ++j ){                
                if(matrixMask[y - i][x0 + j])
                    emojiTranslator(symb, externMatrix[y + i][x0 + j]);
                else
                    symb = DEFAULT_SYMB;
                displayedMatrix[i] += symb;
            }
    }

    void UI::windowRefresh(){

    }

    void UI::display(){
        windowRefresh();
        system("clear");
        
        for(std::string& elem : displayedMatrix)
            std::cout << elem << std::endl;
        std::cout << liveStr << std::endl;
    }

    UI::UI(){
        system("clear");
        window();
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


    void UI::refreshStatusBar(){
        statusBar = "🍏 x" + std::to_string(appleCount) + "   🤖 x" +
         std::to_string(liveCount) + "   💀 x" + std::to_string(dieCount);
    }

    void UI::displayAppleCount(size_t value){
        appleCount = value;
        refreshStatusBar();
    }

    void UI::displayRobotCount(size_t value){
        liveCount = value;
        refreshStatusBar();
    }

    void UI::displayDieCount(size_t value){
        liveCount -= value - dieCount;
        dieCount = value;
        refreshStatusBar();
    }

    void UI::importUpdatedMatrix(std::vector<planet::vectorItems>& updatedMap){
        externMatrix = updatedMap;
    }

    void UI::importUpdatedMaskMatrix(std::vector<std::vector<bool>>& updatedMaskMap){
        matrixMask = updatedMaskMap;
    }

    void UI::changeCentre(size_t x0, size_t y0){
        x = x0;
        y = y0;
    }
}