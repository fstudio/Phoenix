#

LINK=link
CC=cl
AR=lib

INCDIR= -I../../include
CXXFLAGS=-TP -c  -EHsc  -W3  -Zc:forScope -Zc:wchar_t -D_CRT_SECURE_NO_DEPRECATE \
-D_CRT_NONSTDC_NO_DEPRECATE -O2 -MT $(INCDIR)
CFLAGS=-TC -c -O2 -W3  -Zc:wchar_t -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -MT $(INCDIR)

CXXOBJS=  APFloat.obj\
  APInt.obj\
  APSInt.obj\
  ARMBuildAttrs.obj\
  ARMWinEH.obj\
  Allocator.obj\
  BlockFrequency.obj\
  BranchProbability.obj\
  circular_raw_ostream.obj\
  COM.obj\
  CommandLine.obj\
  Compression.obj\
  ConvertUTFWrapper.obj\
  CrashRecoveryContext.obj\
  DataExtractor.obj\
  DataStream.obj\
  Debug.obj\
  DeltaAlgorithm.obj\
  DAGDeltaAlgorithm.obj\
  Dwarf.obj\
  ErrorHandling.obj\
  FileUtilities.obj\
  FileOutputBuffer.obj\
  FoldingSet.obj\
  FormattedStream.obj\
  GraphWriter.obj\
  Hashing.obj\
  IntEqClasses.obj\
  IntervalMap.obj\
  IntrusiveRefCntPtr.obj\
  LEB128.obj\
  LineIterator.obj\
  Locale.obj\
  LockFileManager.obj\
  ManagedStatic.obj\
  MathExtras.obj\
  MemoryBuffer.obj\
  MemoryObject.obj\
  MD5.obj\
  Options.obj\
  PluginLoader.obj\
  PrettyStackTrace.obj\
  RandomNumberGenerator.obj\
  Regex.obj\
  ScaledNumber.obj\
  SmallPtrSet.obj\
  SmallVector.obj\
  SourceMgr.obj\
  SpecialCaseList.obj\
  Statistic.obj\
  StreamingMemoryObject.obj\
  StringExtras.obj\
  StringMap.obj\
  StringPool.obj\
  StringRef.obj\
  SystemUtils.obj\
  Timer.obj\
  ToolOutputFile.obj\
  Triple.obj\
  Twine.obj\
  Unicode.obj\
  YAMLParser.obj\
  YAMLTraits.obj\
  raw_os_ostream.obj\
  raw_ostream.obj\
  Atomic.obj\
  DynamicLibrary.obj\
  Errno.obj\
  Host.obj\
  Memory.obj\
  Mutex.obj\
  Path.obj\
  Process.obj\
  Program.obj\
  RWMutex.obj\
  SearchForAddressOfSpecialSymbol.obj\
  Signals.obj\
  TargetRegistry.obj\
  ThreadLocal.obj\
  Threading.obj\
  TimeValue.obj\
  Valgrind.obj\
  Watchdog.obj\
  
COBJS=  ConvertUTF.obj regcomp.obj  regerror.obj  regexec.obj  regfree.obj  regstrlcpy.obj

LIBRARYNAME=libSupport.lib


all:$(LIBRARYNAME)

$(LIBRARYNAME):  $(COBJS) $(CXXOBJS)
	$(AR) $(COBJS) $(CXXOBJS) -out:$@
	
APFloat.obj:APFloat.cpp
	$(CC) $(CXXFLAGS) -c  $**

APInt.obj:APInt.cpp
	$(CC) $(CXXFLAGS) -c  $**
	
APSInt.obj:APSInt.cpp
	$(CC) $(CXXFLAGS) -c  $**

ARMBuildAttrs.obj:ARMBuildAttrs.cpp
	$(CC) $(CXXFLAGS) -c $**
  
ARMWinEH.obj:ARMWinEH.cpp
	$(CC) $(CXXFLAGS) -c  $**

Allocator.obj:Allocator.cpp
	$(CC) $(CXXFLAGS) -c  $**
 
BlockFrequency.obj:BlockFrequency.cpp
	$(CC) $(CXXFLAGS) -c  $**
	
BranchProbability.obj:BranchProbability.cpp
	$(CC) $(CXXFLAGS) -c  $**

circular_raw_ostream.obj:circular_raw_ostream.cpp
	$(CC) $(CXXFLAGS) -c $**
 
COM.obj:COM.cpp
	$(CC) $(CXXFLAGS) -c $**
  
CommandLine.obj:CommandLine.cpp
	$(CC) $(CXXFLAGS) -c $**

Compression.obj:Compression.cpp
	$(CC) $(CXXFLAGS) -c $**

ConvertUTFWrapper.obj:ConvertUTFWrapper.cpp
	$(CC) $(CXXFLAGS) -c $**

CrashRecoveryContext.obj:CrashRecoveryContext.cpp
	$(CC) $(CXXFLAGS) -c $**

DataExtractor.obj:DataExtractor.cpp
	$(CC) $(CXXFLAGS) -c $**
	
DataStream.obj:DataStream.cpp
	$(CC) $(CXXFLAGS) -c $**

Debug.obj:Debug.cpp
	$(CC) $(CXXFLAGS) -c $**
	
DeltaAlgorithm.obj:DeltaAlgorithm.cpp
	$(CC) $(CXXFLAGS) -c $**
	
DAGDeltaAlgorithm.obj:DAGDeltaAlgorithm.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Dwarf.obj:Dwarf.cpp
	$(CC) $(CXXFLAGS) -c $**

ErrorHandling.obj:ErrorHandling.cpp
	$(CC) $(CXXFLAGS) -c $**
	
