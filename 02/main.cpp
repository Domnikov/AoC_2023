#ifdef TEST
#include "in_test.hpp"
#else
#include "in.hpp"
#endif

#include <queue>
#include <list>

auto in = getInput();

auto count_2() {
    LL result = 0;
    LL red_total = 12;
    LL green_total = 13;
    LL blue_total = 14;
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

auto count_1() {
    LL result = 0;
    LL red_min = 99999;
    LL green_min = 99999;
    LL blue_min = 99999;
    for(auto s : in){
        auto l = splitStr(s, ':');
        auto game = stoi(splitStr(l[0], ' ')[1]);
        auto l2 = splitStr(l[1], ';');
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
            if(balls.count("red") && balls["red"] < red_min) {
                red_min = balls["red"];
                break;
            }
            if(balls.count("green") && balls["green"] < green_min) {
                green_min = balls["green"];
                break;
            }
            if(balls.count("blue") && balls["blue"] < blue_min) {
                blue_min = balls["blue"];
                break;
            }
        }
        P(s, red_min, green_min, blue_min);
        result += red_min*green_min*blue_min;
    }
    return result;
}

int main(int argc, char** argv)
{
    LL score = 0;
    score = count_1();
    P_RR("Part1: %lld\n", score);
    //========================================================

    score = count_2();
    P_RR("Part2: %lld\n", score);
    return 0;
}
