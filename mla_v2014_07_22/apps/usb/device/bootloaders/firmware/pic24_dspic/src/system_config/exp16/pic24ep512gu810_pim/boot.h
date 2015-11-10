#include <xc.h>

/* This address defines the starting addres of the user memory. */
#define BOOT_CONFIG_USER_MEMORY_START_ADDRESS                   0x00002000

#define BOOT_ERASE_BLOCK_SIZE                                   2048

/* Defines the first page to start erasing.  We will set this to the
 * first block of user program memory, but in some applications the user
 * might want to change this so there is a block of user memory that
 * doesn't ever get changed when a new app is loaded (serial number,
 * board specific calibration data, etc.).  This option allows the user
 * to make such a region at the start of the memory. */
#define	BOOT_CONFIG_USER_MEMORY_ERASE_PAGE_START                (BOOT_CONFIG_USER_MEMORY_START_ADDRESS/BOOT_ERASE_BLOCK_SIZE)

#define BOOT_MEMORY_CONFIG_START_ADDRESS                        0x00F80000
#define BOOT_MEMORY_CONFIG_END_ADDRESS                          0x00F80014

#if defined(__PIC24EP256GU810__) || defined(__PIC24EP256GU814__)
    /* This address defines the address at which programming ends (NOTE: this
     * address does not get programmed as it is the address where programming
     * ends).  This address must be word aligned.  This option is for if the
     * config words are not going to be programmed.
     */
    #define BOOT_CONFIG_USER_MEMORY_END_ADDRESS_NO_CONFIGS      0x0002AC00

    /* This address defines the address at which programming ends (NOTE: this
     * address does not get programmed as it is the address where programming
     * ends).  This address must be word aligned.  This option is for if the
     * config words are going to be programmed.
     */
    #define BOOT_CONFIG_USER_MEMORY_END_ADDRESS_CONFIGS         0x0002AC00

#elif defined(__PIC24EP512GU810__) || defined(__PIC24EP512GU814__)
    #define BOOT_CONFIG_USER_MEMORY_END_ADDRESS_NO_CONFIGS      0x00055800
    #define BOOT_CONFIG_USER_MEMORY_END_ADDRESS_CONFIGS         0x00055800
#else
    #error "This bootloader only covers the PIC24EP512GU814 family devices.  Please see another folder for the bootloader appropriate for the selected device."
#endif

#define BOOT_CONFIG_USER_MEMORY_ERASE_PAGE_END_NO_CONFIGS       ((BOOT_CONFIG_USER_MEMORY_END_ADDRESS_NO_CONFIGS/BOOT_ERASE_BLOCK_SIZE)-1)
#define BOOT_CONFIG_USER_MEMORY_ERASE_PAGE_END_CONFIGS          ((BOOT_MEMORY_CONFIG_END_ADDRESS/BOOT_ERASE_BLOCK_SIZE)-1)
