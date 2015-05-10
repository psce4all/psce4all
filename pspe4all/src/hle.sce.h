/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

typedef enum SceKernelDevkitVersion
{
    SCE_FIRMWARE_100 = 0x01000300,
    SCE_FIRMWARE_150 = 0x01050001,
    SCE_FIRMWARE_151 = 0x01050100,
    SCE_FIRMWARE_152 = 0x01050200,
    SCE_FIRMWARE_200 = 0x02000010,
    SCE_FIRMWARE_201 = 0x02000010, // Same as 2.00
    SCE_FIRMWARE_250 = 0x02050010,
    SCE_FIRMWARE_260 = 0x02060010,
    SCE_FIRMWARE_270 = 0x02070010,
    SCE_FIRMWARE_271 = 0x02070110,
    SCE_FIRMWARE_280 = 0x02080010,
    SCE_FIRMWARE_300 = 0x03000010,
    SCE_FIRMWARE_310 = 0x03010010,
    SCE_FIRMWARE_330 = 0x03030010,
    SCE_FIRMWARE_340 = 0x03040010,
    SCE_FIRMWARE_350 = 0x03050010,
    SCE_FIRMWARE_370 = 0x03070010,
    SCE_FIRMWARE_395 = 0x03090510,
    SCE_FIRMWARE_450 = 0x04050010,
    SCE_FIRMWARE_500 = 0x05000010,
    SCE_FIRMWARE_550 = 0x05050010
} SceKernelDevkitVersion;

