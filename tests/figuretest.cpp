#include "gtest/gtest.h"
#include "../src/Figure/figure.h"
#include <QString>
#include <fstream>
#include <cstdio>

TEST(FigureAddPoint, ValidFormat) {
  Figure f;
  auto err = f.AddPoint("1,2");

  EXPECT_EQ(err, Figure::Error::NO_ERROR);
  EXPECT_EQ(f.GetPoints().size(), 1);
  EXPECT_EQ(f.GetPoints()[0].x, 1);
  EXPECT_EQ(f.GetPoints()[0].y, 2);

  err = f.AddPoint("  1,   2");

  ASSERT_EQ(err, Figure::Error::NO_ERROR);
  ASSERT_EQ(f.GetPoints().size(), 2);
  EXPECT_EQ(f.GetPoints()[1].x, 1);
  EXPECT_EQ(f.GetPoints()[1].y, 2);
}

TEST(FigureAddPoint, InvalidFormat) {
    Figure f;

    auto err = f.AddPoint("1");
    EXPECT_EQ(err, Figure::Error::FORMAT_ERROR);

    err = f.AddPoint("1,");
    EXPECT_EQ(err, Figure::Error::FORMAT_ERROR);

    err = f.AddPoint(",1");
    EXPECT_EQ(err, Figure::Error::FORMAT_ERROR);

    err = f.AddPoint(",");
    EXPECT_EQ(err, Figure::Error::FORMAT_ERROR);

    err = f.AddPoint("1,,1");
    EXPECT_EQ(err, Figure::Error::FORMAT_ERROR);

    err = f.AddPoint("");
    EXPECT_EQ(err, Figure::Error::FORMAT_ERROR);

    err = f.AddPoint("  ");
    EXPECT_EQ(err, Figure::Error::FORMAT_ERROR);

    EXPECT_EQ(f.GetPoints().size(), 0);
}

TEST(FigureAddPoint, NeedlessPoint) {
    Figure f;
    auto err = f.AddPoint("1, 1");
    EXPECT_EQ(err, Figure::Error::NO_ERROR);
    err = f.AddPoint("2, 2");
    EXPECT_EQ(err, Figure::Error::NO_ERROR);
    err = f.AddPoint("3, 3");
    EXPECT_EQ(err, Figure::Error::NO_ERROR);
    ASSERT_EQ(f.GetPoints().size(), 2);
    EXPECT_EQ(f.GetPoints()[1].x, 3);
    EXPECT_EQ(f.GetPoints()[1].y, 3);
}

TEST(FigureReadFromFile, FileNotExists) {
    Figure f;
    auto err = f.ReadFromFile("");
    EXPECT_EQ(err, Figure::Error::OPEN_FILE_ERROR);
}

TEST(FigureReadFromFile, EmptyFile) {
    std::ofstream file("input");
    Figure f;
    auto err = f.ReadFromFile("input");
    ASSERT_EQ(err, Figure::Error::NO_ERROR);
    EXPECT_EQ(f.GetPoints().size(), 0);
    file.close();
    std::remove("input");
}

TEST(FigureReadFromFile, NotEmptyFile) {
    std::ofstream file("input");
    file << "1, 1\n2, 2\n 3, 3\n4,4";
    file.close();
    Figure f;
    auto err = f.ReadFromFile("input");
    ASSERT_EQ(err, Figure::Error::NO_ERROR);
    ASSERT_EQ(f.GetPoints().size(), 2);
    EXPECT_EQ(f.GetPoints()[0].x, 1);
    EXPECT_EQ(f.GetPoints()[0].y, 1);
    EXPECT_EQ(f.GetPoints()[1].x, 4);
    EXPECT_EQ(f.GetPoints()[1].y, 4);
    std::remove("input");
}

TEST(Save, NotEmptyFigure) {
    Figure f;
    f.AddPoint("1,1");
    auto err = f.Save("saved");
    EXPECT_EQ(err, Figure::Error::NO_ERROR);
    std::ifstream file("saved");
    ASSERT_TRUE(file.is_open());
    std::string str;
    std::getline(file, str);
    file.close();
    EXPECT_EQ(str, "1, 1");
    std::remove("saved");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
