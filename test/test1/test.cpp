#include <gtest/gtest.h>

#include <mrs_uav_testing/test_generic.h>

class Tester : public mrs_uav_testing::TestGeneric {

public:
  bool test();

  Tester();

  mrs_lib::ServiceClientHandler<std_srvs::Trigger> sch_start_;
};

Tester::Tester() : mrs_uav_testing::TestGeneric() {

  // your node handle
  // this->nh_ 

  // | --------------------- loading params --------------------- |

  /* this->pl_->loadParam("custom_config", variable); */

  sch_start_ = mrs_lib::ServiceClientHandler<std_srvs::Trigger>(nh_, "/uav1/control_manager/pes");
}

bool Tester::test() {

  // --------------------------------------------------------------
  // |                   obtain the UAV handlers                  |
  // --------------------------------------------------------------

  std::shared_ptr<mrs_uav_testing::UAVHandler> uh1;
  std::shared_ptr<mrs_uav_testing::UAVHandler> uh2;
  std::shared_ptr<mrs_uav_testing::UAVHandler> uh3;

  {
    auto [uhopt, message] = getUAVHandler("uav1");

    if (!uhopt) {
      ROS_ERROR("[%s]: Failed obtain handler for uav1: '%s'", ros::this_node::getName().c_str(), message.c_str());
      return false;
    }

    uh1 = uhopt.value();
  }

  {
    auto [uhopt, message] = getUAVHandler("uav2");

    if (!uhopt) {
      ROS_ERROR("[%s]: Failed obtain handler for uav2: '%s'", ros::this_node::getName().c_str(), message.c_str());
      return false;
    }

    uh2 = uhopt.value();
  }

  {
    auto [uhopt, message] = getUAVHandler("uav3");

    if (!uhopt) {
      ROS_ERROR("[%s]: Failed obtain handler for uav3: '%s'", ros::this_node::getName().c_str(), message.c_str());
      return false;
    }

    uh3 = uhopt.value();
  }

  // --------------------------------------------------------------
  // |                      activate the UAVs                     |
  // --------------------------------------------------------------

  {
    auto [success, message] = uh1->activateMidAir();

    if (!success) {
      ROS_ERROR("[%s]: uav1 midair activation failed with message: '%s'", ros::this_node::getName().c_str(), message.c_str());
      return false;
    }
  }

  {
    auto [success, message] = uh2->activateMidAir();

    if (!success) {
      ROS_ERROR("[%s]: uav2 midair activation failed with message: '%s'", ros::this_node::getName().c_str(), message.c_str());
      return false;
    }
  }

  {
    auto [success, message] = uh3->activateMidAir();

    if (!success) {
      ROS_ERROR("[%s]: uav3 midair activation failed with message: '%s'", ros::this_node::getName().c_str(), message.c_str());
      return false;
    }
  }

  // --------------------------------------------------------------
  // |                       DO YOUR STUFF                        |
  // --------------------------------------------------------------

  // e.g., call your services

  {
    std_srvs::Trigger srv;

    if (!sch_start_.call(srv)) {
      
      ROS_ERROR("[%s]: failed to call my service, oh no", ros::this_node::getName().c_str());
    }
  }

  // it might take some time
  this->sleep(10.0);

  // --------------------------------------------------------------
  // |                       FINISH THE TEST                      |
  // --------------------------------------------------------------
  return true;
}


TEST(TESTSuite, test) {

  Tester tester;

  bool result = tester.test();

  if (result) {
    GTEST_SUCCEED();
  } else {
    GTEST_FAIL();
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {

  ros::init(argc, argv, "test");

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