typedef enum SceKernelErrorCode
{
    SCE_KERNEL_ERROR_OK                             = 0,
    SCE_KERNEL_ERROR_ERROR                          = 0x80020001,
    SCE_KERNEL_ERROR_NOTIMP                         = 0x80020002,
    SCE_KERNEL_ERROR_ILLEGAL_EXPCODE                = 0x80020032,
    SCE_KERNEL_ERROR_EXPHANDLER_NOUSE               = 0x80020033,
    SCE_KERNEL_ERROR_EXPHANDLER_USED                = 0x80020034,
    SCE_KERNEL_ERROR_SYCALLTABLE_NOUSED             = 0x80020035,
    SCE_KERNEL_ERROR_SYCALLTABLE_USED               = 0x80020036,
    SCE_KERNEL_ERROR_ILLEGAL_SYSCALLTABLE           = 0x80020037,
    SCE_KERNEL_ERROR_ILLEGAL_PRIMARY_SYSCALL_NUMBER = 0x80020038,
    SCE_KERNEL_ERROR_PRIMARY_SYSCALL_NUMBER_INUSE   = 0x80020039,
    SCE_KERNEL_ERROR_ILLEGAL_CONTEXT                = 0x80020064,
    SCE_KERNEL_ERROR_ILLEGAL_INTRCODE               = 0x80020065,
    SCE_KERNEL_ERROR_CPUDI                          = 0x80020066,
    SCE_KERNEL_ERROR_FOUND_HANDLER                  = 0x80020067,
    SCE_KERNEL_ERROR_NOTFOUND_HANDLER               = 0x80020068,
    SCE_KERNEL_ERROR_ILLEGAL_INTRLEVEL              = 0x80020069,
    SCE_KERNEL_ERROR_ILLEGAL_ADDRESS                = 0x8002006A,
    SCE_KERNEL_ERROR_ILLEGAL_INTRPARAM              = 0x8002006B,
    SCE_KERNEL_ERROR_ILLEGAL_STACK_ADDRESS          = 0x8002006C,
    SCE_KERNEL_ERROR_ALREADY_STACK_SET              = 0x8002006D,
    SCE_KERNEL_ERROR_NO_TIMER                       = 0x80020096,
    SCE_KERNEL_ERROR_ILLEGAL_TIMERID                = 0x80020097,
    SCE_KERNEL_ERROR_ILLEGAL_SOURCE                 = 0x80020098,
    SCE_KERNEL_ERROR_ILLEGAL_PRESCALE               = 0x80020099,
    SCE_KERNEL_ERROR_TIMER_BUSY                     = 0x8002009A,
    SCE_KERNEL_ERROR_TIMER_NOT_SETUP                = 0x8002009B,
    SCE_KERNEL_ERROR_TIMER_NOT_INUSE                = 0x8002009C,
    SCE_KERNEL_ERROR_UNIT_USED                      = 0x800200A0,
    SCE_KERNEL_ERROR_UNIT_NOUSE                     = 0x800200A1,
    SCE_KERNEL_ERROR_NO_ROMDIR                      = 0x800200A2,
    SCE_KERNEL_ERROR_IDTYPE_EXIST                   = 0x800200C8,
    SCE_KERNEL_ERROR_IDTYPE_NOT_EXIST               = 0x800200C9,
    SCE_KERNEL_ERROR_IDTYPE_NOT_EMPTY               = 0x800200CA,
    SCE_KERNEL_ERROR_UNKNOWN_UID                    = 0x800200CB,
    SCE_KERNEL_ERROR_UNMATCH_UID_TYPE               = 0x800200CC,
    SCE_KERNEL_ERROR_ID_NOT_EXIST                   = 0x800200CD,
    SCE_KERNEL_ERROR_NOT_FOUND_UIDFUNC              = 0x800200CE,
    SCE_KERNEL_ERROR_UID_ALREADY_HOLDER             = 0x800200CF,
    SCE_KERNEL_ERROR_UID_NOT_HOLDER                 = 0x800200D0,
    SCE_KERNEL_ERROR_ILLEGAL_PERM                   = 0x800200D1,
    SCE_KERNEL_ERROR_ILLEGAL_ARGUMENT               = 0x800200D2,
    SCE_KERNEL_ERROR_ILLEGAL_ADDR                   = 0x800200D3,
    SCE_KERNEL_ERROR_OUT_OF_RANGE                   = 0x800200D4,
    SCE_KERNEL_ERROR_MEM_RANGE_OVERLAP              = 0x800200D5,
    SCE_KERNEL_ERROR_ILLEGAL_PARTITION              = 0x800200D6,
    SCE_KERNEL_ERROR_PARTITION_INUSE                = 0x800200D7,
    SCE_KERNEL_ERROR_ILLEGAL_MEMBLOCKTYPE           = 0x800200D8,
    SCE_KERNEL_ERROR_MEMBLOCK_ALLOC_FAILED          = 0x800200D9,
    SCE_KERNEL_ERROR_MEMBLOCK_RESIZE_LOCKED         = 0x800200DA,
    SCE_KERNEL_ERROR_MEMBLOCK_RESIZE_FAILED         = 0x800200DB,
    SCE_KERNEL_ERROR_HEAPBLOCK_ALLOC_FAILED         = 0x800200DC,
    SCE_KERNEL_ERROR_HEAP_ALLOC_FAILED              = 0x800200DD,
    SCE_KERNEL_ERROR_ILLEGAL_CHUNK_ID               = 0x800200DE,
    SCE_KERNEL_ERROR_NOCHUNK                        = 0x800200DF,
    SCE_KERNEL_ERROR_NO_FREECHUNK                   = 0x800200E0,
    SCE_KERNEL_ERROR_LINKERR                        = 0x8002012C,
    SCE_KERNEL_ERROR_ILLEGAL_OBJECT                 = 0x8002012D,
    SCE_KERNEL_ERROR_UNKNOWN_MODULE                 = 0x8002012E,
    SCE_KERNEL_ERROR_NOFILE                         = 0x8002012F,
    SCE_KERNEL_ERROR_FILEERR                        = 0x80020130,
    SCE_KERNEL_ERROR_MEMINUSE                       = 0x80020131,
    SCE_KERNEL_ERROR_PARTITION_MISMATCH             = 0x80020132,
    SCE_KERNEL_ERROR_ALREADY_STARTED                = 0x80020133,
    SCE_KERNEL_ERROR_NOT_STARTED                    = 0x80020134,
    SCE_KERNEL_ERROR_ALREADY_STOPPED                = 0x80020135,
    SCE_KERNEL_ERROR_CAN_NOT_STOP                   = 0x80020136,
    SCE_KERNEL_ERROR_NOT_STOPPED                    = 0x80020137,
    SCE_KERNEL_ERROR_NOT_REMOVABLE                  = 0x80020138,
    SCE_KERNEL_ERROR_EXCLUSIVE_LOAD                 = 0x80020139,
    SCE_KERNEL_ERROR_LIBRARY_NOT_YET_LINKED         = 0x8002013A,
    SCE_KERNEL_ERROR_LIBRARY_FOUND                  = 0x8002013B,
    SCE_KERNEL_ERROR_LIBRARY_NOTFOUND               = 0x8002013C,
    SCE_KERNEL_ERROR_ILLEGAL_LIBRARY                = 0x8002013D,
    SCE_KERNEL_ERROR_LIBRARY_INUSE                  = 0x8002013E,
    SCE_KERNEL_ERROR_ALREADY_STOPPING               = 0x8002013F,
    SCE_KERNEL_ERROR_ILLEGAL_OFFSET                 = 0x80020140,
    SCE_KERNEL_ERROR_ILLEGAL_POSITION               = 0x80020141,
    SCE_KERNEL_ERROR_ILLEGAL_ACCESS                 = 0x80020142,
    SCE_KERNEL_ERROR_MODULE_MGR_BUSY                = 0x80020143,
    SCE_KERNEL_ERROR_ILLEGAL_FLAG                   = 0x80020144,
    SCE_KERNEL_ERROR_CANNOT_GET_MODULELIST          = 0x80020145,
    SCE_KERNEL_ERROR_PROHIBIT_LOADMODULE_DEVICE     = 0x80020146,
    SCE_KERNEL_ERROR_PROHIBIT_LOADEXEC_DEVICE       = 0x80020147,
    SCE_KERNEL_ERROR_UNSUPPORTED_PRX_TYPE           = 0x80020148,
    SCE_KERNEL_ERROR_ILLEGAL_PERM_CALL              = 0x80020149,
    SCE_KERNEL_ERROR_CANNOT_GET_MODULE_INFORMATION  = 0x8002014A,
    SCE_KERNEL_ERROR_ILLEGAL_LOADEXEC_BUFFER        = 0x8002014B,
    SCE_KERNEL_ERROR_ILLEGAL_LOADEXEC_FILENAME      = 0x8002014C,
    SCE_KERNEL_ERROR_NO_EXIT_CALLBACK               = 0x8002014D,
    SCE_KERNEL_ERROR_NO_MEMORY                      = 0x80020190,
    SCE_KERNEL_ERROR_ILLEGAL_ATTR                   = 0x80020191,
    SCE_KERNEL_ERROR_ILLEGAL_ENTRY                  = 0x80020192,
    SCE_KERNEL_ERROR_ILLEGAL_PRIORITY               = 0x80020193,
    SCE_KERNEL_ERROR_ILLEGAL_STACK_SIZE             = 0x80020194,
    SCE_KERNEL_ERROR_ILLEGAL_MODE                   = 0x80020195,
    SCE_KERNEL_ERROR_ILLEGAL_MASK                   = 0x80020196,
    SCE_KERNEL_ERROR_ILLEGAL_THID                   = 0x80020197,
    SCE_KERNEL_ERROR_UNKNOWN_THID                   = 0x80020198,
    SCE_KERNEL_ERROR_UNKNOWN_SEMID                  = 0x80020199,
    SCE_KERNEL_ERROR_UNKNOWN_EVFID                  = 0x8002019A,
    SCE_KERNEL_ERROR_UNKNOWN_MBXID                  = 0x8002019B,
    SCE_KERNEL_ERROR_UNKNOWN_VPLID                  = 0x8002019C,
    SCE_KERNEL_ERROR_UNKNOWN_FPLID                  = 0x8002019D,
    SCE_KERNEL_ERROR_UNKNOWN_MPPID                  = 0x8002019E,
    SCE_KERNEL_ERROR_UNKNOWN_ALMID                  = 0x8002019F,
    SCE_KERNEL_ERROR_UNKNOWN_TEID                   = 0x800201A0,
    SCE_KERNEL_ERROR_UNKNOWN_CBID                   = 0x800201A1,
    SCE_KERNEL_ERROR_DORMANT                        = 0x800201A2,
    SCE_KERNEL_ERROR_SUSPEND                        = 0x800201A3,
    SCE_KERNEL_ERROR_NOT_DORMANT                    = 0x800201A4,
    SCE_KERNEL_ERROR_NOT_SUSPEND                    = 0x800201A5,
    SCE_KERNEL_ERROR_NOT_WAIT                       = 0x800201A6,
    SCE_KERNEL_ERROR_CAN_NOT_WAIT                   = 0x800201A7,
    SCE_KERNEL_ERROR_WAIT_TIMEOUT                   = 0x800201A8,
    SCE_KERNEL_ERROR_WAIT_CANCEL                    = 0x800201A9,
    SCE_KERNEL_ERROR_RELEASE_WAIT                   = 0x800201AA,
    SCE_KERNEL_ERROR_NOTIFY_CALLBACK                = 0x800201AB,
    SCE_KERNEL_ERROR_THREAD_TERMINATED              = 0x800201AC,
    SCE_KERNEL_ERROR_SEMA_ZERO                      = 0x800201AD,
    SCE_KERNEL_ERROR_SEMA_OVF                       = 0x800201AE,
    SCE_KERNEL_ERROR_EVF_COND                       = 0x800201AF,
    SCE_KERNEL_ERROR_EVF_MULTI                      = 0x800201B0,
    SCE_KERNEL_ERROR_EVF_ILPAT                      = 0x800201B1,
    SCE_KERNEL_ERROR_MBOX_NOMSG                     = 0x800201B2,
    SCE_KERNEL_ERROR_MPP_FULL                       = 0x800201B3,
    SCE_KERNEL_ERROR_MPP_EMPTY                      = 0x800201B4,
    SCE_KERNEL_ERROR_WAIT_DELETE                    = 0x800201B5,
    SCE_KERNEL_ERROR_ILLEGAL_MEMBLOCK               = 0x800201B6,
    SCE_KERNEL_ERROR_ILLEGAL_MEMSIZE                = 0x800201B7,
    SCE_KERNEL_ERROR_ILLEGAL_SPADADDR               = 0x800201B8,
    SCE_KERNEL_ERROR_SPAD_INUSE                     = 0x800201B9,
    SCE_KERNEL_ERROR_SPAD_NOT_INUSE                 = 0x800201BA,
    SCE_KERNEL_ERROR_ILLEGAL_TYPE                   = 0x800201BB,
    SCE_KERNEL_ERROR_ILLEGAL_SIZE                   = 0x800201BC,
    SCE_KERNEL_ERROR_ILLEGAL_COUNT                  = 0x800201BD,
    SCE_KERNEL_ERROR_UNKNOWN_VTID                   = 0x800201BE,
    SCE_KERNEL_ERROR_ILLEGAL_VTID                   = 0x800201BF,
    SCE_KERNEL_ERROR_ILLEGAL_KTLSID                 = 0x800201C0,
    SCE_KERNEL_ERROR_KTLS_FULL                      = 0x800201C1,
    SCE_KERNEL_ERROR_KTLS_BUSY                      = 0x800201C2,
    SCE_KERNEL_ERROR_PM_INVALID_PRIORITY            = 0x80020258,
    SCE_KERNEL_ERROR_PM_INVALID_DEVNAME             = 0x80020259,
    SCE_KERNEL_ERROR_PM_UNKNOWN_DEVNAME             = 0x8002025A,
    SCE_KERNEL_ERROR_PM_PMINFO_REGISTERED           = 0x8002025B,
    SCE_KERNEL_ERROR_PM_PMINFO_UNREGISTERED         = 0x8002025C,
    SCE_KERNEL_ERROR_PM_INVALID_MAJOR_STATE         = 0x8002025D,
    SCE_KERNEL_ERROR_PM_INVALID_REQUEST             = 0x8002025E,
    SCE_KERNEL_ERROR_PM_UNKNOWN_REQUEST             = 0x8002025F,
    SCE_KERNEL_ERROR_PM_INVALID_UNIT                = 0x80020260,
    SCE_KERNEL_ERROR_PM_CANNOT_CANCEL               = 0x80020261,
    SCE_KERNEL_ERROR_PM_INVALID_PMINFO              = 0x80020262,
    SCE_KERNEL_ERROR_PM_INVALID_ARGUMENT            = 0x80020263,
    SCE_KERNEL_ERROR_PM_ALREADY_TARGET_PWRSTATE     = 0x80020264,
    SCE_KERNEL_ERROR_PM_CHANGE_PWRSTATE_FAILED      = 0x80020265,
    SCE_KERNEL_ERROR_PM_CANNOT_CHANGE_DEVPWR_STATE  = 0x80020266,
    SCE_KERNEL_ERROR_PM_NO_SUPPORT_DEVPWR_STATE     = 0x80020267,
    SCE_KERNEL_ERROR_DMAC_REQUEST_FAILED            = 0x800202BC,
    SCE_KERNEL_ERROR_DMAC_REQUEST_DENIED            = 0x800202BD,
    SCE_KERNEL_ERROR_DMAC_OP_QUEUED                 = 0x800202BE,
    SCE_KERNEL_ERROR_DMAC_OP_NOT_QUEUED             = 0x800202BF,
    SCE_KERNEL_ERROR_DMAC_OP_RUNNING                = 0x800202C0,
    SCE_KERNEL_ERROR_DMAC_OP_NOT_ASSIGNED           = 0x800202C1,
    SCE_KERNEL_ERROR_DMAC_OP_TIMEOUT                = 0x800202C2,
    SCE_KERNEL_ERROR_DMAC_OP_FREED                  = 0x800202C3,
    SCE_KERNEL_ERROR_DMAC_OP_USED                   = 0x800202C4,
    SCE_KERNEL_ERROR_DMAC_OP_EMPTY                  = 0x800202C5,
    SCE_KERNEL_ERROR_DMAC_OP_ABORTED                = 0x800202C6,
    SCE_KERNEL_ERROR_DMAC_OP_ERROR                  = 0x800202C7,
    SCE_KERNEL_ERROR_DMAC_CHANNEL_RESERVED          = 0x800202C8,
    SCE_KERNEL_ERROR_DMAC_CHANNEL_EXCLUDED          = 0x800202C9,
    SCE_KERNEL_ERROR_DMAC_PRIVILEGE_ADDRESS         = 0x800202CA,
    SCE_KERNEL_ERROR_DMAC_NO_ENOUGHSPACE            = 0x800202CB,
    SCE_KERNEL_ERROR_DMAC_CHANNEL_NOT_ASSIGNED      = 0x800202CC,
    SCE_KERNEL_ERROR_DMAC_CHILD_OPERATION           = 0x800202CD,
    SCE_KERNEL_ERROR_DMAC_TOO_MUCH_SIZE             = 0x800202CE,
    SCE_KERNEL_ERROR_DMAC_INVALID_ARGUMENT          = 0x800202CF,
    SCE_KERNEL_ERROR_MFILE                          = 0x80020320,
    SCE_KERNEL_ERROR_NODEV                          = 0x80020321,
    SCE_KERNEL_ERROR_XDEV                           = 0x80020322,
    SCE_KERNEL_ERROR_BADF                           = 0x80020323,
    SCE_KERNEL_ERROR_INVAL                          = 0x80020324,
    SCE_KERNEL_ERROR_UNSUP                          = 0x80020325,
    SCE_KERNEL_ERROR_ALIAS_USED                     = 0x80020326,
    SCE_KERNEL_ERROR_CANNOT_MOUNT                   = 0x80020327,
    SCE_KERNEL_ERROR_DRIVER_DELETED                 = 0x80020328,
    SCE_KERNEL_ERROR_ASYNC_BUSY                     = 0x80020329,
    SCE_KERNEL_ERROR_NOASYNC                        = 0x8002032A,
    SCE_KERNEL_ERROR_REGDEV                         = 0x8002032B,
    SCE_KERNEL_ERROR_NOCWD                          = 0x8002032C,
    SCE_KERNEL_ERROR_NAMETOOLONG                    = 0x8002032D,
    SCE_KERNEL_ERROR_NXIO                           = 0x800203E8,
    SCE_KERNEL_ERROR_IO                             = 0x800203E9,
    SCE_KERNEL_ERROR_NOMEM                          = 0x800203EA,
    SCE_KERNEL_ERROR_STDIO_NOT_OPENED               = 0x800203EB,
    SCE_KERNEL_ERROR_CACHE_ALIGNMENT                = 0x8002044C,
    SCE_KERNEL_ERROR_ERRORMAX                       = 0x8002044D
} SceKernelErrorCode;

