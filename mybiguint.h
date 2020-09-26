#include <iostream>
#include <vector>
#include <iterator>
#include <complex>
#include <algorithm>
#include <cmath>

template <unsigned int Kbit>
class MyBigUint{
    static const uint64_t BASE = 4294967296;
    static const unsigned int Kbyte = Kbit >> 3;
    static const unsigned int DataSize = MyBigUint::Kbyte/sizeof(uint64_t);

    std::vector<uint64_t> number;
    static const int FT_INVERSE = 1;
    static const int FT_DIRECT = -1;
    int N;

    void fft(std::complex<long double> * In, int Ft_flag,int N, int LogN)
    {

        int i, j, n, k, io, ie, in, nn;
        float ru, iu, rtp, itp, rtq, itq, rw, iw, sr;

        static const float Rcoef[14] =
            { -1.0000000000000000F, 0.0000000000000000F,
               0.7071067811865475F, 0.9238795325112867F,
               0.9807852804032304F, 0.9951847266721969F,
               0.9987954562051724F, 0.9996988186962042F,
               0.9999247018391445F, 0.9999811752826011F,
               0.9999952938095761F, 0.9999988234517018F,
               0.9999997058628822F, 0.9999999264657178F };

        static const float Icoef[14] =
            {  0.0000000000000000F, -1.0000000000000000F,
              -0.7071067811865474F, -0.3826834323650897F,
              -0.1950903220161282F, -0.0980171403295606F,
              -0.0490676743274180F, -0.0245412285229122F,
              -0.0122715382857199F, -0.0061358846591544F,
              -0.0030679567629659F, -0.0015339801862847F,
              -0.0007669903187427F, -0.0003834951875714F };

        nn = N >> 1;
        ie = N;
        for (n = 1; n <= LogN; n++) {
            rw  = Rcoef[LogN - n];
            iw  = Icoef[LogN - n];
            if (Ft_flag == MyBigUint::FT_INVERSE)
                iw = -iw;
            in = ie >> 1;
            ru = 1.0F;
            iu = 0.0F;
            for (j = 0; j < in; j++) {
                for (i = j; i < N; i +=ie) {
                    io = i + in;

                    rtp = In[i].real() + In[io].real();
                    itp = In[i].imag() + In[io].imag();
                    rtq = In[i].real() - In[io].real();
                    itq = In[i].imag() - In[io].imag();

                    In[io].real(rtq * ru - itq * iu);
                    In[io].imag(itq * ru + rtq * iu);
                    In[i].real(rtp);
                    In[i].imag(itp);
                }
                sr = ru;
                ru = ru * rw - iu * iw;
                iu = iu * rw + sr * iw;
            }
            ie >>= 1;
        }
        for (j = i = 1; i < N; i++) {
            if (i < j) {
                io = i - 1;
                in = j - 1;
                rtp = In[in].real();
                itp = In[in].imag();
                In[in].real(In[io].real());
                In[in].imag(In[io].imag());
                In[io].real(rtp);
                In[io].imag(itp);
            }
            k = nn;
            while (k < j) {
                j = j - k;
                k >>= 1;
            }
            j = j + k;
        }
        if (Ft_flag == MyBigUint::FT_DIRECT)
            return;
        rw = 1.0F / N;
        for (i = 0; i < N; i++){
            In[i].real(In[i].real() * rw);
            In[i].imag(In[i].imag() * rw);
        }
    }


public:
    /*class Div_Error
    {
    public:
        Div_Error() {
            std::cout<<"Division by zero!"<<std::endl;
        }
    };*/

    MyBigUint(){
        number.reserve(MyBigUint::DataSize);
        number.assign(number.size(),0);
        while(!((number.size() > 1) && (!(((number.size())&(number.size()-1))))))
            number.push_back(0);
        N = std::log2(number.size());
    }

