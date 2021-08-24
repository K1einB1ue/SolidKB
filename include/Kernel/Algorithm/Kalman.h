#pragma once
#include<vector>
#include<functional>
#include<Algorithm/Matrix.h>
template<unsigned int SensorCnt>
class Kalman{
    private:
    Matrix<SensorCnt> F_k;
    bool    MeasuredTable[SensorCnt];
    double  MeasureValues[SensorCnt];
    double  Possibilities[SensorCnt];

    unsigned int SensorValuedCnt=0;
    double PreviousValue=0;
    double Possibility=0;
    double PridictedValue=0;

    public:
    std::function<double(double)> Pre2Pri = nullptr;
    Kalman()=default;
    ~Kalman()=default;

    void SensorValue(unsigned int SensorId,double Value){
        if(!MeasuredTable[SensorId]){
            MeasuredTable[SensorId]=true;
            SensorValuedCnt++;
            if(SensorValuedCnt==SensorCnt){
                for(unsigned int i=0;i<SensorCnt;i++){
                    MeasuredTable[i]=false;
                }
                SensorValuedCnt=0;
                this->Culculate();
            }
        }
    }

    void Culculate(){
        //先验估计
        this->PridictedValue=this->Pre2Pri(this->PreviousValue);
        //计算过程协方差矩阵的微分矩阵

        //计算Kalman增益

        //后验估计误差协方差

        //计算最优角速度值
    }
};
