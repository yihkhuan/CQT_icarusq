#pragma once

#include <string>
#include <exception>

#include <icarusq/icarusq.h>
#include <ipc/server.h>



namespace ipc {
namespace adc {

void init() {
	// Sampling rate getter/setter
	ipc::server.Get("/adc/sampling_rate", [](const httplib::Request& req, httplib::Response& res) {
		unsigned long int sampling_rate = icarusq::device -> adc.get_sampling_rate();
		res.set_content(std::to_string(sampling_rate), "text/plain");
	});

	ipc::server.Post("/adc/sampling_rate", [](const httplib::Request& req, httplib::Response& res) {
		if (req.has_param("rate")) {
			std::string sampling_rate = req.get_param_value("rate");
			unsigned long int rate = std::stoi(sampling_rate);
			icarusq::device -> adc.set_sampling_rate(rate);
		} else {
			throw std::invalid_argument("Sampling rate not specified");
		}
	});

	// Delay setter/getter
	ipc::server.Get("/adc/delay", [](const httplib::Request& req, httplib::Response& res) {
		if (req.has_param("channel")) {
			std::string ch = req.get_param_value("channel");
			unsigned int channel = std::stoi(ch);
			unsigned int delay = icarusq::device -> adc[channel].get_delay();

			res.set_content(std::to_string(delay), "text/plain");
		} else{
			throw std::invalid_argument("Channel not specified");
		} 
	});

	ipc::server.Post("/adc/delay", [](const httplib::Request& req, httplib::Response& res) {
		if (req.has_param("delay") && req.has_param("channel")) {
			std::string delay = req.get_param_value("delay");
			std::string ch = req.get_param_value("channel")
			unsigned int Delay = std::stoi(delay);
			unsigned int channel = std ::stoi(ch);

			icarusq::device -> adc[channel].set_delay(Delay);
		} else {
			throw std::invalid_argument("Missing parameters");
		}//ask when to use a -> and when to use a .
	});
}

}
}