    MyBigUint(const std::vector<uint64_t> & a):number(a){
        while (number.size() < MyBigUint::DataSize) {
            number.push_back(0);
        }
        while (number.size() > MyBigUint::DataSize) {
            number.pop_back();
        }
        while(!((number.size() > 1) && (!(((number.size())&(number.size()-1))))))
            number.push_back(0);
        N = std::log2(number.size());
        }

    void print(){
        auto it = number.begin();
        while(it != number.end()){
            std::cout<< *it<<" ";
            it++;
        }
        std::cout<<std::endl;
    }

    void push (const uint64_t & a){
        number.push_back(a);
    }

    void setN(int n){
        N=n;
    }

    void setNumber(const std::vector<uint64_t> & a){
        number=a;
        while (number.size() < MyBigUint::DataSize) {
            number.push_back(0);
        }
        while (number.size() > MyBigUint::DataSize) {
            number.pop_back();
        }
        while(!((number.size() > 1) && (!(((number.size())&(number.size()-1))))))
            number.push_back(0);
        N = std::log2(number.size());
    }


    bool operator < (const MyBigUint & b){
        std::vector<uint64_t> t_a = number;
        std::vector<uint64_t> t_b = b.number;
        for (int i =t_a.size()-1; i>=0; --i){
            if(t_a[i] < t_b[i])
                return true;
            if(t_a[i] > t_b[i])
                return false;
        }
        return false;
    }

    MyBigUint& operator = (uint64_t b){
        number = {b,0};
        return *this;
    }

    bool operator > (const MyBigUint & b){
        std::vector<uint64_t> t_a = number;
        std::vector<uint64_t> t_b = b.number;
        for (int i =t_a.size()-1; i>=0; --i){
            if(t_a[i] > t_b[i])
                return true;
            if(t_a[i] < t_b[i])
                return false;
        }
        return false;
    }

    bool operator == (const MyBigUint & b){
        std::vector<uint64_t> t_a = number;
        std::vector<uint64_t> t_b = b.number;
        for (int i =t_a.size()-1; i>=0; --i){
            if(t_a[i] != t_b[i])
                return false;
        }
        return true;
    }

    MyBigUint operator + (uint64_t a){
        std::vector<uint64_t> tmp = {a,0};
        MyBigUint mn(tmp);
        return *this + mn;
    }

    MyBigUint operator +(const MyBigUint & a){

        std::vector<uint64_t> tmp;//временный вектор
        auto it1 = number.begin();
        auto it2 = a.number.begin();
        int c =0;
        uint64_t b =0;

        while((it1 != number.end()) && (it2 !=a.number.end())){
            tmp.push_back( *it1 + *it2 + b);//поразарядно скаладываем и добовляем во временный вектор
            if( tmp[c] < *it1) //если произошло переполнение меняем старший разряд
               b =1;
            else
                b =0;
            it1++;
            it2++;
            c++;

        }

        return MyBigUint(tmp);
    }
    MyBigUint operator - (uint64_t a){
        std::vector<uint64_t> tmp = {a,0};
        MyBigUint mn(tmp);
        return *this - mn;
    }

    MyBigUint operator -(const MyBigUint & a){   //вычитание выполняется аналогично сложению
                                                 //при переполнении старший разряд уменьшается
        std::vector<uint64_t> tmp;
        auto it1 = number.begin();
        auto it2 = a.number.begin();
        int c =0;
        uint64_t b =0;

        while((it1 != number.end()) && (it2 !=a.number.end())){
            tmp.push_back( *it1 - *it2 - b);
            if( tmp[c] > *it1){
               b =1;
            }
            else
                b =0;
            it1++;
            it2++;
            c++;
        }
        return MyBigUint(tmp);
    }