typedef enum SceErrorCode
{
    SCE_OK                                          = 0,

    SCE_ERROR_NOT_INITIALIZED                       = 0x80000001,
    SCE_ERROR_UNMATECHED_VERSION                    = 0x80000002,
    SCE_ERROR_NOT_IMPLEMENTED                       = 0x80000003,
    SCE_ERROR_NOT_SUPPORTED                         = 0x80000004,
    SCE_ERROR_ALREADY                               = 0x80000020,
    SCE_ERROR_BUSY                                  = 0x80000021,
    SCE_ERROR_OUT_OF_MEMORY                         = 0x80000022,
    SCE_ERROR_PRIV_REQUIRED                         = 0x80000023,
    SCE_ERROR_TIMEOUT                               = 0x80000024,
    SCE_ERROR_NOT_FOUND                             = 0x80000025,
    SCE_ERROR_ILLEGAL_CONTEXT                       = 0x80000030,
    SCE_ERROR_CPUDI                                 = 0x80000031,
    SCE_ERROR_THREAD                                = 0x80000040,
    SCE_ERROR_SEMAPHORE                             = 0x80000041,
    SCE_ERROR_EVENTFLAG                             = 0x80000042,
    SCE_ERROR_TIMER                                 = 0x80000043,
    SCE_ERROR_ALARM                                 = 0x80000044
} SceErrorCode;

