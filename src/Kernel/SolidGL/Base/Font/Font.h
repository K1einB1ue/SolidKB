#pragma once
#include"../../SolidGL_Standard.h"

namespace SolidGL{
    namespace Encode{
        struct UTF8{
            class String:public std::string{

            };
        };
        struct UTF16{
            class String:public std::string{

            };
        };
        struct Unicode{
            class String:public std::string{

            };
        }; 
        struct ASCII{
            using String = typename UTF8::String;
        };

        

        

        template<typename IN,typename OUT>
        class ConvertManager{
            public:
            using IN_String = typename IN::String;
            using OUT_String = typename OUT::String;
            static OUT_String Convert(const IN_String& INstring);
        };
    }
}