/**
 * @file TestsSupplementaires.cpp
 *
 * @brief Tests unitaires supplementaires
 *
 * Nom: Bui, Phan Tung
 * Code permanent : BUIP26109708
 * Email : phan-tung.bui.1@ens.etsmtl.ca
 *
 */

#include <gtest/gtest.h>

#include "DenseStorage.h"
// Test operateur de setZero
TEST(TestsSupplementaires, Supp01)
{
    gti320::DenseStorage<int, gti320::Dynamic> buf(8);
    buf.setZero();
    for (int i = 0; i < buf.size(); i++) {
        EXPECT_EQ(buf[i], 0);
    }
}
// Test operateur de copie
TEST(TestsSupplementaires, Supp02)
{
    gti320::DenseStorage<int, gti320::Dynamic> buf(8);
    buf.setZero();
    gti320::DenseStorage<int, gti320::Dynamic> bufB(buf);
    EXPECT_NE(bufB.data(), buf.data());
    for (int i = 0; i < buf.size(); i++) {
        EXPECT_EQ(buf[i], bufB[i]);
    }
}

TEST(TestsSupplementaires, Supp03)
{

}

TEST(TestsSupplementaires, Supp04)
{

}

TEST(TestsSupplementaires, Supp05)
{

}

TEST(TestsSupplementaires, Supp06)
{

}

TEST(TestsSupplementaires, Supp07)
{

}

TEST(TestsSupplementaires, Supp08)
{

}

TEST(TestsSupplementaires, Supp09)
{

}

TEST(TestsSupplementaires, Supp10)
{

}
