/**
 * @file GetDeviceMapOnDieUt.c
 * @brief Unit tests for DfXGetDeviceMapOnDie
 *
 * Iterations:
 * -Default: Calls the DfXGetDeviceMapOnDie function and stores the returned value. 
 *           Verififes whether the returned value is as expected. 
 *
 */


#include <UtBaseLib.h>
#include <UtLogLib.h>

#include <OpenSIL\xUSL\DF\DfIp2Ip.h> // Can not recognize DfIp2Ip.h without relative path 
#include "DfXBaseFabricTopology.h"

// Fakes:
uint32_t
DfXFabricRegisterAccRead (
  uint32_t Socket,
  uint32_t Function,
  uint32_t Offset,
  uint32_t Instance
  )
{
    return 1; 
}

uint32_t DfGetNumberOfDiesOnSocket (void)
{
  return 1; 
}

uint32_t
DfGetHostBridgeSystemFabricID (
  uint32_t Socket,
  uint32_t Index
  )
{
  return 1;
}

const
AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *
DfFindDeviceTypeEntryInMap (
  FABRIC_DEVICE_TYPE  Type
  )
{
    static const DEVICE_IDS myIds[1] = {0}; // Mock device IDs.
    static const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP myMap[1] = 
    {
        {
            Ios,       // Device type.
            0,         // Device count.
            myIds      // Associated device IDs...
        }
    };
    return myMap; // Returns a mock device map for testing.
}


AMD_UNIT_TEST_STATUS
EFIAPI
TestPrerequisite (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  return AMD_UNIT_TEST_PASSED;
}

void
EFIAPI
TestBody (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  AMD_UNIT_TEST_FRAMEWORK *Ut = (AMD_UNIT_TEST_FRAMEWORK*) UtGetActiveFrameworkHandle ();
  const char* TestName        = UtGetTestName (Ut);
  const char* IterationName   = UtGetTestIteration (Ut);

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test started.", TestName, IterationName);
    
    if(strcmp(IterationName, "Default") == 0)
    {
        // Arrange
        const DEVICE_IDS   GenoaCsMap [] = 
        {
            {0x00000000, 0x00000000},
            {0x00000001, 0x00000001},
            {0x00000002, 0x00000002},
            {0x00000003, 0x00000003},
            {0x00000004, 0x00000004},
            {0x00000005, 0x00000005},
            {0x00000006, 0x00000006},
            {0x00000007, 0x00000007},
            {0x00000008, 0x00000008},
            {0x00000009, 0x00000009},
            {0x0000000A, 0x0000000A},
            {0x0000000B, 0x0000000B},
            {0x0000000C, 0x0000000C},
            {0x0000000D, 0x0000000D},
            {0x0000000E, 0x0000000E},
            {0x0000000F, 0x0000000F}
        };
        const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP DeviceMap = 
        {   
            Cs,
            sizeof(GenoaCsMap) / sizeof(GenoaCsMap[0]),
            &GenoaCsMap[0]
        };
        const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP* result;
        // Act 
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
        "Call DfXGetDeviceMapOnDie");
        result = DfXGetDeviceMapOnDie();
        // Assert
        if(DeviceMap.Type != result->Type || DeviceMap.Count != result->Count) 
          UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
        
        for (size_t i = 0; i < DeviceMap.Count; i++) 
        {
            if (DeviceMap.IDs[i].FabricID != result->IDs[i].FabricID ||
                DeviceMap.IDs[i].InstanceID != result->IDs[i].InstanceID) 
                {
                    UtSetTestStatus(Ut, AMD_UNIT_TEST_ABORTED);
                    break;
                }
        }
    }
    else
    {
        Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
            "Iteration '%s' is not implemented.", IterationName);
        UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }

    // if we run at any issue, The API is going to abort here.
    UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);

    Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
        "%s (Iteration: %s) Test ended.", TestName, IterationName);
}

AMD_UNIT_TEST_STATUS
EFIAPI
TestCleanUp (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  return AMD_UNIT_TEST_PASSED;
}

/**
 * main
 * @brief      Starting point for Execution
 *
 * @details    This routine:
 *              - Handles the command line arguments.
 *              - Declares the unit test framework.
 *              - Run the tests.
 *              - Deallocate the Unit test framework.
 *
 * @param      argc                     Argument count
 * @param      *argv[]                  Argument vector
 *
 * @retval     AMD_UNIT_TEST_PASSED     Function succeeded
 * @retval     NON-ZERO                 Error occurs
 */
int
main (
  int   argc,
  char  *argv[]
  )
{
  AMD_UNIT_TEST_STATUS Status;
  AMD_UNIT_TEST_FRAMEWORK Ut;

  // Initializing the UnitTest framework
  Status = UtInitFromArgs (
    &Ut,
    argc,
    argv
  );
  if (Status != AMD_UNIT_TEST_PASSED) {
    return Status;
  }

  // Logging the start of the test.
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "Test %s started. TestStatus is %s.", UtGetTestName (&Ut), UtGetTestStatusString (&Ut));

  // Running test.
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Running test.");
  UtRunTest (&Ut);

  // Freeing up all framework related allocated memories
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Test %s ended.", UtGetTestName (&Ut));
  UtDeinit (&Ut);

  return AMD_UNIT_TEST_PASSED;
}
