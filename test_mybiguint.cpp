#include "mybiguint.h"
#include "gtest/gtest.h"

//Размер
TEST(Size,size_128){
    // Arrange    
    MyBigUint<128> biguint128;

    //Act

    //Assert
    ASSERT_EQ(biguint128.size(),2);

}

TEST(Size,size_256){
    // Arrange    
    MyBigUint<256> biguint256;

    //Act

    //Assert
    ASSERT_EQ(biguint256.size(),4);

}

TEST(Size,size_512){
    // Arrange    
    MyBigUint<512> biguint512;

    //Act

    //Assert
    ASSERT_EQ(biguint512.size(),8);

}

TEST(Size,size_1024){
    // Arrange    
    MyBigUint<1024> biguint1024;

    //Act

    //Assert
    ASSERT_EQ(biguint1024.size(),16);

}

TEST(Size,size_2048){
    // Arrange    
    MyBigUint<2048> biguint2048;

    //Act

    //Assert
    ASSERT_EQ(biguint2048.size(),32);

}

//Инициализация

TEST(Init, init_constr){
    //Arrange
    std::vector<uint64_t> a = {1,1};
    MyBigUint<128> b(a);

    //Act

    //Assert
    ASSERT_EQ(b.getNumber(),a);
}

TEST(Init, init_v){
    //Arrange
    std::vector<uint64_t> a = {1,1};
    MyBigUint<128> b;

    //Act
    b.setNumber(a);
    //Assert
    ASSERT_EQ(b.getNumber(),a);
}

TEST(Init, init_Bint){
    //Arrange
    std::vector<uint64_t> a = {1,1};
    MyBigUint<128> b(a);
     MyBigUint<128> c;

    //Act
    c=b;
    //Assert
    ASSERT_EQ(b.getNumber(),c.getNumber());
}

//Операторы сравнения
TEST(Compare, cmp_lt_t){
    //Arrange
    std::vector<uint64_t> a = {1,1};
    MyBigUint<128> b(a);
    a = {1,2};
    MyBigUint<128> c(a);

    //Act
   
    //Assert
    ASSERT_TRUE(b<c);
}

TEST(Compare, cmp_lt_f){
    //Arrange
    std::vector<uint64_t> a = {1,1};
    MyBigUint<128> b(a);
    a = {1,2};
    MyBigUint<128> c(a);

    //Act
   
    //Assert
    ASSERT_FALSE(c<b);
}

TEST(Compare, cmp_lt_fe){
    //Arrange
    std::vector<uint64_t> a = {1,1};
    MyBigUint<128> b(a);
    MyBigUint<128> c(a);

    //Act
   
    //Assert
    ASSERT_FALSE(c<b);
}

TEST(Compare, cmp_gt_t){
    //Arrange
    std::vector<uint64_t> a = {1,1};
    MyBigUint<128> b(a);
    a = {1,2};
    MyBigUint<128> c(a);

    //Act
   
    //Assert
    ASSERT_TRUE(c>b);
}

TEST(Compare, cmp_gt_f){
    //Arrange
    std::vector<uint64_t> a = {1,1};
    MyBigUint<128> b(a);
    a = {1,2};
    MyBigUint<128> c(a);

    //Act
   
    //Assert
    ASSERT_FALSE(b>c);
}

TEST(Compare, cmp_gt_fe){
    //Arrange
    std::vector<uint64_t> a = {1,1};
    MyBigUint<128> b(a);
    MyBigUint<128> c(a);

    //Act
   
    //Assert
    ASSERT_FALSE(c>b);
}

TEST(Compare, cmp_eq_t){
    //Arrange
    std::vector<uint64_t> a = {1,1};
    MyBigUint<128> b(a);
    MyBigUint<128> c(a);

    //Act
   
    //Assert
    ASSERT_TRUE(c==b);
}

TEST(Compare, cmp_eq_f){
    //Arrange
    std::vector<uint64_t> a = {1,1};
    MyBigUint<128> b(a);
    a = {1,2};
    MyBigUint<128> c(a);

    //Act
   
    //Assert
    ASSERT_FALSE(b==c);
}

TEST(Compare, cmp_neq_f){
    //Arrange
    std::vector<uint64_t> a = {1,1};
    MyBigUint<128> b(a);
    MyBigUint<128> c(a);

    //Act
   
    //Assert
    ASSERT_FALSE(c!=b);
}