FileUtilities.obj:FileUtilities.cpp
	$(CC) $(CXXFLAGS) -c $**
	
FileOutputBuffer.obj:FileOutputBuffer.cpp
	$(CC) $(CXXFLAGS) -c $**
	
FoldingSet.obj:FoldingSet.cpp
	$(CC) $(CXXFLAGS) -c $**

FormattedStream.obj:FormattedStream.cpp
	$(CC) $(CXXFLAGS) -c $**
	
GraphWriter.obj:GraphWriter.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Hashing.obj:Hashing.cpp
	$(CC) $(CXXFLAGS) -c $**
	
IntEqClasses.obj:IntEqClasses.cpp
	$(CC) $(CXXFLAGS) -c $**
	
IntervalMap.obj:IntervalMap.cpp
	$(CC) $(CXXFLAGS) -c $**
	
IntrusiveRefCntPtr.obj:IntrusiveRefCntPtr.cpp
	$(CC) $(CXXFLAGS) -c $**
	
LEB128.obj:LEB128.cpp
	$(CC) $(CXXFLAGS) -c $**
	
LineIterator.obj:LineIterator.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Locale.obj:Locale.cpp
	$(CC) $(CXXFLAGS) -c $**
	
LockFileManager.obj:LockFileManager.cpp
	$(CC) $(CXXFLAGS) -c $**
	
ManagedStatic.obj:ManagedStatic.cpp
	$(CC) $(CXXFLAGS) -c $**
	
MathExtras.obj:MathExtras.cpp
	$(CC) $(CXXFLAGS) -c $**
	
MemoryBuffer.obj:MemoryBuffer.cpp
	$(CC) $(CXXFLAGS) -c $**
	
MemoryObject.obj:MemoryObject.cpp
	$(CC) $(CXXFLAGS) -c $**
	
MD5.obj:MD5.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Options.obj:Options.cpp
	$(CC) $(CXXFLAGS) -c $**
	
PluginLoader.obj:PluginLoader.cpp
	$(CC) $(CXXFLAGS) -c $**
	
PrettyStackTrace.obj:PrettyStackTrace.cpp
	$(CC) $(CXXFLAGS) -c $**
	
RandomNumberGenerator.obj:RandomNumberGenerator.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Regex.obj:Regex.cpp
	$(CC) $(CXXFLAGS) -c $**
	
ScaledNumber.obj:ScaledNumber.cpp
	$(CC) $(CXXFLAGS) -c $**
	
SmallPtrSet.obj:SmallPtrSet.cpp
	$(CC) $(CXXFLAGS) -c $**
	
SmallVector.obj:SmallVector.cpp
	$(CC) $(CXXFLAGS) -c $**
	
SourceMgr.obj:SourceMgr.cpp
	$(CC) $(CXXFLAGS) -c $**
	
SpecialCaseList.obj:SpecialCaseList.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Statistic.obj:Statistic.cpp
	$(CC) $(CXXFLAGS) -c $**
	
StreamingMemoryObject.obj:StreamingMemoryObject.cpp
	$(CC) $(CXXFLAGS) -c $**
	
StringExtras.obj:StringExtras.cpp
	$(CC) $(CXXFLAGS) -c $**
	
StringMap.obj:StringMap.cpp
	$(CC) $(CXXFLAGS) -c $**
	
StringPool.obj:StringPool.cpp
	$(CC) $(CXXFLAGS) -c $**
	
StringRef.obj:StringRef.cpp
	$(CC) $(CXXFLAGS) -c $**
	
SystemUtils.obj:SystemUtils.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Timer.obj:Timer.cpp
	$(CC) $(CXXFLAGS) -c $**
	
ToolOutputFile.obj:ToolOutputFile.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Triple.obj:Triple.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Twine.obj:Twine.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Unicode.obj:Unicode.cpp
	$(CC) $(CXXFLAGS) -c $**
	
YAMLParser.obj:YAMLParser.cpp
	$(CC) $(CXXFLAGS) -c $**
	
YAMLTraits.obj:YAMLTraits.cpp
	$(CC) $(CXXFLAGS) -c $**
	
raw_os_ostream.obj:raw_os_ostream.cpp
	$(CC) $(CXXFLAGS) -c $**
	
raw_ostream.obj:raw_ostream.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Atomic.obj:Atomic.cpp
	$(CC) $(CXXFLAGS) -c $**
	
DynamicLibrary.obj:DynamicLibrary.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Errno.obj:Errno.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Host.obj:Host.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Memory.obj:Memory.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Mutex.obj:Mutex.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Path.obj:Path.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Process.obj:Process.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Program.obj:Program.cpp
	$(CC) $(CXXFLAGS) -c $**
	
RWMutex.obj:RWMutex.cpp
	$(CC) $(CXXFLAGS) -c $**
	
SearchForAddressOfSpecialSymbol.obj:SearchForAddressOfSpecialSymbol.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Signals.obj:Signals.cpp
	$(CC) $(CXXFLAGS) -c $**
	
TargetRegistry.obj:TargetRegistry.cpp
	$(CC) $(CXXFLAGS) -c $**
	
ThreadLocal.obj:ThreadLocal.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Threading.obj:Threading.cpp
	$(CC) $(CXXFLAGS) -c $**
	
TimeValue.obj:TimeValue.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Valgrind.obj:Valgrind.cpp
	$(CC) $(CXXFLAGS) -c $**
	
Watchdog.obj:Watchdog.cpp
	$(CC) $(CXXFLAGS) -c $**
	
{.}.c.obj::
	$(CC) $(CFLAGS) $<

	
clean:
	-del /s /q *.obj *.lib >nul 2>nul