    MyBigUint operator * (const MyBigUint & a){
        // Представим вектора как коэффиценты многоченов A и B
        // По свойству DFT(A*B) = DFT(A) * DFT(B) => A * B = invDFT(A*B)

        //a.setN(N);
        std::vector<uint64_t> res(2*number.size());
        std::vector<uint64_t> res1(number.size());
        std::complex<long double> *m1 = new std::complex<long double> [2*number.size()];
        std::complex<long double> *m2 = new std::complex<long double> [2*number.size()];


        for(uint i =0; i < 2*number.size();i=i+2 ){
            m1[i].real(number[i/2]%MyBigUint::BASE);
           //std::cout<<i<<std::endl;
            m1[i+1].real(number[i/2]/MyBigUint::BASE);
            //std::cout<<number[i+1];
            m2[i].real(a.number[i/2]%MyBigUint::BASE);
            m2[i+1].real(a.number[i/2]/MyBigUint::BASE);
        }

        fft(m1,FT_DIRECT,2*number.size(),N+1);
        fft(m2,FT_DIRECT,2*number.size(),N+1);

        for(uint i =0; i < 2 * number.size();i++ ){
            m1[i]*=m2[i];
        }

        fft(m1,FT_INVERSE,2*number.size(),N+1);
        for(uint i =0; i < 2*number.size();i++ ){
            res[i]= (uint64_t)(m1[i].real() + 0.5);
        }
        for (uint i = 0; i < res.size();i=i+2 )
            res1[i/2]=res[i]+res[i+1]*MyBigUint::BASE;

        delete [] m1;
        delete [] m2;
        return MyBigUint(res1);
    }

    MyBigUint operator * (uint64_t b){
        std::vector<uint64_t> tmp ={b,0};
        MyBigUint mn(tmp);
        return *this * mn;
    }

//Деление
    MyBigUint operator /(uint64_t b){
        std::vector<uint64_t> d_a = number;
        uint64_t  high=0;
        uint64_t low=0;
        uint64_t curry =0;
        uint64_t ost = 0;
        std::vector<uint64_t> tmp_a;

        if(b == 0)
            throw std::domain_error("Division by zero!");

        if(b == 1)
            return *this;
        for (int i =d_a.size()-1; i>=0; --i){
            high =d_a[i]/MyBigUint::BASE;
            low = d_a[i]%MyBigUint::BASE;
            high+=curry*MyBigUint::BASE;
            ost = high%b;
            high/=b;
            low+=ost*MyBigUint::BASE;
            ost= low%b;
            low/=b;
            d_a[i]=(high)*MyBigUint::BASE +low;
            curry= ost;

        }
        return MyBigUint(d_a);

    }

    MyBigUint operator / (const MyBigUint & b){

        std::vector<uint64_t> d_a = number;
        std::vector<uint64_t> d_b = b.number;
        uint64_t  high=0;
        uint64_t low=0;
        uint64_t curry =0;
        uint64_t ost = 0;
        std::vector<uint64_t> tmp_a;
        std::vector<uint64_t> tmp_b;
        std::vector<uint64_t> one={1,0};


        if( *this == b){
            return MyBigUint(one);
        }

        while(!d_a.back() && d_a.size()>1){
            d_a.pop_back();
        }

        while(!d_b.back() && d_b.size()>1){
            d_b.pop_back();
        }



        if (d_a.size() < d_b.size())
            return MyBigUint();

        if ((d_a.size() == 1) && (d_a[0] ==0))
            return MyBigUint();

        if((d_b.size() == 1) && (d_b[0] == 0))
            throw std::domain_error("Division by zero!");

        if((d_b.size() == 1) && (d_b[0] != 0)){

            for (int i =d_a.size()-1; i>=0; --i){
                high =d_a[i]/MyBigUint::BASE;
                low = d_a[i]%MyBigUint::BASE;
                high+=curry*MyBigUint::BASE;
                ost = high%d_b[0];
                high/=d_b[0];
                low+=ost*MyBigUint::BASE;
                ost= low%d_b[0];
                low/=d_b[0];
                d_a[i]=(high)*MyBigUint::BASE +low;
                curry= ost;

            }
            return MyBigUint(d_a);
        }

        MyBigUint mul1;
        uint64_t  dvr;
        tmp_b = d_b;
        tmp_a = d_a;

        dvr = d_b[d_b.size()-1];
        curry=0;
        for (uint i =d_a.size()-1; i>=d_b.size()-1; --i){
            high =tmp_a[i]/MyBigUint::BASE;
            low = tmp_a[i]%MyBigUint::BASE;
            high+=curry*MyBigUint::BASE;
            ost = high%dvr;
            high/=dvr;
            low+=ost*MyBigUint::BASE;
            ost= low%dvr;
            low/=dvr;
            tmp_a[i]=(high)*MyBigUint::BASE +low;
            curry= ost;
         }
         while(tmp_a.size()>(d_a.size()-d_b.size() + 1))
               tmp_a.erase(tmp_a.begin());
         mul1.setNumber(tmp_a);
         return mul1;
    }

//Остаток

