# Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
# SPDX-License-Identifier: MIT
#
# @file AgesaModuleUtPkg.dsc.inc
#

!include UnitTestFrameworkPkg/UnitTestFrameworkPkgHost.dsc.inc

[Defines]
  #

[LibraryClasses.common.HOST_APPLICATION]

  UtBaseLib                       | AmdCommonPkg/Test/UnitTest/Library/UtBaseLib/UtBaseLib.inf
  UtJsonLib                       | AmdCommonPkg/Test/UnitTest/Library/UtJsonLib/UtJsonLib.inf

[BuildOptions]
  MSFT:*_*_*_CC_FLAGS  = -D AMD_UNIT_TEST
  GCC:*_*_*_CC_FLAGS   = -D AMD_UNIT_TEST
  XCODE:*_*_*_CC_FLAGS = -D AMD_UNIT_TEST

[PcdsFixedAtBuild]
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x16
