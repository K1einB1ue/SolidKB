#pragma once
#include<list>
#include<functional>


template<typename T,typename ...Args>
class Event{
    private:
    std::list<std::function<T(Args...)>> Funcs;
};