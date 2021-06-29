#include<Abstract/DisplayAbstract.h>
#include<DataPack/ASCIIFont.h>




DisplayBITAbstract::DisplayBITAbstract(){}

DisplayBITAbstract::~DisplayBITAbstract(){
    if(!OutRam){
        for(unsigned int i=0;i<width;i++){
            delete[] this->GRAM[i];
        }
        delete[] this->GRAM;
    }
}

void DisplayBITAbstract::__GraphicInit(unsigned int width, unsigned int height){
    this->width=width;
    this->height=height/8;
    this->GRAM=new u_char*[this->width];
    for(unsigned int i=0;i<this->width;i++){
        this->GRAM[i]=new u_char[this->height];
    }
    this->Clear();
}


void DisplayBITAbstract::__GraphicInit(u_char **GRAM,unsigned int width, unsigned int height){
    OutRam=true;
    this->GRAM=GRAM;
    this->width=width/8;
    this->height=height;
}


void DisplayBITAbstract::DrawPixel(unsigned int x, unsigned int y){
    unsigned int i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	this->GRAM[x][i]|=n;
}

void DisplayBITAbstract::ClearPixel(unsigned int x, unsigned int y){
    unsigned int i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	this->GRAM[x][i]=~this->GRAM[x][i];
	this->GRAM[x][i]|=n;
	this->GRAM[x][i]=~this->GRAM[x][i];
}

void DisplayBITAbstract::DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2){
    unsigned int i,k,k1,k2;
	if((x1<0)||(x2>128)||(y1<0)||(y2>64)||(x1>x2)||(y1>y2))return;
	if(x1==x2) {
        for(i=0;i<(y2-y1);i++) {
            DrawPixel(x1,y1+i);
        }
    }
	else if(y1==y2) {
        for(i=0;i<(x2-x1);i++) {
            DrawPixel(x1+i,y1);
        }
    }
	else {
		k1=y2-y1;
		k2=x2-x1;
		k=k1*10/k2;
		for(i=0;i<(x2-x1);i++) {
            DrawPixel(x1+i,y1+i*k/10);
        }
	}
}

void DisplayBITAbstract::DrawCircle(unsigned int x, unsigned int y, unsigned int radius){
    unsigned int a, b,num;
    a = 0;
    b = radius;
    while(2 * b * b >= radius * radius) {
        DrawPixel(x + a, y - b);
        DrawPixel(x - a, y - b);
        DrawPixel(x - a, y + b);
        DrawPixel(x + a, y + b);
 
        DrawPixel(x + b, y + a);
        DrawPixel(x + b, y - a);
        DrawPixel(x - b, y - a);
        DrawPixel(x - b, y + a);
        
        a++;
        num = (a * a + b * b) - radius*radius;//计算画的点离圆心的距离
        if(num > 0) {
            b--;
            a--;
        }
    }
}

void DisplayBITAbstract::DrawChar(unsigned int x, unsigned int y,const char chr, u_char fontSize){
    unsigned int i,m,temp,size2,chr1;
	unsigned int y0=y;
	size2=(fontSize/8+((fontSize%8)?1:0))*(fontSize/2);  //得到字体一个字符对应点阵集所占的字节数
	chr1=chr-' ';  //计算偏移后的值
	for(i=0;i<size2;i++)
	{
		if(fontSize==12)
        {temp=asc2_1206[chr1][i];} //调用1206字体
		else if(fontSize==16)
        {temp=asc2_1608[chr1][i];} //调用1608字体
		else if(fontSize==24)
        {temp=asc2_2412[chr1][i];} //调用2412字体
		else return;
        for(m=0;m<8;m++) {
            if(temp&0x80)DrawPixel(x,y);
            else ClearPixel(x,y);
            temp<<=1;
            y++;
            if((y-y0)==fontSize) {
                y=y0;
                x++;
                break;
            }
        }
    }
}

void DisplayBITAbstract::DrawString(unsigned int x, unsigned int y,const std::string &str, u_char fontSize){
    for(unsigned int i=0;i<str.size();i++) {
        if((str[i]>=' ')&&(str[i]<='~')) {
            DrawChar(x,y,str[i],fontSize);
            x+=fontSize/2;
            if(x>128u-fontSize) {
                x=0;
                y+=2;
            }
        }
    }
}

void DisplayBITAbstract::Clear(){
    unsigned int i,n;
	for(i=0;i<this->width;i++){
	   for(n=0;n<this->height;n++){
            GRAM[i][n]=0;       //清除所有数据
        }
    }
}

void DisplayBITAbstract::Refresh(){}