typedef enum SceArgumentErrorCode
{
    SCE_ERROR_INVALID_ID      = 0x80000100,
    SCE_ERROR_INVALID_NAME    = 0x80000101,
    SCE_ERROR_INVALID_INDEX   = 0x80000102,
    SCE_ERROR_INVALID_POINTER = 0x80000103,
    SCE_ERROR_INVALID_SIZE    = 0x80000104,
    SCE_ERROR_INVALID_FLAG    = 0x80000105,
    SCE_ERROR_INVALID_COMMAND = 0x80000106,
    SCE_ERROR_INVALID_MODE    = 0x80000107,
    SCE_ERROR_INVALID_FORMAT  = 0x80000108,
    SCE_ERROR_INVALID_VALUE   = 0x800001FE,
    SCE_ERROR_INVALID_ARG     = 0x800001FF
} SceArgumentErrorCode;

typedef enum SceUtilitySaveErrorCode
{
    SCE_UTILITY_SAVEDATA_ERROR_TYPE                 = 0x80110300,
    SCE_UTILITY_SAVEDATA_ERROR_LOAD_NO_MS           = 0x80110301,
    SCE_UTILITY_SAVEDATA_ERROR_LOAD_EJECT_MS        = 0x80110302,
    SCE_UTILITY_SAVEDATA_ERROR_LOAD_ACCESS_ERROR    = 0x80110305,
    SCE_UTILITY_SAVEDATA_ERROR_LOAD_DATA_BROKEN     = 0x80110306,
    SCE_UTILITY_SAVEDATA_ERROR_LOAD_NO_DATA         = 0x80110307,
    SCE_UTILITY_SAVEDATA_ERROR_LOAD_PARAM           = 0x80110308,
    SCE_UTILITY_SAVEDATA_ERROR_LOAD_NO_FILE         = 0x80110309,
    SCE_UTILITY_SAVEDATA_ERROR_LOAD_INTERNAL        = 0x8011030b,
    SCE_UTILITY_SAVEDATA_ERROR_SAVE_NO_MS           = 0x80110381,
    SCE_UTILITY_SAVEDATA_ERROR_SAVE_EJECT_MS        = 0x80110382,
    SCE_UTILITY_SAVEDATA_ERROR_SAVE_MS_NOSPACE      = 0x80110383,
    SCE_UTILITY_SAVEDATA_ERROR_SAVE_MS_PROTECTED    = 0x80110384,
    SCE_UTILITY_SAVEDATA_ERROR_SAVE_ACCESS_ERROR    = 0x80110385,
    SCE_UTILITY_SAVEDATA_ERROR_SAVE_DATA_BROKEN     = 0x80110386,
    SCE_UTILITY_SAVEDATA_ERROR_SAVE_PARAM           = 0x80110388,
    SCE_UTILITY_SAVEDATA_ERROR_SAVE_INTERNAL        = 0x8011038b,
    SCE_UTILITY_SAVEDATA_ERROR_DELETE_NO_MS         = 0x80110341,
    SCE_UTILITY_SAVEDATA_ERROR_DELETE_EJECT_MS      = 0x80110342,
    SCE_UTILITY_SAVEDATA_ERROR_DELETE_MS_PROTECTED  = 0x80110344,
    SCE_UTILITY_SAVEDATA_ERROR_DELETE_ACCESS_ERROR  = 0x80110345,
    SCE_UTILITY_SAVEDATA_ERROR_DELETE_NO_DATA       = 0x80110347,
    SCE_UTILITY_SAVEDATA_ERROR_DELETE_PARAM         = 0x80110348,
    SCE_UTILITY_SAVEDATA_ERROR_DELETE_INTERNAL      = 0x8011034b,
    SCE_UTILITY_SAVEDATA_ERROR_SIZES_NO_MS          = 0x801103C1,
    SCE_UTILITY_SAVEDATA_ERROR_SIZES_EJECT_MS       = 0x801103C2,
    SCE_UTILITY_SAVEDATA_ERROR_SIZES_ACCESS_ERROR   = 0x801103C5,
    SCE_UTILITY_SAVEDATA_ERROR_SIZES_DATA_BROKEN    = 0x801103C6,
    SCE_UTILITY_SAVEDATA_ERROR_SIZES_NO_DATA        = 0x801103C7,
    SCE_UTILITY_SAVEDATA_ERROR_SIZES_PARAM          = 0x801103C8,
    SCE_UTILITY_SAVEDATA_ERROR_SIZES_INTERNAL       = 0x801103Cb,
    SCE_UTILITY_SAVEDATA_ERROR_MC_NO_MS             = 0x80110321,
    SCE_UTILITY_SAVEDATA_ERROR_MC_EJECT_MS          = 0x80110322,
    SCE_UTILITY_SAVEDATA_ERROR_MC_MS_NOSPACE        = 0x80110323,
    SCE_UTILITY_SAVEDATA_ERROR_MC_MS_PROTECTED      = 0x80110324,
    SCE_UTILITY_SAVEDATA_ERROR_MC_ACCESS_ERROR      = 0x80110325,
    SCE_UTILITY_SAVEDATA_ERROR_MC_DATA_BROKEN       = 0x80110326,
    SCE_UTILITY_SAVEDATA_ERROR_MC_NO_DATA           = 0x80110327,
    SCE_UTILITY_SAVEDATA_ERROR_MC_PARAM             = 0x80110328,
    SCE_UTILITY_SAVEDATA_ERROR_MC_NO_FILE           = 0x80110329,
    SCE_UTILITY_SAVEDATA_ERROR_MC_SUSPEND_ERROR     = 0x8011032a,
    SCE_UTILITY_SAVEDATA_ERROR_MC_INTERNAL          = 0x8011032b,
    SCE_UTILITY_SAVEDATA_ERROR_MC_STATUS_ERROR      = 0x8011032c,
    SCE_UTILITY_SAVEDATA_ERROR_MC_SECUREFILE_FULL   = 0x8011032d

} SceUtilitySaveErrorCode;

typedef enum SceAudioErrorCode
{
    SCE_AUDIO_ERROR_NOT_INITIALIZED = 0x80260001,
    SCE_AUDIO_ERROR_OUTPUT_BUSY     = 0x80260002,
    SCE_AUDIO_ERROR_INVALID_CH      = 0x80260003,
    SCE_AUDIO_ERROR_PRIV_REQUIRED   = 0x80260004,
    SCE_AUDIO_ERROR_NOT_FOUND       = 0x80260005,
    SCE_AUDIO_ERROR_INVALID_SIZE    = 0x80260006,
    SCE_AUDIO_ERROR_INVALID_FORMAT  = 0x80260007,
    SCE_AUDIO_ERROR_NOT_RESERVED    = 0x80260008,
    SCE_AUDIO_ERROR_NOT_OUTPUT      = 0x80260009,
    SCE_AUDIO_ERROR_INVALID_FREQ    = 0x8026000A,
    SCE_AUDIO_ERROR_INVALID_VOLUME  = 0x8026000B
} SceAudioErrorCode;

