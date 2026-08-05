// ============================
// Dumped by: proohio
// Website: https://proohio.xyz
// Version: version-145f189a6a974303
// Scan Time: 2.257 seconds
// ============================

#pragma once
#include <windows.h>

struct lua_State;

#define REBASE(x) (x + (uintptr_t)(GetModuleHandle(nullptr)))

namespace Update {
    const uintptr_t Print = REBASE(0x4C27BF0); // "Current identity is %d"
    const uintptr_t ScriptContextResume = REBASE(0x1E21510); // "Can't resume script in this context"
    const uintptr_t GetIdentity = REBASE(0x4C2CE10); // "Current identity is %d"
    const uintptr_t GetIdentityStructure = REBASE(0x55160E0); // "Current identity is %d"
    const uintptr_t IdentityPointer = REBASE(0x8392B28); // "Current identity is %d"
    const uintptr_t GetGlobalState = REBASE(0x1D56360); // "Script Start"
    const uintptr_t GetCapabilities = REBASE(0x4C2D260); // "Script Start"
    const uintptr_t GetFFlag = REBASE(0x516C650); // "[FLog::ResetPlaceFilters] ParseAndSetFilterValue saving %s = %s for %lld" go to 2nd if statement that has func all with a1 == a1 of xref func
    const uintptr_t SetFFlag = REBASE(0x5172100); // "[FLog::FastLogValueChanged] Setting variable {}" xref func
    const uintptr_t TaskDefer = REBASE(0x1E95640); // "task.defer is not available for AuroraScripts" xref func
    const uintptr_t loadsafe = REBASE(0x4B6ECE0); // "not enough memory" look the xrefs
    const uintptr_t OpcodeLookupTable = REBASE(0x639F7B0); // "inside loadsafe"
    const uintptr_t luaH_dummynode = REBASE(0x6BC02C8); // "{\"type\":\"table\",\"cat\":%d,\"size\":%d", should be the pointer around this string
    const uintptr_t luaO_nilobject = REBASE(0x6BC0438); // use lua_unref method to get this
    const uintptr_t luau_execute = REBASE(0x4B7B430); // "cannot resume dead coroutine"
    const uintptr_t luaD_throw = REBASE(0x4B68390); // "Attempt to load a function from a different Lua VM"
    const uintptr_t luaC_step = REBASE(0x4B6CD20); // First function call in lua_newthread
    const uintptr_t FireTouchInterest = REBASE(0x2B25900); // "new overlap in different world" look for 3 same addys at return values
    const uintptr_t FireProximityPrompt = REBASE(0x26E9EC0); // "proximityPromptOnHeartbeat" look in previous dumps
    const uintptr_t FireRightMouseClick = REBASE(0x26AE550);
    const uintptr_t FireLeftMouseClick = REBASE(0x26ADEE0);
    const uintptr_t FireMouseHoverLeave = REBASE(0x26AE2E0);
    const uintptr_t FireMouseHoverEnter = REBASE(0x26AE0F0);
    const uintptr_t LuaVMLoad = REBASE(0x1D9FF00); // "Unexpected type in script compilation cache."
    const uintptr_t CastArgs = REBASE(0x1D370E0); // "Max lua stack size reached"
    const uintptr_t DisconnectConnect = REBASE(0x1D5DA50); // "Function Connection.Disconnect is not safe to call in parallel"
    const uintptr_t KTable = REBASE(0x85A7390); // "Trying to call method on object of type: `%s` with incorrect arguments."
    const uintptr_t InstanceBridgePush = REBASE(0x1D48CA0); // "InvalidInstance"
    const uintptr_t HashLookup = REBASE(0x5079D10); // "slotId"
    const uintptr_t GetProperty = REBASE(0xC8ACA0); // "OnServerEvent"
    const uintptr_t CurrentThreadIdentifier = REBASE(0xACEB60); // "Function being compared to where you found WriteLock"
    const uintptr_t GetCurrentThreadId = REBASE(0x5123F60); // "AppQoSInstance"
    const uintptr_t GetVMState = REBASE(0x1DEB700);
    const uintptr_t GetCurrentState = REBASE(0x64AA50);
    const uintptr_t TaskSchedulerPointer = REBASE(0x84A58E0); // "TaskScheduler::Job:" + jobs
    const uintptr_t FakeDataModelPointer = REBASE(0x7E26978); // "inApp"
    const uintptr_t FlogDataBank = REBASE(0x89FBDE8); // "GameLdrPerformanceCheckLimit" 1st function call -> first arguement of the first function call

    namespace External {
        const uintptr_t ResumeFacet = 0x7D0; // Check references of ScriptContextResume
        const uintptr_t RequireBypass = 0x800 + 0x1D0; // "Cannot require a non-RobloxScript module from a RobloxScript"
        const uintptr_t Primitive = 0x128; // "All parts passed to ArePartsTouchingOthers must be in the WorldRoot"
        const uintptr_t Overlap = 0x1F0; // "All parts passed to ArePartsTouchingOthers must be in the WorldRoot"
        const uintptr_t WriteLock = 0x658; // "dm = {}, context = {}, this = {}" | look for 2nd function call inside of if statement and in there a1 = datamodel
        const uintptr_t JobStart = 0xC8; // "TaskScheduler::Job:" + jobs
        const uintptr_t JobEnd = 0xD0; // "TaskScheduler::Job:" + jobs
        const uintptr_t JobName = 0x18; // "TaskScheduler::Job:" + jobs
        const uintptr_t MaxFPS = 0xB0; // "TaskScheduler::Job:" + jobs
        const uintptr_t RealDataModel = 0x1D0; // "From RequireBypass"
        const uintptr_t ModuleScriptByteCode = 0x138;
        const uintptr_t Name = 0x98;
        const uintptr_t ChildrenStart = 0x70;
        const uintptr_t ChildrenEnd = 0x8;
        const uintptr_t Parent = 0x68;
        const uintptr_t ClassDescriptor = 0x18;
        const uintptr_t ClassName = 0x8;
        const uintptr_t PlaceId = 0x190;
        const uintptr_t GameId = 0x188;
        const uintptr_t CreatorId = 0x180;
        const uintptr_t GameLoaded = 0x578;
        const uintptr_t JobId = 0x120;
        const uintptr_t ScriptContext = 0x440;
        const uintptr_t LocalScriptByteCode = 0x190;
        const uintptr_t ByteCodeSize = 0x20;
        const uintptr_t ByteCodePointer = 0x10;
    }
}