    MyBigUint operator % (uint64_t b){
        std::vector<uint64_t> d_a = number;
        uint64_t  high=0;
        uint64_t low=0;
        uint64_t curry =0;
        uint64_t ost = 0;
        std::vector<uint64_t> tmp_a;

        if(b == 0)
            throw std::domain_error("Division by zero!");

        if(b == 1)
            return *this;
        for (int i =d_a.size()-1; i>=0; --i){
            high =d_a[i]/MyBigUint::BASE;
            low = d_a[i]%MyBigUint::BASE;
            high+=curry*MyBigUint::BASE;
            ost = high%b;
            high/=b;
            low+=ost*MyBigUint::BASE;
            ost= low%b;
            low/=b;
            d_a[i]=(high)*MyBigUint::BASE +low;
            curry= ost;

        }
        tmp_a = {ost,0};
        return MyBigUint(tmp_a);

    }

    MyBigUint operator % (MyBigUint & b){
        std::vector<uint64_t> d_a = number;
        std::vector<uint64_t> d_b = b.number;
        std::vector<uint64_t> buf;
        uint64_t  high=0;
        uint64_t low=0;
        uint64_t curry =0;
        uint64_t ost = 0;

        while(!d_a.back() && d_a.size()>1){
            d_a.pop_back();
        }

        while(!d_b.back()&& d_b.size()>1){
            d_b.pop_back();
        }
        if( *this == b){
            return MyBigUint();
        }

        if (*this < b)
            return b - *this;


        if((d_b.size() == 1) && (d_b[0] == 0))
            throw std::domain_error("Division by zero!");

        if((d_b.size() == 1) && (d_b[0] != 0)){

            for (int i =d_a.size()-1; i>=0; --i){
                high =d_a[i]/MyBigUint::BASE;
                low = d_a[i]%MyBigUint::BASE;
                high+=curry*MyBigUint::BASE;
                ost = high%d_b[0];
                high/=d_b[0];
                low+=ost*MyBigUint::BASE;
                ost= low%d_b[0];
                low/=d_b[0];
                d_a[i]=(high)*MyBigUint::BASE +low;
                curry= ost;

            }
            d_b[0]=curry;
            return MyBigUint(d_b);
        }
        MyBigUint rzn;
        MyBigUint mul1,mul2;
        uint64_t  dvr;
        std::vector<uint64_t> tmp_b = d_b;
        std::vector<uint64_t> tmp_a = d_a;

        dvr = d_b[d_b.size()-1];
        curry=0;
        for (int i =d_a.size()-1; i>=d_b.size()-1; --i){
            high =tmp_a[i]/MyBigUint::BASE;
            low = tmp_a[i]%MyBigUint::BASE;
            high+=curry*MyBigUint::BASE;
            ost = high%dvr;
            high/=dvr;
            low+=ost*MyBigUint::BASE;
            ost= low%dvr;
            low/=dvr;
            tmp_a[i]=(high)*MyBigUint::BASE +low;
            curry= ost;
         }
         while(tmp_a.size()>(d_a.size()-d_b.size() + 1))
               tmp_a.erase(tmp_a.begin());
         std::cout<<tmp_a.size()<<std::endl;
         mul1.setNumber(tmp_a);
         mul2.setNumber(d_b);
         rzn = mul2 - mul1;
         return rzn;



    }
};
