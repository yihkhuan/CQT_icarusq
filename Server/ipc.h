#pragma once

#include <ipc/server.h>
#include <ipc/dac.h>

namespace ipc {
void init() {
	server.Get("/exit", [&](const httplib::Request& req, httplib::Response& res) {
		server.stop();
	});

	dac::init();

	server.listen("0.0.0.0", 8080);
}
}
