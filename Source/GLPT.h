#pragma once

#include <neptune/Neptune.h>

#ifdef _DEBUG
#pragma comment (lib,"Neptune_Debug.lib")
#else
#pragma comment (lib,"Neptune_Release.lib")
#endif

#include "Tasks/TaskModule.h"
#include "Entities/EntityModule.h"
#include "Actions/ActionModule.h"
#include "Components/TemplateModule.h"

#include "Misc/ControlBind.h"
#include "Misc/ParamFetch.h"