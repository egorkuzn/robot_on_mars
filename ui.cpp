#include "ui.h"

//        setlocale(LC_CTYPE, "");

namespace graphics{
    std::string UI::emojiTranslator(planet::Item item){
        switch (item)
        {
        case planet::ROCK:
            return "🪨 ";
        case planet::BOMB:
            return "💣";
        case planet::APPLE:
            return "🍏";
        case planet::EMPTY:
            return "🟫";
        default:
            return "🟫";
        }
    }

    int UI::safetyIndexTake(Matrix mType, size_t x0, size_t y0){
        switch(mType){
            case Matrix::MAP:
                return externMatrix[Y(y0)][X(x0)];
            case Matrix::MASK:
                return matrixMask[Y(y0)][X(x0)];
            default:
                //place for exception
                return false;
        }
    }

    bool UI::isRobotHere(size_t x0, size_t y0){
        X(x0);
        Y(y0);
        for(size_t id = 0; id < xyRobots.size(); ++id)
            if(xyRobots[id].first == y0 && xyRobots[id].second == x0)
                return true;
        return false;
    }

    size_t UI::X(size_t x0){
        return (x0 + x_limit)% x_limit;
    }

    size_t UI::Y(size_t y0){
        return (y0 + y_limit)% y_limit;
    }

    std::string UI::genMatrixString(size_t stringNumb){
        std::string result;
        size_t x0 = X(x - width / 2);
        for(size_t i = 0; i < width; ++i)
            if(isRobotHere(X(x0 + i), stringNumb))
                result += "🤖";
            else if(safetyIndexTake(Matrix::MASK, X(x0 + i), stringNumb))
                result += emojiTranslator((planet::Item)safetyIndexTake(Matrix::MAP, X(x0 + i), stringNumb));
            else
                result += "🟥";
        return result;
    }

    void UI::window(){
        displayedMatrix.resize(high + 1);   
        size_t y0 = Y(y - size_t(high / 2));
        displayedMatrix[0] = statusBar;
        for(size_t i = 0; i < high; ++i)
            displayedMatrix[i + 1] = genMatrixString(Y(i + y0));
    }

    UI::UI( std::vector<std::pair<size_t, size_t>>& xyRobots,
            std::vector<std::vector<bool>>& matrixMask,
            std::vector<planet::vectorItems>& externMatrix,
            size_t x_limit, size_t y_limit ) :
                                                    xyRobots(xyRobots),
                                                    matrixMask(matrixMask),
                                                    externMatrix(externMatrix),
                                                    x_limit(x_limit),
                                                    y_limit(y_limit){
    }

    void UI::display() noexcept{
        system("clear");
        displayedMatrix.clear();
        window();
        for(std::string elem : displayedMatrix)
            std::cout << elem << std::endl;
    }

    UI::~UI(){
        system("clear");
    }

    UI::operator bool() const{
        return status;
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
            case 'w':
                return Keys::W;
            case 27:
                return Keys::Esc;
            default:
                return Keys::EMPTY;
        }
    }

    int UI::_kbhit() {
        static const int STDIN = 0;
        static bool initialized = false;
        int bytesWaiting;
        if (!initialized) {
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
        if(_kbhit()){  /// If keyboard hit
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
        while (clock() < time_end){}
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
    
    void UI::changeCentre(size_t x0, size_t y0){
        if(x != x0 || y != y0){
            x = x0;
            y = y0;
            display();
        }
    }

    void UI::mapUpdate(std::vector<std::pair<size_t, size_t>>& _xyRobots,
                std::vector<std::vector<bool>>& _matrixMask,
                std::vector<planet::vectorItems>& _externMatrix){
        xyRobots = _xyRobots;
        externMatrix = _externMatrix;
        matrixMask = _matrixMask;
        display();
    }
}