typedef enum SceSasErrorCode
{
    SCE_SAS_ERROR_GRAIN_SAMPLES  = 0x80420001, // Granularity specification is invalid
    SCE_SAS_ERROR_VOICES         = 0x80420002, // Voice count specification is invalid
    SCE_SAS_ERROR_OUTPUT_MODE    = 0x80420003, // Output mode specification is invalid
    SCE_SAS_ERROR_FREQUENCY      = 0x80420004, // Frequency specification is invalid
    SCE_SAS_ERROR_ADDRESS        = 0x80420005, // Address alignment is invalid
    SCE_SAS_ERROR_VOICE_INDEX    = 0x80420010, // Voice number is invalid
    SCE_SAS_ERROR_NOISE_CLOCK    = 0x80420011, // Noise clock is invalid
    SCE_SAS_ERROR_PITCH          = 0x80420012, // Pitch specification is invalid
    SCE_SAS_ERROR_ADSR_MODE      = 0x80420013, // ADSR mode is invalid
    SCE_SAS_ERROR_ADPCM_SIZE     = 0x80420014, // ADPCM waveform data size is invalid
    SCE_SAS_ERROR_LOOP_MODE      = 0x80420015, // Loop mode or loop position specification is invalid
    SCE_SAS_ERROR_INVALID_STATE  = 0x80420016, // Cannot be executed in the current state (keyed-on, keyed-off, paused, etc.)
    SCE_SAS_ERROR_VOLUME         = 0x80420018, // Volume value for the voice is invalid
    SCE_SAS_ERROR_ADSR           = 0x80420019, // Either the ADSR value or the SustainLevel value is invalid
    SCE_SAS_ERROR_PCM_SIZE       = 0x8042001a, // PCM size specification is invalid
    SCE_SAS_ERROR_FX_TYPE        = 0x80420020, // Effect type is invalid
    SCE_SAS_ERROR_FX_FEEDBACK    = 0x80420021, // Effect feedback value is invalid
    SCE_SAS_ERROR_FX_DELAY       = 0x80420022, // Effect delay value is invalid
    SCE_SAS_ERROR_FX_VOLUME      = 0x80420023, // Effect volume value is invalid
    SCE_SAS_ERROR_FX_UNAVAILABLE = 0x80420024, // Effects setting function is unavailable in multichannel mode
    SCE_SAS_ERROR_BUSY           = 0x80420030, // sceSasCore() was called multiple times
    SCE_SAS_ERROR_NOTINITED      = 0x80420100, // Initialization has not been performed
    SCE_SAS_ERROR_ALREADYINITED  = 0x80420101, // Initialization has already been performed
} SceSasErrorCode;

enum
{
    SCE_SAS_VOICE_MAX            = 32
};

enum
{
    SCE_SAS_GRAIN_SAMPLES        = 256
};

enum
{
    SCE_SAS_VOLUME_MAX           = 4096
};

enum
{
    SCE_SAS_LOOP_DISABLE         = 0,
    SCE_SAS_LOOP_ENABLE          = 1,
};

enum
{
    SCE_SAS_PITCH_MIN            = 1,
    SCE_SAS_PITCH_BASE           = 0x1000,
    SCE_SAS_PITCH_MAX            = 0x4000,
    SCE_SAS_PITCH_BASE_SHIFT     = 12
};

enum
{
    SCE_SAS_NOISE_CLOCK_MAX      = 0x3F
};

enum
{
    SCE_SAS_ENVELOPE_HEIGHT_MAX  = 0x40000000,
    SCE_SAS_ENVELOPE_RATE_MAX    = 0x7FFFFFFF,
};

enum
{
    SCE_SAS_ADSR_MODE_LINEAR_INC  = 0,
    SCE_SAS_ADSR_MODE_LINEAR_DEC  = 1,
    SCE_SAS_ADSR_MODE_BENT_LINEAR = 2,
    SCE_SAS_ADSR_MODE_REVEXPONENT = 3,
    SCE_SAS_ADSR_MODE_EXPONENT    = 4,
    SCE_SAS_ADSR_MODE_DIRECT      = 5
};

typedef s32                             SceUID;
typedef u32                             SceSize;
typedef u8                              SceUChar;
typedef u32                             SceUInt;
typedef s32                             SceSSize;
typedef s32                             SceMode;
typedef s64                             SceOff;
typedef s64                             SceIores;

typedef struct SceSysMemPartitionInfo
{
    u32 size;
    u32 startaddr;
    u32 memsize;
    u32 attr;
} SceSysMemPartitionInfo;

typedef enum SceThreadAttributes
{
    SCE_KERNEL_THREAD_ATTR_VFPU         = 0x00004000,
    SCE_KERNEL_THREAD_ATTR_SCRATCH_SRAM = 0x00008000,
    SCE_KERNEL_THREAD_ATTR_NO_FILLSTACK = 0x00100000,
    SCE_KERNEL_THREAD_ATTR_CLEAR_STACK  = 0x00200000,
    SCE_KERNEL_THREAD_ATTR_SUSPENDED    = 0x08000000,
    SCE_KERNEL_THREAD_ATTR_USER         = 0x80000000,
    SCE_KERNEL_THREAD_ATTR_USBWLAN      = 0xA0000000,
    SCE_KERNEL_THREAD_ATTR_VSH          = 0xC0000000
} SceThreadAttributes;

typedef enum SceKernelThreadEventId
{
    SCE_KERNEL_THREAD_EVENTID_ALL     = 0xFFFFFFFF,
    SCE_KERNEL_THREAD_EVENTID_KERNEL  = 0xFFFFFFF8,
    SCE_KERNEL_THREAD_EVENTID_USER    = 0xFFFFFFF0,
    SCE_KERNEL_THREAD_EVENTID_CURRENT = 0
} SceKernelThreadEventId;

typedef enum SceKernelThreadEvent
{
    SCE_KERNEL_THREAD_EVENT_CREATE = 1,
    SCE_KERNEL_THREAD_EVENT_START  = 2,
    SCE_KERNEL_THREAD_EVENT_EXIT   = 4,
    SCE_KERNEL_THREAD_EVENT_DELETE = 8,
    SCE_KERNEL_THREAD_EVENT_ALL    = SCE_KERNEL_THREAD_EVENT_CREATE|SCE_KERNEL_THREAD_EVENT_START|SCE_KERNEL_THREAD_EVENT_EXIT|SCE_KERNEL_THREAD_EVENT_DELETE,
} SceKernelThreadEvent;

typedef class SceKernelThreadEntry
{
public:
    SceKernelThreadEntry(u32 entry = 0) : m_entry(entry)
    {
    }
    SceKernelThreadEntry(SceKernelThreadEntry const &entry) : m_entry(entry.m_entry)
    {
    }

    operator u32() const
    {
        return m_entry;
    }

    //int operator()(SceSize args, void *argp) { return *(Memory::addr< int (SceSize, void *) >(m_entry))(args, Memory::addr< void >(argp)); }

private:
    u32 m_entry;
} SceKernelThreadEntry;

typedef struct SceThreadStack
{
    SceUID                              thread_id;
    int                                 unk_4;
    int                                 unk_8;
    int                                 unk_C;
    int                               * value; /* of type 'int *' */
} SceThreadStack;

typedef struct SceSyscallStackInfo
{
    SceSyscallStackInfo               * next;
    SceThreadStack                    * stack;
    SceUInt                             stack_size;
} SceSyscallStackInfo;

