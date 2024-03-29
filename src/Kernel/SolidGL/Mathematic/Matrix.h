#pragma once
#include"../../AbstractDependency/__AbstractDependency.h"

template<unsigned int Size,typename DataType>
class Vector{
protected:
    DataType Data[Size];
public:
    Vector()=default;
    ~Vector()=default;
    DataType& operator[](unsigned int i){
        return this->Data[i];
    }
    Vector& operator *=(Vector Vec){
        for(u_int i=0;i<Size;i++){
            this->Data[i]*=Vec[i];
        }
        return *this;
    }
    Vector& operator +=(Vector Vec){
        for(u_int i=0;i<Size;i++){
            this->Data[i]+=Vec[i];
        }
        return *this;
    }

    Vector& operator =(Vector Vec){
        for(u_int i=0;i<Size;i++){
            this->Data[i]=Vec[i];
        }
        return *this;
    }
};

template<typename DataType>
class Vector2:public Vector<2,DataType>{
public:
    Vector2():x(this->Data[0]),y(this->Data[1]){this->x=0;this->y=0;}
    DataType &x,&y;
    
    Vector2& operator =(Vector2 Vec2){
        this->x=Vec2.x;
        this->y=Vec2.y;
        return *this;
    }
    
};

template<typename DataType>
class Vector3:public Vector<3,DataType>{
public:
    Vector3():x(this->Data[0]),y(this->Data[1]),z(this->Data[2]){this->x=0;this->y=0;this->z=0;}
    DataType &x,&y,&z;
};

template<unsigned int Order,typename DataType>
class Matrix{
private:
    Vector<Order,DataType> Data[Order];
public:
    Matrix()=default;
    ~Matrix()=default;
    DataType &operator[](unsigned int i){
        return this->Data[i];
    }
    
};



