#pragma once

#include <BBScript.h>
#include <PhysicsMgr.h>
#include <PhysicsBody.h>

namespace PhysicsScripts {
void registerPhysicsType(sol::state& lua_state);
}