typedef struct SceKernelSysClock
{
    SceUInt                             low;
    SceUInt                             hi;

    SceKernelSysClock()
    {
    }
    SceKernelSysClock(u64 value) : low(value&0xFFFFFFFF), hi(value>>32)
    {
    }

    operator u64() const
    {
        return (u64)low + ((u64)hi << 32);
    }

    SceKernelSysClock &operator =  (u64 value)
    {
        low = value&0xFFFFFFFF; hi = value>>32; return *this;
    }

    SceKernelSysClock &operator += (u64 value)
    {
        return *this = u64(*this) + value;
    }
    SceKernelSysClock &operator -= (u64 value)
    {
        return *this = u64(*this) - value;
    }
    SceKernelSysClock &operator *= (u64 value)
    {
        return *this = u64(*this) * value;
    }
    SceKernelSysClock &operator /= (u64 value)
    {
        return *this = u64(*this) / value;
    }

    SceKernelSysClock operator + (u64 value)
    {
        return SceKernelSysClock(u64(*this) + value);
    }
    SceKernelSysClock operator - (u64 value)
    {
        return SceKernelSysClock(u64(*this) - value);
    }
    SceKernelSysClock operator * (u64 value)
    {
        return SceKernelSysClock(u64(*this) * value);
    }
    SceKernelSysClock operator / (u64 value)
    {
        return SceKernelSysClock(u64(*this) / value);
    }
} SceKernelSysClock;


typedef struct SceKernelMsgPacket
{
    struct SceKernelMsgPacket         * next;
    SceUChar                            msg_priority;
    SceUChar                            reserved[3];
} SceKernelMsgPacket;


typedef struct SceKernelStructureSize
{
    SceSize                             size;
} SceKernelStructureSize;

typedef struct SceKernelStructureName
{
    char                                name[31 /*SceUID_NAME_MAX*/ + 1];
} SceKernelStructureName;

/* attribute */
enum
{
    SCE_KERNEL_AT_READABLE              = 0x0001U,
    SCE_KERNEL_AT_WRITABLE              = 0x0002U,
    SCE_KERNEL_AT_WAITABLE              = 0x0004U,
    SCE_KERNEL_AT_CANCELABLE            = 0x0008U,
    SCE_KERNEL_AT_DELETABLE             = 0x0010U,
    SCE_KERNEL_AT_UNK20                 = 0x0020U,
    SCE_KERNEL_AT_UNK40                 = 0x0040U,
    SCE_KERNEL_AT_UNK80                 = 0x0080U,
    SCE_KERNEL_AT_THFIFO                = 0x0000U,
    SCE_KERNEL_AT_THPRI                 = 0x0100U,
    SCE_KERNEL_AT_SINGLE                = 0x0000U,
    SCE_KERNEL_AT_MULTI                 = 0x0200U,
    SCE_KERNEL_AT_MSFIFO                = 0x0000U,
    SCE_KERNEL_AT_MSPRI                 = 0x0400U
};

enum
{
    SCE_KERNEL_AT_LEGAL_UID             = 0x000000FFU,
    SCE_KERNEL_AT_LEGAL_WAITQ           = 0x00000100U|SCE_KERNEL_AT_LEGAL_UID,
    SCE_KERNEL_AT_LEGAL_SEMA            = 0x00000100U|SCE_KERNEL_AT_LEGAL_UID,
    SCE_KERNEL_AT_LEGAL_EVF             = 0x00000200U|SCE_KERNEL_AT_LEGAL_WAITQ,
    SCE_KERNEL_AT_LEGAL_MBX             = 0x00000400U|SCE_KERNEL_AT_LEGAL_WAITQ,
    SCE_KERNEL_AT_LEGAL_FPL             = 0x00004000U|SCE_KERNEL_AT_LEGAL_WAITQ,
    SCE_KERNEL_AT_LEGAL_VPL             = 0x00004000U|SCE_KERNEL_AT_LEGAL_WAITQ,
    SCE_KERNEL_AT_LEGAL_MPP             = 0x00005000U|SCE_KERNEL_AT_LEGAL_WAITQ,
    SCE_KERNEL_AT_LEGAL_TH              = 0x80706000U|SCE_KERNEL_AT_LEGAL_UID
};

typedef struct SceKernelStructureAttr
{
    SceUInt                             attributes;
} SceKernelStructureAttr;

typedef struct SceKernelHeapOptParam
: SceKernelStructureSize
{
    int                                 alignment;
} SceKernelHeapOptParam;

typedef class SceKernelThreadEventHandler
{
public:
    SceKernelThreadEventHandler(u32 entry = 0) : m_entry(entry)
    {
    }
    SceKernelThreadEventHandler(SceKernelThreadEventHandler const &entry) : m_entry(entry.m_entry)
    {
    }

    operator u32() const
    {
        return m_entry;
    }

    //int operator()(int a0, int a1, void *a2) { return *(Memory::addr< int (int, int, void *) >(m_entry))(a0, a1, Memory::addr< void >(a2)); }

private:
    u32 m_entry;
} SceKernelThreadEventHandler;

typedef struct SceKernelThreadEventHandlerInfo
: SceKernelStructureSize
, SceKernelStructureName
{
    SceUID                              threadId;
    int                                 mask;
    SceKernelThreadEventHandler         handler;
    u32                                 cookie;
} SceKernelThreadEventHandlerInfo;

typedef class SceKernelCallbackFunction
{
public:
    SceKernelCallbackFunction(u32 entry = 0) : m_entry(entry)
    {
    }
    SceKernelCallbackFunction(SceKernelCallbackFunction const &entry) : m_entry(entry.m_entry)
    {
    }

    operator u32() const
    {
        return m_entry;
    }

    //int operator()(int a0, int a1, void *a2) { return *(Memory::addr< int (int, int, void *) >(m_entry))(a0, a1, Memory::addr< void >(a2)); }

private:
    u32 m_entry;
} SceKernelCallbackFunction;

typedef struct SceKernelCallbackInfo
: SceKernelStructureSize
, SceKernelStructureName
, SceKernelStructureAttr
{
    SceUID                              thread_id;
    SceKernelCallbackFunction           callback;
    u32                                 cookie;
    int                                 notify_count;
    int                                 notify_arg;
} SceKernelCallbackInfo;

enum
{
    SCE_KERNEL_EA_SINGLE = SCE_KERNEL_AT_SINGLE,
    SCE_KERNEL_EA_MULTI  = SCE_KERNEL_AT_MULTI
};

enum
{
    SCE_KERNEL_EW_AND               = 0x00U,
    SCE_KERNEL_EW_OR                = 0x01U,
    SCE_KERNEL_EW_CLEAR_ALL         = 0x10U,
    SCE_KERNEL_EW_CLEAR_PAT         = 0x20U,
    SCE_KERNEL_EW_CLEAR             = SCE_KERNEL_EW_CLEAR_ALL,
};

typedef struct SceKernelEventFlagInfo
: SceKernelStructureSize
, SceKernelStructureName
, SceKernelStructureAttr
{
    SceUInt                             initial_pattern;
    SceUInt                             current_pattern;
    int                                 waiting_threads;
} SceKernelEventFlagInfo;

typedef struct SceKernelEventFlagOptParam
: SceKernelStructureSize
{
} SceKernelEventFlagOptParam;


typedef struct SceKernelFplInfo
: SceKernelStructureSize
, SceKernelStructureName
, SceKernelStructureAttr
{
    int                                 block_size;
    int                                 pool_blocks;
    int                                 free_blocks;
    int                                 waiting_threads;
} SceKernelFplInfo;

typedef struct SceKernelFplOptParam
: SceKernelStructureSize
{
    SceSize                             alignment;
} SceKernelFplOptParam;


