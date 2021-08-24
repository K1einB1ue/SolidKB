#pragma once
#include"../../SolidGL_Standard.h"

namespace SolidGL{
    namespace Draw{
        //占用1字节的1位深度
        //启用缓存时不会占用多余空间
        struct Bit{
            struct Color{
                public:
                Color()=default;
                Color(u_char Byte):Byte(Byte){}
                u_char Byte;
                void Light(bool Light){
                    this->Byte=Light?1:0;
                }
            };
            struct Pen{
                unsigned int Width=1;
                Color color;
            };
        };
        //占用1字节的3/3/2位深度
        struct RGB332{
            union Color{
                public:
                Color()=default;
                Color(u_char Byte):Byte(Byte){}
                u_char Byte;
                void R(u_char R){
                    this->Byte &=~(0b111<<5);
                    this->Byte |=(R<<5);
                }
                void G(u_char G){
                    this->Byte &=~(0b111<<2);
                    this->Byte |=(G<<2);
                }
                void B(u_char B){
                    this->Byte &=~0b11;
                    this->Byte |=B;
                }
            };
            struct Pen{
                unsigned int Width=1;
                Color color;
            };
        };
        //占用2字节的5/6/5位深度
        struct RGB565{
            union Color{
                public:
                Color()=default;
                Color(uint16_t Bytes):Bytes(Bytes){}
                uint16_t Bytes;
                void R(uint16_t R){
                    this->Bytes &=~(0b11111<<11);
                    this->Bytes |=(R<<11);
                }
                void G(uint16_t G){
                    this->Bytes &=~(0b111111<<5);
                    this->Bytes |=(G<<5);
                }
                void B(uint16_t B){
                    this->Bytes &=~0b11111;
                    this->Bytes |=B;
                }
            };
            struct Pen{
                unsigned int Width=1;
                Color color;
            };
        };
        //占用4字节的8/8/8/8位深度
        struct ARGB8888{
            union Color{
                private:
                struct{
                    u_char A_;
                    u_char R_;
                    u_char G_;
                    u_char B_;
                };
                public:
                Color()=default;
                Color(uint32_t Bytes):Bytes(Bytes){}
                
                uint32_t Bytes;
                void A(u_char A){
                    this->A_=A;
                }
                void R(u_char R){
                    this->R_=R;
                }
                void G(u_char G){
                    this->G_=G;
                }
                void B(u_char B){
                    this->B_=B;
                }
            };  
            struct Pen{
                unsigned int Width=1;
                Color color;
            };
        }; 
    }
}