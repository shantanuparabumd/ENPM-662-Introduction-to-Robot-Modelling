
#include <gazebo/physics/Model.hh>
#include <gazebo/physics/Joint.hh>
#include <gazebo/physics/Link.hh>
#include <drone_plugin/drone_plugin_.hpp>
#include <gazebo_ros/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include "drone_plugin/msg/motor_speed.hpp"

#include <ignition/math/Pose3.hh>
#include <ignition/math/Vector3.hh>
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <gazebo/common/Console.hh>
#include <tf2_ros/transform_broadcaster.h>
#include <memory>

namespace gazebo{


class DronePluginPrivate
{
  /**
   * @brief Class to hold data members and methods for plugin
   * 
   */
public:
  /// Connection to world update event. Callback is called while this is alive.
  gazebo::event::ConnectionPtr update_connection_;

  /// Node for ROS communication.
  gazebo_ros::Node::SharedPtr ros_node_;

  gazebo::physics::ModelPtr _model;



  /// Publisher to publsih the pose to /odom topic
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr droneOdomPublisher;

  /// Publisher to publsih the velocity to /velocity topic
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocityPublisher;

  /// Publisher to publsih the velocity to /velocity topic
  rclcpp::Subscription<drone_plugin::msg::MotorSpeed>::SharedPtr motor_speed_subscriber;

  /// TF Broadcaster to pubshil the transform between 2 frames
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

  // Callback function to perform task with each iteration in Gazebo
  void OnUpdate();

  void publishDronePose() ;

  void onMotorSpeedsMsg(const drone_plugin::msg::MotorSpeed::SharedPtr msg);

  void updateThrust() ;

  double calculateThrust(double w) ;

  double calculateTorque(double w) ;



    //   Variable
  double _rate;
  bool _publish_tf;
  double _rotor_thrust_coeff;
  double _rotor_torque_coeff;

  gazebo::physics::LinkPtr baseLink;

  std::string base_link_name;
  std::string world_frame_name;

