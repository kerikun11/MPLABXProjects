#include <xc.h>

/* This address defines the starting addres of the user memory. */
#define BOOT_CONFIG_USER_MEMORY_START_ADDRESS                   0x00001800

#define BOOT_ERASE_BLOCK_SIZE                                   1024

/* Defines the first page to start erasing.  We will set this to the
 * first block of user program memory, but in some applications the user
 * might want to change this so there is a block of user memory that
 * doesn't ever get changed when a new app is loaded (serial number,
 * board specific calibration data, etc.).  This option allows the user
 * to make such a region at the start of the memory. */
#define	BOOT_CONFIG_USER_MEMORY_ERASE_PAGE_START                (BOOT_CONFIG_USER_MEMORY_START_ADDRESS/BOOT_ERASE_BLOCK_SIZE)


#if defined(__PIC24FJ128GC010__) || defined(__PIC24FJ128GC006__)
    /* This address defines the address at which programming ends (NOTE: this
     * address does not get programmed as it is the address where programming
     * ends).  This address must be word aligned.  This option is for if the
     * config words are not going to be programmed.
     */
    #define BOOT_CONFIG_USER_MEMORY_END_ADDRESS_NO_CONFIGS      0x00015400

    /* This address defines the address at which programming ends (NOTE: this
     * address does not get programmed as it is the address where programming
     * ends).  This address must be word aligned.  This option is for if the
     * config words are going to be programmed.
     */
    #define BOOT_CONFIG_USER_MEMORY_END_ADDRESS_CONFIGS         0x000157F8
    #define BOOT_MEMORY_CONFIG_START_ADDRESS                    0x000157F8
    #define BOOT_MEMORY_CONFIG_END_ADDRESS                      0x00015800
#elif defined(__PIC24FJ64GC010__) || defined(__PIC24FJ64GC006__)
    #define BOOT_CONFIG_USER_MEMORY_END_ADDRESS_NO_CONFIGS      0x0000A800
    #define BOOT_CONFIG_USER_MEMORY_END_ADDRESS_CONFIGS         0x0000ABF8
    #define BOOT_MEMORY_CONFIG_START_ADDRESS                    0x0000ABF8
    #define BOOT_MEMORY_CONFIG_END_ADDRESS                      0x0000AC00
#else
    #error "This bootloader only covers the PIC24FJ256GB110 family devices.  Please see another folder for the bootloader appropriate for the selected device."
#endif

#define BOOT_CONFIG_USER_MEMORY_ERASE_PAGE_END_NO_CONFIGS       ((BOOT_CONFIG_USER_MEMORY_END_ADDRESS_NO_CONFIGS/BOOT_ERASE_BLOCK_SIZE)-1)
#define BOOT_CONFIG_USER_MEMORY_ERASE_PAGE_END_CONFIGS          ((BOOT_MEMORY_CONFIG_END_ADDRESS/BOOT_ERASE_BLOCK_SIZE)-1)
