#pragma once

#include <neptune/Neptune.h>

namespace Tasks {
	class LogicController : public Neptune::Kernel::Task {
	public:
		LogicController(void);

		void TaskStep(void);
	};
}