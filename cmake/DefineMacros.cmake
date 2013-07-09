##############################################################################
# include cmake macros
##############################################################################

include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckIncludeFiles)
include(CheckSymbolExists)
include(CheckFunctionExists)
include(CheckLibraryExists)
include(CheckTypeSize)
include(CheckCSourceCompiles)
include(CheckCXXSourceCompiles)
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

include(FeatureSummary)

##############################################################################
# include coolfluid macros
##############################################################################

# TODO: change these macros to new format

include(macros/CFInstallTargets)
include(macros/CFInstallThirdPartyLibrary)
include(macros/CFVariables)
include(macros/CFSearchPaths)
include(macros/CFFindProjectFiles)
include(macros/CFLogToFile)
include(macros/CFCheckFileLength)
include(macros/CFSeparateSources)
include(macros/CFAddApp)
include(macros/CFAddTest)
include(macros/CFAddResources)
include(macros/CFAddCompilationFlags)
include(macros/CFDefinePlugin)
include(macros/GetDate)

# new format macros

include(macros/coolfluid3_add_library)
include(macros/coolfluid3_list_subdirs)
include(macros/coolfluid3_add_plugin)