enum
{
    SCE_KERNEL_VA_THFIFO                = SCE_KERNEL_AT_THFIFO,
    SCE_KERNEL_VA_THPRI                 = SCE_KERNEL_AT_THPRI,
    SCE_KERNEL_VA_MEMBTM                = 0x4000U,
    SCE_KERNEL_VA_EXTEND                = 0x8000U
};

typedef struct SceKernelVplInfo
: SceKernelStructureSize
, SceKernelStructureName
, SceKernelStructureAttr
{
    int                                 pool_size;
    int                                 free_size;
    int                                 waiting_threads;
} SceKernelVplInfo;

typedef struct SceKernelVplOptParam
: SceKernelStructureSize
{
} SceKernelVplOptParam;


typedef struct SceKernelMbxInfo
: SceKernelStructureSize
, SceKernelStructureName
, SceKernelStructureAttr
{
    int                                 waiting_threads;
    int                                 total_messages;
    SceKernelMsgPacket                 *top_packet;
} SceKernelMbxInfo;

typedef struct SceKernelMbxOptParam
: SceKernelStructureSize
{
} SceKernelMbxOptParam;


typedef struct SceKernelMppInfo
: SceKernelStructureSize
, SceKernelStructureName
, SceKernelStructureAttr
{
    int                                 buffer_size;
    int                                 free_size;
    int                                 send_waiting_threads;
    int                                 recv_waiting_threads;
} SceKernelMppInfo;

typedef struct SceKernelMppOptParam
: SceKernelStructureSize
{
} SceKernelMppOptParam;


typedef struct SceKernelSemaInfo
: SceKernelStructureSize
, SceKernelStructureName
, SceKernelStructureAttr
{
    int                                 initial_count;
    int                                 current_count;
    int                                 maximum_count;
    int                                 waiting_threads;
} SceKernelSemaInfo;

typedef struct SceKernelSemaOptParam
: SceKernelStructureSize
{
} SceKernelSemaOptParam;

/* thread priority */
enum
{
    SCE_KERNEL_USER_HIGHEST_PRIORITY    = 16,
    SCE_KERNEL_MODULE_INIT_PRIORITY     = 32,
    SCE_KERNEL_USER_LOWEST_PRIORITY     = 111
};

enum
{
    SCE_KERNEL_EXIT_SUCCESS             = 0,
    SCE_KERNEL_EXIT_FAILURE             = 1
};

/* SceKernelThreadInfo.status */
enum
{
    SCE_KERNEL_THS_RUN                  = 0x01,
    SCE_KERNEL_THS_READY                = 0x02,
    SCE_KERNEL_THS_WAIT                 = 0x04,
    SCE_KERNEL_THS_SUSPEND              = 0x08,
    SCE_KERNEL_THS_WAITSUSPEND          = 0x0C,
    SCE_KERNEL_THS_DORMANT              = 0x10,
    SCE_KERNEL_THS_DEAD                 = 0x20
};

/* SceKernelThreadInfo.attributes */
enum
{
    SCE_KERNEL_TH_UMODE                 = 0x80000000U,
    SCE_KERNEL_TH_NO_FILLSTACK          = 0x00100000U,
    SCE_KERNEL_TH_CLEAR_STACK           = 0x00200000U,
    SCE_KERNEL_TH_LOW_STACK             = 0x00400000U,
    SCE_KERNEL_TH_USE_VFPU              = 0x00004000U
};

typedef struct SceKernelThreadInfo
: SceKernelStructureSize
, SceKernelStructureName
, SceKernelStructureAttr
{
    int                                 status;
    u32                                 entry;
    u32                                 stack_base;
    int                                 stack_size;
    u32                                 gp_reg;
    int                                 initial_priority;
    int                                 current_priority;
    int                                 wait_type;
    SceUID                              wait_id;
    int                                 wakeup_count;
    int                                 exit_status;
    SceKernelSysClock                   run_clocks;
    SceUInt                             intr_preempt_count;
    SceUInt                             thread_preempt_count;
    SceUInt                             release_count;
    int                                 notify_callback;
} SceKernelThreadInfo;

typedef struct SceKernelThreadOptParam
: SceKernelStructureSize
{
    SceUID                              stack_id;
} SceKernelThreadOptParam;

typedef struct SceKernelThreadRunStatus
: SceKernelStructureSize
{
    int                                 status;
    int                                 current_priority;
    int                                 wait_type;
    int                                 wait_id;
    int                                 wakeup_count;
    SceKernelSysClock                   run_clocks;
    SceUInt                             intr_preempt_count;
    SceUInt                             thread_preempt_count;
    SceUInt                             release_count;
    int                                 notify_callback;
} SceKernelThreadRunStatus;


typedef SceUInt(*SceKernelAlarmHandler)(void *cookie);

typedef struct SceKernelAlarmInfo
: SceKernelStructureSize
{
    SceKernelSysClock                   schedule;
    SceKernelAlarmHandler               handler;
    void                              * cookie;
} SceKernelAlarmInfo;

typedef SceUInt(*SceKernelVTimerHandler)(SceUID uid, SceKernelSysClock *base, SceKernelSysClock *current, void *cookie);

typedef struct SceKernelVTimerInfo
: SceKernelStructureSize
, SceKernelStructureName
{
    int                                 active;
    SceKernelSysClock                   base;
    SceKernelSysClock                   current;
    SceKernelSysClock                   schedule;
    SceKernelVTimerHandler              handler;
    void                              * cookie;
} SceKernelVTimerInfo;

typedef struct SceKernelVTimerOptParam
: SceKernelStructureSize
{
} SceKernelVTimerOptParam;

typedef struct SceKernelModuleInfo
: SceKernelStructureSize
{
    char                                nsegment;
    char                                reserved[3];
    int                                 segmentaddr[4];
    int                                 segmentsize[4];
    unsigned int                        entry_addr;
    unsigned int                        gp_value;
    unsigned int                        text_addr;
    unsigned int                        text_size;
    unsigned int                        data_size;
    unsigned int                        bss_size;
    unsigned short                      attribute;
    unsigned char                       version[2];
    char                                name[27];
    char                                terminal;
} SceKernelModuleInfo;

typedef struct SceKernelLMOption
: SceKernelStructureSize
{
    SceUID                              mpidtext;
    SceUID                              mpiddata;
    unsigned int                        flags;
    char                                position;
    char                                access;
    char                                creserved[2];
} SceKernelLMOption;

typedef struct SceKernelSMOption
: SceKernelStructureSize
{
    SceUID                              mpidstack;
    SceSize                             stacksize;
    int                                 priority;
    unsigned int                        attribute;
} SceKernelSMOption;

typedef struct SceThreadContext
{
    unsigned int                        type;    // 0x000
    unsigned int                        gpr[31]; // 0x004-0x07C
    unsigned int                        fpr[32]; // 0x080-0x0FC
    unsigned int                        fc31;    // 0x100-0x104
    unsigned int                        hi;      // 0x108
    unsigned int                        lo;      // 0x10C
    unsigned int                        SR;      // 0x110
    unsigned int                        EPC;     // 0x110
    unsigned int                        field_114;
    unsigned int                        field_118;
} SceThreadContext;

typedef struct SceSCContext
{
    unsigned int                        status;
    unsigned int                        epc;
    unsigned int                        sp;
    unsigned int                        ra;
    unsigned int                        k1;
    unsigned int                        unk[3];
} SceSCContext;

typedef struct SceKernelLoadExecParam
: SceKernelStructureSize
{
    SceUInt                             args;
    void                              * argp;
    char const                        * key;
} SceKernelLoadExecParam;

