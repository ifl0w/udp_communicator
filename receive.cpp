#include <iostream>
#include <chrono>
#include <thread>
#include "udp_lib_switcher.hpp"
#include "msg_A.hpp"
#include "observed_msg.hpp"

int main()
{

	udp::UDPLib<ObservedMsg> client("192.168.0.210", 60000); // IP: Controller PC

	client.udp_bind();

	ObservedMsg msg;

	const int sleep_time = 1; // [msec]

	std::cout << "Receive every " << sleep_time / 1000.0 << " seconds" << std::endl;

	while (1)
	{
		if (client.udp_receive(&msg))
		{
			std::cout << "Receive_time[s] : " << msg.time_counter / 1000.0 << std::endl;
			std::cout << "Receive_speed : " << msg.ego_vehicle_speed << std::endl;
			std::cout << "Receive_x_g : " << msg.ego_vehicle_pose_x_g << std::endl;

			// std::cout << "Receive_type: " << msg.type << std::endl;
			// std::cout << "Receive_x: " << msg.x << std::endl;
		}
		else
		{
			std::cout << "Not receive new msg yet." << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	return 0;
}