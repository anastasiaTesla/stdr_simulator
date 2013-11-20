/******************************************************************************
   STDR Simulator - Simple Two DImensional Robot Simulator
   Copyright (C) 2013 STDR Simulator
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
   
   Authors : 
   * Manos Tsardoulias, etsardou@gmail.com
   * Aris Thallas, aris.thallas@gmail.com
   * Chris Zalidis, zalidis@gmail.com 
******************************************************************************/

#include <stdr_robot/spawn_robot.h>

namespace stdr_robot {
	
SpawnRobot::SpawnRobot() 
  : _spawnRobotClient("stdr_server/spawn_robot", true)
{
}

stdr_msgs::RobotIndexedMsg SpawnRobot::spawnNewRobot(const stdr_msgs::RobotMsg msg) {
	
	stdr_msgs::SpawnRobotGoal goal;
	goal.description = msg;
		
	while (!_spawnRobotClient.waitForServer(ros::Duration(1)) && ros::ok()) {
		ROS_WARN("Could not find stdr_server/spawn_robot action, is it running??");
	}
	
	_spawnRobotClient.sendGoal(goal);
	
	bool success = _spawnRobotClient.waitForResult(ros::Duration(10));
	
	if (!success) {
		throw ConnectionException("Could not spawn robot...");
	}
	
	ROS_INFO("New robot spawned successfully, with name %s.", _spawnRobotClient.getResult()->indexedDescription.name.c_str());
	
	return _spawnRobotClient.getResult()->indexedDescription;
	
}	
	
}