typedef struct ScePspDateTime
{
    unsigned short                      year;
    unsigned short                      month;
    unsigned short                      day;
    unsigned short                      hour;
    unsigned short                      minute;
    unsigned short                      second;
    unsigned int                        microsecond;
} ScePspDateTime;

/* SceIoStat.st_mode */
enum
{
    SCE_STM_FMT    = (0xF << 12),
    SCE_STM_FLNK   = (0x4 << 12),
    SCE_STM_FREG   = (0x2 << 12),
    SCE_STM_FDIR   = (0x1 << 12),

    SCE_STM_RWXU   = 00700,
    SCE_STM_RUSR   = 00400,
    SCE_STM_WUSR   = 00200,
    SCE_STM_XUSR   = 00100,

    SCE_STM_RWXG   = 00070,
    SCE_STM_RGRP   = 00040,
    SCE_STM_WGRP   = 00020,
    SCE_STM_XGRP   = 00010,

    SCE_STM_RWXO   = 00007,
    SCE_STM_ROTH   = 00004,
    SCE_STM_WOTH   = 00002,
    SCE_STM_XOTH   = 00001,

    SCE_STM_RWXUGO = (SCE_STM_RWXU|SCE_STM_RWXG|SCE_STM_RWXO),
    SCE_STM_RUGO   = (SCE_STM_RUSR|SCE_STM_RGRP|SCE_STM_ROTH),
    SCE_STM_WUGO   = (SCE_STM_WUSR|SCE_STM_WGRP|SCE_STM_WOTH),
    SCE_STM_XUGO   = (SCE_STM_XUSR|SCE_STM_XGRP|SCE_STM_XOTH)
};

typedef struct SceIoStat
{
    SceMode                             st_mode;
    unsigned int                        st_attr;
    SceOff                              st_size;
    ScePspDateTime                      st_ctime;
    ScePspDateTime                      st_atime;
    ScePspDateTime                      st_mtime;
    unsigned int                        st_private[6];
} SceIoStat;

typedef struct SceIoDirent
{
    SceIoStat                           d_stat;
    char                                d_name[256];
    void                              * d_private;
} SceIoDirent;

/** The maximum number of hardware channels. */
enum
{
    SCE_AUDIO_CHANNEL_MAX = 8
};

/** Used to request the next available hardware channel. */
enum
{
    SCE_AUDIO_NEXT_CHANNEL = -1
};

enum SceAudioFormat
{
    SCE_AUDIO_FORMAT_STEREO = 0,
    SCE_AUDIO_FORMAT_MONO   = 0x10
};

/** Structure storing a stack (for CALL/RET) */
typedef struct SceGeStack
{
    /** The stack buffer */
    unsigned int stack[8];
} SceGeStack;

/** Structure storing a GE context */
typedef struct SceGeContext
{
    /** The context buffer */
    unsigned int buffer[512];
} SceGeContext;

/** Typedef for a GE callback */
typedef void(*SceGeCallback)(int id, void *arg);

/** Structure to hold the callback data */
typedef struct SceGeCallbackData
{
    /** GE callback for the signal interrupt */
    SceGeCallback signal_func;
    /** GE callback argument for signal interrupt */
    void        * signal_arg;
    /** GE callback for the finish interrupt */
    SceGeCallback finish_func;
    /** GE callback argument for finish interrupt */
    void        * finish_arg;
} SceGeCallbackData;

/** List of arguments when enqueuing a list */
typedef struct SceGeListArgs
{
    /** Size of the structure (16) */
    u32            size;
    /** Pointer to a context */
    SceGeContext * ctx;
    /** Number of stacks to use */
    u32            numStacks;
    /** Pointer to the stacks (unused) */
    SceGeStack   * stacks;
} SceGeListArgs;

/** State of a display list, returned by sceGeListSync() and sceGeDrawSync() */
typedef enum SceGeListState
{
    /** The list has been completed */
    SCE_GE_LIST_COMPLETED,
    /** The list is queued but not executed yet */
    SCE_GE_LIST_QUEUED,
    /** The list is currently being executed */
    SCE_GE_LIST_DRAWING,
    /** The list was stopped because it encountered stall address */
    SCE_GE_LIST_STALLING,
    /** The list is paused because of a signal */
    SCE_GE_LIST_PAUSED
} SceGeListState;

/** State of a display list, internally */
typedef enum SceGeDisplayListState
{
    /** No state assigned, the list is empty */
    SCE_GE_DL_STATE_NONE      = 0,
    /** The list has been queued */
    SCE_GE_DL_STATE_QUEUED    = 1,
    /** The list is being executed */
    SCE_GE_DL_STATE_RUNNING   = 2,
    /** The list was completed and will be removed */
    SCE_GE_DL_STATE_COMPLETED = 3,
    /** The list has been paused by a signal */
    SCE_GE_DL_STATE_PAUSED    = 4
} SceGeDisplayListState;

/** Signal state of a display list */
typedef enum SceGeDisplayListSignal
{
    /** No signal received */
    SCE_GE_DL_SIGNAL_NONE  = 0,
    /** The break signal was received */
    SCE_GE_DL_SIGNAL_BREAK = 1,
    /** The pause signal was received */
    SCE_GE_DL_SIGNAL_PAUSE = 2,
    /** The sync signal was received */
    SCE_GE_DL_SIGNAL_SYNC  = 3
} SceGeDisplayListSignal;

/** Structure holding a display list */
typedef struct SceGeDisplayList
{
    /** Next display list of the queue */
    SceGeDisplayList     * next;
    /** Previous display list */
    SceGeDisplayList     * prev;
    /** Current display list state */
    SceGeDisplayListState  state;
    /** Current display list received signal */
    SceGeDisplayListSignal signal;
    /** 1 if context is up to date, 0 otherwise */
    u8                     ctxUpToDate;
    /* (padding) */
    char                   unused11;
    /** The display list context */
    SceGeContext         * ctx; // 12
    /** The display list flags */
    int                    flags;
    /** Pointer to the list of commands */
    void                 * list; // 20
    /** Pointer to the stall address, where the display list will stop being executed */
    void                 * stall; // 24
    /** Internal data */
    int                    unk28;
    /** Internal data */
    int                    unk32;
    /** Internal data */
    int                    unk36;
    /** Internal data */
    int                    unk40;
    /** Internal data */
    int                    unk44;
    /** Internal data */
    int                    unk48;
    /** The callbacks id set with sceGeSetCallback() */
    short                  cbId; // 52
    /** Some argument passed to the interrupt handler when calling the subintrs */
    u16                    unk54;
    /** The number of stacks of the display list */
    short                  numStacks; // 56
    /** The offset of the current stack */
    u16                    stackOff; // 58
    /** A pointer to the list of stacks */
    SceGeStack           * stack; // 60
} SceGeDisplayList; // size: 64

enum SceIsofsIoctlCommand
{
    SCE_ISOFS_GET_PVD           = 0x01020001,
    SCE_ISOFS_GET_PTBL          = 0x01020002,
    SCE_ISOFS_GET_SECTOR_SIZE   = 0x01020003,
    SCE_ISOFS_GET_FILEPOINTER   = 0x01020004,
    SCE_ISOFS_SEEK_FILE         = 0x01010005,
    SCE_ISOFS_GET_LBA           = 0x01020006,
    SCE_ISOFS_GET_FSIZE         = 0x01020007,
    SCE_ISOFS_UNCACHED_READ     = 0x01030008,
};
