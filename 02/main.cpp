#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

auto count() {
    LL result = 0;
// #ifdef TEST
    LL red_total = 12;
    LL green_total = 13;
    LL blue_total = 14;
// #endif
    for(auto s : in){
        auto l = splitStr(s, ':');
        auto game = stoi(splitStr(l[0], ' ')[1]);
        auto l2 = splitStr(l[1], ';');
        bool correct = true;
        for(auto set: l2){
            std::map<S, LL> balls;
            auto balls_set = splitStr(set, ',');
            for(auto ball: balls_set) {
                auto l3 = splitStr(ball, ' ');
                auto num = stoi(l3[0]);
                auto color = l3[1];
                if(!balls.count(color)){
                    balls[color] = 0;
                }
                balls[color] += num;
            }
            // P_MAP(balls);
            if((balls.count("red") + balls.count("green") + balls.count("blue")) != balls.size()) {
                correct = false;
                break;
            }
            if(balls.count("red") && balls["red"] > red_total) {
                correct = false;
                break;
            }
            if(balls.count("green") && balls["green"] > green_total) {
                correct = false;
                break;
            }
            if(balls.count("blue") && balls["blue"] > blue_total) {
                correct = false;
                break;
            }
        }
        result += correct ? game : 0;
        if(correct)P(s);
    }
    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count();
    P_RR("Part1: %lld\n", score);
    //========================================================

    // score = count();
    P_RR("Part2: %lld\n", score);
    return 0;
}
