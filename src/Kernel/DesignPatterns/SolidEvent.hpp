#pragma once
#include<map>
#include<vector>
#include<functional>
class SolidEvent{
    private:
    std::vector<std::pair<std::function<bool(void)>,std::function<void(void)>>> m_Functions;
    SolidEvent(){}
    public:

    void Update(){
        for(unsigned int i=0;i<m_Functions.size();i++){
            if(m_Functions[i].first()){
                m_Functions[i].second();
            }
        }
    }

    void Register(std::function<bool(void)> trigger,std::function<void(void)> invoke){
        std::pair<std::function<bool(void)>,std::function<void(void)>> *temp=new std::pair<std::function<bool(void)>,std::function<void(void)>>(trigger,invoke);
        m_Functions.push_back(*temp);
    }

    static SolidEvent& getInstance(){
        static SolidEvent instance;
        return instance;
    }
};