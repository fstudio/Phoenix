/*********************************************************************************************************
* LibOS.cc
* Note: Phoenix Container Library OS API
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Windows.h>

/*
Upcalls:
ExceptionDispatch(ExceptionInfo)
ThreadEntry()
Downcalls:
AsyncCancel(AsyncHandle)
AsyncPoll(AsyncHandle) -> Results
DebugStringPrint(Message)
EventClear(EventHandle)
EventSet(EventHandle)
ObjectClose(Handle)
ObjectsWaitAny(Count, Handles, Timeout) -> Index
ProcessExit(ExitCode)
StreamAttributesQueryByHandle(StreamHandle) -> Attribs
StreamFlush(StreamHandle)
StreamGetEvent(StreamHandle, EventId) -> EventHandle
StreamOpen(URI, Options) -> StreamHandle
StreamRead(StreamHandle, Off, Len, Buf) -> AsyncHandle
StreamWrite(StreamHandle, Off, Len, Buf) -> AsyncHandle
SystemTimeQuery() -> Time
ThreadCreate(Tcs) -> ThreadHandle
ThreadExit()
ThreadInterrupt(ThreadHandle)
ThreadYieldExecution()
VirtualMemoryCommit(Addr, Size, Prot)
VirtualMemoryFree(Addr, Size)
VirtualMemoryProtect(Addr, Size, Prot)
*/