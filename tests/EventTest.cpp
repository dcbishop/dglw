#include <gtest/gtest.h>

#include <dglw.hpp>
#include <Applications/Events.hpp>

#ifdef USE_QT
#include <Applications/QTApplication.hpp>
#endif

#ifdef USE_GLFW
#include <Applications/GLFWApplication.hpp>
#endif

using namespace dglw;

TEST(Sanity, Basic_Sanity_Check) {
   EXPECT_EQ(true, true);
}

TEST(Events, MouseButton) {
   MouseButton mb1 {2};
   ASSERT_EQ(mb1.getButtonNumber(), 2);
   mb1.setButtonNumber(1);
   ASSERT_EQ(mb1.getButtonNumber(), 1);
   MouseButton mb2 {1};
   ASSERT_EQ(mb1.getButtonNumber(), mb2.getButtonNumber());
   ASSERT_TRUE(mb1 == mb2);
   ASSERT_FALSE(mb1 != mb2);
   mb2.setButtonNumber(3);
   ASSERT_FALSE(mb1 == mb2);
   ASSERT_TRUE(mb1 != mb2);
}

class MouseCoordTest : public ::testing::Test {
   protected:
      MouseCoord mc0 {1, 1};
      MouseCoord mc1 {100, 200};
      MouseCoord mc2 {100, 200};
      MouseCoord mc3 {640, 480};
      MouseCoord mc4 {100, 480};
      MouseCoord mc5 {100, 1};
      MouseCoord mc6 {1, 480};
      MouseCoord mc7 {640, 1};
};

TEST_F(MouseCoordTest, MouseCoord_Construction) {
   ASSERT_EQ(mc1.getX(), 100);
   ASSERT_EQ(mc1.getY(), 200);
}

TEST_F(MouseCoordTest, MouseCoord_Equals) {
   EXPECT_TRUE(mc1 == mc2);
   EXPECT_FALSE(mc1 == mc3);
   EXPECT_FALSE(mc1 == mc4);
}

TEST_F(MouseCoordTest, MouseCoord_NotEquals) {
   EXPECT_FALSE(mc1 != mc2);
   EXPECT_TRUE(mc1 != mc3);
   EXPECT_TRUE(mc1 != mc4);
}

TEST_F(MouseCoordTest, MouseCoord_LessThan) {
   EXPECT_TRUE(mc1 < mc3);
   EXPECT_FALSE(mc1 < mc4);
   EXPECT_FALSE(mc6 < mc2);
}

TEST_F(MouseCoordTest, MouseCoord_GreatorThan) {
   EXPECT_TRUE(mc1 > mc0);
   EXPECT_FALSE(mc1 > mc3);
   EXPECT_FALSE(mc7 > mc2);
}

TEST_F(MouseCoordTest, MouseCoord_LessThanOrEquals) {
   EXPECT_TRUE(mc1 <= mc2);
   EXPECT_FALSE(mc1 <= mc0);
   EXPECT_FALSE(mc4 <= mc2);
}

TEST_F(MouseCoordTest, MouseCoord_GreatorThanOrEquals) {
   EXPECT_TRUE(mc1 >= mc2);
   EXPECT_FALSE(mc1 >= mc3);
   EXPECT_FALSE(mc5 >= mc4);
}

#ifdef USE_QT
TEST(Applications, QTApplication) {
   int argc = 0;
   char** argv = NULL;

   QTApplication qapp;
   qapp.setSize(200,100);
   EXPECT_EQ(qapp.getWidth(), 200);
   EXPECT_EQ(qapp.getHeight(), 100);

   const std::string title {"Test Title"};
   qapp.setTitle(title);
}
#endif /* USE_QT */

#ifdef USE_GLFW
TEST(Application, GLFWApplication) {
   GLFWApplication gapp;
   gapp.setSize(200, 100);
   EXPECT_EQ(gapp.getWidth(), 200);
   EXPECT_EQ(gapp.getHeight(), 100);

   const std::string title {"Test Title"};
   gapp.setTitle(title);
}
#endif /* USE_GLFW */
