#include "Base.h"
#include "ScriptController.h"
#include "lua_AIAgentListener.h"
#include "AIAgent.h"
#include "Base.h"
#include "Game.h"
#include "Node.h"
#include "Ref.h"

namespace gameplay
{

void luaRegister_AIAgentListener()
{
    const luaL_Reg lua_members[] = 
    {
        {"messageReceived", lua_AIAgentListener_messageReceived},
        {NULL, NULL}
    };
    const luaL_Reg* lua_statics = NULL;
    std::vector<std::string> scopePath;
    scopePath.push_back("AIAgent");

    ScriptUtil::registerClass("AIAgentListener", lua_members, NULL, lua_AIAgentListener__gc, lua_statics, scopePath);
}

static AIAgent::Listener* getInstance(lua_State* state)
{
    void* userdata = luaL_checkudata(state, 1, "AIAgentListener");
    luaL_argcheck(state, userdata != NULL, 1, "'AIAgentListener' expected.");
    return (AIAgent::Listener*)((ScriptUtil::LuaObject*)userdata)->instance;
}

int lua_AIAgentListener__gc(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA))
            {
                void* userdata = luaL_checkudata(state, 1, "AIAgentListener");
                luaL_argcheck(state, userdata != NULL, 1, "'AIAgentListener' expected.");
                ScriptUtil::LuaObject* object = (ScriptUtil::LuaObject*)userdata;
                if (object->owns)
                {
                    AIAgent::Listener* instance = (AIAgent::Listener*)object->instance;
                    SAFE_DELETE(instance);
                }
                
                return 0;
            }
            else
            {
                lua_pushstring(state, "lua_AIAgentListener__gc - Failed to match the given parameters to a valid function signature.");
                lua_error(state);
            }
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

int lua_AIAgentListener_messageReceived(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 2:
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA) &&
                (lua_type(state, 2) == LUA_TUSERDATA || lua_type(state, 2) == LUA_TTABLE || lua_type(state, 2) == LUA_TNIL))
            {
                // Get parameter 1 off the stack.
                AIMessage* param1 = ScriptUtil::getObjectPointer<AIMessage>(2, "AIMessage", false);

                AIAgent::Listener* instance = getInstance(state);
                bool result = instance->messageReceived(param1);

                // Push the return value onto the stack.
                lua_pushboolean(state, result);

                return 1;
            }
            else
            {
                lua_pushstring(state, "lua_AIAgentListener_messageReceived - Failed to match the given parameters to a valid function signature.");
                lua_error(state);
            }
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 2).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

}