  std::shared_ptr<drone_plugin::msg::MotorSpeed> _motor_speed_msg;

};


/**
 * @brief Construct a new Drone Plugin:: Drone Plugin object
 * 
 */
DronePlugin::DronePlugin()
: impl_(std::make_unique<DronePluginPrivate>())
{
  std::cout << "Starting drone_plugin" << std::endl;
}

/**
 * @brief Destroy the Drone Plugin:: Drone Plugin object
 * 
 */
DronePlugin::~DronePlugin()
{
    std::cout << "Closing drone_plugin" << std::endl;
}

/**
 * @brief Load the SDF/URDF model of the robot and access the links/joints.
 * 
 * @param model 
 * @param sdf 
 */
void DronePlugin::Load(gazebo::physics::ModelPtr model, sdf::ElementPtr sdf)
{   


    impl_->_model = model;
    impl_->ros_node_ = gazebo_ros::Node::Get(sdf);
    impl_->droneOdomPublisher = impl_->ros_node_->create_publisher<geometry_msgs::msg::PoseStamped>("/drone_pose", 10);
    impl_->velocityPublisher = impl_->ros_node_->create_publisher<geometry_msgs::msg::Twist>("/drone_velocity", 10);
    
    // Create subscriber
    impl_->motor_speed_subscriber = impl_->ros_node_->create_subscription<drone_plugin::msg::MotorSpeed>(
    "/motor_speed", 10, 
    std::bind(&DronePluginPrivate::onMotorSpeedsMsg, impl_.get(), std::placeholders::_1));


    
    impl_->tf_broadcaster_ =std::make_unique<tf2_ros::TransformBroadcaster>(impl_->ros_node_);

    /// Check for the frame element in the URDF
    if (sdf->HasElement("drone_frame")) {
        std::cout  << "Reference link  found!" << std::endl;
        impl_->base_link_name  = sdf->GetElement("drone_frame")->Get<std::string>();

        std::cout  << "Base link  name: " <<impl_->base_link_name<< std::endl;
    } else {
        // Handle the case where the element doesn't exist
        std::cerr << "Reference link not found!" << std::endl;
        return;
    }
    // Access the base link of the model .
    impl_->baseLink = model->GetLink(impl_->base_link_name);
    

    // Check if the base link exists.
    if (!impl_->baseLink) {
        std::cerr  << "Base link not found!" << std::endl;
        return;
    }

    if (sdf->HasElement("updateRate")) {
      impl_->_rate = sdf->GetElement("updateRate")->Get<double>();
    } else {
      impl_->_rate = 100.0;
    }
   
    if (sdf->HasElement("publishTf")) {
      impl_->_publish_tf = sdf->GetElement("publishTf")->Get<bool>();
    } else {
      impl_->_publish_tf = true;
    }
   
    if (sdf->HasElement("rotorThrustCoeff")) {
      impl_->_rotor_thrust_coeff =
         sdf->GetElement("rotorThrustCoeff")->Get<double>();
    } else {
      impl_->_rotor_thrust_coeff = 0.00025;
    }
   
    if (sdf->HasElement("rotorTorqueCoeff")) {
      impl_->_rotor_torque_coeff =
        sdf->GetElement("rotorTorqueCoeff")->Get<double>();
    } else {
      impl_->_rotor_torque_coeff = 0.0000074;
    }
    
    // Set up a Gazebo update callback function.
    impl_->update_connection_ = gazebo::event::Events::ConnectWorldUpdateBegin(
        std::bind(&DronePluginPrivate::OnUpdate, impl_.get()));

    if (impl_->update_connection_) {
        std::cout << "Successfully connected to the world update event!" << std::endl;
    } else {
        std::cerr << "Failed to connect to the world update event!" << std::endl;
    }

}

void DronePluginPrivate::onMotorSpeedsMsg(const drone_plugin::msg::MotorSpeed::SharedPtr msg)  {
    _motor_speed_msg = msg;
}



void DronePluginPrivate::publishDronePose() {

    geometry_msgs::msg::PoseStamped odometryMessage;
    // Get the current pose of the base link.
    ignition::math::Pose3 baseLinkPose = baseLink->WorldPose();

    // Get the linear and angular velocities of the base link.
    ignition::math::Vector3d linearVelocity = baseLink->WorldLinearVel();
    ignition::math::Vector3d angularVelocity = baseLink->WorldAngularVel();

    // Extract position and orientation information
    odometryMessage.header.stamp = ros_node_->now();
    odometryMessage.header.frame_id = base_link_name;  
    odometryMessage.pose.position.x = baseLinkPose.Pos().X();
    odometryMessage.pose.position.y = baseLinkPose.Pos().Y();
    odometryMessage.pose.position.z = baseLinkPose.Pos().Z();
    odometryMessage.pose.orientation.x = baseLinkPose.Rot().X();
    odometryMessage.pose.orientation.y = baseLinkPose.Rot().Y();
    odometryMessage.pose.orientation.z = baseLinkPose.Rot().Z();
    odometryMessage.pose.orientation.w = baseLinkPose.Rot().W();

    // Create and set linear and angular velocities in the Twist message
    geometry_msgs::msg::Twist twist;

    twist.linear.x = linearVelocity.X();
    twist.linear.y = linearVelocity.Y();
    twist.linear.z = linearVelocity.Z();
    twist.angular.x = angularVelocity.X();
    twist.angular.y = angularVelocity.Y();
    twist.angular.z = angularVelocity.Z();

    

    velocityPublisher->publish(twist);

    droneOdomPublisher->publish(odometryMessage);
 
    if (_publish_tf) {
        geometry_msgs::msg::TransformStamped t;

        // Read message content and assign it to
        // corresponding tf variables
        t.header.stamp = ros_node_->now();
        t.header.frame_id = world_frame_name;
        t.child_frame_id = base_link_name;

        t.transform.translation.x = baseLinkPose.Pos().X();
        t.transform.translation.y = baseLinkPose.Pos().Y();
        t.transform.translation.z = baseLinkPose.Pos().Z();
        t.transform.rotation.x = baseLinkPose.Rot().X();
        t.transform.rotation.y = baseLinkPose.Rot().Y();
        t.transform.rotation.z = baseLinkPose.Rot().Z();
        t.transform.rotation.w = baseLinkPose.Rot().W();

        // Send the transformation
        tf_broadcaster_->sendTransform(t);
    }
}


/**
 * @brief This method is called at every time interval in Gazebo
 * 
 */
void DronePluginPrivate::OnUpdate()
{   
    publishDronePose();
    updateThrust();

}



void DronePluginPrivate::updateThrust() {
  
  if(!_motor_speed_msg){
    
  }
  else{
    int n = _motor_speed_msg->name.size();
  for (int i = 0; i < n; ++i) {
    double thrust = calculateThrust(_motor_speed_msg->velocity[i]);
    double torque = calculateTorque(_motor_speed_msg->velocity[i]);
    gazebo::physics::LinkPtr link = _model->GetLink(_motor_speed_msg->name[i]);
    if (link != NULL) {
      link->AddLinkForce(ignition::math::Vector3d(0, 0, thrust));
      link->AddRelativeTorque(ignition::math::Vector3d(0, 0, torque));
    }
  }
  }

 
  
}


double DronePluginPrivate::calculateThrust(double w) {
  double thrust = _rotor_thrust_coeff * w * w;
  return thrust;
}

double DronePluginPrivate::calculateTorque(double w) {
  double torque = copysign(_rotor_torque_coeff * w * w, w);
  return torque;
}


// Register this plugin with the simulator
GZ_REGISTER_MODEL_PLUGIN(DronePlugin)

}