TEST(Compare, cmp_neq_t){
    //Arrange
    std::vector<uint64_t> a = {1,1};
    MyBigUint<128> b(a);
    a = {1,2};
    MyBigUint<128> c(a);

    //Act
   
    //Assert
    ASSERT_TRUE(b!=c);
}

//Сложение
TEST(Add, add_uint){
    //Arrange
    std::vector<uint64_t> a = {18446744073709551610UL,0};
    MyBigUint<128> b(a);
    a = {0,1};
    MyBigUint<128> ans(a);
    uint64_t c=6;

    //Act
    b=b+c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Add, add_bint){
    //Arrange
    std::vector<uint64_t> a = {18446744073709551610UL,0};
    MyBigUint<128> b(a);
    a = {0,1};
    MyBigUint<128> ans(a);
    a = {6,0};
    MyBigUint<128> c(a);

    //Act
    b=b+c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

//Вычитание

TEST(Sub, sub_uint){
    //Arrange
    std::vector<uint64_t> a = {0,1};
    MyBigUint<128> b(a);
    a =  {18446744073709551610UL,0};
    MyBigUint<128> ans(a);
    uint64_t c=6;

    //Act
    b=b-c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Sub, sub_bint){
    //Arrange
    std::vector<uint64_t> a = {0,1};
    MyBigUint<128> b(a);
    a =  {18446744073709551610UL,0};
    MyBigUint<128> ans(a);
    a={6,0};
    MyBigUint<128> c(a);
    

    //Act
    b=b-c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

//Умножение
TEST(Mul, mul_uint){
    //Arrange
    std::vector<uint64_t> a = {6,6};
    MyBigUint<128> b(a);
    a =  {36,36};
    MyBigUint<128> ans(a);
    uint64_t c=6;

    //Act
    b=b*c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Mul, mul_uint_one){
    //Arrange
    std::vector<uint64_t> a = {6,6};
    MyBigUint<128> b(a);
    MyBigUint<128> ans(a);
    uint64_t c=1;

    //Act
    b=b*c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Mul, mul_uint_z){
    //Arrange
    std::vector<uint64_t> a = {6,6};
    MyBigUint<128> b(a);
    a={0,0};
    MyBigUint<128> ans(a);
    uint64_t c=0;

    //Act
    b=b*c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Mul, mul_bint){
    //Arrange
    std::vector<uint64_t> a = {6,6};
    MyBigUint<256> b(a);
    a =  {36,72,36};
    MyBigUint<256> ans(a);
    a={6,6};
    MyBigUint<256> c(a);
    

    //Act
    b=b*c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());

}

TEST(Mul, mul_bint_one){
    //Arrange
    std::vector<uint64_t> a = {6,6};
    MyBigUint<128> b(a);
    MyBigUint<128> ans(a);
    a={1,0};
    MyBigUint<128> c(a);
    
    //Act
    b=b*c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Mul, mul_bint_z){
    //Arrange
    std::vector<uint64_t> a = {6,6};
    MyBigUint<128> b(a);
    a={0,0};
    MyBigUint<128> ans(a);
    a={0,0};
    MyBigUint<128> c(a);
    
    //Act
    b=b*c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

//Деление
TEST(Div, div_uint){
    //Arrange
    std::vector<uint64_t> a = {7,1};
    MyBigUint<128> b(a);
    a =  {6148914691236517207,0};
    MyBigUint<128> ans(a);
    uint64_t c=3;

    //Act
    b=b/c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Div, div_uint_eq){
    //Arrange
    std::vector<uint64_t> a = {7,0};
    MyBigUint<128> b(a);
    a =  {1,0};
    MyBigUint<128> ans(a);
    uint64_t c=7;

    //Act
    b=b/c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Div, div_uint_one){
    //Arrange
    std::vector<uint64_t> a = {7,1};
    MyBigUint<128> b(a);
    a =  {7,1};
    MyBigUint<128> ans(a);
    uint64_t c=1;

    //Act
    b=b/c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Div, div_uint_z){
    //Arrange
    std::vector<uint64_t> a = {7,1};
    MyBigUint<128> b(a);
    uint64_t c=0;

    //Act

    //Assert
    EXPECT_THROW(b/c,std::exception);
}

TEST(Div, div_bint){
    //Arrange
    std::vector<uint64_t> a = {2,0,3};
    MyBigUint<256> b(a);
    a =  {9223372036854775808U,1,0};
    MyBigUint<256> ans(a);
    a = {0,2,0};

    MyBigUint<256> c(a);

    //Act
    b=b/c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}


TEST(Div, div_bint_eq){
    //Arrange
    std::vector<uint64_t> a = {2,0,3};
    MyBigUint<256> b(a);
    MyBigUint<256> c(a);
    a = {1,0,0};
    MyBigUint<256> ans(a);
    
    
    //Act
    b=b/c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Div, div_bint_gt){
    //Arrange
    std::vector<uint64_t> a = {2,0,3};
    MyBigUint<256> b(a);
    a = {5,0,3};
    MyBigUint<256> c(a);
    a = {0,0,0};
    MyBigUint<256> ans(a);
    
    
    //Act
    b=b/c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Div, div_bint_one){
    //Arrange
    std::vector<uint64_t> a = {2,0,3};
    MyBigUint<256> b(a);
    MyBigUint<256> ans(a);
    a = {1,0,0};
    MyBigUint<256> c(a);

  
    //Act
    b=b/c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Div, div_bint_z){
    //Arrange
    std::vector<uint64_t> a = {7,1};
    MyBigUint<128> b(a);
    a={0,0};
    MyBigUint<128> c(a);

    //Act

    //Assert
    EXPECT_THROW(b/c,std::exception);
}

//Взятие остатка

TEST(Mod, mod_uint){
    //Arrange
    std::vector<uint64_t> a = {102,1};
    MyBigUint<128> b(a);
    a =  {18,0};
    MyBigUint<128> ans(a);
    uint64_t c=100;

    //Act
    b=b%c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Mod, mod_uint_eq){
    //Arrange
    std::vector<uint64_t> a = {102,0};
    MyBigUint<128> b(a);
    a =  {0,0};
    MyBigUint<128> ans(a);
    uint64_t c=102;

    //Act
    b=b%c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Mod, mod_uint_one){
    //Arrange
    std::vector<uint64_t> a = {102,0};
    MyBigUint<128> b(a);
    MyBigUint<128> ans(a);
    uint64_t c=1;

    //Act
    b=b%c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Mod, mod_uint_z){
    //Arrange
    std::vector<uint64_t> a = {7,1};
    MyBigUint<128> b(a);
    uint64_t c=0;

    //Act

    //Assert
    EXPECT_THROW(b%c,std::exception);
}

TEST(Mod, mod_bint){
    //Arrange
    std::vector<uint64_t> a = {102,3};
    MyBigUint<128> b(a);
    a =  {97,1};
    MyBigUint<128> ans(a);
    a = {100,1};
    MyBigUint<128> c(a);

    //Act
    b=b%c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}


TEST(Mod, mod_bint_eq){
    //Arrange
    std::vector<uint64_t> a = {2,0,3};
    MyBigUint<256> b(a);
    MyBigUint<256> c(a);
    a = {0,0,0};
    MyBigUint<256> ans(a);
    
    
    //Act
    b=b%c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Mod, mod_bint_gt){
    //Arrange
    std::vector<uint64_t> a = {2,0,3};
    MyBigUint<256> b(a);
    a = {5,0,3};
    MyBigUint<256> c(a);
    a = {3,0,0};
    MyBigUint<256> ans(a);
    
    
    //Act
    b=b%c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Mod, mod_bint_one){
    //Arrange
    std::vector<uint64_t> a = {2,0,3};
    MyBigUint<256> b(a);
    MyBigUint<256> ans(a);
    a = {1,0,0};
    MyBigUint<256> c(a);

  
    //Act
    b=b%c;   
    //Assert
    ASSERT_EQ(b.getNumber(),ans.getNumber());
}

TEST(Mod, mod_bint_z){
    //Arrange
    std::vector<uint64_t> a = {7,1};
    MyBigUint<128> b(a);
    a={0,0};
    MyBigUint<128> c(a);

    //Act

    //Assert
    EXPECT_THROW(b%c,std::exception);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}