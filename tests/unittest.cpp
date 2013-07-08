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

TEST(Events, MouseCoord) {
   MouseCoord mc1 {1234, 5678};
   ASSERT_EQ(mc1.getX(), 1234);
   ASSERT_EQ(mc1.getY(), 5678);
   MouseCoord mc2 {1234, 5678};
   ASSERT_TRUE(mc1 == mc2);
   ASSERT_FALSE(mc1 != mc2);
   MouseCoord mc3 {10000, 10000};
   ASSERT_TRUE(mc1 < mc3);
   ASSERT_FALSE(mc1 > mc3);
   ASSERT_TRUE(mc1 <= mc2);
   ASSERT_TRUE(mc1 >= mc2);
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
